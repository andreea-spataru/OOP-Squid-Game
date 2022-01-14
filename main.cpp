#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <random>
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include "PersonPool.h"

using namespace std;

// first game function - Red Light Green Light
void FirstGame(PersonPool &pp)
{
    for(int i = 1; i < pp.nopl; i += 2)
    {
        pp.EliminatePlayer(i);
    }

}

// second game function - Tug of War
void SecondGame(PersonPool &pp)
{
    Team t[4];

    int n = pp.GetAliveNo(); // number of alive players
    int PlPerTeam = n / 4; // number of players for each of the 4 teams

    cout << "Alive players:" << n << "\n" << endl;

    int i = 0;

    for(int j = 0; j < 4; j++)
    {
        t[j].InitTeam(n, &pp);
        // add players until it makes the team
        while(t[j].nopl < PlPerTeam)
        {
            if(pp.players[i].alive)
                t[j].AddPlayer(i);
            i++;

        }
        cout << "Team " << j + 1 << ":" << endl;
        cout << "Number of players: " << t[j].nopl << endl;
        cout << "Players index: ";
        t[j].PrintTeam();
        cout << "Weight: " << t[j].GetWeight() << endl;
        cout << "\n";
    }

//elimination of the team with less weight
    for(int i = 0; i < 4; i += 2)
    {
        if(t[i].GetWeight() < t[i + 1].GetWeight())
            t[i].EliminateTeam();
        else
            t[i + 1].EliminateTeam();
    }
}

// third game function - Marbles
void ThirdGame(PersonPool &pp)
{
    Team t[20];

    int m = pp.GetAliveNo(), j; // m = number of alive players
    int PlperTeam = 2; // number of players for each of the teams

    cout << "Alive players: " << m << "\n" << endl;

    int i = 0;

    for(j = 0; i < pp.nopl; j++)
    {
        t[j].InitTeam(m, &pp);

        while(t[j].nopl < PlperTeam && i < pp.nopl)
        {
            if(pp.players[i].alive)
                t[j].AddPlayer(i);
            i++;

        }
        cout << "Team " << j + 1 << ":" << endl;
        cout << "Number of players: " << t[j].nopl << endl;
        cout << "Players index: ";
        t[j].PrintTeam();

        cout << "Random number for each player is: ";
        for(int k = 0; k < t[j].nopl; k++)
        {
            pp.players[t[j].players[k]].AssignRandomNo();
            cout << pp.players[t[j].players[k]].randno << " ";
        }

        cout << "\n\n";
    }

    int noteams = j;

    for(j = 0; j < noteams; j++)
    {
        if(t[j].nopl >= PlperTeam)
        {
            if(pp.players[t[j].players[0]].randno < pp.players[t[j].players[1]].randno)
                pp.EliminatePlayer(t[j].players[1]);
            else
                pp.EliminatePlayer(t[j].players[0]);
        }
    }
}

// fourth game function - Genken
void FourthGame(PersonPool &pp)
{
    int i, fpi = -1, spi = -1, k = 0;

    while(pp.GetAliveNo() > 1)
    {

        for(i = pp.nopl - 1; i >= 0; i--)
        {
            if(pp.players[i].alive)
            {
                if(fpi < 0)
                    fpi = i;
                else
                {
                    spi = i;

                    while(true)
                    {
                        int fpc, spc;

                        fpc = (Genken)(rand() % 3);
                        spc = (Genken)(rand() % 3);

                        if((fpc + 1) % 3 == spc)
                        {
                            pp.EliminatePlayer(fpi);
                            break;
                        }
                        if((spc + 1) % 3 == fpc)
                        {
                            pp.EliminatePlayer(spi);
                            break;
                        }
                    }
                    fpi = -1;
                    spi = -1;
                }
            }
        }

        cout << "Round:" << k + 1 << endl;
        pp.PrintAlivePlayers();
        k++;
    }
}

void Reward(PersonPool &pp)
{
    int winner = 0, i, j, tmp;
    float winnerPrize = 0;

    for(i = 0; i < pp.nopl; i++)
    {
        if(pp.players[i].alive)
            winner = i;
        else
            winnerPrize += pp.players[i].debt;
    }
    cout << "\nThe winner is number: " << winner + 1 << endl;
    cout << "The winner's prize is: " << winnerPrize << "\n" << endl;

    // each supervisor's prize
    for(i = 0; i < pp.nosup; i++)
    {
        for(j = 0; j < pp.supervisors[i].numSupPl; j++)
        {
            if(!pp.players[pp.supervisors[i].supPL[j]].alive)
                pp.supervisors[i].prize += pp.players[pp.supervisors[i].supPL[j]].debt;
            else
            {
                pp.supervisors[i].prize = pp.players[pp.supervisors[i].supPL[j]].debt * 10;
                break;
            }
        }
        pp.supervisors[i].prize -= pp.supervisors[i].debt;
        cout << "Supervisor number " << i + 1 << " won: " << pp.supervisors[i].prize << endl;
    }

    // the team of supervisors with the most money
    int supWinnerNo = 0;

    for(i = 0; i < pp.nosup; i++)
    {
        if(pp.supervisors[0].prize < pp.supervisors[i].prize)
        {
            pp.supervisors[0].prize = pp.supervisors[i].prize;
            supWinnerNo = i;
        }
    }

    cout << "\nThe team of supervisors with the most money is supervisor number " << supWinnerNo + 1 << " with " << pp.supervisors[0].prize << "." << endl;

    cout << endl;

    // display the amount of money in descending order
    cout << "Descending order of the amount of money: " << endl;

    for(i = 0; i < pp.nosup; i++)
    {
        for(j = i + 1; j < pp.nosup; j++)
        {
            if(pp.supervisors[i].prize < pp.supervisors[j].prize)
            {
                tmp = pp.supervisors[i].prize;
                pp.supervisors[i].prize = pp.supervisors[j].prize;
                pp.supervisors[j].prize = tmp;
            }
        }
        cout << pp.supervisors[i].prize << endl;
    }
}

int main()
{
    srand(time(NULL));

    PersonPool persPool(99, 9);

    cout << "\n---------------- First game - Red Light Green Light -------------\n" << endl;
    FirstGame(persPool);
    persPool.PrintAlivePlayers();

    cout << "\n---------------- Second Game - Tug of War -----------------------\n" <<  endl;
    SecondGame(persPool);
    persPool.PrintAlivePlayers();

    cout << "\n---------------- Third Game - Marbles ---------------------------\n" << endl;
    ThirdGame(persPool);
    persPool.PrintAlivePlayers();

    cout << "\n---------------- Fourth Game - Genken ---------------------------\n" << endl;
    FourthGame(persPool);
    persPool.PrintAlivePlayers();

    Reward(persPool);

    return 0;
}
