#pragma once
#include "SQlite.h"
#include <cctype>
#include <string>
#include <Windows.h>
#include "sqlite-amalgamation-3450300/sqlite3.h"
#include <vector>

using namespace::std;
string Login;

//login/score database config
int przypisanie_rekordów(const char* login){
	sqlite3* baza_danych;
	char* error_message = nullptr;
	int rc;

	rc = sqlite3_open("baza1", &baza_danych);
	if (rc != 0) { std::cerr << sqlite3_errmsg(baza_danych); return 1; }

	const char* zapytanie = "INSERT INTO wyniki (login, wynik) VALUES (?,?);";

	sqlite3_stmt* stmt; //uchwyt na zapytanie :)
	rc = sqlite3_prepare_v2(baza_danych, zapytanie, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Błąd przygotowywania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_close(baza_danych);
		return 1;
	}
	int n = 0;
	// Wstawienie wartości do zapytania
	sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
	sqlite3_bind_int(stmt, 2, n);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "Błąd wykonania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(baza_danych);
		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(baza_danych);
	return 0;
}


//----------------------------------------------------------------// logging in
int pobierz_wynik(const char* login) {
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;
	int wynik = -1;

	// Otwieranie bazy danych
	rc = sqlite3_open("baza1", &db);
	if (rc != SQLITE_OK) {
		std::cerr << "Nie można otworzyć bazy danych: " << sqlite3_errmsg(db) << std::endl;
		return wynik;
	}

	// Przygotowanie zapytania SQL
	const char* zapytanie = "SELECT wynik FROM wyniki WHERE login = ?;";
	rc = sqlite3_prepare_v2(db, zapytanie, -1, &stmt, 0);
	if (rc != SQLITE_OK) {
		std::cerr << "Nie udało się przygotować zapytania: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return wynik;
	}

	// Bindowanie wartości login do zapytania
	sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);

	// Wykonanie zapytania
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		// Pobranie wartości wyniku
		wynik = sqlite3_column_int(stmt, 0);
	}
	else {
		std::cerr << "Nie znaleziono rekordu dla danego loginu" << std::endl;
	}

	// Zakończenie pracy z zapytaniem i zamknięcie bazy danych
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return wynik;
}
string konwersja_na_string(const char* słowo)
{
	return string(słowo);
}
int sprawdzenie_poprawności_loginu(string login)
{
	sqlite3* baza_danych;
	sqlite3_stmt* stmt;
	int rc;

	rc = sqlite3_open("baza1", &baza_danych);
	if (rc != SQLITE_OK) {
		std::cerr << "Nie można otworzyć bazy danych: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_close(baza_danych);
		return 1;
	}

	// Zapytanie SQL sprawdzające, czy istnieje dana nazwa
	const char* zapytanie = "SELECT COUNT(*) FROM uzytkownicy WHERE login = ?;";

	rc = sqlite3_prepare_v2(baza_danych, zapytanie, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Błąd przygotowywania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_close(baza_danych);
		return 1;
	}

	// Wstawienie wartości do zapytania
	sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

	// Wykonanie zapytania
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		// Pobranie wyniku zapytania (liczba rekordów)
		int liczba_rekordow = sqlite3_column_int(stmt, 0);
		// Jeśli liczba rekordów jest większa niż 0, to nazwa istnieje w bazie

		if (bool istnieje = (liczba_rekordow > 0)) {

			// Zwolnienie zasobów i zamknięcie bazy danych
			sqlite3_finalize(stmt);
			sqlite3_close(baza_danych);

			return 2;
		}
		else return 0;
	}
	else {
		std::cerr << "Błąd wykonania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(baza_danych);
		return 1;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(baza_danych);
	return 1;

}
int sprawdź_hasło(string login, string hasło)
{
	sqlite3* baza_danych;
	sqlite3_stmt* stmt;
	int rc;

	rc = sqlite3_open("baza1", &baza_danych);
	if (rc != SQLITE_OK) {
		std::cerr << "Nie można otworzyć bazy danych: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_close(baza_danych);
		return 1;
	}

	// Zapytanie SQL sprawdzające, czy istnieje dana nazwa
	const char* zapytanie = "SELECT password FROM uzytkownicy WHERE login = ?;";

	rc = sqlite3_prepare_v2(baza_danych, zapytanie, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Błąd przygotowywania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_close(baza_danych);
		return 1;
	}

	// Wstawienie wartości do zapytania
	sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

	// Wykonanie zapytania
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		const unsigned char* haslo = sqlite3_column_text(stmt, 0);
		if (string(reinterpret_cast<const char*>(haslo)) == hasło)
		{
			cout << "poprawne haslo\n";
			sqlite3_finalize(stmt);
			sqlite3_close(baza_danych);
			return 0;
		}
		else
			cout << "niepoprawne haslo ";

		sqlite3_finalize(stmt);
		sqlite3_close(baza_danych);
		return 1;
	}
	else if (rc == SQLITE_DONE) {
		std::cerr << "Nie znaleziono rekordu dla danego loginu" << std::endl;
	}
	else {
		std::cerr << "Błąd wykonania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
	}
	sqlite3_finalize(stmt);
	sqlite3_close(baza_danych);
	return 1;
}
//log in function
int zaloguj()
{
	system("cls");
	string login;
	string hasło;
	cout << "podaj login: ";
	cin >> login; Login = login;
	if (sprawdzenie_poprawności_loginu(login) == 2)
	{
		cout << "\nwpisz haslo: ";
		cin >> hasło;
		if (sprawdź_hasło(login, hasło) == 1)
		{
			return zaloguj();
		}
		else
		{
			cout << "zalogowano ";
			poprzedni_wynik = pobierz_wynik(login.c_str());
			return 1;
		}
		return 0;
	}
	else
	{
		cout << "bledny login \n";
		return zaloguj();
	}
}

