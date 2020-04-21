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
#include "Hotel.h"

using namespace std;

class Miasto
{
private:
	string m_nazwa_miasta;
	vector<Hotel> hotele;
	vector<Miasto> miasta;

public:
	Miasto(string nazwa_miasta = " ") : m_nazwa_miasta{ nazwa_miasta }
	{}

	string get_nazwa_miasta(void) const { return m_nazwa_miasta; }
	void set_nazwa_miasta(string& nazwa_miasta) { m_nazwa_miasta = nazwa_miasta; }
	friend ostream& operator<<(ostream& wyjj, const Miasto& mm);


	vector<Hotel> zaladuj_hotele(string& nazwa_miasta)
	{
		string linia_tekstu;
		hotele.clear();
		// klasa ifstream otwiera plik do odczytu
		ifstream baza_danych("C:\\Users\\MONIKA\\Desktop\\Hotel reservation system\\baza_danych.txt");

		Hotel h1;

		while (!baza_danych.eof())                   //Funkcja eof() zwróci wartoœæ true wtedy, gdy nie bêdzie ju¿ w pliku wiêcej danych do odczytu.
		{
			getline(baza_danych, linia_tekstu);
			int pozycja = linia_tekstu.find(nazwa_miasta, 0);

			if (pozycja >= 0)
			{
				linia_tekstu.erase(pozycja, size(nazwa_miasta) + 1);
				h1.set_nazwa_hotelu(linia_tekstu);
				//string pomoc = h1.get_nazwa_hotelu();
				//h1.set_wektor_pokoji(h1.zaladuj_pokoje(pomoc));

				h1.set_wektor_pokoji(h1.zaladuj_pokoje(h1.get_nazwa_hotelu()));
				hotele.push_back(h1);
			}
		}

		hotele.erase(hotele.begin());

		return hotele;
	}

	void wyswietl_hotele(string& nazwa_miasta)
	{
		vector<Hotel> pomochotele;
		vector<Pokoj> pomocpokoje;
		pomochotele = zaladuj_hotele(nazwa_miasta);

		for (int i = 0; i < pomochotele.size(); i++)
		{
			cout << "Nazwa hotelu: " << hotele[i] << endl;

			pomocpokoje = pomochotele[i].get_wektor_pokoji();

			cout << "Numery pokoi: ";
			for (int j = 0; j < pomocpokoje.size(); j++)
			{
				cout << pomocpokoje[j] << " ";
			}
			cout << endl;
		}

	}

	void wyswietlanie_miast(vector<Miasto>& miasta)
	{
		miasta.clear();
		cout << "Lista miast w bazie danych:" << endl;
		ifstream baza_danych("C:\\Users\\MONIKA\\Desktop\\Hotel reservation system\\baza_danych.txt");
		while (!baza_danych.eof())
		{
			string linia_tekstu;
			getline(baza_danych, linia_tekstu);
			int pozycja = linia_tekstu.find("Miasto:", 0);
			if (pozycja >= 0)
			{
				linia_tekstu.erase(pozycja, 8);
				Miasto m1;
				m1.set_nazwa_miasta(linia_tekstu);
				miasta.push_back(m1);
			}
		}
	}

