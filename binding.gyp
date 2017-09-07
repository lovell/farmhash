{
  'targets': [{
    'target_name': 'farmhash',
    'sources': [
       'src/upstream/farmhash.cc',
       'src/bindings.cc'
    ],
    'include_dirs': [
      '<!(node -e "require(\'nan\')")'
    ],
    'cflags_cc': [
        '-fexceptions',
        '-Wall',
        '-Ofast',
        '-funroll-loops'
    ],
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
