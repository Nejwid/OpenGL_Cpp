#include "oponent.h"
#include "zmienne.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <string>
#include "gracz.h"

using namespace::std;

Obstacle::Obstacle(float x, float distance) : X1(x), distance(distance) {
    Z1 = -1.f + distance;
    Y1 = -1.f;
    Y2 = Y1 + 0.6f;
    X2 = X1 + 0.2f;
    Z2 = Z1 + 0.2f;

    flaga_oponent = 0;
    mno�nik_wyniku = 1;
}

void Obstacle::MoveObstacle(float speed)
{
    Z1 = Z1 - speed;
    Z2 = Z2 - speed;
   /* if (Z1 < -1.f)
    {
        Z1 = -1.f + distance;
        Z2 = -0.8f + distance;
    }*/
}

void Obstacle::RenderObstacle()
{
    glPushMatrix();

    if (flaga_oponent != 1) 
    { 

        glColor3f(1.f, 1.f, 1.f);
        glBegin(GL_QUADS);

        // Front face
        glVertex3f(X1, Y1, Z1);
        glVertex3f(X2, Y1, Z1);
        glVertex3f(X2, Y2, Z1);
        glVertex3f(X1, Y2, Z1);

        // Back face
        glVertex3f(X2, Y1, Z2);
        glVertex3f(X1, Y1, Z2);
        glVertex3f(X1, Y2, Z2);
        glVertex3f(X2, Y2, Z2);

        // Left face
        glVertex3f(X1, Y1, Z2);
        glVertex3f(X1, Y1, Z1);
        glVertex3f(X1, Y2, Z1);
        glVertex3f(X1, Y2, Z2);

        // Right face
        glVertex3f(X2, Y1, Z1);
        glVertex3f(X2, Y1, Z2);
        glVertex3f(X2, Y2, Z2);
        glVertex3f(X2, Y2, Z1);

        // Top face
        glVertex3f(X1, Y2, Z1);
        glVertex3f(X2, Y2, Z1);
        glVertex3f(X2, Y2, Z2);
        glVertex3f(X1, Y2, Z2);

        // Bottom face
        glVertex3f(X1, Y1, Z2);
        glVertex3f(X2, Y1, Z2);
        glVertex3f(X2, Y1, Z1);
        glVertex3f(X1, Y1, Z1);


        glEnd();
    }
    glPopMatrix();
}

void Obstacle::CheckCollision(Player& player) {
    AABB pojazd = { player.getPlayer_x2(), player.getPlayer_y2(), player.getPlayer_z2(), player.getPlayer_x1(), player.getPlayer_y1(), player.getPlayer_z1() };
    AABB przeszkoda = { X1, Y1, Z1, X2, Y2, Z2 };

    if (collision(pojazd, przeszkoda))
    {
        flaga_oponent = 1;
        wynik = wynik + mno�nik_wyniku;
    }
}

void Obstacle::LoadTextures(string nazwa, string polozenie)
{
    //polo�enie = polozenie;
    int w, h, channel;
    unsigned char* data = stbi_load(nazwa.c_str(), &w, &h, &channel, 0);
    if (!data) { std::cout << "brak\n" << std::endl; }

    if (polozenie == "prz�d") indeks_polo�enia = 0;
    if (polozenie == "prawo") indeks_polo�enia = 1;
    if (polozenie == "ty�") indeks_polo�enia = 2;
    if (polozenie == "lewo") indeks_polo�enia = 3;
    if (polozenie == "g�ra") indeks_polo�enia = 4;
    if (polozenie == "d�") indeks_polo�enia = 5;


    glGenTextures(1, &tekstura[indeks_polo�enia]);
    glBindTexture(GL_TEXTURE_2D, tekstura[indeks_polo�enia]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Obstacle::BindTextures(string polozenie) {

    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D); //najwazniejszy fragment

    if (polozenie == "prz�d") {
        glEnable(GL_TEXTURE_BINDING_2D);
        glBindTexture(GL_TEXTURE_2D, tekstura[0]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y1, Z1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X2, Y1, Z1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y2, Z1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y2, Z1);
        glEnd();
    }
    if (polozenie == "prawo")
    {
        glEnable(GL_TEXTURE_BINDING_2D);
        glBindTexture(GL_TEXTURE_2D, tekstura[1]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y1, Z1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X1, Y1, Z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X1, Y2, Z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y2, Z1);
        glEnd();
    }
    if (polozenie == "ty�")
    {
        glEnable(GL_TEXTURE_BINDING_2D);
        glBindTexture(GL_TEXTURE_2D, tekstura[2]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X2, Y1, Z2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X1, Y1, Z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X1, Y2, Z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X2, Y2, Z2);
        glEnd();
    }
    if (polozenie == "lewo")
    {
        glEnable(GL_TEXTURE_BINDING_2D);
        glBindTexture(GL_TEXTURE_2D, tekstura[3]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X2, Y1, Z2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X2, Y1, Z1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y2, Z1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X2, Y2, Z2);
        glEnd();
    }
    if (polozenie == "g�ra")
    {
        glEnable(GL_TEXTURE_BINDING_2D);
        glBindTexture(GL_TEXTURE_2D, tekstura[4]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y2, Z1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X2, Y2, Z1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y2, Z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y2, Z2);
        glEnd();
    }
    if (polozenie == "d�")
    {
        glEnable(GL_TEXTURE_BINDING_2D);
        glBindTexture(GL_TEXTURE_2D, tekstura[5]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y1, Z2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X2, Y1, Z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y1, Z1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y1, Z1);
        glEnd();
    }

    glDisable(GL_TEXTURE_2D);
}
