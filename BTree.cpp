#include "BTree.h"
#include <iostream>

template <typename T>
BTree<T>::BTree(int degree) : deg(degree), depth(1) {
    root = new Node<T>();
    root->type = NodeType::NODE_LEAF;
}

template <typename T>
BTree<T>::~BTree() {
    clear();
}

template <typename T>
Node<T>* BTree<T>::findLeaf(int key) {
    Node<T>* curr = root;

    while (curr->type != NodeType::NODE_LEAF) {
        int index = curr->keyInsertIndex(key);
        curr = curr->children[index];
    }

    return curr;
}

template <typename T>
void BTree<T>::set(int key, const T& val) {
    Node<T>* curr = findLeaf(key);
    int index = curr->findKey(key);

    curr->set(key, val);

    if (index != -1) {
        return;
    }

    while (curr && curr->size >= deg) {
        Node<T>* newRootNode = curr->splitNode();

        if (newRootNode) {
            depth++;
            root = newRootNode;
        }

        curr = curr->parent;
    }
}

template <typename T>
void BTree<T>::remove(int key) {
    Node<T>* curr = findLeaf(key);
    int index = curr->findKey(key);

    if (index != -1) {
        remove(key, curr);
    }
}

template <typename T>
void BTree<T>::remove(int key, Node<T>* curr) {
    int minCapacity = deg >> 1;

    if (curr->type == NodeType::NODE_LEAF) {
        curr->removeFromLeaf(key);
    } else {
        curr->removeFromInternal(key);
    }

    if (curr->size < minCapacity) {
        if (curr->type == NodeType::NODE_ROOT) {
            if (!curr->size && !curr->children.empty()) {
                Node<T>* newRoot = curr->children[0];
                delete curr;

                newRoot->parent = nullptr;
                root = newRoot;
                depth--;

                if (depth > 1) {
                    newRoot->type = NodeType::NODE_ROOT;
                } else {
                    newRoot->type = NodeType::NODE_LEAF;
                }
            }
        } else if (curr->type == NodeType::NODE_INTERNAL) {
            Node<T>* parent = curr->parent;
            int currChildIndex = parent->indexOfChild(curr);

            Node<T>* next = nullptr;
            Node<T>* prev = nullptr;

            if (parent->children.size() > static_cast<size_t>(currChildIndex + 1)) {
                next = parent->children[currChildIndex + 1];
            }

            if (currChildIndex > 0) {
                prev = parent->children[currChildIndex - 1];
            }

            if (next && next->parent == parent && next->size > minCapacity) {
                curr->borrowFromRightInternal(next);
            } else if (prev && prev->parent == parent && prev->size > minCapacity) {
                curr->borrowFromLeftInternal(prev);
            } else if (next && next->parent == parent && next->size <= minCapacity) {
                curr->mergeWithRightInternal(next);
            } else if (prev && prev->parent == parent && prev->size <= minCapacity) {
                curr->mergeWithLeftInternal(prev);
                curr = prev;
            }
        } else {
            Node<T>* parent = curr->parent;
            Node<T>* next = curr->next;
            Node<T>* prev = curr->prev;

            if (next && next->parent == parent && next->size > minCapacity) {
                curr->borrowFromRightLeaf();
            } else if (prev && prev->parent == parent && prev->size > minCapacity) {
                curr->borrowFromLeftLeaf();
            } else if (next && next->parent == parent && next->size <= minCapacity) {
                curr->mergeWithRightLeaf();
            } else if (prev && prev->parent == parent && prev->size <= minCapacity) {
                curr->mergeWithLeftLeaf();
                curr = prev;
            }
        }
    }

    if (curr && curr->parent) {
        remove(key, curr->parent);
    }
}

template <typename T>
T* BTree<T>::find(int key) {
    Node<T>* curr = findLeaf(key);
    int index = curr->findKey(key);

    if (index != -1) {
        return &curr->vals[index];
    }

    return nullptr;
}

template <typename T>
void BTree<T>::printTree() {
    if (root) {
        printTree(root, "", true);
    }
}

template <typename T>
void BTree<T>::printTree(Node<T>* node, const std::string& prefix, bool last) {
    std::cout << prefix << "├ [";

    for (size_t i = 0; i < node->keys.size(); i++) {
        std::cout << node->keys[i];
        if (i != node->keys.size() - 1) {
            std::cout << ", ";
        }
    }

    std::cout << "]" << std::endl;

    std::string newPrefix = prefix + (last ? "   " : "╎  ");

    if (node->type != NodeType::NODE_LEAF) {
        for (size_t i = 0; i < node->children.size(); i++) {
            bool isLast = (i == node->children.size() - 1);
            printTree(node->children[i], newPrefix, isLast);
        }
    }
}

template <typename T>
bool BTree<T>::empty() const {
    return root->size == 0;
}

template <typename T>
int BTree<T>::size() const {
    // This would require a traversal to count all keys
    // For now, return -1 to indicate not implemented
    return -1;
}

template <typename T>
void BTree<T>::clear() {
    if (root) {
        // Recursive deletion would be implemented here
        // For now, just delete root
        delete root;
        root = nullptr;
        depth = 0;
    }
}

// Explicit template instantiation for common types
template class BTree<std::string>;
template class BTree<int>;
template class BTree<double>;
