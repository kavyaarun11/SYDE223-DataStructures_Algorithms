#include "doubly-linked-list.h"
#include <iostream>

DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    next = NULL;
    prev = NULL;

}

DoublyLinkedList::DoublyLinkedList()
{
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}

DoublyLinkedList::~DoublyLinkedList()
{
    while (head_!=NULL) { //loop while head is not NULL
        Node* temp = head_; //assign head_ node to temporary node
        head_ = head_ -> next; // assign next node to head_ node
        delete temp; //delete temporary node which was previously the head_ node
    }
}


unsigned int DoublyLinkedList::size() const
{
    return size_; //returns size
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY; //returns capacity
}

bool DoublyLinkedList::empty() const
{
    if (size() == 0) //checks if size is 0, indicating it is empty
        return true;
    else
        return false;
}

bool DoublyLinkedList::full() const
{
    if (size() == capacity()) //checks if size equals the capacity, which means it is full
        return true;
    else
        return false;

}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (index<0 || index>size()-1) //checks if the passed index is less than 0 or greater than the number of elements (size), which makes the index value the last node in list
        index = size()-1;
    return getNode(index) -> value; //returns the value of node at that specified index
}

unsigned int DoublyLinkedList::search(DataType value) const
{
    unsigned int index = 0; //index starts off at 0
    Node *temp = head_; //creating a temporary node which is the head (index = 0)
    while(temp){ //while loop while the temp node still exists (not NULL)
        if (temp->value == value) //if the value of the temp node equals the passed value, it returns index, and increases it by 1
            return index;
        ++index;
        temp = temp -> next; //temp node equals the next node
    }
    return index; //returns the index at which
}

void DoublyLinkedList::print() const
{
    if(size()==0) //if the size of the list is 0, there are no values to print
        std::cout << "No values in list.";
    else {
        Node* temp = head_; //creates a temp node which equals the head
        while (temp) {
            if (temp != head_) //if the temp node does not equal the head
                std::cout << ", ";
            std::cout << temp -> value; //prints out the value of the temp node in the format 1, 2, 3, 4, 5, 6, 7
            temp = temp->next; //assigned next node to temp
        }
        std::cout << std::endl;
    }
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    unsigned int i = 0;
    Node* temp = head_; //new temp node which equals the head
    while (i < index && temp) { //while loop, for which the i is less than index, and temp node exists
        temp = temp -> next; //assigned next node to temp
        ++i; //increases value of i by 1
    }
    return temp; //returns the temp node
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    if (index < 0) //if passed index is less than 0, returns false, since negative index is not possible
        return false;

    Node *newNode = new Node(value); //creates new node called newNode, in which passed value is being passed


    if (index==0 && !head_){ //if index is 0 and there is no head node currently there
        head_ =  newNode; //head node is now assigned newNode
        tail_ = newNode; //tail node is also assigned newNode
        ++size_; //increases size of the list by 1, since newNode has been added
        return true;
    }else if(index ==0){ //if index is 0 and there is already a head node there, nodes must be shifted to the right so newNode can be inserted at index=0
        Node* oldHead = head_; //creating node called oldHead which is the current head in the list
        newNode -> next = oldHead; //the next node from newNode which is being inserted in the list at index 0, is the oldNode, since it is shifting to the right
        oldHead -> prev = newNode; //the previous node of the oldHead which has now shifted one to the right, is the newNode at index =0, so the head of the list
        head_ = newNode; //assigning the newNode to be head since it is as index = 0
        ++size_; //increases size of list by 1, since new Node is being inserted
        return true;
    }
    if (index>size()) //if index is greater than the size of the list, it is not possible to insert a value if the previous index is empty
        return false;


    if (index == size()){ //if index equals the size, the new node is being added to the back of the list
        if(!head_) //if there is no head, that means size is 0, and node is being added to index = 0
        {
            head_ = newNode; //this means the head will be the newNode
            tail_ = newNode; //tail will also be the newNode since size is 1, so there is only one node in list
        }else
        {
            newNode->prev = tail_; //if there is already a head, the newNode's previous node will be the tail, since this is being added to the end of the list
            tail_->next = newNode; //the tail, which was the last node, has a next node, which will be the newNode since it is at the end of the list
            tail_ = newNode; //the tail is now assigned the newNode since that is the last node in the list
        }
    } else { //if newNode is being added to the middle of a list
        Node* oldNode = getNode(index); //oldNode is the node which shifts to the right, to make space for newNode
        Node* previousNode = oldNode-> prev; //previousNode is the node which used to be to the left(previous) of the oldNode
        newNode -> prev = previousNode; //since oldNode shifts to the right, to make room for the newNode, the previous node of newNode will now be previousNode
        newNode -> next = oldNode;//the next node from the newNode is the oldNode, since that shifted to the right to make room for the newNode
        previousNode -> next = newNode; //the node next to the previous node is now the newNode
        oldNode -> prev = newNode; //the node previous to the oldNode now is the newNode
    }
     ++size_; //size of list increases since newNode is being added
    return true;
}

