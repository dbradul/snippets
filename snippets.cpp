// stacktrace.h (c) 2008, Timo Bingmann from http://idlebox.net/
// published under the WTFPL v2.0

#ifndef _STACKTRACE_H_
#define _STACKTRACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>

/** Print a demangled stack backtrace of the caller function to FILE* out. */
static inline void print_stacktrace(FILE *out = stderr, unsigned int max_frames = 63)
{
    fprintf(out, "stack trace:\n");

    // storage array for stack trace address data
    void* addrlist[max_frames+1];

    // retrieve current stack addresses
    int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));

    if (addrlen == 0) {
	fprintf(out, "  <empty, possibly corrupt>\n");
	return;
    }

    // resolve addresses into strings containing "filename(function+address)",
    // this array must be free()-ed
    char** symbollist = backtrace_symbols(addrlist, addrlen);

    // allocate string which will be filled with the demangled function name
    size_t funcnamesize = 256;
    char* funcname = (char*)malloc(funcnamesize);

    // iterate over the returned symbol lines. skip the first, it is the
    // address of this function.
    for (int i = 1; i < addrlen; i++)
    {
	char *begin_name = 0, *begin_offset = 0, *end_offset = 0;

	// find parentheses and +address offset surrounding the mangled name:
	// ./module(function+0x15c) [0x8048a6d]
	for (char *p = symbollist[i]; *p; ++p)
	{
	    if (*p == '(')
		begin_name = p;
	    else if (*p == '+')
		begin_offset = p;
	    else if (*p == ')' && begin_offset) {
		end_offset = p;
		break;
	    }
	}

	if (begin_name && begin_offset && end_offset
	    && begin_name < begin_offset)
	{
	    *begin_name++ = '\0';
	    *begin_offset++ = '\0';
	    *end_offset = '\0';

	    // mangled name is now in [begin_name, begin_offset) and caller
	    // offset in [begin_offset, end_offset). now apply
	    // __cxa_demangle():

	    int status;
	    char* ret = abi::__cxa_demangle(begin_name,
					    funcname, &funcnamesize, &status);
	    if (status == 0) {
		funcname = ret; // use possibly realloc()-ed string
		fprintf(out, "  %s : %s+%s\n",
			symbollist[i], funcname, begin_offset);
	    }
	    else {
		// demangling failed. Output function name as a C function with
		// no arguments.
		fprintf(out, "  %s : %s()+%s\n",
			symbollist[i], begin_name, begin_offset);
	    }
	}
	else
	{
	    // couldn't parse the line? print the whole line.
	    fprintf(out, "  %s\n", symbollist[i]);
	}
    }

    free(funcname);
    free(symbollist);
}

#endif // _STACKTRACE_H_




////////////////////////////////////////////////////////////////////////
QJsonDocument doc = QJsonDocument::fromJson(prop.toUtf8());
QJsonObject obj = doc.object();
int callID = obj["callID"].toInt(-1);
qDebug() << "callID: "  << callID;
////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////
#include <execinfo.h>
#define PRINT_CALLSTACK \
    do \
    { \
        void *buffer[200]; \
        int n = backtrace(buffer,20); \
        char **str = backtrace_symbols(buffer, n); \
        for (int i = 0; i < n; i++) \
        { \
            printf("%d:  %s\n", i, str[i]); \
        } \
    } while(0) \
////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////
// possible implementation for QJsonValue::fromVariant
////////////////////////////////////////////////////////////////////////
QJsonValue QJsonValue::fromVariant(const QVariant& value)
{
    QJsonValue retValue;

    switch(value.type())
    {
        case QMetaType::QStringList:
        {
            QJsonArray result;

            foreach(QString listItem, value.toStringList())
            {
                result.push_back(listItem);
            }

            retValue = QJsonValue(result);
            break;
        }

        // recursevely unwrap nested lists
        case QMetaType::QVariantList:
        {
            QJsonArray result;

            foreach(QVariant listItem, value.toList())
            {
                result.push_back(QVariant2QJson(listItem));
            }

            retValue = QJsonValue(result);
            break;
        }

        case QMetaType::QVariantHash:
        {
            QJsonObject result;
            ////result.fromVariantHash(value.toHash());

            QVariantHash::const_iterator it = value.toHash().constBegin();
            for (; it != value.toHash().constEnd(); ++it)
            {
                result.insert(it.key(), QJsonValue::fromVariant(it.value()));
            }

            retValue = QJsonValue(result);
            break;

        }

        case QMetaType::QVariantMap:
        {
            QJsonObject result;
            result.fromVariantMap(value.toMap());

            retValue = QJsonValue(result);
            break;

        }

        case QMetaType::Int:
        case QMetaType::UInt:
        case QMetaType::Long:
        case QMetaType::LongLong:
        case QMetaType::ULongLong:
        case QMetaType::Double:
            retValue = QJsonValue(value.toDouble());
            break;

        case  QMetaType::Bool:
            retValue = QJsonValue(value.toBool());
            break;

        case QMetaType::QString:
            retValue = QJsonValue(value.toString());
            break;

        default:
            LOG_ERROR("Unrecognized type: '%s'", value.typeName());
            retValue = QJsonValue(value.toJsonValue());
    }

    return retValue;
}


