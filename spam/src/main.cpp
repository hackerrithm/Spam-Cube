#include "include.h"

PyObject* some_function(PyObject* self, PyObject* args)
{
	int i;
	if (!PyArg_ParseTuple(args, "i", &i))
	{
		goto error;
	}
	return PyInt_FromLong(i * i * i);
error:
	return 0;
}

static PyObject *SpamError;

PyMethodDef SpamMethods[] =
{
	{"cube", (PyCFunction)some_function, METH_VARARGS, 0},
	{0,0,0,0}
};

PyMODINIT_FUNC

initspam(void)
{
	PyObject *m;

	m = Py_InitModule("spam", SpamMethods);
	if (m == NULL)
		return;

	SpamError = PyErr_NewException("spam.error", NULL, NULL);
	Py_INCREF(SpamError);
	PyModule_AddObject(m, "error", SpamError);
}