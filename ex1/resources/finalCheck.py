#!/usr/bin/env python3

import os
import sys
import tempfile
import zipfile

PROVIDED_EURO_FILES = ['eurovision.h', 'list.h', 'set.h']
PROVIDED_MAP_FILES = ['map.h']
PROVIDED_TEST_FILES = ['test_utilities.h', 'map_example_test.c',
                       'eurovisionTests.h', 'eurovisionTests.c',
                       'eurovisionTestsMain.c']
PROVIDED_MISC_FILES = ['finalCheck.py']
PROVIDED_FILES = PROVIDED_EURO_FILES + PROVIDED_MAP_FILES + PROVIDED_TEST_FILES + PROVIDED_MISC_FILES

MINIMUM_REQUIRED_TOP_DIR_FILES = ['eurovision.c','map.c']
MINIMUM_REQUIRED_TOP_DIR_FILES_CASE_INSENSITIVE = ['dry.pdf', 'makefile']

def main():
    if len(sys.argv) != 2:
        print("Usage: %s <zipfile>" % sys.argv[0])
        return
    with tempfile.TemporaryDirectory() as path:
        zip_ref = zipfile.ZipFile(sys.argv[1], 'r')
        zip_ref.extractall(path)
        zip_ref.close()
        check_folder(path)

def check_folder(path):
    files = os.listdir(path)
    found_errors = check_folder_contents(files,
                                         MINIMUM_REQUIRED_TOP_DIR_FILES,
                                         MINIMUM_REQUIRED_TOP_DIR_FILES_CASE_INSENSITIVE,
                                         PROVIDED_FILES)
    if found_errors:
        print("\nThere are errors in the ZIP file.")
    else:
        print("\nThe ZIP file contains all the necessary files.")

def check_folder_contents(contents, required_files, required_files_case_insensitive,
                          forbidden_files, prefix=''):
    found_errors = False
    for filename in required_files:
        pretty_name = os.path.join(prefix, filename)
        if filename in contents:
            print('Found required file/directory:', pretty_name)
        else:
            found_errors = True
            print('ERROR: Missing required file/directory:', pretty_name)

    for filename in required_files_case_insensitive:
        pretty_name = os.path.join(prefix, filename)
        if filename.lower() in map(str.lower, contents):
            print('Found required file/directory:', pretty_name)
        else:
            found_errors = True
            print('ERROR: Missing required file/directory:', pretty_name)

    for filename in forbidden_files:
        if filename in contents:
            found_errors = True
            print('ERROR: Found provided file/directory:', os.path.join(prefix, filename))

    for filename in contents:
        pretty_name = os.path.join(prefix, filename)
        if (filename in required_files or
            filename in forbidden_files or
            filename.lower() in required_files_case_insensitive):
            # already checked above
            continue

        if filename.endswith('.c') or filename.endswith('.h'):
            print('Found C file:', pretty_name)
            continue

        found_errors = True
        print('ERROR: Found unexpected file/directory:', pretty_name)

    return found_errors

if __name__ == '__main__':
    main()
