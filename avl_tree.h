#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <stack>
#include <queue>
#include <algorithm>

template <typename T>
class AvlTree {
    struct AvlNode {
        AvlNode(const T& ele, AvlNode* lt, AvlNode* rt)
            : element{ele}, left{lt}, right{rt} {}

        T element;
        AvlNode* left;
        AvlNode* right;
    };

public:
    AvlTree() : root_{nullptr}{

    }

    AvlTree(const AvlTree& rhs) {
        root_ = clone(rhs.root_);
    }

    AvlTree& operator=(const AvlTree& rhs) {
        if (this != &rhs) {
            clear();
            root_ = clone(rhs.root_);
        }
        return *this;
    }

    ~AvlTree() {
        clear();
    }

    void clear() {
        clear(root_);
        root_ = nullptr;
    }

    bool empty() const {
        return root_ == nullptr;
    }

    bool contain(const T& x) const {
        return find(x);
    }

    void insert(const T& x) {
        if (root_ == nullptr) {
            root_ = new AvlNode{x, nullptr, nullptr};
            return;
        }

        std::stack<AvlNode*> parents;
        auto pos = find(x, parents);
        
        // find x,need not insert
        if (pos) {
            return;
        }

        auto parent = parents.top();
        if (x < parent->element) {
            parent->left = new AvlNode{x, nullptr, nullptr};
        } else {
            parent->right = new AvlNode{x, nullptr, nullptr};
        }

        if (!inserted_balance(parent)) {
            parents.pop();
            rebalance(parent, parents);
        }
    }

    void erase(const T& x) {
        std::stack<AvlNode*> parents;
        auto pos = find(x, parents);
        
        // not found
        if (!pos) {
            return;
        }

        if (pos->left == nullptr) {
            if (pos->right == nullptr) {
                // root node
                if (parents.empty()) {
                    delete pos;
                    root_ = nullptr;
                } else {
                    auto& parent = parents.top();
                    if (x < parent->element) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }

                    if (!erased_balance(parent)) {
                        parents.pop();
                        rebalance(parent, parents);
                    }
                }
            } else {
                // root node
                if (parents.empty()) {
                    root_ = pos->right;
                    delete pos;
                } else {
                    auto& parent = parents.top();
                    if (x < parent->element) {
                        parent->left = pos->right;
                        delete pos;
                    } else {
                        parent->right = pos->right;
                    }

                    if (!erased_balance(parent)) {
                        parents.pop();
                        rebalance(parent, parents);
                    }
                }
            }
        } else {
            if (pos->right == nullptr) {
                // root node
                if (parents.empty()) {
                    root_ = pos->left;
                    delete pos;
                } else {
                    auto& parent = parents.top();
                    if (x < parent->element) {
                        parent->left = pos->left;
                    } else {
                        parent->right = pos->left;
                    }

                    if (!erased_balance(parent)) {
                        parents.pop();
                        rebalance(parent, parents);
                    }
                }
            } else {
                std::stack<AvlNode*> min_parents;
                auto right_min = find_min(pos->right, min_parents);
                std::swap(pos->element, right_min->element);
                auto parent = min_parents.empty() ? pos : min_parents.top();
                if (parent == pos) {
                    parent->right = nullptr;   
                } else {
                    parent->left = nullptr;
                }
                if (!erased_balance(parent)) {
                    parents.pop();
                    rebalance(parent, parents);
                }
            }
        }
    }

    // middle traverse
    template <typename InsertIter>
    void traverse(InsertIter insert_iter) {
        traverse(root_, insert_iter);
    }

    // level traverse
    template <typename InsertIter>
    void traverse_by_level(InsertIter insert_iter) {
        if (root_ == nullptr) {
            return;
        }
        std::queue<AvlNode*> _queue;
        _queue.push(root_);

        while (!_queue.empty()) {
            auto top = _queue.front();
            *insert_iter++ = top->element;
            _queue.pop();
            if (top->left) {
                _queue.push(top->left);
            }
            if (top->right) {
                _queue.push(top->right);
            }
        }
    }


