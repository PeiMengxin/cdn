#ifndef __MINHEAP_H
#define __MINHEAP_H

template<class Elem>
void swap(Elem A[], int x, int y)
{
    Elem temp = A[x];
    A[x] = A[y];
    A[y] = temp;
}


template<class Elem>
class minheap
{
private:
    Elem *Heap;
    int size;
    int n;

public:
    minheap(Elem *A, int num, int max)
    {
        Heap = A;
        n = num;
        size = max;
        buildHeap();
    }

    bool isempty() const
    {
        return n<=0;
    }

    bool isLeaf(int pos)
    {
        return (pos>=n/2)&&(pos<n);
    }

    int leftchild(int pos)
    {
        return 2*pos+1;
    }

    int rightchild(int pos)
    {
        return 2*pos+2;
    }

    int parent(int pos)
    {
        return (pos-1)/2;
    }

    void siftdown(int pos)
    {
        while (!isLeaf(pos))
        {
            int j = leftchild(pos);
            int rc = rightchild(pos);
            if((rc<n)&&(Heap[j]>Heap[rc]))
            {
                j=rc;
            }
            if(!Heap[pos]>Heap[j])
            {
                return;
            }
            swap(Heap, pos, j);
            pos = j;
        }
    }

    void buildHeap()
    {
        for (int i = n/2-1;i>=0;i++)
        {
            siftdown(i);
        }
    }

    bool insert(Elem &val)
    {
        if(n>=size)
            return false;

        int curr = n++;
        Heap[curr] = val;

        while ((curr!=0)&&(Heap[curr]<Heap[parent(curr)]))
        {
            swap(Heap, curr, parent(curr));
        }
        return true;
    }

    Elem removemin()
    {
        swap(Heap, 0, --n);
        if(n!=0)
        {
            siftdown(0);
        }
        return Heap[n];
    }

    bool remove(int pos, Elem &it)
    {
        if ((pos < 0) || (pos >= n)) return false;
        swap(Heap, pos, --n);
        while (pos != 0 && (Heap[pos] < Heap[parent(pos)]))
        {
            swap(Heap, pos, parent(pos));
            pos = parent(pos);
        }
        //siftdown(pos);
        it = Heap[n];
        return true;
    }
};

#endif // __MINHEAP_H
