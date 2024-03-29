//
// Created by alexandre on 18-03-2024.
//

#ifndef APPLICATION_H
#define APPLICATION_H
#include <unordered_map>

#include "Graph.h"
#include "NetworkPoint.h"


class Application {
    Graph network_;

public:
    Application();
    const Graph &getNetwork() const;

};



#endif //APPLICATION_H
