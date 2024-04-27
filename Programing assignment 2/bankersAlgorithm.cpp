//bankersProblem.cpp
//this program is designed to evaluate process allocation and determine if the system is safe or not
//Matthew Crosby
//4/26/2024


#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int NUM_PROCESSES = 5;
const int NUM_RESOURCES = 3;

vector<int> available(NUM_RESOURCES);
vector<vector<int>> maximum(NUM_PROCESSES, vector<int>(NUM_RESOURCES));
vector<vector<int>> allocation(NUM_PROCESSES, vector<int>(NUM_RESOURCES));
vector<vector<int>> need(NUM_PROCESSES, vector<int>(NUM_RESOURCES));

vector<int> safeSequence;

// Read data from input file
void readInput(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        exit(1);
    }

    // Read available resources
    for (int i = 0; i < NUM_RESOURCES; ++i) {
        file >> available[i];
    }

    // Read allocation matrix
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            file >> allocation[i][j];
        }
    }

    // Read maximum matrix
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        for (int j = 0; j < NUM_RESOURCES; ++j) {
            file >> maximum[i][j];
            need[i][j] = maximum[i][j] - allocation[i][j];
        }
    }

    file.close();
}

// Find if system is in safe state
bool isSafe() {
    vector<bool> finish(NUM_PROCESSES, false);
    vector<int> work = available;

    int count = 0;
    while (count < NUM_PROCESSES) {
        bool found = false;
        for (int i = 0; i < NUM_PROCESSES; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < NUM_RESOURCES; ++j) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < NUM_RESOURCES; ++j) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finish[i] = true;
                    ++count;
                    found = true;
                }
            }
        }
        if (!found)
            break;
    }
    return count == NUM_PROCESSES;
}

int main() {
    readInput("input.txt");

    if (isSafe()) {
        cout << "System is in a safe state." << endl;
        cout << "Safe Sequence: ";
        for (int i = 0; i < safeSequence.size(); ++i) {
            cout << "P" << safeSequence[i];
            if (i != safeSequence.size() - 1)
                cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "System is not in a safe state." << endl;
    }

    return 0;
}