//----------------------------------------------------------------// creating an account
int sprawdzenie_czy_login_istnieje(string login)
{
	sqlite3* baza_danych;
	sqlite3_stmt* stmt;
	int rc;

	rc = sqlite3_open("baza1", &baza_danych);
	if (rc != SQLITE_OK) {
		std::cerr << "Nie można otworzyć bazy danych: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_close(baza_danych);
		return 1;
	}

	// Zapytanie SQL sprawdzające, czy istnieje dana nazwa
	const char* zapytanie = "SELECT COUNT(*) FROM uzytkownicy WHERE login = ?;";

	rc = sqlite3_prepare_v2(baza_danych, zapytanie, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Błąd przygotowywania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_close(baza_danych);
		return 1;
	}

	// Wstawienie wartości do zapytania
	sqlite3_bind_text(stmt, 1, login.c_str(), -1, SQLITE_STATIC);

	// Wykonanie zapytania
	rc = sqlite3_step(stmt);
	if (rc == SQLITE_ROW) {
		// Pobranie wyniku zapytania (liczba rekordów)
		int liczba_rekordow = sqlite3_column_int(stmt, 0);
		// Jeśli liczba rekordów jest większa niż 0, to nazwa istnieje w bazie

		if (bool istnieje = (liczba_rekordow > 0)) {

			// Zwolnienie zasobów i zamknięcie bazy danych
			sqlite3_finalize(stmt);
			sqlite3_close(baza_danych);

			return 2;
		}
		else
		{
			sqlite3_finalize(stmt);
			sqlite3_close(baza_danych);
			return 0;
		}
	}
	else {
		std::cerr << "Błąd wykonania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(baza_danych);
		return 1;
	}
	return 1;
}
string ustawienie_loginu() // set login
{
	cout << "podaj nowy login od 5 do 10 znakow: ";
	string login;
	cin >> login;
	if (sprawdzenie_czy_login_istnieje(login) == 0)
	{
		if (login.length() > 4)
		{
			if (login.length() < 10) return login;
		}
	}
	return ustawienie_loginu();
}
string ustawienie_hasła() // set password
{
	cout << "podaj haslo od 5 do 10 znakow tym znak specjalny: ";
	string hasło;
	cin >> hasło;
	if (hasło.length() > 4)
	{
		if (hasło.length() < 10)
		{
			for (const auto iterator : hasło)
			{
				if (iterator == '!' || iterator == '@' || iterator == '#' || iterator == '$'
					|| iterator == '%' || iterator == '^' || iterator == '&' || iterator == '*')
					return hasło;
			}
		}
	}
	return ustawienie_hasła();
}
int zapisanie_hasła(const char* login, const char* hasło) // bind password to login
{
	sqlite3* baza_danych;
	char* error_message = nullptr;
	int rc;

	rc = sqlite3_open("baza1", &baza_danych);
	if (rc != 0) { std::cerr << sqlite3_errmsg(baza_danych); return 1; }

	const char* zapytanie = "INSERT INTO uzytkownicy (login, password) VALUES (?,?);";

	sqlite3_stmt* stmt; //uchwyt na zapytanie :)
	rc = sqlite3_prepare_v2(baza_danych, zapytanie, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Błąd przygotowywania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_close(baza_danych);
		return 1;
	}

	// Wstawienie wartości do zapytania
	sqlite3_bind_text(stmt, 1, login, -1, SQLITE_STATIC);
	sqlite3_bind_text(stmt, 2, hasło, -1, SQLITE_STATIC);

	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "Błąd wykonania zapytania: " << sqlite3_errmsg(baza_danych) << std::endl;
		sqlite3_finalize(stmt);
		sqlite3_close(baza_danych);
		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(baza_danych);

	//utworzenie korespondującej tabeli login/wynik
	przypisanie_rekordów(login);

	return 0;
}
int user_co_zrobić()
{
	system("cls");
	cout << "\nzarejestrowano. powrot(1)";
	char user_response_2;
	cin >> user_response_2;
	if (user_response_2 == '1') return 0;
	return user_co_zrobić();
}
//creating an account function
int zarejestruj()
{
	system("cls");
	string loginn = ustawienie_loginu();
	string hasłoo = ustawienie_hasła();
	const char* login = loginn.c_str(); 
	const char* hasło = hasłoo.c_str();
	zapisanie_hasła(login, hasło);
	if (user_co_zrobić() == 1)return 1;
	return 0;
}

