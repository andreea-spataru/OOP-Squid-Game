#include "PersonPool.h"

using namespace std;

const int MAX = 26;

string printRandomStringName(int n) // random names generator
{
    char alphabet[MAX] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                           'h', 'i', 'j', 'k', 'l', 'm', 'n',
                           'o', 'p', 'q', 'r', 's', 't', 'u',
                           'v', 'w', 'x', 'y', 'z'
                         };

    string name = "";

    for (int i = 0; i < n; i++)
        name += alphabet[rand() % MAX];

    return name;
}

string printRandomStringLastame(int m) // random lastname generator
{
    char alph[MAX] = { 'z', 'y', 'c', 't', 'e', 'w', 'g',
                       'h', 'i', 'j', 'r', 'l', 'o', 'n',
                       'm', 'p', 'q', 'k', 's', 'd', 'u',
                       'v', 'f', 'x', 'b', 'a'
                     };

    string lastname = "";

    for (int i = 0; i < m; i++)
        lastname += alph[rand() % MAX];

    return lastname;
}

string printRandomCity (int x) // random cities name generator
{
    char alpha[MAX] = { 'm', 'y', 'c', 't', 'e', 'w', 'a',
                        'h', 'i', 'n', 'k', 'l', 'o', 'j',
                        'z', 'p', 'q', 'r', 's', 'd', 'u',
                        'v', 'f', 'x', 'b', 'g'
                      };

    string city = "";

    for (int i = 0; i < x; i++)
        city += alpha[rand() % MAX];

    return city;
}

void User::generateData()
{
    int n = 4, m = 5, x = 6;

    this->name = printRandomStringName(n);

    cout<<"Name: ";
    cout << this->name << endl;
// -------------------------------------------------------
    this->lastname = printRandomStringLastame(m);
    cout<<"Lastname: ";
    cout << this->lastname << endl;
// -------------------------------------------------------
    this->city = printRandomCity(x);
    cout<<"City: ";
    cout << this->city << endl;
// -------------------------------------------------------
    cout << "Debt: ";

    int lower = 10000, upper = 100000;

    this->debt = (rand() % (upper - lower + 1)) + lower;

    printf("%d\n", this->debt);
// -------------------------------------------------------
    cout << "Weight: ";

    int low = 50, upp = 100;

    this->weight = (rand() % (upp - low + 1)) + low;

    printf("%d\n", this->weight);
// -------------------------------------------------------

    cout << "-------------------------------------------------------" << endl;

}

//players and supervisors data
PersonPool::PersonPool(int nopl, int nosup)
{

    this->nopl = nopl;
    this->nosup = nosup;

    this->players = new Player[nopl];
    this->supervisors = new Supervisor[nosup];

    for(int i = 0; i < nopl; i++)
    {
        cout << "Player " << i + 1 << endl;

        this->players[i].generateData();
        this->players[i].NoPlayer = i + 1;
    }

    //mask shape for supervisors
    for(int i = 0; i < nosup; i++)
    {
        cout << "Supervisor "<< i+ 1 << endl;

        this->supervisors[i].maskShape = (MaskShape)(i / 3);

        cout << "Mask shape: " << this->supervisors[i].maskShape << endl;
        this->supervisors[i].generateData();
    }

    int plPerSup = nopl / nosup;

    for(int i = 0; i < nopl; i++)
    {
        int si = i / plPerSup;

        if(si >= nosup)
            si = nosup - 1;

        this->players[i].SupIndex = si;

        this->supervisors[si].supPL[this->supervisors[si].numSupPl++] = i; //adauga la capatul listei

    }

    cout << "Player supervisor index: ";

    for(int i = 0; i < nopl; i++)
        cout << this->players[i].SupIndex << " ";

    cout << endl << endl;

    //players divided into groups
    cout << "Supervisor player list: " << endl;

     for(int i = 0; i < nosup; i++)
     {
         cout << "Supervisor: " << i << " :";
         for(int j = 0; j < this->supervisors[i].numSupPl; j++)
            cout << this->supervisors[i].supPL[j] << " ";
         cout << endl;
     }

}

//destructor
PersonPool::~PersonPool()
{
    delete[] this->players;
    delete[] this->supervisors;

}

