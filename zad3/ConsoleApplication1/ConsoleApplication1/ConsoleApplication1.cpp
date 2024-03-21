#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<sstream>
#include<cmath>
#include<algorithm>


using namespace std;

int main()
{
    ifstream plik_fasta, plik_qual;
    stringstream ss;
    string linia_fasta, linia_qual, do_wektora , temp;
    vector <string> fasta;
    vector<vector<int>> qual;
    vector<int> temp_qual;
    int licznik = 0, found;

    plik_fasta.open("fasta.txt", ios::in | ios::out);
    plik_qual.open("qual.txt", ios::in | ios::out);
    if (!plik_fasta.good() == true && !plik_qual.good() == true)
    {
        cout << "nie ok" << endl;
        exit(0);
    }
    else
    {
        cout << "plik otwarty" << endl;
    }
    int znacznik = 0;
    //temp_qual.push_back(100);
    while (getline(plik_fasta, linia_fasta))
    {
        getline(plik_qual, linia_qual);
        //cout<<linia_qual<<endl;
        //cout<<linia_qual<<endl;
        if (linia_fasta[0] == '>')
        {
            if (znacznik == 0)
            {
                znacznik = 1;
                continue;
            }
            fasta.push_back(do_wektora);
            qual.push_back(temp_qual);
            temp_qual.clear();
            //do_wektora = "x";
            licznik++;
            temp_qual.push_back(100);
        }
        else
        {
            do_wektora += linia_fasta;
            ss << linia_qual;
            while (!ss.eof())
            {
                ss >> temp;
                //cout<<temp<<endl;
                if (stringstream(temp) >> found)
                {
                    temp_qual.push_back(found);
                    //cout<<found<< " ";
                }
                temp = "";
            }
            //cout<<endl;
        }
        ss.clear();
    }
    if (temp_qual.size() != do_wektora.size())
    {
        cout << "zły rozmiar" << endl;
        return 0;
    }
    fasta.push_back(do_wektora);
    qual.push_back(temp_qual);
    temp_qual.clear();

    for(int i=0; i<fasta.size();i++)
    {
        cout<<"i: "<<i<<" string: "<<fasta[i]<<endl;
        for(int j=0; j<qual[i].size();j++)
        {
            cout<<qual[i][j]<<" ";
        }
        cout<<endl;
    }

    int wiarygodnosc, wyciete = 0;
    cout << "Prosze podac prog wiarygodnosci?" << endl;
    cin >> wiarygodnosc;
    //wiarygodnosc=5;

    vector <string> new_fasta;
    vector<vector<int>> new_qual, old_position;
    vector <int> temp_old_position;


    for (int i = 0; i < fasta.size(); i++)          //usuwanie nukleotydow
    {
        temp = fasta[i];
        do_wektora = "";
        for (int j = 0; j < qual[i].size(); j++)
        {
            //cout<<"j: "<<j<<endl;
            if (qual[i][j] >= wiarygodnosc)
            {
                do_wektora += temp[j];
                temp_qual.push_back(qual[i][j]);
                temp_old_position.push_back(j);
            }
        }
        //cout<<"temp "<<temp<<endl;
        new_fasta.push_back(do_wektora);
        //cout<<"new fasta:  "<<new_fasta[i]<<endl;
        new_qual.push_back(temp_qual);
        old_position.push_back(temp_old_position);
        temp_qual.clear();
        temp_old_position.clear();
        //do_wektora.clear();
        cout << endl;
    }
    /*for(int i=0; i<new_fasta.size();i++)
    {
        cout<<"i: "<<i<<" string: "<<new_fasta[i]<<endl;
        for(int j=0; j<new_qual[i].size();j++)
        {
            cout<<new_qual[i][j]<<" ";
        }
        cout<<endl;
    }*/

    int dlugosc;
    string temp_fragment = "";
    vector<vector<string>> fragment;
    vector<string> tfragment;
    // vector<vector<int>> pozycja;
    cout << "Prosze podac dlugosc sekwencji" << endl;
    while (1)
    {
        cin >> dlugosc;
        if (dlugosc > 3 && dlugosc < 10)
        {
            break;
        }
        cout << "Prosze podac dlugosc z zakresu od 4 do 9" << endl;
    }
    //dlugosc=5;
    int max_vertices = 0;
    for (int i = 0; i < new_fasta.size(); i++)          //tworzenie fragmentow o padanej dlugosci
    {
        temp = new_fasta[i];
        // cout<<"i: "<<i<<endl;
        for (int j = 1; j < (new_qual[i].size() - dlugosc + 1); j++)
        {
            // cout<<"j: "<<j<<endl;
            for (int k = 0; k < dlugosc; k++)
            {
                // cout<<"k: "<<k<<endl;
                temp_fragment += temp[j + k];
                // cout<<temp_fragment<<endl;
            }
            tfragment.push_back(temp_fragment);
            temp_fragment = "";
            max_vertices++;
            //cout<<new_qual[i][j]<<endl;
        }
        fragment.push_back(tfragment);
        tfragment.clear();
    }

    /*for (int i = 0; i < new_fasta.size(); i++)
    {
        cout << "i: " << i << " string: " << new_fasta[i] << endl;
        for (int j = 0; j < fragment[i].size(); j++)
        {
            cout << fragment[i][j] << " ";
        }
        cout << endl;
    }*/

    int  nr1 = 0, nr2 = 0;
    vector<vector<int>> matrix(max_vertices + 1, vector<int>(max_vertices + 1));

    for (int i = 0; i < max_vertices; i++)
    {
        for (int j = 0; j < max_vertices; j++)
        {
            matrix[i][j] = 0;
        }
    }

    for (int i = 0; i < new_fasta.size(); i++)      //wypelnienie tablicy zawierającej wszystkie fragmenty
    {
        for (int j = 0; j < fragment[i].size(); j++)
        {
            nr1++;
            for (int k = 0; k < new_fasta.size(); k++)
            {
                for (int l = 0; l < fragment[k].size(); l++)
                {
                    nr2++;
                    if (k == i)
                    {
                        continue;
                    }
                    if ((old_position[i][j + 1] - old_position[k][l + 1]) > (dlugosc * 10))
                    {
                        continue;
                    }
                    if (fragment[i][j] == fragment[k][l])
                    {
                        //cout<<"fragment 1: "<< fragment[i][j]<<", fragment 2:"<<fragment[i][j]<<endl;
                        matrix[nr1][nr2] = 1;
                        matrix[nr2][nr1] = 1;
                    }
                }
            }
            nr2 = 0;
        }
    }
    /*for (int i=0;i<max_vertices;i++)
    {
        for(int j=0;j<max_vertices;j++)
        {
            if(matrix[i][j]==1)
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }*/
    vector<vector<float>> clique;
    vector<float> temp_clique;
    string stemp;
    int check = 0, niema = 0;
    nr1 = 0;
    nr2 = 0;
    float ftemp;
    for (int i = 0; i < new_fasta.size(); i++)          //szukanie kliki
    {
        //cout<<"i: "<<i<<endl;
        //cout<<"rozmiar: "<<fragment[i].size()<<endl;
        for (int j = 0; j < fragment[i].size(); j++)
        {
            //cout<<"j: "<<j<<endl;

            nr1++;
            ftemp = (float)j + ((float)i / 100);
            temp_clique.push_back(ftemp);
            for (int k = 0; k < new_fasta.size(); k++)
            {
                //cout<<"k: "<<k<<endl;
                for (int l = 0; l < fragment[k].size(); l++)
                {
                    //cout<<"l: "<<l<<endl;
                    nr2++;
                    if (check == 1 || niema == 1 || k == i)
                        continue;
                    //cout<<"fr: "<<fragment[i][j]<<endl;
                    //cout<<"fr: "<<fragment[k][l]<<endl;
                    if (matrix[nr1][nr2] == 1)
                    {
                        //cout<<stemp<<endl;
                        ftemp = (float)l + ((float)k / 100);
                        temp_clique.push_back(ftemp);
                        check = 1;
                        niema = 0;
                        //temp_clique.push_back()
                    }
                }
                if (temp_clique.size() != k + 1)
                {
                    niema = 1;
                    temp_clique.clear();

                }
                check = 0;
            }

            nr2 = 0;
            if (niema == 0)
            {
                clique.push_back(temp_clique);
            }
            niema = 0;
            temp_clique.clear();
        }
    }
    /*for (int i = 0; i < clique.size(); i++)
    {
        cout << "klika:";
        for (int j = 0; j < clique[i].size(); j++)
        {
            cout << " " << clique[i][j];
        }
        cout << endl;
    }*/

    int x, y;
    float whole, fractional;
    for (int i = 0; i < clique.size(); i++)
    {
        cout << "klika nr " << i + 1 << endl;
        for (int j = 0; j < clique[i].size(); j++)
        {
            fractional = modf(clique[i][j], &whole);
            fractional = round(fractional * 100);
            y = static_cast<int>(fractional);
            x = static_cast<int> (whole);

            //cout<<"x i y "<<whole<<" "<<fractional<<" klika: "<<clique[i][j]<<endl;
            cout << "sekwencja wejsciowa: " << y + 1 << " nr pozycji: " << x << endl;
        }
        cout << "sekwencja nukleotydowa: " << fragment[y][x] << endl;
    }

    //cout << "koniec" << endl;
}