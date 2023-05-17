/**
 * The function compares the heights of AVL and Red-Black trees for a set of input files and writes the
 * results to an output file.
 * 
 * @param node This parameter represents a node in a binary search tree, AVL tree, or Red-Black tree.
 * It contains information such as the key value, color (for Red-Black trees), left and right child
 * nodes, and height (for AVL trees).
 * @param k The key value of a node to be inserted into the AVL and RBT trees.
 * 
 * @return The program returns the height of AVL and Red-Black trees for a set of input files and
 * writes the results to an output file.
 */
#include <iostream>
#include <vector>
#include <cstring>
#include <string> 
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

/**
 * Define the node of the AVL tree with two constructors 
*/
class NodeAVL{
public:
    int key;    // This is the key value of this Node
    NodeAVL *left;  // This is the left child node of this Node
    NodeAVL *right; // This is the right child node of this Node
    int height; // This is the height of the tree whose root is this Node

    /**
     * Construct a null node with height 0, null left child and null right child. 
    */

    NodeAVL(){
        left = NULL;
        right = NULL;
        height = 0;
    }

    /**
     * Construct a node with a specified key value
     * @param k the initial key value of this node
    */
    NodeAVL(int k){
        key = k;
        left = NULL;
        right = NULL;
        height = 1; // The height of one node is 1
    }

    /**
     * Destruct a node
    */
    ~NodeAVL(){}

    /**
     * Return a height of the AVL tree whose root is node
     * @param node the root node of the AVL tree 
    */
    friend int getHeight(NodeAVL *node){
        // If node is NULL, the height of node is 0
        if (node == NULL){
            return 0;
        } 
        // Return the height of AVL tree if node is not NULL
        return node->height;
    }

    /**
     * Return the root of the AVL tree after rotating right
     * @param node the root of the subtree
    */
    friend NodeAVL *rightRotate(NodeAVL *node){
        // The left child X of this node becomes the root 
        // This node becomes the right child of its left child (the current root X)
        // The right child of X becomes the left child of this node 
        NodeAVL *x = node->left;    
        NodeAVL *y = x->right;

        x->right = node;
        node->left = y;

        // Update the height of node 
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        // Update the height of the current root node
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        // Return the current root X
        return x;
    }

    /**
     * Return the root of the AVL tree after rotating left
     * @param node the root of the subtree
    */

    friend NodeAVL *leftRotate(NodeAVL *node){
        // The right child X of this node becomes the root 
        // This node becomes the left child of its right child (the current root X)
        // The left child of X becomes the right child of this node 
        NodeAVL *x = node->right;
        NodeAVL *y = x->left;

        x->left = node;
        node->right = y;

        // Update the height of node 
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        // Update the height of the current root node
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        // Return the current root X
        return x;
    }

    /**
     * Return the balance of the tree whose root is node
     * @param node the root of the AVL tree 
    */

    friend int getBalance(NodeAVL *node){
        // If the tree does not have any node, the balance is 0
        if (node == NULL){
            return 0;
        }
        // The balance is the height discrepancy of two subtrees
        return getHeight(node->left) - getHeight(node->right);
    }
};

