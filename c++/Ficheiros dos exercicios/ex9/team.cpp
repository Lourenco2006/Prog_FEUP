#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

struct Player {
    int number;
    string name;
    double pointsPerGame;
};

void insertFromCSV(const string&, vector<Player>&);
void printContent(const vector<Player>& );

int main() {
    vector<Player> players;
    insertFromCSV("players.txt", players);
    printContent(players);
    return 0;
}

void insertFromCSV(const string& filename, vector<Player>& players)
{
    /* Exercise 9a */
}

void printContent(const vector<Player>& players)
{    
    /* Exercise 9b */
}