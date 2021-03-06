# -*- coding: utf-8 -*-
"""
    This Python module is part of the mataraclari package, which provides
    some mathematical shortcuts for Python.

    
    Copyright (C) 2011  Yaşar Arabacı

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

"""
import unittest
from __init__ import *
from random import randint

class carpanlarTests(unittest.TestCase):

    def testCarpanlarSanity(self):

        # 100 rasgele sayi dene
        for i in range(100):
            sayi = randint(0,1000000)
            carp = carpanlar(sayi)

            for carpan in carp:
                self.assertEqual(sayi % carpan,0)

    def testAsalCarpanlarSanity(self):
        # 100 sayi dene
        for i in range(100):
            sayi = randint(0,1000000)
            carpanlar = asalCarpanlar(sayi)
            sonuc = reduce(int.__mul__,carpanlar)
            self.assertEqual(sayi, sonuc)


class asallarToplamiTests(unittest.TestCase):
    asallar = primes(1000)

    def testAsallarToplamiSanity(self):
        for i in range(100):
            girdi = 2 * randint(2,500)
            asal1, asal2 = asallarToplami(girdi)
            self.assertEqual(asal1 + asal2, girdi)
            self.assertTrue(asal1 in self.asallar)
            self.assertTrue(asal2 in self.asallar)

    def testAsallarToplamiHepsiSanity(self):

        for i in range(100):
            girdi = 2  * randint(2,500)
            for asal1, asal2 in asallarToplamiHepsi(girdi):
                self.assertEqual(asal1 + asal2, girdi)
                self.assertTrue(asal1 in self.asallar)
                self.assertTrue(asal2 in self.asallar)
if __name__ == "__main__":
    unittest.main()

        
