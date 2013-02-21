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

