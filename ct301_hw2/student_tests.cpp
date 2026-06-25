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
    // TODO: build a small vector. Check that operator[] returns the right
    // element, and that at(pos) throws std::out_of_range when pos is past the
    // end (use a try/catch around at()).
    todo("test_at_is_bounds_checked");
}

void test_reserve_grows_capacity() {
    std::cout << "test_reserve_grows_capacity\n";
    // TODO: reserve a larger capacity on a small vector. Check that capacity()
    // grew to at least what you asked for, that size() did not change, and that
    // the existing elements are still correct.
    todo("test_reserve_grows_capacity");
}

void test_iterators_walk_in_order() {
    std::cout << "test_iterators_walk_in_order\n";
    // TODO: build a vector, sum it by walking begin() to end(), and check the
    // sum. Then check that rbegin()/rend() visit the elements in reverse.
    todo("test_iterators_walk_in_order");
}

void test_insert_and_erase() {
    std::cout << "test_insert_and_erase\n";
    // TODO: start from {1,2,4}. insert 3 before the 4 and check you get
    // {1,2,3,4}. Then erase the 2 and check you get {1,3,4}.
    todo("test_insert_and_erase");
}

void test_clear_then_reuse() {
    std::cout << "test_clear_then_reuse\n";
    // TODO: fill a vector, clear() it, check size() == 0 and empty() is true,
    // then push_back again and check it still works.
    todo("test_clear_then_reuse");
}

void test_move_leaves_source_empty() {
    std::cout << "test_move_leaves_source_empty\n";
    // TODO: build a vector, move-construct a second one from it, and check the
    // second has the elements. (A moved-from vector is valid but unspecified;
    // do not assume what is left in the source.)
    todo("test_move_leaves_source_empty");
}

void test_big_vector_via_generator() {
    std::cout << "test_big_vector_via_generator\n";
    // TODO: use make_sequence(1000) from fixtures.h. Check size() == 1000 and
    // total(...) == 500500. This grows the buffer through many reallocations.
    todo("test_big_vector_via_generator");
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
