//
// Created by alexandre on 07-03-2024.
//

#include "Graph.h"

/************************* Vertex  **************************/

template <class T>
Vertex<T>::Vertex(T in): info(in) {}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
Edge<T> * Vertex<T>::addEdge(Vertex<T> *d, double w) {
    auto newEdge = new Edge<T>(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdge(T in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        Vertex<T> *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
template <class T>
void Vertex<T>::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

template <class T>
T Vertex<T>::getInfo() const {
    return this->info;
}

template <class T>
std::vector<Edge<T>*> Vertex<T>::getAdj() const {
    return this->adj;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return this->visited;
}

template <class T>
bool Vertex<T>::isProcessing() const {
    return this->processing;
}

template <class T>
unsigned int Vertex<T>::getIndegree() const {
    return this->indegree;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template <class T>
Edge<T> *Vertex<T>::getPath() const {
    return this->path;
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return this->incoming;
}

template <class T>
void Vertex<T>::setInfo(T in) {
    this->info = in;
}

template <class T>
void Vertex<T>::setVisited(bool visited) {
    this->visited = visited;
}

template <class T>
void Vertex<T>::setProcesssing(bool processing) {
    this->processing = processing;
}

template <class T>
void Vertex<T>::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

template <class T>
void Vertex<T>::setDist(double dist) {
    this->dist = dist;
}

template <class T>
void Vertex<T>::setPath(Edge<T> *path) {
    this->path = path;
}

template <class T>
void Vertex<T>::deleteEdge(Edge<T> *edge) {
    Vertex<T> *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/

template <class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, double w): orig(orig), dest(dest), weight(w) {}

template <class T>
Vertex<T> * Edge<T>::getDest() const {
    return this->dest;
}

template <class T>
double Edge<T>::getWeight() const {
    return this->weight;
}

template <class T>
Vertex<T> * Edge<T>::getOrig() const {
    return this->orig;
}

template <class T>
Edge<T> *Edge<T>::getReverse() const {
    return this->reverse;
}

template <class T>
bool Edge<T>::isSelected() const {
    return this->selected;
}

template <class T>
double Edge<T>::getFlow() const {
    return flow;
}

template <class T>
void Edge<T>::setSelected(bool selected) {
    this->selected = selected;
}

template <class T>
void Edge<T>::setReverse(Edge<T> *reverse) {
    this->reverse = reverse;
}

template <class T>
void Edge<T>::setFlow(double flow) {
    this->flow = flow;
}

/********************** Graph  ****************************/

int Graph::getNumVertex() const {
    return vertexSet.size();
}

std::unordered_map<std::string, Vertex<NetworkPoint> *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex<NetworkPoint> * Graph::findVertex(const NetworkPoint &in) const {
    auto a = vertexSet.find(in.getCode());
    if (a != vertexSet.end()) return a->second;
    return nullptr;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const NetworkPoint &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.emplace(in.getCode(), new Vertex<NetworkPoint>(in));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
bool Graph::removeVertex(const NetworkPoint &in) {
    auto it = vertexSet.find(in.getCode());

    if (it == vertexSet.end()) return false;

    it->second->removeOutgoingEdges();

    auto itt = vertexSet.begin();

    while (itt != vertexSet.end()) {
        itt->second->removeEdge(it->second->getInfo());
        ++itt;
    }

    vertexSet.erase(it);

    delete it->second;
    return true;

    /*for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }`*/
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(const NetworkPoint &sourc, const NetworkPoint &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
bool Graph::removeEdge(const NetworkPoint &sourc, const NetworkPoint &dest) {
    Vertex<NetworkPoint> * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

bool Graph::addBidirectionalEdge(const NetworkPoint &sourc, const NetworkPoint &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

/****************** DFS ********************/

/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 */
std::vector<NetworkPoint> Graph::dfs() const {
    std::vector<NetworkPoint> res;
    for (auto v : vertexSet)
        v.second->setVisited(false);
    for (auto v : vertexSet)
        if (!v.second->isVisited())
            dfsVisit(v.second, res);
    return res;
}

/*
 * Performs a depth-first search (dfs) in a graph (this) from the source node.
 * Returns a vector with the contents of the vertices by dfs order.
 */
std::vector<NetworkPoint> Graph::dfs(const NetworkPoint & source) const {
    std::vector<NetworkPoint> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }
    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v.second->setVisited(false);
    }
    // Perform the actual DFS using recursion
    dfsVisit(s, res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */
void Graph::dfsVisit(Vertex<NetworkPoint> *v, std::vector<NetworkPoint> & res) const {
    v->setVisited(true);
    res.push_back(v->getInfo());
    for (auto & e : v->getAdj()) {
        auto w = e->getDest();
        if (!w->isVisited()) {
            dfsVisit(w, res);
        }
    }
}

/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */
std::vector<NetworkPoint> Graph::bfs(const NetworkPoint & source) const {
    std::vector<NetworkPoint> res;
    // Get the source vertex
    auto s = findVertex(source);
    if (s == nullptr) {
        return res;
    }

    // Set that no vertex has been visited yet
    for (auto v : vertexSet) {
        v.second->setVisited(false);
    }

    // Perform the actual BFS using a queue
    std::queue<Vertex<NetworkPoint> *> q;
    q.push(s);
    s->setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for (auto & e : v->getAdj()) {
            auto w = e->getDest();
            if ( ! w->isVisited()) {
                q.push(w);
                w->setVisited(true);
            }
        }
    }
    return res;
}

/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

bool Graph::isDAG() const {
    for (auto v : vertexSet) {
        v.second->setVisited(false);
        v.second->setProcesssing(false);
    }
    for (auto v : vertexSet) {
        if (! v.second->isVisited()) {
            if ( ! dfsIsDAG(v.second) ) return false;
        }
    }
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
bool Graph::dfsIsDAG(Vertex<NetworkPoint> *v) const {
    v->setVisited(true);
    v->setProcesssing(true);
    for (auto e : v->getAdj()) {
        auto w = e->getDest();
        if (w->isProcessing()) return false;
        if (! w->isVisited()) {
            if (! dfsIsDAG(w)) return false;
        }
    }
    v->setProcesssing(false);
    return true;
}

/****************** toposort ********************/
//=============================================================================
// Exercise 1: Topological Sorting
//=============================================================================
// TODO
/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

std::vector<NetworkPoint> Graph::topsort() const {
    std::vector<NetworkPoint> res;

    for (auto v : vertexSet) {
        v.second->setIndegree(0);
    }
    for (auto v : vertexSet) {
        for (auto e : v.second->getAdj()) {
            unsigned int indegree = e->getDest()->getIndegree();
            e->getDest()->setIndegree(indegree + 1);
        }
    }

    std::queue<Vertex<NetworkPoint> *> q;
    for (auto v : vertexSet) {
        if (v.second->getIndegree() == 0) {
            q.push(v.second);
        }
    }

    while( !q.empty() ) {
        Vertex<NetworkPoint> * v = q.front();
        q.pop();
        res.push_back(v->getInfo());
        for(auto e : v->getAdj()) {
            auto w = e->getDest();
            w->setIndegree(w->getIndegree() - 1);
            if(w->getIndegree() == 0) {
                q.push(w);
            }
        }
    }

    if ( res.size() != vertexSet.size() ) {
        //std::cout << "Impossible topological ordering!" << std::endl;
        res.clear();
        return res;
    }

    return res;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

void Graph::calculateMaxFlowForAll() {
    addSuperSourceAndSink();

    auto s = findVertex(NetworkPoint("source"));
    auto t = findVertex(NetworkPoint("sink"));

    if (s == nullptr || t == nullptr || s==t) {
        std::cout << "Error! Either vertex not found or they are the same";
        return;
    }

    //zero the flow
    for (auto p : vertexSet) {
        for (auto e : p.second->getAdj()) {
            e->setFlow(0);
        }
    }

    while (findAugPath(s, t))  {
        unsigned fl = findMinimalResidualAlongPath(s, t);
        augment(s, t, fl);
    }

    /*
    unsigned max_flow = 0;
    for (auto edge : s->getAdj()) {
        max_flow+=edge->getFlow();
    }

    std::cout << max_flow << std::endl;
     */
}

bool Graph::findAugPath(Vertex<NetworkPoint> *s, Vertex<NetworkPoint> *t) const{
    for (auto p : vertexSet) {
        p.second->setVisited(false);
    }

    s->setVisited(false);

    std::queue<Vertex<NetworkPoint> *> qu;

    qu.push(s);

    while (!t->isVisited() && !qu.empty()) {
        auto v = qu.front();
        qu.pop();
        for (auto edge : v->getAdj()) {
            if (!edge->getDest()->isVisited() && (edge->getWeight() - edge->getFlow())) {
                edge->getDest()->setVisited(true);
                edge->getDest()->setPath(edge);
                qu.push(edge->getDest());
            }
        }

        for (auto edge : v->getIncoming()) {
            if (!edge->getOrig()->isVisited() && edge->getFlow()) {
                edge->getOrig()->setVisited(true);
                edge->getOrig()->setPath(edge);
                qu.push(edge->getOrig());
            }
        }
    }
    return t->isVisited();
}

unsigned int Graph::findMinimalResidualAlongPath(Vertex<NetworkPoint> *s, Vertex<NetworkPoint> *t) const{
    unsigned int min_residual = UINTMAX_MAX;
    for (auto current_vertex = t; current_vertex != s;) {
        auto edge = current_vertex->getPath();
        if (edge->getDest() == current_vertex) {
            min_residual = std::min((double)min_residual, edge->getWeight() - edge->getFlow());
            current_vertex = edge->getOrig();
        } else {
            min_residual = std::min((double)min_residual, edge->getFlow());
            current_vertex = edge->getDest();
        }
    }
    return min_residual;
}

void Graph::augment(Vertex<NetworkPoint> *s, Vertex<NetworkPoint> *t, unsigned f) {
    for (auto current_vertex = t; current_vertex != s;) {
        auto edge = current_vertex->getPath();
        unsigned int current_flow = edge->getFlow();
        if (edge->getDest() == current_vertex) {
            edge->setFlow(current_flow + f);
            current_vertex = edge->getOrig();
        } else {
            edge->setFlow(current_flow - f);
            current_vertex = edge->getDest();
        }
    }
}

void Graph::addSuperSource() {
    std::vector<Vertex<NetworkPoint> *> sources;
    for (const auto &p : vertexSet) {
        auto v = p.second;
        if (v->getInfo().getPointType() == "reservoir") {
            sources.push_back(v);
        }
    }
    NetworkPoint s("source");

    addVertex(s);

    for (const auto &v : sources) {
        addEdge(s, v->getInfo(), DBL_MAX);
    }
}

void Graph::addSuperSourceAndSink() {
    std::vector<Vertex<NetworkPoint> *> sources;
    std::vector<Vertex<NetworkPoint> *> sinks;
    for (const auto &p : vertexSet) {
        auto v = p.second;
        if (v->getInfo().getPointType() == "reservoir") {
            sources.push_back(v);
        }
        else if (v->getInfo().getPointType() == "city") {
            sinks.push_back(v);
        }
    }
    NetworkPoint ss("source");
    NetworkPoint sss("sink");
    addVertex(ss);
    addVertex(sss);

    for (const auto &v : sources) {
        addEdge(ss, v->getInfo(), DBL_MAX);
    }
    for (const auto &v : sinks) {
        addEdge(v->getInfo(), sss, DBL_MAX);
    }
}

void Graph::getMaxFlow(NetworkPoint city) {
    if (!maxFlowRan) {
        calculateMaxFlowForAll();
        maxFlowRan = true;
    }

    auto sink = findVertex(city);

    unsigned max_flow = 0;
    for (auto e : sink->getAdj()) {
        if (e->getDest()->getInfo().getCode() == "sink") {
            max_flow = e->getFlow();
        }
    }

    std::cout << max_flow << std::endl;
}

