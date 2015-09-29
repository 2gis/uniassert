#include <functional>
#include <gtest/gtest.h>

#define UNI_FORCE_ASSERTS
#define UNI_ENABLE_ASSERT_HANDLER
#include <uniassert/uniassert.h>

#include "assertion_failed_handler.h"
#include "TestException.h"

namespace uniassert
{
namespace test
{

class UniThrowTest : public ::testing::Test
{
protected:
	UniThrowTest()
	{
		using namespace std::placeholders;
		g_assertion_failed_handler = std::bind(&UniThrowTest::Assertion, this, _1, _2, _3, _4);
	}
	virtual ~UniThrowTest() override
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

TEST_F(UniThrowTest, ShouldNotFailIfConditionIsTrue)
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

TEST_F(UniThrowTest, ShouldNotFailIfConditionIsFalse)
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

TEST_F(UniThrowTest, ShouldNotThrowIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(true, "error");
		};

	EXPECT_NO_THROW(func());
}

TEST_F(UniThrowTest, ShouldThrowIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, "error");
		};

	EXPECT_ANY_THROW(func());
}

TEST_F(UniThrowTest, ShouldThrowRuntimeErrorIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, "error");
		};

	EXPECT_THROW(func(), ::std::runtime_error);
}

TEST_F(UniThrowTest, ShouldThrowRuntimeErrorWithCorrectTextIfConditionIsFalse)
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

TEST_F(UniThrowTest, ExtendedVersionShouldNotFailIfConditionIsTrue)
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

TEST_F(UniThrowTest, ExtendedVersionShouldNotFailIfConditionIsFalse)
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

TEST_F(UniThrowTest, ExtendedVersionShouldNotThrowIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(true, "error");
		};

	EXPECT_NO_THROW(func());
}

TEST_F(UniThrowTest, ExtendedVersionShouldThrowIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, "error");
		};

	EXPECT_ANY_THROW(func());
}

TEST_F(UniThrowTest, ShouldThrowSelectedExceptionIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, TestException, "error");
		};

	EXPECT_THROW(func(), TestException);
}

TEST_F(UniThrowTest, ShouldThrowSelectedExceptionWithCorrectTextIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_CHECK_THROW(false, TestException, "error");
		};

	try
	{
		func();
	}
	catch (const TestException &exception)
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
