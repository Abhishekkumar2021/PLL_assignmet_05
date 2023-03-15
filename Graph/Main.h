#include<bits/stdc++.h>
using namespace std;

template <typename T>

class GraphNode{
    T label;
    vector<GraphNode<T>*> neighbours;
    bool visited;               // For DFS and BFS traversal
    bool beingVisited;        // For detecting cycles

    public:
    GraphNode(T label){
        this->label = label;
        visited = false;
    }

    void addNeighbour(GraphNode<T>* neighbour){
        neighbours.push_back(neighbour);
    }

    void removeNeighbour(GraphNode<T>* neighbour){
        for(int i=0; i<neighbours.size(); i++){
            if(neighbours[i] == neighbour){
                neighbours.erase(neighbours.begin()+i);
                return;
            }
        }
    }
    void removeNeighbour(T label){
        for(int i=0; i<neighbours.size(); i++){
            if(neighbours[i]->getLabel() == label){
                neighbours.erase(neighbours.begin()+i);
                return;
            }
        }
    }

    vector<GraphNode<T>*> getNeighbours(){
        return neighbours;
    }

    T getLabel(){
        return label;
    }

    bool isVisited(){
        return visited;
    }

    void setVisited(bool visited){
        this->visited = visited;
    }

    bool isBeingVisited(){
        return beingVisited;
    }

    void setBeingVisited(bool beingVisited){
        this->beingVisited = beingVisited;
    }

    bool hasNeighbour(GraphNode<T>* neighbour){
        for(int i=0; i<neighbours.size(); i++){
            if(neighbours[i] == neighbour){
                return true;
            }
        }
        return false;
    }

    bool hasNeighbour(T label){
        for(int i=0; i<neighbours.size(); i++){
            if(neighbours[i]->getLabel() == label){
                return true;
            }
        }
        return false;
    }

    GraphNode<T>* getNeighbour(T label){
        for(int i=0; i<neighbours.size(); i++){
            if(neighbours[i]->getLabel() == label){
                return neighbours[i];
            }
        }
        return NULL;
    }

    void print(){
        cout << label << " -> ";
        for(int i=0; i<neighbours.size(); i++){
            cout << neighbours[i]->getLabel() << " ";
        }
        cout << endl;
    }

    int getDegree(){
        return neighbours.size();
    }
    
};

template <typename T>
class Graph{
    vector<GraphNode<T>*> nodes;

    public: Graph(){
        nodes = vector<GraphNode<T>*>();
    }

    private: void addNode(GraphNode<T>* node){
        nodes.push_back(node);
    }

    public: void addNode(T label){
        GraphNode<T>* node = new GraphNode(label);
        nodes.push_back(node);
    }

    private: void addEdge(GraphNode<T>* node1, GraphNode<T>* node2){
        node1->addNeighbour(node2);
    }

    public: void addEdge(T label1, T label2){
        GraphNode<T>* node1 = getNode(label1);
        GraphNode<T>* node2 = getNode(label2);
        if(node1 == NULL || node2 == NULL){
            return;
        }
        addEdge(node1, node2);
    }

    private: void removeNode(GraphNode<T>* node){
        for(int i=0; i<nodes.size(); i++){
            if(nodes[i] == node){
                nodes.erase(nodes.begin()+i);
                return;
            }
        }
    }

    public: void removeNode(T label){
        for(int i=0; i<nodes.size(); i++){
            if(nodes[i]->getLabel() == label){
                nodes.erase(nodes.begin()+i);
                return;
            }
        }
    }

    private: GraphNode<T>* getNode(T label){
        for(int i=0; i<nodes.size(); i++){
            if(nodes[i]->getLabel() == label){
                return nodes[i];
            }
        }
        return NULL;
    }

    public: void print(){
        for(int i=0; i<nodes.size(); i++){
            nodes[i]->print();
        }
    }

    public: void printGraphviz(string filename){
        ofstream fout("graph.dot");
        fout << "digraph G {" << endl;
        stringstream ss;
        for(int i=0; i<nodes.size(); i++){
            vector<GraphNode<T>*> neighbours = nodes[i]->getNeighbours();
            for(int j=0; j<neighbours.size(); j++){
                fout << nodes[i]->getLabel() << " -> " << neighbours[j]->getLabel() << endl;
            }
        }
        fout << "}" << endl;
        fout.close();
        string command = "dot -Tpng graph.dot -o " + filename;
        system(command.c_str());
    }

    private: void dfs(GraphNode<T>* node){
        node->setVisited(true);
        cout << node->getLabel() << " ";
        vector<GraphNode<T>*> neighbours = node->getNeighbours();
        for(int i=0; i<neighbours.size(); i++){
            if(!neighbours[i]->isVisited()){
                dfs(neighbours[i]);
            }
        }
    }

