#include <iostream>
#include "stack.h"
#include <fstream>
#include <cstdio>
#include <string>
using namespace std;

int main(){
    cout << "Please enter the input file name: ";
    Stack<linkNode*> object;
    string filename;
    cin >> filename;
    ifstream infile(filename);
    int x, y, z;
    int current_x = 0;
    int current_y = 0;
    linkNode* temp_ptr = nullptr;
    z = 0;
    while(infile >> x >> y){  
        //cout << "\nline number " << z << endl;
        linkNode* search_ptr = object.top();
        bool already_visited = false;
        while(search_ptr != nullptr){
            //cout << "Current value of search_ptr is " << search_ptr->value_string() << endl;
            if(search_ptr->x_value() == x && search_ptr->y_value() == y){
                already_visited = true;
                break;
            }
            search_ptr = search_ptr->prev;
        }
        if(already_visited == true){
            cout << "Time travel back to (" << x << ", " << y << ")\n";
            current_x = x;
            current_y = y;
			if (temp_ptr == nullptr) {
				temp_ptr = new linkNode(nullptr, nullptr, current_x, current_y, true);
			}
			else { 
				temp_ptr->next = new linkNode(nullptr, temp_ptr, current_x, current_y, true);
				temp_ptr = temp_ptr->next;
			}
			object.push(temp_ptr);
			//cout << "\n pushing: " << temp_ptr->value_string() << " to the stack. WITH TIMETRAVELED TRUE\n";
			continue;
        }
		cout << "Moving to (" << x << "," << y << ")\n";
        while(current_x != x){
            if(current_x < x){
                current_x++;
            }
            else{
                current_x--;
            }
            if(current_y == y && current_x && x){
                cout << "Arrived to (" << current_x << "," << current_y << ")\n";
            }
            else{
                cout << "(" << current_x << "," << current_y << ")\n";
            }
            if(temp_ptr == nullptr){
                temp_ptr = new linkNode(nullptr, nullptr, current_x, current_y);
            }
            else{
                temp_ptr->next = new linkNode(nullptr, temp_ptr, current_x, current_y);
                temp_ptr = temp_ptr->next;
            }
            object.push(temp_ptr);
            //cout << "\n pushing: " << temp_ptr->value_string() << " to the stack.\n";
        }
        while(current_y != y){
            if(current_y < y){
                current_y++;
            }
            else{
                current_y--;
            }
            if(current_y == y && current_x && x){
                cout << "Arrived to (" << current_x << "," << current_y << ")\n";
            }
            else{
                cout << "(" << current_x << "," << current_y << ")\n";
            }
            if(temp_ptr == nullptr){
                temp_ptr = new linkNode(nullptr, nullptr, current_x, current_y);
            }
            else{
                temp_ptr->next = new linkNode(nullptr, temp_ptr, current_x, current_y);
                temp_ptr = temp_ptr->next;
            }
            object.push(temp_ptr);
            //cout << "\n pushing: " << temp_ptr->value_string() << " to the stack.\n";
        }
        z++;
    }
    //cout << "\nCurrently in the stack: ";
    linkNode* count_ptr = object.top();
	/*
    while(count_ptr != nullptr){
        cout << count_ptr->value_string() << "\t with time travel: " << count_ptr->beentimetraveled() << endl;
        count_ptr = count_ptr->prev;
    }
	object.pop();
    cout << "After pop: ";
    count_ptr = object.top();
    while(count_ptr != nullptr){
		cout << count_ptr->value_string() << "\t with time travel: " << count_ptr->beentimetraveled() << endl;
		object.pop();
		count_ptr = object.top();
    }
	*/
	cout << "Back to (0,0): " << endl;
	//cout << current_x << "\t" << current_y << endl;
	bool firsttime = true;
	count_ptr = object.top();
	while (current_x != 0 || current_y != 0) {
		if (count_ptr == nullptr) {
			break;
		}
		if (!firsttime) {
			current_x = count_ptr->x_value();
			current_y = count_ptr->y_value();
			cout << "(" << current_x << "," << current_y << ")\n";
		}
		if (count_ptr->beentimetraveled()) {
			while(count_ptr->prev->x_value() != current_x || count_ptr->prev->y_value() != current_y) {
				object.pop();
				count_ptr = object.top();
			}
			object.pop();
			count_ptr = object.top();
		}
		else {
			//do nothing.
		}
		object.pop();
		count_ptr = object.top();
		firsttime = false;
	}
	//cout << "(" << current_x << "," << current_y << ")\n";
	cout << "(0,0)\n";
	cout << "Home sweet home.";
    return 0;
}