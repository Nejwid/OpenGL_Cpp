#pragma once
class player
{
public:
	float x = -0.4f;
	float y = 0.0f;
	float v = 0.00013f;
	void up();
	void draw(float cx, float cy, float r, int num_segments);
	void update();
};

