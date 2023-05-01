//======== Copyright (c) 2023, Fedgerino VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - graph
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Richard Huska <xhuska03@stud.fit.vutbr.cz>
// $Date:       $2023-03-07
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author Martin Dočekal
 * @author Karel Ondřej
 *
 * @brief Implementace metod tridy reprezentujici graf.
 */

#include "tdd_code.h"


Graph::Graph(){}

Graph::~Graph(){
    clear();
}

std::vector<Node*> Graph::nodes() {
    std::vector<Node*> nodes;
    nodes = nodes2;
    return nodes;
}

std::vector<Edge> Graph::edges() const{
    std::vector<Edge> edges;
    edges = edges2;
    return edges;
}

Node* Graph::addNode(size_t nodeId) {
    for(auto node : nodes2){
        if(node->id == nodeId)
        return nullptr;
    }
    Node *newNode = new Node();
    newNode->id = nodeId;
    newNode->color = 0;
    nodes2.push_back(newNode);
    
    return newNode;
}

bool Graph::addEdge(const Edge& edge){
    if(containsEdge(edge) == false && edge.a != edge.b){
    addNode(edge.a);
    addNode(edge.b);
    edges2.push_back(edge);
    return true;
    }
    return false;

}

void Graph::addMultipleEdges(const std::vector<Edge>& edges) {
    for(Edge edge1 : edges){
        if(containsEdge(edge1) == false){
            addEdge(edge1);
        }
    }
}

Node* Graph::getNode(size_t nodeId){
    for(auto node: nodes2){
        if (node->id == nodeId){
            return node;
        }
    }
    return nullptr;
}

bool Graph::containsEdge(const Edge& edge) const{
    for(Edge edgerino : edges2){
        if(edgerino == edge){
            return true;
        }
    }
    return false;
}

void Graph::removeNode(size_t nodeId){
    Node* nodeRemove = getNode(nodeId);
    int check = 0;
    if(nodeRemove == nullptr){
        throw std::out_of_range("bla");
    }
    
    for(auto edger = edges2.begin(); edger != edges2.end();){
        if(edger->a == nodeId || edger->b == nodeId){
            edges2.erase(edger);
            check++;
        }else{
            edger++;
        }
    }
    if(check == 0){
        throw std::out_of_range("blah");
    }
    for(auto noder = nodes2.begin(); noder != nodes2.end();){
        if(*noder == nodeRemove){
            nodes2.erase(noder);
        }else{
            ++noder;
        }
    }
    
}

void Graph::removeEdge(const Edge& edge){
    int check = 0;
    for(auto edgerino = edges2.begin(); edgerino != edges2.end();){
        if(*edgerino == edge){
            edges2.erase(edgerino);
            ++check;
        }else{
            ++edgerino;
        }
    }
    if(check == 0){
        throw std::out_of_range("blah");
    }
    

}

size_t Graph::nodeCount() const{
    return nodes2.size();
}

size_t Graph::edgeCount() const{
    return edges2.size();
}

size_t Graph::nodeDegree(size_t nodeId) const{
    size_t num = 0;
    for(const Edge& edger : edges2){
        if(edger.a == nodeId || edger.b == nodeId){
            num++;
        }
    }
    if(num == 0){
        throw std::out_of_range("a");
    }
    return num;
}

size_t Graph::graphDegree() const{
    size_t max = 0;
    for( Node* node : nodes2){
       if(nodeDegree(node->id) > max){
        max = nodeDegree(node->id);
       }
    }
    return max;
}

void Graph::coloring(){
    clear();
}

void Graph::clear() {
    for(auto node : nodes2){
        delete node;
    }
    nodes2.clear();
    auto nodes2 = nodes();
    for(auto node : nodes2){
        delete node;
    }
    
    edges2.clear();
    nodes2.clear();
}

/*** Konec souboru tdd_code.cpp ***/
