#include "minheap.h"

template <class T>
void MinHeap<T> :: swap(int pos_x,int pos_y) {
    T temp = heapArray[pos_x];
    heapArray[pos_x] = heapArray[pos_y];
    heapArray[pos_y] = temp;
}

template <class T>
void MinHeap<T> :: BuildHeap() {
    for (int i = CurrentSize/2 - 1; i >= 0; i--) {
        SiftDown(i);
    }
}

template <class T>
MinHeap<T> :: MinHeap(const int n) {
    if(n < 0) return;
    CurrentSize = 0;
    MaxSize = n;
    heapArray = new T[MaxSize];
    BuildHeap();
}

template <class T>
MinHeap<T> :: MinHeap(const int n, T * arr) {
    if(n < 0) return;
    CurrentSize = n;
    MaxSize = n;
    heapArray = new T[MaxSize];
    for (int i = 0; i < n; i++) heapArray[i] = arr[i];
    BuildHeap();
}

template <class T>
MinHeap<T> :: ~MinHeap() {
    delete []heapArray;
}

template <class T>
bool MinHeap<T> :: isEmpty() {
    return CurrentSize == 0;
}

template <class T>
bool MinHeap<T> :: isLeaf(int pos) const {
    return (pos >= CurrentSize/2) && (pos < CurrentSize);
}

template <class T>
int MinHeap<T> :: LeftChild(int pos) const {
    return 2*pos+1;
}

template <class T>
int MinHeap<T> :: RightChild(int pos) const {
    return 2*pos+2;
}

template <class T>
int MinHeap<T> :: Parent(int pos) const {
    return (pos-1)/2;
}

template <class T>
void MinHeap<T> :: Insert(const T & newNode) {
    heapArray[CurrentSize] = newNode;
    SiftUp(CurrentSize);
    CurrentSize++;
}

template <class T>
T & MinHeap<T> :: RemoveMin() {
    swap(0,--CurrentSize);
    if(CurrentSize > 1) SiftDown(0);
    return heapArray[CurrentSize];
}

template <class T>
bool MinHeap<T> :: Remove(int pos, T & node) {
    if((pos < 0) || (pos >= CurrentSize)) return false;
    node = heapArray[pos];
    heapArray[pos] = heapArray[--CurrentSize];
    if(heapArray[Parent(pos)] > heapArray[pos]) SiftUp(pos);
    else SiftDown(pos);
    return true;
}

template <class T>
void MinHeap<T> :: SiftUp(int pos) {
    int temppos = pos;
    T temp = heapArray[temppos];
    while((temppos > 0) && (heapArray[Parent(temppos)] > temp)) {
        heapArray[temppos] = heapArray[Parent(temppos)];
        temppos = Parent(temppos);
    }
    heapArray[temppos] = temp;
}

template <class T>
void MinHeap<T> :: SiftDown(int pos) {
    int i = pos;
    int j = LeftChild(i);
    T temp = heapArray[i];
    while(j < CurrentSize) {
        if((j < CurrentSize - 1) && (heapArray[j] > heapArray[j+1])) j++;
        if(temp > heapArray[j]) {
            heapArray[i] = heapArray[j];
            i = j;
            j = LeftChild(i);
        }
        else break;
    }
    heapArray[i] = temp;
}