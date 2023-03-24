/** @file */
#include <iostream>
#undef _HAS_STD_BYTE
#include "Hero.h"

using namespace std;

/**
* Klasa wirtualna. Zawiera ona trzy wirtualne metody, beda one wywolywane dla wielu lokalizacji w zaleznosci od miejsca gdzie obecnie znajduje sie gracz.
* */
class VirtualLocation
{
public:
	virtual void description() = 0;             //opis lokalizacji
	virtual void player_action(Hero& hero)=0;   //proces przechodzenia przez lokalizacjê
	virtual void reroll(int x)=0;               //losuje nowy ennumber (identyfikator lokalizacji)
};


/**
* Klasa zawierajaca kilka metod, zostana one wywolane podczas pobytu bohatera w wybranej lokacji w celu jego interakcji z kolejnymi poziomami gry.
* */
class Location : public VirtualLocation
{
protected:
	int ennumber;
public:
	int textspeed;
	int random(int x); //zakres wylosowanych liczb 0 - (x-1)
	void printdc(string a);
	void player_action(Hero& hero) {};
	void leavechamber();
	void setspeed(); //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	
};


/**
* Klasa Korytarza. Znajduje sie on pomiedzy kolejnymi komnatami. Gracz na koncu korytarza wybiera kierunek swojej dalszej podrozy.
* */
class Hallway : public Location
{
	
public:
	Hallway() { ennumber = random(5); }
	~Hallway() {}

	void description();
	void player_action() {};
	void reroll(int x);
	int go_next();


};

/**
* Klasa Komnaty. Po niej dziedzicza konkretne rodzaje komnat, ktore bohater bedzie napotykal na swojej drodze
* */
class Chamber : public Location
{

public:
	Chamber() {};
	~Chamber() {};
	void description() {};
};
/**
* *Klasa komnaty z przeciwnikiem. Gracz musi wybrac sposob konfrontacji z wrogiem aby zdobyc skarb i ruszyc dalej
* */
class Skirmish_Chamber : public Chamber
{
	
public:
	Skirmish_Chamber() { ennumber = random(5); };
	~Skirmish_Chamber() {};
	void description();
	void player_action(Hero& hero);
	void reroll(int x);
};

/**
* Klasa komnaty zawierajacej skrzynie ze skarbem. Bohater moze otworzyc skrzynke w celu zdobycia skarbu lub zaniechac tej czynnosci
* */
class Treasure_Chamber : public Chamber
{
	
public:
	Treasure_Chamber() { ennumber = random(5); };
	~Treasure_Chamber() {};

	void description();
	void player_action(Hero& hero);
	void reroll(int x);
};

/**
* Klasa komnaty z wydarzeniem. Tutaj bohater moze napotkac wszelkiego rodzaju przygody.
* */
class Event_Chamber : public Chamber
{
	
public:
	Event_Chamber() { ennumber = random(5); }
	~Event_Chamber() {};

	void description();
	void player_action(Hero& h);
	void reroll(int x);

};

class Special_Chamber : public Chamber
{
public:
	Special_Chamber() { ennumber = random(3); }
	~Special_Chamber() {};

	void description();
	void player_action(Hero& hero);
	void reroll(int x);
};
