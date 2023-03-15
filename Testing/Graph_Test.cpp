#include<bits/stdc++.h>
#include "../Graph/Main.h"
using namespace std;

int main(){
    Graph<int> g;
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addEdge(1,2);
    g.addEdge(1,3);
    g.addEdge(2,3);

    g.printGraphviz("Graph1.png");
}