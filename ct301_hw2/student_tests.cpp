//
// CT 301 - HW#2 (Summer 2026) - student_tests.cpp  [your tester, not graded]
// ----------------------------------------------------------------------------
// This is a tester for your own use. It is NOT the grader: the real grading is
// automated and uses tests you will not see. Each test below is a named
// function. A few are written for you as worked examples; the rest are marked
// TODO for you to finish. Filling them in is how you build confidence that your
// vector and driver are correct.
//
// Build:  make tests        Run:  ./student_tests
//
// How to write one: build a small vector, do something to it, then call
// check(condition, "what you are checking"). Test small cases you can verify by
// hand first, then reach for the larger generators in fixtures.h.
// ----------------------------------------------------------------------------
#include "ctvector.h"
#include "driver.h"
#include "fixtures.h"
#include <iostream>
#include <string>

static int g_failures = 0;
static int g_todo = 0;

// Use this in a test: it prints PASS or FAIL and remembers any failure.
static void check(bool condition, const std::string& what) {
    std::cout << (condition ? "  [PASS] " : "  [FAIL] ") << what << "\n";
    if (!condition) ++g_failures;
}

// Call this from a test you have not written yet, so it shows up as unfinished
// instead of silently "passing". Delete the call once you write the test.
static void todo(const std::string& test_name) {
    std::cout << "  [TODO] " << test_name << " is not written yet\n";
    ++g_todo;
}

// ============================================================================
// Worked examples (these are written for you)
// ============================================================================

void test_push_back_and_size() {
    std::cout << "test_push_back_and_size\n";
    ct::Vector<int> v;
    check(v.size() == 0, "a new vector has size 0");
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    check(v.size() == 3, "size is 3 after three push_back");
    check(v[0] == 10 && v[2] == 30, "elements are stored in order");
    check(v.back() == 30, "back() is the last element");
    v.pop_back();
    check(v.size() == 2, "size is 2 after pop_back");
}

void test_copy_is_independent() {
    std::cout << "test_copy_is_independent\n";
    ct::Vector<int> a = {1, 2, 3};
    ct::Vector<int> b = a;           // copy constructor
    b[0] = 99;                       // change the copy
    check(a[0] == 1, "changing the copy does not change the original");
    check(b[0] == 99, "the copy reflects its own change");
    check(a.size() == b.size(), "copy has the same size");
}

void test_driver_on_world_cup() {
    std::cout << "test_driver_on_world_cup\n";
    using namespace ctlab;
    ct::Vector<int> cups = world_cup_titles();   // {5,4,4,3,2,2,1,1}
    check(total(cups) == 22, "titles total to 22");
    check(largest(cups) == 5, "the most titles by one team is 5");
    check(count_even(cups) == 4, "four of the title counts are even");
    check(contains(cups, 3) && !contains(cups, 7), "contains 3 but not 7");
}

// ============================================================================
// Your turn (finish these). Replace the todo(...) line with real check(...)
// calls. The comment in each says what to test.
// ============================================================================

void test_at_is_bounds_checked() {
    std::cout << "test_at_is_bounds_checked\n";
      // TODO: reserve a larger capacity on a small vector. Check that capacity()
    // grew to at least what you asked for, that size() did not change, and that
    // the existing elements are still correct.
    ct::Vector<int> v{1, 2, 3};
    
    // test operator[] returns right element
    check(v[0] == 1, "operator[] index 0");
    check(v[1] == 2, "operator[] index 1");
    check(v[2] == 3, "operator[] index 2");
    
    // test at() throws out_of_range when out of bounds
    bool threw = false;
    try {
        v.at(10);
    } catch (const std::out_of_range&) {
        threw = true;
    }
    check(threw, "at() throws out_of_range");
}

void test_reserve_grows_capacity() {
    std::cout << "test_reserve_grows_capacity\n";
     std::cout << "test_reserve_grows_capacity\n";

    ct::Vector<int> v{1, 2, 3};
    
    size_t old_capacity = v.capacity();
    v.reserve(100);
    
    check(v.capacity() >= 100, "capacity >= 100 after reserve");
    check(v.capacity() > old_capacity, "capacity grew");
    check(v.size() == 3, "size unchanged after reserve");
    check(v[0] == 1, "elements preserved after reserve");
    check(v[1] == 2, "elements preserved after reserve");
    check(v[2] == 3, "elements preserved after reserve");
}

