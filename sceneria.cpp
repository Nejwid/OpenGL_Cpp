#include "sceneria.h"

void sceneria::load_scene(string nazwa, string polozenie)
{
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

    if (polozenie == "t³o") indeks_polo¿enia = 0;
    else if (polozenie == "prawo") indeks_polo¿enia = 1;
    else if (polozenie == "lewo") indeks_polo¿enia = 2;
    else if (polozenie == "góra") indeks_polo¿enia = 3;
    else if (polozenie == "dó³") indeks_polo¿enia = 4;

    glGenTextures(1, &tekstura[indeks_polo¿enia]);
    glBindTexture(GL_TEXTURE_2D, tekstura[indeks_polo¿enia]);
    glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void sceneria::bind_scene(string polozenie)
{
    glPushMatrix();
    glDisable(GL_LIGHTING); //wazne
    glDisable(GL_BLEND); //wazne
    glEnable(GL_TEXTURE_2D); //wazne
    glEnable(GL_TEXTURE_BINDING_2D); //wazne 

    if (polozenie == "t³o") {
        glBindTexture(GL_TEXTURE_2D, tekstura[0]);
        glBegin(GL_QUADS);
        //glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X2, Y1, Z2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X1, Y1, Z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X1, Y2, Z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X2, Y2, Z2);
        glEnd();
    }
    else if (polozenie == "prawo") {
        glBindTexture(GL_TEXTURE_2D, tekstura[1]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X2, Y1, Z2);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X2, Y1, Z1);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y2, Z1);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X2, Y2, Z2);
        glEnd();
    }
    else if (polozenie == "lewo") {
        glBindTexture(GL_TEXTURE_2D, tekstura[2]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y1, Z1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X1, Y1, Z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X1, Y2, Z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X1, Y2, Z1);
    }
    else if (polozenie == "góra") {
        glBindTexture(GL_TEXTURE_2D, tekstura[3]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y2, Z1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X1, Y2, Z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y2, Z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X2, Y2, Z1);
    }
    else if (polozenie == "dó³") {
        glBindTexture(GL_TEXTURE_2D, tekstura[4]);
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(X1, Y1, Z1);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(X1, Y1, Z2);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(X2, Y1, Z2);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(X2, Y1, Z1);
    }
    glEnd();
    glPopMatrix();
}

void sceneria::bind_plain_scene()
{
    glPushMatrix();

glColor3f((116/256.f),(197/256.f),(239/256.f));
glBegin(GL_QUADS);
glVertex3f(X1, Y1, Z2); 
glVertex3f(X2, Y1, Z2);
glVertex3f(X2, Y2, Z2);
glVertex3f(X1, Y2, Z2);
glEnd();

glColor3f((156 / 256.f), (197 / 256.f), (239 / 256.f));
glBegin(GL_QUADS);
glVertex3f(X2, Y1, Z2);
glVertex3f(X2, Y1, Z1);
glVertex3f(X2, Y2, Z1);
glVertex3f(X2, Y2, Z2);
glEnd();

glBegin(GL_QUADS);
glVertex3f(X1, Y1, Z1);
glVertex3f(X1, Y1, Z2);
glVertex3f(X1, Y2, Z2);
glVertex3f(X1, Y2, Z1);
glEnd();

glColor3f((186 / 256.f), (197 / 256.f), (239 / 256.f));
glBegin(GL_QUADS);
glVertex3f(X1, Y2, Z1);
glVertex3f(X1, Y2, Z2);
glVertex3f(X2, Y2, Z2);
glVertex3f(X2, Y2, Z1);
glEnd();

glColor3f(0.5f, 0.5f, 0.5f);
glBegin(GL_QUADS);
glVertex3f(X1, Y1, Z1);
glVertex3f(X1, Y1, Z2);
glVertex3f(X2, Y1, Z2);
glVertex3f(X2, Y1, Z1);
glEnd();
glPopMatrix();
}