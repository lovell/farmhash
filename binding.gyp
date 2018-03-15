{
  'targets': [{
    'target_name': 'farmhash',
    'sources': [
       'src/upstream/farmhash.cc',
       'src/bindings.cc'
    ],
    'include_dirs' : [
          "<!@(node -p \"require('node-addon-api').include\")"
    ],
    'dependencies': ["<!(node -p \"require('node-addon-api').gyp\")"],
    'cflags_cc': [
        '-Wall',
        '-Ofast',
        '-funroll-loops'
    ],
    'cflags!': [ '-fno-exceptions' ],
    'cflags_cc!': [ '-fno-exceptions' ],
    'conditions': [
      ['OS=="win"', {
        'defines': [
          'FARMHASH_OPTIONAL_BUILTIN_EXPECT'
        ]
      }],
      ['OS=="linux"', {
        'cflags_cc': [
          '-flto',
        ]
      }],
      ['target_arch!="arm"', {
        'cflags_cc': [
          '-march=native'
        ]
      }]
    ],
    'xcode_settings': {
      "CLANG_CXX_LIBRARY": "libc++",
      'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
      'MACOSX_DEPLOYMENT_TARGET': '10.7',
      'OTHER_CPLUSPLUSFLAGS': [
        '-fexceptions',
        '-Wall',
        '-march=native',
        '-Ofast',
        '-funroll-loops'
      ]
    },
    'configurations': {
      'Release': {
        'msvs_settings': {
          'VCCLCompilerTool': {
            'ExceptionHandling': 1,
            'DisableSpecificWarnings': ['4244', '4307', '4319']
          }
        }
      }
    }
  }]
}
