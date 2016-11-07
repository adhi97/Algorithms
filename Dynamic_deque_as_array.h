#ifndef DYNAMIC_DEQUE_AS_ARRAY_H
#define DYNAMIC_DEQUE_AS_ARRAY_H



#include "ece250.h"
#include "Exception.h"

#include <iostream>
#include <algorithm>

using namespace std;


class Dynamic_deque_as_array
{

	public:
		Dynamic_deque_as_array( int = 10 );
		~Dynamic_deque_as_array();


		int head() const; //What is the const used for in this case?
		int tail() const; 
		int size() const;
		bool empty() const;
		int capacity() const;
		void double_capacity();
		void print();

		void enqueue_head( const int & );
		void enqueue_tail( const int & );
		int dequeue_head();
		int dequeue_tail();
		void clear();

	private:
		int mhead, mtail, count, array_size; 
		int* array;
};


Dynamic_deque_as_array::Dynamic_deque_as_array( int n ) {
	array_size = std::max(1,n);
	array = new int[array_size];
	count = 0;
}


Dynamic_deque_as_array::~Dynamic_deque_as_array() {
	delete[] array;
}


int Dynamic_deque_as_array::size() const {
	return count;
}


int Dynamic_deque_as_array::capacity() const {
	return array_size;
}


bool Dynamic_deque_as_array::empty() const {
	if (count == 0){ return true; } 
	return false;	
}


int Dynamic_deque_as_array::head() const {
	return *(array + mhead);
}


int Dynamic_deque_as_array::tail() const {
	return *(array + mtail); // array[mtail]
}

//Doubling the capacity occurs in O(n) time. 
void Dynamic_deque_as_array::double_capacity() {
	int* tmp = array; // stores pointer to old array
	//print();
	int old_array_size = array_size;
	array_size = 2*array_size;
	array = new int[array_size];
	for(int i=0; i<old_array_size; i++){ // loop dequeue's from tail and fills it up in the new array from the head
		array[i] = tmp[mtail];
		mtail = (++mtail) % old_array_size;
	}
	delete[] tmp; //call delete to delete the previous array
	mtail = 0;
	mhead = count - 1;
	return;
}

void Dynamic_deque_as_array::print() { -- function used for debugging the program 
	for (int i=0; i<array_size; i++){
		cout << array[i] << "|";
	}
	cout << endl;
	// cout << head() << endl;
	// cout << tail() << endl;
}

// enqueue_head & enqueue_tail treat the array as a circular array, 
//where both the tail and head can overlap each other
// All operations here are performed in O(1) time except the case when the array has to be resized.
void Dynamic_deque_as_array::enqueue_head( const int &obj ) { 
	if (count == array_size){ 
		double_capacity(); 
	}
	if (count == 0){
		array[0] = obj;
		mtail = 0;
		mhead = 0;
		//print();
		count++;
	} 
	else {
		mhead = (mhead+1+array_size) % array_size;
		array[mhead] = obj;
		//print();
		count++;
	}
	return;
}

void Dynamic_deque_as_array::enqueue_tail( const int &obj ) {
	if (count == array_size){ 
		double_capacity();
	}
	if (count == 0){ 
		array[0] = obj;
		mtail = 0;
		mhead = 0;
		//print();
		count++;
	} 
	else {
		mtail = (mtail-1+array_size) % array_size;
		array[mtail] = obj;
		//print();
		count++;
	}
	return;
}

//dequeue_head and dequeue_tail treat the array like a circular array, where the mod function
//helps position the head and tail pointers, so that they dont access out of bounds of the array
//All operation are performed in O(1) time. 
int Dynamic_deque_as_array::dequeue_head() {
	if (count == 0){ throw underflow(); }
	int return_val = array[mhead];
	mhead = (mhead-1+array_size) % array_size;
	//print();
	count--;
	return return_val;
}

int Dynamic_deque_as_array::dequeue_tail() {
	if (count == 0){ throw underflow(); }
	int return_val = array[mtail];
	mtail = (mtail+1+array_size) % array_size;
	//print();
	count--;
	return return_val;
}

//clear sets the head tail and count var's to 0, thus performing the function in O(1) time.
void Dynamic_deque_as_array::clear() {
	mhead, mtail, count = 0;
	return;
}

#endif

