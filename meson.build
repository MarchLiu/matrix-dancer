project('matrix-dancer', ['c', 'cpp'],
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++17', 'c_std=c11'])

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_MESON_LIBRARY']

blas_dep = dependency('openblas')
lapack_dep = dependency('lapack')

shared_library('matrix-dancer', 'dance.cpp', 'dancer.c',
               install : true,
               cpp_args : lib_args,
               dependencies : [blas_dep, lapack_dep]
)

dancer_test = executable('dancer-test', 'dance.cpp', 'dancer.c', 'dancer_test.cpp',
                         install : true,
                         cpp_args : lib_args,
                         dependencies : [blas_dep, lapack_dep]
)

qsort_test = executable('qsort-test', 'dancer.c', 'test_qsort.c',
                        install : true,
                        cpp_args : lib_args,
                        dependencies : [blas_dep, lapack_dep]
)

top_k_test = executable('top-k-test', 'utils.cpp', 'dancer.c', 'test_top_k.cpp',
                        install : true,
                        cpp_args : lib_args,
                        dependencies : [blas_dep, lapack_dep]
)

reduce_test = executable('reduce-test', 'utils.cpp', 'dancer.c', 'test_reduce.cpp',
                        install : true,
                        cpp_args : lib_args,
                        dependencies : [blas_dep, lapack_dep]
)