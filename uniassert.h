#pragma once

#include <stdexcept>
#include <cassert>

#if !defined(UNI_FUNCTION)
#	if defined(__GNUC__)
#		define UNI_FUNCTION __PRETTY_FUNCTION__
#	elif defined(_MSC_VER)
#		define UNI_FUNCTION __FUNCSIG__
#	else
#		define UNI_FUNCTION __func__
#	endif
#endif

#if defined(NDEBUG) && !defined(UNI_FORCE_ASSERTS) && !defined(UNI_DISABLE_ASSERTS)
#	define UNI_DISABLE_ASSERTS
#endif

#if defined(UNI_DISABLE_ASSERTS)
#	define UNI_ASSERT(cond) ((void)0)
#elif defined(UNI_ENABLE_ASSERT_HANDLER)
#	define UNI_ASSERT(cond) ((!(cond)) \
		? (uniassert::assertion_failed(#cond, __FILE__, UNI_FUNCTION, __LINE__)) \
		: ((void)0))
#	define UNI_ASSERTION_HANDLER_DEFINED
#else
#	if defined(UNI_SYSTEM_ASSERT_HEADER)
#		include UNI_SYSTEM_ASSERT_HEADER
#	endif
#	if !defined(UNI_SYSTEM_ASSERT)
#		if defined(_MSC_VER) && defined(_DEBUG)
#			define UNI_SYSTEM_ASSERT(expr) _ASSERTE(expr)
#		elif defined(assert)
#			define UNI_SYSTEM_ASSERT(expr) assert(expr)
#		else
#			define UNI_SYSTEM_ASSERT(expr) ((void)0)
#		endif
#	endif
#	define UNI_ASSERT UNI_SYSTEM_ASSERT
#endif

#if defined(__clang__)
#	if __has_feature(attribute_analyzer_noreturn)
#		define UNI_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
#	else
#		define UNI_ANALYZER_NORETURN
#	endif
#else
#	define UNI_ANALYZER_NORETURN
#endif

#ifdef UNI_ASSERTION_HANDLER_DEFINED
namespace uniassert
{

void assertion_failed(char const *assertion, char const *file, char const *function, int line) UNI_ANALYZER_NORETURN;

} // namespace uniassert
#endif

namespace uniassert
{
namespace uniassert_private
{

template<class T>
inline void unused(const T &) {}

} // namespace uniassert_private
} // namespace uniassert

#define UNI_UNUSED(x) ::uniassert::uniassert_private::unused(x);

#define PRIVATE_UNI_ABEGIN do {

#if defined(_MSC_VER)
#	define PRIVATE_UNI_AEND } \
		__pragma(warning(push)) \
		__pragma(warning(disable: 4127)) \
		while(0) \
		__pragma(warning(pop))
#else
#	define PRIVATE_UNI_AEND } while(0)
#endif

#define UNI_VERIFY(expr) \
	PRIVATE_UNI_ABEGIN \
		bool __uni_cond_val = !!(expr); \
		UNI_ASSERT(__uni_cond_val && #expr); \
		UNI_UNUSED(__uni_cond_val) \
	PRIVATE_UNI_AEND

#define PRIVATE_UNI_ENSURE(expr, fault_action) \
	PRIVATE_UNI_ABEGIN \
		bool __uni_cond_val = !!(expr); \
		UNI_ASSERT(__uni_cond_val && #expr); \
		if (!__uni_cond_val) { \
			fault_action \
		} \
	PRIVATE_UNI_AEND

#define PRIVATE_UNI_CHECK(expr, fault_action) \
	PRIVATE_UNI_ABEGIN \
		if (!(expr)) { \
			fault_action \
		} \
	PRIVATE_UNI_AEND

// HACK for MSVS 2012 which doesn't expand __VA_ARGS__ correctly
#define PRIVATE_UNI_EXPAND(x) x

#define PRIVATE_UNI_GET_3TH_ARG(arg1, arg2, arg3, ...) \
	arg3

#define PRIVATE_UNI_GET_4TH_ARG(arg1, arg2, arg3, arg4, ...) \
	arg4

#define PRIVATE_UNI_FAULT_ACTION_THROW(error_message) \
	throw ::std::runtime_error(error_message);

#define PRIVATE_UNI_FAULT_ACTION_THROW_TYPE(type, error_message) \
	throw type(error_message);

// UNI_ENSURE_THROW(expr[, exception_type], message)

#define PRIVATE_UNI_ENSURE_THROW(expr, error_message) \
	PRIVATE_UNI_ENSURE(expr, \
		PRIVATE_UNI_FAULT_ACTION_THROW(error_message) \
	)

#define PRIVATE_UNI_ENSURE_THROW_TYPE(expr, type, error_message) \
	PRIVATE_UNI_ENSURE(expr, \
		PRIVATE_UNI_FAULT_ACTION_THROW_TYPE(type, error_message) \
	)

#define PRIVATE_UNI_ENSURE_THROW_CHOOSER(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_GET_4TH_ARG(__VA_ARGS__, PRIVATE_UNI_ENSURE_THROW_TYPE, PRIVATE_UNI_ENSURE_THROW, NONSENSE))

#define UNI_ENSURE_THROW(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_ENSURE_THROW_CHOOSER(__VA_ARGS__)(__VA_ARGS__))

// UNI_THROW_IF(expr[, exception_type], message)

#define PRIVATE_UNI_THROW_IF(expr, error_message) \
	PRIVATE_UNI_CHECK(expr, \
		PRIVATE_UNI_FAULT_ACTION_THROW(error_message) \
	)

#define PRIVATE_UNI_THROW_IF_TYPE(expr, type, error_message) \
	PRIVATE_UNI_CHECK(expr, \
		PRIVATE_UNI_FAULT_ACTION_THROW_TYPE(type, error_message) \
	)

#define PRIVATE_UNI_THROW_IF_CHOOSER(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_GET_4TH_ARG(__VA_ARGS__, PRIVATE_UNI_THROW_IF_TYPE, PRIVATE_UNI_THROW_IF, NONSENSE))

#define UNI_THROW_IF(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_THROW_IF_CHOOSER(__VA_ARGS__)(__VA_ARGS__))

// UNI_ENSURE_RETURN(expr[, return_code])

#define PRIVATE_UNI_FAULT_ACTION_RETURN(return_code) \
	return return_code;

#define PRIVATE_UNI_ENSURE_RETURN_VALUE(expr, return_code) \
	PRIVATE_UNI_ENSURE(expr, \
		PRIVATE_UNI_FAULT_ACTION_RETURN(return_code) \
	)

#define PRIVATE_UNI_ENSURE_RETURN(expr) \
	PRIVATE_UNI_ENSURE(expr, \
		return; \
	)

#define PRIVATE_UNI_ENSURE_RETURN_CHOOSER(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_GET_3TH_ARG(__VA_ARGS__, PRIVATE_UNI_ENSURE_RETURN_VALUE, PRIVATE_UNI_ENSURE_RETURN, NONSENSE))

#define UNI_ENSURE_RETURN(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_ENSURE_RETURN_CHOOSER(__VA_ARGS__)(__VA_ARGS__))

// UNI_RETURN_IF(expr[, return_code])

#define PRIVATE_UNI_RETURN_IF_VALUE(expr, return_code) \
	PRIVATE_UNI_CHECK(expr, \
		PRIVATE_UNI_FAULT_ACTION_RETURN(return_code) \
	)

#define PRIVATE_UNI_RETURN_IF(expr) \
	PRIVATE_UNI_CHECK(expr, \
		return; \
	)

#define PRIVATE_UNI_RETURN_IF_CHOOSER(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_GET_3TH_ARG(__VA_ARGS__, PRIVATE_UNI_RETURN_IF_VALUE, PRIVATE_UNI_RETURN_IF, NONSENSE))

#define UNI_RETURN_IF(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_RETURN_IF_CHOOSER(__VA_ARGS__)(__VA_ARGS__))

