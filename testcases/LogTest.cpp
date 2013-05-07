#include <gtest/gtest.h>
#include <pcore/Log.h>

TEST(LogTest, compileTest) {
	logi ("Hello World");
	logi ("Hello World", "How");
	logi ("Hello World", "How", "Are");
	logi ("Hello World", "How", "Are","You");
	logi ("Hello World", "How", "Are","You", "Now");
	logi ("Hello World", "How", "Are","You", "Now", "?");

	pc::logSetThreadName ("main");
	logi ("With ThreadName");

}

TEST(LogTest, logLevelTest) {
	pc::logSetMinLockLevel(pc::LL_NOTICE);
	ASSERT_FALSE (pc::logIsRequested(pc::LL_DEBUG));
	ASSERT_FALSE (pc::logIsRequested(pc::LL_INFO));
	ASSERT_TRUE  (pc::logIsRequested(pc::LL_NOTICE));
	ASSERT_TRUE  (pc::logIsRequested(pc::LL_WARNING));
	pc::logSetMinLockLevel(pc::LL_INFO);
	ASSERT_TRUE (pc::logIsRequested(pc::LL_INFO));
}

