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
