#ifndef PERSONPOOL_H
#define PERSONPOOL_H
#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define MAXSUPPL 100

using namespace std;

//users data
class User
{
public:
    string name, lastname, city;
    int debt, weight;

    virtual void generateData();
};

//mask shape for supervisors
enum MaskShape {Square, Triangle, Circle};

//supervisors extra data
class Supervisor: public User
{
public:
    MaskShape maskShape;

    int supPL[MAXSUPPL], numSupPl = 0;
    float prize = 0;
};

//players extra data
class Player: public User
{
public:
    int NoPlayer, SupIndex, randno = 0;
    bool alive = true;

    void AssignRandomNo()
    {
        int l = 50, u = 100;

        this->randno = (rand() % (u - l + 1)) + l;
    }
};

class PersonPool
{
public:
    Supervisor* supervisors = nullptr;
    Player* players = nullptr;

    int nopl, nosup;

    PersonPool(int nopl, int nosup);
    ~PersonPool();

    void EliminatePlayer(int PlayerNo)
    {
        this->players[PlayerNo].alive = false;
    }

    void PrintAlivePlayers()
    {
        cout << "Alive players: " << endl;
        for(int i = 0; i < nopl; i++)
        {
            if(this->players[i].alive)
                cout << this->players[i].NoPlayer << " ";
        }
        cout << endl;

    }

    int GetAliveNo()
    {
        int sum = 0;

        for(int i = 0; i < nopl; i++)
            if(this->players[i].alive)
                sum ++;
        return sum;
    }

};

class Team
{
public:
    int nopl, *players = nullptr;
    PersonPool* persPool = nullptr;

    void InitTeam(int maxNopl, PersonPool *pp)
    {
        players = new int[maxNopl];
        this->persPool = pp;
        this->nopl = 0;
    }

    ~Team()
    {
        delete[] players;
    }

    void AddPlayer(int plIndex)
    {
        this->players[this->nopl++] = plIndex;
    }

    void EliminateTeam()
    {
        for(int i = 0; i < nopl; i++)
            this->persPool->EliminatePlayer(this->players[i]);
    }

    float GetWeight()
    {
        float sum = 0;
        for(int i = 0; i < nopl; i++)
            sum += this->persPool->players[this->players[i]].weight;
        return sum;
    }

    void PrintTeam()
    {
        for(int i = 0; i < nopl; i++)
            cout << this->players[i] << " ";
        cout << endl;
    }
};

enum Genken {Rock, Paper, Scissors};
#endif // PERSONPOOL_H
