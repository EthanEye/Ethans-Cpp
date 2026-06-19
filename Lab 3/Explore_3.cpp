#include <iostream>
#include <new>     // placement new

struct Noisy {
    int id;
    Noisy(int i) : id(i) { std::cout << "construct " << id << "\n"; }
    ~Noisy()             { std::cout << "destroy "   << id << "\n"; }
};

int main() {
    // 1. Allocate RAW memory for 4 Noisy objects. NONE are constructed yet.
    void* raw = ::operator new(4 * sizeof(Noisy));
    Noisy* buf = static_cast<Noisy*>(raw);
    std::cout << "room for 4, constructed 0 so far\n";

    // 2. Construct only TWO, in place, with placement new.
    new (buf + 0) Noisy(1);
    new (buf + 1) Noisy(2);
    // buf[2] and buf[3] are allocated but NOT constructed. Leave them alone.

    // 3. Destroy the two we built by calling the destructor explicitly. No delete.
    (buf + 0)->~Noisy();
    (buf + 1)->~Noisy();

    // 4. Free the raw bytes (this calls no destructor).
    ::operator delete(raw);
    return 0;
}

// 1. First we allocate RAM for 4 Noisy objects, which are objects that print whenever something to them.
// No objects are created yet its just raw bytes on the heap, just empty space. 
// void* is a generic pointer thats saying we dont have a type yet
// ::operator new is used for allocating raw memory
// sizeof(Noisy) tells us how much byte this noisy object takes
// We use Noisy* buf = static_cast<Noisy*>(raw); then to convert the raw memory into a Noisy type.
// This is good when you dont know the amount of objects in a buffer you will need.
// 2. we than only create 2 noisy objects  with new and the first ( ) is the address where we want to 
// contruct the object. (buf + 0) = address of the first (buf + 1) = address of the second. 
// buf essentially points to the beining of the chunk of raw memory.
// 3. we call the destructor explicitly with ~Noisy() (buf + 0)->~Noisy(); (Tilde is ~) which destroys object 
//  and then another noisy object can be allocated there 
// ::operator delete(raw); will free the raw memory.