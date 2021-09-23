#include "sequential-list.h"
#include <iostream>

SequentialList::SequentialList(unsigned int cap)
{
    capacity_ = cap; //Assigning the passed unsigned int as the capacity
    size_ = 0; //Requires 0 elements in list when initializing
    DataType *seqListArray = new DataType[capacity_]; //SequentialList Constructor declaration
    data_= seqListArray; //Assigning array to the pointer
}

SequentialList::~SequentialList()
{
    delete [] data_; //deletes array to manually de-allocate memory space
    data_ = NULL; //assigns pointer to NULL after delete to avoid dangling pointers
}

unsigned int SequentialList::size() const
{
    return size_; //returns size of list
}

unsigned int SequentialList::capacity() const
{
    return capacity_; //returns capacity of list
}

bool SequentialList::empty() const
{
    if(size()==0) { //checks if size of the array is 0, which means it's empty
        return true;
    }else
        return false;
}

bool SequentialList::full() const
{
    if(size() == capacity()){ //check if the size of the array equals the capacity, which indicates the array is at full capacity
        return true;
    }else
        return false;
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if (index>size() -1 || index <0){ //Checks if index is greater than number of indexes in array, or if the index is greater than 0, then assigns index to be last element in array
        index = size() - 1;
    }
    return data_[index];// returns value at the given index in the list
}

unsigned int SequentialList::search(DataType val) const
{
    for(unsigned int i=0; i<=size()-1; i++){ //iterates through for loop from i = 0 to size_ -1
        if (data_[i]== val){ //checks if the value in index i, equals val. Returns value of val if true
            return i;
        }
    }
    return size(); //returns size of the list if val is not found in the list
}

void SequentialList::print() const
{
    if (size() > 0) { //Checks if
        for (int i = 0; i <= size() - 1; i++) { //iterates through for loop from i = 0 to size_ -1
            if (i>0)
                std::cout << ", "; //Separator for values
            std::cout << data_[i]; //Prints elements in list, in the format 1, 2, 3, 4, 5
        }
        std::cout<<std::endl;
    }else
        std::cout << "No values in list.";
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    if (full() || index > capacity() -1 || index < 0 || index > size())
        return false;
    else {
        for(unsigned int i = size(); i>index; i--){ //shifts values from one index to the one on the right
            data_[i] = data_[i-1];
        }
        data_[index] = val; //stores value val at start of the list, at index 0
        size_++; //increases size list by 1
        return true;
    }
}

bool SequentialList::insert_front(DataType val)
{
    return insert(val, 0);// Adds value to beginning of the list when the index is equal to 0
}

bool SequentialList::insert_back(DataType val)
{
    return insert(val, size());// Adds value to end of the list when the index is equal to size of the array
}

bool SequentialList::remove(unsigned int index)
{
    if (index > capacity() -1 || index < 0 || index > size() -1 || size() == 0)
        return false;
    else {
        for(unsigned int i = index; i<size(); i++){ //shifts values from one index to the one on the left
            data_[i] = data_[i+1];
        }
        size_--; //decreases size list by 1
        return true;
    }
}

bool SequentialList::remove_front()
{
    return remove(0); //removes the first value in the list, which is located at index = 0
}

bool SequentialList::remove_back()
{
    return remove(size() -1); //removes the last value in the list, which is located at index = size_ - 1
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    if (index >= size() || index <0) // Checks if the index value doesn't contain an element or if the index is less than 0
        return false;
    else{
        data_[index]=val; //Assigns value val to the element located at passed index
        return true;
    }
}

