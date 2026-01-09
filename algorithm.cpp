#include <iostream>
#include <fstream>
using namespace std;

int main(){
    string word;
    ifstream file("input.txt");

    if (!file.is_open()) {
        cerr << "Error: Unable to open file" << endl;
        return 1;
    }
    while (file >> word) {
        cout << word << endl;
    }

    file.close();

    return 0;
}