#include "obstacles.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "zmienne.h"
#include "player.h"

using namespace::std;

Obstacle::Obstacle(float pos) :xpos1(pos) {
	this->xpos2 = this->xpos1 + 0.2f;
	this->speed = 0.00008f;
	this->gap = 0.6f;
}

void Obstacle::NextObstacleHeight()
{
	if (xpos1 == 1.0f || xpos1==1.75f || xpos1==2.5f) {
		int random = rand() % 81 - 10;
		height = random * 0.01f;
	}
}
	
void Obstacle::Refresh()
{
	xpos1 = xpos1 - speed;
	xpos2 = xpos2 - speed;
	if (xpos1 < -1.199999999999f)
	{
		xpos1 = 1.0f;
		xpos2 = 1.2f;
		wynik = wynik + 1;
	}
}

void Obstacle::RenderObstacle()
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.4f, 0.0f);
	glVertex2f(xpos1, 1.0f);
	glVertex2f(xpos2, 1.0f);
	glVertex2f(xpos2, height);
	glVertex2f(xpos1, height);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.4f, 0.0f);
	glVertex2f(xpos1, -1.0f);
	glVertex2f(xpos2, -1.0f);
	glVertex2f(xpos2, height-gap);
	glVertex2f(xpos1, height-gap);
	glEnd();
}

void Obstacle::Loss(bool& loss, Player& player) // should have implemented AABB collision system or similar but this game so simple I easily hardcoded whether its collision or not
{
	if (xpos2 > player.GetXpos() && xpos1 < player.GetXpos() && player.GetYpos() > height - 0.05f)
	{
		loss = true;
	}

	if (xpos2 > player.GetXpos() && xpos1 < player.GetXpos() && player.GetYpos() < height - gap + 0.05f)
	{
		loss = true;
	}

	if (player.GetYpos() < -0.95f)
	{
		loss = true;
	}
	if (player.GetYpos() > 0.95f)
	{
		player.SetYpos(0.95f);
	}
	if (loss)
	{
		this->speed = 0.0f;
		player.Loss();
	}
}