////////////////////////////////////////////////////////////////////////
// serialize to/from JSON
////////////////////////////////////////////////////////////////////////
// serialize to JSON
QJsonArray arr0;
arr0.append(QJsonValue("xxx"));
QJsonArray arr;
arr.append(arr0);
QJsonObject jsonObj;
jsonObj.insert("args", arr);
QJsonDocument doc(jsonObj);
QString serializedDoc = doc.toJson(QJsonDocument::Compact);
qDebug() << "serializedDoc: " << serializedDoc;

// deserialize from JSON
QJsonObject objMessage      = QJsonDocument::fromJson(serializedDoc.toUtf8()).object();
QVariantList args           = objMessage["args"].toArray().toVariantList();

qDebug() << "list.at(0).type: "     << args.at(0).type();
qDebug() << "list.at(0).typeName: " << args.at(0).typeName();


////////////////////////////////////////////////////////////////////////
// Qt calculate hash for image
////////////////////////////////////////////////////////////////////////
QImage image;
QCryptographicHash hash(QCryptographicHash::Md5);
for (int row = 0; row < image.height(); ++row)
{
    hash.addData(reinterpret_cast<const char*>(image.scanLine(row)), image.width() * 4);
}
QString actualHash = hash.result().toHex();



////////////////////////////////////////////////////////////////////////
// Timestamp
////////////////////////////////////////////////////////////////////////
#include <sys/time.h>

long long current_timestamp()
{
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
    return milliseconds;
}



////////////////////////////////////////////////////////////////////////
// config.h
////////////////////////////////////////////////////////////////////////

static bool _DebugEnabled()
{
    QByteArray loggingEnv = qgetenv("__DEBUG");
    if (loggingEnv.isEmpty())
        return false;
    return true;
}

static bool _DEBUG = _DebugEnabled();

#define TRC_GROUP "MyGroup"

#define TRC_DEBUG_FUNC_ENTER(s, f,  args...)  do { if (_DEBUG) { printf( TRC_GROUP "\t" ); printf( "%s: ENTER: " f, __PRETTY_FUNCTION__, ##args); printf ("\n"); } } while(0)
#define TRC_DEBUG_FUNC_EXIT(s)                do { if (_DEBUG) { printf( TRC_GROUP "\t" ); printf( "%s: EXIT", __PRETTY_FUNCTION__); printf ("\n"); } } while(0)
#define TRC_DEBUG(s, f,  args...) do { if (_DEBUG) { printf( TRC_GROUP "\t" ); printf( "%s: " f, __PRETTY_FUNCTION__, ##args); printf ("\n"); } } while(0)
#define TRC_INFO( s, f,  args...) do { if (_DEBUG) { printf( TRC_GROUP "\t" ); printf( "%s: " f, __PRETTY_FUNCTION__, ##args); printf ("\n"); } } while(0)
#define TRC_WARN( s, f,  args...) do { if (_DEBUG) { printf( TRC_GROUP "\t" ); printf( "%s: " f, __PRETTY_FUNCTION__, ##args); printf ("\n"); } } while(0)
#define TRC_ERROR(s, f,  args...) do { if (_DEBUG) { printf( TRC_GROUP "\t" ); printf( "%s: " f, __PRETTY_FUNCTION__, ##args); printf ("\n"); } } while(0)
#define TRC_FATAL(s, f,  args...) do { if (_DEBUG) { printf( TRC_GROUP "\t" ); printf( "%s: " f, __PRETTY_FUNCTION__, ##args); printf ("\n"); } } while(0)


[...]
TRC_DEBUG_FUNC_ENTER(0U, "");
TRC_DEBUG_FUNC_EXIT (0U);
TRC_INFO(0U, "New request is received: request='%s'", request.getHeaderStr().c_str());


////////////////////////////////////////////////////////////////////////////////////////////////////
// Read key-value pairs
struct Flag_name_value {
    std::string name;
    std::string value;
};

std::string input("ab=xy z,time a=1s");
std::istringstream iss(input);

std::vector<Flag_name_value> flags;

std::string token;
Flag_name_value flag;
while (std::getline(iss, token, ',')) {
    size_t pos   = token.find('=');
    flag.name    = token.substr(0, pos);
    flag.value   = token.substr(pos + 1);
    flags.push_back(flag);
}

