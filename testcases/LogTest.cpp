#include <gtest/gtest.h>
#include <pcore/Log.h>

TEST(LogTest, compileTest) {
	logi ("Hello World");
	logi ("Hello World", "How");
	logi ("Hello World", "How", "Are");
	logi ("Hello World", "How", "Are","You");
	logi ("Hello World", "How", "Are","You", "Now");
	logi ("Hello World", "How", "Are","You", "Now", "?");
}
