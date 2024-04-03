//
// Created by alexandre on 18-03-2024.
//

#include "Application.h"

#include "FileReader.h"

Application::Application() {
    FileReader cities("../../dataset/Cities_Madeira.csv");
    FileReader reservoirs("../../dataset/Reservoirs_Madeira.csv");
    FileReader stations("../../dataset/Stations_Madeira.csv");
    FileReader pipes("../../dataset/Pipes_Madeira.csv");

    for (const auto &v : cities.getData()) {
        network_.addVertex(NetworkPoint(v.at(0), std::stoi(v.at(1)), v.at(2),
            stof(v.at(3)), v.at(4)));
    }

    for (const auto &v : reservoirs.getData()) {
        network_.addVertex(NetworkPoint(v.at(0), v.at(1), std::stoi(v.at(2)),
            v.at(3), std::stoi(v.at(4))));
    }

    for (const auto &v : stations.getData()) {
        network_.addVertex(NetworkPoint(std::stoi(v.at(0)), v.at(1)));
    }

    for (const auto &v : pipes.getData()) {
        network_.addEdge(NetworkPoint(v.at(0)), NetworkPoint(v.at(1)),
            std::stod(v.at(2)));
        if (v.at(3) == "0") {
            network_.addEdge(NetworkPoint(v.at(0)), NetworkPoint(v.at(1)),
                std::stod(v.at(2)));
        }
    }

    network_.edmondsKarp(NetworkPoint("source"), NetworkPoint("C_10"));
    for (auto v : network_.getVertexSet()) {
        std::cout << v.second->getInfo().getCode() << std::endl;
        for (auto e : v.second->getAdj()) {
            std::cout << e->getFlow() << "||" << e->getWeight() << std::endl;
        }
        std::cout << std::endl;
    }
}

const Graph & Application::getNetwork() const {
    return network_;
}
