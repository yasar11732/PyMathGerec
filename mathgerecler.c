#include <Python.h>
#include <math.h>

struct bigcouples {
unsigned long long first;
unsigned long long second;
};

void swap(struct bigcouples *couple){
    unsigned long long backup;
    backup = couple->first;
    couple->first = couple->second;
    couple->second = backup;
}

void bubbleSort(unsigned long long numbers[], int array_size)
{
  int i, j;
  unsigned long long temp;
 
  for (i = (array_size - 1); i > 0; i--)
  {
    for (j = 1; j <= i; j++)
    {
      if (numbers[j-1] > numbers[j])
      {
        temp = numbers[j-1];
        numbers[j-1] = numbers[j];
        numbers[j] = temp;
      }
    }
  }
}


unsigned long long obeb_couples(struct bigcouples couple) {
/* Finds bigges common divedor of to numbers*/
    if(couple.first == 0) {
        if (couple.second)
            return couple.second;
        else
            return 1L;
    }
    if(couple.second == 0)
        return couple.first;

    while(1) {
        if (couple.second > couple.first)
            swap(&couple);
        couple.first = fmod(couple.first, couple.second);
        if(!couple.first)
            return couple.second;
    }

}

unsigned long long okek_couples(struct bigcouples couple) {
    /* Common divident of two numbers*/
    return (couple.first/obeb_couples(couple)) * couple.second;
}

int ParseArguments(unsigned long long arr[],int size, PyObject *args) {
    /* Get arbitrary number of positive numbers from Py_Tuple */
    int i;
    unsigned long long typeCheck;
    PyObject *temp_p;


    for (i=0;i<size;i++) {
        temp_p = PyTuple_GetItem(args,i);
        if (PyInt_Check(temp_p)) {
            typeCheck = (unsigned long long)PyInt_AsLong(temp_p);
            if(typeCheck == -1.0 && PyErr_Occurred())
                return NULL;
        }

        else if (PyLong_Check(temp_p)) {
            typeCheck = (unsigned long long)PyLong_AsLong(temp_p);
            if(typeCheck == -1.0 && PyErr_Occurred())
                return NULL;
        }

        else {
            PyErr_SetString(PyExc_ValueError,"All arguments need to be either int or long");
            return 0;
        }

        if (typeCheck < 1){
            PyErr_SetString(PyExc_ValueError,"All argument must be bigger than 0");
            return 0;
        }

        arr[i] = typeCheck;

    }

    return 1;
}


static PyObject *
math_okek(PyObject *self, PyObject *args)
{
    const int TupleSize = PyTuple_Size(args);
    int i;
    struct bigcouples temp;
    unsigned long long current;
    if(!TupleSize) {
        PyErr_SetString(PyExc_TypeError,"You must supply at least one argument.");
        return NULL;
    }

    unsigned long long nums [TupleSize];

    if(!ParseArguments(nums, TupleSize, args))
            return NULL;

    bubbleSort(nums, TupleSize);

    current = nums[0];

    for (i = 1; i< TupleSize; i++) {
        temp.first = current;
        temp.second = nums[i];
        current = okek_couples(temp);
    }
    return Py_BuildValue("K",current);
}


static PyObject *
math_obeb(PyObject *self, PyObject *args) {
    PyObject *temp_p;
    struct bigcouples temp;
    unsigned long long current;
    int i;
    const int TupleSize = PyTuple_Size(args);
    if (!TupleSize) {
        PyErr_SetString(PyExc_TypeError,"You must supply at least one int or long object.");
        return NULL;
    }
    unsigned long long nums [TupleSize];
    
    if(!ParseArguments(nums, TupleSize, args))
            return NULL;

    current = nums[0];

    for (i = 1; i < TupleSize ; i++) {

        temp.first = current;
        temp.second = nums[i];
        current = obeb_couples(temp);
        if (current == 1)
            break;
    }
    return Py_BuildValue("i",current); 
}


static PyObject *
math_primes(PyObject *self, PyObject *args)
{
    PyObject *m;
    Py_ssize_t arr_size;
    double kok;
    unsigned int i;
    unsigned int j;

    if(!PyArg_ParseTuple(args,"n", &arr_size))
        return NULL;

    m = PyList_New(0);
    if(arr_size <= 1)
        return m;
    
    PyList_Append(m, Py_BuildValue("k",2));
    kok = sqrt((double)arr_size);

    arr_size = ((arr_size + 1) / 2) - 1;
    
    
    
    
    unsigned long *numbs = malloc(arr_size * sizeof(unsigned long));
    
    
    for(i=0; i < arr_size;i++){
        numbs[i] = 2 * (i + 1) + 1;
    }

    for(i=0;i< arr_size;i++) {
        if (numbs[i] > kok) break;
        if (numbs[i]) {
            
            for (j = i + numbs[i];j<arr_size;j += numbs[i]) {
                
                
                numbs[j] = 0;
            }
        }
    }

    for(i=0;i<arr_size;i++){
        if (numbs[i])
            if(PyList_Append(m,Py_BuildValue("k",numbs[i])) == -1) {
            Py_DECREF(m);
            free(numbs);
            return NULL;
            }
    } 
    free(numbs);
    return m;

}

static PyMethodDef MathMethods [] = {

    {"primes",math_primes,METH_VARARGS, "Find primes up to point."},
    {"okek",math_okek,METH_VARARGS, "Find okeks of random nums of arguments"},
    {"obeb",math_obeb,METH_VARARGS, "Finds obebs of random number of arguments"},
    {NULL,NULL,0,NULL}
};

PyMODINIT_FUNC
initmathGerecleri(void)
{
    PyObject *m;

    m = Py_InitModule("mathGerecleri", MathMethods);
} 
