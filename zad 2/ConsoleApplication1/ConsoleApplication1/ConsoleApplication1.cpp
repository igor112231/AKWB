#include <iostream>
#include <fstream>
#include <string>
#include <vector>


using namespace std;

const int MAX_SIZE = 20;

int main()
{
    int adjMatrix[MAX_SIZE][MAX_SIZE];
    int size;
    bool conjugate = 1;
    bool onegraf = 1;
    string FilePath = "sprz.txt";
    string Line;
    ifstream InputFile(FilePath);

    if (!InputFile.is_open()) {
        cerr << "Error opening file: " << FilePath << endl;
        return 1;
    }

    //size;
    getline(InputFile, Line);
    size = stoi(Line);
    cout << size << endl;
    string stemp;

    //create matrix
    for (int i = 0; i < size; i++) {
        getline(InputFile, Line);
        cout << i << ": ";
        for (int j = 0; j < size; j++) {
            stemp = Line[j];
            adjMatrix[i][j] = stoi(stemp);
            cout << Line[j] << " ";
        }
        cout << endl;

    }
    InputFile.close();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            cout << adjMatrix[i][j];
        }
        cout << endl;
    }

    //sprawdzenie czy 1-graf
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (adjMatrix[i][j] > 1) {
                onegraf = 0;
                cout << "1-graf=0" << endl;
            }
        }
    }

    //sprawdzenie czy sprzezony
    bool match = 0, mismatch = 0, check_conj = 1;
    if (onegraf == 1) {
        for (int i = 0; i < size - 1; i++) {
            for (int k = i+1; k < size - 1; k++) {
                for (int j = 0; j < size - 1; j++) {
                    if (adjMatrix[i][j] != adjMatrix[k][j] && (adjMatrix[i][j] == 1 || adjMatrix[k][j] == 1)) {
                        mismatch = 1;
                    }
                    else if (adjMatrix[i][j] == adjMatrix[k][j] && adjMatrix[k][j] == 1) {
                        match = 1;
                    }
                }
                if (match == mismatch && (match == 1 || mismatch == 1)) {
                    check_conj = 0;
                    cout << "graf jest niesprzezony" << endl;
                    return 0;
                }
                match = 0;
                mismatch = 0;

            }
        }
    }
    //sprawdzenie czy liniowy
    bool check_linear = 1;
    if (check_conj == 1 && onegraf == 1)
    {
        cout << "sprz" << endl;

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (adjMatrix[i][j] == 1 && i != j) {
                    for (int k = j + 1; k < size - 1; k++) {
                        if (adjMatrix[k][j] == 1 && k != j) {         //pierwszy graf, występuje przy takich warunkach: adjMatrix[i][j]=1&&adjMatrix[k][j]=1&&adjMatrix[l][i]=1&&adjMatrix[l][k]
                            for (int l = 0; l < size - 1; l++) {
                                if (adjMatrix[l][i] == 1 && adjMatrix[l][k] == 1 && i != k) {
                                   // cout << l + 1 << " " << i + 1 << " " << k + 1 << endl;
                                    check_linear = 0;
                                }
                            }
                            if (adjMatrix[k][j] == 1 && adjMatrix[i][j] == 1 && i != k) {           //drugi graf,  występuje przy takich warunkach: adjMatrix[i][j]=1&&adjMatrix[k][j]&&adjMatrix[j][k]&&adjMatrix[j][i]
                                check_linear = 0;
                                //cout << "drugi graf" << endl;
                            }
                        }
                        
                    }
                }
                if (adjMatrix[i][i] == 1 && adjMatrix[j][j] == 1 && adjMatrix[i][j] == 1 && adjMatrix[j][i] == 1) {             //trzeci graf,  występuje przy takich warunkach: adjMatrix[i][i]=1&&adjMatrix[j][j]=1&&adjMatrix[i][j]=1&&adjMatrix[j][i]==1
                    check_linear = 0;
                    //cout << "trzeci graf" << endl;
                }
            }
        }
        if (check_linear == 0) {
            cout << "graf jest nieliniowy" << endl;
        }
        if (check_linear == 1) {
            cout << "graf jest liniowy" << endl;
        }
    }

    //transformacja
    int counter = 1;
    vector<vector<int>> helper_vector;      //tablica wierzchołków zamieniona na rozdzielne łuki

    for (int i = 0; i < size; i++) {
        helper_vector.push_back({0, 0});        
        //counter++;
    }
    /*for (const auto& array : helper_vector) {
        for (int element : array) {
            cout << element << " ";
        }
        cout << endl;
    }*/


    for (int i = 0; i < helper_vector.size(); i++) {
        for (int j = 0; j < 2; j++) {
            if (helper_vector[i][j] == 0)
            {
                helper_vector[i][j] = counter;
                counter++;
            }
        }

        for (int k = 0; k < helper_vector.size(); k++) {
            if (adjMatrix[i][k] == 1) {
                
                helper_vector[k][1] = helper_vector[i][0];
            }
        } 

        for (int y = 0; y < helper_vector.size(); y++) {
            if (adjMatrix[y][i] == 1) {
                helper_vector[y][0] = helper_vector[i][1];
                //cout << endl << "i, y" << i << " " << y << endl;
            }
        } // y
    } // i

    for (const auto& array : helper_vector) {
        for (int element : array) {
            cout << element << " ";
        }
        std::cout << std::endl;
    }

    // uporządkowanie
    bool found = 0;
    int smallest_needed=100;
    for (int i = 0; i<helper_vector.size(); i++) {
        for (int j = i; j < helper_vector.size(); j++) {
            if (helper_vector[j][0] == i || helper_vector[j][1] == i) {
                found = 1;
                //smallest_needed = i + 1;
                break;
            }
        }
        if (found == 0) {
            for (int j = 0; j < helper_vector.size(); j++) {            //znalezienie najmniejszej nieuporzadkowanej wartosci
                if (helper_vector[j][0] >= i && helper_vector[j][0] < smallest_needed) {
                    smallest_needed = helper_vector[j][0];
                }
                if (helper_vector[j][1] >= i && helper_vector[j][1] < smallest_needed) {
                    smallest_needed = helper_vector[j][1];
                }
               // cout <<"sm "<< j << " " << smallest_needed << endl;
            }
            for (int j = 0; j < helper_vector.size(); j++) {
                if (helper_vector[j][0] == smallest_needed) {
                    //cout << "im in " << j << endl;
                    helper_vector[j][0] = i;
                }
                if (helper_vector[j][1] == smallest_needed) {
                   // cout << "hp " << helper_vector[j][1] << " sm " << smallest_needed <<" i "<<i<<" j "<< j << endl;
                    helper_vector[j][1] = i;  
                   // cout << "hp " << helper_vector[j][1] << endl;
                }
            }
        }
        smallest_needed = 100;
        //cout << endl << "found " << i << found << endl;
        found = 0;
    }
    cout << endl << "wynik porz" << endl;
    int new_size = 0;
    for (const auto& array : helper_vector) {
        for (int element : array) {
            cout << element << " ";
            if (element > new_size) {
                new_size = element;
            }
        }
        cout << endl;
    }
    vector<vector<int>> orgMatrix(new_size+1, vector<int> (new_size+1));

    for (const auto& array : orgMatrix) {
        for (int element : array) {
            element = 0;
        }
    }

    for (int i = 0; i < helper_vector.size(); i++) {
        orgMatrix[helper_vector[i][1]][helper_vector[i][0]]++;
    }
    for (const auto& array : orgMatrix) {
        for (int element : array) {
            cout << element << " ";
        }
        cout << endl;
    }

    string filePath = "output.txt";
    ofstream outputFile(filePath);
    if (outputFile.is_open()) { 
        outputFile << new_size + 1 << "\n";

        for (const auto& array : orgMatrix) {
            for (int element : array) {
                outputFile << element;
            }
            outputFile << "\n";
        }
    }
    else {
        cerr << "Error opening file: " << filePath << endl;
        return 1;
    }


}
