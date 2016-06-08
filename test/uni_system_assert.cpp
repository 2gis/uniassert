#include "undef.h"
#define UNI_FORCE_ASSERTS
#define UNI_SYSTEM_ASSERT 1

#include <uniassert/uniassert.h>

#if !defined(UNI_ASSERT)
#	error "UNI_ASSERT is not defined"
#elif UNI_ASSERT != 1
#	error "UNI_SYSTEM_ASSERT was not used"
#endif
