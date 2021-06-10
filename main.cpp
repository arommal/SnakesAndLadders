/*
    Snakes and Ladders Board Game
    Design and Analysis of Algorithms - D
    Rosa Valentine Lammora - 05111840000035
    Salsabila Harlen - 05111840000127
*/

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int breakpoint, boardSize, numOfLadders, numOfSnakes, a, b;

/* Function to print board */
void printBoard(vector< list<int> > adj, vector< list<int> > temp, int curpos) {
    int i, val, counter = 0, zig = 1;

    for(i = adj.size()-1; i > 0; i--) {
        /*
            'val' = the value of block to be printed
            'counter' = the value of the current column
            'zig' = 1 if the current row is printing forwards, -1 if the current row is printing backwards
            'curpos' = your current location
        */

        if (zig == 1)
            val = i;
        else if (zig == -1)
            val = i - (breakpoint - 1 - (2 * (counter)));

        if (val == curpos)  cout << "<" << val << ">";
        else    cout << val;

        counter++;

        if(val != temp[val].back())
            cout << "(" << temp[val].back() << ")";

        if(counter == breakpoint) {
            cout << endl;
            zig *= -1;
            counter = 0;
        } else {
            cout << "\t";
        }
    }
    cout << endl;
}

/* Function to call the print function for the sequence of ideal positions */
void printIteration(vector< list<int> > adj, vector< list<int> > temp, int parent[], int dest) {
    if(parent[dest] == -1) {
        printBoard(adj, temp, dest);
    } else {
        printIteration(adj, temp, parent, parent[dest]);
        // printBoard(adj, temp, dest);
    }
}

/* Function to replace adjacency list of the 6 preceding blocks */
void replacePreceding(vector< list<int> >&adj, vector< list<int> >&temp, int oldVal, int newVal) {
    int precede = oldVal - 1;

    temp[oldVal].pop_back();
    temp[oldVal].push_back(newVal);

    adj[oldVal].clear();

    for(precede; precede >= 0 && precede >= oldVal-6; --precede) {
        replace(adj[precede].begin(), adj[precede].end(), oldVal, newVal);
    }
}

/* Function to traverse the board */
void BFS(vector< list<int> > adj, int parent[], int level[], int start)
{
    list<int>::iterator itr;
    list<int> queue; 

    level[start] = 0;
    queue.push_back(start);
    
    while (!queue.empty()) {
        int newVertex = queue.front();
 
        itr = adj[newVertex].begin();
 
        while (itr != adj[newVertex].end()) {
            if (level[*itr] == -1) {
                level[*itr] = level[newVertex] + 1;
                parent[*itr] = newVertex;
                queue.push_back(*itr);              
            }
            ++itr;
        }

        queue.pop_front();
    }
}

int main() {
    cout << "Enter width of board" << endl;
    cout << "Recommended Width: 10" << endl;
    cin >> breakpoint;
    boardSize = breakpoint * breakpoint;

    vector< list<int> >adj(boardSize+1);
    vector< list<int> >temp(boardSize+1);

    /*
        'adj' = stores original board and its 6 forward steps as a list
        'temp' = stores a single value (either the block number if it is a normal block or the snake/ladder destination if it is not)
    */

    cout<< "You will be making a " << breakpoint << " x " << breakpoint << " board with " << boardSize << " blocks" << endl;

    for(int i = 1; i <= boardSize; i++) {
        for(int j = i+1; j <= i+6 && j <= boardSize; ++j) {
            adj[i].push_back(j);
        }
        temp[i].push_back(i);
    }

    // Ladders
    cout << endl << "Enter number of ladders" << endl;
    cin >> numOfLadders;

    cout << endl << "Enter ladder routes" << endl;

    for(int i = 1; i <=numOfLadders; i++) {
        cout << "- ";
        cin >> a >> b;
        replacePreceding(adj, temp, a, b);
    }
    
    // Snakes
    cout << endl << "Enter number of snakes" << endl;
    cin >> numOfSnakes;

    cout << endl << "Enter snake routes" << endl;

    for(int i = 1; i <= numOfSnakes; i++) {
        cout << "- ";
        cin >> a >> b;
        replacePreceding(adj, temp, a, b);
    }
    
    cout << endl << "Initial board" << endl;
    printBoard(adj, temp, 1);

    int parent[boardSize + 1];
    int level[boardSize + 1];

    // Initialising our arrays
    for (int i = 1; i <= boardSize; i++) {
        parent[i] = -1;
        level[i] = -1;
    }
    
    BFS(adj, parent, level, 1);

    printIteration(adj, temp, parent, boardSize);

    cout << "Minimum moves: " << level[boardSize];
}