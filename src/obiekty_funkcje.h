#pragma once
#include <set>
#include <random>
#include <memory>
#include <vector>


using namespace::std;

class Player;
class Object;
class Scenery;


// TWORZYMY OBIEKTY

class ObjGenerator {
private:
    vector<Scenery>scene;
    set<unique_ptr<Object>> objects;
    float objFlag;
    static ObjGenerator* instance;
    ObjGenerator();
    int RandomObjPlacement();
    int RandomObjType(int min, int max);
    void ObjFlag(float speed);
    void CreateObject();
    void DeleteObject();
    void ObjectsMovement(float speed, Player& player);
    void BindImages();
    void RenderAll();
public:
    ObjGenerator(const ObjGenerator&) = delete;
    ObjGenerator& operator=(const ObjGenerator&) = delete;
    static ObjGenerator& getInstance();   
    void obiekty_akcja(float speed, Player& player, int &wynik);
};