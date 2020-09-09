#include <iostream>
#include <string>
using namespace std;


int main(){
    string string_1 = "Story";
    string string_2 = "S";
    cout << "Comparing string 1 with string 2... \n";
    if(string_1.compare(string_2) == 1){
        cout << string_2 << " comes first...\n";
    }
    else if(string_1.compare(string_2) == -1){
        cout << string_1 << " comes first...\n";
    }
    else if(string_1.compare(string_2) == 0){
        cout << "They are the same." << endl;
    }
    cout <<string_1.compare(string_2);
}