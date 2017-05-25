#pragma once

#include <type_traits>

#if defined(__GNUC__)
   #if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 5)
       #define PROMISE_HAS_NOEXCEPT
       #define NOEXCEPT noexcept
   #else
       #define NOEXCEPT throw()
   #endif
#else
   #define PROMISE_HAS_NOEXCEPT
   #define NOEXCEPT noexcept
#endif

#if defined(__GNUC__)
   #if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)
       #define PROMISE_HAS_COPY_CONSTRUCTIBLE
   #endif
#else
   #define PROMISE_HAS_COPY_CONSTRUCTIBLE
#endif

#if defined(__GNUC__)
   #if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 5)
       #define PROMISE_HAS_MAKE_EXCEPTION_PTR
   #endif
#else
   #define PROMISE_HAS_MAKE_EXCEPTION_PTR
#endif

#if defined(__GNUC__)
   #if defined(__clang__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 5)
       #define PROMISE_HAS_RANGE_BASED_FOR
   #endif
#else
   #define PROMISE_HAS_RANGE_BASED_FOR
#endif

namespace std {

#ifndef PROMISE_HAS_COPY_CONSTRUCTIBLE
template <typename T>
struct is_copy_constructible :
    std::is_constructible<T,
        typename std::add_lvalue_reference<typename std::add_const<T>::type>::type
    > {};
#endif // PROMISE_HAS_COPY_CONSTRUCTIBLE

#ifndef PROMISE_HAS_MAKE_EXCEPTION_PTR
/// Obtain an exception_ptr pointing to a copy of the supplied object.
template<typename _Ex>
exception_ptr
make_exception_ptr(_Ex __ex)
{
    try
  	{
  	    throw __ex;
  	}
    catch(...)
  	{
  	    return current_exception();
  	}
}
#endif // PROMISE_HAS_MAKE_EXCEPTION_PTR

} // namespace std
