#pragma once

#include <string>

namespace uniassert
{
namespace test
{

class test_exception
{
public:
	test_exception(const char * error_message)
		: error_(error_message)
	{
	}

	const char * what() const
	{
		return error_.c_str();
	}

private:
	std::string error_;
};

} // namespace test
} // namespace uniassert