private:
    AvlNode* clone(AvlNode* node) {
        if (node == nullptr) {
            return nullptr;
        }
        auto left = clone(node->left);
        auto right = clone(node->right);
        return new AvlNode(node->element, left, right);
    }

    void clear(AvlNode* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

    AvlNode* find(const T& x) const {
        auto p = root_;
        while (p && p->element != x) {
            if (x < p->element) {
                p = p->left;
            } else {
                p = p->right;
            }
        }

        return p;
    }

    AvlNode* find(const T& x, std::stack<AvlNode*>& parents) const {
        auto p = root_;
        while (p && p->element != x) {
            parents.push(p);
            if (x < p->element) {
                p = p->left;
            } else {
                p = p->right;
            }
        }

        return p;
    }

    AvlNode* find_min(AvlNode* node, std::stack<AvlNode*>& parents) const {
        if (node == nullptr) {
            return nullptr;
        }
        
        auto p = node;
        while (p->left) {
            parents.push(p);
            p = p->left;
        }

        return p;
    }
    
    template <typename InsertIter>
    void traverse(AvlNode* node, InsertIter insert_iter) const {
        if (node == nullptr) {
            return;
        }

        traverse(node->left, insert_iter);
        *insert_iter++ = node->element;
        traverse(node->right, insert_iter);
    }

    int height(AvlNode* node) const {
        if (node == nullptr) {
            return 0;
        }

        /*int left_height = node->left ? node->left->height : 0;
        int right_height = node->right ? node->right->height : 0;
        return std::max(left_height, right_height) + 1;*/
        return std::max(height(node->left), height(node->right)) + 1;
    }

    int balance_factor(AvlNode* node) const {
        if (node == nullptr) {
            return 0;
        }

        return height(node->right) - height(node->left);
    }

    // if balance factor equal zero
    // it means the parent has one child before insert,need not rebalance
    bool inserted_balance(AvlNode* node) const {
        return !balance_factor(node);
    }

    // if 1 or -1,it means before erase,parent has two child,need not rebalance
    bool erased_balance(AvlNode* node) const {
        int _balance_factor = balance_factor(node);
        return _balance_factor == 1 || _balance_factor == -1;
    }

    void rebalance(AvlNode* node, std::stack<AvlNode*>& parents) {
        AvlNode* p = nullptr;
        int _balance_factor = balance_factor(node);
        if (_balance_factor != 2 && _balance_factor != -2) {
            while (!parents.empty()) {
                auto temp = parents.top();
                parents.pop();
                int temp_balance_factor = balance_factor(temp);
                if (temp_balance_factor == 2 || temp_balance_factor == -2) {
                    p = temp;
                    break;
                }
            }
        } else {
            p = node;
        }

        // p is the node that need balance
        if (p) {
            AvlNode* mid = nullptr;
            
            int p_balance_factor = balance_factor(p);
            if (p_balance_factor == 2) {
                int p_right_balance_factor = balance_factor(p->right);
                if (p_right_balance_factor == -1) { // RL
                    mid = right_left_rotate(p);
                } else { // RR
                    mid = left_rotate(p);
                }
            } else {
                int p_left_balance_factor = balance_factor(p->left);
                if (p_left_balance_factor == 1) { // LR
                    mid = left_right_rotate(p);
                } else { // LL
                    mid = right_rotate(p);
                }
            }
            
            if (parents.empty()) {
                root_ = mid;
            } else {
                auto parent = parents.top();
                if (mid->element < parent->element) {
                    parent->left = mid;
                } else {
                    parent->right = mid;
                }
            }
        }
    }

    AvlNode* left_rotate(AvlNode* node) {
        auto right = node->right;
        node->right = right->left;
        right->left = node;
        return right;
    }

    AvlNode* right_rotate(AvlNode* node) {
        auto left = node->left;
        node->left = left->right;
        left->right = node;
        return left;
    }

    AvlNode* left_right_rotate(AvlNode* node) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    AvlNode* right_left_rotate(AvlNode* node) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }
private:
    AvlNode* root_;
};

#endif
