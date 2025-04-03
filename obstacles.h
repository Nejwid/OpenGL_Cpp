#pragma once

class Player;

class Obstacle
{
private:
	float gap;
	float height;
	float speed;
	float xpos1, xpos2;
	unsigned int texture;
public:
	Obstacle(float pos);
	void Loss(bool &loss, Player& player);
	void RenderObstacle();
	void NextObstacleHeight();
	void Refresh();
};

