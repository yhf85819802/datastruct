#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#include <queue>
#include <algorithm>
#include <utility>

template <typename T>
class LeftistHeap {
public:
    LeftistHeap() : root_{nullptr} {}

    LeftistHeap(const LeftistHeap& rhs) {
       root_ = clone(rhs.root_);
    }

    LeftistHeap& operator=(const LeftistHeap& rhs) {
        if (this != &rhs) {
            clear();
            root_ = clone(rhs.root_);
        }

        return *this;
    }

    ~LeftistHeap() {
        clear();
    }

    bool empty() const {
        return root_ == nullptr;
    }

    const T& top() const {
        return root_->data;
    }

    void insert(const T& x) {
        auto node = new LeftistNode{x, nullptr, nullptr, 0};

        if (root_ == nullptr) {
            root_ = node;
            return;
        }

        root_ = merge(root_, node);
        if (calc_npl(root_->left) < calc_npl(root_->right)) {
            std::swap(root_->left, root_->right);
        }
    }

    void pop() {
        if (root_ == nullptr) {
            return;
        }

        auto old_root = root_;
        root_ = merge(root_->left, root_->right);
        delete old_root;
    }

    void pop(T& x) {
        if (root_ == nullptr) {
            return;
        }

        x = root_->data;
        pop();
    }

    void clear() {
        clear(root_);
        root_ = nullptr;
    }

    void merge(LeftistHeap& rhs) {
        if (this == &rhs) {
            return;
        }

        root_ = merge(root_, rhs.root_);
        rhs.root_ = nullptr;
    }

    template <typename InsertIter>
    void level_traverse(InsertIter&& it) const {
        if (root_ == nullptr) {
            return;
        }

        std::queue<LeftistNode*> queue;
        queue.push(root_);
        auto p = root_;

        while (!queue.empty()) {
            auto top_node = queue.front();
            *it++ = top_node->data;
            auto left = top_node->left;
            auto right = top_node->right;
            if (left) {
                queue.push(left);
            }
            if (right) {
                queue.push(right);
            }
            queue.pop();
        }
    }

private:
    struct LeftistNode {
        T data;
        LeftistNode* left;
        LeftistNode* right;
        int npl;

        LeftistNode(const T& data_, LeftistNode* left_ = nullptr,
            LeftistNode* right_ = nullptr, int npl_ = 0) 
            : data{data_}, left{left_}, right{right_}, npl{npl_} {} 
    };

    void clear(LeftistNode* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    int calc_npl(LeftistNode* node) {
        if (node == nullptr) {
            return -1;
        }

        auto left = node->left;
        auto right = node->right;

        if (left == nullptr || right == nullptr) {
            return 0;
        }

        return std::min(left->npl, right->npl) + 1;
    }

    LeftistNode* merge(LeftistNode* lhs, LeftistNode* rhs) {
        if (lhs == nullptr) {
            return rhs;
        }

        if (rhs == nullptr) {
            return lhs;
        }

        if (lhs->data <= rhs->data) {
            lhs->right = merge(lhs->right, rhs);
            if (calc_npl(lhs->left) < calc_npl(lhs->right)) {
                std::swap(lhs->left, lhs->right);
            }

            return lhs;
        } else {
            rhs->right = merge(rhs->right, lhs);
            if (calc_npl(rhs->left) < calc_npl(rhs->right)) {
                std::swap(rhs->left, rhs->right);
            }

            return rhs;
        }
    }

    LeftistNode* clone(LeftistNode* node) {
        if (node == nullptr) {
            return nullptr;
        }

        auto left = clone(node->left);
        auto right = clone(node->right);
        auto ret = new LeftistNode{node->data, left, right, 0};
        ret->npl = calc_npl(ret);
        return ret;
    }

private:

    LeftistNode* root_;
};

#endif
