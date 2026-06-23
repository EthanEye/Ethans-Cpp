#include <iostream>
#include <string>

// TODO: make Box a template so it works for ANY type T, not just int.
// (Add  template <typename T>  above the class, and replace int with T.)
template <typename T> 
class Box {
public:
    Box(T value) : value_(value) {}
    T get() const { return value_; }
    void set(T value) { value_ = value; }
private:
    T value_;
};

int main() {
    Box<int> a(42);                 // these compile only after you templatize Box
    Box<double> c(52);   
    Box<std::string> b("hello");
    std::cout << a.get() << " " << b.get() << " " << c.get() << "\n";   // expect: 42 hello 52
    return 0;
}