#include <gtest/gtest.h>

#include "undef.h"
#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_DYNAMIC_ASSERT_HANDLER

#include <uniassert/uniassert.h>

namespace uniassert
{
namespace test
{

class UniCheckReturnTest : public ::testing::Test
{
protected:
	UniCheckReturnTest()
		: assert_handler_guard_(&UniCheckReturnTest::Assertion)
	{
	}
	virtual ~UniCheckReturnTest() override
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

bool UniCheckReturnTest::failed_ = false;

TEST_F(UniCheckReturnTest, ShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_CHECK_RETURN(true);
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniCheckReturnTest, ShouldNotFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_RETURN(false);
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniCheckReturnTest, ShouldNotReturnIfConditionIsTrue)
{
	bool returned = true;

	const auto func =
		[&returned]
		{
			UNI_CHECK_RETURN(true);
			returned = false;
		};

	func();

	EXPECT_FALSE(returned);
}

TEST_F(UniCheckReturnTest, ShouldReturnIfConditionIsFalse)
{
	bool returned = true;

	const auto func =
		[&returned]
		{
			UNI_CHECK_RETURN(false);
			returned = false;
		};

	func();

	EXPECT_TRUE(returned);
}

TEST_F(UniCheckReturnTest, ExtendedVersionShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_CHECK_RETURN(true, true);
			return false;
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniCheckReturnTest, ExtendedVersionShouldNotFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_RETURN(false, true);
			return false;
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniCheckReturnTest, ExtendedVersionShouldNotReturnIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_CHECK_RETURN(true, true);
			return false;
		};

	EXPECT_FALSE(func());
}

TEST_F(UniCheckReturnTest, ExtendedVersionShouldNotEvaluateValueIfConditionIsTrue)
{
	int counter = 0;
	const auto func =
		[&counter]
		{
			UNI_CHECK_RETURN(true, ++counter);
			return -1;
		};

	func();

	EXPECT_EQ(counter, 0);
}

TEST_F(UniCheckReturnTest, ExtendedVersionShouldReturnIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_RETURN(false, true);
			return false;
		};

	EXPECT_TRUE(func());
}

TEST_F(UniCheckReturnTest, ExtendedVersionShouldEvaluateValueOnceIfConditionIsFalse)
{
	int counter = 0;
	const auto func =
		[&counter]
		{
			UNI_CHECK_RETURN(false, ++counter);
			return -1;
		};

	func();

	EXPECT_EQ(counter, 1);
}

} // namespace test
} // namespace uniassert
