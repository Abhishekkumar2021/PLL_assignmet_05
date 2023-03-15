#include<bits/stdc++.h>
#include "../Trie/Main.h"
using namespace std;

int main(){
    Trie t;
    t.insert("abhishek");
    t.insert("akansha");
    t.insert("graph");
    t.insert("mohit");

    t.printGraphviz("Before.png");

    t.remove("akansha");
    t.remove("graph");

    t.printGraphviz("After.png");

    cout << t.countPrefix("ab") << endl;
    cout << t.countPrefix("m") << endl;
    cout << t.size() << endl;
}

