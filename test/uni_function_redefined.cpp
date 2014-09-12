#define UNI_FUNCTION 100500
#include <uniassert/uniassert.h>

#if !defined(UNI_FUNCTION)
#	error "UNI_FUNCTION is not defined"
#elif UNI_FUNCTION != 100500
#	error "UNI_FUNCTION is redefined inside uniassert.h"
#endif