// funtion that runs all previous ones
int exe()
{
	system("cls");
	cout << "Witaj! Wybierz co chcesz zrobic:\nzaloguj(1)\nzarejestruj(2)\n";
	char user_response_1;
	cin >> user_response_1;
	if (user_response_1 == '1')
	{
		if (zaloguj() == 1) return 1;
	}
	else if (user_response_1 == '2')
	{
		if (zarejestruj() == 0) return exe();
	}
	else
	{
		system("cls");
		return exe();
	}
	return 0;
}


////////////////////////////////////////////////////////////////////////////////////
int lobby()
{
	Sleep(1000);
	system("cls");
	cout << "Aby rozpoczac gre nacisnij 1\nAby poznac zasady gry nacisnij 2\nAby wyjsc zamknij okno (X)\n";
	char user_repsonse;
	cin >> user_repsonse;
	if (user_repsonse == '1') return 1;
	else if (user_repsonse == '2')
	{
		system("cls");
		cout << "zlap jak najwiecej papryk!\nzbieraj tez inne owoce! a takze warzywa!\nsterowanie strzalkami prawo/lewo\n\nAby rozpoczac gre nacisnij 1\nPowrot nacisnij 2\n\n";
		cout<<"ABY PRZERWAC OKNO GRY I WROCIC NA WYJSCIE KONSOLI NACISNIJ 'X' Z KLAWIATURY\n\naby zrobic zoom wcisnij Z\n\nPOKONAJ CZERWONE PAPRYKI I OCAL GALAKTYKE!";
		char user_repsonse_2;
		cin >> user_repsonse_2;
		if (user_repsonse_2 == '1')return 1;
		else return lobby();
	}
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
int SaveScore(int wynik)
{
	sqlite3* db;
	sqlite3_stmt* stmt;
	int rc;

	// Otwórz bazę danych w trybie zapisu
	rc = sqlite3_open_v2("baza1", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Nie można otworzyć bazy danych: " << sqlite3_errmsg(db) << std::endl;
		return 1;
	}

	// Przygotowanie zapytania SQL do aktualizacji wyniku
	const char* updateQuery = "UPDATE wyniki SET wynik = ? WHERE login = ?;";
	rc = sqlite3_prepare_v2(db, updateQuery, -1, &stmt, nullptr);
	if (rc != SQLITE_OK) {
		std::cerr << "Nie udało się przygotować zapytania: " << sqlite3_errmsg(db) << std::endl;
		sqlite3_close(db);
		return 1;
	}

	// Zwiąż wartość całkowitą wyniku (4) z zapytaniem
	sqlite3_bind_int(stmt, 1, wynik);
	// Zwiąż wartość tekstową loginu ("kuzik") z zapytaniem
	sqlite3_bind_text(stmt, 2, Login.c_str(), -1, SQLITE_STATIC);

	// Wykonaj zapytanie
	rc = sqlite3_step(stmt);
	if (rc != SQLITE_DONE) {
		std::cerr << "Błąd podczas wykonywania zapytania: " << sqlite3_errmsg(db) << std::endl;
	}
	else {
		std::cout << "wynik zostal zapisany" << std::endl;
	}

	// Zakończenie pracy z zapytaniem i zamknięcie bazy danych
	sqlite3_finalize(stmt);
	sqlite3_close(db);

	return (rc == SQLITE_DONE) ? 0 : 1;
}

