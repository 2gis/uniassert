#include "undef.h"
#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_DYNAMIC_ASSERT_HANDLER
#define UNI_ENABLE_STATIC_ASSERT_HANDLER

#include <uniassert/uniassert.h>

#if !defined(UNI_ASSERTS_ENABLED)
#	error "UNI_ASSERTS_ENABLED is not defined"
#endif
#if !defined(UNI_SYSTEM_ASSERT)
#	error "UNI_SYSTEM_ASSERT is not defined"
#endif
#if !defined(UNI_DYNAMIC_ASSERT_HANDLER_DEFINED)
#	error "UNI_DYNAMIC_ASSERT_HANDLER_DEFINED is not defined"
#endif
#if defined(UNI_STATIC_ASSERT_HANDLER_DEFINED)
#	error "UNI_STATIC_ASSERT_HANDLER_DEFINED is defined"
#endif

#if !defined(UNI_ASSERT)
#	error "UNI_ASSERT is not defined"
#endif
