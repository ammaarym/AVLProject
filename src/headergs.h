#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int id;       // Node's identifier
    string name;  // Name associated with the node
    Node* left;   // Pointer to left child
    Node* right;  // Pointer to right child
    int height;   // Height of the node

    // Node constructor
    Node(int id, string name) : id(id), name(name), left(nullptr), right(nullptr), height(1) {}

    // Return the height of the node
    static int getHeight(Node* root) {
        if (!root) {
            return 0;
        }
        else {
            return root->height;
        }
    }

    // Update the height of the node
    static int updateHeight(Node* root) {
        if (!root){
            return 0;
        }
        return max(Node::getHeight(root->left), Node::getHeight(root->right)) + 1;
    }

    // Calculate the balance factor for AVL tree balancing
    static int getBalance(Node* node) {
        if (!node) {
            return 0;
        }
        int balance = Node::getHeight(node->left) - Node::getHeight(node->right);
        return balance;
    }
};

class AVLTree {
public:
    Node* root = nullptr;  // Root of the AVL Tree

    // Right Rotation (Used in balancing AVL Tree)
    Node* rotateR(Node* parent) {
        Node* child = parent->left;
        Node* gchild = child->right;

        // Perform the rotation
        child->right = parent;
        parent->left = gchild;

        // Update the heights
        parent->height = Node::updateHeight(parent);
        child->height = Node::updateHeight(child);

        return child;  // Return new root after rotation
    }

    // Left Rotation
    Node* rotateL(Node* parent) {
        Node* child = parent->right;
        Node* gchild = child->left;

        child->left = parent;
        parent->right = gchild;

        // Update the heights
        parent->height = Node::updateHeight(parent);
        child->height = Node::updateHeight(child);

        return child;  // Return new root after rotation
    }

    // Right-Left Rotation
    Node* rotateRL(Node* parent) {
        parent->right = AVLTree::rotateR(parent->right);
        return AVLTree::rotateL(parent);
    }

    // Left-Right Rotation
    Node* rotateLR(Node* parent) {
        parent->left = AVLTree::rotateL(parent->left);
        return AVLTree::rotateR(parent);
    }

    // Function to insert a new node based on ID
    void insertHelper(int id, string name){
        bool flag = false;

        // Validate the name and ID inputs
        for (const char c: name) {
            if (!isalpha(c) && c != ' ' && c){
                cout << "unsuccessful" << endl;
                return;
            }
        }
        if (0 > id || id > 99999999){
            cout << "unsuccessful" << endl;
            return;
        }

        // Insert the node and print result
        this->root = insert(root, id, name, flag);
        if (flag) {
            cout << "unsuccessful" << endl;
        } else {
            cout << "successful" << endl;
        }
    }

    // Recursive function to insert node in AVL tree and maintain balance
    Node* insert(Node* parent, int id, string name, bool& flag) {
        // Recursive insertion
        if (!parent) {
            return new Node (id, name);
        }
        if (id < parent->id) {
            parent->left = insert(parent->left, id, name, flag);
        }
        else if (id > parent->id) {
            parent->right = insert(parent->right, id, name, flag);
        }
        // Checks for duplicate ids
        // christian
        else {
            flag = true;
            return parent;
        }

        // Update node's height
        parent->height = Node::updateHeight(parent);

        // Check node's balance and perform rotations if necessary
        int balance = Node::getBalance(parent);
        if (balance > 1 && id < parent->left->id) {
            return rotateR(parent);
        }
        if (balance > 1 && id > parent->left->id) {
            return rotateLR(parent);
        }
        if (balance < -1 && id > parent->right->id) {
            return rotateL(parent);
        }
        if (balance < -1 && id < parent->right->id) {
            return rotateRL(parent);
        }
        return parent;  // Return potentially updated root node
    }

    // Function to search tree by ID
    void searchiDHelper(int id){
        bool flag = false;

        // Validate the ID input
        if (0 > id || id > 99999999){
            cout << "unsuccessful" << endl;
            return;
        }

        // Search for the ID and print result
        searchiD(root, id, flag);
        if (!flag) {
            cout << "unsuccessful" << endl;
        }
    }

    // Recursive function to search by ID
    void searchiD(Node* parent, int id, bool& flag) {
        if (!parent) {
            return;
        }
        if (id == parent->id) {
            cout << parent->name << endl;
            flag = true;
        }
        if (id < parent->id) {
            searchiD(parent->left, id, flag);
        } else if (id > parent->id) {
            searchiD(parent->right, id, flag);
        }
    }

    // Function to search tree by name
    void searchNameHelper(string name) {
        bool flag = false;
        searchbyName(root, name, flag);
        if (!flag) {
            cout << "unsuccessful" << endl;
        }
    }

    // Recursive function to search by name
    void searchbyName(Node* parent, string name, bool& flag) {
        if (!parent) {
            return;
        }
        if (name == parent->name) {
            cout << parent->id << endl;
            flag = true;
        }
        searchbyName(parent->left, name, flag);
        searchbyName(parent->right, name, flag);
    }

