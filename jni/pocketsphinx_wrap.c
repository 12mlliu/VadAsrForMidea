/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 3.0.8
 *
 * This file is not intended to be easily readable and contains a number of
 * coding conventions designed to improve portability and efficiency. Do not make
 * changes to this file unless you know what you are doing--modify the SWIG
 * interface file instead.
 * ----------------------------------------------------------------------------- */


#ifndef SWIGJAVA
#define SWIGJAVA
#endif


/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#  ifndef GCC_HASCLASSVISIBILITY
#    define GCC_HASCLASSVISIBILITY
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif

/* Deal with Apple's deprecated 'AssertMacros.h' from Carbon-framework */
#if defined(__APPLE__) && !defined(__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES)
# define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#endif

/* Intel's compiler complains if a variable which was never initialised is
 * cast to void, which is a common idiom which we use to indicate that we
 * are aware a variable isn't used.  So we just silence that warning.
 * See: https://github.com/swig/swig/issues/192 for more discussion.
 */
#ifdef __INTEL_COMPILER
# pragma warning disable 592
#endif


/* Fix for jlong on some versions of gcc on Windows */
#if defined(__GNUC__) && !defined(__INTEL_COMPILER)
  typedef long long __int64;
#endif

/* Fix for jlong on 64-bit x86 Solaris */
#if defined(__x86_64)
# ifdef _LP64
#   undef _LP64
# endif
#endif

#include <jni.h>
#include <stdlib.h>
#include <string.h>


/* Support for throwing Java exceptions */
typedef enum {
  SWIG_JavaOutOfMemoryError = 1, 
  SWIG_JavaIOException, 
  SWIG_JavaRuntimeException, 
  SWIG_JavaIndexOutOfBoundsException,
  SWIG_JavaArithmeticException,
  SWIG_JavaIllegalArgumentException,
  SWIG_JavaNullPointerException,
  SWIG_JavaDirectorPureVirtual,
  SWIG_JavaUnknownError
} SWIG_JavaExceptionCodes;

typedef struct {
  SWIG_JavaExceptionCodes code;
  const char *java_exception;
} SWIG_JavaExceptions_t;


static void SWIGUNUSED SWIG_JavaThrowException(JNIEnv *jenv, SWIG_JavaExceptionCodes code, const char *msg) {
  jclass excep;
  static const SWIG_JavaExceptions_t java_exceptions[] = {
    { SWIG_JavaOutOfMemoryError, "java/lang/OutOfMemoryError" },
    { SWIG_JavaIOException, "java/io/IOException" },
    { SWIG_JavaRuntimeException, "java/lang/RuntimeException" },
    { SWIG_JavaIndexOutOfBoundsException, "java/lang/IndexOutOfBoundsException" },
    { SWIG_JavaArithmeticException, "java/lang/ArithmeticException" },
    { SWIG_JavaIllegalArgumentException, "java/lang/IllegalArgumentException" },
    { SWIG_JavaNullPointerException, "java/lang/NullPointerException" },
    { SWIG_JavaDirectorPureVirtual, "java/lang/RuntimeException" },
    { SWIG_JavaUnknownError,  "java/lang/UnknownError" },
    { (SWIG_JavaExceptionCodes)0,  "java/lang/UnknownError" }
  };
  const SWIG_JavaExceptions_t *except_ptr = java_exceptions;

  while (except_ptr->code != code && except_ptr->code)
    except_ptr++;

  (*jenv)->ExceptionClear(jenv);
  excep = (*jenv)->FindClass(jenv, except_ptr->java_exception);
  if (excep)
    (*jenv)->ThrowNew(jenv, excep, msg);
}


/* Contract support */

#define SWIG_contract_assert(nullreturn, expr, msg) if (!(expr)) {SWIG_JavaThrowException(jenv, SWIG_JavaIllegalArgumentException, msg); return nullreturn; } else

