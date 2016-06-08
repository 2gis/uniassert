#include <gtest/gtest.h>

#include "undef.h"
#define UNI_ENABLE_DYNAMIC_ASSERT_HANDLER

#include <uniassert/uniassert.h>

#if !defined(NDEBUG)
#	if !defined(UNI_SYSTEM_ASSERT)
#		error "UNI_SYSTEM_ASSERT is not defined"
#	endif
#	if !defined(UNI_DYNAMIC_ASSERT_HANDLER_DEFINED)
#		error "UNI_DYNAMIC_ASSERT_HANDLER_DEFINED is not defined"
#	endif
#else
#	if defined(UNI_SYSTEM_ASSERT)
#		error "UNI_SYSTEM_ASSERT is defined"
#	endif
#	if defined(UNI_DYNAMIC_ASSERT_HANDLER_DEFINED)
#		error "UNI_DYNAMIC_ASSERT_HANDLER_DEFINED is defined"
#	endif
#endif

#if defined(UNI_STATIC_ASSERT_HANDLER_DEFINED)
#	error "UNI_STATIC_ASSERT_HANDLER_DEFINED is defined"
#endif
#if !defined(UNI_ASSERT)
#	error "UNI_ASSERT is not defined"
#endif

namespace uniassert
{
namespace test
{

TEST(UniEnableDynamicAssertHandlerTest, AssertHandlerGuardShouldBeVisible)
{
	const assert_handler handler = nullptr;
	assert_handler_guard guard(handler);
}

TEST(UniEnableDynamicAssertHandlerTest, DisableAssertsGuardShouldBeVisible)
{
	disable_asserts_guard guard;
}

} // namespace test
} // namespace uniassert
