#pragma once
#include <ostream>
#include <math.h>
#include <algorithm>

/**
 * @file
 * Some easy to use 2D geometry primitives.
 *
 * If Box2D math ("Box2D/Common/b2Math.h") is included before this file,
 * some conversion routines will also be inserted.
 */

namespace pc {

template <class T>
struct Vec2 {
	Vec2 () : x(0), y(0) {}
	Vec2 (T _x, T _y) : x(_x), y(_y) {}

	Vec2<T> scaled (const Vec2<T> & other) {
		return Vec2<T> (x * other.x, y * other.y);
	}

#ifdef B2_MATH_H
	/** Conversion to Box2D vector. */
	b2Vec2 toB2Vec () const {
		return b2Vec2(x,y);
	}

	/** Conversion from Box2D vector. */
	static Vec2<T> fromB2Vec (const b2Vec2 & vec) {
		return Vec2<T> (vec.x, vec.y);
	}

#endif

	/** Returns length. */
	T length() const {
		return sqrt (x * x + y * y);
	}

	/** To float conversion. */
	Vec2<float> toVec2f () const {
		return Vec2<float> (x,y);
	}

	/** Negation. */
	Vec2<T> negation () const {
		return Vec2<T> (0 - x, 0 - y);
	}

	/** Normalization. */
	Vec2<T> normalization() const {
		T l = length();
		return Vec2<T> (x / l, y / l);
	}

	/** += operation. */
	Vec2<T>& operator+= (const Vec2<T>& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	/** reset to 0,0.*/
	void reset() {
		x = 0;
		y = 0;
	}

	/** is null check. */
	bool isNull() const {
		return x == 0 && y == 0;
	}

	T x,y; ///< Components
};

template <class T>
inline bool operator== (const Vec2<T>& a, const Vec2<T> & b) {
	return a.x == b.x && a.y == b.y;
}

template <class T>
inline Vec2<T> operator+ (const Vec2<T>& a, const Vec2<T> & b) {
	return Vec2<T> (a.x + b.x, a.y + b.y);
}

template <class T>
inline Vec2<T> operator- (const Vec2<T>&a, const Vec2<T> & b) {
	return Vec2<T> (a.x - b.x, a.y - b.y);
}
// Scalar multiplication
template <class T>
inline Vec2<T> operator* (const Vec2<T>&a, const T & b) {
	return Vec2<T> (a.x * b, a.y * b);
}
template <class T>
inline Vec2<T> operator/ (const Vec2<T>&a, const T & b) {
	return Vec2<T> (a.x / b, a.y / b);
}
template <class T>
inline Vec2<T> operator* (const T&a, const Vec2<T>&b) {
	return Vec2<T> (a * b.x, a*b.y);
}
template <class T>
inline Vec2<T> min (const Vec2<T> & a, const Vec2<T> & b) {
	return Vec2<T> (std::min(a.x, b.x), std::min (a.y, b.y));
}

template <class T>
inline Vec2<T> max (const Vec2<T> & a, const Vec2<T> & b) {
	return Vec2<T> (std::max(a.x, b.x), std::max (a.y, b.y));
}

template <class T>
inline T dot (const Vec2<T> & a, const Vec2<T> & b) {
	return (a.x * b.x + a.y * b.y);
}


typedef Vec2<int> Vec2i;
typedef Vec2<int> Point2i;
typedef Vec2<float> Vec2f;
typedef Vec2<float> Point2f;
// TODO: Differ between Points and Vectors!

inline Point2f toPoint2f (const Point2i & in) {
	return Point2f (in.x, in.y);
}

template <class T>
struct AABB2 {
	AABB2 () : empty (true) {}
	AABB2 (const Vec2<T> & tl, const Vec2<T> & br) {
		this->tl = tl;
		this->br = br;
		empty = false;
	}

#ifdef B2_MATH_H
	static AABB2<float> fromB2 (const b2AABB & in) {
		AABB2<float> result;
		result.tl = Vec2<float>::fromB2Vec(in.lowerBound);
		result.br = Vec2<float>::fromB2Vec(in.upperBound);
		result.empty = false;
		return result;
	}
#endif

	static AABB2<T> fromRect (const Vec2<T> & tl, const Vec2<T> & size) {
		AABB2<T> result;
		result.tl = tl;
		result.br = tl + size;
		result.empty = false;
		return result;
	}

	/** Add another AABB2 to this AABB2. */
	void add (const AABB2<T> & other) {
		if (empty) {
			tl = other.tl;
			br = other.br;
			empty = other.empty;
		} else {
			tl = min (tl, other.tl);
			br = max (br, other.br);
		}
	}

	/** Add a point to this AABB2. */
	void add (const Vec2<T> & point) {
		if (empty) {
			tl = point;
			br = point;
		} else {
			tl = min (tl, point);
			br = max (br, point);
		}
		empty = false;
	}

	/** Returns true if the given point is contained. */
	bool contains (const Vec2<T> & point) const {
		return point.x >= tl.x && point.x < br.x
				&& point.y >= tl.y && point.y < br.y;
	}

	/** Contains the point or touches it (only valid for integer accurate ones)*/
	bool containsOrTouch (const Vec2<T> & point) const {
		return (point.x + 1) >= tl.x && (point.x - 1) <= br.x
				&& (point.y + 1) >= tl.y && (point.y - 1) <= br.y;
	}

	/** Returns true if this AABB intersects with another one. */
	bool intersect (const AABB2<T> & other) const {
		return
		  contains (other.tl) ||
		  contains (other.br) ||
		  other.contains (tl);
	}

	/** Intersects or touches another AABB2 (only valid for integer accurate ones).*/
	bool intersectOrTouch (const AABB2<T> & other) const {
		return
		  containsOrTouch (other.tl) ||
		  containsOrTouch (other.br) ||
		  other.containsOrTouch (tl);
	}

	/** Move this AABB2 with a given distance. */
	AABB2<T> moved (const Vec2<T> & distance) const {
		if (empty) {
			return AABB2<T>();
		} else {
			return AABB2<T> (tl + distance, br + distance);
		}
	}

#ifdef B2_MATH_H
	b2AABB tob2AABB () const {
		b2AABB result;
		result.lowerBound = tl.toB2Vec();
		result.upperBound = br.toB2Vec();
		return result;
	}
#endif

	/** Returns width. */
	T width () const {
		return (br.x - tl.x);
	}

	/** Returns height .*/
	T height () const {
		return (br.y - tl.y);
	}

	/** Returns center. */
	Vec2<T> center () const {
		return Vec2<T> (tl.x + width() / 2, tl.y + height() / 2);
	}

	/** top left corner. */
	Vec2<T> tl;
	/** bottom right corner. */
	Vec2<T> br;
	/** Is empty. */
	bool empty;
};
typedef AABB2<int> AABB2i;
typedef AABB2<float> AABB2f;

template <class T>
std::ostream & operator<< (std::ostream & os, const Vec2<T> & vec) {
	return os << vec.x << "," << vec.y;
}

template <class T>
std::ostream & operator<< (std::ostream & os, const AABB2<T> & aabb) {
	return os << "[(" << aabb.tl << "),(" <<  aabb.br << ")]";
}


}
