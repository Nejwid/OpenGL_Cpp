#include "stb_image.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "obstacles.h"
#include "player.h"
#include "zmienne.h"
#include <vector>
#include <memory>



void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_X && action == GLFW_RELEASE) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}


int main(){

	Player& gracz = Player::getInstance();
	std::vector<std::unique_ptr<Obstacle>> obstacles;
	obstacles.emplace_back(std::make_unique<Obstacle>(1.0f));
	obstacles.emplace_back(std::make_unique<Obstacle>(1.75f));
	obstacles.emplace_back(std::make_unique<Obstacle>(2.5f));

	glfwInit();
	GLFWwindow* window;
	window = glfwCreateWindow(800, 400, "Flappy Bird", NULL, NULL);
	glfwSetInputMode(window, GLFW_REPEAT, GLFW_TRUE);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);

	gracz.LoadBackground();
		
	while (!glfwWindowShouldClose(window)&&!gameEnding){

		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT);

		gracz.DrawBackground();

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
			gracz.MoveUp();
		} else {
			gracz.MoveDown();
		}

		for (auto& it : obstacles) {
			it->NextObstacleHeight();
			it->Refresh();
			it->RenderObstacle();
		}

		gracz.Render();
		
		for (auto& it : obstacles) {
			it->Loss(loss, gracz);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	std::cout << "wynik: " << wynik << std::endl << loss;

	return 0;
}