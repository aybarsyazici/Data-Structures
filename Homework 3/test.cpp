#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
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

int main(){

	string test_string = "Istanbul, Ankara, izmir";
	stripUnicode(test_string);
		cout <<"TEST STRING IS: " <<test_string << endl;
	stringstream str_iterator(test_string);
	string temp_str;
	while(str_iterator >> temp_str){
		cout << "TEMP STR IS: " << temp_str << endl;
	}
}