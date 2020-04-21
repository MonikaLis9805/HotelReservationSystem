#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include <windows.h>
#include <winbase.h>
#include <conio.h>
#include "Kalendarz.h"
#include "Rezerwacja.h"
#include "Pokoj.h"

using namespace std;

class Hotel
{
private:
	string m_nazwa_hotelu;
	vector<Pokoj> pokoje;

public:
	Hotel(string nazwa_hotelu = "") : m_nazwa_hotelu{ nazwa_hotelu }
	{}

	string get_nazwa_hotelu(void) const { return m_nazwa_hotelu; }
	void set_nazwa_hotelu(string& nazwa_hotelu) { m_nazwa_hotelu = nazwa_hotelu; }
	vector<Pokoj> get_wektor_pokoji(void) const { return pokoje; }
	void set_wektor_pokoji(vector<Pokoj> yy_pokoje) { pokoje = yy_pokoje; }
	friend ostream& operator<<(ostream& wyjscie, const Hotel& h);

	int string_toDouble(string napis)
	{
		int konwersja = stoi(napis, nullptr, 10);
		return konwersja;
	}

	vector<Pokoj> zaladuj_pokoje(string nazwa_hotelu)
	{
		Hotel h1;
		h1.set_nazwa_hotelu(nazwa_hotelu);
		pokoje.clear();

		ifstream baza_danych("C:\\Users\\MONIKA\\Desktop\\Hotel reservation system\\baza_danych.txt");
		string linia_tekstu;
		string linia_tekstu2;
		string linia_tekstu3;
		int liczba;

		while (!baza_danych.eof())                   //Funkcja eof() zwróci wartoœæ true wtedy, gdy nie bêdzie ju¿ w pliku wiêcej danych do odczytu.
		{
			getline(baza_danych, linia_tekstu);
			int znaleziona_pozycja = linia_tekstu.find(nazwa_hotelu, 0);
			int pozycja_kursora = baza_danych.tellg();

			if (znaleziona_pozycja >= 0)
			{
				getline(baza_danych, linia_tekstu2);

				getline(baza_danych, linia_tekstu3);


				while (1)
				{
					int pozycja2 = linia_tekstu2.find("(", 0);
					if (pozycja2 == -1)
					{
						break;
					}
					int pozycja3 = linia_tekstu2.find(")", 0);
					int dlugosc_numeru = pozycja3 - pozycja2 - 1; // musi byæ -1 bo indeksowanie tablicy zaczyna siê od zera

					string numer = linia_tekstu2.substr(pozycja2 + 1, dlugosc_numeru);

					int numer_pokonwersji = string_toDouble(numer);

					Pokoj p1;

					p1.set_nr_pokoju(numer_pokonwersji);

					linia_tekstu2.replace(pozycja2, 1, "[");
					linia_tekstu2.replace(pozycja3, 1, "]");

					int pozycja4 = linia_tekstu3.find("(", 0);
					if (pozycja4 == -1)
					{
						break;
					}
					int pozycja5 = linia_tekstu3.find(")", 0);
					int dlugosc_numeru2 = pozycja5 - pozycja4 - 1;
					string numer2 = linia_tekstu3.substr(pozycja4 + 1, dlugosc_numeru2);
					int numer_pokonwersji2 = stoi(numer2, nullptr, 10);
					p1.set_liczba_osob(numer_pokonwersji2);

					linia_tekstu3.replace(pozycja4, 1, "[");
					linia_tekstu3.replace(pozycja5, 1, "]");

					h1.pokoje.push_back(p1);
				}
			}

		}

		/*for (int i = 0; i < h1.pokoje.size(); i++)
		{
			cout << h1.pokoje[i] << " ";
		}*/

		return h1.pokoje;
	}
};

