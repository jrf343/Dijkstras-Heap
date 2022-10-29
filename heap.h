/**
	@file
	@author Julia Frances <jrf343@drexel.edu>
	@date August 25, 2022
	@section DESCRIPTION
 
	A simple Heap class for Dijkstra's Algorithm
 */

#ifndef _HEAP_H_
#define _HEAP_H_
/**
	Node struct for min heap array
 */
struct Node{
  int name; // identifier
  int weight; // weight from weight(G)
};
typedef struct Node Node;

/**
	Heap as a classic min-heap stored using an array
 */
struct Heap{
	Node** data; // pointer to array of node pointers
	int maxSize; // max number of values the array can store
  int currentSize; // current amount of values
};
typedef struct Heap Heap;

/**
	Make a New empty heap
	@param size is the size
	@return Pointer to heap Object
 */
Heap* newHeap(int size);

/**
	Insert node n into heap H with path weight w
	@param n is the node name to insert
  @param H is the heap in which to insert
  @param w is the weight of the node
 */
void insert(Heap* H, int name, int weight);

/**
	Return the node's name with the minimum weight from H
  @param H is the heap in which to find the min
  @return min int
 */
int min(Heap* H);

/**
	Delete the node with the minimum weight from the heap
  @param H is the heap in which to delete the min
 */
void deleteMin(Heap* H);

/**
	Delete all items from heap and free memory
  @param H is the heap to delete
 */
void deleteHeap(Heap* H);

/**
	find the parent index for a node
  @param i is the node to find the parent of
  @return parent index
 */
int parent(int i);

/**
	find the left and right children's indexes for a node
  @param i is the node to find the children of
  @return child index
 */
int leftChild(int i);

int rightChild(int i);

/**
	Swap nodes in Heap
  @param H is the heap to swap within
  @params i, j are the node indexes to swap
 */
void swap(Heap* H, int i, int j);

/**
	Determines if heap is empty
  @param H is the heap to find empty or not
  @returns 1 if empty or 0 if not
 */
int isEmpty(Heap* H);

/**
	Expands heap size by allocating new array and copying values
  @param H is the heap to expand
 */
void expand(Heap* H);

/**
	Swap recursively based on value of parent after insertion in order to repair heap order
  @param H is the heap just suffering from an insert
  @param i is the starting index
 */
void upheap(Heap* H, int index);

/**
	Swap recursively based on value of child after deletion in order to repair heap order
  @param H is the heap just suffering from a deletion
  @param i is the starting index
 */
void downheap(Heap* H, int index);

/**
	Find minimum index of node's children
  @param H is the heap 
  @param leftIndex is the left child index
  @param rightIndex is the right child index
  @return the minimum index
 */
int pickSmallerChild(Heap* H, int leftIndex, int rightIndex);

#endif