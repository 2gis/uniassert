# uniassert

The uniassert library is a small collection of useful macros. Most of them are
designed for assumption checks (and this is a reason behind the library name).

This library was tested on gcc 4.8, gcc 4.9, clang 3.5 and MSVS 2013,
but will probably work on any c++ compiler with c++11 support.

## Assumption checks

### Using

#### UNI_ASSERT

If you are familiar with `assert` from the standard library, `BOOST_ASSERT`
from *boost* or `Q_ASSERT` from *Qt*, you already know how to use `UNI_ASSERT`.
For all others we recommend to read Wikipedia article
[Assertion (software development)](https://en.wikipedia.org/wiki/Assertion_%28software_development%29).
By default `UNI_ASSERT` is equivalent to `assert` (or `_ASSERTE` for MSVS in
most cases), but this behavior can be changed (see "Configuration" section).

You can use `UNI_ASSERT` in other macros but make sure that the expression is
evaluated only once.

#### UNI_VERIFY

`UNI_VERIFY` is similar to `BOOST_VERIFY` from *boost*. It has exactly the same
behavior as `UNI_ASSERT`, except that the expression passed to `UNI_VERIFY` is
always evaluated.

`UNI_VERIFY` uses `UNI_ASSERT` but the expression is evaluated only once.

#### UNI_ENSURE_THROW

`UNI_ENSURE_THROW(condition[, exception_type], message)`

`UNI_ENSURE_THROW` throws exception if `condition` is not equal to `true`.
If `exception_type` is not specified, `std::runtime_error` is thrown. In that
case `message` must be a C string, `std::string` or any other type that can be
implicitly converted to these types. If `exception_type` is specified, it must
be constructable from the `message` type.

`UNI_ENSURE_THROW` uses `UNI_ASSERT` but the expression is evaluated only once.

#### UNI_ENSURE_RETURN

`UNI_ENSURE_RETURN(condition[, return_code])`

`UNI_ENSURE_RETURN` returns `return_code` if `condition` is not equal to `true`.
If `UNI_ENSURE_RETURN` is used in a function with `void` result type,
`return_code` must be omitted.

`UNI_ENSURE_RETURN` uses `UNI_ASSERT` but the expression is evaluated only once.

### Configuration

To configure *uniassert* library add additional defines before including
`uniassert.h`. These defines can be added either by passing additional
parameters to a compiler, or by adding them inside your own proxy header (see
example below).

`myassert.h`:

    #define PARAM VALUE
    #include <uniassert.h>

`code.cpp`:

    #include <myassert.h>

In later examples we will provide code for the second case, but `uniassert.h`
include will be skipped.

#### UNI_ENABLE_ASSERT_HANDLER

It is possible to call an external function when an assumption check is failed.
All you need is to define `UNI_ENABLE_ASSERT_HANDLER` and implement
`uniassert::assertion_failed` function somewhere else:

    namespace uniassert
    {

    void assertion_failed(char const *assertion, char const *file, char const *function, int line)
    {
        // Something useful
    }

    } // namespace uniassert

#### UNI_FUNCTION

The function description passed to `uniassert::assertion_failed` is compiler
specific. We use `__PRETTY_FUNCTION__` for gcc and clang, `__FUNCSIG__` for MSVS
and `__func__` in other cases. If you think that the generated function
description is too long (or your compiler has a better macro for that), you can
define your own `UNI_FUNCTION`:

    #define UNI_FUNCTION COMPILER_SPECIFIC_FUNCTION_NAME

`UNI_FUNCTION` is always defined and you can use it in your own code.

#### UNI_SYSTEM_ASSERT

By default `UNI_ASSERT` is mapped to `assert` or `_ASSERTE` for MSVS, but one
can change this mapping by defining `UNI_SYSTEM_ASSERT`:

    #define UNI_SYSTEM_ASSERT YOUR_OWN_ASSERT

If both `UNI_SYSTEM_ASSERT` and `UNI_ENABLE_ASSERT_HANDLER` are defined,
`UNI_SYSTEM_ASSERT` will be ignored.

#### UNI_SYSTEM_ASSERT_HEADER

If your `UNI_SYSTEM_ASSERT` requires any additional header to be included, you
can also define `UNI_SYSTEM_ASSERT_HEADER`:

    #define UNI_SYSTEM_ASSERT_HEADER <QtCore/QtGlobal>
    #define UNI_SYSTEM_ASSERT Q_ASSERT

#### UNI_DISABLE_ASSERTS

You can disable `UNI_ASSERT` even for **debug** builds by defining
`UNI_DISABLE_ASSERT`.

#### UNI_FORCE_ASSERTS

By default `UNI_ASSERT` does nothing if `NDEBUG` is defined (almost always
true for **release** builds). This check can be disabled by defining
`UNI_FORCE_ASSERTS`. You have to define either `UNI_SYSTEM_ASSERT` or
`UNI_ENABLE_ASSERT_HANDLER`, otherwise `UNI_ASSERT` will still do nothing.

If both `UNI_FORCE_ASSERT` and `UNI_DISABLE_ASSERTS` are defined,
`UNI_FORCE_ASSERTS` will be ignored.

## Additional macros

### Condition checks

Single-line checks are useful even in general code. These macros don't use
`UNI_ASSERT` and they do their action if `condition` **is** `true`.

#### UNI_THROW_IF

`UNI_THROW_IF(condition[, exception_type], message)`

See `UNI_ENSURE_THROW`.

#### UNI_RETURN_IF

`UNI_RETURN_IF(expr[, return_code])`

See `UNI_ENSURE_RETURN`.

### General macros

#### UNI_UNUSED

You can suppress warnings for unused variables with the help of `UNI_UNUSED`
macro:

    void func(int variable)
    {
        UNI_UNUSED(variable);
    }

Of course, `int /*variable*/` works on any known compiler, but variable can be
used (or not used) based on defined macros and `UNI_UNUSED` is a common case
solution.

#### UNI_FUNCTION

See `UNI_FUNCTION` in "Assumption checks" section.
