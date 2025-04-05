#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "obiekty_funkcje.h"
#include "zmienne.h"
#include "gracz.h"
#include "oponent.h"
#include "obiekt.h"
#include "sceneria.h"


ObjGenerator::ObjGenerator() {
	objFlag = 0.f;
}

int ObjGenerator::RandomObjPlacement() { //generujemy losowe po³o¿enie X
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(-80, 80);
    return dis(gen);
}

int ObjGenerator::RandomObjType(int min, int max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);

    return dis(gen);
}

void ObjGenerator::ObjFlag(float speed) {
    if (refresh_rate == 144)
    {
        objFlag += 2 * speed;
        if (objFlag > 0.25f) { // kontrola czêstotliwoœci spawnu obiektów
            objFlag = 0.f;
        }
    }
    else if (refresh_rate == 60)
    {
        objFlag += 2 * 2.43 * speed;
        if (objFlag > 0.25f) { // kontrola czêstotliwoœci spawnu obiektów
            objFlag = 0.f;
        }
    }
}

void ObjGenerator::CreateObject() {
    if (objFlag == 0.f) {
        unique_ptr<Object> obj = make_unique<Object>(RandomObjPlacement() * 0.01f, 10.5, RandomObjType(1, 5));
        int objType = obj->GetType();
        if (objType == 1) {
            obj->load("pepper.jpg", "przód");
        }
        else if (objType == 2) {
            obj->load("banan.jpg", "przód");
        }
        else if (objType == 3) {
            obj->load("tomato.jpg", "przód");
        }
        else if (objType == 4) {
            obj->load("lemon.jpg", "przód");
        }
        else if (objType == 5) {
            obj->load("carrot.jpg", "przód");
        }

        objects.insert(move(obj));
        objFlag = 0.1f; //setting this flag to false so only one object was generated
    }
}

void ObjGenerator::DeleteObject() { //deleting obj when it is out of range
    for (auto& it : objects) {
        if (it->GetZpos() < -0.5f) {
            objects.erase(it);
        }
    }
}

void ObjGenerator::ObjectsMovement(float speed, Player& player) {
    for (auto& it : objects) {
        it->rysuj();
        it->ruch(speed);
        it->bind("przód");
        it->kolizja(player);
    }
}

void ObjGenerator::obiekty_akcja(float speed, Player& player, int&wynik) {
    ObjFlag(0.0005f);
    CreateObject();
    ObjectsMovement(speed, player);
    DeleteObject();
}

void ObjGenerator::BindImages(){
    Scenery scenery(-1.f, 1.f, -1.f, 1.f, 0.f, 10.f);
    scene.push_back(scenery);
    scenery.LoadScene("kuzik_s³oñce.png", "t³o");
    scenery.LoadScene("niebo.png", "lewo");
    scenery.LoadScene("niebo.png", "prawo");
    scenery.LoadScene("niebo_góra.png", "góra");
    scenery.LoadScene("trawa.png", "dó³");
}

void ObjGenerator::RenderAll(){
    for (auto& iterator : scene){
        iterator.BindScene("t³o");
        iterator.BindScene("lewo");
        iterator.BindScene("prawo");
        iterator.BindScene("góra");
        iterator.BindScene("dó³");
    }
}

ObjGenerator* ObjGenerator::instance = nullptr;

ObjGenerator& ObjGenerator::getInstance() {
    if (instance == nullptr) {
        instance = new ObjGenerator();
    }
    return *instance;
}