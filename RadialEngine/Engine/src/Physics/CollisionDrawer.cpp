#include "CollisionDrawer.h"

CollisionDrawer::CollisionDrawer() {
}

CollisionDrawer::~CollisionDrawer() {
}

void CollisionDrawer::DrawBox(const b2Vec2& position, float width, float height, const b2Color& color) {
    // Drawing a box with the specified dimensions
    b2Vec2 vertices[4];
    vertices[0] = position;
    vertices[1] = position + b2Vec2(width, 0);
    vertices[2] = position + b2Vec2(width, height);
    vertices[3] = position + b2Vec2(0, height);

    // Draw the box
    DrawSolidPolygon(vertices, 4, color);
}

void CollisionDrawer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{

}

void CollisionDrawer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) 
{
    // Draw the outline of the polygon with the specified color
    for (int32 i = 0; i < vertexCount - 1; ++i) {
        DrawSegment(vertices[i], vertices[i + 1], color);
    }

    // Connect the last and first vertices to complete the loop
    DrawSegment(vertices[vertexCount - 1], vertices[0], color);
}

//Need to draw using a graphics library, not worth for sdl since opengl needs to be implemented