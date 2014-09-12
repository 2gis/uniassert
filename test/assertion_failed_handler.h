#pragma once

#include <functional>

namespace uniassert
{
namespace test
{

typedef std::function<void (char const *assertion, char const *file, char const *function, int line)> AssertionFailedHandler;

extern AssertionFailedHandler g_assertion_failed_handler;

} // namespace test
} // namespace uniassert