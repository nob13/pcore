cmake_minimum_required (VERSION 2.6)
project (libpcore)

# Library
file (GLOB_RECURSE src_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} pcore/*.cpp)
file (GLOB_RECURSE header_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} pcore/*.h)
include_directories (${CMAKE_SOURCE_DIR})
add_library (pcore  ${src_files} ${header_files})
install (TARGETS pcore ARCHIVE DESTINATION lib LIBRARY DESTINATION lib)
install (DIRECTORY pcore DESTINATION include FILES_MATCHING PATTERN "*.h" PATTERN "pcore/impl*" EXCLUDE)
install (FILES FindPCORE.cmake DESTINATION share/cmake/Modules)

# Test App
add_executable (test test/main.cpp)
target_link_libraries (test pcore)

# Testcases
find_package (GTest)
if (GTEST_FOUND)
	file (GLOB_RECURSE test_src_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} testcases/*.cpp)
	file (GLOB_RECURSE test_header_files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} testcases/*.h)
	add_executable (testcases ${test_src_files} ${test_header_files})	
	target_link_libraries (testcases pcore ${GTEST_BOTH_LIBRARIES})
else()
	message (STATUS "No google test found, no testcases")
endif()
