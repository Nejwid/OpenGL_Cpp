#include "gracz.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "zmienne.h"

void Player::RenderPlayer(float speed){
	if (flaga == 0)
		MovePlayer(speed);
	else if (flaga == 1){
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
			player_z1 = player_z1 - 0.0005f;
			player_z2 = player_z2 - 0.0005f;
		}
	}
	else if (flaga == 2){
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
			player_z1 = player_z1 + 0.0005f;
			player_z2 = player_z2 + 0.0005f;
		}
	}
	else if (flaga == 3){
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			player_x1 = player_x1 + 0.0001f;
			player_x2 = player_x2 + 0.0001f;
		}
	}
	else if (flaga == 4){
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
			player_x1 = player_x1 - 0.0001f;
			player_x2 = player_x2 - 0.0001f;
		}
	}
	else if (flaga == 5){
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
			player_y1 = player_y1 - 0.0001f;
			player_y2 = player_y2 - 0.0001f;
		}
	}
	else if (flaga == 6){
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
			player_y1 = player_y1 + 0.0001f;
			player_y2 = player_y2 + 0.0001f;
		}
	}

	glPushMatrix();
	glDisable(GL_BLEND);
	glDisable(GL_LIGHTING);
	glColor3f(0.6f, 0.6f, 0.6f);
	glBegin(GL_QUADS);

	glVertex3f(player_x2, player_y2, player_z1); // lewy dolny
	glVertex3f(player_x1, player_y2, player_z1);  // prawy dolny
	glVertex3f(player_x1, player_y1, player_z1);  // prawy górny
	glVertex3f(player_x2, player_y1, player_z1); // lewy górny

	// Tylna œciana
	glVertex3f(player_x2, player_y2, player_z2); // lewy dolny
	glVertex3f(player_x2, player_y1, player_z2); // lewy górny
	glVertex3f(player_x1, player_y1, player_z2);  // prawy górny
	glVertex3f(player_x1, player_y2, player_z2);  // prawy dolny

	// Lewa œciana
	glVertex3f(player_x2, player_y2, player_z2); // przednia dolna
	glVertex3f(player_x2, player_y2, player_z1); // przednia górna
	glVertex3f(player_x2, player_y1, player_z1); // tylna górna
	glVertex3f(player_x2, player_y1, player_z2); // tylna dolna

	// Prawa œciana
	glVertex3f(player_x1, player_y2, player_z2); // przednia dolna
	glVertex3f(player_x1, player_y1, player_z2);  // przednia górna
	glVertex3f(player_x1, player_y1, player_z1);  // tylna górna
	glVertex3f(player_x1, player_y2, player_z1);  // tylna dolna

	// Górna œciana
	glVertex3f(player_x2, player_y1, player_z2); // lewy przód
	glVertex3f(player_x2, player_y1, player_z1); // lewy ty³
	glVertex3f(player_x1, player_y1, player_z1);  // prawy ty³
	glVertex3f(player_x1, player_y1, player_z2);  // prawy przód

	// Dolna œciana
	glVertex3f(player_x2, player_y2, player_z2); // lewy przód
	glVertex3f(player_x1, player_y2, player_z2);  // prawy przód
	glVertex3f(player_x1, player_y2, player_z1);  // prawy ty³
	glVertex3f(player_x2, player_y2, player_z1); // lewy ty³ 

	glEnd();
	glPopMatrix();

}

void Player::MovePlayer(float speed){
	if (player_x2 > -0.9f && glfwGetKey(window, GLFW_KEY_LEFT) != GLFW_PRESS) {
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
			player_x1 = player_x1 - speed;
			player_x2 = player_x2 - speed;
		}
	}

	if (player_x1 < 0.9f && glfwGetKey(window, GLFW_KEY_RIGHT) != GLFW_PRESS){
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
			player_x1 = player_x1 + speed;
			player_x2 = player_x2 + speed;
		}
	}
}

float Player::getPlayer_x1() const {
	return player_x1;
}

float Player::getPlayer_x2() const {
	return player_x2;
}

float Player::getPlayer_y1() const {
	return player_y1;
}

float Player::getPlayer_y2() const {
	return player_y2;
}

float Player::getPlayer_z1() const {
	return player_z1;
}

float Player::getPlayer_z2() const {
	return player_z2;
}

Player* Player::instance = nullptr;

Player& Player::getInstance() {
	if (instance == nullptr) {
		instance = new Player();
	}
	return *instance;
}

Player::Player(){
	player_x1 = 0.05f;
	player_x2 = -0.05f;
	player_y1 = -0.9f;
	player_y2 = -1.f;
	player_z1 = 2.05f;
	player_z2 = 1.95f;
};
