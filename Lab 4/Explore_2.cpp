#include <iostream>

class IntArray
{
public:
    IntArray(int n) : data_(new int[n]), size_(n)
    {
        for (int i = 0; i < n; ++i)
            data_[i] = 0;
    }
    ~IntArray() { delete[] data_; }

    // TODO: add a copy constructor and a copy assignment operator that make a
    // DEEP copy (allocate a new buffer and copy the elements), so that two
    // IntArrays never share the same buffer.
    // 1.
    // copy constructor takes a constant reference to the same type
    // const because you should modify the original while making a copy
    // & reference because if it took a value , it would need to copy the object to pass it in,
    // which would call the copy constructor again, leading to infinite recursion
    // 2.
    // The member initializer list initialize memebers before the constructor body runs.
    // 3.
    // The for loop copies each element from the other IntArray's data_ to the new data_ array.
    // since data is a pointer we want to call new.

    IntArray(const IntArray &other) : data_(new int[other.size_]), size_(other.size_)
    {
        for (int i = 0; i < size_; ++i)
        {
            data_[i] = other.data_[i];
        }
    }

    // Copy assignment object already has data, must free it first
    // 1.
    // overload the assignment operator to handle deep copy assignment
    // 2.
    // self-assignment check: if the object is assigned to itself, we don't want to
    IntArray &operator=(const IntArray &other)
    {
        if (this == &other)
            return *this; // self-assignment check

        delete[] data_; // free OLD memory (constructor doesn't need this)

        size_ = other.size_;
        data_ = new int[size_];
        for (int i = 0; i < size_; i++)
            data_[i] = other.data_[i];

        return *this; // return *this (constructor doesn't need this)
    }

    int &at(int i) { return data_[i]; }
    int size() const { return size_; }

private:
    int *data_;
    int size_;
};

int main()
{
    IntArray a(3);
    a.at(0) = 10;
    a.at(1) = 20;
    a.at(2) = 30;
    IntArray b = a; // copy; with a DEEP copy, b gets its own buffer
    b.at(0) = 99;   // this must NOT change a
    IntArray c(5);
    c = a;
    c.at(0) = 55; // this must NOT change a
    std::cout << "a[0] = " << a.at(0) << " (should stay 10)" << std::endl;
    std::cout << "b[0] = " << b.at(0) << " (should be 99)" << std::endl;
    std::cout << "c[0] = " << c.at(0) << " (should be 55)" << std::endl;
    return 0;
}