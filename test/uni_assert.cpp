#include <uniassert/uniassert.h>

#if !defined(NDEBUG)
#	ifdef UNI_DISABLE_ASSERTS
#		error "UNI_DISABLE_ASSERTS is defined in debug build"
#	endif
#	ifndef UNI_SYSTEM_ASSERT
#		error "UNI_SYSTEM_ASSERT is not defined in debug build"
#	endif
#else
#	ifndef UNI_DISABLE_ASSERTS
#		error "UNI_DISABLE_ASSERTS is not defined in release build"
#	endif
#	ifdef UNI_SYSTEM_ASSERT
#		error "UNI_SYSTEM_ASSERT is defined in release build"
#	endif
#endif

#ifndef UNI_ASSERT
#	error "UNI_ASSERT is not defined"
#endif