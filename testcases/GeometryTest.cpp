#include <gtest/gtest.h>
#include <pcore/Geometry.h>
using namespace pc;


TEST (GeometryTest, boundingBox){
	AABB2i box1 (Vec2i (640, 64), Vec2i (703, 94));
	AABB2i box2 (Vec2i (576,64), Vec2i (639, 94));
	ASSERT_TRUE (box1.intersect(box1));
	ASSERT_TRUE (box2.intersect(box2));
	ASSERT_FALSE(box1.intersect(box2));
	ASSERT_FALSE(box2.intersect(box1));
	ASSERT_TRUE (box1.intersectOrTouch(box2));
	ASSERT_TRUE (box2.intersectOrTouch(box1));
}

TEST (GeometryTest, constructor) {
	AABB2i box  = AABB2i::fromRect (Vec2i (100,120), Vec2i (50, 70));
	ASSERT_TRUE (!box.empty);
	ASSERT_TRUE (box.tl == Vec2i (100, 120));
	ASSERT_TRUE (box.br == Vec2i (150, 190));
}

TEST (GeometryTest, basicOps) {
	Vec2f a (1, 2);
	ASSERT_EQ (a.negation(), Vec2f (-1,-2));
	Vec2f b (3, 4);
	ASSERT_NEAR (b.length(), 5, 0.01);
}

TEST (GeometryTest, rect1) {
	Recti r (10, 20, 30, 40);
	ASSERT_EQ (r.origin.x, 10);
	ASSERT_EQ (r.origin.y, 20);
	ASSERT_EQ (r.width(), 30);
	ASSERT_EQ (r.height(), 40);

	Recti r2 (40, 20, -30, 40);
	Recti r2n = r2.normalization();
	ASSERT_EQ (r, r2n);
}

TEST (GeometryTest, vecEqualTest) {
	Vec2i a (3, 4);
	Vec2i b (3, 4);
	Vec2i c (4, 4);
	Vec2i d (3, 5);
	ASSERT_EQ (a, b);
	ASSERT_FALSE (a != b);
	ASSERT_NE (a, c);
	ASSERT_NE (a, d);
}

TEST (GeometryTest, rectEqualTest) {
	Recti a (3,4,5,6);
	Recti b (3,4,5,6);
	Recti c (3,5,5,6);
	Recti d (3,4,5,7);
	ASSERT_EQ (a,b);
	ASSERT_FALSE (a != b);
	ASSERT_NE (a,c);
	ASSERT_NE (a,d);
}
