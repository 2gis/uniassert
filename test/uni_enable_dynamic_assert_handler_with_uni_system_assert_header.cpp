#include "undef.h"
#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_DYNAMIC_ASSERT_HANDLER
#define UNI_SYSTEM_ASSERT_HEADER "test/system_assert_header.h"

#include <uniassert/uniassert.h>

#if !defined(UNI_ASSERT)
#	error "UNI_ASSERT is not defined"
#endif
#if !defined(UNI_TEST_SPECIAL_MACRO)
#	error "UNI_SYSTEM_ASSERT_HEADER was not used"
#endif
#if !defined(UNI_SYSTEM_ASSERT)
#	error "UNI_SYSTEM_ASSERT is not defined"
#elif UNI_SYSTEM_ASSERT != 1
#	error "UNI_SYSTEM_ASSERT was redefined inside uniassert.h"
#endif
