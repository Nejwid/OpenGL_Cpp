#pragma once
#include <GL/glew.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "zmienne.h"
#include <algorithm>

class tiniest_obj_loader
{
public:
	struct Vertex {
		float x, y, z;
	};
	struct Normal {
		float x, y, z;
	};
	struct FaceVertex {
		int vertexIndex, normalIndex;
	};
	void load_obj(const std::string& filename);
	void render_obj();
	void render_obj_buffers();
	std::vector<Vertex> v;
	std::vector<Normal> vn;
	std::vector<std::vector<FaceVertex>> f_v;
	std::vector<int>wierzcho³ki;
	std::vector<Vertex>wierzcho³ki_bufor;
	GLuint wierzcho³ki_powtarzalne;
	GLuint vbo;
	GLuint ebo;
	void test_render();
};

#pragma once
