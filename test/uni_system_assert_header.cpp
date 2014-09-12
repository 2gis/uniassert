#define UNI_FORCE_ASSERTS
#define UNI_SYSTEM_ASSERT(cond) ((!(cond)) \
		? (uniassert::test::g_assertion_failed_handler(#cond, __FILE__, __FUNCTION__, __LINE__)) \
		: ((void)0))
#define UNI_SYSTEM_ASSERT_HEADER <uniassert/test/assertion_failed_handler.h>
#include <uniassert/uniassert.h>

#include <gtest/gtest.h>

namespace uniassert
{
namespace test
{

TEST(UniSystemAssertHandlerTest, ShouldCallSelectedFunction)
{
	bool function_called = false;
	g_assertion_failed_handler =
		[&function_called](char const *assertion, char const *file, char const *function, int line)
		{
			UNI_UNUSED(assertion);
			UNI_UNUSED(file);
			UNI_UNUSED(function);
			UNI_UNUSED(line);

			function_called = true;
		};

	UNI_ASSERT(false);
	EXPECT_TRUE(function_called);
}

} // namespace test
} // namespace uniassert
