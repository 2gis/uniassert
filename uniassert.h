#pragma once

#include <stdexcept>
#include <cassert>

// UNI_FUNCTION

#if !defined(UNI_FUNCTION)
#	if defined(__GNUC__)
#		define UNI_FUNCTION __PRETTY_FUNCTION__
#	elif defined(_MSC_VER)
#		define UNI_FUNCTION __FUNCSIG__
#	else
#		define UNI_FUNCTION __func__
#	endif
#endif

// UNI_ANALYZER_NORETURN

#if defined(__clang__)
#	if __has_feature(attribute_analyzer_noreturn)
#		define UNI_ANALYZER_NORETURN __attribute__((analyzer_noreturn))
#	else
#		define UNI_ANALYZER_NORETURN
#	endif
#else
#	define UNI_ANALYZER_NORETURN
#endif

// UNI_ASSERTS_ENABLED

#if defined(NDEBUG) && !defined(UNI_FORCE_ASSERTS) && !defined(UNI_DISABLE_ASSERTS)
#	define UNI_DISABLE_ASSERTS
#elif !defined(UNI_DISABLE_ASSERTS)
#	define UNI_ASSERTS_ENABLED
#endif

// UNI_EMPTY_EXPRESSION

#define UNI_EMPTY_EXPRESSION ((void)0)

// UNI_UNUSED(var)

#define UNI_UNUSED(x) ::uniassert::uniassert_private::unused(x)

namespace uniassert
{
namespace uniassert_private
{

template<class T>
inline void unused(const T &) {}

} // namespace uniassert_private
} // namespace uniassert

// UNI_ASSERT(cond)

