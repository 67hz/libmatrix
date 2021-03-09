project('libmatrix', 'cpp',
  version : '0.0.1',
  default_options :
  ['warning_level=3',
    'cpp_std=c++17'])

incdir = 'include'

libmatrix = library('matrix',
  'Mat.h',
  include_directories: incdir,
  install : true,
  version : '0.0.1',
  soversion : '0')

libmatrix_dep = declare_dependency(include_directories : incdir,
  link_with : libmatrix)


# add check2 as proper test dependency
#catch2_dep = dependency('Catch2')

testdatadir = meson.current_source_dir() + '/test/'

mattest = executable('matrixtest',
  'test/Matrix_test.cpp',
  include_directories: [incdir],
  dependencies : libmatrix_dep)
# dependencies : catch2_dep)
  #install : true)


test('basic', mattest, workdir: testdatadir)
