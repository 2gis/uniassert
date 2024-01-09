#include <gtest/gtest.h>

#include "undef.h"
#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_DYNAMIC_ASSERT_HANDLER

#include <uniassert/uniassert.h>

namespace uniassert
{
namespace test
{

class UniEnsureReturnTest : public ::testing::Test
{
protected:
	UniEnsureReturnTest()
		: assert_handler_guard_(&UniEnsureReturnTest::Assertion)
	{
	}
	virtual ~UniEnsureReturnTest() override
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

bool UniEnsureReturnTest::failed_ = false;

TEST_F(UniEnsureReturnTest, ShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_ENSURE_RETURN(true);
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniEnsureReturnTest, ShouldFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_RETURN(false);
		};

	func();

	EXPECT_TRUE(failed_);
}

TEST_F(UniEnsureReturnTest, ShouldNotReturnIfConditionIsTrue)
{
	bool returned = true;

	const auto func =
		[&returned]
		{
			UNI_ENSURE_RETURN(true);
			returned = false;
		};

	func();

	EXPECT_FALSE(returned);
}

TEST_F(UniEnsureReturnTest, ShouldReturnIfConditionIsFalse)
{
	bool returned = true;

	const auto func =
		[&returned]
		{
			UNI_ENSURE_RETURN(false);
			returned = false;
		};

	func();

	EXPECT_TRUE(returned);
}

TEST_F(UniEnsureReturnTest, ExtendedVersionShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_ENSURE_RETURN(true, true);
			return false;
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniEnsureReturnTest, ExtendedVersionShouldFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_RETURN(false, true);
			return false;
		};

	func();

	EXPECT_TRUE(failed_);
}

TEST_F(UniEnsureReturnTest, ExtendedVersionShouldNotReturnIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_ENSURE_RETURN(true, true);
			return false;
		};

	EXPECT_FALSE(func());
}

TEST_F(UniEnsureReturnTest, ExtendedVersionShouldNotEvaluateResultIfConditionIsTrue)
{
	int counter = 0;
	const auto func =
		[&counter]
		{
			UNI_ENSURE_RETURN(true, ++counter);
			return -1;
		};

	func();

	EXPECT_EQ(0, counter);
}

TEST_F(UniEnsureReturnTest, ExtendedVersionShouldReturnIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_RETURN(false, true);
			return false;
		};

	EXPECT_TRUE(func());
}

TEST_F(UniEnsureReturnTest, ExtendedVersionShouldEvauateResultOnceIfConditionIsFalse)
{
	int counter = 0;
	const auto func =
		[&counter]
		{
			UNI_ENSURE_RETURN(false, ++counter);
			return -1;
		};

	func();

	EXPECT_EQ(1, counter);
}

} // namespace test
} // namespace uniassert
