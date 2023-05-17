#include <iostream>
#include <vector>
#include <cstring>
#include <string> 
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

class Node{
public:
    int key;
    Node *left;
    Node *right;
    int height;

    Node(){
        left = NULL;
        right = NULL;
        height = 0;
    }

    Node(int k){
        key = k;
        left = NULL;
        right = NULL;
        height = 1;
    }

    ~Node(){}

    friend Node* newNode(int k){
        Node* node = new Node(k);
        return node;
    }

    friend int getHeight(Node *N){
        if (N == NULL){
            return 0;
        }
        return N->height;
    }

    friend Node *rightRotate(Node *y){
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    friend Node *leftRotate(Node *x){
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    friend int getBalance(Node *N){
        if (N == NULL){
            return 0;
        }
        return getHeight(N->left) - getHeight(N->right);
    }

    
    friend ostream &operator << (ostream &os, Node *root){
        if (root != NULL){
            os << root->key << ' ';
            os << root->left;
            os << root->right;
        }
        return os;
    }
};

Node* insert(Node *node, int k){
    if (node == NULL){
        Node* newnode = new Node(k);
        return newnode;
    }
    if (k < node->key){
        node->left = insert(node->left, k);
    } else {
        node->right = insert(node->right, k);
    }

    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    int balance = getBalance(node);

    if (balance > 1 && k < node->left->key){
        return rightRotate(node);
    }

    if (balance < -1 && k >= node->right->key){
        return leftRotate(node);
    }

    if (balance > 1 && k >= node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && k < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void clear(Node *node){
    if (node != NULL){
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

int main(){
    vector<int> figure_1, figure_2;
    ofstream fo;
    fo.open("figure_AVL.out");
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
        // fo << numNode << '\n'; 
        Node *root = NULL;
        for (int j = 0; j < numNode; j++){
            int key;
            fi >> key;
            // fo << key << '\n';
            root = insert(root, key);            
            // cout << root << '\n';
        }

        figure_1.push_back(numNode);
        figure_2.push_back(getHeight(root));

        // fo << root << '\n';
        clear(root);
        fi.close();
        // fo << "Tree " << i + 1 << ": ";
        // fo << root;
        // fo << '\n';
    }

    fo << setprecision(3) << fixed;
    fo << "LogN:\t";
    for (int i = 0; i < numTest; i++){
        fo << log2(figure_1[i]) << '\t';
    }
    fo << '\n';
    fo << "Height:\t";
    for (int i = 0; i < numTest; i++){
        fo << figure_2[i] << '\t';
    }
    fo << '\n';
    fo << "1.45LogN:\t";
    for (int i = 0; i < numTest; i++){
        fo << 1.45 * log2(figure_1[i]) << '\t';
    }
    fo << '\n';

    fo.close();
    return 0;
}