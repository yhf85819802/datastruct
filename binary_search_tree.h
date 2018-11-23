#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

#include <iostream>

template <typename Comparable>
class BinarySearchTree {
 public:
    BinarySearchTree() : root{nullptr} {

    }

    BinarySearchTree(const BinarySearchTree& rhs) {
        root = clone(rhs.root);
    }
    
    BinarySearchTree& operator=(const BinarySearchTree& rhs) {
        if (this != &rhs) {
            makeEmpty();
            root = clone(rhs.root);
        }
        return *this;
    }
    
    ~BinarySearchTree() {
        makeEmpty();
    }

    const Comparable& findMin() const {
        auto trailer = root;
        auto p = root;
        while (p) {
            trailer = p;
            p = p->left;
        }

        return trailer->element;
    }

    const Comparable& findMax() const {
        auto trailer = root;
        auto p = root;
        while (p) {
            trailer = p;
            p = p->right;
        }

        return trailer->element;
    }

    bool contains(const Comparable& x) const {
        BinaryNode* p = root;
        while (p && p->element != x) {
            if (p->element < x) {
                p = p->right;
            } else {
                p = p->left;
            }
        }

        return p;
    }
    
    bool isEmpty() const {
        return root == nullptr;
    }

    void printTree() const {
        printTree(root);
    }

    void makeEmpty() {
        makeEmpty(root);
    }

    void insert(const Comparable& x) {
        if (root == nullptr) {
            root = new BinaryNode{x, nullptr, nullptr};
            return;
        }
        
        auto p = root;
        while (p && p->element != x) {
            if (x < p->element) {
                if (p->left == nullptr) {
                    p->left = new BinaryNode{x, nullptr, nullptr};
                    break;
                } else {
                    p = p->left;
                }
            } else if (p->element < x) {
                if (p->right == nullptr) {
                    p->right = new BinaryNode{x, nullptr, nullptr};
                    break;
                } else {
                    p = p->right;
                }
            }
        }
    }

    void remove(const Comparable& x) {
        auto p = root;
        auto trailer = root;

        while (p && p->element != x) {
            trailer = p;
            if (p->element < x) {
                p = p->right;
            } else {
                p = p->left;
            }
        }

        if (!p) {
            return;
        }

        // p is the node to be removed
        remove(trailer, p);
    }

 private:
    struct BinaryNode {
        Comparable element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const Comparable& theElement, BinaryNode* lt, BinaryNode* rt)
            : element{theElement}, left{lt}, right{rt} {}
    };

    void remove(BinaryNode* pre, BinaryNode* cur) {
        bool is_left_child = pre->element > cur->element;
        if (cur->left == nullptr) {
            if (cur->right == nullptr) {
                if (cur == root) {
                    root = nullptr;
                } else if (is_left_child) {
                    pre->left = nullptr;
                } else {
                    pre->right = nullptr;
                }
            } else {
                if (cur == root) {
                    root = cur->right;
                } else if (is_left_child) {
                    pre->left = cur->right;
                } else {
                    pre->right = cur->right;
                }
            }
            delete cur;
        } else {
            if (cur->right == nullptr) {
                if (cur == root) {
                    root = cur->left;
                } else if (is_left_child) {
                    pre->left = cur->left;
                } else {
                    pre->right = cur->left;
                }
                delete cur;
            } else {
                auto right_min_pre = cur;
                auto right_min = cur->right;
                while (right_min->left != nullptr) {
                    right_min_pre = right_min;
                    right_min = right_min->left;
                }
                std::swap(cur->element, right_min->element);
                remove(right_min_pre, right_min);
            }
        }
    
    }
    
    BinaryNode* findMin(BinaryNode* t) const {
        BinaryNode* trailer = t;
        BinaryNode* p = t;
        while (p) {
            trailer = p;
            p = p->left;
        }

        return trailer;
    }

    BinaryNode* findMax(BinaryNode* t) const {
        BinaryNode* trailer = t;
        BinaryNode* p = t;
        while (p) {
            trailer = p;
            p = p->right;
        }

        return trailer;
    }

    bool contains(const Comparable& x, BinaryNode* t) const {
        return true;
    }

    void makeEmpty(BinaryNode*& t) {
        if (t == nullptr) {
            return;
        }

        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    void printTree(BinaryNode* t) const {
        if (t == nullptr) {
            return;
        }

        printTree(t->left);
        std::cout << t->element << ' ';
        printTree(t->right);
    }

    BinaryNode* clone(BinaryNode* t) const {
        if (t == nullptr) {
            return nullptr;
        }

        BinaryNode* left = clone(t->left);
        BinaryNode* right = clone(t->right);
        return new BinaryNode{t->element, left, right};
    }
 private:
    BinaryNode* root;
};

#endif
