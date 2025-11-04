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

    MinHeap() { size = 0; } //constructor size = 0

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        if (size == 64) throw out_of_range("MinHeap stack overflow"); //checks elements within index array
        data[size] = idx; //assigns the index to the position, or next available index
        upheap(size, weightArr); //sends the position to upheap with global array so swapping can be done based on weight
        size++; //update size of index array
    }
    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        if (size == 0) throw out_of_range("MinHeap stack underflow"); //assumes nothing is in array
        int mindex = data[0];
        size--; //decrease size since pop function removes one
        data[0] = data[size]; //swap index 0 with index n-1
        downheap(0, weightArr); //reorders the array based on global array values
        return mindex;
        // Replace root with last element, then call downheap()
    }
//use upheap for inserting
    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) { //out of bounds condition checker
            int parentPos = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parentPos]]) { //checks associated weights using global array
                int temp = data[pos];
                data[pos] = data[parentPos];
                data[parentPos] = temp;
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
        while (pos < size) {
            //ensures position is not out of bounds
            int left = pos * 2 + 1; //assign left and right child
            int right = pos * 2 + 2;
            if (left >= size) break; //condition for reaching a leaf node -- no more children
            int smallchild = left;
            if (right < size) {
                int leftn = data[left];
                int rightn = data[right];
                if (weightArr[data[right]] < weightArr[data[left]] ) { //smallchild can only be right if it exists
                    smallchild = right;
                }
            }
            int small = data[smallchild];
            int current = data[pos];

            if (weightArr[small]<weightArr[current]) {
                int temp = data[small];
                data[small] = data[pos];
                data[pos] = temp;
                pos = smallchild;
            }
            else { break;
            }
        }
    }
};


#endif