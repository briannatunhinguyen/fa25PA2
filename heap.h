//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <fstream> //string formatting
#include<stack> //needed to use stacks
#include<string> //std::string
using namespace std;

struct MinHeap {
    int data[64]; //an array that can hold 64 int values representing indices
    int size; //total number of nodes in data[], updated as program runs

    MinHeap() { size = 0; } //constructor

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        if (size == 64) throw out_of_range("MinHeap stack overflow"); //checks elements within index array
        int pos = size; //assigns pos to the next available index of the array
        data[pos] = idx; //assigns the index to the position, or next available index
        upheap(pos, weightArr); //sends the position to upheap with global array so swapping can be done based on weight
        size++; //update size of index array
    }
    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0) throw out_of_range("MinHeap stack underflow"); //assumes nothing is in array
        int mindex = data[0];
        data[0] = data[size - 1]; //swap index 0 with index n-1
        size--; //decrease size since pop function removes one
        downheap(0, weightArr); //reorders the array based on global array values
        return mindex;
        // Replace root with last element, then call downheap()
    }
//use upheap for inserting
    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) { //out of bounds condition checker
            int parentPos = (pos - 1) / 2;
            if (weightArr[pos] < weightArr[parentPos]) { //checks associated weights using global array
                swap(data[parentPos], data[pos]); //swaps index array based on check
                pos = parentPos;
            }
            else {
                break;
            }
        }
    }
//use downheap for removal
    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
    while (pos < size) { //ensures position is not out of bounds
        int left = pos * 2 + 1; //assign left and right child
        int right = pos * 2 + 2;
        if (left >= size) break; //condition for reaching a leaf node -- no more children
        int smallchild = left;
        if (right < size && weightArr[right] < weightArr[left] ) { //smallchild can only be right if it exists
            smallchild = right;
        }
        if (weightArr[pos] <= weightArr[smallchild]) break; //compares node with small child

        swap(data[pos], data[smallchild]);
        pos = smallchild;
    }
    }
};

#endif