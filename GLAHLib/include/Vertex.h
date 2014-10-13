#pragma once

#include "Vector.h"

//declare our vertex structure
struct Vertex
{
	Vertex(Vector2 pos, Vector4 colour_)
	{
		colour = colour_;
		position.x = pos.x;
		position.y = pos.y;
		position.z = 0.0f;
		position.w = 1.0f;
	}

	Vertex(Vector4 pos_, Vector4 colour_)
	{
		colour = colour_;
		position = pos_;
	}

	Vertex()
	{
		position.x = 0.0f;
		position.y = 0.0f;
		position.z = 0.0f;
		position.w = 0.0f;
	}

	void SetPosition(Vector2 vec)
	{
		position.x = vec.x;
		position.y = vec.y;
	}

	void SetColour(float r_, float g_, float b_, float a_ = 1.0f)
	{
		colour.x = r_;
		colour.y = g_;
		colour.z = b_;
		colour.w = a_;
	}

	Vector4 position;
	Vector4 colour;
	Vector2 textureCoordinate;
};
