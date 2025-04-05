#include <GL/glew.h>
#include <GL/GLU.h>
#include <GLFW/\glfw3.h>
#include <glut.h>
#include "zmienne.h"

std::string rozmiar_okna = "HD";
int set_window()
{
	system("cls");
	std::cout << "fullHD 1080p 60Hz (1)\nfullHD 1080p 144Hz (2)\nHD 720p 60Hz (3)\nHD 720p 144Hz (4)";
	char user_repsonse_2;
	std::cin >> user_repsonse_2;
	if (user_repsonse_2 == '1')
	{
		refresh_rate = 60;
		rozmiar_okna = "fullHD";
		return 1;
	}
	else if (user_repsonse_2 == '2')
	{
		refresh_rate = 144;
		rozmiar_okna = "fullHD";
		return 1;
	}
	else if (user_repsonse_2 == '3')
	{
		refresh_rate = 60;
		return 1;
	}
	else if (user_repsonse_2 == '4')
	{
		refresh_rate = 144;
		return 1;
	}
	return set_window();
}
int refresh_rate = 0; 
int setup()
{
	system("cls");
	std::cout << "podaj swoja czestotliwosc odswiezania ekranu: \n60 Hz (1)\n120/144 Hz (2)\naby dodatkowo zmienic rozmiar okna nacisnij (3)";
	char user_repsonse;
	std::cin >> user_repsonse;
	if (user_repsonse == '1')
	{
		refresh_rate = 60; return 1;
	}
	else if (user_repsonse == '2')
	{
		refresh_rate = 144; return 1;
	}
	else if (user_repsonse == '3')
	{
		if (set_window() == 1) return 1;
	}
	return setup();
}

float angleX = 0.f;
float angleY = 0.f;

float camera_X = 0.f;
float camera_Y = 0.f;
float camera_Z = 0.f;

float fov = 40;

void camera()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glPushMatrix();
	gluPerspective(fov, 1.0, 0.1, 100.0);

	// Ustawienie kamery
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.f, 0.f, -1.0f - camera_Z,    // Pozycja kamery (x, y, z)
		0.f, 0.f, camera_Z,    // Punkt, na który patrzy kamera (x, y, z) z dostosowaniem do obrotu pojazdu
		0.0, 1.0, 0.0);   // Wektor wskazuj¹cy górê kamery (x, y, z)
	glPopMatrix();
}
void rotate_camera() {

	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS) {
		angleY += 0.004f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_PRESS) {
		angleY -= 0.004f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS) {
		angleX -= 0.004f;
	}
	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS) {
		angleX += 0.004f;
	}
}
void set_fov()
{
	if (glfwGetKey(window, GLFW_KEY_Z) != GLFW_PRESS)
	{
		fov = 40;
	}
	else fov = 25;

}

bool collision(const AABB& box1, const AABB& box2)
{
	if (box1.maxX < box2.minX || box1.minX > box2.maxX) return false;
	if (box1.maxY < box2.minY || box1.minY > box2.maxY) return false;
	if (box1.maxZ < box2.minZ || box1.minZ > box2.maxZ) return false;
	return true;
}

int flaga = 0;
int* flaga_wsk = &flaga;

int wynik = 0;
int poprzedni_wynik = 0;

