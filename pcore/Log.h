#pragma once

#include <ostream>

namespace pc {

// Different log levels
enum LogLevel { LL_DEBUG, LL_INFO, LL_NOTICE, LL_WARNING, LL_ERROR, LL_COUNT };

/// Returns the logstream for a given file, line and log level
std::ostream & logStreamPreformat (const char * file, int line, LogLevel level);

/// Executes a given Log
void execLog (LogLevel logLevel, std::ostream&);

template <class A>
void log (const char * file, int line, LogLevel level, const A&a) {
	execLog (level, logStreamPreformat (file, line, level) << a);
}
template <class A, class B>
void log (const char * file, int line, LogLevel level, const A&a, const B&b) {
	execLog (level, logStreamPreformat (file, line, level) << a << " " << b);
}
template <class A, class B, class C>
void log (const char * file, int line, LogLevel level, const A&a, const B&b, const C&c) {
	execLog (level, logStreamPreformat (file, line, level) << a << " " << b << " " << c);
}
template <class A, class B, class C, class D>
void log (const char * file, int line, LogLevel level, const A&a, const B&b, const C&c, const D&d) {
	execLog (level, logStreamPreformat (file, line, level) << a << " " << b << " " << c  << " " << d);
}
template <class A, class B, class C, class D, class E>
void log (const char * file, int line, LogLevel level, const A&a, const B&b, const C&c, const D&d, const E&e) {
	execLog (level, logStreamPreformat (file, line, level) << a << " " << b << " " << c  << " " << d << " " << e);
}
template <class A, class B, class C, class D, class E, class F>
void log (const char * file, int line, LogLevel level, const A&a, const B&b, const C&c, const D&d, const E&e, const F&f) {
	execLog (level, logStreamPreformat (file, line, level) << a << " " << b << " " << c  << " " << d << " " << e << " " << f);
}

}

// Variadic macros, Part of C99 and Supported by GCC and VS >= 2008
#define logd(...) ::pc::log (__FILE__, __LINE__, ::pc::LL_DEBUG, __VA_ARGS__)
#define logi(...) ::pc::log (__FILE__, __LINE__, ::pc::LL_INFO, __VA_ARGS__)
#define logn(...) ::pc::log (__FILE__, __LINE__, ::pc::LL_NOTICE, __VA_ARGS__)
#define logw(...) ::pc::log (__FILE__, __LINE__, ::pc::LL_WARNING, __VA_ARGS__)
#define loge(...) ::pc::log (__FILE__, __LINE__, ::pc::LL_ERROR, __VA_ARGS__)

// Provide your own loglevel log_customlevel --> log_customlevel (loglevel, args)
#define log_customlevel(...)::pc::log (__FILE__, __LINE__, __VA_ARGS__)


