#include <functional>
#include <gtest/gtest.h>

#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_ASSERT_HANDLER
#include <uniassert/uniassert.h>

#include "assertion_failed_handler.h"

namespace uniassert
{
namespace test
{

class UniVerifyEnabledAssertsTest : public ::testing::Test
{
protected:
	UniVerifyEnabledAssertsTest()
	{
		using namespace std::placeholders;
		g_assertion_failed_handler = std::bind(&UniVerifyEnabledAssertsTest::Assertion, this, _1, _2, _3, _4);
	}
	virtual ~UniVerifyEnabledAssertsTest() override
	{
		g_assertion_failed_handler = nullptr;
	}

	virtual void SetUp() override
	{
		failed_ = false;
	}

	virtual void TearDown() override
	{
	}

private:
	void Assertion(char const *assertion, char const *file, char const *function, int line)
	{
		UNI_UNUSED(assertion);
		UNI_UNUSED(file);
		UNI_UNUSED(function);
		UNI_UNUSED(line);

		failed_ = true;
	}

protected:
	bool failed_;
};

TEST_F(UniVerifyEnabledAssertsTest, ShouldNotFailIfConditionIsTrue)
{
	UNI_VERIFY(true);

	EXPECT_FALSE(failed_);
}

TEST_F(UniVerifyEnabledAssertsTest, ShouldFailIfConditionIsFalse)
{
	UNI_VERIFY(false);

	EXPECT_TRUE(failed_);
}

TEST_F(UniVerifyEnabledAssertsTest, ShouldEvaluateCode)
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

TEST_F(UniVerifyEnabledAssertsTest, ShouldEvaluateCodeOnlyOnce)
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
