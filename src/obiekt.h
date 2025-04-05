#pragma once
#include <string>
using namespace::std;

class Player;

class Object {
private:
	float distance;
	float X1;
	float Y1;
	float Z1;
	float X2;
	float Y2;
	float Z2;
	unsigned int objType;
	int placementIndex;
	unsigned int texture[6];
	int objFlag;
	int thisScore;

public:
	Object(float x, float distance, int typ);
	void ruch(float speed);
	void rysuj();
	void kolizja(Player& player);
	void load(string nazwa, string polozenie);
	void bind(string polozenie);
	int GetType() const;
	float GetZpos() const;
	bool operator<(const Object& other) const;
};

