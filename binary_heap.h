#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <functional>
#include <vector>
#include <algorithm>

template <typename T, typename Compare = std::less<T> >
class BinaryHeap {
public:
    explicit BinaryHeap(const Compare& comp = Compare()) : comp_{comp} {
        // the array_[0] we need not use it
        // for example:
        // 0   1   2   3   4   5   6
        //     5   7   8   10  12  15
        // why?
        // for array_[x], array[2x] and array_[2x + 1] is its left and right child
        // array_[x / 2] is its parent
        // if i from 0,then its childs: 1 = 2 * (0 + 1) - 1, 2 = 2 * (0 + 1) terrible...
        array_.emplace_back();
    }

    template <typename InputIter>
    BinaryHeap(InputIter first, InputIter last, const Compare& comp = Compare()) 
      : comp_{comp} {
        array_.emplace_back();
        array_.insert(array_.end(), first, last);
        auto array_size = array_.size();
        size_ = array_size > 1 ? array_size - 1 : 1;
        build_heap();
    }

    bool empty() const {
        return size_ == 0;
    }

    size_t size() const {
        return size_;
    }

    const T& top() const {
        return array_[1];  
    }
    
    void insert(const T& x) {
        size_t array_size = array_.size() - 1; // really element size
        if (size_ < array_size) {
            array_[size_ + 1] = x;
        } else {
            array_.push_back(x);
        }
        ++size_;
        up(size_);
    }

    void pop() {
        array_[1] = array_[size_--];
        down(1);
    }

    // store the top element to x
    void pop(T& x) {
        x = array_[1];
        pop();
    }

    void clear() {
        size_ = 0;
    }

private:
    void build_heap() {
        size_t i = size_ / 2;

        for (; i >= 1; --i) {
            down(i);
        }
    }

    void up(size_t idx) {
        auto element_to_up = array_[idx];

        size_t i = idx;
        while (i >= 1) {
            size_t parent_idx = i / 2;
            if (parent_idx < 1) {
                break;
            }

            if (comp_(element_to_up, array_[parent_idx])) {
                array_[i] = array_[parent_idx];
                i = parent_idx;
            } else {
                break;
            }
        }

        array_[i] = element_to_up;
    }

    
    void down(size_t idx) {
        auto element_to_down = array_[idx];

        size_t i = idx;
        while (i <= size_) {
            size_t left_idx = 2 * i;
            size_t right_idx = 2 * i + 1;
            size_t dst_idx = left_idx;
            if (left_idx > size_) {
                break;
            }

            if (right_idx <= size_ && comp_(array_[right_idx], array_[left_idx])) {
                dst_idx = right_idx;
            }

            if (comp_(array_[dst_idx], element_to_down)) {
                array_[i] = array_[dst_idx];
                i = dst_idx;
            } else {
                break;
            }
        }

        array_[i] = element_to_down;
    }

private:
    size_t size_ = 0;
    std::vector<T> array_;
    Compare comp_;
};

#endif