bool DoublyLinkedList::insert_front(DataType value)
{
  return insert(value, 0); //inserting at a front of a list is when the index is 0

}

bool DoublyLinkedList::insert_back(DataType value)
{
    return insert(value, size()); //inserting at the back of a list is when the index equals the size of the list
}

bool DoublyLinkedList::remove(unsigned int index)
{
    if (empty()) { //if list if empty, it returns false since there is nothing to remove
        return false;
    } else if (index == 0){ //if index is equal to 0, it is to remove the first node in the list
        Node* temp = head_; //creating new temp node which is the head
        head_ = head_ -> next; //the current head of the list, at index =0, now shifts to the right
        if (head_) //if head exists
            head_ -> prev = NULL; //the head's previous value is removed and becomes null
        else
            tail_ = NULL; //the tail value is removed and becomes null
        delete temp; //the temp node is then deleted
    }else if (index == size()){ //if index equals size, it is to remove the last node in the list
        Node* lastNode = tail_; //creating temp lastNode which is equal to the tail
        Node* previousNode = lastNode-> prev; //creating a previousNode which is the node to the left of the lastNode, which is the tail
        tail_ = previousNode; //assigning the tail to become the previousNode, which is to the left of the lastNode in the list
        if (tail_) //if tail exists
        {
            tail_->next = NULL; //the lastNode value is removed and becomes null, which is the node next to the tail
        }else{
            head_ = NULL; //head becomes null
        }
        delete lastNode; //lastNode is deleted
    } else if (index>= size()) { //if index is greater than size, there is nothing to remove
        return false;
    }
    else { //to remove a node in the middle of a list
        Node* oldNode = getNode(index); //creating a temp called oldNode which is the node in the passed index
        if(!oldNode) //if it isn't oldNode, return false
            return false;
        if(oldNode == tail_){ //if the oldNode is equal to the tail, that means last node in the list is being removed
            return remove_back();
        }
        else {
            Node *previousNode = oldNode->prev; //previous node is the node to the left of the oldNode
            Node *nextNode = oldNode->next; //nextNode is the node to the right of oldNode
            previousNode->next = nextNode; //the node next to previousNode is the nextNode
            nextNode->prev = previousNode;//the node previous to nextNode is previousNode
            delete oldNode; //oldNode is removed and deleted
        }
    }
    --size_; //size of list decreases since node is being removed
    return true;
}

bool DoublyLinkedList::remove_front()
{
    return remove(0); //removing at the front of the list means removing the node at index 0
}

bool DoublyLinkedList::remove_back()
{
    return remove(size()); //removing at the back of the list means removing the node when index = size
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    Node* temp = getNode(index); //creating temporary node which has the value of the node at passed index
    if (temp!= NULL){ //if the node at passed index has a value, and is not NULL, the value of the temp node is the value at passed index
        temp -> value = value;
        return true;
    }else
        return false;
}

