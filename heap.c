/**
	@file
	@author Julia Frances <jrf343@drexel.edu>
	@date August 25, 2022
	@section DESCRIPTION
 
	Creating a heap for Dijsktra's Algorithm
 */


#include "stdlib.h"
#include "stdio.h"
#include "heap.h"
#include "limits.h"

// make new empty heap
Heap* newHeap(int size){
  Heap* H = malloc(sizeof(Heap)); // allocated memory for heap
  H->data = malloc(sizeof(Node*)*size); // allocate memory for node array in heap
  H->maxSize = size;
  H->currentSize = 0;
  return H;
}

// Insert node n into heap H with path weight w
void insert(Heap* H, int name, int weight){
  // if heap is full, go to expand function to create more space
  if (H->currentSize == H->maxSize) {
    expand(H);
  }
  Node* newNode = malloc(sizeof(Node)); // allocate memory for new node
  newNode->name = name;
  newNode->weight = weight;
  H->data[H->currentSize] = newNode; // insert node in the next available space
  H->currentSize++; // increase size
  upheap(H, H->currentSize-1); // readjust properties of heap
  return;
}

// Return the node with the minimum weight from H
int min(Heap* H){
  if (isEmpty(H)) {
    return 0;
  }
  return H->data[0]->name; // return identifier of node for distance/path array in main
}

// Delete the node with the minimum weight from the heap
void deleteMin(Heap* H){
  if (isEmpty(H)) {
    return;
  }
  // swap root and last element
  swap(H, 0, H->currentSize-1);
  // decrease size
  H->currentSize = H->currentSize - 1;
  downheap(H, 0); // readjust properties of heap
}

// Delete all items from heap and free memory
void deleteHeap(Heap* H){
	//Free Struct
  free(H);
  H = NULL;
}

// find parent Node index
int parent(int i){
  if (i == 0) {
    return 0;
  }
  return (i-1)/2;
}

// find left and right child node indexes
int leftChild(int i){
  return 2*i +1;
}

int rightChild(int i){
  return 2*i + 2;
 }

// Swap values in Heap
void swap(Heap* H, int i, int j){
  Node* temp = H->data[i];
  H->data[i] = H->data[j];
  H->data[j] = temp;
  return;
}

// Determines if heap is empty
int isEmpty(Heap *H){
  if (H->currentSize == 0) {
    return 1;
  } else {
    return 0;
  }
}

// Expands heap size by allocating new array and copying values
void expand(Heap* H){
  int newSize = 2*H->currentSize; // double the size of original array for new array
  Node** newdata = malloc(sizeof(Node*)*newSize); // new array of node pointers
  // copy data to new array
  for (int i = 0; i < H->currentSize+1; i++) {
    newdata[i] = H->data[i];
  }
  H->data = newdata;
  H->maxSize = newSize;
  return;
}

// Swap recursively based on weight of parent after insertion in order to repair heap order
void upheap(Heap* H, int index){
  int p = parent(index); // determine parent
  if (p < 0) {
    return;
  }
  int pWeight = H->data[index]->weight; // get parents weight
  // if parents weight is less than node's weight, heap is valid
  if (pWeight <= H->data[index]->weight) {
    return;
  }
  swap(H, index, p); // otherwise, swap with parent
  upheap(H, p); // continue until valid heap
}

void downheap(Heap* H, int index){
  // determine location of children
  int leftIndex = leftChild(index);
  int rightIndex = rightChild(index);
  if (leftIndex >= H->currentSize) {
    return; // no children
  }
  int minIndex = pickSmallerChild(H, leftIndex, rightIndex); // determine child with smallest weight
  // repair heap 
  if (H->data[index]->weight > H->data[minIndex]->weight) {
    swap(H, index, minIndex);
    downheap(H, minIndex);
  }
}

int pickSmallerChild(Heap* H, int leftIndex, int rightIndex){
  int minIndex;
  // if no right child, left is smaller
  if (rightIndex >= H->currentSize) {
    minIndex = leftIndex;
  } else {
    // compare weights of two children
    if (H->data[leftIndex]->weight < H->data[rightIndex]->weight) {
      minIndex = leftIndex;
    } else {
      minIndex = rightIndex;
    }
  }
  return minIndex;
}