/**
 * Insert a new node whose key is to the tree whose root is node
 * @param node the root of the tree
 * @param k the initial key value of the new node
*/
NodeAVL* insert(NodeAVL *node, int k){
    // Insert a new node if the tree has no node
    if (node == NULL){
        NodeAVL* newnode = new NodeAVL(k);
        return newnode;
    }
    // Insert a new node to the left subtree if k is less than the key value of this node
    // Insert a new node to the right subtree if k is greater than or equal the key value of this node 
    if (k < node->key){
        node->left = insert(node->left, k);
    } else {
        node->right = insert(node->right, k);
    }

    // Update the height of this node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);
    
    // If balance is greater than 1 and k is inserted to the left subtree of the root's left node
    // Left left case
    if (balance > 1 && k < node->left->key){
        return rightRotate(node);
    }

    // If balance is less than -1 and k is inserted to the right subtree of the root's right node
    // Right right case
    if (balance < -1 && k >= node->right->key){
        return leftRotate(node);
    }

    // If balance is greater than 1 and k is inserted to the right subtree of the root's left node
    // Left right case
    if (balance > 1 && k >= node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // If balance is greater than 1 and k is inserted to the left subtree of the root's right node
    // Right left case
    if (balance < -1 && k < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/**
 * Clear the AVL tree whose root is node
 * @param node the root of the AVL tree
*/
void clearAVL(NodeAVL *node){
    if (node != NULL){
        clearAVL(node->left);
        clearAVL(node->right);
        delete node;
    }
}


/**
 * Define the node of the RBT tree with two constructors 
*/
class NodeRBT{
public:
    int key;    // This is the key value of this node
    int color;  // This is the color of this node, this color has two cases, red 'R' and black 'B'
    NodeRBT *left;  // This is the left child node of this node
    NodeRBT *right; // This is the right child node of this node
    NodeRBT *parent;    // This is the parent node of this node

    /**
     * Construct a null node with color 'R', null left child, null right child and null parent. 
    */
    NodeRBT(){
        color = 'R';
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    /**
     * Construct a new node with key value k, color 'R', null left child, null right child and null parent.
     * @param k the initial key value of this node
    */

    NodeRBT(int k){
        key = k;
        color = 'R';
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    /**
     * Destruct this node
    */
    ~NodeRBT(){}

    /**
     * Return the root of RB tree after rotating left
     * @param node the root of the RB tree 
    */
    friend NodeRBT *leftRotate(NodeRBT *node){
        // The right child X of this node becomes the root 
        // This node becomes the left child of its right child (the current root X) and its right child becomes its parent
        // The left child of X becomes the right child of this node and this node becomes Y's parent 
        NodeRBT *x = node->right;
        NodeRBT *y = x->left;

        x->left = node;
        node->right = y;
        node->parent = x;

        if (y != NULL){
            y->parent = node;
        }

        // Return the current root        
        return x;
    }

    friend NodeRBT *rightRotate(NodeRBT *node){
        // The left child X of this node becomes the root 
        // This node becomes the right child of its left child (the current root X) and its left child becomes its parent
        // The right child of X becomes the left child of this node and this node becomes Y's parent 
        NodeRBT *x = node->left;
        NodeRBT *y = x->right;

        x->right = node;
        node->left = y;
        node->parent = x;

        if (y != NULL){
            y->parent = node;
        }

        // Return the current root  
        return x;
    }

    /**
     * Return the height of tree whose root is node
     * @param node the root of RB tree
    */
    friend int getHeightNode(NodeRBT *node){
        // The height of tree is 0 if the tree has no node
        // Else the height of tree is the max height of two subtrees plus 1
        if (node == NULL){
            return 0;
        }
        else {
            return max(getHeightNode(node->left), getHeightNode(node->right)) + 1;
        }
    }
};


/**
 * Define the Red Black Tree with one constructor
*/
class RBT{
public:
    NodeRBT *root;  // This is the root of RBT
    RBT(){
        root = NULL;    // The default value of root is NULL
    }
    ~RBT(){}
    
    // The status of the balance of this tree
    // These values are true when this tree has these cases each
    bool isLL = false, isRR = false, isLR = false, isRL = false;

    /**
     * The function inserts a new node into a Red-Black Tree and handles color conflicts by performing
     * rotations and color changes.
     * 
     * @param node A pointer to the current node being considered for insertion or rotation in the
     * Red-Black Tree.
     * @param k The key value to be inserted into the Red-Black tree.
     * 
     * @return a pointer to a NodeRBT object, which represents the root of the Red-Black Tree after the
     * insertion of a new node with the given key value.
     */
    NodeRBT *insertChild(NodeRBT *node, int k){

        // If the tree has two nodes whose color is red, the isColorConflict is true 
        bool isColorConflict = false;

        // Insert a new node if this node is a child of leaf node 
        if (node == NULL){
            NodeRBT *newNode = new NodeRBT(k);
            return newNode;
        }

        if (k < node->key){
            node->left = insertChild(node->left, k);
            node->left->parent = node;
            if (node != this->root){
                if (node->color == 'R' && node->left->color == 'R'){
                    isColorConflict = true;
                }
            }
            
        } else {
            node->right = insertChild(node->right, k);
            node->right->parent = node;
            if (node != this->root){
                if (node->color == 'R' && node->right->color == 'R'){
                    isColorConflict = true;
                }
            }
        }

        
        if (this->isLL){
            node = leftRotate(node);
            node->color = 'B';
            node->left->color = 'R';
            this->isLL = false;
        }
        else if (this->isRR){
            node = rightRotate(node);
            node->color = 'B';
            node->right->color = 'R';
            this->isRR = false;
        }
        else if (this->isRL){
            node->right = rightRotate(node->right);
            node->right->parent = node;
            node = leftRotate(node);
            node->color = 'B';
            node->left->color = 'R';
            this->isRL = false;
        }
        else if (this->isLR){
            node->left = leftRotate(node->left);
            node->left->parent = node;
            node = rightRotate(node);
            node->color = 'B';
            node->right->color = 'R';
            this->isLR = false;
        }

        if (isColorConflict){
            if (node->parent->right == node){
                if (node->parent->left == NULL || node->parent->left->color == 'B'){
                    if (node->left != NULL && node->left->color == 'R'){
                        this->isRL = true;
                    }
                    else if (node->right != NULL && node->right->color == 'R'){
                        this->isLL = true;
                    }
                }
                else {
                    node->parent->left->color = 'B';
                    node->color = 'B';
                    if (node->parent != this->root){
                        node->parent->color = 'R';
                    }
                }
            }
            else {
                if (node->parent->right == NULL || node->parent->right->color == 'B'){
                    if (node->left != NULL && node->left->color == 'R'){
                        this->isRR = true;
                    }
                    else if (node->right != NULL && node->right->color == 'R'){
                        this->isLR = true;
                    }
                }
                else {
                    node->parent->right->color = 'B';
                    node->color = 'B';
                    if (node->parent != this->root){
                        node->parent->color = 'R';
                    }
                }
            }
            isColorConflict = false;
        }
        return node;
    }

   /**
    * This function inserts a new node with a given value into a Red-Black Tree.
    * 
    * @param k The value to be inserted into the Red-Black Tree.
    */
    void insert(int k){
        if (this->root == NULL){
            this->root = new NodeRBT(k);
            this->root->color = 'B';
        }
        else {
            this->root = insertChild(this->root, k);
        }
    }

    /**
     * This function returns the height of a binary tree.
     * 
     * @return The function `getHeight()` returns the height of the binary search tree. If the root of
     * the tree is `NULL`, it returns 0. Otherwise, it calls the function `getHeightNode()` to
     * calculate the height of the tree starting from the root node.
     */
    int getHeight(){
        if (this->root == NULL){
            return 0;
        }
        else {
            return getHeightNode(root);
        }
    }
};

/**
 * The function recursively prints the keys of a red-black tree starting from the given node.
 * 
 * @param node A pointer to a NodeRBT object, which represents a node in a Red-Black Tree.
 */
void print(NodeRBT *node){
    if (node != NULL){
        cout << node->key << ' ';
        print(node->left);
        print(node->right);
    }
}

/**
 * The function recursively deletes all nodes in a red-black tree.
 * 
 * @param node A pointer to a NodeRBT object, which represents a node in a Red-Black Tree.
 */
void clearRBT(NodeRBT *node){
    if (node != NULL){
        clearRBT(node->left);
        clearRBT(node->right);
        delete node;
    }
}

/**
 * The above code defines a struct named "Result" with three integer fields.
 * @property {int} num - An integer value representing some numerical data or identifier.
 * @property {int} AVL - AVL stands for Adelson-Velsky and Landis, which is a self-balancing binary
 * search tree. The AVL property is that the heights of the left and right subtrees of any node differ
 * by at most one. This ensures that the tree remains balanced and the time complexity of operations
 * like
 * @property {int} RBT - RBT stands for Red-Black Tree. It is a self-balancing binary search tree where
 * each node has an extra bit, called the color bit, which can be either red or black. The color of the
 * node is used to ensure that the tree remains balanced during insertions and deletions.
 */
struct Result{
    int num;
    int AVL;
    int RBT;
};

int main(){
    /* The above code is declaring a vector named "figure" that will store objects of type "Result".*/
    vector<Result> figure;
    ofstream fo;
    fo.open("figure.out");
    int numTest = 10;
    for (int i = 0; i < numTest; i++){
        /*
            * Read and write file
        */
        string inPut = "test_" + to_string(i + 1) + ".inp";
        ifstream fi;
        fi.open(inPut);

        int numNode;
        fi >> numNode;
        NodeAVL *root = NULL;
        RBT tree;
        
        for (int j = 0; j < numNode; j++){
            int key;
            fi >> key;
            root = insert(root, key);  
            tree.insert(key);           
        }

        figure.push_back({numNode, getHeight(root), tree.getHeight()});
        clearAVL(root);
        clearRBT(tree.root);
        fi.close();
    }

    fo << setprecision(3) << fixed;
    fo << "N:\t";
    for (int i = 0; i < numTest; i++){
        fo << figure[i].num << '\t';
    }
    fo << '\n';
    fo << "LogN:\t";
    for (int i = 0; i < numTest; i++){
        fo << log2(figure[i].num) << '\t';
    }
    fo << '\n';
    fo << "AVL_Tree:\t";
    for (int i = 0; i < numTest; i++){
        fo << figure[i].AVL << '\t';
    }
    fo << '\n';
    fo << "RB_Tree:\t";
    for (int i = 0; i < numTest; i++){
        fo << figure[i].RBT << '\t';
    }
    fo << '\n';
    fo << "1.45LogN:\t";
    for (int i = 0; i < numTest; i++){
        fo << 1.45 * log2(figure[i].num) << '\t';
    }
    fo << '\n';

    fo.close();
    return 0;
}
