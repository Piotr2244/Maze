/** @file */
#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <string>

using namespace std;


/**
* Klasa Bohatera. Zawiera ona w sobie wszelkie atrybuty postaci oraz metody umo�liwiajace wiele jego interakcji z graczem.
*@param HP obecne punkty wytrzymalosci bohatera 
* @param STR obecne punkty sily bohatera 
* @param LCK obecne punkty szczescia bohatera 
* @param NAME imie bohatera
* @param PROF profesja bohatera
* @param GOLD posiadane zloto
* @param XP punkty doswiadczenia, niewidoczne dla gracza, maja wplyw na trudnosc rozgrywki
*/
class Hero
{
public:
	int HP;
	int STR;
	int LCK;
	string NAME;
	string PROF;
	int GOLD=0;
	int XP = 0; //wp�ywa na liczb� znalezionych skarb�w


	void SetStats(int H, int S, int L, string P); // Ustawia statystyki bohatera
	void CreateHero();                            // Przeprowadza gracza przez proces tworzenia bohatera
	void ShowHero();                              // Pokazuje statystyki bohatera
	void SaveStats();                             // Zapisuje do pliku wynik ko�cowy gry
	void Endgame();                               // Procedura ko�cz�ca rozgrywk�
	void Printdch(string a);                      // Funkcja kosmetyczna wy�wietlaj�ca tekst z op�nieniem
	//statystyki do wyniku ko�cowego
	int TotalChambers = 0;
	int TotalEnemies = 0;
	int TotalLuckUsed = 0;
	int TotalPotions = 0;
};

int MainMenu();
void Howtoplay();

