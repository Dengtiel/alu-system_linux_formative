from distutils.core import setup, Extension

module = Extension(
    'statsmodule',
    sources=['statsmodule.c'],
    extra_compile_args=['-O2'],
    libraries=['m'],
)

setup(
    name='statsmodule',
    version='1.0',
    description='Fast statistics C extension',
    ext_modules=[module],
)
