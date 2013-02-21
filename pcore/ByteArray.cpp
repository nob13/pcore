#include "ByteArray.h"
#include <assert.h>
#include <string.h>

namespace pc {

bool ByteArray::printable () const {
	for (const_iterator i = begin(); i != end(); i++){
		unsigned char c = (unsigned char) *i;
		if (c == '\t' || c == '\n' || c == '\r') continue; // also displayable
		if (c == 0x0 && (i+1) == end()) continue; // one terminating is allowed
		if (c < 0x20) return false;
		
	}
	return true;
}

void ByteArray::l_truncate (size_t pos) {
	size_t before = size();
	size_t after  = before - pos;
	assert (pos <= before);

	if (pos == before) { clear (); return; }

	char * dst = &(*begin());
	const char * src = dst + pos;

	::memmove (dst, src, after);
	resize (after);
}

/// Output operator for ByteArray
std::ostream & operator<< (std::ostream & stream, const ByteArray & array) {
	if (!array.printable()){
		return stream << "Bytearray (nonprintable, size=" << array.size() << ")" << std::endl;		
	}
	
	for (ByteArray::const_iterator i = array.begin(); i != array.end(); i++){
		stream << *i;
	}
	return stream;
}

}
