#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_ASSERT_HANDLER
#include <uniassert/uniassert.h>

#if !defined(UNI_ASSERTION_HANDLER_DEFINED)
#	error "UNI_ASSERTION_HANDLER_DEFINED is not defined"
#endif
#if !defined(UNI_ASSERT)
#	error "UNI_ASSERT is not defined"
#endif