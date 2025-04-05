#pragma once
#include <string>
using namespace::std;

class Player;

class Obstacle{
private:
	float distance;
	float X1;
	float Z1;
	float Y1;

	float Y2;
	float X2;
	float Z2;

	int flaga_oponent;
	int indeks_polo¿enia;
	unsigned int tekstura[6];
	unsigned int mno¿nik_wyniku;
public:
	Obstacle(float x, float distance);

	void MoveObstacle(float speed);
	void RenderObstacle();
	void CheckCollision(Player& player);
	void LoadTextures(string nazwa, string polozenie);
	void BindTextures(string polozenie);
};