/*  Errors in SWIG */
#define  SWIG_UnknownError    	   -1
#define  SWIG_IOError        	   -2
#define  SWIG_RuntimeError   	   -3
#define  SWIG_IndexError     	   -4
#define  SWIG_TypeError      	   -5
#define  SWIG_DivisionByZero 	   -6
#define  SWIG_OverflowError  	   -7
#define  SWIG_SyntaxError    	   -8
#define  SWIG_ValueError     	   -9
#define  SWIG_SystemError    	   -10
#define  SWIG_AttributeError 	   -11
#define  SWIG_MemoryError    	   -12
#define  SWIG_NullReferenceError   -13




SWIGINTERN void SWIG_JavaException(JNIEnv *jenv, int code, const char *msg) {
  SWIG_JavaExceptionCodes exception_code = SWIG_JavaUnknownError;
  switch(code) {
  case SWIG_MemoryError:
    exception_code = SWIG_JavaOutOfMemoryError;
    break;
  case SWIG_IOError:
    exception_code = SWIG_JavaIOException;
    break;
  case SWIG_SystemError:
  case SWIG_RuntimeError:
    exception_code = SWIG_JavaRuntimeException;
    break;
  case SWIG_OverflowError:
  case SWIG_IndexError:
    exception_code = SWIG_JavaIndexOutOfBoundsException;
    break;
  case SWIG_DivisionByZero:
    exception_code = SWIG_JavaArithmeticException;
    break;
  case SWIG_SyntaxError:
  case SWIG_ValueError:
  case SWIG_TypeError:
    exception_code = SWIG_JavaIllegalArgumentException;
    break;
  case SWIG_UnknownError:
  default:
    exception_code = SWIG_JavaUnknownError;
    break;
  }
  SWIG_JavaThrowException(jenv, exception_code, msg);
}


#if defined(SWIG_NOINCLUDE) || defined(SWIG_NOARRAYS)


static int SWIG_JavaArrayInSchar (JNIEnv *jenv, jbyte **jarr, signed char **carr, jbyteArray input);
static void SWIG_JavaArrayArgoutSchar (JNIEnv *jenv, jbyte *jarr, signed char *carr, jbyteArray input);
static jbyteArray SWIG_JavaArrayOutSchar (JNIEnv *jenv, signed char *result, jsize sz);


static int SWIG_JavaArrayInUchar (JNIEnv *jenv, jshort **jarr, unsigned char **carr, jshortArray input);
static void SWIG_JavaArrayArgoutUchar (JNIEnv *jenv, jshort *jarr, unsigned char *carr, jshortArray input);
static jshortArray SWIG_JavaArrayOutUchar (JNIEnv *jenv, unsigned char *result, jsize sz);


static int SWIG_JavaArrayInShort (JNIEnv *jenv, jshort **jarr, short **carr, jshortArray input);
static void SWIG_JavaArrayArgoutShort (JNIEnv *jenv, jshort *jarr, short *carr, jshortArray input);
static jshortArray SWIG_JavaArrayOutShort (JNIEnv *jenv, short *result, jsize sz);


static int SWIG_JavaArrayInUshort (JNIEnv *jenv, jint **jarr, unsigned short **carr, jintArray input);
static void SWIG_JavaArrayArgoutUshort (JNIEnv *jenv, jint *jarr, unsigned short *carr, jintArray input);
static jintArray SWIG_JavaArrayOutUshort (JNIEnv *jenv, unsigned short *result, jsize sz);


static int SWIG_JavaArrayInInt (JNIEnv *jenv, jint **jarr, int **carr, jintArray input);
static void SWIG_JavaArrayArgoutInt (JNIEnv *jenv, jint *jarr, int *carr, jintArray input);
static jintArray SWIG_JavaArrayOutInt (JNIEnv *jenv, int *result, jsize sz);


static int SWIG_JavaArrayInUint (JNIEnv *jenv, jlong **jarr, unsigned int **carr, jlongArray input);
static void SWIG_JavaArrayArgoutUint (JNIEnv *jenv, jlong *jarr, unsigned int *carr, jlongArray input);
static jlongArray SWIG_JavaArrayOutUint (JNIEnv *jenv, unsigned int *result, jsize sz);


