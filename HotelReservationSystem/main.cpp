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
#include "Miasto.h"
#include "Hotel.h"

using namespace std;

ostream& operator<<(ostream& wyjscie, Kalendarz& k1)
{
	wyjscie << k1.m_dzien << "." << k1.m_miesiac << "." << k1.m_rok << endl;
	return wyjscie;
}

bool operator==(const Kalendarz& d1, const Kalendarz& d2)
{
	return ((d1.m_dzien == d2.m_dzien) && (d1.m_miesiac == d2.m_miesiac) && (d1.m_rok == d2.m_rok));
}

ostream& operator<<(ostream& wyj, const Pokoj& pp)
{
	wyj << pp.m_nr_pokoju;
	return wyj;
}

ostream& operator<<(ostream& wyj, const Rezerwacja& r)
{
	wyj << r.m_liczba_osob;
	return wyj;
}

ostream& operator<<(ostream& wyjscie, const Hotel& h)
{
	wyjscie << h.m_nazwa_hotelu;
	return wyjscie;
}

ostream& operator<<(ostream& wyjj, const Miasto& mm)
{
	wyjj << mm.m_nazwa_miasta;
	return wyjj;
}

bool operator <(const Kalendarz& data1, const Kalendarz& data2)
{
	return ((data1.m_dzien < data2.m_dzien) || (data1.m_miesiac < data2.m_miesiac) || (data1.m_rok < data2.m_rok));
}

bool operator >(const Kalendarz& data1, const Kalendarz& data2)
{
	return ((data1.m_dzien > data2.m_dzien) || (data1.m_miesiac > data2.m_miesiac) || (data1.m_rok > data2.m_rok));
}


void koniec(void)
{
	char d;

	cout << endl;
	cout << endl;
	cout << "nacisnij dowolny klawisz oraz Enter aby wrocic do menu.." << endl;

	cin >> d;

	switch (d)
	{
	default:
		break;
	}
}

void wstep(Miasto& m1, Rezerwacja& r1, Pokoj p1, Hotel h1, int liczba_osob, int nr_pokoju, string nazwa_miasta, vector<Miasto> miasta, string& poczatek_rezerwacji, string& koniec_rezerwacji, string& imie, string& nazwisko, string& email, string& nr_ID, int& nr_tel, string nazwa_hotelu)
{
	char c;


	while (true)
	{
		system("cls");
		cout << endl;
		cout << "###########################################" << endl;
		cout << "###    WITAMY W WYSZUKIWARCE HOTELI!    ###" << endl;
		cout << "###########################################" << endl;
		cout << endl;
		cout << endl;
		cout << " Wybierz preferowana opcje:" << endl;
		cout << endl;
		cout << "  1. Lista dostepnych miast" << endl;
		cout << "  2. Lista hoteli w danym miescie" << endl;
		cout << "  3. Wyszukaj dostepne hotele w danym terminie" << endl;
		cout << "  4. Dodaj rezerwacje" << endl;
		cout << "  5. Znajdz swoja rezerwacje" << endl;

		cin >> c;

		switch (c)
		{
		case '1':

			m1.wyswietlanie_miast(miasta);
			for (int i = 0; i < miasta.size(); i++)
			{
				cout << miasta[i] << endl;
			}

			koniec();
			break;

		case '2':

			cout << "podaj nazwe miasta, w ktorym chcesz wyszukac hotele" << endl;
			cin >> nazwa_miasta;
			//m1.zaladuj_hotele(nazwa_miasta);
			m1.wyswietl_hotele(nazwa_miasta);
			koniec();
			break;

		case '3':
			m1.dostepnosc(nazwa_miasta, r1, h1, p1, poczatek_rezerwacji, koniec_rezerwacji, liczba_osob);
			koniec();
			break;

		case '4':

			p1.dodaj_rezerwacje(liczba_osob, nr_pokoju, nazwa_miasta, poczatek_rezerwacji, koniec_rezerwacji, imie, nazwisko, email, nr_ID, nr_tel, nazwa_hotelu, p1);
			koniec();
			break;

		case '5':
			p1.wyswietl_rezerwacje(p1);
			koniec();
			break;

		default:
			cout << "Blad. Podaj numer jednej z powyzszych opcji" << endl;
			break;
		}
	}
}

int main()
{
	string nazwa_hotelu;
	string nazwa_miasta;
	int nr_pokoju = 200;
	int liczba_osob = 2;
	string nr_rezerwacji;
	string poczatek_rezerwacji;
	string koniec_rezerwacji;
	string imie;
	string nazwisko;
	string email;
	string nr_ID;
	int nr_tel;
	vector<Miasto> miasta;
	vector<Pokoj> pokoje;
	Pokoj p1;
	Miasto m1;
	Rezerwacja r1;
	Hotel h1;

	wstep(m1, r1, p1, h1, liczba_osob, nr_pokoju, nazwa_miasta, miasta, poczatek_rezerwacji, koniec_rezerwacji, imie, nazwisko, email, nr_ID, nr_tel, nazwa_hotelu);

	return 0;
}