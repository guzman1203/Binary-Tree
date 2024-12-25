#include <iostream>
#include <queue>
#include <stack>

using namespace std;

// Define the TreeNode class
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    // Constructor
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Define the Tree class
class Tree {
private:
    TreeNode* root;

    void dfsHelper(TreeNode* node) const;
    int countLeafNodesHelper(TreeNode* node) const;
    void deleteTree(TreeNode* node); // Helper function to delete the tree
    TreeNode* removeGreaterThanHelper(TreeNode* node, int x); // Recursive helper for removeGreaterThan

public:
    Tree();
    void setRoot(int value);
    TreeNode* getRoot() const;

    void addLeftChild(TreeNode* parent, int value);
    void addRightChild(TreeNode* parent, int value);

    void preOrderTraversalHelper(TreeNode* node) const;
    void preOrderTraversal() const;

    void postOrderTraversalHelper(TreeNode* node) const;
    void postOrderTraversal() const;

    void inOrderTraversalHelper(TreeNode* node) const;
    void inOrderTraversal() const;

    void bfs() const; // Level-order traversal
    int countLeafNodes() const;

    void removeGreaterThan(int x); // Public interface for removeGreaterThan

    ~Tree();
};

// Constructor
Tree::Tree() : root(nullptr) {}

// Set the root of the tree
void Tree::setRoot(int value) {
    root = new TreeNode(value);
}

// Get the root of the tree
TreeNode* Tree::getRoot() const {
    return root;
}

// Add a left child to a parent node
void Tree::addLeftChild(TreeNode* parent, int value) {
    if (parent->left) {
        cout << "Left child already exists\n"; // invalid, child already exist
        return;
    }
    if (parent) {
        parent->left = new TreeNode(value);
    }
}

// Add a right child to a parent node
void Tree::addRightChild(TreeNode* parent, int value) {
    if (parent->right) {
        cout << "Right child already exists\n";
        return;
    }
    if (parent) {
        parent->right = new TreeNode(value);
    }
}

// Preorder traversal helper
void Tree::preOrderTraversalHelper(TreeNode* node) const {
    if (node == nullptr) {
        return;
    }
    cout << node->data << " ";
    preOrderTraversalHelper(node->left);
    preOrderTraversalHelper(node->right);
}

// Preorder traversal
void Tree::preOrderTraversal() const {
    cout << "Preorder traversal: ";
    preOrderTraversalHelper(root);
    cout << endl;
}

// Postorder traversal helper
void Tree::postOrderTraversalHelper(TreeNode* node) const {
    if (node == nullptr) {
        return;
    }
    postOrderTraversalHelper(node->left);
    postOrderTraversalHelper(node->right);
    cout << node->data << " ";
}

// Postorder traversal
void Tree::postOrderTraversal() const {
    cout << "Postorder traversal: ";
    postOrderTraversalHelper(root);
    cout << endl;
}

// Inorder traversal helper
void Tree::inOrderTraversalHelper(TreeNode* node) const {
    if (node == nullptr) {
        return;
    }
    inOrderTraversalHelper(node->left);
    cout << node->data << " ";
    inOrderTraversalHelper(node->right);
}

// Inorder traversal
void Tree::inOrderTraversal() const {
    cout << "Inorder traversal: ";
    inOrderTraversalHelper(root);
    cout << endl;
}

// Level-order traversal (BFS)
void Tree::bfs() const {
    if (root == nullptr) {
        return;
    }
    queue<TreeNode*> q;
    q.push(root);
    cout << "BFS traversal: ";

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        cout << current->data << " ";
        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }
    cout << endl;
}

// Count leaf nodes helper
int Tree::countLeafNodesHelper(TreeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    if (node->left == nullptr && node->right == nullptr) {
        return 1;
    }
    return countLeafNodesHelper(node->left) + countLeafNodesHelper(node->right);
}

// Count leaf nodes
int Tree::countLeafNodes() const {
    return countLeafNodesHelper(root);
}

// Helper function to delete the tree
void Tree::deleteTree(TreeNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

// Remove nodes greater than x
TreeNode* Tree::removeGreaterThanHelper(TreeNode* node, int x) {
    if (node == nullptr) {
        return nullptr;
    }

    // Process the right subtree
    node->right = removeGreaterThanHelper(node->right, x);

    // If the current node's value is greater than x
    if (node->data > x) {
        TreeNode* leftSubtree = node->left;
        delete node; // Delete the current node
        return removeGreaterThanHelper(leftSubtree, x); // Continue with the left subtree
    }

    // Process the left subtree
    node->left = removeGreaterThanHelper(node->left, x);

    return node;
}

// Public interface to remove nodes greater than x
void Tree::removeGreaterThan(int x) {
    root = removeGreaterThanHelper(root, x);
}

// Destructor
Tree::~Tree() {
    deleteTree(root);
}

// Main function
int main() {
    Tree tree;
    tree.setRoot(20);

    TreeNode* root = tree.getRoot();
    tree.addLeftChild(root, 10);
    tree.addRightChild(root, 30);

    tree.addLeftChild(root->left, 5);
    tree.addRightChild(root->left, 15);

    tree.addLeftChild(root->right, 25);
    tree.addRightChild(root->right, 35);

    cout << "Original tree (in-order): ";
    tree.inOrderTraversal();

    // Test removeGreaterThan
    int x = 25;
    cout << "\nRemoving nodes greater than " << x << "...\n";
    tree.removeGreaterThan(x);

    // Display the modified tree
    cout << "Modified tree (in-order): ";
    tree.inOrderTraversal();

    return 0;
}
