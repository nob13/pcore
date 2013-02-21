#include "Log.h"
#include <iostream>
#include "assert.h"
#include <sstream>

#ifdef __ANDROID__
#include <android/log.h>
#endif

namespace pc {

int lineCount = 0;

static std::ostream & logStream(LogLevel level) {
	return std::cerr;
}

static const char * logLevelToString (LogLevel level) {
	switch (level) {
	case LL_DEBUG:  return  " Debug";
	case LL_INFO:   return  "  Info";
	case LL_NOTICE: return  "Notice";
	case LL_WARNING: return "  Warn";
	case LL_ERROR:  return  " Error";
	default:
		assert (!"Unknown loglevel");
		return "Unknown";
	}
}

static int countLogLevel (LogLevel level) {
	static int count[LL_COUNT] = { 0 } ;
	return count[level]++;
}

/// Strips directory from basename
static const char * myBaseName (const char * file) {
	const char * result = file;
	const char * p = result;
	while (*p != 0) {
		if (*p == '/' || *p == '\\') {
			result = p + 1;
		}
		p++;
	}
	return result;
}

#ifdef __ANDROID__
static std::ostringstream gAndroidOutputStream;

static android_LogPriority logPriority (LogLevel level) {
	switch (level) {
	case LL_DEBUG:  return ANDROID_LOG_DEBUG;
	case LL_INFO:   return ANDROID_LOG_INFO;
	case LL_NOTICE: return ANDROID_LOG_INFO;
	case LL_WARNING: return ANDROID_LOG_WARN;
	case LL_ERROR:  return ANDROID_LOG_ERROR;
	default:
		assert (!"Unknown loglevel");
		return ANDROID_LOG_UNKNOWN;
	}
}
#endif

std::ostream & logStreamPreformat (const char * file, int line, LogLevel level) {
#ifdef __ANDROID__
	return gAndroidOutputStream << countLogLevel(level) <<  " " << myBaseName(file) << ":" << line <<  " ";
#else
	return logStream (level) << "[" << logLevelToString (level) << "] " << countLogLevel(level) <<  " " << myBaseName(file) << ":" << line <<  " ";
#endif
}

void execLog (LogLevel level, std::ostream& stream) {
#ifdef __ANDROID__
	// TODO: Make 'tag' configureable
	__android_log_print (logPriority(level), "pcore", gAndroidOutputStream.str().c_str());
	gAndroidOutputStream.str("");
#else
	stream << std::endl;
#endif
}


}

