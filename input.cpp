#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int getPosNum(){
    int positifNumber(-1);
    bool flag = positifNumber<=0;
    while(flag) {
        cout << "How much time until tests?(days) ";
        cin >> positifNumber;
        flag = positifNumber <= 0;
        if(flag){
            cout << "Duration must be positive" << endl;
        }
    }
    return positifNumber;
}

int main(){
    int dur = getPosNum();
    cout << dur;
    return 0;
}