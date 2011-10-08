import unittest
from _carpanlar import carpanlar, asalCarpanlar
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


if __name__ == "__main__":
    unittest.main()

        
