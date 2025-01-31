#include "obstacles.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "zmienne.h"

using namespace::std;

void obstacles::hejt()
{
	if (x == 1.0f || x==1.75f || x==2.5f) {
		int random = rand() % 81 - 10;
		height = random * 0.01f;
	}
}
	
void obstacles::update()
{
	x = x - speed;
	x2 = x2 - speed;
	if (x < -1.199999999999f)
	{
		x = 1.0f;
		x2 = 1.2f;
		wynik = wynik + 1;
	}
}

void obstacles::draw()
{
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.4f, 0.0f);
	glVertex2f(x, 1.0f);
	glVertex2f(x2, 1.0f);
	glVertex2f(x2, height);
	glVertex2f(x, height);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.4f, 0.0f);
	glVertex2f(x, -1.0f);
	glVertex2f(x2, -1.0f);
	glVertex2f(x2, height-gap);
	glVertex2f(x, height-gap);
	glEnd();
}

void obstacles::wczytaj_t³o()
{
	int w, h, channel;
	unsigned char* data = stbi_load("t³o.png", &w, &h, &channel, 0);
	if (!data) { cout << "brak\n" << endl; }
	else { cout << w << h << channel << endl; }
	glGenTextures(1, &tekstura);
	glBindTexture(GL_TEXTURE_2D, tekstura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void obstacles::t³o()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D); //najwazniejszy fragment
	glEnable(GL_TEXTURE_BINDING_2D);
	glBindTexture(GL_TEXTURE_2D, tekstura);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


