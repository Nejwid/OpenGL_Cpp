#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "zmienne.h"
#include "gameplay.h"
#include "konto.h"

GLFWwindow* window = nullptr;

int okno_gry()
{
	wynik = 0;
		if (gameplay() == -1) return -1;
		else
		{
			system("cls");
			if (wynik > poprzedni_wynik) zapisz(wynik);
			cout << "koniec gry. twoj wynik wynosi: " << wynik;
		}
	if (exit() == 0) return 0;
	else if (exit() == 1) return okno_gry();
}

int action()
{
	system("cls");
	if (exe() == 1)
		if (lobby() == 1)
			if (okno_gry() == 0) return 0;	
}

int main()
{
	setup();
	if (action() == 0) return 0;
	//gameplay();
}