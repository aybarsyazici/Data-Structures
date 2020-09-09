#include <string>
#include <vector>
using namespace std;


#ifndef head_protect
#define head_protect
bool IsPrime(int number)
{
    if (number == 2 || number == 3)
        return true;
    if (number % 2 == 0 || number % 3 == 0)
        return false;
    int divisor = 6;
    while (divisor * divisor - 2 * divisor + 1 <= number)
    {
        if (number % (divisor - 1) == 0)
            return false;
        if (number % (divisor + 1) == 0)
            return false;
        divisor += 6;
    }
    return true;
}
int nextPrime(int a){
    while (!IsPrime(++a)){}
    return a;
}
#endif
struct WordItem
{
    WordItem(){
        //Do nothing.
    }
    WordItem(string tempword, string document_name)
    {
        //cout << "Trying to create a new wordItem" <<endl;
        word = tempword;
        document_names.push_back(document_name);
        howmany.push_back(1);
        left_ptr = nullptr;
        right_ptr = nullptr;
		ascii_value = 0;
		for (int i = 0; i < tempword.length(); i++) {
			ascii_value += int(tempword[i]);
		}
        info = "ACTIVE";
    }
    void update(string document_name){
        bool found = false;
        for(int i = 0; i < document_names.size(); i++){
            if(document_names[i]==document_name){
                howmany[i]++;
                found = true;
                break;
            }
        }
        if(found == false){
            document_names.push_back(document_name);
            howmany.push_back(1);
        }
    }
    bool operator>(WordItem& temp_obj){
        if(this->element().compare(temp_obj.element())>0)
            return true;
        else
            return false;
    }
    bool operator<(WordItem& temp_obj){
        if(this->element().compare(temp_obj.element())<0){
            return true;
        }
        else{
            return false;
        }
    }
    bool operator==(WordItem& temp_obj){
        if(this->element().compare(temp_obj.element())==0){
            return true;
        }
        return false;
    }
    string element(){
        return word;
    }
    WordItem* left_ptr;
    WordItem* right_ptr;
    vector<string> document_names;
    vector<int> howmany;
	int ascii_value;
    string info;
    private:
        string word;
};


template <class Key>
class BinarySearchTree
{
private:
    Key* root;
public:
    BinarySearchTree(/* args */);
    ~BinarySearchTree();
    Key* search_in_tree(Key& temp_ptr);
    bool insert_in_tree(Key& temp_ptr);
    Key* return_root(){
        return root; 
    };
    bool isEmpty(){
        if(root == nullptr){
            return true;
        }
        return false;
    }
    void PrintTree(Key* temp_root){
        if(temp_root != nullptr){
            cout << temp_root->element() << " ";
            PrintTree(temp_root->left_ptr);
            PrintTree(temp_root->right_ptr);
        }
    }
};

template <class Key>
BinarySearchTree<Key>::BinarySearchTree()
{
    root = nullptr; //Initialize an empty BST.
}

template <class Key>
BinarySearchTree<Key>::~BinarySearchTree()
{
    delete root;
    root = nullptr;

}

template <class Key>
Key* BinarySearchTree<Key>::search_in_tree(Key& temp_ptr){
    Key* search_ptr = this->return_root();
    while(search_ptr != nullptr){
        if(*search_ptr < temp_ptr){
            search_ptr = search_ptr->right_ptr;
        }
        else if(*search_ptr > temp_ptr){
            search_ptr = search_ptr->left_ptr;
        }
        else if(*search_ptr == temp_ptr){
            return search_ptr;
        }
    }
	return search_ptr;
}

