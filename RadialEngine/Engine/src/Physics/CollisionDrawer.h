#pragma once
#include "box2d/b2_draw.h"


class CollisionDrawer : public b2Draw
{
	public:
	CollisionDrawer();
	~CollisionDrawer();

	void DrawBox(const b2Vec2& position, float width, float height, const b2Color& color);
	void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
	void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override;
};

