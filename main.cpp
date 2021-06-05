#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

void printBoard(vector< list<int> > adj) {}

int main() {
    int boardSize, numOfLadders, numOfSnakes, a, b;
    cout << "Enter size of board" << endl;
    cin >> boardSize;

    vector< list<int> > adj(boardSize);

    for(int i=1; i<=boardSize; i++) {
        for(int j=1+1; j<=i+6 && j<=boardSize; j++) {
            adj[i].push_back(j);
        }
    }

    // Ladders
    cout << endl << "Enter number of ladders" << endl;
    cin >> numOfLadders;

    cout << endl << "Enter ladder routes" << endl;

    for(int i=1; i<=numOfLadders; i++) {
        cout << "- ";
        cin >> a >> b;
    }
    
    // Snakes
    cout << endl << "Enter number of snakes" << endl;
    cin >> numOfSnakes;

    cout << endl << "Enter snake routes" << endl;

    for(int i=1; i<=numOfSnakes; i++) {
        cout << "- ";
        cin >> a >> b;
    }

    printBoard(adj);
}