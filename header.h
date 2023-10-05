#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int id;
    int data;
    string name;
    Node* left;
    Node* right;
    int height;
    Node(int id, string name) : id(id), name(name), left(nullptr), right(nullptr), height(1) {}


    static int getHeight(Node* root) {
        // checking if root exists
        if (!root) {
            return 0;
        }
        else {
            return root->height;
        }
    }

    // changed
    static int updateHeight(Node* root) {
        // if (root->left == nullptr || root->right == nullptr) {
        // 	return 1;
        // }
        // else {
        // 	return max(Node::getHeight(root->left), Node::getHeight(root->right)) + 1;
        // }
        if (!root){
            return 0;
        }
        return max(Node::getHeight(root->left), Node::getHeight(root->right)) + 1;
    }

    static int getBalance(Node* node) {
        if (!node) {
            cout << "node doesnt exist!" << endl;
            return 0;
        }
        int balance = Node::getHeight(node->left) - Node::getHeight(node->right);
        return balance;
    }
};

class AVLTree {
public:
    Node* root = nullptr;
    // in the case of L - L - L imbalance
    Node* rotateR(Node* parent) {
        // setup nodes and pointers
        Node* child = parent->left;
        Node* gchild = child->right;

        // perform rotation
        child->right = parent;
        parent->left = gchild;

        // update heights
        parent->height = Node::updateHeight(parent);
        child->height = Node::updateHeight(child);

        // returns child as new root
        return child;
    }

    Node* rotateL(Node* parent) {
        Node* child = parent->right;
        Node* gchild = child->left;

        child->left = parent;
        parent->right = gchild;

        // update heights
        parent->height = Node::updateHeight(parent);
        child->height = Node::updateHeight(child);

        // return child as new root
        return child;
    }

    Node* rotateRL(Node* parent) {
        parent->right = AVLTree::rotateR(parent->right);
        return AVLTree::rotateL(parent);
    }

    Node* rotateLR(Node* parent) {
        parent->left = AVLTree::rotateL(parent->left);
        return AVLTree::rotateR(parent);
    }

    // pass in root, string name, int id, bool flag)
    // insert by id
    void insertHelper(int id, string name){
        bool flag = false;
        // check id and name validity
        // string: !letter and !space = !isalpha(c) && c != ' '
        for (const char c: name) {
            // for const char c : name
            if (!isalpha(c) && c != ' '){
                cout << "unsuccessful." << endl;
                return;
            }
        }
        // id: if !id is >= 00000000 = 0 and <= 99999999
        if (0 > id || id > 99999999){
            cout << "unsuccessful." << endl;
            return;
        }

        // call insert
        this->root = insert(root, id, name, flag);
        // if duplicate == true
        if (flag == true){
            // print unsuccessful
            cout << "unsuccessful." << endl;
            return;
        }
        else {
            // print successful
            // print tester
            cout << "successful. node inserted." << endl;
        }
    }

    Node* insert(Node* parent, int id, string name, bool& flag) {
        // traverse to the right location and insert
        if (parent == nullptr) {
            return new Node (id, name);
        }
        if (id < parent->id) {
            parent->left = insert(parent->left, id, name, flag);
        }
        else if (id > parent->id) {
            parent->right = insert(parent->right, id, name, flag);
        }
        else {
            flag = true;
            return parent;
        }
        // changed this line
        // parent->height = max(Node::getHeight(parent->left), Node::getHeight(parent->right)) + 1;
        parent->height = Node::updateHeight(parent);

        int balance = Node::getBalance(parent);

        // rotations based on balance factor and id
        // left-left
        // changed: added returns
        if (balance > 1 && id < parent->left->id) {
            return rotateR(parent);
        }
        // left right
        if (balance > 1 && id > parent->left->id) {
            return rotateLR(parent);
        }
        // right-right
        if (balance < -1 && id > parent->right->id) {
            return rotateL(parent);
        }
        // right left
        if (balance < -1 && id < parent->right->id) {
            return rotateRL(parent);
        }
        return parent;
    }

    void searchiDHelper(int id){
        bool flag = false;
        // id: if !id is >= 00000000 = 0 and <= 99999999
        if (0 > id || id > 99999999){
            cout << "unsuccessful." << endl;
            return;
        }
        // checking if the id has any alphabet characters
        // fix alpha
        // causing errors because it always converts to string
//        string idStr = to_string(id);
//        for (char c : idStr){
//            cout << "unsucessful." << endl;
//            return;
//        }
        searchiD(root, id, flag);
        if (flag == false) {
            cout << "unsuccessful." << endl;
        }
    }

    // search by ID
    void searchiD(Node* parent, int id, bool& flag) {
        // return all names with ID
        // changed nullptr to NULL
        if (parent == NULL) {
            // print tester
            cout << "Unsuccessful. No node found!" << endl;
        }
        if (parent->id == id) {
            cout << parent->name << endl;
            flag = true;
        }
        // call search recursively
        if (id < parent->id) {
            searchiD(parent->left, id, flag);
        }
        else if (id > parent->id) {
            searchiD(parent->right, id, flag);
        }
    }

    // make func that takes in the name you want to search and have bool in that func and then youd call search
    void searchNameHelper(string name) {
        // call the search function
        bool flag = false;
        for (const char c: name) {
            // for const char c : name
            if (!isalpha(c) && c != ' '){
                cout << "unsucessful." << endl;
                return;
            }
        }
        searchbyName(root, name, flag);
        // if flag == false
        // changed to false
        if (flag == false) {
            // print unsuccessful
            cout << "Unsuccessful. Node w/name provided not found." << endl;
        }
    }

