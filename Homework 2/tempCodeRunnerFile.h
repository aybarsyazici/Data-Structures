#include <string>
#include <vector>
using namespace std;

/*
struct IntItem
{
    IntItem(int temp_x)
    {
        x = temp_x;
        left_ptr = nullptr;
        right_ptr = nullptr;
    }
    int element(){
        return x;
    }
    bool operator<(IntItem &temp_obj){
        if(this->element() < temp_obj.element()){
            return true;
        }
        return false;
    }
    bool operator>(IntItem &temp_obj){
        if(this->element() > temp_obj.element()){
            return true;
        }
        return false;
    }
    IntItem* left_ptr;
    IntItem* right_ptr;
    private:
        int x;
};
*/
struct WordItem
{
    WordItem(string tempword, string document_name)
    {
        cout << "Trying to create a new wordItem" <<endl;
        word = tempword;
        document_names.push_back(document_name);
        howmany.push_back(1);
        left_ptr = nullptr;
        right_ptr = nullptr;
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
        if(this->element().compare(temp_obj.element())==1)
            return true;
        else
            return false;
    }
    bool operator<(WordItem& temp_obj){
        if(this->element().compare(temp_obj.element())==-1){
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
    private:
        string word;
        vector<string> document_names;
        vector<int> howmany;
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
            cout << temp_root->element();
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
    cout << "We are here." << endl;
    Key* search_ptr = this->return_root();
    if(this->isEmpty()){
        cout << "The tree was empty." << endl;
        root = &temp_ptr;
        return false;
    }
    else{
        cout << "The tree was not empty... looking for a spot.\n";
        while(search_ptr != nullptr){
            if(*search_ptr < temp_ptr && search_ptr->right_ptr != nullptr){
                cout << search_ptr->element() << " compared to " << temp_ptr.element() << " word comes later!(PTR WAS NOT EMPTY)\n";
                search_ptr = search_ptr->right_ptr;
            }
            else if(*search_ptr > temp_ptr && search_ptr->left_ptr != nullptr){
                cout << search_ptr->element() << " compared to " << temp_ptr.element() << " word comes before!(PTR WAS NOT EMPTY)\n";
                
                search_ptr = search_ptr->left_ptr;
            }
            else if(*search_ptr < temp_ptr && search_ptr->right_ptr == nullptr){
                cout << search_ptr->element() << " compared to " << temp_ptr.element() << " word comes later!\n";
                search_ptr->right_ptr = &temp_ptr;
                return false;
                break;
            }
            else if(*search_ptr > temp_ptr && search_ptr->left_ptr == nullptr){
                cout << search_ptr->element() << " compared to " << temp_ptr.element() << " word comes before!\n";
                search_ptr->left_ptr = &temp_ptr;
                return false;
                break;
            }
            else if(*search_ptr == temp_ptr){
                return true; //The word was already in the BST.
            }
        }
    }
}