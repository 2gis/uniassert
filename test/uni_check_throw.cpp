#include <gtest/gtest.h>

#include "test_exception.h"

#include "undef.h"
#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_DYNAMIC_ASSERT_HANDLER

#include <uniassert/uniassert.h>

namespace uniassert
{
namespace test
{

class UniCheckThrowTest : public ::testing::Test
{
protected:
	UniCheckThrowTest()
		: assert_handler_guard_(&UniCheckThrowTest::Assertion)
	{
	}
	virtual ~UniCheckThrowTest() override
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

bool UniCheckThrowTest::failed_ = false;

TEST_F(UniCheckThrowTest, ShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(true, "error");
		};

	try
	{
		func();
	}
	catch (...)
	{
	}

	EXPECT_FALSE(failed_);
}

TEST_F(UniCheckThrowTest, ShouldNotFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, "error");
		};

	try
	{
		func();
	}
	catch (...)
	{
	}

	EXPECT_FALSE(failed_);
}

TEST_F(UniCheckThrowTest, ShouldNotThrowIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(true, "error");
		};

	EXPECT_NO_THROW(func());
}

TEST_F(UniCheckThrowTest, ShouldNotEvaluateMessageIfConditionIsTrue)
{
	auto message = "1error";
	const auto func =
		[&message]
		{
			UNI_CHECK_THROW(true, ++message);
		};

	func();

	EXPECT_STREQ("1error", message);
}

TEST_F(UniCheckThrowTest, ShouldThrowIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, "error");
		};

	EXPECT_ANY_THROW(func());
}

TEST_F(UniCheckThrowTest, ShouldThrowRuntimeErrorIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, "error");
		};

	EXPECT_THROW(func(), ::std::runtime_error);
}

TEST_F(UniCheckThrowTest, ShouldThrowRuntimeErrorWithCorrectTextIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, "error");
		};

	try
	{
		func();
	}
	catch (const ::std::runtime_error &exception)
	{
		EXPECT_STREQ("error", exception.what());
	}
	catch (...)
	{
		FAIL();
	}
}

TEST_F(UniCheckThrowTest, ShouldEvaluateMessageOnceIfConditionIsFalse)
{
	auto message = "1error";
	const auto func =
		[&message]
		{
			UNI_CHECK_THROW(false, ++message);
		};

	EXPECT_ANY_THROW(func());

	EXPECT_STREQ("error", message);
}

TEST_F(UniCheckThrowTest, ExtendedVersionShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(true, test_exception, "error");
		};

	try
	{
		func();
	}
	catch (...)
	{
	}

	EXPECT_FALSE(failed_);
}

TEST_F(UniCheckThrowTest, ExtendedVersionShouldNotFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, test_exception, "error");
		};

	try
	{
		func();
	}
	catch (...)
	{
	}

	EXPECT_FALSE(failed_);
}

TEST_F(UniCheckThrowTest, ExtendedVersionShouldNotThrowIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(true, test_exception, "error");
		};

	EXPECT_NO_THROW(func());
}

TEST_F(UniCheckThrowTest, ExtendedVersionShouldNotEvaluateMessageIfConditionIsTrue)
{
	auto message = "1error";
	const auto func =
		[&message]
		{
			UNI_CHECK_THROW(true, test_exception, ++message);
		};

	func();

	EXPECT_STREQ("1error", message);
}

TEST_F(UniCheckThrowTest, ExtendedVersionShouldThrowIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, test_exception, "error");
		};

	EXPECT_ANY_THROW(func());
}

TEST_F(UniCheckThrowTest, ExtendedVersionShouldEvaluateMessageOnceIfConditionIsFalse)
{
	auto message = "1error";
	const auto func =
		[&message]
		{
			UNI_CHECK_THROW(false, test_exception, ++message);
		};

	EXPECT_ANY_THROW(func());

	EXPECT_STREQ("error", message);
}

TEST_F(UniCheckThrowTest, ExtendedVersionShouldThrowSelectedExceptionIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, test_exception, "error");
		};

	EXPECT_THROW(func(), test_exception);
}

TEST_F(UniCheckThrowTest, ExtendedVersionShouldThrowSelectedExceptionWithCorrectTextIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, test_exception, "error");
		};

	try
	{
		func();
	}
	catch (const test_exception &exception)
	{
		EXPECT_STREQ("error", exception.what());
	}
	catch (...)
	{
		FAIL();
	}
}

} // namespace test
} // namespace uniassert
