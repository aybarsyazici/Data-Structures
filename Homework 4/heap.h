#include <vector>
using namespace std;


template <class Comparable>
class BinaryHeap{
    public:
        BinaryHeap(int capacity = 100);
        bool isEmpty();
        bool isFull();
        virtual void insert(Comparable & x){};
        virtual void deleteMin(Comparable & minItem){};
        void makeEmpty();
        Comparable getTop();
        int HeapSize();
        Comparable deleteTop();
        virtual void percolateDown(int hole){};
    protected:
        int currentSize; // Number of elements in heap
        vector<Comparable> array; // The heap array
};

template <class Comparable>
BinaryHeap<Comparable>::BinaryHeap(int capacity){
    vector<Comparable> temp_array(capacity);
    this->array = temp_array;
	this->currentSize = 0;
}

template <class Comparable>
void BinaryHeap<Comparable>::makeEmpty(){
    array.clear();
    currentSize = 0;
}

template <class Comparable>
bool BinaryHeap<Comparable>::isEmpty(){
    return currentSize==0;
}
template <class Comparable>
bool BinaryHeap<Comparable>::isFull(){
    if(currentSize==array.size()-1){
        return true;
    }
    return false;
}
template <class Comparable>
Comparable BinaryHeap<Comparable>::getTop(){
    return this->array[1];
}

template <class Comparable>
int BinaryHeap<Comparable>::HeapSize(){
    return currentSize;
}
template <class Comparable>
Comparable BinaryHeap<Comparable>::deleteTop(){
    Comparable return_var = array[1];
    array[1] = array[currentSize];
    currentSize = currentSize--;
    percolateDown(1);
    return return_var;
}
template <class Comparable>
class MinHeap: public BinaryHeap<Comparable>{
    public:
		MinHeap(int capacity = 100) {
			vector<Comparable> temp_array(capacity);
			this->array = temp_array;
            this->currentSize = 0;
		}
		void insert(Comparable& x) {
			this->currentSize = this->currentSize + 1;
			int hole = this->currentSize;
			for (; hole > 1 && x < this->array[hole / 2]; hole /= 2)
				this->array[hole] = this->array[hole / 2];
			this->array[hole] = x;
			if(this->isFull()){
				int int_resize = 2 * this->array.size();
				this->array.resize(int_resize);
			}
		}
        void percolateDown(int hole){
            int child;
            Comparable tmp = this->array[hole];
            for(; hole * 2 <= this->currentSize; hole = child ){
                child = hole * 2;
                if (child != this->currentSize && this->array[child + 1] < this->array[child] )
                    child++; 
                if (this->array[child] < tmp)
                    this->array[hole] = this->array[child];
                else
                    break;
            }
			this->array[hole] = tmp;
        }
};


template <class Comparable>
class MaxHeap: public BinaryHeap<Comparable>
{
    public:
		MaxHeap(int capacity = 100) {
			vector<Comparable> temp_array(capacity);
			this->array = temp_array;
            this->currentSize = 0;
		}
        void insert(Comparable & x){
            this->currentSize++;
            int hole = this->currentSize;
            for (;hole > 1 && x > this->array[hole/2];hole /= 2)
                this->array[hole] = this->array[hole/2];
            this->array[hole] = x;
			if (this->isFull()) {
				int int_resize = 2 * this->array.size();
				this->array.resize(int_resize);
			}
        }
        int getSize(){
            return this->array.size();
        }
        void percolateDown(int hole){
            int child;
            Comparable tmp = this->array[hole];
            for(; hole * 2 <= this->currentSize; hole = child ){
                child = hole * 2;
                if (child != this->currentSize && this->array[child + 1] > this->array[child] )
                    child++; 
                if (this->array[child] > tmp)
					this->array[hole] = this->array[child];
                else
                    break;
            }
			this->array[hole] = tmp;
        }
};