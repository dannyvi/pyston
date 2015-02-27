// This file is originally from CPython 2.7, with modifications for Pyston

/* Interfaces to parse and execute pieces of python code */

#ifndef Py_PYTHONRUN_H
#define Py_PYTHONRUN_H
#ifdef __cplusplus
extern "C" {
#endif

#define PyCF_MASK (CO_FUTURE_DIVISION | CO_FUTURE_ABSOLUTE_IMPORT | \
                   CO_FUTURE_WITH_STATEMENT | CO_FUTURE_PRINT_FUNCTION | \
                   CO_FUTURE_UNICODE_LITERALS)
#define PyCF_MASK_OBSOLETE (CO_NESTED)
#define PyCF_SOURCE_IS_UTF8  0x0100
#define PyCF_DONT_IMPLY_DEDENT 0x0200
#define PyCF_ONLY_AST 0x0400

typedef struct {
    int cf_flags;  /* bitmask of CO_xxx flags relevant to future */
} PyCompilerFlags;

PyAPI_FUNC(void) Py_SetProgramName(char *) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) Py_GetProgramName(void) PYSTON_NOEXCEPT;

PyAPI_FUNC(void) Py_SetPythonHome(char *) PYSTON_NOEXCEPT;
PyAPI_FUNC(char *) Py_GetPythonHome(void) PYSTON_NOEXCEPT;

PyAPI_FUNC(void) Py_Initialize(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) Py_InitializeEx(int) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) Py_Finalize(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) Py_IsInitialized(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(PyThreadState *) Py_NewInterpreter(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) Py_EndInterpreter(PyThreadState *) PYSTON_NOEXCEPT;

PyAPI_FUNC(int) PyRun_AnyFileFlags(FILE *, const char *, PyCompilerFlags *) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) PyRun_AnyFileExFlags(FILE *, const char *, int, PyCompilerFlags *) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) PyRun_SimpleStringFlags(const char *, PyCompilerFlags *) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) PyRun_SimpleFileExFlags(FILE *, const char *, int, PyCompilerFlags *) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) PyRun_InteractiveOneFlags(FILE *, const char *, PyCompilerFlags *) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) PyRun_InteractiveLoopFlags(FILE *, const char *, PyCompilerFlags *) PYSTON_NOEXCEPT;

PyAPI_FUNC(struct _mod *) PyParser_ASTFromString(const char *, const char *,
                                                 int, PyCompilerFlags *flags,
                                                 PyArena *) PYSTON_NOEXCEPT;
PyAPI_FUNC(struct _mod *) PyParser_ASTFromFile(FILE *, const char *, int,
                                               char *, char *,
                                               PyCompilerFlags *, int *,
                                               PyArena *) PYSTON_NOEXCEPT;
#define PyParser_SimpleParseString(S, B) \
    PyParser_SimpleParseStringFlags(S, B, 0)
#define PyParser_SimpleParseFile(FP, S, B) \
    PyParser_SimpleParseFileFlags(FP, S, B, 0)
PyAPI_FUNC(struct _node *) PyParser_SimpleParseStringFlags(const char *, int,
                                                          int) PYSTON_NOEXCEPT;
PyAPI_FUNC(struct _node *) PyParser_SimpleParseFileFlags(FILE *, const char *,
                                                        int, int) PYSTON_NOEXCEPT;

PyAPI_FUNC(PyObject *) PyRun_StringFlags(const char *, int, PyObject *,
                                         PyObject *, PyCompilerFlags *) PYSTON_NOEXCEPT;

PyAPI_FUNC(PyObject *) PyRun_FileExFlags(FILE *, const char *, int,
                                         PyObject *, PyObject *, int,
                                         PyCompilerFlags *) PYSTON_NOEXCEPT;

#define Py_CompileString(str, p, s) Py_CompileStringFlags(str, p, s, NULL)
PyAPI_FUNC(PyObject *) Py_CompileStringFlags(const char *, const char *, int,
                                             PyCompilerFlags *) PYSTON_NOEXCEPT;
PyAPI_FUNC(struct symtable *) Py_SymtableString(const char *, const char *, int) PYSTON_NOEXCEPT;

