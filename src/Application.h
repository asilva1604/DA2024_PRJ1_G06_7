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
    void menu();
    void maxFlow(std::string c);
    void waterSupply();
    void metrics();
    void reservoir(std::string c);
    void stations();
    void pipelines();
    void goBack();
    bool waterSupplyRan = false;
    std::vector<std::pair<std::string, std::pair<double, double>>> supply;
};



#endif //APPLICATION_H
