#pragma once
#include "obiekty_funkcje.h"
#include "sceneria.h"
#include "tiniest_obj_loader.h"
#include "gracz.h"
#include <memory>


int Gameplay(){
    if (!glfwInit()) {
        return -1;
    }
    if (rozmiar_okna == "HD") {
        window = glfwCreateWindow(1280, 720, "fruit ninja look alike mini game", NULL, NULL);
    }
    else {
        window = glfwCreateWindow(1920, 1080, "fruit ninja look alike mini game", NULL, NULL);
    }
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cerr << "B³¹d inicjalizacji GLEW!" << std::endl;
        return -1;
    }

    Player& player = Player::getInstance();
    ObjGenerator& obj_generator = ObjGenerator::getInstance();
    Scenery scena(1.f, -1.f, -1.f, 1.f, 0.f, 10.f);
    scena.LoadScene("pod³oga.jpg","dó³");
    scena.LoadScene("mao.jpg", "lewo");
    scena.LoadScene("mao.jpg","t³o");
    scena.LoadScene("mao.jpg","prawo");
    scena.LoadScene("sufit.jpg", "góra");
    unique_ptr<tiniest_obj_loader> obiekt_3D = make_unique<tiniest_obj_loader>();
    obiekt_3D->load_obj("grizzly.obj");

    while (!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_X)!=GLFW_PRESS) {

        glfwSwapInterval(1); //synchronizes with screen refresh rate
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        camera();
        rotate_camera();
        set_fov();
        scena.BindScene("prawo");
        scena.BindScene("lewo");
        scena.BindScene("t³o");
        scena.BindScene("dó³");
        scena.BindScene("góra");
        //scena.bind_plain_scene(); 

        glPushMatrix();
        glTranslatef(-0.005f, -0.25f, 0.1f);
        glScalef(0.02f, 0.02f, 0.02f);
        glRotatef(-2*angleX, 0.f, 1.f, 0.f);
        glTranslatef(19*player.getPlayer_x1(), 0.f, 0.f);
        obiekt_3D->render_obj_buffers();
        glPopMatrix();

        if (refresh_rate == 144) {
            player.RenderPlayer(2*0.0035f);
            obj_generator.obiekty_akcja(2*0.007f, player, wynik);
        }
        else {
            player.RenderPlayer(2*2.43 * 0.0035f);
            obj_generator.obiekty_akcja(2*2.43 * 0.007f, player, wynik);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate(); 
    return 0;
}

int Exit(){
    cout << "\n\naby zagrac ponownie nacisnij 1\naby wyjsc nacisnij x\n";
    char user_response_3;
    cin >> user_response_3;
    if (user_response_3 == 'x') {
        system("cls");
        return 0;
    }
    else if (user_response_3 == '1') {
        system("cls"); return 1;
    }
    return Exit(); 
}
