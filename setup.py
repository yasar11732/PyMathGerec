from distutils.core import setup, Extension
import os

pack_dir = os.path.join(os.path.dirname(__file__),"mataraclari")

mathgerecleri = Extension('mataraclari._mathGerecleri',
                    sources = ['mataraclari/mathgerecler.c'])

setup (name="mataraclari",
       version = '0.1',
       description = 'Provides some math utilities',
       packages = ["mataraclari"],
       package_dir = {"mataraclari":pack_dir},
       ext_modules = [mathgerecleri]
       )
