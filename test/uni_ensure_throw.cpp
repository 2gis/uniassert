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

class UniEnsureThrowTest : public ::testing::Test
{
protected:
	UniEnsureThrowTest()
		: assert_handler_guard_(&UniEnsureThrowTest::Assertion)
	{
	}
	virtual ~UniEnsureThrowTest() override
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

bool UniEnsureThrowTest::failed_ = false;

TEST_F(UniEnsureThrowTest, ShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(true, "error");
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

TEST_F(UniEnsureThrowTest, ShouldFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, "error");
		};

	try
	{
		func();
	}
	catch (...)
	{
	}

	EXPECT_TRUE(failed_);
}

TEST_F(UniEnsureThrowTest, ShouldNotThrowIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(true, "error");
		};

	EXPECT_NO_THROW(func());
}

TEST_F(UniEnsureThrowTest, ShouldNotEvaluateMessageIfConditionIsTrue)
{
	auto message = "1error";
	const auto func =
		[&message]
		{
			UNI_ENSURE_THROW(true, ++message);
		};

	func();

	EXPECT_STREQ("1error", message);
}

TEST_F(UniEnsureThrowTest, ShouldThrowIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, "error");
		};

	EXPECT_ANY_THROW(func());
}

TEST_F(UniEnsureThrowTest, ShouldThrowRuntimeErrorIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, "error");
		};

	EXPECT_THROW(func(), ::std::runtime_error);
}

TEST_F(UniEnsureThrowTest, ShouldThrowRuntimeErrorWithCorrectTextIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, "error");
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

TEST_F(UniEnsureThrowTest, ShouldEvaluateMessageOnceIfConditionIsFalse)
{
	auto message = "1error";
	const auto func =
		[&message]
		{
			UNI_ENSURE_THROW(false, ++message);
		};

	EXPECT_ANY_THROW(func());

	EXPECT_STREQ("error", message);
}

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldNotFailIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(true, test_exception, "error");
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

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldFailIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, test_exception, "error");
		};

	try
	{
		func();
	}
	catch (...)
	{
	}

	EXPECT_TRUE(failed_);
}

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldNotThrowIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(true, test_exception, "error");
		};

	EXPECT_NO_THROW(func());
}

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldNotEvaluateMessageIfConditionIsTrue)
{
	auto message = "1error";
	const auto func =
		[&message]
		{
			UNI_ENSURE_THROW(true, test_exception, ++message);
		};

	func();

	EXPECT_STREQ("1error", message);
}

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldThrowIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, test_exception, "error");
		};

	EXPECT_ANY_THROW(func());
}

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldThrowSelectedExceptionIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, test_exception, "error");
		};

	EXPECT_THROW(func(), test_exception);
}

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldThrowSelectedExceptionWithCorrectTextIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, test_exception, "error");
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

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldEvaluateMessageOnceIfConditionIsFalse)
{
	auto message = "1error";
	const auto func =
		[&message]
		{
			UNI_ENSURE_THROW(false, test_exception, ++message);
		};

	EXPECT_ANY_THROW(func());

	EXPECT_STREQ("error", message);
}

} // namespace test
} // namespace uniassert
