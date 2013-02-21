# Find pcore Library
# Output variables
# PCORE_LIBRARY and PCORE_INCLUDE_DIR
find_library (PCORE_LIBRARY pcore)
set (LIBS ${LIBS} ${PCORE_LIBRARY})
find_path (PCORE_INCLUDE_DIR pcore/ByteArray.h)
include_directories (${PCORE_INCLUDE_DIR})

message (STATUS "PCORE lib = ${PCORE_LIBRARY} , include dir ${PCORE_INCLUDE_DIR}")

if (NOT PCORE_INCLUDE_DIR_NOTFOUND AND NOT PCORE_LIBRARY_NOTFOUND)
	set (PCORE_FOUND)
endif()

