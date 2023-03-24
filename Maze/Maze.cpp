#include <iostream>
#include <locale.h>
#include <Windows.h>
#include <thread>
#include <future>
#undef _HAS_STD_BYTE
#include "Locations.h"
#include "Hero.h"
using namespace std;

/**
* Funkcja sprawdzajaca czy punkty zycia bohatera nie spadly do zera lub ponizej.
* */
void is_hero_alive(Hero& hero,bool& alive)
{
    while (hero.HP > 0)
    {
        Sleep(1000);
    }
    alive = false;
    
}
 

/**
* Funkcja liczaca czas rozgrywki
* */
void gameTime(bool& gameison, std::promise<int>& prom)
{
    int seconds = 0;
    while (gameison == true)
    {
        Sleep(1000);
        seconds++;
    }
    prom.set_value(seconds);
}

/**
* Funkcja Main, Tworzone sa w niej obiekty lokacji oraz bohatera.
* Cala funkcja operuje procesem gry wywolujac odpowiednie funkcje oraz metody, w tym wirtualne.
* Po rozpoczeciu gry nastepuje proces tworzenia bohatera.
* Po zakonczeniu tworzenia bohatera, uruchamiane sa wszelkie watki i gra sie rozpoczyna
* w zaleznosci od decyzji gracza, wywolywane sa konkretne metody a calosc symuluje proces chodzenia po labiryncie.
* Labirynt tworzy sie na biezaco, kolejne komnaty przybieraja nowe postacie, opisy oraz zawartosci.
* Po zakonczeniu gry wywolywane sa odpowiednie metody koncowe a nastepnie gracz wraca do menu glownego.
* */
int main()
{
    setlocale(LC_CTYPE, "Polish");
    int menuoption=0;
    while (menuoption != 3)
    {
        
        menuoption = MainMenu();
        switch (menuoption)
        {
        case 1:
        {
            Hero h;
            h.CreateHero();
            int next_chamber_number, random_chamber;
            VirtualLocation* pointer;            
            Hallway a;
            Skirmish_Chamber ss;
            Event_Chamber E;
            Treasure_Chamber T;
            Special_Chamber SC;
            bool Alive = true;
            promise<int> p;
            future<int> f = p.get_future();
            thread game(gameTime, ref(Alive), ref(p));

            thread play(is_hero_alive, ref(h), ref(Alive));
            while (0 != 1)
            {

                system("CLS");
                h.ShowHero();
                pointer = &a;
                pointer->reroll(5);
                pointer->description();
                next_chamber_number = a.go_next();
                system("CLS");
                h.ShowHero();
                random_chamber = rand() % 10;
                next_chamber_number += random_chamber;
                if (next_chamber_number < 4)
                {
                    pointer = &T;
                }
                if (next_chamber_number >= 4 && next_chamber_number <= 6)
                {
                    pointer = &E;
                }
                if (next_chamber_number > 6)
                {
                    pointer = &ss;
                }
                if (h.TotalChambers % 10 == 0 && h.TotalChambers != 0)
                {           
                    pointer = &SC;
                    pointer->reroll(4);
                }
                pointer->description();
                pointer->player_action(h);
                if (Alive == false) break;
                h.TotalChambers++;
                pointer->reroll(5);
                ss.leavechamber();
            }
            game.join();
            play.join();
          
            h.Endgame();
            system("CLS");
            cout << "Czas Twojej gry wyniósł " << f.get() << " sekund" << endl;
            cout << "naciśnij enter by kontynuować" << endl;
            cin.ignore();
            cin.ignore();
            break;
        }


        case 2:
        {
            Howtoplay();
            break;
        }
        case 3:
        {
            break;
        }      
        }
    }
}
