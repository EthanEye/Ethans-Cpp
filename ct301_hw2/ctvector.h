#ifndef CT_VECTOR_H
#define CT_VECTOR_H

// ============================================================================
// CT 301 - HW#2 (Summer 2026) - ctvector.h  [STUDENT STARTER]
// ----------------------------------------------------------------------------
// You implement every body marked  // TODO . Do NOT change any signature.
// All includes and all type aliases are given. A set of functions is written
// for you as worked examples; the rest are signatures with a one-line hint.
//
//   The aliases below use "using NAME = TYPE;". You may see the older spelling
//   "typedef TYPE NAME;" in other code; they mean the same thing (see the
//   assignment document for why both exist).
//
// Standard: C++26.  Build: -std=c++26 -Wall -Wextra -Wpedantic
//                          -fsanitize=address,undefined -g
// You may NOT use std::vector or smart pointers. Manage storage with raw
// pointers. Every element you construct must be destroyed exactly once.
//
// ----------------------------------------------------------------------------
//  WARNING: every // TODO body below is a NON-FUNCTIONAL PLACEHOLDER, and the
//  worked examples call into them. The file builds and runs from day one (each
//  constructor delegates to Vector() so the object is a valid EMPTY vector),
//  but until you replace a TODO that operation does the WRONG thing. The given
//  insert/emplace/push_back will not work until the helpers they call
//  (push_back, emplace_back, grow_if_needed, begin/end, ...) are implemented.
//  Do not trust any result until its TODO is done.
// ============================================================================

#include <cstddef>          // std::size_t, std::ptrdiff_t
#include <stdexcept>        // std::out_of_range, std::length_error, std::logic_error
#include <memory>           // std::uninitialized_*, std::destroy_*
#include <algorithm>        // std::rotate, std::equal, std::move
#include <limits>           // std::numeric_limits
#include <iterator>         // std::reverse_iterator
#include <initializer_list> // std::initializer_list
#include <utility>          // std::move, std::forward

// Warning suppressor: lets the stubs keep readable, named parameters before
// they are used. Delete this once everything is implemented.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

namespace ct
{

    template <typename T>
    class Vector
    {
    public:
        // ---- Member type aliases (given) --------------------------------------
        using value_type = T;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;
        using iterator = T *;
        using const_iterator = const T *;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;

        // ---- Constructors / destructor ----------------------------------------
        Vector() noexcept
            : elements_(nullptr), size_(0), capacity_(0) {} // given

        explicit Vector(size_type count) : Vector()
        { // given
            if (count > 0)
            {
                reserve(count);
                std::uninitialized_value_construct_n(elements_, count);
                size_ = count;
            }
        }

        Vector(size_type count, const T &value) : Vector()
        {
            // TODO: make room for count, then copy-construct that many values.
            if (count > 0)
            {
                reserve(count); // allocates memory initializes elements_ member to that address
                for (size_type i = 0; i < count; i++)
                {
                    new (elements_ + i) T(value); // placement new copy value into each slot
                }
                size_ = count;
            }
        }
        // a initializer list uses curly brackets { }
        Vector(std::initializer_list<T> list) : Vector()
        {
            // TODO: make room for list.size(), then copy the elements in.
            reserve(list.size());
            for (const T &val : list)
            {
                new (elements_ + size_) T(val);
                size_++;
            }
        }

        // Range constructor from a pointer range. A const_iterator (pointer) cannot
        // be confused with an integer count, so no template and no concepts.
        Vector(const_iterator first, const_iterator last) : Vector()
        {
            size_type range = static_cast<size_type>(last - first);
            if (range > 0)
            {
                reserve(range);
                for (size_type i = 0; i < range; i++)
                {
                    new (elements_ + i) T(first[i]);
                }
                size_ = range;
            }
        }

        Vector(const Vector &other) : Vector()
        {
            // TODO: make room for other.size(), then copy its elements in.
            size_type new_size = other.size_;
            if (new_size > 0)
            {
                reserve(new_size);
                for (size_type i = 0; i < new_size; i++)
                {
                    new (elements_ + i) T(other.elements_[i]);
                }
            }
            size_ = new_size;
        }

