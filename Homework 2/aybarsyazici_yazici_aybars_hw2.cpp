#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "BST.h"
using namespace std;


int main()
{
    
    cout << "Enter number of input files: ";
    int iteration, iteration_2 = 1;
    cin >> iteration;
    vector<string> filenames;
    while(iteration_2 != iteration+1){
        cout << "Enter " << iteration_2 <<  ". file name: ";
        string temp_name;
        cin >> temp_name;
        filenames.push_back(temp_name);
        iteration_2++;
    }
    ifstream in_file; 
    BinarySearchTree<WordItem> object;//Creating the tree.
	for (int i = 0; i < filenames.size(); i++) {
        //cout << "Arrived here2.\n";
		string file_name = filenames[i];
        in_file.open(file_name);
        //cout << "filename is " << filenames[i] << endl;
        string word;
        while(in_file >> word){
            //cout << "word is " << word << endl;
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            WordItem* insert_ptr = new WordItem(word,filenames[i]);
            //cout << "Trying to insert..." << endl; 
            if(object.insert_in_tree(*insert_ptr)==true){
                //cout << "OBJECT WAS ALREADY IN THE TREE!!!\n";
                insert_ptr = object.search_in_tree(*insert_ptr);
                insert_ptr->update(filenames[i]);
            }
            //cout << "Insert complete..." << endl;
        }
        in_file.close();
    }/*
	if (object.isEmpty()) {
		cout << "The tree is empty\n";
	}
	else {
		cout << "The tree is NOT empty\n";
	}*/
	//WordItem* print_ptr = object.return_root();
	//object.PrintTree(print_ptr);
    string search_word;
    cout << endl;
    cin.clear();
    cin.sync();
    cout << "Enter queried words in one line: ";
    getline(cin, search_word);
    string buffer;
    stringstream ss(search_word);
    vector<WordItem*> ptr_array;
	int our_size = 0;
    while(ss >> buffer){
        //cout << "BUFFER IS " << buffer<< endl;
        transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
        WordItem* search_word_ptr = new WordItem(buffer,"a.txt");
        WordItem* result_ptr = object.search_in_tree(*search_word_ptr);
        if(result_ptr!=nullptr){
            ptr_array.push_back(result_ptr);
        }
		our_size++;
    }
    if(ptr_array.size() == 0){
        cout << "No document contains the given query";
    }
    /*
    for(int i = 0; i < ptr_array.size(); i++){
        cout << ptr_array[i]->element() << " has been found in: ";
        for(int j = 0; j < ptr_array[i]->document_names.size(); j++){
            cout << ptr_array[i]->document_names[j] << " " << ptr_array[i]->howmany[j] << " times,  ";
        }
        cout << endl;
    }*/
    int output_int = 0;
    for(int i = 0; i < filenames.size(); i++){
        bool first_time = true;
        bool nothing_found = true;
		int counter_int = 0;
        for(int j = 0; j < ptr_array.size(; j++){
            for(int z = 0; z < ptr_array[j]->document_names.size();z++){
                if(filenames[i]==ptr_array[j]->document_names[z] && first_time==true){
                    cout << "in Document " << filenames[i] << ", " << ptr_array[j]->element() << " found " << ptr_array[j]->howmany[z] << " times";
                    first_time = false;
                    nothing_found = false;
					counter_int++;
                    break;
                }
                else if(filenames[i]==ptr_array[j]->document_names[z] && first_time==false){
                    cout << ", " << ptr_array[j]->element() << " found " << ptr_array[j]->howmany[z] << " times";
					counter_int++;
                    nothing_found = false;
                }
            }
        }
        if(nothing_found == false){
            cout << ".\n";
			output_int++;
        }
    }
    return 0;
}