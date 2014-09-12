#include <functional>
#include <gtest/gtest.h>

#define UNI_DISABLE_ASSERTS
#include <uniassert/uniassert.h>

namespace uniassert
{
namespace test
{

TEST(UniVerifyDisabledAssertsTest, ShouldNotFailIfConditionIsTrue)
{
	UNI_VERIFY(true);
}

TEST(UniVerifyDisabledAssertsTest, ShouldNotFailIfConditionIsFalse)
{
	UNI_VERIFY(false);
}

TEST(UniVerifyDisabledAssertsTest, ShouldEvaluateCode)
{
	bool called = false;
	auto func =
		[&called]
		{
			called = true;
			return true;
		};

	UNI_VERIFY(func());

	EXPECT_TRUE(called);
}

TEST(UniVerifyDisabledAssertsTest, ShouldEvaluateCodeOnlyOnce)
{
	unsigned called_times = 0;
	auto func =
		[&called_times]
		{
			++called_times;
			return true;
		};

	UNI_VERIFY(func());

	EXPECT_EQ(1u, called_times);
}

} // namespace test
} // namespace uniassert
