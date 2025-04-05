#include "obiekt.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include "gracz.h"
#include "zmienne.h"

using namespace::std;

Object::Object(float x, float distance, int typ) : X1(x), distance(distance), objType(typ), placementIndex(INT_MIN) {
    X2 = X1 + 0.2f;
    Y1 = -1.f;
    Y2 = Y1 + 0.8f;
    Z1 = -1.f + distance;
    Z2 = Z1 + 0.2f;
    objFlag = 0;
    thisScore = 0;
}

void Object::rysuj(){
    if (objFlag != 1){
        glPushMatrix();

        //if (typ_obiektu == 1)
           // glColor3f(0.5f, 0.5f, 0.5f);
        //else if (typ_obiektu == 2)
            glColor3f(0.f, 0.5f, 0.5f);

        glBegin(GL_QUADS);

        glVertex3f(X1, Y1, Z1);
        glVertex3f(X2, Y1, Z1);
        glVertex3f(X2, Y2, Z1);
        glVertex3f(X1, Y2, Z1);
        //
        glVertex3f(X2, Y1, Z2);
        glVertex3f(X1, Y1, Z2);
        glVertex3f(X1, Y2, Z2);
        glVertex3f(X2, Y2, Z2);
        //
        glVertex3f(X1, Y1, Z2);
        glVertex3f(X1, Y1, Z1);
        glVertex3f(X1, Y2, Z1);
        glVertex3f(X1, Y2, Z2);
        //
        glVertex3f(X2, Y1, Z1);
        glVertex3f(X2, Y1, Z2);
        glVertex3f(X2, Y2, Z2);
        glVertex3f(X2, Y2, Z1);
        //
        glVertex3f(X1, Y2, Z1);
        glVertex3f(X2, Y2, Z1);
        glVertex3f(X2, Y2, Z2);
        glVertex3f(X1, Y2, Z2);
        //
        glVertex3f(X1, Y1, Z2);
        glVertex3f(X2, Y1, Z2);
        glVertex3f(X2, Y1, Z1);
        glVertex3f(X1, Y1, Z1);


        glEnd();
        glPopMatrix();
    }
}

void Object::kolizja(Player& player){
    AABB pojazd = { player.getPlayer_x2(), player.getPlayer_y2(), player.getPlayer_z2(), player.getPlayer_x1(), player.getPlayer_y1(), player.getPlayer_z1() };

    AABB przeszkoda = { X1, Y1, Z1, X2, Y2, Z2 };

    if (collision(pojazd, przeszkoda)){
        objFlag = 1;
        if (objType == 1)
            thisScore = 10;
        else if (objType == 2)
            thisScore = 1;
        else if (objType == 3)
            thisScore = 2;
        else if (objType == 4)
            thisScore = 3;
        else if (objType == 5)
            thisScore = 4;
    }
}

void Object::ruch(float speed){
    Z1 = Z1 - speed;
    Z2 = Z2 - speed;
}

void Object::load(string nazwa, string polozenie){
    int w, h, channel;
    unsigned char* data = stbi_load(nazwa.c_str(), &w, &h, &channel, 0);
    if (!data) { std::cout << "brak\n" << std::endl; }
    GLenum format;
    if (data) {
        if (channel == 1)
            format = GL_RED;
        else if (channel == 3)
            format = GL_RGB;
        else if (channel == 4)
            format = GL_RGBA;
    }


    if (polozenie == "przód") placementIndex = 0;
    if (polozenie == "prawo") placementIndex = 1;
    if (polozenie == "ty³") placementIndex = 2;
    if (polozenie == "lewo") placementIndex = 3;
    if (polozenie == "góra") placementIndex = 4;
    if (polozenie == "dó³") placementIndex = 5;


    glGenTextures(1, &texture[placementIndex]);
    glBindTexture(GL_TEXTURE_2D, texture[placementIndex]);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Object::bind(string polozenie){
    if (objFlag != 1) {
        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);
        glEnable(GL_TEXTURE_2D); //najwazniejszy fragment

        if (polozenie == "przód"){
            glEnable(GL_TEXTURE_BINDING_2D);
            glBindTexture(GL_TEXTURE_2D, texture[0]);
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y1, Z1);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(X2, Y1, Z1);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y2, Z1);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y2, Z1);
            glEnd();
        }
        if (polozenie == "prawo"){
            glEnable(GL_TEXTURE_BINDING_2D);
            glBindTexture(GL_TEXTURE_2D, texture[1]);
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y1, Z1);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(X1, Y1, Z2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(X1, Y2, Z2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y2, Z1);
            glEnd();
        }
        if (polozenie == "ty³"){
            glEnable(GL_TEXTURE_BINDING_2D);
            glBindTexture(GL_TEXTURE_2D, texture[2]);
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(X2, Y1, Z2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(X1, Y1, Z2);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(X1, Y2, Z2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(X2, Y2, Z2);
            glEnd();
        }
        if (polozenie == "lewo"){
            glEnable(GL_TEXTURE_BINDING_2D);
            glBindTexture(GL_TEXTURE_2D, texture[3]);
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(X2, Y1, Z2);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(X2, Y1, Z1);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y2, Z1);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(X2, Y2, Z2);
            glEnd();
        }
        if (polozenie == "góra"){
            glEnable(GL_TEXTURE_BINDING_2D);
            glBindTexture(GL_TEXTURE_2D, texture[4]);
            glBegin(GL_QUADS);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y2, Z1);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(X2, Y2, Z1);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y2, Z2);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y2, Z2);
            glEnd();
        }
        if (polozenie == "dó³"){
            glEnable(GL_TEXTURE_BINDING_2D);
            glBindTexture(GL_TEXTURE_2D, texture[5]);
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
}

int Object::GetType() const {
    return this->objType;
}

float Object::GetZpos() const {
    return this->Z1;
}

bool Object::operator<(const Object& other) const {
    return this->GetZpos() < other.GetZpos();
}

