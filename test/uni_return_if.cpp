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

class UniReturnTest : public ::testing::Test
{
protected:
	UniReturnTest()
	{
		using namespace std::placeholders;
		g_assertion_failed_handler = std::bind(&UniReturnTest::Assertion, this, _1, _2, _3, _4);
	}
	virtual ~UniReturnTest() override
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

TEST_F(UniReturnTest, ShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_RETURN_IF(true);
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniReturnTest, ShouldNotFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_RETURN_IF(false);
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniReturnTest, ShouldNotReturnIfConditionIsTrue)
{
	bool returned = true;

	const auto func =
		[&returned]
		{
			UNI_RETURN_IF(true);
			returned = false;
		};

	func();

	EXPECT_FALSE(returned);
}

TEST_F(UniReturnTest, ShouldReturnIfConditionIsFalse)
{
	bool returned = true;

	const auto func =
		[&returned]
		{
			UNI_RETURN_IF(false);
			returned = false;
		};

	func();

	EXPECT_TRUE(returned);
}

TEST_F(UniReturnTest, ExtendedVersionShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_RETURN_IF(true, true);
			return false;
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniReturnTest, ExtendedVersionShouldNotFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_RETURN_IF(false, true);
			return false;
		};

	func();

	EXPECT_FALSE(failed_);
}

TEST_F(UniReturnTest, ExtendedVersionShouldNotReturnIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_RETURN_IF(true, true);
			return false;
		};

	EXPECT_FALSE(func());
}

TEST_F(UniReturnTest, ExtendedVersionShouldReturnIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_RETURN_IF(false, true);
			return false;
		};

	EXPECT_TRUE(func());
}

} // namespace test
} // namespace uniassert