#if defined(UNI_DISABLE_ASSERTS)
#	define UNI_ASSERT(cond) UNI_EMPTY_EXPRESSION
#elif defined(UNI_ENABLE_DYNAMIC_ASSERT_HANDLER)
#	if defined(UNI_SYSTEM_ASSERT_HEADER)
#		include UNI_SYSTEM_ASSERT_HEADER
#	endif
#	if !defined(UNI_SYSTEM_ASSERT)
#		if defined(_MSC_VER) && defined(_DEBUG)
#			define UNI_SYSTEM_ASSERT(expr) _ASSERTE(expr)
#		elif defined(assert)
#			define UNI_SYSTEM_ASSERT(expr) assert(expr)
#		else
#			define UNI_SYSTEM_ASSERT(expr) UNI_EMPTY_EXPRESSION
#		endif
#	endif
#	define UNI_ASSERT(cond) \
		PRIVATE_UNI_ABEGIN \
			bool __uni_assert_cond_val = !!(cond); \
			if (!__uni_assert_cond_val) { \
				if (!::uniassert::uniassert_private::invoke_assert_handler(#cond, __FILE__, UNI_FUNCTION, __LINE__)) { \
					UNI_SYSTEM_ASSERT(__uni_assert_cond_val && #cond); \
				} \
			} \
		PRIVATE_UNI_AEND
#	define UNI_DYNAMIC_ASSERT_HANDLER_DEFINED
#elif defined(UNI_ENABLE_STATIC_ASSERT_HANDLER)
#	define UNI_ASSERT(cond) ((!(cond)) \
		? (::uniassert::assertion_failed(#cond, __FILE__, UNI_FUNCTION, __LINE__)) \
		: UNI_EMPTY_EXPRESSION)
#	define UNI_STATIC_ASSERT_HANDLER_DEFINED
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
#			define UNI_SYSTEM_ASSERT(expr) UNI_EMPTY_EXPRESSION
#		endif
#	endif
#	define UNI_ASSERT UNI_SYSTEM_ASSERT
#endif

#if defined(UNI_ENABLE_DYNAMIC_ASSERT_HANDLER)
namespace uniassert
{

using assert_handler = void (*)(const char * assertion, const char * file, const char * function, int line);

#if defined(UNI_DYNAMIC_ASSERT_HANDLER_DEFINED)
namespace uniassert_private
{

inline assert_handler * get_current_assert_handler_ptr()
{
	static assert_handler current_assert_handler;
	return &current_assert_handler;
}

inline bool invoke_assert_handler(const char * const assertion, const char * const file, const char * const function, const int line) UNI_ANALYZER_NORETURN
{
	const auto current_assert_handler_ptr = get_current_assert_handler_ptr();
	if (!*current_assert_handler_ptr)
	{
		return false;
	}

	(*current_assert_handler_ptr)(assertion, file, function, line);
	return true;
}

} // namespace uniassert_private

inline assert_handler set_assert_handler(assert_handler new_assert_handler)
{
	const auto current_assert_handler_ptr = uniassert_private::get_current_assert_handler_ptr();
	assert_handler old_assert_handler = *current_assert_handler_ptr;
	*current_assert_handler_ptr = new_assert_handler;
	return old_assert_handler;
}

class assert_handler_guard final
{
public:
	explicit assert_handler_guard(const assert_handler new_assert_handler)
		: original_assert_handler_(set_assert_handler(new_assert_handler))
	{
	}

	~assert_handler_guard()
	{
		set_assert_handler(original_assert_handler_);
	}

private:
	const assert_handler original_assert_handler_;
};

class disable_asserts_guard final
{
public:
	disable_asserts_guard()
		: guard_(&disable_asserts_guard::assertion_failed)
	{
	}

	static void assertion_failed(char const * const assertion, char const * const file, char const * const function, const int line)
	{
		UNI_UNUSED(assertion);
		UNI_UNUSED(file);
		UNI_UNUSED(function);
		UNI_UNUSED(line);
	}

private:
	const assert_handler_guard guard_;
};
#else
inline assert_handler set_assert_handler(assert_handler new_assert_handler)
{
	UNI_UNUSED(new_assert_handler);
	return nullptr;
}

class assert_handler_guard final
{
public:
	explicit assert_handler_guard(const assert_handler new_assert_handler)
	{
		UNI_UNUSED(new_assert_handler);
	}
};

class disable_asserts_guard final
{
public:
	disable_asserts_guard() {}
};
#endif

} // namespace uniassert
#elif defined(UNI_STATIC_ASSERT_HANDLER_DEFINED)
namespace uniassert
{

void assertion_failed(char const * assertion, char const * file, char const * function, int line) UNI_ANALYZER_NORETURN;

} // namespace uniassert
#endif

// UNI_VERIFY(expr)

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
		UNI_UNUSED(__uni_cond_val); \
	PRIVATE_UNI_AEND

// UNI_ENSURE_THROW(expr[, exception_type], message)

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

// HACK for MSVS which doesn't expand __VA_ARGS__ correctly
#define PRIVATE_UNI_EXPAND(x) x

#define PRIVATE_UNI_GET_ARG_3(arg1, arg2, arg3, ...) \
	arg3

#define PRIVATE_UNI_GET_ARG_4(arg1, arg2, arg3, arg4, ...) \
	arg4

#define PRIVATE_UNI_FAULT_ACTION_THROW(error_message) \
	throw ::std::runtime_error(error_message);

#define PRIVATE_UNI_FAULT_ACTION_THROW_TYPE(type, error_message) \
	throw type(error_message);

#define PRIVATE_UNI_ENSURE_THROW(expr, error_message) \
	PRIVATE_UNI_ENSURE(expr, \
		PRIVATE_UNI_FAULT_ACTION_THROW(error_message) \
	)

#define PRIVATE_UNI_ENSURE_THROW_TYPE(expr, type, error_message) \
	PRIVATE_UNI_ENSURE(expr, \
		PRIVATE_UNI_FAULT_ACTION_THROW_TYPE(type, error_message) \
	)

#define PRIVATE_UNI_ENSURE_THROW_CHOOSER(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_GET_ARG_4(__VA_ARGS__, PRIVATE_UNI_ENSURE_THROW_TYPE, PRIVATE_UNI_ENSURE_THROW, NONSENSE, NONSENSE))

#define UNI_ENSURE_THROW(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_ENSURE_THROW_CHOOSER(__VA_ARGS__)(__VA_ARGS__))

// UNI_CHECK_THROW(expr[, exception_type], message)

#define PRIVATE_UNI_CHECK_THROW(expr, error_message) \
	PRIVATE_UNI_CHECK(expr, \
		PRIVATE_UNI_FAULT_ACTION_THROW(error_message) \
	)

#define PRIVATE_UNI_CHECK_THROW_TYPE(expr, type, error_message) \
	PRIVATE_UNI_CHECK(expr, \
		PRIVATE_UNI_FAULT_ACTION_THROW_TYPE(type, error_message) \
	)

#define PRIVATE_UNI_CHECK_THROW_CHOOSER(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_GET_ARG_4(__VA_ARGS__, PRIVATE_UNI_CHECK_THROW_TYPE, PRIVATE_UNI_CHECK_THROW, NONSENSE, NONSENSE))

#define UNI_CHECK_THROW(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_CHECK_THROW_CHOOSER(__VA_ARGS__)(__VA_ARGS__))

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
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_GET_ARG_3(__VA_ARGS__, PRIVATE_UNI_ENSURE_RETURN_VALUE, PRIVATE_UNI_ENSURE_RETURN, NONSENSE))

#define UNI_ENSURE_RETURN(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_ENSURE_RETURN_CHOOSER(__VA_ARGS__)(__VA_ARGS__))

// UNI_CHECK_RETURN(expr[, return_code])

#define PRIVATE_UNI_CHECK_RETURN_VALUE(expr, return_code) \
	PRIVATE_UNI_CHECK(expr, \
		PRIVATE_UNI_FAULT_ACTION_RETURN(return_code) \
	)

#define PRIVATE_UNI_CHECK_RETURN(expr) \
	PRIVATE_UNI_CHECK(expr, \
		return; \
	)

#define PRIVATE_UNI_CHECK_RETURN_CHOOSER(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_GET_ARG_3(__VA_ARGS__, PRIVATE_UNI_CHECK_RETURN_VALUE, PRIVATE_UNI_CHECK_RETURN, NONSENSE))

#define UNI_CHECK_RETURN(...) \
	PRIVATE_UNI_EXPAND(PRIVATE_UNI_CHECK_RETURN_CHOOSER(__VA_ARGS__)(__VA_ARGS__))
