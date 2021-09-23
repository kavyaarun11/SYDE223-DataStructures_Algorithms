#include "avl-tree.h"
#include <iostream>

bool AVLTree::insert(DataType val)
{
    BinarySearchTree::insert(val); //inserts value using BST Insert function
    if (exists(val) == true){//check if the value was successfully inserted in the tree
        helperBalance(getRootNode()); //use balance helper function to check the balance, with root node being passed
        return true; //returns true if insert was successful
    }
    else
        return false;//returns false if insert was successful
}

bool AVLTree::remove(DataType val)
{
    BinarySearchTree::remove(val);
    if (exists(val) == false){//check if the value was successfully removed in the tree
        helperBalance(getRootNode()); //use balance helper function to check the balance, with root node being passed
        return true;
    }
    else
        return false;
}


int AVLTree::heightDifference(Node* node)
{
    int balanceFactor;
    if(node->left == NULL && node-> right == NULL) //if there are no child nodes, the balance factor is 0
        balanceFactor = 0;
    else if(node->left == NULL){ //if there is only a right child
        updateNodeBalance(node->right); //update node balance with only the right child node
        int rightHeight = node->right->avlBalance; //the right height of the tree is the height from right child node
        balanceFactor = rightHeight*-1; //making the balance factor negative for right subtree height
    }
    else if(node->right ==NULL){ //if there is only a left child
        updateNodeBalance(node->left); //update the node balance with only the left child node
        int leftHeight = node->left->avlBalance;//the left height of the tree is the height from left child node
        balanceFactor = leftHeight;//making the balance factor equal the left subtree height
    }
    else { //if there are 2 children nodes, on both right and left subtrees
        //update both of the node balances
        updateNodeBalance(node->left);
        updateNodeBalance(node->right);
        int leftHeight = node->left->avlBalance; //left subtree height is height from left child node
        int rightHeight = node->right->avlBalance; //right subtree height is height from right child node
        balanceFactor = leftHeight-rightHeight; //the balance factor is equal to the left subtree - right subtree
    }
    return balanceFactor; //returns int value of the balance factor
}

void AVLTree::leftLeft(Node* node){ //Left left rotation
    BinarySearchTree::Node* leftChild = node->left; //node variable with left child nodes
    BinarySearchTree::Node* rightChild = node->right; //node variable with right child nodes
    Node* tempNode = new Node(node->val); //input is the tempNode
    tempNode->left = leftChild->right; //the input's left child is the parent node's left child's, right child node
    tempNode->right = rightChild; //the input's right child is the parent node's right child
    node->val = node->left->val; //the value of the parent node, becomes the value of the child node to the left of it
    node->left = leftChild->left; // the left child of the parent's node becomes the node that is 2 children to the left of it
    node->right = tempNode; //the parent node's right node is the input node
}

void AVLTree::rightRight(Node* node){ //right right rotation
    BinarySearchTree::Node* rightChild = node->right; //node variable with right child nodes
    BinarySearchTree::Node* leftChild = node->left; //node variable with left child nodes
    Node* tempNode = new Node(node->val); //input is the tempNode
    tempNode->left = leftChild;//the input's left child is the parent node's left child
    tempNode->right = rightChild->left;//the input's right child is the parent node's right child's, left child node
    node->val = rightChild->val;//the value of the parent node, becomes the value of the child node to the right of it
    node->right = rightChild->right;// the right child of the parent's node becomes the node that is 2 children to the right of it
    node->left = tempNode;//the parent node's left node is the input node
}

void AVLTree::leftRight(Node* node){
    BinarySearchTree::Node* leftChild = node->left; //node variable with left child nodes
    rightRight(leftChild);
    leftLeft(node);
}

void AVLTree::rightLeft(Node* node){
    BinarySearchTree::Node* rightChild = node->right; //node variable with right child nodes
    leftLeft(rightChild);
    rightRight(node);
}

void AVLTree::helperBalance(Node* node){
    if(node != NULL) { //if the node is not null, and till it reaches the leaf nodes
        BinarySearchTree::Node* leftChild = node->left; //node variable with left child nodes
        BinarySearchTree::Node* rightChild = node->right; //node variable with right child nodes
        helperBalance(leftChild); //recursively calling helperBalance for both left and right subtrees till leaf nodes are reached, and node is not null
        helperBalance(rightChild); //recursively calling helperBalance for both left and right subtrees till leaf nodes are reached, and node is not null
        int balanceFactor = heightDifference(node); // calling height difference for balance factor variable
        if (balanceFactor < -1 && heightDifference(rightChild) > 0 ) //if the balance factor is negative, the right subtree is greater than the left subtree, and if the height of the right child subtree is greater, then do a right left rotation
            rightLeft(node);
        else if (balanceFactor < -1) //else if the left subtree is larger than the right child subtree, do a right right rotation
            rightRight(node);
        if (balanceFactor > 1 && heightDifference(leftChild) >= 0) //if the balance factor is greater than 1, then the left subtree is greater than right subtree, and if the height from left child node is greater than 0, do a single right rotation
            leftLeft(node);
        else if (balanceFactor > 1) //else if the right subtree has greater height, do left right rotation
            leftRight(node);
    }
}
