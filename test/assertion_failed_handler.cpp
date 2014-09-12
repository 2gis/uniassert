#include "assertion_failed_handler.h"

namespace uniassert
{
namespace test
{

AssertionFailedHandler g_assertion_failed_handler;

} // namespase test

void assertion_failed(char const *assertion, char const *file, char const *function, int line);

void assertion_failed(char const *assertion, char const *file, char const *function, int line)
{
	if (test::g_assertion_failed_handler)
	{
		test::g_assertion_failed_handler(assertion, file, function, line);
	}
}

} // namespace uniassert
