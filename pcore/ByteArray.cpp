#include "ByteArray.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

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

#define READ_BUF_LENGTH 8192

int ByteArray::load(const char * filename) {
	FILE * f = fopen (filename, "rb");
	if (!f) return -1; // Could not open
	clear();
	char buf [READ_BUF_LENGTH];
	size_t r = 0;
	while ((r = fread(buf, 1, READ_BUF_LENGTH, f)) > 0) {
		append (buf, r);
	}
	bool isEof = feof(f);
	fclose (f);
	return isEof ? 0 : -1;
}

int ByteArray::save(const char * file) {
	FILE * f = fopen (file, "wb");
	if (!f) {
		return -1;
	}
	size_t written = fwrite(const_c_array(), size(), 1, f);
	fclose(f);
	return written == 1 ? 0 : -1;
}

}
