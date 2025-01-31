#pragma once

class obstacles
{
public:
	float gap = 0.6f;
	float height;
	float speed = 0.00008f;
	unsigned int tekstura;
	obstacles(float y) :x(y) {
		x2 = x + 0.2f;
	};
	float x;
	float x2;
	void draw();
	void hejt();
	void update();
	void wczytaj_t³o();
	void t³o();
};