static int SWIG_JavaArrayInLong (JNIEnv *jenv, jint **jarr, long **carr, jintArray input);
static void SWIG_JavaArrayArgoutLong (JNIEnv *jenv, jint *jarr, long *carr, jintArray input);
static jintArray SWIG_JavaArrayOutLong (JNIEnv *jenv, long *result, jsize sz);


static int SWIG_JavaArrayInUlong (JNIEnv *jenv, jlong **jarr, unsigned long **carr, jlongArray input);
static void SWIG_JavaArrayArgoutUlong (JNIEnv *jenv, jlong *jarr, unsigned long *carr, jlongArray input);
static jlongArray SWIG_JavaArrayOutUlong (JNIEnv *jenv, unsigned long *result, jsize sz);


static int SWIG_JavaArrayInLonglong (JNIEnv *jenv, jlong **jarr, jlong **carr, jlongArray input);
static void SWIG_JavaArrayArgoutLonglong (JNIEnv *jenv, jlong *jarr, jlong *carr, jlongArray input);
static jlongArray SWIG_JavaArrayOutLonglong (JNIEnv *jenv, jlong *result, jsize sz);


static int SWIG_JavaArrayInFloat (JNIEnv *jenv, jfloat **jarr, float **carr, jfloatArray input);
static void SWIG_JavaArrayArgoutFloat (JNIEnv *jenv, jfloat *jarr, float *carr, jfloatArray input);
static jfloatArray SWIG_JavaArrayOutFloat (JNIEnv *jenv, float *result, jsize sz);


static int SWIG_JavaArrayInDouble (JNIEnv *jenv, jdouble **jarr, double **carr, jdoubleArray input);
static void SWIG_JavaArrayArgoutDouble (JNIEnv *jenv, jdouble *jarr, double *carr, jdoubleArray input);
static jdoubleArray SWIG_JavaArrayOutDouble (JNIEnv *jenv, double *result, jsize sz);


#else


