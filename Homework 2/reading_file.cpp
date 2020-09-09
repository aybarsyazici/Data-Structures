#include <iostream>
#include <fstream>
using namespace std;


int main(){
    ifstream in_file;
    in_file.open("a.txt");
    string word;
    while(in_file >> word){
        cout << word << "\t";
    }
}