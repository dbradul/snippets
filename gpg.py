import os
import gnupg

from pprint import pprint
from os import listdir
from os.path import isfile, join

encrypted_path ='/home/dbhost/.gnupg'
key_paths = ['/home/dbhost/.gnupg/public.key',
             '/home/dbhost/.gnupg/private.key']

PASSPHRASE = 'passphrase'
ENCRYPTED_FILE_EXTENTION = '.asc'


def initialize_gpg(key_paths):

    def extend_kwargs(f, **extra):
        def inner(*args, **kwargs):
            kwargs.update(**extra)
            return f(*args, **kwargs)
        return inner

    gpg = gnupg.GPG()
    gpg._handle_io__orig = gpg._handle_io
    gpg._handle_io = extend_kwargs(gpg._handle_io, passphrase=PASSPHRASE)

    print('Importing keys...')

    for path in key_paths:
        key_data = open(path, 'rb').read()
        import_result = gpg.import_keys(key_data)
        print('Imported keys from %s: %s' % (path, import_result.count))
        print('     result: %s' % import_result.results)

    gpg._handle_io = gpg._handle_io__orig

    return gpg



def remove_gpg_from_path(path):
    return os.path.splitext(path)[0]


def decrypt_file(gpg, encrypted_path):

    with open(encrypted_path, 'rb') as a_file:

        decrypted_path = remove_gpg_from_path(encrypted_path)

        result = gpg.decrypt_file(a_file, output=decrypted_path, passphrase=PASSPHRASE+'dd')

        return result, decrypted_path


def encrypt_data(gpg):
    public_keys = gpg.list_keys()
    private_keys = gpg.list_keys(True)
    pprint(public_keys)
    pprint(private_keys)

    unencrypted_string = 'Who are you? How did you get in my house?'
    encrypted_data = gpg.encrypt(unencrypted_string, private_keys.fingerprints[0])
    encrypted_string = str(encrypted_data)
    decrypted_data = gpg.decrypt(encrypted_string, passphrase='passphrase')

    print('ok: ', decrypted_data.ok)
    print('status: ', decrypted_data.status)
    print('stderr: ', decrypted_data.stderr)
    print('decrypted string: ', decrypted_data.data)


def main(key_paths, encrypted_path):
    gpg = initialize_gpg(key_paths)

    encrypted_files = [
        join(encrypted_path, file)
        for file in listdir(encrypted_path)
        if isfile(join(encrypted_path, file)) and
           file.lower().endswith(ENCRYPTED_FILE_EXTENTION)
    ]

    for encrypted_file in encrypted_files:
        print('Decrypting file: %s' % encrypted_file)
        result, decrypted_file = decrypt_file(gpg, encrypted_file)
        result_msg = {'status': result.status}
        result_msg['details'] = f'output file: {decrypted_file}' if result.ok else result.stderr
        print('     result: %s' % (result_msg))
        # print('     result: %s' % pformat(result_msg))


if __name__ == '__main__':
    main(key_paths, encrypted_path)
