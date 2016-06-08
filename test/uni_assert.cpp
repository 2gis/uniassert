#include "undef.h"

#include <uniassert/uniassert.h>

#if !defined(NDEBUG)
#	if defined(UNI_DISABLE_ASSERTS)
#		error "UNI_DISABLE_ASSERTS is defined"
#	endif
#	if !defined(UNI_ASSERTS_ENABLED)
#		error "UNI_ASSERTS_ENABLED is not defined"
#	endif
#	if !defined(UNI_SYSTEM_ASSERT)
#		error "UNI_SYSTEM_ASSERT is not defined"
#	endif
#else
#	if !defined(UNI_DISABLE_ASSERTS)
#		error "UNI_DISABLE_ASSERTS is not defined"
#	endif
#	if defined(UNI_ASSERTS_ENABLED)
#		error "UNI_ASSERTS_ENABLED is defined"
#	endif
#	if defined(UNI_SYSTEM_ASSERT)
#		error "UNI_SYSTEM_ASSERT is defined"
#	endif
#endif

#if defined(UNI_DYNAMIC_ASSERT_HANDLER_DEFINED)
#	error "UNI_DYNAMIC_ASSERT_HANDLER_DEFINED is defined"
#endif
#if defined(UNI_STATIC_ASSERT_HANDLER_DEFINED)
#	error "UNI_STATIC_ASSERT_HANDLER_DEFINED is defined"
#endif
#if !defined(UNI_ASSERT)
#	error "UNI_ASSERT is not defined"
#endif
