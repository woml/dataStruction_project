#ifndef MINHEAP_H
#define MINHEAP_H

template <class T>
class MinHeap {
    private:
        T * heapArray;
        int CurrentSize;
        int MaxSize;
        void swap(int pos_x,int pos_y);
        void BuildHeap();
    public:
        MinHeap(const int n);
        MinHeap(const int n, T * arr);
        ~MinHeap();
        bool isEmpty();
        bool isLeaf(int pos) const;
        int LeftChild(int pos) const;
        int RightChild(int pos) const;
        int Parent(int pos) const;
        void Insert(const T & newNode);
        T & RemoveMin();
        bool Remove(int pos, T & node);
        void SiftUp(int pos);
        void SiftDown(int pos);
};

#endif