    // return UF ID's with a given name
    // DOESN'T WORK FOR MULTIPLE NAMES
    void searchbyName(Node* parent, string name, bool& flag) {
        if (parent == nullptr) {
            return;
        }
        if (name == parent->name) {
            cout << parent->id << endl;
            flag = true;
        }
        searchbyName(parent->left, name, flag);
        searchbyName(parent->right, name, flag);

    }

    void removeHelper(int id){
        bool flag = false;
        // id: if !id is >= 00000000 = 0 and <= 99999999
        if (0 > id || id > 99999999){
            cout << "unsuccessful." << endl;
            return;
        }

        remove(root, id, flag);
        if (flag == false){
            cout << "unsuccessful." << endl;
        }
        else {
            cout << "successful." << endl;
        }
    }

    Node* remove(Node* parent, int id, bool& flag) {
        // take into account 3 scenarios: 0, 1, 2 children
        if (parent == nullptr) {
            return parent;
        }
        if (id < parent->id) {
            parent->left = remove(parent->left, id, flag);
        }
        if (id > parent->id) {
            parent->right = remove(parent->right, id, flag);
        }
        if (id == parent->id) {
            // 0
            if (parent->right == nullptr && parent->left == nullptr) {
                flag = true;
                delete parent;
                return nullptr;
            }
            // 1
            if (parent->right != nullptr && parent->left == nullptr) {
                // save ptr to parent as temp
                Node* temp = parent->right;
                // remove node
                flag = true;
                delete parent;
                // return temp
                return temp;

            }
            else if (parent->left != nullptr && parent->right == nullptr) {
                // save ptr to parent as temp
                Node* temp = parent->left;
                // remove node
                flag = true;
                delete parent;
                // return temp
                return temp;
            }
            // 2
            if (parent->left != nullptr && parent->right != nullptr) {
                // find the inorder successor
                Node* successor = parent->right;
                while (successor->left != nullptr) {
                    successor = successor->left;
                }
                // make temp point to inorder successor
                Node* temp = successor;
                // copy over id of successor
                parent->id = temp->id;
                parent->name = temp->name;
                // remove successor and take care of its children
                flag = true;
                parent->right = remove(parent->right, temp->id, flag);
            }
        }
        return parent;
    }

    void removeInorderHelper(int n){
        bool flag = false;
        removeInorder(n, flag);
        if (flag == false){
            cout << "unsuccessful." << endl;
        }
        else{
            cout << "successful. removed node " << n << "." << endl;
        }
    }

    // changed from type Node to type void
    void removeInorder(int n, bool& flag) {
        vector<int> UFIDs;
        // call get inorder with parent and vector
        getInOrder(root, UFIDs);
        // check if size of vector is < n
        if (UFIDs.size() - 1 < n || n < 0) {
            flag = false;
            // change tester
//            cout << n << endl;
        }
        // return remove at ufid(n)
        else {
            flag = true;
            root = remove(root, UFIDs[n], flag);
        }
    }

    void getInOrder(Node* parent, vector<int> &UFIDs) {
        if (parent == nullptr) {
            return;
        }
        getInOrder(parent->left, UFIDs);
        UFIDs.push_back(parent->id);
        getInOrder(parent->right, UFIDs);
    }

    void getPreOrder(Node* parent, vector<int>& UFIDs) {
        if (parent == nullptr) {
            return;
        }
        UFIDs.push_back(parent->id);
        getPreOrder(parent->left, UFIDs);
        getPreOrder(parent->right, UFIDs);
    }

    void getPostOrder(Node* parent, vector<int>& UFIDs) {
        if (parent == nullptr) {
            return;
        }
        getPostOrder(parent->left, UFIDs);
        getPostOrder(parent->right, UFIDs);
        UFIDs.push_back(parent->id);
    }

    void printInOrder() {
        vector<int> UFIDs;
        getInOrder(root, UFIDs);
        for (int i = 0; i < UFIDs.size(); i++) {
            // takes care of every node except last
            if (i != UFIDs.size() - 1) {
                cout << UFIDs[i] << ", ";
            }
            // takes care of last node
            if (i == UFIDs.size() - 1) {
                cout << UFIDs[i] << endl;
            }
        }
    }

    void printPreOrder() {
        vector<int> UFIDs;
        getPreOrder(root, UFIDs);
        for (int i = 0; i < UFIDs.size(); i++) {
            // takes care of every node except last
            if (i != UFIDs.size() - 1) {
                cout << UFIDs[i] << ", ";
            }
            // takes care of last node
            if (i == UFIDs.size() - 1) {
                cout << UFIDs[i] << endl;
            }
        }
    }

    void printPostOrder() {
        vector<int> UFIDs;
        getPostOrder(root, UFIDs);
        for (int i = 0; i < UFIDs.size(); i++) {
            // takes care of every node except last
            if (i != UFIDs.size() - 1) {
                cout << UFIDs[i] << ", ";
            }
            // takes care of last node
            if (i == UFIDs.size() - 1) {
                cout << UFIDs[i] << endl;
            }
        }
    }

    // int printLevelCount() {
    // 	if (root == nullptr) {
    // 		return 0;
    // 	}
    // 	return max(printLevelCount(root->left), printLevelCount(root->right)) + 1;
    // }
    int printLevelCount(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return max(printLevelCount(node->left), printLevelCount(node->right)) + 1;
    }

    void printLCHelper(){
        cout << printLevelCount(root) << endl;
    }

};