from distutils.core import setup, Extension

mathgerecleri = Extension('mathGerecleri',
                    sources = ['mathgerecler.c'])

setup (name="MathGerec",
       version = '0.1',
       description = 'Provides some math utilities',
       ext_modules = [mathgerecleri]
       )
