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

using namespace std;

class Rezerwacja
{
private:
	string m_nazwa_miasta;
	string m_nazwa_hotelu;
	int m_nr_pokoju;
	int m_liczba_osob;
	string m_nr_rezerwacji;
	string m_poczatek_rezerwacji;
	string m_koniec_rezerwacji;
	string m_imie;
	string m_nazwisko;
	string m_email;
	string m_nr_ID;
	int m_nr_tel;
	vector<Kalendarz> dlugosc_pobytu;

public:
	Rezerwacja(string nazwa_miasta = "", string nazwa_hotelu = "", int nr_pokoju = 0, int liczba_osob = 2, string nr_rezerwacji = "10", string poczatek_rezerwacji = "1.1.10", string koniec_rezerwacji = "2.1.10", string imie = "", string nazwisko = "", string email = "", string nr_ID = "", int nr_tel = 111) :m_nazwa_miasta{ nazwa_miasta }, m_nazwa_hotelu{ nazwa_hotelu }, m_nr_pokoju{ nr_pokoju }, m_liczba_osob{ liczba_osob }, m_nr_rezerwacji{ nr_rezerwacji }, m_poczatek_rezerwacji{ poczatek_rezerwacji }, m_koniec_rezerwacji{ koniec_rezerwacji }, m_imie{ imie }, m_nazwisko{ nazwisko }, m_email{ email }, m_nr_ID{ nr_ID }, m_nr_tel{ nr_tel }
	{}
	string get_nazwa_miasta(void) const { return m_nazwa_miasta; }
	void set_nazwa_miasta(string nazwa_miasta) { m_nazwa_miasta = nazwa_miasta; }
	string get_nazwa_hotelu(void) const { return m_nazwa_hotelu; }
	void set_nazwa_hotelu(string nazwa_hotelu) { m_nazwa_hotelu = nazwa_hotelu; }
	int get_nr_pokoju(void) const { return m_nr_pokoju; }
	void set_nr_pokoju(int nr_pokoju) { m_nr_pokoju = nr_pokoju; }
	int get_liczba_osob(void) const { return m_liczba_osob; }
	void set_liczba_osob(int liczba_osob) { m_liczba_osob = liczba_osob; }
	string get_nr_rezerwacji(void) const { return m_nr_rezerwacji; }
	void set_nr_rezerwacji(string nr_rezerwacji) { m_nr_rezerwacji = nr_rezerwacji; }
	string get_poczatek_rezerwacji(void) const { return m_poczatek_rezerwacji; }
	void set_poczatek_rezerwacji(string poczatek_rezerwacji) { m_poczatek_rezerwacji = poczatek_rezerwacji; }
	string get_koniec_rezerwacji(void) const { return m_koniec_rezerwacji; }
	void set_koniec_rezerwacji(string koniec_rezerwacji) { m_koniec_rezerwacji = koniec_rezerwacji; }
	string get_imie(void) const { return m_imie; }
	void set_imie(string imie) { m_imie = imie; }
	string get_nazwisko(void) const { return m_nazwisko; }
	void set_nazwisko(string nazwisko) { m_nazwisko = nazwisko; }
	string get_email(void) const { return m_email; }
	void set_email(string email) { m_email = email; }
	string get_nr_ID(void) const { return m_nr_ID; }
	void set_nr_ID(string nr_ID) { m_nr_ID = nr_ID; }
	int get_nr_tel(void) const { return m_nr_tel; }
	void set_nr_tel(int nr_tel) { m_nr_tel = nr_tel; }
	vector<Kalendarz> get_dlugosc_pobytu(void) const { return dlugosc_pobytu; }
	void set_dlugosc_pobytu(vector<Kalendarz> yy_dlugosc_pobytu) { dlugosc_pobytu = yy_dlugosc_pobytu; }

	friend ostream& operator<<(ostream& wyj, const Rezerwacja& r);

