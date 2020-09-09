#include "heap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main(){
    MinHeap<int> minh(500);
    MaxHeap<int> maxh(500);
    double CurrentMedian = 0;
    while(!cin.eof()){
        string fileName;
        cin.clear();
        cin.sync();
        cout << "Please enter the next file name that contains integer stream: ";
        getline(cin, fileName);
        cout << endl;
        int word;
        ifstream in_file;
        in_file.open(fileName);
        while(in_file >> word){
            if(maxh.isEmpty()){
                maxh.insert(word);
            }
            else{
                if(word < maxh.getTop() || word == maxh.getTop()){
					maxh.insert(word);
                    if(maxh.HeapSize() - minh.HeapSize() == 2){
                        int temp_word = maxh.deleteTop();
                        minh.insert(temp_word);
                    }
                }
                else{
					minh.insert(word);
                    if(minh.HeapSize() - maxh.HeapSize() == 2){
                        int temp_word = minh.deleteTop();
                        maxh.insert(temp_word);
                    }
                }
            }
        }
		if (cin.eof()) {
			break;
		}
        if(minh.HeapSize() < maxh.HeapSize()){
            CurrentMedian = maxh.getTop();
        }
        else if(minh.HeapSize() > maxh.HeapSize()){
            CurrentMedian = minh.getTop();
        }
        else{
            CurrentMedian = (double)minh.getTop() + (double)maxh.getTop();
            CurrentMedian /= 2;
        }
		cout << "current median: " << CurrentMedian << endl;
    }
}