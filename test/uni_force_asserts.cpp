#include <gtest/gtest.h>

#include "undef.h"
#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_DYNAMIC_ASSERT_HANDLER

#include <uniassert/uniassert.h>

#if defined(UNI_DISABLE_ASSERTS)
#	error "UNI_DISABLE_ASSERTS is defined"
#endif
#if !defined(UNI_ASSERTS_ENABLED)
#	error "UNI_ASSERTS_ENABLED is not defined"
#endif

namespace uniassert
{
namespace test
{

class UniForceAssertsTest : public ::testing::Test
{
protected:
	UniForceAssertsTest()
		: assert_handler_guard_(&UniForceAssertsTest::Assertion)
	{
	}
	virtual ~UniForceAssertsTest() override
	{
	}

	virtual void SetUp() override
	{
		failed_ = false;
	}

	virtual void TearDown() override
	{
	}

private:
	static void Assertion(char const * assertion, char const * file, char const * function, int line)
	{
		UNI_UNUSED(assertion);
		UNI_UNUSED(file);
		UNI_UNUSED(function);
		UNI_UNUSED(line);

		failed_ = true;
	}

protected:
	static bool failed_;
	const assert_handler_guard assert_handler_guard_;
};

bool UniForceAssertsTest::failed_ = false;

TEST_F(UniForceAssertsTest, ShouldNotFailIfConditionIsTrue)
{
	UNI_ASSERT(true);

	EXPECT_FALSE(failed_);
}

TEST_F(UniForceAssertsTest, ShouldFailIfConditionIsFalse)
{
	UNI_ASSERT(false);

	EXPECT_TRUE(failed_);
}

TEST_F(UniForceAssertsTest, ShouldEvaluateCode)
{
	bool called = false;
	auto func =
		[&called]
		{
			called = true;
			return true;
		};

	UNI_ASSERT(func());

	EXPECT_TRUE(called);
}

TEST_F(UniForceAssertsTest, ShouldEvaluateCodeOnlyOnce)
{
	unsigned called_times = 0;
	auto func =
		[&called_times]
		{
			++called_times;
			return true;
		};

	UNI_ASSERT(func());

	EXPECT_EQ(1u, called_times);
}

} // namespace test
} // namespace uniassert
