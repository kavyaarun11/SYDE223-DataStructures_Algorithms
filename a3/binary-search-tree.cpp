#include "binary-search-tree.h"
#include <iostream>


BinarySearchTree::Node::Node(DataType newval)
{
    val = newval; //value of the node equals the datatype newval which is being passed in
    left = NULL; //left children are NULL
    right = NULL;//right children are NULL
    avlBalance = 0;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    if(n ==NULL)
        return 0; //if node is null, there is no root, and depth of tree is 0
    else{
        //finds the depth of each subtree
        int leftDepth = getNodeDepth(n->left);
        int rightDepth = getNodeDepth(n->right);

        if(rightDepth>leftDepth)
            return (rightDepth + 1); //if right subtree is larger, it returns the depth of the right subtree
        else
            return (leftDepth + 1); //if left subtree is larger, or if both subtrees are equal, it returns the depth of the left subtree
    }
}

void BinarySearchTree::updateNodeBalance(Node* n)
{
    if(n!=NULL)
        n-> avlBalance = getNodeDepth(n);
}

void subtreeRemoval(BinarySearchTree::Node* currentNode)
{
    if(currentNode!=NULL){ //if the tree is not already empty
        if(currentNode -> left!=NULL) //if the root's left child is not null, remove the child
            subtreeRemoval(currentNode->left);
        if(currentNode->right !=NULL)
            subtreeRemoval(currentNode->right); //if the root's right child is not null, remove the child
        delete currentNode; //delete the root node
    }
}

BinarySearchTree::BinarySearchTree()
{
    size_ = 0; //size of empty tree is 0
    root_ = NULL; //since tree is empty, there is no root node, hence it is NULL
}

BinarySearchTree::~BinarySearchTree()
{
    subtreeRemoval(root_); //calling the helper function subtreeRemoval to delete the tree
}

unsigned int BinarySearchTree::size() const
{
    return size_; //returns the size
}

BinarySearchTree::DataType BinarySearchTree::max() const
{
    Node* maxNode = root_;
    while(maxNode->right != NULL){
        maxNode = maxNode -> right; //in a BST, all the keys in the right subtree are larger than the node's key value, hence keep traversing through the right subtree nodes till the largest leaf node is reached
    }
    return maxNode->val; //returns the value in the max node
}

BinarySearchTree::DataType BinarySearchTree::min() const
{
    Node* minNode = root_;
    while(minNode->left != NULL){
        minNode = minNode -> left; //in a BST, all the keys in the left subtree are smaller than the node's key value, hence keep traversing through the left subtree nodes till the smallest leaf node is reached
    }
    return minNode -> val;//returns the value in the min node
}

unsigned int BinarySearchTree::depth() const
{
    return getNodeDepth(root_) -1; //calls the getNodeDepth function, and passes root node as the parameter
}


void BinarySearchTree::print() const
{

}

bool BinarySearchTree::exists(DataType val) const
{
    Node* currentNode = root_;
    while(currentNode != NULL){ //loops through while the current node exists or till the value is found
        if(val == currentNode->val) //if the value matches the current node value, then it returns true
            return true;
        else if(val>currentNode->val)//if the value is greater than the current node, it needs to traverse to the right side of the tree
            currentNode = currentNode ->right; //the current node now becomes the node to the right of it
        else //if the value is less than the current node, it needs to traverse to the left side of the tree
            currentNode = currentNode ->left;//the current node now becomes the node to the left of it
    }
    return false; //returns false if value is not found in BST
}

BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
    return root_; //returns the root node
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;//returns the memory address of the root node
}

bool BinarySearchTree::insert(DataType val)
{
    Node* currentNode = root_;
    Node* parentNode;
    if(root_==NULL){ //if the tree is empty, the inserted node will become the root
        root_ = new Node(val);
    }
    else {
        while(currentNode != NULL){ //loops through while the current node exists or till the value is found
            if(val == currentNode->val) //if the value matches the current node value, then it returns false, since it is already in there
                return false;
            else if(val>currentNode->val) {//if the value is greater than the current node, it needs to traverse to the right side of the tree
                parentNode = currentNode; //the parent node will become the current node
                currentNode = currentNode->right; //the current node now becomes the node to the right of it, since it is greater than the parent value
            }
            else{ //if the value is less than the current node, it needs to traverse to the left side of the tree
                parentNode = currentNode;
                currentNode = currentNode->left;//the current node now becomes the node to the left of it
            }
        }
        Node* insertedNode = new Node(val);
        if(val >= parentNode ->val) //if the value is greater than the parent node's value
            parentNode->right = insertedNode ; //insert the node to the right of the parent node
        else
            parentNode->left = insertedNode; //or else, it means value is less than the parent node, hence insert it to the left of the parent node
    }
    size_++; //size increases when a node is inserted
    return true; //returns true when node is inserted
}


BinarySearchTree::Node* removeNode(BinarySearchTree::Node* currentNode, BinarySearchTree::DataType val)
{
    if(currentNode == NULL) //if the root node is null, then the tree is empty and there is nothing to remove
        return NULL;

    if(val == currentNode->val){
        //Case 1: Node does not have any children
        if(currentNode -> left == NULL && currentNode -> right == NULL)
            return NULL;
        //Case 2: Node has no left child
        if(currentNode -> left == NULL)
            return currentNode ->right;
        //Case 3: Node has no right child
        if(currentNode -> right == NULL)
            return currentNode ->left;
        //Case 4: Node has 2 children
        BinarySearchTree::Node* tempNode = currentNode->left; //using the predecessor method to remove nodes (goes left once, then right)
        while(tempNode->right != NULL){//while there is still a child node to the right, make the tempNode equal to the right most node
            tempNode = tempNode ->right;
        }
        currentNode -> val = tempNode->val; //the root node's value now becomes the predecessor node's value
        currentNode -> left = removeNode(currentNode->left,tempNode->val); //the node to the left of the root, is removed
        return currentNode; //returns the
    } else if(val < currentNode -> val){ //if the value is smaller than the root's value, let the root's left node equal the removedNode
        currentNode -> left = removeNode(currentNode-> left, val);
        return currentNode;
    } else{
        currentNode -> right = removeNode(currentNode->right, val);//if the value is larger than the root's value, let the root's right node equal the removedNode
        return currentNode;
    }
}


bool BinarySearchTree::remove(DataType val)
{
    if(exists(val)){ //check if the value exists in order to be removed
        root_ = removeNode(root_, val); //remove the value
        if(exists(val) == true) //check if the value was successfully removed from the tree
            return false;
        else{
            size_--; //decrease size of tree after removing node
            return true;
        }
    }
    else
        return false;
}
