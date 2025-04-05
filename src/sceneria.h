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

class Scenery{
private:
	float X1, X2, Y1, Y2, Z1, Z2;
	unsigned int placementIndex;
	unsigned int texture[5];
public:
	Scenery(float x1, float x2, float y1, float y2, float z1, float z2): X1(x1), X2(x2), Y1(y1), Y2(y2), Z1(z1), Z2(z2) {}
	void LoadScene(string nazwa, string polozenie);
	void BindScene(string polozenie);
	void BindPlainScene();
};

