// Binary Search Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <chrono>

// Define the TreeNode structure for each node in the Binary Search Tree
template <typename T>
struct TreeNode {
    T data;               // Data stored in the node
    TreeNode* left;       // Pointer to the left child node
    TreeNode* right;      // Pointer to the right child node
    TreeNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

// Define the BinarySearchTree class
template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;    // Pointer to the root node of the tree

    // Private helper methods for insertion, removal, and traversal
    TreeNode<T>* insert(TreeNode<T>* node, const T& val);     // Helper for inserting a value
    TreeNode<T>* remove(TreeNode<T>* node, const T& val);     // Helper for removing a value
    TreeNode<T>* findMax(TreeNode<T>* node);                  // Helper to find maximum node
    void inorderTraversal(TreeNode<T>* node, std::vector<T>& result); // Helper for inorder traversal

public:
    BinarySearchTree() : root(nullptr) {}

    // Public methods for insertion, removal, finding maximum, and traversal
    void insert(const T& val);              // Insert a value
    void remove(const T& val);              // Remove a value
    T maximum();                            // Find the maximum value
    std::vector<T> inorderTraversal();      // Perform inorder traversal

    // Performance analysis methods for insertion and removal
    void performanceAnalysisInsert(int numNodes); // Analyze insertion performance
    void performanceAnalysisRemove(int numNodes); // Analyze removal performance
};

// Private helper method for inserting a value iteratively
template <typename T>
TreeNode<T>* BinarySearchTree<T>::insert(TreeNode<T>* node, const T& val) {
    TreeNode<T>* newNode = new TreeNode<T>(val);
    if (!node) {
        return newNode;
    }

    TreeNode<T>* current = node;
    TreeNode<T>* parent = nullptr;
    while (current) {
        parent = current;
        if (val < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (val < parent->data) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    return node;
}

// Private helper method for removing a value iteratively
template <typename T>
TreeNode<T>* BinarySearchTree<T>::remove(TreeNode<T>* node, const T& val) {
    if (!node) {
        return nullptr;
    }

    TreeNode<T>* current = node;
    TreeNode<T>* parent = nullptr;

    // Find the node to be removed
    while (current && current->data != val) {
        parent = current;
        if (val < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    if (!current) {
        return node; // Node not found, return original tree
    }

    if (!current->left) {
        TreeNode<T>* temp = current->right;
        delete current;
        if (!parent) {
            return temp; // Node was root
        }
        if (parent->left == current) {
            parent->left = temp;
        }
        else {
            parent->right = temp;
        }
        return temp; // Return the new root of the modified tree
    }
    else if (!current->right) {
        TreeNode<T>* temp = current->left;
        delete current;
        if (!parent) {
            return temp; // Node was root
        }
        if (parent->left == current) {
            parent->left = temp;
        }
        else {
            parent->right = temp;
        }
        return temp; // Return the new root of the modified tree
    }

    TreeNode<T>* minRight = findMax(current->left);
    current->data = minRight->data;
    current->left = remove(current->left, minRight->data);
    return node; // Return the root of the modified tree
}

// Private helper method to find the maximum node in the tree
template <typename T>
TreeNode<T>* BinarySearchTree<T>::findMax(TreeNode<T>* node) {
    while (node->right) {
        node = node->right; // Traverse right until no more right children
    }
    return node;
}

// Private helper method for inorder traversal
template <typename T>
void BinarySearchTree<T>::inorderTraversal(TreeNode<T>* node, std::vector<T>& result) {
    if (!node) {
        return; // Base case: empty node, return
    }
    inorderTraversal(node->left, result);   // Traverse left subtree
    result.push_back(node->data);           // Push current node's data to result vector
    inorderTraversal(node->right, result);  // Traverse right subtree
}

// Public method to insert a value into the BST
template <typename T>
void BinarySearchTree<T>::insert(const T& val) {
    root = insert(root, val); // Call private insert method with root node
}

// Public method to remove a value from the BST
template <typename T>
void BinarySearchTree<T>::remove(const T& val) {
    root = remove(root, val); // Call private remove method with root node
}

// Public method to find the maximum value in the BST
template <typename T>
T BinarySearchTree<T>::maximum() {
    TreeNode<T>* maxNode = findMax(root); // Find maximum node
    return maxNode->data;                // Return maximum node's data
}

// Public method to perform an inorder traversal of the BST
template <typename T>
std::vector<T> BinarySearchTree<T>::inorderTraversal() {
    std::vector<T> result;                 // Vector to store traversal result
    inorderTraversal(root, result);        // Call private inorderTraversal method
    return result;                         // Return the traversal result
}

// Performance analysis method for inserting nodes
template <typename T>
void BinarySearchTree<T>::performanceAnalysisInsert(int numNodes) {
    auto start = std::chrono::high_resolution_clock::now(); // Record start time

    for (int i = 0; i < numNodes; ++i) {
        insert(i); // Insert values from 0 to numNodes - 1
    }

    auto end = std::chrono::high_resolution_clock::now();   // Record end time
    std::chrono::duration<double> duration = end - start;   // Calculate duration

    // Display time in milliseconds
    std::cout << "Insertion time for " << numNodes << " nodes: " << duration.count() * 1000 << " milliseconds\n";
}

// Performance analysis method for removing nodes
template <typename T>
void BinarySearchTree<T>::performanceAnalysisRemove(int numNodes) {
    auto start = std::chrono::high_resolution_clock::now(); // Record start time

    for (int i = 0; i < numNodes; ++i) {
        remove(i); // Remove values from 0 to numNodes - 1
    }

    auto end = std::chrono::high_resolution_clock::now();   // Record end time
    std::chrono::duration<double> duration = end - start;   // Calculate duration

    // Display time in milliseconds
    std::cout << "Removal time for " << numNodes << " nodes: " << duration.count() * 1000 << " milliseconds\n";
}

// Main function
int main() {
    BinarySearchTree<int> bst;

    int values[] = { 5, 3, 8, 2, 4, 7, 9 };
    for (int val : values) {
        bst.insert(val);
    }

    bst.remove(3);

    int maxVal = bst.maximum();
    std::cout << "Maximum value: " << maxVal << std::endl;

    std::vector<int> traversal = bst.inorderTraversal();
    std::cout << "Inorder traversal: ";
    for (int val : traversal) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    int numNodes[] = { 100, 1000, 10000, 100000 };

    // Perform insertion performance analysis
    for (int num : numNodes) {
        bst.performanceAnalysisInsert(num);
    }

    // Perform removal performance analysis
    for (int num : numNodes) {
        bst.performanceAnalysisRemove(num);
    }

    return 0;
}
