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

class UniEnsureThrowTest : public ::testing::Test
{
protected:
	UniEnsureThrowTest()
	{
		using namespace std::placeholders;
		g_assertion_failed_handler = std::bind(&UniEnsureThrowTest::Assertion, this, _1, _2, _3, _4);
	}
	virtual ~UniEnsureThrowTest() override
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

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldNotFailIfConditionIsTrue)
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

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldFailIfConditionIsFalse)
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

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldNotThrowIfConditionIsTrue)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(true, "error");
		};

	EXPECT_NO_THROW(func());
}

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldThrowIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, "error");
		};

	EXPECT_ANY_THROW(func());
}

TEST_F(UniEnsureThrowTest, ExtendedVersionShouldThrowSelectedExceptionIfConditionIsFalse)
{
	const auto func =
		[]
		{
			UNI_ENSURE_THROW(false, TestException, "error");
		};

	EXPECT_THROW(func(), TestException);
}

} // namespace test
} // namespace uniassert
