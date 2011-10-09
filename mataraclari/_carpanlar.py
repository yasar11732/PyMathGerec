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
from itertools import combinations as _combinations
from _mathGerecleri import primes as _primes

def TekilAsalCarpanlar(sayi):
    return sorted(set(asalCarpanlar(sayi)))

def asalCarpanlar(sayi):
    muhtemel_asal_carpanlar = _primes(int(sayi ** 0.5) + 1)

    # Bir tane daha asal çarpan olabilir.
    
    current = sayi
    asal_carpanlar = []
    for i in muhtemel_asal_carpanlar:

        if current == 1:

            break

        while True:

            if current % i == 0:
                asal_carpanlar.append(i)
                current = current / i
            else:
                break

    if current != 1:
        # Son bir asal atlandı...
        asal_carpanlar.append(current)
    return asal_carpanlar
    
def carpanlar(sayi):
    asal_carpanlar = asalCarpanlar(sayi)
    if len(asal_carpanlar) == 1:
        return [1] + [sayi]
    
    sonuc = [1]
    for i in range(1,len(asal_carpanlar)):
        
        for carpilcaklar in _combinations(asal_carpanlar, i):
            
            carpim = carpilcaklar[0]
            for j in range(1,i):
                carpim *= carpilcaklar[j]
            sonuc.append(carpim)

    sonuc.append(sayi)
    return sorted(tuple(set(sonuc)))
            

            
            
            
