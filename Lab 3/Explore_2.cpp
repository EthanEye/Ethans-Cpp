#include <iostream>

class IntBuffer
{
public:
    IntBuffer(int n)
    {
        // TODO: allocate an array of n ints with new[], and remember n
        int *arr = new int[n]();
        begin = &arr[0];
        buffSize = n;
    }
    ~IntBuffer()
    {
        // TODO: free the array with delete[]
        delete[] begin; // allocator knows this is the starting location of buffer so it deletes whole chunk of memory
    }
    void set(int i, int value)
    {
        int *element;
        if (i < buffSize)
        {
            element = begin + i;
            *element = value; // go to the address stored in element and put value there.
        }
        else
        {
            throw std::out_of_range("index out of bounds");
        }
    }
    int get(int i) const
    { /* TODO: return the value at index i */
        int *element;
        if (i < buffSize)
        {
            element = begin + i;
        }
        else
        {
            throw std::out_of_range("index out of bounds");
        }
        return *element;
    }
    int size() const { /* TODO: return how many ints this holds */ return buffSize; }

private:
    // TODO: a pointer to the array, and an int for the size
    int *begin;
    int buffSize;
};

int main()
{
    IntBuffer b(4);
    for (int i = 0; i < b.size(); ++i)
        b.set(i, i * i);
    for (int i = 0; i < b.size(); ++i)
        std::cout << b.get(i) << " ";
    std::cout << "\n"; // expect: 0 1 4 9
    return 0;          // b's destructor frees the memory here
}
