#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "zmienne.h"
#include "gameplay.h"
#include "konto.h"

GLFWwindow* window = nullptr;

int GameWindow(){
	wynik = 0;
		if (Gameplay() == -1) return -1;
		else
		{
			system("cls");
			if (wynik > poprzedni_wynik) {
				SaveScore(wynik);
			}
			cout << "koniec gry. twoj wynik wynosi: " << wynik;
		}
		if (Exit() == 0) {
			return 0;
		}
		else if (Exit() == 1) {
			return GameWindow();
		}
}

int action(){
	system("cls");
	if (exe() == 1) {
		if (lobby() == 1) {
			if (GameWindow() == 0) {
				return 0;
			}
		}
	}
}

int main(){
	setup();
	if (action() == 0) {
		return 0;
	}
	//gameplay();
}