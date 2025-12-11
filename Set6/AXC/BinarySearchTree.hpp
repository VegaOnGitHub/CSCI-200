// Daniel Vega
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <queue>
#include <stack>
#include <vector>

template<typename T>
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree& other);
    ~BinarySearchTree();

    BinarySearchTree& operator=(const BinarySearchTree& other);

    void insert(const T val);
    int size() const;

    void printInOrder() const;
    void printPreOrder() const;
    void printPostOrder() const;
    void printBreadthOrder() const;
    void printDepthOrder() const;
    void printByLevels() const;
    int height() const;

private:
    struct TreeNode {
        T value;
        TreeNode* pLeft;
        TreeNode* pRight;
    };

    TreeNode* _pRoot;
    int _size;

    static TreeNode* clone(const TreeNode* pNode);
    static void destroy(TreeNode* pNode);
    static void insertNode(TreeNode*& pNode, const T val);

    static void printInOrder(const TreeNode* pNode);
    static void printPreOrder(const TreeNode* pNode);
    static void printPostOrder(const TreeNode* pNode);
    static int height(const TreeNode* pNode);
};

//---------------------------------------------------------

template<typename T>
BinarySearchTree<T>::BinarySearchTree() : _pRoot(nullptr), _size(0) {}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other)
    : _pRoot(clone(other._pRoot)), _size(other._size) {}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    destroy(_pRoot);
    _pRoot = nullptr;
    _size = 0;
}

template<typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree& other) {
    if (this != &other) {
        destroy(_pRoot);
        _pRoot = clone(other._pRoot);
        _size = other._size;
    }
    return *this;
}

template<typename T>
void BinarySearchTree<T>::insert(const T val) {
    insertNode(_pRoot, val);
    ++_size;
}

template<typename T>
int BinarySearchTree<T>::size() const {
    return _size;
}

template<typename T>
void BinarySearchTree<T>::printInOrder() const {
    printInOrder(_pRoot);
    std::cout << std::endl;
}

template<typename T>
void BinarySearchTree<T>::printPreOrder() const {
    printPreOrder(_pRoot);
    std::cout << std::endl;
}

template<typename T>
void BinarySearchTree<T>::printPostOrder() const {
    printPostOrder(_pRoot);
    std::cout << std::endl;
}

template<typename T>
void BinarySearchTree<T>::printBreadthOrder() const {
    if (_pRoot == nullptr) {
        std::cout << std::endl;
        return;
    }
    std::queue<TreeNode*> q;
    q.push(_pRoot);
    while (!q.empty()) {
        TreeNode* pCur = q.front();
        q.pop();
        std::cout << pCur->value << " ";
        if (pCur->pLeft != nullptr) {
            q.push(pCur->pLeft);
        }
        if (pCur->pRight != nullptr) {
            q.push(pCur->pRight);
        }
    }
    std::cout << std::endl;
}

template<typename T>
void BinarySearchTree<T>::printDepthOrder() const {
    if (_pRoot == nullptr) {
        std::cout << std::endl;
        return;
    }
    std::stack<TreeNode*> st;
    st.push(_pRoot);
    while (!st.empty()) {
        TreeNode* pCur = st.top();
        st.pop();
        std::cout << pCur->value << " ";
        if (pCur->pRight != nullptr) {
            st.push(pCur->pRight);
        }
        if (pCur->pLeft != nullptr) {
            st.push(pCur->pLeft);
        }
    }
    std::cout << std::endl;
}

template<typename T>
void BinarySearchTree<T>::printByLevels() const {
    if (_pRoot == nullptr) {
        return;
    }
    std::queue<TreeNode*> q;
    q.push(_pRoot);
    int level = 1;
    while (!q.empty()) {
        std::size_t levelCount = q.size();
        std::cout << "Level " << level << ": ";
        for (std::size_t i = 0; i < levelCount; ++i) {
            TreeNode* pCur = q.front();
            q.pop();
            std::cout << pCur->value;
            if (i + 1 < levelCount) {
                std::cout << " ";
            }
            if (pCur->pLeft != nullptr) {
                q.push(pCur->pLeft);
            }
            if (pCur->pRight != nullptr) {
                q.push(pCur->pRight);
            }
        }
        std::cout << std::endl;
        ++level;
    }
}

template<typename T>
int BinarySearchTree<T>::height() const {
    return height(_pRoot);
}

//---------------------------------------------------------

template<typename T>
typename BinarySearchTree<T>::TreeNode* BinarySearchTree<T>::clone(const TreeNode* pNode) {
    if (pNode == nullptr) {
        return nullptr;
    }
    TreeNode* pNew = new TreeNode{pNode->value, nullptr, nullptr};
    pNew->pLeft = clone(pNode->pLeft);
    pNew->pRight = clone(pNode->pRight);
    return pNew;
}

template<typename T>
void BinarySearchTree<T>::destroy(TreeNode* pNode) {
    if (pNode == nullptr) {
        return;
    }
    destroy(pNode->pLeft);
    destroy(pNode->pRight);
    delete pNode;
}

template<typename T>
void BinarySearchTree<T>::insertNode(TreeNode*& pNode, const T val) {
    if (pNode == nullptr) {
        pNode = new TreeNode{val, nullptr, nullptr};
        return;
    }
    if (val < pNode->value) {
        insertNode(pNode->pLeft, val);
    } else {
        insertNode(pNode->pRight, val);
    }
}

template<typename T>
void BinarySearchTree<T>::printInOrder(const TreeNode* pNode) {
    if (pNode == nullptr) {
        return;
    }
    printInOrder(pNode->pLeft);
    std::cout << pNode->value << " ";
    printInOrder(pNode->pRight);
}

template<typename T>
void BinarySearchTree<T>::printPreOrder(const TreeNode* pNode) {
    if (pNode == nullptr) {
        return;
    }
    std::cout << pNode->value << " ";
    printPreOrder(pNode->pLeft);
    printPreOrder(pNode->pRight);
}

template<typename T>
void BinarySearchTree<T>::printPostOrder(const TreeNode* pNode) {
    if (pNode == nullptr) {
        return;
    }
    printPostOrder(pNode->pLeft);
    printPostOrder(pNode->pRight);
    std::cout << pNode->value << " ";
}

template<typename T>
int BinarySearchTree<T>::height(const TreeNode* pNode) {
    if (pNode == nullptr) {
        return 0;
    }
    const int leftHeight = height(pNode->pLeft);
    const int rightHeight = height(pNode->pRight);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

#endif // BINARY_SEARCH_TREE_HPP
