#pragma once
#include <GL/glew.h>
#include <GL/GLU.h>
#include <GLFW/\glfw3.h>
#include "stb_image.h"
#include <string>
#include <iostream>
#include <vector>
#include "zmienne.h"

using namespace::std;

class sceneria
{
public:
	float X1, X2, Y1, Y2, Z1, Z2;
	sceneria(float x1, float x2, float y1, float y2, float z1, float z2): X1(x1), X2(x2), Y1(y1), Y2(y2), Z1(z1), Z2(z2) {}
	unsigned int indeks_polo¿enia;
	unsigned int tekstura[5];
	void load_scene(string nazwa, string polozenie);
	void bind_scene(string polozenie);
	void bind_plain_scene();
};

