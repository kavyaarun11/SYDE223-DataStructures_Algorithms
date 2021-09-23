#include "circular-queue.h"
#include <iostream>

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = -1000000000; //empty queue constant

CircularQueue::CircularQueue() {
    capacity_ = 16; //capacity is set to 16
    size_=0; //initial size of the queue is 0
    head_ =0; //head is the 0th index
    tail_ =head_; //tail is the 0th index, which is the head
    items_ = new QueueItem[capacity_]; //items array has capacity equal to capacity_
}

CircularQueue::CircularQueue(unsigned int capacity) {
    capacity_ = capacity; //capacity is set to passed int capacity value
    size_=0; //initial size of the queue is 0
    head_ =0; //head is the 0th index
    tail_ =head_; //tail is the 0th index, which is the head
    items_ = new QueueItem[capacity_]; //items array has capacity equal to capacity_
}

CircularQueue::~CircularQueue() {
    delete [] items_; //delete all elements in array
    items_ = nullptr; //sets all values to NULL to avoid dangling pointers
}

bool CircularQueue::empty() const {
    return size_ == 0; //if size of queue is 0, it means it is empty
}

bool CircularQueue::full() const {
    return size_ == capacity_; //if size of queue equals the capacity, it means it is full
}

int CircularQueue::size() const {
    return size_; //returns size of the queue
}

bool CircularQueue::enqueue(QueueItem value) {
    if (!full()){ //if the circular array isn't full (it is empty)
        items_[tail_] = value; //enqueue adds value to the end of the circular array, which is where the tail is located
        if(tail_ == capacity_-1) {//if the tail is at the last index before the 0th index, the tail circles back to 0
            tail_ = 0;
        }
        else
            tail_++;//once a value is added, the tail points to the next index
        size_++; //increases size of array once an element is added
        return true;
    }
    else
        return false;
}

CircularQueue::QueueItem CircularQueue::dequeue() {
    if(empty())
        return EMPTY_QUEUE; //returns empty_queue constant if array is empty, nothing to return
    else {
        QueueItem dequeuedVal = items_[head_]; //int variable which is the value of the element that is being dequeued
        if(head_ == capacity_-1) //if the head is at the last index, before the 0th index, head circles back to 0, after dequeuing a value from front
            head_=0;
        else
            head_++;//head points to the next element in array after dequeuing value at head
        size_--; //decreasing size of array after removing an element
        return dequeuedVal; //returns the value of element which was dequeued
    }
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if(empty())
        return EMPTY_QUEUE; //returns empty queue constant if the array is empty, because there is nothing to peek
    else
        return items_[head_];//peeks at first value in circular array, where head points and returns the value of that element
}

void CircularQueue::print() const {
    if(tail_ >= head_){ //if the tail is not same as head, and it is in front of head element in the circular array, just print values from
        for(int i = head_; i <= tail_; i++){//prints values from the head index to the tail index
            std::cout<<items_[i]<< std::endl; //prints out elements in circular queue
        }
    } else{ //if the tail is in front of the head element
        for(int i = head_; i<size_; i++){ //prints all the values from the head till the end of the circular array, before looping back to the 0th index
            std::cout<<items_[i]<< std::endl; //prints out elements in circular queue
        }
        for(int i=0; i<=tail_; i++){ //prints all the values from the 0th index to the tail
            std::cout<<items_[i]<< std::endl; //prints out elements in circular queue
        }
    }
    std::cout<<std::endl;
}