/* signed char[] support */
static int SWIG_JavaArrayInSchar (JNIEnv *jenv, jbyte **jarr, signed char **carr, jbyteArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetByteArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (signed char*) malloc(sz * sizeof(signed char)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (signed char)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutSchar (JNIEnv *jenv, jbyte *jarr, signed char *carr, jbyteArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jbyte)carr[i];
  (*jenv)->ReleaseByteArrayElements(jenv, input, jarr, 0);
}

static jbyteArray SWIG_JavaArrayOutSchar (JNIEnv *jenv, signed char *result, jsize sz) {
  jbyte *arr;
  int i;
  jbyteArray jresult = (*jenv)->NewByteArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetByteArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jbyte)result[i];
  (*jenv)->ReleaseByteArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* unsigned char[] support */
static int SWIG_JavaArrayInUchar (JNIEnv *jenv, jshort **jarr, unsigned char **carr, jshortArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetShortArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (unsigned char*) malloc(sz * sizeof(unsigned char)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (unsigned char)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutUchar (JNIEnv *jenv, jshort *jarr, unsigned char *carr, jshortArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jshort)carr[i];
  (*jenv)->ReleaseShortArrayElements(jenv, input, jarr, 0);
}

static jshortArray SWIG_JavaArrayOutUchar (JNIEnv *jenv, unsigned char *result, jsize sz) {
  jshort *arr;
  int i;
  jshortArray jresult = (*jenv)->NewShortArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetShortArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jshort)result[i];
  (*jenv)->ReleaseShortArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* short[] support */
static int SWIG_JavaArrayInShort (JNIEnv *jenv, jshort **jarr, short **carr, jshortArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetShortArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (short*) malloc(sz * sizeof(short)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (short)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutShort (JNIEnv *jenv, jshort *jarr, short *carr, jshortArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jshort)carr[i];
  (*jenv)->ReleaseShortArrayElements(jenv, input, jarr, 0);
}

static jshortArray SWIG_JavaArrayOutShort (JNIEnv *jenv, short *result, jsize sz) {
  jshort *arr;
  int i;
  jshortArray jresult = (*jenv)->NewShortArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetShortArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jshort)result[i];
  (*jenv)->ReleaseShortArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* unsigned short[] support */
static int SWIG_JavaArrayInUshort (JNIEnv *jenv, jint **jarr, unsigned short **carr, jintArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetIntArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (unsigned short*) malloc(sz * sizeof(unsigned short)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (unsigned short)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutUshort (JNIEnv *jenv, jint *jarr, unsigned short *carr, jintArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jint)carr[i];
  (*jenv)->ReleaseIntArrayElements(jenv, input, jarr, 0);
}

static jintArray SWIG_JavaArrayOutUshort (JNIEnv *jenv, unsigned short *result, jsize sz) {
  jint *arr;
  int i;
  jintArray jresult = (*jenv)->NewIntArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetIntArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jint)result[i];
  (*jenv)->ReleaseIntArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* int[] support */
static int SWIG_JavaArrayInInt (JNIEnv *jenv, jint **jarr, int **carr, jintArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetIntArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (int*) malloc(sz * sizeof(int)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (int)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutInt (JNIEnv *jenv, jint *jarr, int *carr, jintArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jint)carr[i];
  (*jenv)->ReleaseIntArrayElements(jenv, input, jarr, 0);
}

static jintArray SWIG_JavaArrayOutInt (JNIEnv *jenv, int *result, jsize sz) {
  jint *arr;
  int i;
  jintArray jresult = (*jenv)->NewIntArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetIntArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jint)result[i];
  (*jenv)->ReleaseIntArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* unsigned int[] support */
static int SWIG_JavaArrayInUint (JNIEnv *jenv, jlong **jarr, unsigned int **carr, jlongArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetLongArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (unsigned int*) malloc(sz * sizeof(unsigned int)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (unsigned int)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutUint (JNIEnv *jenv, jlong *jarr, unsigned int *carr, jlongArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jlong)carr[i];
  (*jenv)->ReleaseLongArrayElements(jenv, input, jarr, 0);
}

static jlongArray SWIG_JavaArrayOutUint (JNIEnv *jenv, unsigned int *result, jsize sz) {
  jlong *arr;
  int i;
  jlongArray jresult = (*jenv)->NewLongArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetLongArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jlong)result[i];
  (*jenv)->ReleaseLongArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* long[] support */
static int SWIG_JavaArrayInLong (JNIEnv *jenv, jint **jarr, long **carr, jintArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetIntArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (long*) malloc(sz * sizeof(long)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (long)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutLong (JNIEnv *jenv, jint *jarr, long *carr, jintArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jint)carr[i];
  (*jenv)->ReleaseIntArrayElements(jenv, input, jarr, 0);
}

static jintArray SWIG_JavaArrayOutLong (JNIEnv *jenv, long *result, jsize sz) {
  jint *arr;
  int i;
  jintArray jresult = (*jenv)->NewIntArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetIntArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jint)result[i];
  (*jenv)->ReleaseIntArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* unsigned long[] support */
static int SWIG_JavaArrayInUlong (JNIEnv *jenv, jlong **jarr, unsigned long **carr, jlongArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetLongArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (unsigned long*) malloc(sz * sizeof(unsigned long)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (unsigned long)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutUlong (JNIEnv *jenv, jlong *jarr, unsigned long *carr, jlongArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jlong)carr[i];
  (*jenv)->ReleaseLongArrayElements(jenv, input, jarr, 0);
}

static jlongArray SWIG_JavaArrayOutUlong (JNIEnv *jenv, unsigned long *result, jsize sz) {
  jlong *arr;
  int i;
  jlongArray jresult = (*jenv)->NewLongArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetLongArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jlong)result[i];
  (*jenv)->ReleaseLongArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* jlong[] support */
static int SWIG_JavaArrayInLonglong (JNIEnv *jenv, jlong **jarr, jlong **carr, jlongArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetLongArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (jlong*) malloc(sz * sizeof(jlong)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (jlong)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutLonglong (JNIEnv *jenv, jlong *jarr, jlong *carr, jlongArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jlong)carr[i];
  (*jenv)->ReleaseLongArrayElements(jenv, input, jarr, 0);
}

static jlongArray SWIG_JavaArrayOutLonglong (JNIEnv *jenv, jlong *result, jsize sz) {
  jlong *arr;
  int i;
  jlongArray jresult = (*jenv)->NewLongArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetLongArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jlong)result[i];
  (*jenv)->ReleaseLongArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* float[] support */
static int SWIG_JavaArrayInFloat (JNIEnv *jenv, jfloat **jarr, float **carr, jfloatArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetFloatArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (float*) malloc(sz * sizeof(float)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (float)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutFloat (JNIEnv *jenv, jfloat *jarr, float *carr, jfloatArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jfloat)carr[i];
  (*jenv)->ReleaseFloatArrayElements(jenv, input, jarr, 0);
}

static jfloatArray SWIG_JavaArrayOutFloat (JNIEnv *jenv, float *result, jsize sz) {
  jfloat *arr;
  int i;
  jfloatArray jresult = (*jenv)->NewFloatArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetFloatArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jfloat)result[i];
  (*jenv)->ReleaseFloatArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


/* double[] support */
static int SWIG_JavaArrayInDouble (JNIEnv *jenv, jdouble **jarr, double **carr, jdoubleArray input) {
  int i;
  jsize sz;
  if (!input) {
    SWIG_JavaThrowException(jenv, SWIG_JavaNullPointerException, "null array");
    return 0;
  }
  sz = (*jenv)->GetArrayLength(jenv, input);
  *jarr = (*jenv)->GetDoubleArrayElements(jenv, input, 0);
  if (!*jarr)
    return 0; 
  *carr = (double*) malloc(sz * sizeof(double)); 
  if (!*carr) {
    SWIG_JavaThrowException(jenv, SWIG_JavaOutOfMemoryError, "array memory allocation failed");
    return 0;
  }
  for (i=0; i<sz; i++)
    (*carr)[i] = (double)(*jarr)[i];
  return 1;
}

static void SWIG_JavaArrayArgoutDouble (JNIEnv *jenv, jdouble *jarr, double *carr, jdoubleArray input) {
  int i;
  jsize sz = (*jenv)->GetArrayLength(jenv, input);
  for (i=0; i<sz; i++)
    jarr[i] = (jdouble)carr[i];
  (*jenv)->ReleaseDoubleArrayElements(jenv, input, jarr, 0);
}

static jdoubleArray SWIG_JavaArrayOutDouble (JNIEnv *jenv, double *result, jsize sz) {
  jdouble *arr;
  int i;
  jdoubleArray jresult = (*jenv)->NewDoubleArray(jenv, sz);
  if (!jresult)
    return NULL;
  arr = (*jenv)->GetDoubleArrayElements(jenv, jresult, 0);
  if (!arr)
    return NULL;
  for (i=0; i<sz; i++)
    arr[i] = (jdouble)result[i];
  (*jenv)->ReleaseDoubleArrayElements(jenv, jresult, arr, 0);
  return jresult;
}


#endif


#ifndef __cplusplus
typedef int bool;
#define true 1
#define false 0
#endif


#include "logMMSE.h"
typedef LOGMMSE_VAR  LogmmseVar;

typedef cmd_ln_t Config;



SWIGINTERN LogmmseVar *new_LogmmseVar(void){
        LogmmseVar *logmmse;
        logmmse = (LogmmseVar *)malloc(sizeof(LogmmseVar));
        return logmmse;
    }
SWIGINTERN void delete_LogmmseVar(LogmmseVar *self){
        free(self);
    }
SWIGINTERN void LogmmseVar_logmmseinit(LogmmseVar *self){
        logMMSE_Init(self);        
    }
SWIGINTERN char const *LogmmseVar_logmmsedenosebufall(LogmmseVar *self,X_INT16 *sigBuf,int32 BufSize,Config *config,int32 threshold,char const *orderfilename){
        char const *hypstr;
        hypstr = logMMSE_denosie_bufall(sigBuf,BufSize,self,config,threshold,orderfilename);   
        return hypstr;
    }
SWIGINTERN int LogmmseVar_noiseestimatebufall(LogmmseVar *self,X_INT16 *sigBuf,int32 BufSize){
        return noise_estimate_bufall(sigBuf, BufSize,self);
    }

#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORT jlong JNICALL Java_com_midea_VadAsr_PocketSphinxJNI_new_1LogmmseVar(JNIEnv *jenv, jclass jcls) {
  jlong jresult = 0 ;
  LogmmseVar *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  result = (LogmmseVar *)new_LogmmseVar();
  *(LogmmseVar **)&jresult = result; 
  return jresult;
}


SWIGEXPORT void JNICALL Java_com_midea_VadAsr_PocketSphinxJNI_delete_1LogmmseVar(JNIEnv *jenv, jclass jcls, jlong jarg1) {
  LogmmseVar *arg1 = (LogmmseVar *) 0 ;
  
  (void)jenv;
  (void)jcls;
  arg1 = *(LogmmseVar **)&jarg1; 
  delete_LogmmseVar(arg1);
}


SWIGEXPORT void JNICALL Java_com_midea_VadAsr_PocketSphinxJNI_LogmmseVar_1logmmseinit(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_) {
  LogmmseVar *arg1 = (LogmmseVar *) 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(LogmmseVar **)&jarg1; 
  LogmmseVar_logmmseinit(arg1);
}


SWIGEXPORT jstring JNICALL Java_com_midea_VadAsr_PocketSphinxJNI_LogmmseVar_1logmmsedenosebufall(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jshortArray jarg2, jint jarg3, jlong jarg4, jobject jarg4_, jint jarg5, jstring jarg6) {
  jstring jresult = 0 ;
  LogmmseVar *arg1 = (LogmmseVar *) 0 ;
  X_INT16 *arg2 = (X_INT16 *) 0 ;
  int32 arg3 ;
  Config *arg4 = (Config *) 0 ;
  int32 arg5 ;
  char *arg6 = (char *) 0 ;
  jshort *jarr2 ;
  char *result = 0 ;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  (void)jarg4_;
  arg1 = *(LogmmseVar **)&jarg1; 
  if (!SWIG_JavaArrayInShort(jenv, &jarr2, (short **)&arg2, jarg2)) return 0; 
  arg3 = (int32)jarg3; 
  arg4 = *(Config **)&jarg4; 
  arg5 = (int32)jarg5; 
  arg6 = 0;
  if (jarg6) {
    arg6 = (char *)(*jenv)->GetStringUTFChars(jenv, jarg6, 0);
    if (!arg6) return 0;
  }
  result = (char *)LogmmseVar_logmmsedenosebufall(arg1,arg2,arg3,arg4,arg5,(char const *)arg6);
  if (result) jresult = (*jenv)->NewStringUTF(jenv, (const char *)result);
  SWIG_JavaArrayArgoutShort(jenv, jarr2, (short *)arg2, jarg2); 
  free(arg2); 
  if (arg6) (*jenv)->ReleaseStringUTFChars(jenv, jarg6, (const char *)arg6);
  return jresult;
}


SWIGEXPORT jint JNICALL Java_com_midea_VadAsr_PocketSphinxJNI_LogmmseVar_1noiseestimatebufall(JNIEnv *jenv, jclass jcls, jlong jarg1, jobject jarg1_, jshortArray jarg2, jint jarg3) {
  jint jresult = 0 ;
  LogmmseVar *arg1 = (LogmmseVar *) 0 ;
  X_INT16 *arg2 = (X_INT16 *) 0 ;
  int32 arg3 ;
  jshort *jarr2 ;
  int result;
  
  (void)jenv;
  (void)jcls;
  (void)jarg1_;
  arg1 = *(LogmmseVar **)&jarg1; 
  if (!SWIG_JavaArrayInShort(jenv, &jarr2, (short **)&arg2, jarg2)) return 0; 
  arg3 = (int32)jarg3; 
  result = (int)LogmmseVar_noiseestimatebufall(arg1,arg2,arg3);
  jresult = (jint)result; 
  SWIG_JavaArrayArgoutShort(jenv, jarr2, (short *)arg2, jarg2); 
  free(arg2); 
  return jresult;
}


#ifdef __cplusplus
}
#endif