    private: void dfs(T label){
        GraphNode<T>* node = getNode(label);
        if(node == NULL){
            return;
        }
        dfs(node);
    }

    public: void dfs(){
        for(int i=0; i<nodes.size(); i++){
            if(!nodes[i]->isVisited()){
                dfs(nodes[i]);
            }
        }
    }

    private: void bfs(GraphNode<T>* node){
        queue<GraphNode<T>*> q;
        q.push(node);
        node->setVisited(true);
        while(!q.empty ()){
            GraphNode<T>* current = q.front();
            q.pop();
            cout << current->getLabel() << " ";
            vector<GraphNode<T>*> neighbours = current->getNeighbours();
            for(int i=0; i<neighbours.size(); i++){
                if(!neighbours[i]->isVisited()){
                    q.push(neighbours[i]);
                    neighbours[i]->setVisited(true);
                }
            }
        }
    }

    private: void bfs(T label){
        GraphNode<T>* node = getNode(label);
        if(node == NULL){
            return;
        }
        bfs(node);
    }

    public: void bfs(){
        for(int i=0; i<nodes.size(); i++){
            if(!nodes[i]->isVisited()){
                bfs(nodes[i]);
            }
        }
    }

    public: bool hasEdge(T label1, T label2){
        GraphNode<T>* node1 = getNode(label1);
        GraphNode<T>* node2 = getNode(label2);
        if(node1 == NULL || node2 == NULL){
            return false;
        }
        return node1->hasNeighbour(node2);
    } 

    public: void removeEdge(T label1, T label2){
        GraphNode<T>* node1 = getNode(label1);
        GraphNode<T>* node2 = getNode(label2);
        if(node1 == NULL || node2 == NULL){
            return;
        }
        node1->removeNeighbour(node2);
    }

    private: void resetVisited(){
        for(int i=0; i<nodes.size(); i++){
            nodes[i]->setVisited(false);
        }
    }

    private: void dfsIterative(GraphNode<T>* node){
        stack<GraphNode<T>*> s;
        s.push(node);
        node->setVisited(true);
        while(!s.empty()){
            GraphNode<T>* current = s.top();
            s.pop();
            cout << current->getLabel() << " ";
            vector<GraphNode<T>*> neighbours = current->getNeighbours();
            for(int i=0; i<neighbours.size(); i++){
                if(!neighbours[i]->isVisited()){
                    s.push(neighbours[i]);
                    neighbours[i]->setVisited(true);
                }
            }
        }
    }

    private: void dfsIterative(T label){
        GraphNode<T>* node = getNode(label);
        if(node == NULL){
            return;
        }
        dfsIterative(node);
    }

    public: void dfsIterative(){
        for(int i=0; i<nodes.size(); i++){
            if(!nodes[i]->isVisited()){
                dfsIterative(nodes[i]);
            }
        }
    }

    public: int countConnectedComponents(){
        int count = 0;
        for(int i=0; i<nodes.size(); i++){
            if(!nodes[i]->isVisited()){
                count++;
                dfs(nodes[i]);
            }
        }
        return count;
    }

    public: bool isTree(){
        if(isCyclic()){
            return false;
        }
        for(int i=0; i<nodes.size(); i++){
            if(!nodes[i]->isVisited()){
                return false;
            }
        }
        return true;
    }

    // Check cycle for directed graph
    public: bool isCyclic(){
        resetVisited();
        for(int i=0; i<nodes.size(); i++){
            if(!nodes[i]->isVisited()){
                if(isCyclic(nodes[i])){
                    return true;
                }
            }
        }
        return false;
    }

    private: bool isCyclic(GraphNode<T>* node){
        node->setVisited(true);
        node->setBeingVisited(true);
        vector<GraphNode<T>*> neighbours = node->getNeighbours();
        for(int i=0; i<neighbours.size(); i++){
            if(!neighbours[i]->isVisited()){
                if(isCyclic(neighbours[i])){
                    return true;
                }
            } else if(neighbours[i]->isBeingVisited()){
                return true;
            }
        }
        node->setBeingVisited(false);
        return false;
    }

    public: void topologicalSort(){
        stack<GraphNode<T>*> s;
        resetVisited();
        for(int i=0; i<nodes.size(); i++){
            if(!nodes[i]->isVisited()){
                topologicalSort(nodes[i], s);
            }
        }
        while(!s.empty()){
            cout << s.top()->getLabel() << " ";
            s.pop();
        }
        cout << endl;
    }

    private: void topologicalSort(GraphNode<T>* node, stack<GraphNode<T>*>& s){
        node->setVisited(true);
        vector<GraphNode<T>*> neighbours = node->getNeighbours();
        for(int i=0; i<neighbours.size(); i++){
            if(!neighbours[i]->isVisited()){
                topologicalSort(neighbours[i], s);
            }
        }
        s.push(node);
    }

};