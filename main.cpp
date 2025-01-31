#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "obstacles.h"
#include "player.h"
#include "zmienne.h"
#include <Windows.h>

obstacles test(1.0f);
obstacles test2(1.75f);
obstacles test3(2.5f);
player gracz;


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

void pora¿ka()
{
	if (test.x2 > gracz.x && test.x < gracz.x && gracz.y > test.height - 0.05f)
	{
		loss = 1;
	}
	if (test2.x2 > gracz.x && test2.x < gracz.x && gracz.y > test2.height - 0.05f)
	{
		loss = 2;
	}
	if (test3.x2 > gracz.x && test3.x < gracz.x && gracz.y > test3.height - 0.05f)
	{
		loss = 3;
	}
	if (test.x2 > gracz.x && test.x < gracz.x && gracz.y < test.height - test.gap + 0.05f)
	{
		loss = 4;
	}
	if (test2.x2 > gracz.x && test2.x < gracz.x && gracz.y < test2.height - test2.gap + 0.05f)
	{
		loss = 5;
	}
	if (test3.x2 > gracz.x && test3.x < gracz.x && gracz.y < test3.height - test3.gap + 0.05f)
	{
		loss = 6;
	}
	if (gracz.y < -0.95f)
	{
		loss = 7;
		Sleep(500);
	}
	if (gracz.y > 0.95f)
	{
		gracz.y = 0.95f;
	}
	if (loss > 0)
	{
		test.speed = 0.0f;
		test2.speed = 0.0f;
		test3.speed = 0.0f;
		gracz.v = 0.00040;
	}
}

int main()
{

	glfwInit();
	GLFWwindow* window;
	window = glfwCreateWindow(800, 400, "Flappy Bird", NULL, NULL);
	glfwSetInputMode(window, GLFW_REPEAT, GLFW_TRUE);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);

	test.wczytaj_t³o();
		
	while (!glfwWindowShouldClose(window)&&loss!=7)
	{
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT);

		test.t³o();

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		{
			gracz.up();
		}
		else {
			gracz.y = gracz.y - gracz.v;
		}

		test.hejt();
		test.update();
		test.draw();
		test2.hejt();
		test2.update();
		test2.draw();
		test3.hejt();
		test3.update();
		test3.draw();

		gracz.draw(gracz.x, gracz.y, 0.05f, 100);
		
		pora¿ka();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	std::cout << wynik << "\n" <<loss;

	return 0;
}