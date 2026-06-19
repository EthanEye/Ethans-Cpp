#include <iostream>

int main() {
    int data[5] = {2, 4, 6, 8, 10};
    int* begin = data;           // points at the first element
    int* end   = data + 5;       // points one past the last
    for (int* p = begin; p != end; ++p)
        std::cout << *p << " ";
    std::cout << "\n";
    // p[i] and *(p + i) are the same thing:
    std::cout << begin[2] << " == " << *(begin + 2) << "\n";
    return 0;
}