template <class Key>
bool BinarySearchTree<Key>::insert_in_tree(Key &temp_ptr){
    //cout << "We are here." << endl;
    Key* search_ptr = this->return_root();
    if(this->isEmpty()){
        //cout << "The tree was empty." << endl;
        root = &temp_ptr;
        return false;
    }
    else{
        //cout << "The tree was not empty... looking for a spot.\n";
        while(search_ptr != nullptr){
            if(*search_ptr < temp_ptr && search_ptr->right_ptr != nullptr){
                //cout << search_ptr->element() << " compared to " << temp_ptr.element() << " word comes later!(PTR WAS NOT EMPTY)\n";
                search_ptr = search_ptr->right_ptr;
            }
            else if(*search_ptr > temp_ptr && search_ptr->left_ptr != nullptr){
                //cout << search_ptr->element() << " compared to " << temp_ptr.element() << " word comes before!(PTR WAS NOT EMPTY)\n";
                
                search_ptr = search_ptr->left_ptr;
            }
            else if(*search_ptr < temp_ptr && search_ptr->right_ptr == nullptr){
                //cout << search_ptr->element() << " compared to " << temp_ptr.element() << " word comes later!\n";
                search_ptr->right_ptr = &temp_ptr;
                return false;
                break;
            }
            else if(*search_ptr > temp_ptr && search_ptr->left_ptr == nullptr){
                //cout << search_ptr->element() << " compared to " << temp_ptr.element() << " word comes before!\n";
                search_ptr->left_ptr = &temp_ptr;
                return false;
                break;
            }
            else if(*search_ptr == temp_ptr){
                return true; //The word was already in the BST.
            }
        }
    }
    return false;
}

template <class HashedObj>

class HashTable {
    public:
        HashTable(int size);
        HashedObj & find(HashedObj & x);
        void makeEmpty();
        bool insert(HashedObj & x);
        void remove(HashedObj & x );
        //enum EntryType { ACTIVE, EMPTY, DELETED };
        int hash(HashedObj & x, int size);
        HashedObj ITEM_NOT_FOUND;
    private:
        vector<HashedObj> array;
        int currentSize;
        bool isActive(int currentPos);
        int findPos(HashedObj & x);
        void rehash();
};


template <class HashedObj>
HashTable<HashedObj>::HashTable(int size){
    currentSize = 0;
    vector<HashedObj> temp_array(size);
	for(int i = 0; i < temp_array.size(); i++){
		temp_array[i].info = "EMPTY";
	}
    this->array = temp_array;
};

template <class HashedObj>
int HashTable<HashedObj>::findPos(HashedObj & x){
    int collisionNum = 0;
    int currentPos = hash(x, array.size());
    while (array[currentPos].info != "EMPTY" && array[currentPos].element() != x.element() ) {
        currentPos += 2 * ++collisionNum - 1; // add the difference
        if (currentPos >= array.size()) // perform the mod
            currentPos = currentPos - array.size(); // if necessary
    }
    return currentPos;
};

template <class HashedObj>
int HashTable<HashedObj>::hash(HashedObj & x, int size){
    int position = x.ascii_value % size;
	if(position < 0){position += size;}
    return position;
};

template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos){
    return array[currentPos].info == "ACTIVE";
};

template <class HashedObj>
void HashTable<HashedObj>::remove(HashedObj & x){
    int currentPos = findPos(x);
    if (isActive(currentPos))
        array[ currentPos ].info = "DELETED";
};

template <class HashedObj>
HashedObj & HashTable<HashedObj>::find(HashedObj & x){
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return array[currentPos];
    return ITEM_NOT_FOUND;
};

template <class HashedObj>
bool HashTable<HashedObj>::insert(HashedObj & x){
// Insert x as active
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return true;
    array[currentPos] = x;
// enlarge the hash table if necessary
    if (++currentSize >= array.size()/2)
        rehash();
    return false;

}

template <class HashedObj>
void HashTable<HashedObj>::rehash(){
    vector<HashedObj> oldArray = array;
    // Create new double-sized, empty table
    cout << "rehashed...\nPrevious table size:" << array.size() << ",";
    array.resize(nextPrime(2*oldArray.size()));
    int x = array.size();
    double loadfactor = currentSize / x;
    cout << " new table size: " << array.size() << ", current unique word count " << currentSize << endl << "current load factor: " << loadfactor << endl;
    for (int j = 0; j < array.size(); j++ )
        array[j].info = "EMPTY";
        // Copy table over
    currentSize = 0;
    for (int i = 0; i < oldArray.size(); i++)
        if (oldArray[i].info == "ACTIVE")
            insert(oldArray[i]);
};