void test_iterators_walk_in_order() {
    std::cout << "test_iterators_walk_in_order\n";
    // TODO: build a vector, sum it by walking begin() to end(), and check the
    // sum. Then check that rbegin()/rend() visit the elements in reverse.

    ct::Vector<int> v{1, 2, 3, 4, 5};

    // sum with forward iterators
    int sum = 0;
    for (auto it = v.begin(); it != v.end(); ++it)
        sum += *it;
    check(sum == 15, "forward iterator sum");

    // check reverse iterators visit in reverse
    ct::Vector<int> reversed;
    for (auto it = v.rbegin(); it != v.rend(); ++it)
        reversed.push_back(*it);

    check(reversed[0] == 5, "rbegin starts at last element");
    check(reversed[4] == 1, "rend ends at first element");
    

}

void test_insert_and_erase() {
    std::cout << "test_insert_and_erase\n";

    ct::Vector<int> v{1, 2, 4};

    // insert 3 before the 4
    v.insert(v.begin() + 2, 3);
    check(v[0] == 1, "after insert: v[0] == 1");
    check(v[1] == 2, "after insert: v[1] == 2");
    check(v[2] == 3, "after insert: v[2] == 3");
    check(v[3] == 4, "after insert: v[3] == 4");
    check(v.size() == 4, "after insert: size == 4");

    // erase the 2 (index 1)
    v.erase(v.begin() + 1);
    check(v[0] == 1, "after erase: v[0] == 1");
    check(v[1] == 3, "after erase: v[1] == 3");
    check(v[2] == 4, "after erase: v[2] == 4");
    check(v.size() == 3, "after erase: size == 3");
}

void test_clear_then_reuse() {
    std::cout << "test_clear_then_reuse\n";
    // TODO: fill a vector, clear() it, check size() == 0 and empty() is true,
    // then push_back again and check it still works.
    ct::Vector<int> v{1, 2, 3, 4, 5};

    v.clear();
    check(v.size() == 0, "after clear: size == 0");
    check(v.empty(), "after clear: empty() is true");

    // reuse after clear
    v.push_back(10);
    v.push_back(20);
    check(v.size() == 2, "after reuse: size == 2");
    check(v[0] == 10, "after reuse: v[0] == 10");
    check(v[1] == 20, "after reuse: v[1] == 20");
}

void test_move_leaves_source_empty() {
    std::cout << "test_move_leaves_source_empty\n";
     ct::Vector<int> a{1, 2, 3};

    // move construct b from a
    ct::Vector<int> b(std::move(a));

    // b should have the elements
    check(b.size() == 3, "after move: b.size() == 3");
    check(b[0] == 1, "after move: b[0] == 1");
    check(b[1] == 2, "after move: b[1] == 2");
    check(b[2] == 3, "after move: b[2] == 3");

    // a is valid but unspecified — only check it won't crash
    check(a.size() == 0, "after move: source is empty");
}

void test_big_vector_via_generator() {
    std::cout << "test_big_vector_via_generator\n";

    ct::Vector<int> v = ctlab::make_sequence(1000);

    check(v.size() == 1000, "size == 1000");
    check(ctlab::total(v) == 500500, "total == 500500");
}

// ============================================================================
// Runner: add your new tests to this list as you write them.
// ============================================================================
int main() {
    test_push_back_and_size();
    test_copy_is_independent();
    test_driver_on_world_cup();
    test_at_is_bounds_checked();
    test_reserve_grows_capacity();
    test_iterators_walk_in_order();
    test_insert_and_erase();
    test_clear_then_reuse();
    test_move_leaves_source_empty();
    test_big_vector_via_generator();

    std::cout << "\n" << g_failures << " failed, " << g_todo << " still to write.\n";
    return g_failures == 0 ? 0 : 1;
}
