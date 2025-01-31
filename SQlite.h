#pragma once
#include "sqlite-amalgamation-3450300/sqlite3.h"
#include <iostream>

int SQ_config(const char* nazwa)
{
	sqlite3* baza_danych;
	char* error_message = nullptr;
	int rc;

	//otwarcie bazy
	rc = sqlite3_open(nazwa, &baza_danych);
	if (rc != 0) { std::cerr << sqlite3_errmsg(baza_danych); return 1; }

	//zapytanie
	const char* zapytanie = "CREATE TABLE IF NOT EXISTS uzytkownicy("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"login TEXT NOT NULL,"
		"password TEXT NOT NULL);";

	//wykonanie zapytania (rc to kontrolka bledow)
	rc = sqlite3_exec(baza_danych, zapytanie, nullptr, nullptr, &error_message);
	if (rc != 0)
	{
		std::cerr << "B³¹d SQL: " << error_message << std::endl;
		sqlite3_free(error_message);
	}

	//zamkniecie bazy
	sqlite3_close(baza_danych);
	return 0;
}

int delete_tab(const char* nazwa)
{
	sqlite3* baza_danych;
	char* error_message = nullptr;
	int rc; //return code - aktualny kod stanu bazy - inny ni¿ 0 wskazuje na b³¹d

	rc = sqlite3_open(nazwa, &baza_danych);
	if (rc != 0) { std::cerr << sqlite3_errmsg(baza_danych); return 11; }

	const char* zapytanie = " DROP TABLE IF EXISTS u¿ytkownicy";

	rc = sqlite3_exec(baza_danych, zapytanie, nullptr, nullptr, &error_message);
	if (rc != 0)
	{
		std::cerr << "B³¹d SQL: " << error_message << std::endl;
		sqlite3_free(error_message);
	}

	sqlite3_close(baza_danych);
	return 0;
} //usuwanie 

int delete_base(const char* nazwa)
{
	if (std::remove(nazwa) != 0) {
		std::cerr << "B³¹d podczas usuwania bazy danych" << std::endl;
		return 1;
	}
	return 0;
}

