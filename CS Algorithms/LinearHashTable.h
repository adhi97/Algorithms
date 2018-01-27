#ifndef LINEAR_HASH_TABLE_H
#define LINEAR_HASH_TABLE_H

#include <math.h>

enum state {EMPTY, OCCUPIED, DELETED};

template<typename T>
class LinearHashTable {
private:
    int count;
    int power;
    int array_size;
    int mod;
    int initial_cap;
    T *array;
    state *occupied;
    
    
public:
    LinearHashTable( int = 5 );
    ~LinearHashTable();
    int size() const;
    int capacity() const;
    double load_factor() const;
    bool empty() const;
    bool member( T const & ) const;
    T bin( int ) const;
    void double_array();
    void half_array();
    int findIndexToInsert(T const &obj, state * array_state);
    
    
    void insert( T const & );
    bool remove( T const & );
    void clear();
    void print() const;
};

template<typename T >
LinearHashTable<T >::LinearHashTable( int m ):
array_size( 1 << m ){
    count = 0;
    power = m;
    array_size = pow(2, power);
    initial_cap = array_size;
    mod = array_size;
    array = new T[array_size];
    occupied = new state[array_size];
    for (int i=0; i <array_size; i++) {
        occupied[i] = EMPTY;
    }
}

template<typename T >
LinearHashTable<T >::~LinearHashTable() {
    delete[] array;
    delete[] occupied;
}

template<typename T >
int LinearHashTable<T >::size() const {
    return count;
}

template<typename T >
int LinearHashTable<T >::capacity() const {
    return array_size;
}

template<typename T >
double LinearHashTable<T >::load_factor() const {
    return (double) count/array_size;
}

template<typename T >
bool LinearHashTable<T >::empty() const {
    if (count == 0) {return true;}
    return false;
}


template<typename T >
bool LinearHashTable<T >::member( T const &obj ) const {
    bool found = false;
    int counter = 0;
    int index = (int) obj % array_size;
    while (counter < array_size){ //have to reset i to 0 to start back from the start of the array and conti to size
        if (array[index] == obj && occupied[index] == OCCUPIED){
            found = true;
            break;
        }
        counter++;
        index = (index+counter) % array_size;
    }
    if (found) {return true;}
    return false;
}

template<typename T >
T LinearHashTable<T >::bin( int n ) const {
    if (occupied[n] == OCCUPIED) {return array[n];}
    else return NULL;
}

template<typename T >
void LinearHashTable<T >::double_array() {
    
    int old_array_size = array_size;
    array_size = array_size * 2;
    T * new_array = new T[array_size];
    state *new_occupied = new state[array_size];
    
    for (int i = 0; i<array_size; i++) {//fill  location of empty if not occupied in new array
        new_occupied[i] = EMPTY;
    }
    
    for (int i = 0; i<old_array_size; i++) {//old array size
        if (occupied[i] == OCCUPIED) {
            int indexToInsert = findIndexToInsert(array[i], new_occupied);
            new_array[indexToInsert] = array[i];//finds new index to insert
            new_occupied[indexToInsert] = OCCUPIED;
        }
    }
    
    delete[] array;
    delete[] occupied;
    
    array = new_array;
    occupied = new_occupied;
    
    
}

template<typename T >
int LinearHashTable<T>::findIndexToInsert(T const &obj, state * array_state) {
    int probe=0;
    int hashIndex = (int)obj%array_size;
    int newindex = 0;
    for (int i = 0; i<array_size; i++) {
        newindex = (hashIndex + probe) % array_size;
        
        if (!(array_state[newindex] == OCCUPIED)) {//seeing if its not Occupied
            break;
        }
        probe++;
    }
    
    return newindex;
}


template<typename T >
void LinearHashTable<T >::half_array() {
    int old_array_size = array_size;
    array_size = array_size/2;
    mod = array_size;
    T *new_array = new T[array_size];
    state *new_occupied = new state[array_size];
    
    for (int i=0; i<array_size; i++){
        new_occupied[i] = EMPTY;
    }
    
    for (int i=0; i<old_array_size; i++){
        if(occupied[i] == OCCUPIED){
            int index = (int) array[i] % array_size;
            int newindex = 0;
            while (new_occupied[index] == OCCUPIED) {
                newindex = (1+index) % array_size;
            }
            new_array[newindex] = array[i];
            new_occupied[newindex] = OCCUPIED;
        }
    }
    delete[] array;
    delete[] occupied;
    array = new_array;
    occupied = new_occupied;
}

template<typename T >
void LinearHashTable<T >::insert( T const &obj ) {
    if (load_factor() > 0.75){
        double_array();
    }
    
    int probe=0;
    int index = (int)obj%array_size;
    int newindex = 0;
    for (int i = 0; i<array_size; i++) {
        newindex = (index + probe) % array_size;
        
        if (!(occupied[newindex] == OCCUPIED)) {//seeing if its not Occupied
            break;
        }
        probe++;
    }
    array[newindex] = obj;
    occupied[newindex] = OCCUPIED;
    count++;
//    print();
    return;
}

template<typename T >
bool LinearHashTable<T >::remove( T const &obj ) {

    if(load_factor() <= 0.25 && array_size != initial_cap){
        half_array();
    }
    bool found = false;
    int counter = 0;
    int newindex = 0;
    int index = (int) obj % array_size;
    while (counter < array_size){ //have to reset i to 0 to start back from the start of the array and conti to size
        if (array[newindex] == obj && occupied[newindex] == OCCUPIED){
            found = true;
            occupied[newindex] = DELETED;
            array[newindex] = NULL;
            count--;
//            print();
            break;
        }
        newindex = (index+counter) % array_size;
        counter++;
    }
    if (found) {return true;}
    return false;
}


template<typename T >
void LinearHashTable<T >::clear() {
    for (int i=0; i<array_size; i++){
        occupied[i] = EMPTY;
    }
}


template<typename T >
void LinearHashTable<T >::print() const{
    for (int i=0; i<array_size; i++){
        std::cout << occupied[i] << "|";
    }
    std::cout << std::endl;
    std::cout << "end of occupied" << std::endl;
    for (int i=0; i<array_size; i++){
        std::cout << array[i] << "|";
    }
}

#endif
