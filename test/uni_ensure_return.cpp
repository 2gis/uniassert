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

class UniEnsureReturnTest : public ::testing::Test
{
protected:
	UniEnsureReturnTest()
	{
		using namespace std::placeholders;
		g_assertion_failed_handler = std::bind(&UniEnsureReturnTest::Assertion, this, _1, _2, _3, _4);
	}
	virtual ~UniEnsureReturnTest() override
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

} // namespace test
} // namespace uniassert
