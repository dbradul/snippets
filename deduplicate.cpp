// cl /EHsc /nologo /W4 /MTd deduplicate.cpp /I boost-1.46.1\include /link /libpath:boost-1.46.1\lib bcrypt.lib

#pragma warning(disable: 4512) // assignment operator could not be generated

#include <stddef.h>
#include <fstream>
#include <ios>
#include <iostream>
#include <ostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>
#include <boost/bimap.hpp>
#include <boost/filesystem.hpp>
#include <boost/scope_exit.hpp>
#include <windows.h>
#include <bcrypt.h> // http://msdn.microsoft.com/en-us/library/aa376217(VS.85).aspx
using namespace std;
using namespace boost;
using namespace boost::filesystem;

vector<unsigned char> sha256(const vector<unsigned char>& v) {
    BCRYPT_ALG_HANDLE  hAlg         = NULL;
    BCRYPT_HASH_HANDLE hHash        = NULL;
    DWORD              cbData       = 0;
    DWORD              cbHash       = 0;
    DWORD              cbHashObject = 0;

    BOOST_SCOPE_EXIT((&hAlg)) {
        if (hAlg) {
            BCryptCloseAlgorithmProvider(hAlg, 0);
        }
    } BOOST_SCOPE_EXIT_END

    BOOST_SCOPE_EXIT((&hHash)) {
        if (hHash) {
            BCryptDestroyHash(hHash);
        }
    } BOOST_SCOPE_EXIT_END

    if (BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_SHA256_ALGORITHM, NULL, 0) < 0) {
        throw runtime_error("BCryptOpenAlgorithmProvider() failed.");
    }

    if (BCryptGetProperty(hAlg, BCRYPT_OBJECT_LENGTH, reinterpret_cast<unsigned char *>(&cbHashObject), sizeof(DWORD), &cbData, 0) < 0) {
        throw runtime_error("BCryptGetProperty() failed.");
    }

    vector<unsigned char> HashObject(cbHashObject);

    if (BCryptGetProperty(hAlg, BCRYPT_HASH_LENGTH, reinterpret_cast<unsigned char *>(&cbHash), sizeof(DWORD), &cbData, 0) < 0) {
        throw runtime_error("BCryptGetProperty() failed.");
    }

    vector<unsigned char> ret(cbHash);

    if (BCryptCreateHash(hAlg, &hHash, HashObject.data(), HashObject.size(), NULL, 0, 0) < 0) {
        throw runtime_error("BCryptCreateHash() failed.");
    }

    if (BCryptHashData(hHash, const_cast<unsigned char *>(v.data()), v.size(), 0) < 0) {
        throw runtime_error("BCryptHashData() failed.");
    }

    if (BCryptFinishHash(hHash, ret.data(), ret.size(), 0) < 0) {
        throw runtime_error("BCryptFinishHash() failed.");
    }

    return ret;
}

string hexify(const vector<unsigned char>& v) {
    string s(2 * v.size(), 'x');

    string::iterator k = s.begin();

    for (auto i = v.begin(); i != v.end(); ++i) {
        *k++ = "0123456789ABCDEF"[*i >> 4];
        *k++ = "0123456789ABCDEF"[*i & 0x0F];
    }

    return s;
}

vector<unsigned char> read_file(const string& name) {
    ifstream f(name, ios_base::binary);

    vector<unsigned char> ret;

    const int N = 64 * 1024;

    vector<char> buf;

    while (f) {
        buf.resize(N);
        f.read(&buf[0], N);
        buf.resize(static_cast<size_t>(f.gcount()));
        ret.insert(ret.end(), buf.begin(), buf.end());
    }

    return ret;
}

void read_batch_file(const string& batch_file_name, bimap<string, string>& hash_file) {
    ifstream batch(batch_file_name);

    const regex r("@REM ([[:xdigit:]]{64}) (.+)");

    for (string s; getline(batch, s); ) {
        smatch m;

        if (regex_match(s, m, r)) {
            hash_file.insert(bimap<string, string>::value_type(m[1], m[2]));
        }
    }
}

void write_batch_file(const string& batch_file_name, bimap<string, string>& hash_file) {
    ofstream batch(batch_file_name, ios_base::app);

    for (recursive_directory_iterator i(initial_path()), end; i != end; ++i) {
        const string f = i->path().string().substr(initial_path().string().size() + 1);

        if (!is_regular_file(i->path()) || f == batch_file_name || hash_file.right.find(f) != hash_file.right.end()) {
            continue;
        }

        const string h = hexify(sha256(read_file(f)));

        const bimap<string, string>::left_const_iterator j = hash_file.left.find(h);

        if (j == hash_file.left.end()) {
            hash_file.insert(bimap<string, string>::value_type(h, f));

            batch << "@REM " << h << " " << f << endl;
        } else {
            cout << "del \"" << f << "\"" << endl;

            batch << "@copy \"" << j->second << "\" \"" << f << "\"" << endl;
        }
    }

    batch << "@REM **********" << endl;
}

int main() {
    const string batch_file_name("reduplicate.bat");

    bimap<string, string> hash_file;

    read_batch_file(batch_file_name, hash_file);

    write_batch_file(batch_file_name, hash_file);
}