PyAPI_FUNC(void) PyErr_Print(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyErr_PrintEx(int) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyErr_Display(PyObject *, PyObject *, PyObject *) PYSTON_NOEXCEPT;

PyAPI_FUNC(int) Py_AtExit(void (*func)(void)) PYSTON_NOEXCEPT;

PyAPI_FUNC(void) Py_Exit(int) PYSTON_NOEXCEPT;

PyAPI_FUNC(int) Py_FdIsInteractive(FILE *, const char *) PYSTON_NOEXCEPT;

/* Bootstrap */
PyAPI_FUNC(int) Py_Main(int argc, char **argv) PYSTON_NOEXCEPT;

/* Use macros for a bunch of old variants */
#define PyRun_String(str, s, g, l) PyRun_StringFlags(str, s, g, l, NULL)
#define PyRun_AnyFile(fp, name) PyRun_AnyFileExFlags(fp, name, 0, NULL)
#define PyRun_AnyFileEx(fp, name, closeit) \
    PyRun_AnyFileExFlags(fp, name, closeit, NULL)
#define PyRun_AnyFileFlags(fp, name, flags) \
    PyRun_AnyFileExFlags(fp, name, 0, flags)
#define PyRun_SimpleString(s) PyRun_SimpleStringFlags(s, NULL)
#define PyRun_SimpleFile(f, p) PyRun_SimpleFileExFlags(f, p, 0, NULL)
#define PyRun_SimpleFileEx(f, p, c) PyRun_SimpleFileExFlags(f, p, c, NULL)
#define PyRun_InteractiveOne(f, p) PyRun_InteractiveOneFlags(f, p, NULL)
#define PyRun_InteractiveLoop(f, p) PyRun_InteractiveLoopFlags(f, p, NULL)
#define PyRun_File(fp, p, s, g, l) \
    PyRun_FileExFlags(fp, p, s, g, l, 0, NULL)
#define PyRun_FileEx(fp, p, s, g, l, c) \
    PyRun_FileExFlags(fp, p, s, g, l, c, NULL)
#define PyRun_FileFlags(fp, p, s, g, l, flags) \
    PyRun_FileExFlags(fp, p, s, g, l, 0, flags)

/* In getpath.c */
PyAPI_FUNC(char *) Py_GetProgramFullPath(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(char *) Py_GetPrefix(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(char *) Py_GetExecPrefix(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(char *) Py_GetPath(void) PYSTON_NOEXCEPT;

/* In their own files */
PyAPI_FUNC(const char *) Py_GetVersion(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) Py_GetPlatform(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) Py_GetCopyright(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) Py_GetCompiler(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) Py_GetBuildInfo(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) _Py_svnversion(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) Py_SubversionRevision(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) Py_SubversionShortBranch(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) _Py_hgidentifier(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(const char *) _Py_hgversion(void) PYSTON_NOEXCEPT;

/* Internal -- various one-time initializations */
PyAPI_FUNC(PyObject *) _PyBuiltin_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(PyObject *) _PySys_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) _PyImport_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) _PyExc_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) _PyImportHooks_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) _PyFrame_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) _PyInt_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) _PyLong_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) _PyFloat_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(int) PyByteArray_Init(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) _PyRandom_Init(void) PYSTON_NOEXCEPT;

/* Various internal finalizers */
PyAPI_FUNC(void) _PyExc_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) _PyImport_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyMethod_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyFrame_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyCFunction_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyDict_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyTuple_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyList_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PySet_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyString_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyInt_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyFloat_Fini(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyOS_FiniInterrupts(void) PYSTON_NOEXCEPT;
PyAPI_FUNC(void) PyByteArray_Fini(void) PYSTON_NOEXCEPT;

/* Stuff with no proper home (yet) */
PyAPI_FUNC(char *) PyOS_Readline(FILE *, FILE *, char *) PYSTON_NOEXCEPT;
PyAPI_DATA(int) (*PyOS_InputHook)(void);
PyAPI_DATA(char) *(*PyOS_ReadlineFunctionPointer)(FILE *, FILE *, char *);
PyAPI_DATA(PyThreadState*) _PyOS_ReadlineTState;

/* Stack size, in "pointers" (so we get extra safety margins
   on 64-bit platforms).  On a 32-bit platform, this translates
   to a 8k margin. */
#define PYOS_STACK_MARGIN 2048

#if defined(WIN32) && !defined(MS_WIN64) && defined(_MSC_VER) && _MSC_VER >= 1300
/* Enable stack checking under Microsoft C */
#define USE_STACKCHECK
#endif

#ifdef USE_STACKCHECK
/* Check that we aren't overflowing our stack */
PyAPI_FUNC(int) PyOS_CheckStack(void) PYSTON_NOEXCEPT;
#endif

/* Signals */
typedef void (*PyOS_sighandler_t)(int);
PyAPI_FUNC(PyOS_sighandler_t) PyOS_getsig(int) PYSTON_NOEXCEPT;
PyAPI_FUNC(PyOS_sighandler_t) PyOS_setsig(int, PyOS_sighandler_t) PYSTON_NOEXCEPT;

/* Random */
PyAPI_FUNC(int) _PyOS_URandom (void *buffer, Py_ssize_t size) PYSTON_NOEXCEPT;

#ifdef __cplusplus
}
#endif
#endif /* !Py_PYTHONRUN_H */
