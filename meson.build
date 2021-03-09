project('libmatrix', 'cpp',
  version : '0.0.1',
  default_options :
  ['warning_level=3',
    'cpp_std=c++17'])

incdir = 'include'
data = 'test/data'

libmatrix_dep = library('matrix',
  'Mat.h',
  include_directories: incdir,
  version : '0.0.1',
  soversion : '0')


# add check2 as proper test dependency
#catch2_dep = dependency('Catch2')

mattest = executable('matrixtest',
  'test/Matrix_test.cpp',
  include_directories: [incdir],
  link_with : libmatrix_dep)
# dependencies : catch2_dep)
  #install : true)

testdatadir = meson.current_source_dir() + '/test/'

test('basic', mattest, workdir: testdatadir)