	void dostepnosc(string nazwa_miasta, Rezerwacja r1, Hotel h1, Pokoj p1, string poczatek_rezerwacji, string koniec_rezerwacji, int liczba_osob)
	{
		cout << "podaj miasto, w ktorym chcesz wyszukac dostepne hotele" << endl;
		cin >> nazwa_miasta;

		vector<Hotel> wektorhoteli;
		wektorhoteli = zaladuj_hotele(nazwa_miasta);

		vector<Kalendarz> daty = r1.wprowadzanie_dat(poczatek_rezerwacji, koniec_rezerwacji);

		string pompdzien = to_string(daty[0].get_dzien());
		if (pompdzien.size() == 1)
		{
			pompdzien = "0" + pompdzien;
		}
		string pompmiesiac = to_string(daty[0].get_miesiac());
		if (pompmiesiac.size() == 1)
		{
			pompmiesiac = "0" + pompmiesiac;
		}
		string pomprok = to_string(daty[0].get_rok());

		string pomkdzien = to_string(daty[1].get_dzien());
		if (pomkdzien.size() == 1)
		{
			pomkdzien = "0" + pomkdzien;
		}
		string pomkmiesiac = to_string(daty[1].get_miesiac());
		if (pomkmiesiac.size() == 1)
		{
			pomkmiesiac = "0" + pomkmiesiac;
		}
		string pomkrok = to_string(daty[1].get_rok());

		string pocz_rez = pompdzien + "." + pompmiesiac + "." + pomprok;
		string kon_rez = pomkdzien + "." + pomkmiesiac + "." + pomkrok;


		cout << "podaj liczbe osob w pokoju" << endl;
		cin >> liczba_osob;
		int a;

		vector<Rezerwacja> wektorrezerwacji;
		wektorrezerwacji = p1.zaladuj_rezerwacje();

		vector<Kalendarz> nowadlpobytu;
		vector<Pokoj> wektorpokoji;



		for (int i = 0; i < wektorrezerwacji.size(); i++)
		{
			a = 0;

			if (wektorrezerwacji[i].get_nazwa_miasta() == nazwa_miasta)
			{

				if (wektorrezerwacji[i].get_liczba_osob() >= liczba_osob)
				{

					nowadlpobytu.clear();
					nowadlpobytu = wektorrezerwacji[i].get_dlugosc_pobytu();

					for (int j = 0; j < nowadlpobytu.size(); j++)
					{
						if (a == 1)
						{
							break;
						}

						if ((nowadlpobytu[j] == daty[0]) || (nowadlpobytu[j] == daty[1]) || (daty[0] < nowadlpobytu[0]) && (daty[1] > nowadlpobytu[nowadlpobytu.size() - 1]))
						{

							string hotel = wektorrezerwacji[i].get_nazwa_hotelu();

							for (int k = 0; k < wektorhoteli.size(); k++)
							{
								wektorpokoji = wektorhoteli[k].get_wektor_pokoji();


								if (wektorhoteli[k].get_nazwa_hotelu() == hotel)
								{

									for (int x = 0; x < wektorpokoji.size(); x++)
									{
										int numer_pokoju = wektorrezerwacji[i].get_nr_pokoju();

										if ((wektorpokoji[x].get_liczba_osob() < liczba_osob) || (wektorpokoji[x].get_nr_pokoju() == numer_pokoju))
										{

											int dodatkowaliczbaosob = wektorpokoji[x].get_liczba_osob();
											wektorpokoji.erase(wektorpokoji.begin() + x);

											Pokoj p;
											p.set_liczba_osob(dodatkowaliczbaosob);
											p.set_nr_pokoju(1);
											wektorpokoji.insert(wektorpokoji.begin() + x, p);
										}
									}
								}

								wektorhoteli[k].set_wektor_pokoji(wektorpokoji);

							}

							a = 1;
						}
					}
				}
			}
		}
		vector<Pokoj> niemoge4;
		for (int i = 0; i < wektorhoteli.size(); i++)
		{
			Hotel hehe3 = wektorhoteli[i];
			niemoge4 = hehe3.get_wektor_pokoji();

			for (int j = 0; j < niemoge4.size(); j++)
			{
				if (niemoge4[j].get_liczba_osob() < liczba_osob)
				{
					niemoge4[j].set_nr_pokoju(1);
				}
			}

			wektorhoteli[i].set_wektor_pokoji(niemoge4);
		}

		vector<Pokoj> niemoge2;
		int g = 0;

		for (int i = 0; i < wektorhoteli.size(); i++)
		{
			Hotel hehe = wektorhoteli[i];

			niemoge2 = hehe.get_wektor_pokoji();
			int nowyrozmiar = niemoge2.size();

			while (true)
			{
				g = 0;

				for (int j = 0; j < nowyrozmiar; j++)
				{
					if (niemoge2[j].get_nr_pokoju() == 1)
					{
						niemoge2.erase(niemoge2.begin() + j);
						g++;
					}

					nowyrozmiar = niemoge2.size();
				}

				if (g == 0)
				{
					break;
				}
			}

			wektorhoteli[i].set_wektor_pokoji(niemoge2);

		}
		system("cls");
		cout << endl;
		cout << endl;
		cout << "Wyniki wyszukiwania dostepnych hoteli w miescie " << nazwa_miasta << " w dniach od " << pocz_rez << " do " << kon_rez << " dla " << liczba_osob << " osob: " << endl;
		cout << endl;

		for (int i = 0; i < wektorhoteli.size(); i++)
		{
			cout << "hotel: " << wektorhoteli[i] << " " << endl;

			Hotel hehe2 = wektorhoteli[i];
			vector<Pokoj> niemoge3 = hehe2.get_wektor_pokoji();
			if (niemoge3.size() == 0)
			{
				cout << "Przykro nam! Brak dostepnych pokoji w tym hotelu w podanym terminie :(";
			}
			else
			{
				cout << "Pokoje: ";
				for (int j = 0; j < niemoge3.size(); j++)
				{
					cout << niemoge3[j] << " ";
				}
			}
			cout << endl;
		}
	}
};

