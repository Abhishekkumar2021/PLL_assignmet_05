#include<bits/stdc++.h>
using namespace std;

class Node{
    private:
    Node* children[26];
    int count;

    public:

    Node(){
        count = 0;
        for(int i=0; i<26; i++){
            children[i] = NULL;
        }
    }

    bool hasChild(char c){
        return children[c-'a'] != NULL;
    }

    Node* getChild(char c){
        return children[c-'a'];
    }

    void addChild(char c){
        children[c-'a'] = new Node();
    }

    void removeChild(char c){
        children[c-'a'] = NULL;
    }


    bool isEndOfWord(){
        return count > 0;
    }

    void incrementCount(){
        count++;
    }

    int getWordEndCount(){
        return count;
    }

    void decrementCount(){
        count--;
    }

    int getChildrenCount(){
        int count = 0;
        for(int i=0; i<26; i++){
            if(children[i] != NULL){
                count++;
            }
        }
        return count;
    }

};

class Trie{
    private: 
    Node* root;

    void printGraphviz(Node* node, ofstream& out){
        if(node == NULL){
            return;
        }
        if(node->isEndOfWord()){
            out << "node" << node << " [label=" <<node->getWordEndCount() << ", shape=doublecircle];" << endl;
        }
        for(int i=0; i<26; i++){
            if(node->hasChild(i+'a')){
                // Add node label and edge label
                out << "node" << node << " [label=" <<node->getWordEndCount() << "];" << endl;
                out << "node" << node << " -> node" << node->getChild(i+'a') << " [label=\"" << (char)(i+'a') << "\"];" << endl;
                printGraphviz(node->getChild(i+'a'), out);
            }
        }

    }
    void remove(Node* node, string word, int index){
        if(index == word.length()){
            node->decrementCount();
            return;
        }
        char c = word[index];
        if(node->hasChild(c)){
            Node* child = node->getChild(c);
            remove(node->getChild(c), word, index+1);
            if(child->getWordEndCount() == 0 && child->getChildrenCount() == 0){
                node->removeChild(c);
            }
        }
    }

    int size(Node* node){
        int count = 0;
        if(node->isEndOfWord()){
            count += node->getWordEndCount();
        }
        for(int i=0; i<26; i++){
            if(node->hasChild(i+'a')){
                count += size(node->getChild(i+'a'));
            }
        }
        return count;
    }

    public:
    Trie(){
        root = new Node();
    }

    void insert(string word){
        Node* current = root;
        for(int i=0; i<word.length(); i++){
            char c = word[i];
            if(!current->hasChild(c)){
                current->addChild(c);
            }
            current = current->getChild(c);
        }
        current->incrementCount();
    }

    bool search(string word){
        Node* current = root;
        for(int i=0; i<word.length(); i++){
            char c = word[i];
            if(!current->hasChild(c)){
                return false;
            }
            current = current->getChild(c);
        }
        return current->isEndOfWord();
    }

    // Delete a word from the trie
    void remove(string word){
        remove(root, word, 0);
    }

    int size(){
        return size(root);
    }

    int getChildrenCount(){
        return root->getChildrenCount();
    }

    int countPrefix(string prefix){
        Node* current = root;
        for(int i=0; i<prefix.length(); i++){
            char c = prefix[i];
            if(!current->hasChild(c)){
                return 0;
            }
            current = current->getChild(c);
        }
        return current->getChildrenCount();
    }

    void printGraphviz(string filename){
        ofstream out("graph.dot");
        out << "digraph G {" << endl;
        out << "node [shape=circle, fillcolor=lightgreen, style=filled];" << endl;
        printGraphviz(root, out); 
        out << "}";
        out.close();
        string command = "dot -Tpng graph.dot -o " + filename;
        system(command.c_str());
    }
};