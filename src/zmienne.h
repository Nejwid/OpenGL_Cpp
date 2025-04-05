#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

extern GLFWwindow* window;

struct AABB {
    float minX, minY, minZ;
    float maxX, maxY, maxZ;
};

extern std::string rozmiar_okna;
extern int refresh_rate;
int setup();

extern float angleX;
extern float angleY;

extern float camera_X;
extern float camera_Y;
extern float camera_Z;

extern float fov;

void camera();
void rotate_camera();
void set_fov();

bool collision(const AABB& pojazd, const AABB& przeszkoda);

/*
extern float pojazd_x1;
extern float pojazd_x2;
extern float pojazd_y1;
extern float pojazd_y2;
extern float pojazd_z1;
extern float pojazd_z2;
*/

extern int flaga;
extern int* flaga_wsk;

extern int wynik;
extern int poprzedni_wynik;

//void ruch_pojazdu(float speed);



