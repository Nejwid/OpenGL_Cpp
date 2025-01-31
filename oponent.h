#pragma once
#include <string>
using namespace::std;
class oponent
{
public:
	float distance;
	float X1;
	float Z1 = -1.f + distance;
	float Y1 = -1.f;

	float Y2 = Y1 + 0.6f;
	float X2 = X1 + 0.2f;
	float Z2 = Z1 + 0.2f;

	int flaga_oponent = 0;
	int indeks_polo¿enia;
	unsigned int tekstura[6];
	unsigned mno¿nik_wyniku=1;

	oponent(float x, float distance) : X1(x), distance(distance) {};

	void ruch(float speed);
	void rysuj();
	void kolizja();
	void load(string nazwa, string polozenie);
	void bind(string polozenie);
};

