#include <iostream>
#include <string>
using namespace std;

struct linkNode
{
	linkNode(linkNode* tempptr,linkNode* prevtemp, int coor1, int coor2, bool time=false){
		next = tempptr;
		x_coor = coor1;
		y_coor = coor2;
		both = to_string(coor1) + "," + to_string(coor2);
		prev = prevtemp;
		timetraveled = time;
	};
	string value_string(){
		return both;
	};
	int x_value(){
		return x_coor;
	};
	int y_value(){
		return y_coor;
	};
	bool beentimetraveled() {
		return timetraveled;
	}
	linkNode* next;
	linkNode* prev;
	private:
		int x_coor;
		int y_coor;
		string both;
		bool timetraveled;
};


template <class T>
class Stack {
	private:
		linkNode* headptr;
		linkNode* top_ptr;
		// Put your internal data representation here
	public:
		Stack(){
			headptr = nullptr;
		}
		void push(T coor){
			if(isEmpty()){
				headptr = coor;
				top_ptr = coor;
			}
			else
				top_ptr = coor;
		}
		void pop(){
			if(isEmpty()){
				//do nothing.
			}
			else{
				if (top_ptr->prev != nullptr) {
					linkNode* temporary = top_ptr->prev;
					delete top_ptr;
					top_ptr = temporary;
					top_ptr->next = nullptr;
				}
				else{
					delete top_ptr;
					top_ptr = nullptr;
				}
			}
		}
		T top(){
			return top_ptr;
		}
		bool isEmpty(){
			if(headptr == nullptr)
				return true;
			return false;
		}
		const static T noItem;
};