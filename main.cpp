#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

int breakpoint, boardSize, numOfLadders, numOfSnakes, a, b;

void printBoard(vector< list<int> > adj, vector< list<int> > temp, int curpos) {
    int i, val, counter = 0, decrease = 1, zig = 1, id;

    for(i = adj.size()-1; i > 0; i--) {
        if (zig == 1) {
            val = i;
        } else if (zig == -1) {
            val = i - (breakpoint - 1 - (2 * (counter)));
        }

        if (val == curpos) {
            cout << "<" << val << ">";
        } else {
            cout << val;
        }

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

void printIteration(vector< list<int> > adj, vector< list<int> > temp, int parent[], int dest) {
    if(parent[dest] == -1) {
        // printBoard(adj, temp, dest);
        cout << dest << " -> " << endl;
    } else {
        printIteration(adj, temp, parent, parent[dest]);
        cout << dest << " -> " << endl;

        // printBoard(adj, temp, dest);
    }
}

vector< list<int> > replacePreceding(vector< list<int> >adj, vector< list<int> >temp, int oldVal, int newVal) {
    int precede = oldVal - 1;

    temp[oldVal].pop_back();
    temp[oldVal].push_back(newVal);

    for(precede; precede >= 0 && precede >= oldVal-6; precede--) {
        replace(adj[precede].begin(), adj[precede].end(), oldVal, newVal);
    }

    return temp;
}

void BFS(vector< list<int> > adj, int parent[], int level[], int start)
{
    list<int>::iterator itr;

    level[start] = 0;

    list<int> queue; 
    queue.push_back(start);
    
    while (!queue.empty()) 
    {
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

    cout<< "You will be making a " << breakpoint << " x " << breakpoint << " board" << endl;

    for(int i = 1; i <= boardSize; i++) {
        for(int j = i+1; j <= i+6 && j <= boardSize; j++) {
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
        temp = replacePreceding(adj, temp, a, b);
    }
    
    // Snakes
    cout << endl << "Enter number of snakes" << endl;
    cin >> numOfSnakes;

    cout << endl << "Enter snake routes" << endl;

    for(int i = 1; i <= numOfSnakes; i++) {
        cout << "- ";
        cin >> a >> b;
        temp = replacePreceding(adj, temp, a, b);
    }
    
    cout << endl << "Initial board" << endl;
    printBoard(adj, temp, 1);

    int parent[boardSize];
    int level[boardSize];

    // Initialising our arrays
    for (int i = 1; i <= boardSize; i++) {
        parent[i] = -1;
        level[i] = -1;
    }
    
    BFS(adj, parent, level, 1);

    printIteration(adj, temp, parent, boardSize);
    
}