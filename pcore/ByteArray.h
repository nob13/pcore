#pragma once

#include <vector>
#include <ostream>
#include <cstring>
#include <string>

namespace pc {

/// An easy to use array for generic data
class ByteArray : public std::vector<char> {
public:
	ByteArray () {}
	
	/// Constructs a byte array from given data (makes a deep copy)
	ByteArray (const char * data, size_t length) : std::vector<char> (data, data + length) {}
	
	/// Constructs a byte array from a null terminated string
	ByteArray (const char * data) : std::vector<char> (data, data + std::strlen (data)) {}
	
	/// Constructs a byte array from a std::string
	ByteArray (const std::string & s) : std::vector<char> (s.begin(), s.end()) {}
	
	/// Constructs Bytearray with specific size and already filled
	ByteArray (size_t size, char fill) : std::vector<char> (size, fill) {}

	ByteArray (const ByteArray & other) : std::vector<char> (other) {
	}
	ByteArray& operator= (const ByteArray& other) {
		std::vector<char>::operator=(other);
		return *this;
	}

#if __cplusplus >= 201103L
	/// Moving constructor
	ByteArray (const ByteArray && other) : std::vector<char> (std::move (other)){

	}
#endif

	/// Hack for C-Style array compatiblity
	const char * const_c_array () const {
		return &(*begin());
	}
	
	/// Hack for C-style array compatibility
	char * c_array () {
		return &(*begin());
	}
	
	/// determines if the string is printable (consists of characters abobe 0x20 only)
	bool printable () const;
	
	/// append another bytearray to this one, with nicer syntax
	void append (const ByteArray & other) {
		insert (end(), other.begin(), other.end());
	}

	/// append one byte
	void append (unsigned char c){
		push_back ((char) c);
	}
	
	/// append a C-Array
	void append (const char * data, size_t length){
		insert (end(), data, data + length);
	}
	
	/// append one byte
	void append (char c){
		push_back (c);
	}
	
	/// cuts the array at the given position 
	void truncate (size_t pos) { resize (pos); }
	
	/// cuts the array at position and let it be the second part
	/// position can also be interpreted as bytes (so '0' won't cut anything, 'length()' will cut them all)
	/// this is expensive
	void l_truncate (size_t pos);

	/// Load a (binary) file.
	/// Returns 0 on success
	int load(const char * filename);

	/// Load a (binary) file and returns asscociated ByteArray
	/// Only fast on C++ 0X
	static ByteArray from_file (const char * filename)  {
		ByteArray result;
		result.load(filename);
		return result;
	}

	/// Saves into a file
	/// Returns 0 on success
	int save(const char * file);
};

/// Output operator for ByteArray
std::ostream & operator<< (std::ostream & stream, const ByteArray & array);

}

