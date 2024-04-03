//
// Created by alexandre on 07-03-2024.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <float.h>
#include <unordered_map>
#include "NetworkPoint.h"

template <class T>
class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
public:
    Vertex(T in);

    T getInfo() const;
    std::vector<Edge<T> *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge<T> *getPath() const;
    std::vector<Edge<T> *> getIncoming() const;

    void setInfo(T info);
    void setVisited(bool visited);
    void setProcesssing(bool processing);
    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge<T> *path);
    Edge<T> * addEdge(Vertex<T> *dest, double w);
    bool removeEdge(T in);
    void removeOutgoingEdges();
    Edge<T>* findEdge(Vertex<T>* dest);

protected:
    T info;                // info node
    std::vector<Edge<T> *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge<T> *path = nullptr;

    std::vector<Edge<T> *> incoming; // incoming edges

    void deleteEdge(Edge<T> *edge);

};

/********************** Edge  ****************************/

template <class T>
class Edge {
public:
    Edge(Vertex<T> *orig, Vertex<T> *dest, double w);

    Vertex<T> * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex<T> * getOrig() const;
    Edge<T> *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge<T> *reverse);
    void setFlow(double flow);
    double getResidual() const;
protected:
    Vertex<T> * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex<T> *orig;
    Edge<T> *reverse = nullptr;

    double flow = 0; // for flow-related problems
};

template<class T>
double Edge<T>::getResidual() const {
    return weight - flow;
}

/********************** Graph  ****************************/

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex<NetworkPoint> *findVertex(const NetworkPoint &in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const NetworkPoint &in);
    bool removeVertex(const NetworkPoint &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const NetworkPoint &sourc, const NetworkPoint &dest, double w);
    bool removeEdge(const NetworkPoint &source, const NetworkPoint &dest);
    bool addBidirectionalEdge(const NetworkPoint &sourc, const NetworkPoint &dest, double w);

    int getNumVertex() const;
    std::unordered_map<std::string, Vertex<NetworkPoint> *> getVertexSet() const;

    std:: vector<NetworkPoint> dfs() const;
    std:: vector<NetworkPoint> dfs(const NetworkPoint & source) const;
    void dfsVisit(Vertex<NetworkPoint> *v,  std::vector<NetworkPoint> & res) const;
    std::vector<Vertex<NetworkPoint> *> bfs(const NetworkPoint & source) const;

    bool isDAG() const;
    bool dfsIsDAG(Vertex<NetworkPoint> *v) const;
    std::vector<NetworkPoint> topsort() const;
    void edmondKarp(Vertex<NetworkPoint> *source, Vertex<NetworkPoint> *sink);
    /**
     * @brief calculates max flow to a certain city
     * @param city
     */
    void getMaxFlow(NetworkPoint city);

    bool bfs(Vertex<NetworkPoint> *source, Vertex<NetworkPoint> *sink, std::unordered_map<Vertex<NetworkPoint>*, Vertex<NetworkPoint>*>& parent);

protected:
    std::unordered_map<std::string, Vertex<NetworkPoint> *> vertexSet;    // vertex set
    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall
    void addSuperSourceAndSink();
    void addSuperSource();

    /**
     * should only run once, is supposed to calculate max flow to all cities, which are the sinks
     */

    /**
     * serves to store if the maximum flow edmond karps algorithm has already been ran
     */
    bool maxFlowRan = false;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


#endif //GRAPH_H
