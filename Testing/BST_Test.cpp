#include<bits/stdc++.h>
#include "../BST/Main.h"
using namespace std;

int main(){
    BST bst;
    bst.insert(10);
    bst.insert(5);
    bst.insert(15);
    bst.insert(3);
    bst.insert(7);
    bst.insert(12);
    // bst.prettyPrint();
    bst.printGraphViz("BST.png");
    return 0;
}