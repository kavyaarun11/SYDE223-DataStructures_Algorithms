#include "polynomial.h"
#include <iostream>
using namespace std;

Polynomial::Polynomial(int A[], int size) {
    size_ = size; //the size of this' list is equal to size
    for(int i=0; i<size_; i++) { //for loop which goes through each element in A[] and adds it to the list, while putting it through the back of the list
        coefficients.insert_back(A[i]); //insert back function is called here to insert values from A[] to the back of the list
    }
}
Polynomial* Polynomial::add(Polynomial* rhs) {
    int maxSize, minSize, temp;
    if(size_>= rhs->size_){ //checks if the size of the this polynomial is great than the size of the rhs polynomial list
        maxSize = size_; //makes the maximum size of the polynomial, the size of the this polynomial list
        minSize = rhs->size_; //makes the minimum size of the polynomial, the size of the rhs polynomial list
    }
    else {
        minSize = size_;//makes the minimum size of the polynomial, the size of the this polynomial list
        maxSize = rhs->size_; //makes the maximum size of the polynomial, the size of the rhs polynomial list
    }
    int* newArr = new int[maxSize](); //initializing a new array with the maximum possible size, maxSize

    for(int i=0; i<=minSize-1; i++){ //for loop which loops through the index of the polynomial list which is smaller/or assigned minSize
        temp = this->coefficients.select(i) + rhs->coefficients.select(i); // temp value which equals the value of the sum of the coefficients in front of the according exponent degree
        newArr[i] = temp; //replaces the value at the according index in the this polynomial list, with the sum value that was assigned to temp
    }
    if(size_ <maxSize){ //if the size of this is smaller than the maxSize
        for(int i = minSize; i<=maxSize-1; i++){ //for loop which loops through the index of the polynomial list which is larger/or assigned maxSize
            newArr[i] = rhs->coefficients.select(i);//replaces the remaining values at the according index in the this polynomial list, with the default value in the max list because it is being added with 0
        }
    } else if(size_ == maxSize){ //if the size of this equals the maxSize, for loop which adds the remaining last coefficient into the array
        for (int i = minSize; i<=maxSize -1; i++){
            newArr[i] = coefficients.select(i);
        }
    }
    Polynomial *newPolynomial = new Polynomial(newArr, maxSize); //creates a new polynomial, with size maxSize
    return newPolynomial; //returns the new polynomial
}
Polynomial* Polynomial::sub(Polynomial* rhs) {
    int maxSize, minSize, temp;
    if(size_>= rhs->size_){ //checks if the size of the this polynomial is great than the size of the rhs polynomial list
        maxSize = size_; //makes the maximum size of the polynomial, the size of the this polynomial list
        minSize = rhs->size_; //makes the minimum size of the polynomial, the size of the rhs polynomial list
    }
    else {
        minSize = size_;//makes the minimum size of the polynomial, the size of the this polynomial list
        maxSize = rhs->size_; //makes the maximum size of the polynomial, the size of the rhs polynomial list
    }
    int* newArr = new int[maxSize](); //initializing a new array with the maximum possible size, maxSize

    for(int i=0; i<=minSize-1; i++){ //for loop which loops through the index of the polynomial list which is smaller/or assigned minSize
        temp = this->coefficients.select(i) - rhs->coefficients.select(i); // temp value which equals the value of the difference of the coefficients in front of the according exponent degree
        newArr[i] = temp; //replaces the value at the according index in the this polynomial list, with the difference value that was assigned to temp
    }
    if(size_ == maxSize){ //if the size of this is smaller than the maxSize
        for(int i = minSize; i<=maxSize-1; i++){ //for loop which loops through the index of the polynomial list which is larger/or assigned maxSize
            newArr[i] = this->coefficients.select(i);//replaces the remaining values at the according index in the this polynomial list, with the default value in the max list because it is being added with 0
        }
    } else { //for loop which inverses the numbers to become negative
        for (int i = minSize; i<=maxSize -1; i++){
            newArr[i] = rhs->coefficients.select(i)*(-1);
        }
    }
    Polynomial *newPolynomial = new Polynomial(newArr, maxSize); //creates a new polynomial, with size maxSize
    return newPolynomial; //returns the new polynomial
}
Polynomial* Polynomial::mul(Polynomial* rhs) {
    int arrSize = size_ + rhs->size_ -1; //maximum possible size of the array is this polynomial list size plus the rhs list size
    int* newArr = new int[arrSize](); //initializing a new array with the maximum possible size, arrSize
    int temp;
    for(int i = 0; i<size_; i++){ //for loop which iterates through the index of the this polynomial
        for(int j = 0; j<rhs->size_; j++){ //for loop which iterates through the index of the rhs polynomial
            temp = this->coefficients.select(i) * rhs->coefficients.select(j); //temp value which equals the product of the coefficients of the this and rhs polynomial at the according index
            newArr[i+j] = newArr[i+j] + temp; //the (i+j)th element in the product list array is the ith element in the this polynomial times the jth element in the rhs list
        }
    }
    Polynomial *newPolynomial = new Polynomial(newArr, arrSize); //creates a new polynomial, with size arrSize which is size of the this list + the size of the rhs list minus 1
    return newPolynomial; //returns the new polynomial
}

void Polynomial::print() {
    int temp;
    int count =0;
    for(int i = 0; i<size_; i++){
        if (coefficients.select(i) != 0)
            count++; //increases the value of count, everytime there is an integer that is not a 0 is found
    }
    int addSymbol = count -1; //new int variable which holds the number of plus symbols required in the output, which is 1 less than the number of terms
    for(int i=size_-1; i>=0; i--){
        temp = this->coefficients.select(i); //temp value equals the value of the coefficient at the specified index of the exponential degree
        if(temp == 0){
            continue; //continues with the program if the value is a 0
        }
        if(temp<0){ //if the value of the coefficient is less than 0, making it negative, it adds brackets around the -
            cout<<"("<<temp<<")x^"<<i;
        }
        else{
            cout<<temp<<"x^"<<i;
        }
        if(i>0 && i<size_ && addSymbol>0){ //only adds a plus if the index is greater than 0 and less than the size of this && if addSymbol is greater than 0
            cout<<" + ";
            addSymbol--; //decreases the number of addition signs required after going through this condition and outputting one
        }
    }
    cout<<endl;
}