    // Function to remove a node by ID
    void removeHelper(int id){
        bool flag = false;

        // Validate the ID input
        if (0 > id || id > 99999999){
            cout << "unsuccessful" << endl;
            return;
        }

        // Remove the node and print result
        root = remove(root, id, flag);
        if (!flag){
            cout << "unsuccessful" << endl;
        } else {
            cout << "successful" << endl;
        }
    }

    // Recursive function to remove node from AVL tree and maintain balance
    Node* remove(Node* parent, int id, bool& flag) {
        if (!parent) {
            return parent;
        }

        // Recursive removal
        if (id < parent->id) {
            parent->left = remove(parent->left, id, flag);
        } else if (id > parent->id) {
            parent->right = remove(parent->right, id, flag);
        } else {
            // Node with only one child or no child
            if (!parent->left) {
                Node* temp = parent->right;
                delete parent;
                flag = true;
                return temp;
            } else if (!parent->right) {
                Node* temp = parent->left;
                delete parent;
                flag = true;
                return temp;
            }

            // Node with two children, get inorder successor (smallest in the right subtree)
            Node* temp = parent->right;
            while (temp->left) {
                temp = temp->left;
            }
            parent->id = temp->id;
            parent->name = temp->name;
            parent->right = remove(parent->right, temp->id, flag);
        }
        return parent;
    }

    // Helper function to remove a node based on its position in an inorder traversal
    void removeInorderHelper(int n){
        bool flag = false;
        // Remove the nth node and print result
        removeInorder(n, flag);
        if (!flag) {
            cout << "unsuccessful" << endl;
        } else {
            cout << "successful" << endl;
        }
    }

    // Remove the nth node based on inorder traversal of the tree
    void removeInorder(int n, bool& flag) {
        vector<int> UFIDsInt;
        getInOrderInt(root, UFIDsInt);
        // Ensure the given position is within valid range
        if (static_cast<int>(UFIDsInt.size()) - 1 < n || n < 0) {
            flag = false;
        } else {
            flag = true;
            root = remove(root, UFIDsInt[n], flag);
        }
    }

    // Helper function to populate the UFIDsInt vector with the inorder traversal of node IDs
    void getInOrderInt(Node* parent, vector<int> &UFIDsInt) {
        if (!parent) {
            return;
        }
        getInOrderInt(parent->left, UFIDsInt);
        UFIDsInt.push_back(parent->id);
        getInOrderInt(parent->right, UFIDsInt);
    }

    // Helper function to populate the UFIDs vector with the inorder traversal of node names
    void getInOrder(Node* parent, vector<string> &UFIDs) {
        if (!parent) {
            return;
        }
        getInOrder(parent->left, UFIDs);
        UFIDs.push_back(parent->name);
        getInOrder(parent->right, UFIDs);
    }

    // Helper function to populate the UFIDs vector with the preorder traversal of node names
    void getPreOrder(Node* parent, vector<string>& UFIDs) {
        if (!parent) {
            return;
        }
        UFIDs.push_back(parent->name);
        getPreOrder(parent->left, UFIDs);
        getPreOrder(parent->right, UFIDs);
    }

    // Helper function to populate the UFIDs vector with the postorder traversal of node names
    void getPostOrder(Node* parent, vector<string>& UFIDs) {
        if (!parent) {
            return;
        }
        getPostOrder(parent->left, UFIDs);
        getPostOrder(parent->right, UFIDs);
        UFIDs.push_back(parent->name);
    }

    // Function to print the names in an inorder traversal
    void printInOrder() {
        vector<string> UFIDs;
        getInOrder(root, UFIDs);
        for (int i = 0; i < static_cast<int>(UFIDs.size()); i++) {
            // Print all names separated by commas, except for the last name
            if (i != static_cast<int>(UFIDs.size()) - 1) {
                cout << UFIDs[i] << ", ";
            } else {
                cout << UFIDs[i] << endl;
            }
        }
    }

    // Function to print the names in a preorder traversal
    void printPreOrder() {
        vector<string> UFIDs;
        getPreOrder(root, UFIDs);
        for (int i = 0; i < static_cast<int>(UFIDs.size()); i++) {
            // Print all names separated by commas, except for the last name
            if (i != static_cast<int>(UFIDs.size()) - 1) {
                cout << UFIDs[i] << ", ";
            } else {
                cout << UFIDs[i] << endl;
            }
        }
    }

    // Function to print the names in a postorder traversal
    void printPostOrder() {
        vector<string> UFIDs;
        getPostOrder(root, UFIDs);
        for (int i = 0; i < static_cast<int>(UFIDs.size()); i++) {
            // Print all names separated by commas, except for the last name
            if (i != static_cast<int>(UFIDs.size()) - 1) {
                cout << UFIDs[i] << ", ";
            } else {
                cout << UFIDs[i] << endl;
            }
        }
    }

    // Function to determine the number of levels in the AVL tree
    int printLevelCount(Node* node) {
        if (!node) {
            return 0;
        }
        return max(printLevelCount(node->left), printLevelCount(node->right)) + 1;
    }

    // Helper function to print the count of levels in the tree
    void printLCHelper(){
        cout << printLevelCount(root) << endl;
    }
};