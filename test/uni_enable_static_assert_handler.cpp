#include "undef.h"
#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_STATIC_ASSERT_HANDLER
#define UNI_SYSTEM_ASSERT_HEADER "system_assert_header.h"

#include <uniassert/uniassert.h>

#if !defined(UNI_STATIC_ASSERT_HANDLER_DEFINED)
#	error "UNI_STATIC_ASSERT_HANDLER_DEFINED is not defined"
#endif
#if defined(UNI_DYNAMIC_ASSERT_HANDLER_DEFINED)
#	error "UNI_DYNAMIC_ASSERT_HANDLER_DEFINED is defined"
#endif
#if defined(UNI_SYSTEM_ASSERT)
#	error "UNI_SYSTEM_ASSERT is defined"
#endif
#if defined(UNI_TEST_SPECIAL_MACRO)
#	error "UNI_SYSTEM_ASSERT_HEADER was used"
#endif

#if !defined(UNI_ASSERT)
#	error "UNI_ASSERT is not defined"
#endif
