#include <functional>
#include <gtest/gtest.h>

#define UNI_DISABLE_ASSERTS
#include <uniassert/uniassert.h>

namespace uniassert
{
namespace test
{

TEST(UniAssertDisabledAssertsTest, ShouldNotFailIfConditionIsTrue)
{
	UNI_ASSERT(true);
}

TEST(UniAssertDisabledAssertsTest, ShouldNotFailIfConditionIsFalse)
{
	UNI_ASSERT(false);
}

TEST(UniAssertDisabledAssertsTest, ShouldNotEvaluateCode)
{
	bool called = false;
	auto func =
		[&called]
		{
			called = true;
			return true;
		};

	UNI_ASSERT(func());

	EXPECT_FALSE(called);
}


} // namespace test
} // namespace uniassert