        Vector(Vector &&other) noexcept : Vector()
        {
            // TODO: steal other's buffer/size/capacity; leave other empty.
            elements_ = other.elements_;
            size_ = other.size_;
            capacity_ = other.capacity_;

            other.elements_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        ~Vector()
        { // given
            clear();
            deallocate();
        }

        // ---- Assignment -------------------------------------------------------
        Vector &operator=(const Vector &other)
        {
            // TODO: copy-assign (copy-and-swap is one clean way).
            return *this;
        }

        Vector &operator=(Vector &&other) noexcept
        {
            // TODO: release what you hold, then steal from other.
            return *this;
        }

        Vector &operator=(std::initializer_list<T> list)
        { // given
            assign(list);
            return *this;
        }

        // ---- assign -----------------------------------------------------------
        void assign(const_iterator first, const_iterator last)
        {
            // TODO: drop current contents, then take the elements of [first,last).
        }

        void assign(size_type count, const T &value)
        {
            // TODO: drop current contents, then hold count copies of value.
        }

        void assign(std::initializer_list<T> ilist)
        { // given (delegates)
            assign(ilist.begin(), ilist.end());
        }

        // ---- Element access ---------------------------------------------------
        // back() is given as the worked example. Mirror it for at/[]/front/data.
        T &at(size_type pos) { throw std::logic_error("ct::Vector: TODO at"); }
        const T &at(size_type pos) const { throw std::logic_error("ct::Vector: TODO at"); }
        T &operator[](size_type pos) { throw std::logic_error("ct::Vector: TODO operator[]"); }
        const T &operator[](size_type pos) const { throw std::logic_error("ct::Vector: TODO operator[]"); }
        T &front() { throw std::logic_error("ct::Vector: TODO front"); }
        const T &front() const { throw std::logic_error("ct::Vector: TODO front"); }

        T &back()
        { // given
            if (empty())
                throw std::out_of_range("ct::Vector::back: empty");
            return elements_[size_ - 1];
        }
        const T &back() const
        { // given
            if (empty())
                throw std::out_of_range("ct::Vector::back: empty");
            return elements_[size_ - 1];
        }

        T *data() noexcept { return nullptr; /* TODO */ }
        const T *data() const noexcept { return nullptr; /* TODO */ }

        // ---- Forward iterators ------------------------------------------------
        iterator begin() noexcept { return nullptr; /* TODO */ }
        const_iterator begin() const noexcept { return nullptr; /* TODO */ }
        iterator end() noexcept { return nullptr; /* TODO */ }
        const_iterator end() const noexcept { return nullptr; /* TODO */ }
        const_iterator cbegin() const noexcept { return nullptr; /* TODO */ }
        const_iterator cend() const noexcept { return elements_ + size_; } // given

        // ---- Reverse iterators ------------------------------------------------
        // rbegin() is given. Mirror it: rend maps to begin(), and the const/c-
        // versions follow the same shape (use std::reverse_iterator).
        reverse_iterator rbegin() noexcept { return reverse_iterator(end()); } // given
        const_reverse_iterator rbegin() const noexcept { return {}; /* TODO */ }
        reverse_iterator rend() noexcept { return {}; /* TODO */ }
        const_reverse_iterator rend() const noexcept { return {}; /* TODO */ }
        const_reverse_iterator crbegin() const noexcept { return {}; /* TODO */ }
        const_reverse_iterator crend() const noexcept { return {}; /* TODO */ }

        // ---- Capacity ---------------------------------------------------------
        bool empty() const noexcept { return false; /* TODO */ }
        size_type size() const noexcept { return 0; /* TODO */ }
        size_type capacity() const noexcept { return 0; /* TODO */ }
        size_type max_size() const noexcept
        { // given
            return std::numeric_limits<size_type>::max() / sizeof(T);
        }

        // The heart of the assignment. Grow the buffer to hold at least new_cap.
        //   1. allocate raw storage (allocate()).   3. destroy the old elements.
        //   2. move your live elements into it.      4. free the old buffer; adopt new.
        // Do nothing if new_cap <= capacity_.
        void reserve(size_type new_cap)
        {
            // TODO
            if (new_cap <= capacity_)
                return;
            T *new_data = allocate(new_cap);
            std::uninitialized_move_n(elements_, newcap_, new_data); // move objects into empty memory, one by one
            std::destroy_n(elements_, newcap_);                      // call destructor on each element but dosent free the memroy
            deallocate(elements_);                                   // calls ::operator delete whichs free the memory for itself in the future or another process

            elements_ = new_data;
            capacity_ = new_cap;
        }

        void shrink_to_fit()
        {
            // TODO: reduce capacity to size (the same four steps, smaller).
        }

        // ---- Modifiers --------------------------------------------------------
        void clear() noexcept
        {
            // TODO: destroy every element; size becomes 0 (capacity unchanged).
        }

        iterator insert(const_iterator pos, const T &value)
        { // given
            const size_type index = static_cast<size_type>(pos - begin());
            push_back(value);
            std::rotate(begin() + index, end() - 1, end());
            return begin() + index;
        }

        iterator insert(const_iterator pos, T &&value)
        {
            // TODO: like the given insert, but move the value in.
            return begin() + (pos - begin());
        }

        iterator insert(const_iterator pos, size_type count, const T &value)
        {
            // TODO: insert count copies of value before pos.
            return begin() + (pos - begin());
        }

        iterator insert(const_iterator pos, const_iterator first, const_iterator last)
        {
            // TODO: insert the range [first,last) before pos.
            return begin() + (pos - begin());
        }

        iterator insert(const_iterator pos, std::initializer_list<T> il)
        { // given (delegates)
            return insert(pos, il.begin(), il.end());
        }

        template <typename... Args>
        iterator emplace(const_iterator pos, Args &&...args)
        { // given
            const size_type index = static_cast<size_type>(pos - begin());
            emplace_back(std::forward<Args>(args)...);
            std::rotate(begin() + index, end() - 1, end());
            return begin() + index;
        }

        iterator erase(const_iterator pos)
        {
            // TODO: remove the element at pos; return iterator to the next one.
            return begin() + (pos - begin());
        }

        iterator erase(const_iterator first, const_iterator last)
        {
            // TODO: remove [first, last); return iterator to the element after.
            return begin() + (first - begin());
        }

        void push_back(const T &value)
        {
            // TODO: if full, grow; then construct a copy of value at the end.
        }

        void push_back(T &&value)
        { // given
            grow_if_needed(1);
            new (elements_ + size_) T(std::move(value));
            ++size_;
        }

        template <typename... Args>
        void emplace_back(Args &&...args)
        {
            // TODO: if full, grow; then construct from args at the end.
        }

        void pop_back()
        {
            // TODO: destroy the last element; size shrinks by one.
        }

        void resize(size_type count)
        {
            // TODO: shrink (destroy tail) or grow (value-initialize new tail).
        }

        void resize(size_type count, const T &value)
        {
            // TODO: like resize(count), but fill new slots with value.
        }

        void swap(Vector &other) noexcept
        {
            // TODO: swap the buffer pointer, size, and capacity with other.
        }

    private:
        T *elements_;
        size_type size_;
        size_type capacity_;

        static constexpr size_type initSize = 8;  // suggested first capacity
        static constexpr size_type incFactor = 2; // suggested 2x growth

        // TODO: growth policy. If size_ + extra would not fit, grow capacity_
        // (double it, or start at initSize) by calling reserve().
        void grow_if_needed(size_type extra)
        {
            // TODO
        }

        // TODO: raw storage helpers (the memory is yours to manage).
        //   allocate(n):  uninitialized space for n objects, NO constructors run.
        //                 The raw call is  ::operator new(sizeof(T) * n)  cast to T*.
        //   deallocate(): free the buffer with  ::operator delete(elements_) .
        T *allocate(size_type n)
        {
            // TODO
            void *raw = ::operator new(sizeof(T) * n); // stores pointer first no type yet
            T *ptr = static_cast<T *>(raw);            // determine the type needed

            return ptr;
        }
        void deallocate() noexcept
        {
            ::operator delete(ptr);
        }
    };

    // ---- Non-member functions ------------------------------------------------
    template <typename T>
    bool operator==(const Vector<T> &lhs, const Vector<T> &rhs)
    {
        // TODO: equal sizes and equal elements in order.
        return false;
    }

    template <typename T> // given (delegates)
    bool operator!=(const Vector<T> &lhs, const Vector<T> &rhs)
    {
        return !(lhs == rhs);
    }

    // Given. This non-member swap forwards to the MEMBER swap you write:
    // it calls lhs.swap(rhs); your member swap exchanges elements_, size_, and
    // capacity_ (use std::swap on each member).
    template <typename T> // given (delegates)
    void swap(Vector<T> &lhs, Vector<T> &rhs) noexcept
    {
        lhs.swap(rhs);
    }

} // namespace ct

#pragma GCC diagnostic pop

#endif // CT_VECTOR_H
