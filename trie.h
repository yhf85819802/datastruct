#ifndef TRIE_H
#define TRIE_H

#include <functional>
#include <vector>
#include <utility>
#include <algorithm>
#include <stack>

template <typename T>
using HashFunc = std::function<size_t(T)>;


template <typename T>
class Trie {

public:
    Trie(const HashFunc<T>& hash_func, size_t length) 
        : root_{new TrieNode}, hash_func_{hash_func} {
        root_->childs.resize(length, nullptr);
    }

    Trie(const Trie& rhs)
        : root_{new TrieNode{*rhs.root_}}, hash_func_{rhs.hash_func_} {}

    Trie& operator=(const Trie& rhs) {
        if (this != &rhs) {
            Trie temp{rhs};
            std::swap(root_, temp.root_);
            std::swap(hash_func_, temp.hash_func_);
        }

        return *this;
    }

    ~Trie() {
        delete root_;
    }

    template <typename Word>
    void insert(const Word& x) {
        TrieNode* last = nullptr;
        auto size = x.size();
        auto index = find(x, last);

        if (index == size) { // all matched
            if (last->is_final) { // and x is a legal word
                return;
            } else {
                last->is_final = true;
            }
        } else {
            for (int i = index; i != size; ++i) {
                auto new_node = last->childs[hash_func_(x[i])] = new TrieNode();
                new_node->childs.resize(root_->childs.size());
                new_node->data = x[i];
                new_node->is_final = (i == size - 1);
                last = new_node;
            }
        }    
    }

    template <typename Word>
    void erase(const Word& x) {
        TrieNode* last = nullptr;
        auto size = x.size();
        std::stack<TrieNode*> parents;
        auto index = find(x, last, parents);
        if (index != size) {
            return;
        }

        if (last->is_final) {
            if (std::any_of(last->childs.begin(), last->childs.end(),
                [](TrieNode* i) {return i != nullptr;})) {
                last->is_final = false;
            } else {
                TrieNode* parent = parents.top();
                parents.pop();
                parent->childs[hash_func_(last->data)] = nullptr;
                delete last;
                last = parent;

                while (!last->is_final && !parents.empty()) {
                    TrieNode* parent = parents.top();
                    parents.pop();

                    if (std::any_of(last->childs.begin(), last->childs.end(),
                        [](TrieNode* i) {return i != nullptr;})) {
                        break;
                    }
                    parent->childs[hash_func_(last->data)] = nullptr;
                    delete last;
                    last = parent;
                }
            }
        }
    }

    template <typename Word>
    bool has(const Word& x) {
        TrieNode* last = nullptr;
        return find(x, last) == x.size() && last->is_final;
    }

private:
    struct TrieNode {
        TrieNode() = default;

        TrieNode(const TrieNode& rhs) : data{rhs.data}, is_final{rhs.is_final} {
            childs.resize(rhs.childs.size(), nullptr);
            for (size_t i = 0; i < childs.size(); ++i) {
                auto rhs_child = rhs.childs[i];
                if (rhs_child) {
                    childs[i] = new TrieNode{*rhs_child};
                }
            }
        }

        ~TrieNode() {
            for (auto& tree_node : childs) {
                delete tree_node;
                tree_node = nullptr;
            }
        }

        std::vector<TrieNode*> childs;
        T data;
        bool is_final;
    };

private:
    TrieNode* root_;
    HashFunc<T> hash_func_;

private:
    template <typename Word>
    size_t find(const Word& x, TrieNode*& last) {
        auto p = root_;
        size_t size = x.size();
        int i = 0;

        for (; i != size; ++i) {
            auto next = p->childs[hash_func_(x[i])];

            if (next == nullptr) {
                break;
            } else {
                p = next;
            }
        }

        last = p;

        return i;
    }

    template <typename Word>
    size_t find(const Word& x, TrieNode*& last, std::stack<TrieNode*>& parents) {
        auto p = root_;
        size_t size = x.size();
        int i = 0;

        for (; i != size; ++i) {
            auto next = p->childs[hash_func_(x[i])];

            if (next == nullptr) {
                break;
            } else {
                parents.push(p);
                p = next;
            }
        }

        last = p;
        return i;
    }
};

#endif
