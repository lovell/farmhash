# Copyright 2014 Lovell Fuller and others.
# SPDX-License-Identifier: Apache-2.0

{
  'targets': [{
    'target_name': 'farmhash-<!(node -p \"require(\'../platform\')\")',
    'sources': [
       'upstream/farmhash.cc',
       'bindings.cc'
    ],
    'include_dirs' : [
      "<!(node -p \"require('node-addon-api').include_dir\")"
    ],
    'dependencies': [
      "<!(node -p \"require('node-addon-api').gyp\")"
    ],
    'cflags_cc': [
      '-Wall',
      '-Os',
      '-funroll-loops'
    ],
    'cflags!': [ '-fno-exceptions' ],
    'cflags_cc!': [ '-fno-exceptions' ],
    'conditions': [
      ['OS=="win"', {
        'defines': [
          'FARMHASH_OPTIONAL_BUILTIN_EXPECT'
        ]
      }]
    ],
    'defines': [
      'FARMHASH_DEBUG=0',
      'NAPI_VERSION=9'
    ],
    'xcode_settings': {
      'CLANG_CXX_LIBRARY': 'libc++',
      'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
      'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES',
      'MACOSX_DEPLOYMENT_TARGET': '10.7',
      'OTHER_CPLUSPLUSFLAGS': [
        '-fexceptions',
        '-Wall',
        '-Oz',
        '-funroll-loops'
      ]
    },
    'configurations': {
      'Release': {
        'msvs_settings': {
          'VCCLCompilerTool': {
            'ExceptionHandling': 1,
            'Optimization': 1,
            'DisableSpecificWarnings': ['4244', '4307', '4319']
          }
        }
      }
    }
  }]
}
