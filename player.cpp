#include "player.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include <cmath>
#include "zmienne.h"

using namespace::std;

Player* Player::instance = nullptr; 

Player& Player::getInstance() {
	if (instance == nullptr) {
		instance = new Player();
	}
	return *instance;
}

Player::Player() : xPos(-0.4f), yPos(0.0f), velocity(0.00013f) {}

void Player::MoveUp(){	
	yPos += velocity;
}

void Player::MoveDown(){
	yPos -= velocity;
}

void Player::Render()
{
	const float PI = 3.14159265f;

	 
	glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < 100; i++) {
			float theta = 2.0f * PI * float(i) / float(100);
			float dx = 0.05f * cosf(theta);
			float dy = 0.05f * sinf(theta);
			glVertex2f(xPos + dx, yPos + dy);
		}
		glEnd();
	
}

void Player::SetYpos(float ypos) {
	this->yPos = ypos;
}

float Player::GetXpos() const {
	return this->xPos;
}

float Player::GetYpos() const {
	return this->yPos;
}

void Player::Loss() {
	velocity = 0.00040f;
	if (this->yPos < -0.95f) {
		gameEnding = true;
	}
}

void Player::LoadBackground()
{
	int w, h, channel;
	unsigned char* data = stbi_load("t³o.png", &w, &h, &channel, 0);
	if (!data) { cout << "brak\n" << endl; }
	else { cout << w << h << channel << endl; }
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Player::DrawBackground()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D); //najwazniejszy fragment
	glEnable(GL_TEXTURE_BINDING_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex2f(1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}