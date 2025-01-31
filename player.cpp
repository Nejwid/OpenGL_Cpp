#include "player.h"
#include <GLFW/glfw3.h>
#include <cmath>


void player::up()
{	
		y = y + v;
}

void player::draw(float cx, float cy, float r, int num_segments)
{
	const float PI = 3.14159265f;

	 
	glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < num_segments; i++) {
			float theta = 2.0f * PI * float(i) / float(num_segments);
			float x = r * cosf(theta);
			float y = r * sinf(theta);
			glVertex2f(x + cx, y + cy);
		}
		glEnd();
	
}

