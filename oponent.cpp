#include "oponent.h"
#include "zmienne.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include <string>

using namespace::std;

void oponent::ruch(float speed)
{
    Z1 = Z1 - speed;
    Z2 = Z2 - speed;
   /* if (Z1 < -1.f)
    {
        Z1 = -1.f + distance;
        Z2 = -0.8f + distance;
    }*/
}

void oponent::rysuj()
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

void oponent::kolizja()
{
    AABB pojazd = { pojazd_x2, pojazd_y2, pojazd_z2, pojazd_x1, pojazd_y1, pojazd_z1 };
    AABB przeszkoda = { X1, Y1, Z1, X2, Y2, Z2 };

    if (collision(pojazd, przeszkoda))
    {
        flaga_oponent = 1;
        wynik = wynik + mno¿nik_wyniku;
    }
}

void oponent::load(string nazwa, string polozenie)
{
    //polo¿enie = polozenie;
    int w, h, channel;
    unsigned char* data = stbi_load(nazwa.c_str(), &w, &h, &channel, 0);
    if (!data) { std::cout << "brak\n" << std::endl; }

    if (polozenie == "przód") indeks_polo¿enia = 0;
    if (polozenie == "prawo") indeks_polo¿enia = 1;
    if (polozenie == "ty³") indeks_polo¿enia = 2;
    if (polozenie == "lewo") indeks_polo¿enia = 3;
    if (polozenie == "góra") indeks_polo¿enia = 4;
    if (polozenie == "dó³") indeks_polo¿enia = 5;


    glGenTextures(1, &tekstura[indeks_polo¿enia]);
    glBindTexture(GL_TEXTURE_2D, tekstura[indeks_polo¿enia]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void oponent::bind(string polozenie) {

    glDisable(GL_LIGHTING);
    glDisable(GL_BLEND);
    glEnable(GL_TEXTURE_2D); //najwazniejszy fragment

    if (polozenie == "przód") {
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
    if (polozenie == "ty³")
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
    if (polozenie == "góra")
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
    if (polozenie == "dó³")
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
