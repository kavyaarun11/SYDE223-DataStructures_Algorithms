#include <iostream>
#include "dynamic-stack.h"

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -1000000000; //empty stack constant

DynamicStack::DynamicStack() {
    init_capacity_ = 16; //initial capacity of array is 16
    size_ = 0; //initial stack size is 0
    capacity_ = init_capacity_; //capacity of stack equals the initial capacity
    items_ = new StackItem[capacity_]; //items array has capacity equal to capacity
}

DynamicStack::DynamicStack(unsigned int capacity){
    capacity_ = capacity; //capacity equals the capacity being passed in
    init_capacity_ = capacity_; //initial cap equals the capacity
    size_ = 0; //size of the stack is still zero
    items_ = new StackItem[capacity_]; //items array has capacity equal to capacity
}

DynamicStack::~DynamicStack() {
    delete [] items_; //delete all elements in array
    items_ = nullptr; //sets all values to NULL to avoid dangling pointers
}

bool DynamicStack::empty() const {
    return size_ == 0; //if size of stack is 0, it means it is empty
}

int DynamicStack::size() const {
    return size_; //returns the size of the stack
}

void DynamicStack::push(StackItem value) {
    if (size() == capacity_){ //if the size == capacity, then the stack is full and capacity needs to be doubled
        int *doubleCap = new int [2*capacity_]; //creating new array with double capacity
        capacity_ *= 2; //doubling capacity
        for(int i = 0; i < size_; i++){
            doubleCap[i] = items_[i]; //transfers elements from old array to new one
        }
        int *temp = items_;
        items_ = doubleCap; //transferring elements in item array to double capacity array
        delete [] temp; //deleting temp array

    }
    size_++; //increases size of array since new element is being added
    items_[size_-1] = value;
}

DynamicStack::StackItem DynamicStack::pop() {
    if(size_ == 0){
        return EMPTY_STACK; //EMPTY RETURN value
    }
    else{
        StackItem popVal = items_[size_-1]; //popVal is the value at top of stack to be popped out
        items_[size_-1]=items_[size_]; //top value in stack now equals nothing
        size_--;//size of the array decreases by 1

        if (size_ <= capacity_/4 && init_capacity_ <= capacity_ / 2){ //if size is less than or equal to 1/4 of the cap and initial cap is less than or equal to half of the cap, array is halved
            int *halfCap = new int [capacity_/2]; //creating new array with half capacity
            capacity_ /= 2; //half capacity
            for(int i = 0; i < size_; i++){
                halfCap[i] = items_[i]; //transfers elements from old array to new one
            }
            int *temp = items_;
            items_ = halfCap; //transferring elements in item array to half capacity array
            delete [] temp; //deleting temp array
        }
        return popVal; //returns the value of popped element
    }
}

DynamicStack::StackItem DynamicStack::peek() const {
    if(size_ == 0){
        return EMPTY_STACK; //EMPTY RETURN value
    }
    else {
        int topVal = items_[size_-1]; //the top value in the stack is size_-1
        return topVal;
    }
}

void DynamicStack::print() const {
    for(int i = size_ - 1; i >= 0; i--){
        std::cout<<items_[i]<< std::endl; //prints out elements in stack array
    }
    std::cout<<std::endl;
}

