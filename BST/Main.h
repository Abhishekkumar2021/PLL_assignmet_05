#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node *left, *right;
    Node(int data){
        this->data = data;
        left = right = NULL;
    }
    Node(){
        left = right = NULL;
    }
};

class BST{
    private:
    Node* root;

    // Helper functions
    Node* insert(Node* root, int data){
        if(root == NULL){
            root = new Node(data);
            return root;
        }
        if(data < root->data){
            root->left = insert(root->left, data);
        }
        else{
            root->right = insert(root->right, data);
        }
        return root;
    }

    bool search(Node* root, int data){
        if(root == NULL){
            return false;
        }
        if(root->data == data){
            return true;
        }
        if(data < root->data){
            return search(root->left, data);
        }
        else{
            return search(root->right, data);
        }
    }

    Node* remove(Node* root, int data){
        if(root==NULL){
            return root;
        }
        if(data < root->data){
            root->left = remove(root->left, data);
        }
        else if(data > root->data){
            root->right = remove(root->right, data);
        }
        else{
            if(root->left == NULL){
                Node* temp = root->right;
                return temp;
            }
            else if(root->right == NULL){
                Node* temp = root->left;
                return temp;
            }
            else{
                Node* temp = root->right;
                while(temp->left != NULL){
                    temp = temp->left;
                }
                root->data = temp->data;
                root->right = remove(root->right, temp->data);
            }
        }
        return root;
    }

    void inorder(Node* root){
        if(root == NULL){
            return;
        }
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void preorder(Node* root){
        if(root == NULL){
            return;
        }
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void postorder(Node* root){
        if(root == NULL){
            return;
        }
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

    int height(Node* root){
        if(root == NULL){
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return max(leftHeight, rightHeight) + 1;
    }

    int size(Node* root){
        if(root == NULL){
            return 0;
        }
        return size(root->left) + size(root->right) + 1;
    }

    int leafNodes(Node* root){
        if(root == NULL){
            return 0;
        }
        if(root->left == NULL && root->right == NULL){
            return 1;
        }
        return leafNodes(root->left) + leafNodes(root->right);
    }

    int nonLeafNodes(Node* root){
        return size(root) - leafNodes(root);
    }

    int oneChildNodes(Node* root){
        if(root == NULL){
            return 0;
        }
        if(root->left == NULL && root->right != NULL){
            return 1 + oneChildNodes(root->right);
        }
        if(root->left != NULL && root->right == NULL){
            return 1 + oneChildNodes(root->left);
        }
        return oneChildNodes(root->left) + oneChildNodes(root->right);
    }

    int twoChildNodes(Node* root){
        if(root == NULL){
            return 0;
        }
        if(root->left != NULL && root->right != NULL){
            return 1 + twoChildNodes(root->left) + twoChildNodes(root->right);
        }
        return twoChildNodes(root->left) + twoChildNodes(root->right);
    }

    void printLevel(Node* root, int curr, int level){
        if(root == NULL){
            return;
        }
        if(curr == level){
            cout << root->data << " ";
            return;
        }
        printLevel(root->left, curr+1, level);
        printLevel(root->right, curr+1, level);
    }

    void printLevel(Node* root, int level){
        printLevel(root, 0, level);
    }

    void prettyPrint(Node* root, int indent){
        if(root == NULL){
            return;
        }
        prettyPrint(root->right, indent + 4);
        for(int i=0; i<indent; i++){
            cout << " ";
        }
        cout << root->data << endl;
        prettyPrint(root->left, indent + 4);
    }
    
    void printGraphViz(Node* root, ofstream &out){
        if(root == NULL){
            return;
        }
        if(root->left != NULL){
            out << root->data << " -> " << root->left->data << endl;
        }
        if(root->right != NULL){
            out << root->data << " -> " << root->right->data << endl;
        }
        printGraphViz(root->left, out);
        printGraphViz(root->right, out);
    }
    
    public:
    BST(){
        root = NULL;
    }

    // Insertion
    void insert(int data){
        root = insert(root, data);
    }

    // Search
    bool search(int data){
        return search(root, data);
    }

    // Deletion
    void remove(int data){
        root = remove(root, data);
    }

    // Inorder traversal
    void inorder(){
        inorder(root);
    }

    // Preorder traversal
    void preorder(){
        preorder(root);
    }

    // Postorder traversal
    void postorder(){
        postorder(root);
    }

    // Height of the tree
    int height(){
        return height(root);
    }

    // Number of nodes in the tree
    int size(){
        return size(root);
    }

    // Number of leaf nodes in the tree
    int leafNodes(){
        return leafNodes(root);
    }

    // Number of non-leaf nodes in the tree
    int nonLeafNodes(){
        return nonLeafNodes(root);
    }

    // Number of nodes with one child in the tree
    int oneChildNodes(){
        return oneChildNodes(root);
    }

    // Number of nodes with two children in the tree
    int twoChildNodes(){
        return twoChildNodes(root);
    }

    // Print kth level of the tree
    void printLevel(int k){
        printLevel(root, k);
        cout << "\n";
    }

    // Print all levels of the tree
    void levelOrder(){
        int h = height(root);
        for(int i=1; i<=h; i++){
            printLevel(root, i);
            cout << endl;
        }
    }

    void prettyPrint(){
        prettyPrint(root, 0);
    }

    void printGraphViz(string filename){
        ofstream out("graph.dot");
        out << "digraph G{ " << endl;
        // Settings for the graph
        out << "node [shape=circle, fillcolor=lightgreen, style=filled];" << endl;
        printGraphViz(root, out);
        out << "}" << endl;
        out.close();
        string cmd = "dot -Tpng graph.dot -o " + filename;
        system(cmd.c_str());
    }
};