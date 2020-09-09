#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include "HashTable.h"

using namespace std;


bool invalidChar (char & c) 
{
	if(!(c>=97 && c <123)){
		c = ' ';
	}
    //return !(c>=97 && c <122);  
	return false;
} 

void stripUnicode(string & str) 
{ 
    //str.erase(remove_if(str.begin(),str.end(), invalidChar), str.begin());  
	remove_if(str.begin(),str.end(), invalidChar);
}

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
	HashTable<WordItem> hash_object(53); //Creating the hash table.
	for (int i = 0; i < filenames.size(); i++) {
		string file_name = filenames[i];
		in_file.open(file_name);
		string word;
		while (in_file >> word) {
			transform(word.begin(), word.end(), word.begin(), ::tolower);
            stripUnicode(word);
            stringstream temp_iterator(word);
            string temp_string;
            while(temp_iterator >> temp_string){
			    WordItem* insert_ptr = new WordItem(temp_string, filenames[i]);
                WordItem* hash_insert_ptr = new WordItem(temp_string, filenames[i]);
			    if (object.insert_in_tree(*insert_ptr) == true) {
				    insert_ptr = object.search_in_tree(*insert_ptr);
				    insert_ptr->update(filenames[i]);
			    }
                if (hash_object.insert(*hash_insert_ptr) == true){
                    hash_insert_ptr = &hash_object.find(*hash_insert_ptr);
                    hash_insert_ptr->update(filenames[i]);
                }
            }
		}
		in_file.close(); 
	}
	cout << "\nAfter preprocessing, the unique word count is " << hash_object.currentSize << " Current load ratio is " << double(hash_object.currentSize)/hash_object.array.size() <<endl;

    string search_word;
    cout << endl;
    cin.clear();
    cin.sync();
    cout << "Enter queried words in one line: ";
    getline(cin, search_word);
    string buffer;
    stringstream ss(search_word);
    vector<WordItem*> ptr_array;
    vector<WordItem*> hash_ptr_array;
    vector<string> words_to_be_searched;
	int our_size = 0;
    while(ss >> buffer){ //Get the words to be searched from the user.
        //cout << "BUFFER IS " << buffer<< endl;
        transform(buffer.begin(), buffer.end(), buffer.begin(), ::tolower);
		stripUnicode(buffer);
		stringstream temp_iterator(buffer);
		string temp_string;
		while(temp_iterator >> temp_string){
			words_to_be_searched.push_back(temp_string); //Push them into a vector so we can use it to search both in BST and the Hash table.
			our_size++;
		}
    }
    int k = 500; //Repeat the search process
	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < k; i++)
	{
        ptr_array.clear(); //Clear the result vector before starting to search again.
        for(int j = 0; j < words_to_be_searched.size(); j++){ 
            WordItem* search_word_ptr = new WordItem(words_to_be_searched[j],"a.txt"); //Search in the tree.
            WordItem* result_ptr = object.search_in_tree(*search_word_ptr);
            if(result_ptr!=nullptr){
                ptr_array.push_back(result_ptr); //If found push into the result vector.
            }
        }
	}
	auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - start);
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
	{
        hash_ptr_array.clear();
        for(int j = 0; j < words_to_be_searched.size(); j++){
            WordItem* search_word_ptr = new WordItem(words_to_be_searched[j],"a.txt");
            WordItem* hash_result_ptr = &hash_object.find(*search_word_ptr); //Search in the hash table.
            if(hash_result_ptr != &hash_object.ITEM_NOT_FOUND){
                hash_ptr_array.push_back(hash_result_ptr); //If found, push into the result vector.
            }
        }
	}
	auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    //cout << "\nhash_ptr_array size is " << hash_ptr_array.size() << endl;
    //Print Tree results
    int output_int = 0;
    for(int i = 0; i < filenames.size(); i++){
        bool first_time = true;
        bool nothing_found = true;
		int counter_int = 0;
		string output_string = "";
        for(int j = 0; j < ptr_array.size(); j++){
            for(int z = 0; z < ptr_array[j]->document_names.size();z++){
                if(filenames[i]==ptr_array[j]->document_names[z] && first_time==true){
					output_string += "in Document " + filenames[i] + ", " + ptr_array[j]->element() + " found " + to_string(ptr_array[j]->howmany[z]) + " times";
                    //cout << "in Document " << filenames[i] << ", " << ptr_array[j]->element() << " found " << ptr_array[j]->howmany[z] << " times";
                    first_time = false;
                    nothing_found = false;
					counter_int++;
                    break;
                }
                else if(filenames[i]==ptr_array[j]->document_names[z] && first_time==false){
					output_string +=  ", " + ptr_array[j]->element() + " found " + to_string(ptr_array[j]->howmany[z]) + " times";
                    //cout << ", " << ptr_array[j]->element() << " found " << ptr_array[j]->howmany[z] << " times";
					counter_int++;
                    nothing_found = false;
                }
            }
        }
        if(nothing_found == false && counter_int == our_size){
            cout << output_string << ".\n";
			output_int++;
        }
    }
    if(output_int == 0){cout << "No document contains the given query\n";}
    //Print Hash Table results
    output_int = 0;
    for(int i = 0; i < filenames.size(); i++){
        bool first_time = true;
        bool nothing_found = true;
		int counter_int = 0;
		string output_string = "";
        for(int j = 0; j < hash_ptr_array.size(); j++){
            for(int z = 0; z < hash_ptr_array[j]->document_names.size();z++){
                if(filenames[i]==hash_ptr_array[j]->document_names[z] && first_time==true){
					output_string += "in Document " + filenames[i] + ", " + hash_ptr_array[j]->element() + " found " + to_string(hash_ptr_array[j]->howmany[z]) + " times";
                    //cout << "in Document " << filenames[i] << ", " << ptr_array[j]->element() << " found " << ptr_array[j]->howmany[z] << " times";
                    first_time = false;
                    nothing_found = false;
					counter_int++;
                    break;
                }
                else if(filenames[i]==hash_ptr_array[j]->document_names[z] && first_time==false){
					output_string +=  ", " + hash_ptr_array[j]->element() + " found " + to_string(hash_ptr_array[j]->howmany[z]) + " times";
                    //cout << ", " << ptr_array[j]->element() << " found " << ptr_array[j]->howmany[z] << " times";
					counter_int++;
                    nothing_found = false;
                }
            }
        }
        if(nothing_found == false && counter_int == our_size){
            cout << output_string << ".\n";
			output_int++;
        }
    }
    if(output_int == 0){cout << "No document contains the given query\n";}
    //Print the times...
    cout << "\nTime: " << BSTTime.count() / k << "\n";
    cout << "\nTime: " << HTTime.count() / k << "\n";
    cout << "Speed up: " << (double)BSTTime.count() / (double)HTTime.count() << "\n";
    return 0;
}