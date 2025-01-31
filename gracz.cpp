#include "gracz.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "zmienne.h"

void gracz::ruch(float speed)
{
	if (flaga == 0)
		ruch_pojazdu(speed);
	else if (flaga == 1)
	{
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			pojazd_z1 = pojazd_z1 - 0.0005f;
			pojazd_z2 = pojazd_z2 - 0.0005f;
		}
	}
	else if (flaga == 2)
	{
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			pojazd_z1 = pojazd_z1 + 0.0005f;
			pojazd_z2 = pojazd_z2 + 0.0005f;
		}
	}
	else if (flaga == 3)
	{
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			pojazd_x1 = pojazd_x1 + 0.0001f;
			pojazd_x2 = pojazd_x2 + 0.0001f;
		}
	}
	else if (flaga == 4)
	{
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			pojazd_x1 = pojazd_x1 - 0.0001f;
			pojazd_x2 = pojazd_x2 - 0.0001f;
		}
	}
	else if (flaga == 5)
	{
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			pojazd_y1 = pojazd_y1 - 0.0001f;
			pojazd_y2 = pojazd_y2 - 0.0001f;
		}
	}
	else if (flaga == 6)
	{
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			pojazd_y1 = pojazd_y1 + 0.0001f;
			pojazd_y2 = pojazd_y2 + 0.0001f;
		}
	}

	glPushMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_QUADS);

	glVertex3f(pojazd_x2, pojazd_y2, pojazd_z1); // lewy dolny
	glVertex3f(pojazd_x1, pojazd_y2, pojazd_z1);  // prawy dolny
	glVertex3f(pojazd_x1, pojazd_y1, pojazd_z1);  // prawy górny
	glVertex3f(pojazd_x2, pojazd_y1, pojazd_z1); // lewy górny

	// Tylna œciana
	glVertex3f(pojazd_x2, pojazd_y2, pojazd_z2); // lewy dolny
	glVertex3f(pojazd_x2, pojazd_y1, pojazd_z2); // lewy górny
	glVertex3f(pojazd_x1, pojazd_y1, pojazd_z2);  // prawy górny
	glVertex3f(pojazd_x1, pojazd_y2, pojazd_z2);  // prawy dolny

	// Lewa œciana
	glVertex3f(pojazd_x2, pojazd_y2, pojazd_z2); // przednia dolna
	glVertex3f(pojazd_x2, pojazd_y2, pojazd_z1); // przednia górna
	glVertex3f(pojazd_x2, pojazd_y1, pojazd_z1); // tylna górna
	glVertex3f(pojazd_x2, pojazd_y1, pojazd_z2); // tylna dolna

	// Prawa œciana
	glVertex3f(pojazd_x1, pojazd_y2, pojazd_z2); // przednia dolna
	glVertex3f(pojazd_x1, pojazd_y1, pojazd_z2);  // przednia górna
	glVertex3f(pojazd_x1, pojazd_y1, pojazd_z1);  // tylna górna
	glVertex3f(pojazd_x1, pojazd_y2, pojazd_z1);  // tylna dolna

	// Górna œciana
	glVertex3f(pojazd_x2, pojazd_y1, pojazd_z2); // lewy przód
	glVertex3f(pojazd_x2, pojazd_y1, pojazd_z1); // lewy ty³
	glVertex3f(pojazd_x1, pojazd_y1, pojazd_z1);  // prawy ty³
	glVertex3f(pojazd_x1, pojazd_y1, pojazd_z2);  // prawy przód

	// Dolna œciana
	glVertex3f(pojazd_x2, pojazd_y2, pojazd_z2); // lewy przód
	glVertex3f(pojazd_x1, pojazd_y2, pojazd_z2);  // prawy przód
	glVertex3f(pojazd_x1, pojazd_y2, pojazd_z1);  // prawy ty³
	glVertex3f(pojazd_x2, pojazd_y2, pojazd_z1); // lewy ty³ 

	glEnd();
	glPopMatrix();

}