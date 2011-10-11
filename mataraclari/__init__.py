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
from _mathGerecleri import *
from _carpanlar import *

def sadelestir(*args):
    k = obeb(*args)
    return [i/k for i in args]

def EsitlemeKatsayilar(*args):
    k = okek(*args)
    return [k/i for i in args]

def asalMi(sayi):

    eleyenler = primes(int(sayi ** 0.5))

    for asal in eleyenler:
        if sayi % asal == 0:
            return False

    return True

def asallarToplami(sayi):
    """
    Verilen çift sayiyi iki asalin toplami şeklinde
    yazar. Eğer birden fazla asal toplam döndürülebiliyorsa,
    yine de tek bir tane döndürür.
    >>> asallarToplami(8)
    (5,3)
    >>> asallarToplami(10)
    (7,3)
    """

    if sayi % 2 != 0:
        raise ValueError(u"Çift sayı girmelisiniz.")

    asallar = primes(sayi)

    for i in asallar:
        if sayi - i in asallar:
            return (sayi - i, i)

def asallarToplamiHepsi(sayi):

    if sayi % 2 != 0:
        raise ValueError("Çift sayı giriniz.")

    asallar = primes(sayi)
    toplamlar = []

    yarisi = len(asallar) / 2

    for i in range(yarisi + 1):
        asal = asallar[i]
        if sayi - asal in asallar:
            toplamlar.append((sayi-asal, asal))

    return toplamlar
