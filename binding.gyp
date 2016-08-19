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
        '-flto',
        '-funroll-loops',
        '<@(march)',
    ],
    'conditions': [
      [ 'OS=="win"', {
        'defines': [
          'FARMHASH_OPTIONAL_BUILTIN_EXPECT'
        ]
      }, {  # OS != "win"
        'variables' : {
          'march': '<!(test -z "${FARMHASH_NOMARCH:-}" && echo -march=native || :)'
        },
      }]
    ],
    'xcode_settings': {
      'OTHER_CPLUSPLUSFLAGS': [
        '-fexceptions',
        '-Wall',
        '-Ofast',
        '-funroll-loops',
        '<@(march)',
      ]
    },
    'configurations': {
      'Release': {
        'msvs_settings': {
          'VCCLCompilerTool': {
            'ExceptionHandling': 1,
          }
        }
      }
    }
  }, {
    'target_name': 'farmhash-legacy',
    'defines': [
      'FARMHASH_LEGACY'
    ],
    'sources': [
       'src/upstream/farmhash-legacy.cc',
       'src/bindings.cc'
    ],
    'include_dirs': [
      '<!(node -e "require(\'nan\')")'
    ],
    'cflags_cc': [
        '-fexceptions',
        '-Wall',
        '-Ofast',
        '-flto',
        '-funroll-loops',
        '<@(march)',
    ],
    'conditions': [
      [ 'OS=="win"', {
        'defines': [
          'FARMHASH_OPTIONAL_BUILTIN_EXPECT'
        ]
      }, {  # OS != "win"
        'variables' : {
          'march': '<!(test -z "${FARMHASH_NOMARCH:-}" && echo -march=native || :)'
        },
      }]
    ],
    'xcode_settings': {
      'OTHER_CPLUSPLUSFLAGS': [
        '-fexceptions',
        '-Wall',
        '-Ofast',
        '-funroll-loops',
        '<@(march)',
      ]
    },
    'configurations': {
      'Release': {
        'msvs_settings': {
          'VCCLCompilerTool': {
            'ExceptionHandling': 1,
          }
        }
      }
    }
  }]
}