	vector<Kalendarz> wprowadzanie_dat(string poczatek_rezerwacji, string koniec_rezerwacji)
	{
		Kalendarz data1;
		int i = 0;
		int j = 0;
		int k = 0;
		int m_tab[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		SYSTEMTIME st;
		GetSystemTime(&st);

		while (i == 0 || j == 0 || k == 0)
		{
			cout << "Podaj date poczatku rezerwacji w formacie: dd.mm.rrrr" << endl;
			cin >> poczatek_rezerwacji;

			string pdzien = poczatek_rezerwacji.substr(0, 2);
			string pmiesiac = poczatek_rezerwacji.substr(3, 2);
			string prok = poczatek_rezerwacji.substr(6, 4);

			int Pdzien = stoi(pdzien, nullptr, 10);
			int Pmiesiac = stoi(pmiesiac, nullptr, 10);
			int Prok = stoi(prok, nullptr, 10);


			if (Prok % 4 == 0)
			{
				m_tab[1] = 29;
			}

			if ((Pdzien > m_tab[Pmiesiac - 1] || Pdzien < 1))
			{
				cout << "bledny dzien" << endl;
				cout << endl;
			}
			if ((Pdzien < st.wDay) && (Pmiesiac == st.wMonth))
			{
				cout << "bledny dzien" << endl;
				cout << endl;
			}
			else
			{
				data1.set_dzien(Pdzien);
				i++;
			}

			if (Pmiesiac > 12 || Pmiesiac < 1)
			{
				cout << "bledny miesiac" << endl;
				cout << endl;
			}
			if ((Pmiesiac < st.wMonth) && (Prok == st.wYear))
			{
				cout << "bledny miesiac" << endl;
				cout << endl;
			}
			else
			{
				data1.set_miesiac(Pmiesiac);
				j++;
			}

			if (Prok < st.wYear)
			{
				cout << "bledny rok" << endl;
				cout << endl;
			}
			else if (Prok > st.wYear + 2)
			{
				cout << "nie mozna zarezerwowac hotelu pozniej niz 2 lata do przodu" << endl;
				cout << endl;
			}
			else
			{
				data1.set_rok(Prok);
				k++;
			}
		}

		Kalendarz data2;
		int x = 0;
		int y = 0;
		int z = 0;

		while (x == 0 || y == 0 || z == 0)
		{

			cout << "Podaj date konca rezerwacji w formacie: dd.mm.rrrr" << endl;
			cin >> koniec_rezerwacji;

			string kdzien = koniec_rezerwacji.substr(0, 2);
			string kmiesiac = koniec_rezerwacji.substr(3, 2);
			string krok = koniec_rezerwacji.substr(6, 4);

			int Kdzien = stoi(kdzien, nullptr, 10);
			int Kmiesiac = stoi(kmiesiac, nullptr, 10);
			int Krok = stoi(krok, nullptr, 10);

			if (Krok % 4 == 0)
			{
				m_tab[1] = 29;
			}


			data2.set_dzien(Kdzien);

			if ((data1.get_dzien() == data2.get_dzien()) && (data1.get_miesiac() == data2.get_miesiac()))
			{
				cout << "rezerwacja musi obejmowac przynajmniej jedna dobe" << endl;
				cout << endl;
			}

			else if ((Kdzien > m_tab[Kmiesiac - 1]) || (Kdzien < 1))
			{
				cout << "bledny dzien" << endl;
				cout << endl;
			}

			else if ((Kdzien < data1.get_dzien()) && (data1.get_miesiac() == Kmiesiac))
			{
				cout << "zle wprowadzona data" << endl;
			}
			else
			{
				x++;
			}

			if (Kmiesiac > 12 || Kmiesiac < 1)
			{
				cout << "bledny miesiac" << endl;
				cout << endl;
			}

			else
			{
				data2.set_miesiac(Kmiesiac);
				y++;
			}

			if (Krok < st.wYear)
			{
				cout << "bledny rok" << endl;
				cout << endl;
			}
			else if (Krok > st.wYear + 2)
			{
				cout << "nie mozna zarezerwowac hotelu pozniej niz 2 lata do przodu" << endl;
				cout << endl;
			}
			else
			{
				data2.set_rok(Krok);
				z++;
			}
		}

		vector<Kalendarz> daty;
		daty.push_back(data1);
		daty.push_back(data2);

		return daty;
	}

	vector<Kalendarz> tworzenie_wektoru_dlugosci_pobytu(string& poczatek_rezerwacji, string& koniec_rezerwacji)
	{
		Kalendarz data1;
		Kalendarz data2;

		string pdzien = poczatek_rezerwacji.substr(0, 2);
		string pmiesiac = poczatek_rezerwacji.substr(3, 2);
		string prok = poczatek_rezerwacji.substr(6, 4);

		int Pdzien = stoi(pdzien, nullptr, 10);
		int Pmiesiac = stoi(pmiesiac, nullptr, 10);
		int Prok = stoi(prok, nullptr, 10);


		string kdzien = koniec_rezerwacji.substr(0, 2);
		string kmiesiac = koniec_rezerwacji.substr(3, 2);
		string krok = koniec_rezerwacji.substr(6, 4);

		int Kdzien = stoi(kdzien, nullptr, 10);
		int Kmiesiac = stoi(kmiesiac, nullptr, 10);
		int Krok = stoi(krok, nullptr, 10);

		data1.set_dzien(Pdzien);
		data1.set_miesiac(Pmiesiac);
		data1.set_rok(Prok);

		data2.set_dzien(Kdzien);
		data2.set_miesiac(Kmiesiac);
		data2.set_rok(Krok);

		int m_tab[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

		if (Prok % 4 == 0)
		{
			m_tab[1] = 29;
		}

		if (Krok % 4 == 0)
		{
			m_tab[1] = 29;
		}

		while (!(data1 == data2))
		{
			dlugosc_pobytu.push_back(data1);
			int nowydzien = data1.get_dzien();
			nowydzien++;
			data1.set_dzien(nowydzien);

			if (data1.get_dzien() > m_tab[data1.get_miesiac() - 1])
			{
				data1.set_dzien(1);
				int nowymiesiac = data1.get_miesiac();
				nowymiesiac++;
				data1.set_miesiac(nowymiesiac);

				if (data1.get_miesiac() > 12)
				{
					data1.set_miesiac(1);
					int nowyrok = data1.get_rok();
					nowyrok++;
					data1.set_rok(nowyrok);
				}
			}
		}

		dlugosc_pobytu.push_back(data2);

		return dlugosc_pobytu;
	}
};


