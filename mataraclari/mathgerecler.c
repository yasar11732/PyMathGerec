#include <Python.h>
#include <math.h>

struct bigcouples {
unsigned long first;
unsigned long second;
};


void
swap(struct bigcouples *couple){
    unsigned long backup;
    backup = couple->first;
    couple->first = couple->second;
    couple->second = backup;
}

void
bubbleSort(unsigned long *numbers, Py_ssize_t array_size)
{
  Py_ssize_t i, j;
  unsigned long temp;
 
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


unsigned long
obeb_couples(struct bigcouples couple) {
/* Finds bigges common divedor of to numbers*/
    if(couple.first == 0) {
        if (couple.second)
            return couple.second;
        else
            return 1;
    }
    if(couple.second == 0)
        return couple.first;

    while(1) {
        if (couple.second > couple.first)
            swap(&couple);
        couple.first = couple.first % couple.second;
        if(!couple.first) {
            return couple.second; }
    }

}

unsigned long
okek_couples(struct bigcouples couple) {
    /* Common divident of two numbers*/
    unsigned long up_part = couple.first/obeb_couples(couple);
    unsigned long result = up_part * couple.second;
    /* Check for overflow */
    if (result < up_part || result < couple.second) {
        PyErr_SetString(PyExc_OverflowError,"Values too large to calculate");
        return NULL;
    }
    return  result;
}

int
ParseArguments(unsigned long arr[],Py_ssize_t size, PyObject *args) {
    /* Get arbitrary number of positive numbers from Py_Tuple */
    Py_ssize_t i;
    PyObject *temp_p, *temp_p2;


    for (i=0;i<size;i++) {
        temp_p = PyTuple_GetItem(args,i);
        if(temp_p == NULL) {return NULL;}

        /* Check if temp_p is numeric */
        if (PyNumber_Check(temp_p) != 1) {
            PyErr_SetString(PyExc_TypeError,"Non-numeric argument.");
            return NULL;
        }

        /* Convert number to python long and than C unsigned long */
        temp_p2 = PyNumber_Long(temp_p);
        arr[i] = PyLong_AsUnsignedLong(temp_p2);
        Py_DECREF(temp_p2);
        if (arr[i] == 0) {
            PyErr_SetString(PyExc_ValueError,"Zero doesn't allowed as argument.");
            return NULL;
        }
        if (PyErr_Occurred()) {return NULL; }
    }

    return 1;
}


static PyObject *
math_okek(PyObject *self, PyObject *args)
{
    Py_ssize_t TupleSize = PyTuple_Size(args);
    Py_ssize_t i;
    struct bigcouples *temp = malloc(sizeof(struct bigcouples));
    unsigned long current;
    
    if(!TupleSize) {
        if(!PyErr_Occurred()) 
            PyErr_SetString(PyExc_TypeError,"You must supply at least one argument.");
        free(temp);
        return NULL;
    }

    unsigned long *nums = malloc(TupleSize * sizeof(unsigned long));

    if(!ParseArguments(nums, TupleSize, args)){
        free(temp);
        free(nums);
        return NULL;
    }

    bubbleSort(nums, TupleSize);

    current = nums[0];

    for (i = 1; i< TupleSize; i++) {
        temp->first = current;
        temp->second = nums[i];
        current = okek_couples(*temp);
        if(!current) {return NULL;}
    }

    free(temp);
    free(nums);
    return Py_BuildValue("k",current);
}


static PyObject *
math_obeb(PyObject *self, PyObject *args) {
    PyObject *temp_p;
    struct bigcouples temp;
    unsigned long current;
    Py_ssize_t i;
    Py_ssize_t TupleSize = PyTuple_Size(args);
    if (!TupleSize) {
        PyErr_SetString(PyExc_TypeError,"You must supply at least one int or long object.");
        return NULL;
    }
    unsigned long *nums = malloc(TupleSize * sizeof(unsigned long));
    
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
    return Py_BuildValue("k",current); 
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
            if(PyList_Append(m,Py_BuildValue("i",numbs[i])) == -1) {
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
init_mathGerecleri(void)
{
    PyObject *m;

    m = Py_InitModule("_mathGerecleri", MathMethods);
} 
