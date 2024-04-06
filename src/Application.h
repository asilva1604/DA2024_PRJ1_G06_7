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
    std::vector<std::string> cities_;

public:
    Application();
    const Graph &getNetwork() const;
    void menu();
    void maxFlow(std::string c);
    void waterSupply();
    void metrics();
    void reservoir();
    void stations();
    void pipelines();
    void goBack();
};



#endif //APPLICATION_H
