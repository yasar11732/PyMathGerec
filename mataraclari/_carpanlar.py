# -*- coding: utf-8 -*-
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
            

            
            
            
