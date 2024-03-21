#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<sstream>
#include<cmath>
#include<algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;


//k=maxind
void szukaj(vector <int> mapa, vector <int> fragmenty, int k, int ind, int* jest)
{

    if (ind == k)
    {
        int suma = 0;
        int pass = 0;

        for (int i = 0; i < fragmenty.size(); i++) {
            for (int l = 0; l < mapa.size(); l++)
            {
                for (int p = l; p < mapa.size(); p++)
                {
                    suma += fragmenty[mapa[p]];
                    if (find(fragmenty.begin(), fragmenty.end(), suma) == fragmenty.end())
                    {
                        pass=1;
                    }
                }
                suma = 0;
            }
        }
        cout << "finalna mapa: ";
        for (int i = 0; i < mapa.size(); i++)
        {
            cout << fragmenty[mapa[i]] << " ";
        }
        *jest = 1;
        cout << endl;
    }
    else
    {
        int pass = 0;
        for (int i = 0; i < fragmenty.size(); i++)
        {
            if (find(mapa.begin(), mapa.end(), i) == mapa.end())
            {
                mapa.push_back(i);
                int suma = 0;
                for (int l = 0; l < mapa.size() && pass == 0; l++)
                {
                    for (int p = l; p < mapa.size() && pass == 0; p++)
                    {
                        suma += fragmenty[mapa[p]];
                        if (find(fragmenty.begin(), fragmenty.end(), suma) == fragmenty.end())
                        {
                            pass = 1;
                        }
                    }
                    suma = 0;
                }
                if (pass == 1)
                {
                    mapa.pop_back();
                    if (fragmenty[i] == fragmenty[i + 1])
                    {
                        i++;
                    }
                }
                if (pass == 0)
                {
                    szukaj(mapa, fragmenty, k, ind + 1, jest);

                    if (*jest == 1)
                    {
                        return;
                    }
                    mapa.pop_back();
                }
                pass = 0;
            }
        }
    }
}

int main()
{
    string instancje, temp;
    stringstream ss;
    ifstream plik;
    int found;

    plik.open("instancje.txt", ios::in | ios::out);
    if (!plik.good() == true)
    {
        cout << "NIE OK" << endl;
        exit(0);
    }

    getline(plik, instancje);

    cout << instancje << endl;


    vector <int> fragmenty, mapa;

    ss << instancje;
    while (!ss.eof())
    {
        ss >> temp;

        if (stringstream(temp) >> found)
        {
            fragmenty.push_back(found);
        }
        temp = "";
    }

    int poprawna_liczba = 0, k = 0;
    while (fragmenty.size() > poprawna_liczba)
    {
        poprawna_liczba = ((k) * (k)+3 * (k)+2) / 2;
        cout << "K: " << k << " pop licz: " << poprawna_liczba << " fragmenty:" << fragmenty.size() << endl;
        if (poprawna_liczba == fragmenty.size())
            break;
        k++;
    }
    if (fragmenty.size() != poprawna_liczba)
    {
        cout << "k: " << k << endl;
        cout << "nieodpowiednia ilosc fragmentow";
        return 0;
    }
    cout << "k: " << k << endl;

    int max, prawiemax;
    if (fragmenty[0] < fragmenty[1])
    {
        prawiemax = fragmenty[0];
        max = fragmenty[1];
    }
    else {
        max = fragmenty[0];
        prawiemax = fragmenty[1];
    }
    for (int i = 2; i < fragmenty.size(); i++)
    {
        if (fragmenty[i] > max)
        {
            prawiemax = max;
            max = fragmenty[i];
        }
        if (fragmenty[i]<max && fragmenty[i]>prawiemax)
        {
            prawiemax = fragmenty[i];
        }
    }


    int pierwszy = max - prawiemax;
    for (int i = 0; i < fragmenty.size(); i++)
    {
        cout << "fragment: " << fragmenty[i] << endl;
        if (pierwszy == fragmenty[i])
        {
            mapa.push_back(i);
            break;
        }
    }

    cout << "max i prawie " << max << " " << prawiemax << endl;

    int jest = 0;
    auto start = high_resolution_clock::now();
    szukaj(mapa, fragmenty, k, 1, &jest);
    auto stop = high_resolution_clock::now();

    if (jest == 0)
    {
        cout << "informuje o braku rozwiazania" << endl;
    }
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "czas dzialania: " << duration.count() << endl;
}