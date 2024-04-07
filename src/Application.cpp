//
// Created by alexandre on 18-03-2024.
//

#include "Application.h"

#include "FileReader.h"
#include <iostream>

using namespace std;

Application::Application() {
    FileReader cities("../../dataset/Cities_Madeira.csv");
    FileReader reservoirs("../../dataset/Reservoirs_Madeira.csv");
    FileReader stations("../../dataset/Stations_Madeira.csv");
    FileReader pipes("../../dataset/Pipes_Madeira.csv");

    for (const auto &v: cities.getData()) {
        network_.addVertex(NetworkPoint(v.at(0), stoi(v.at(1)), v.at(2),
                                        stof(v.at(3)), v.at(4)));
        cities_.push_back(v.at(2));
    }

    for (const auto &v: reservoirs.getData()) {
        network_.addVertex(NetworkPoint(v.at(0), v.at(1), stoi(v.at(2)),
                                        v.at(3), stoi(v.at(4))));
    }

    for (const auto &v: stations.getData()) {
        network_.addVertex(NetworkPoint(stoi(v.at(0)), v.at(1)));
    }

    for (const auto &v: pipes.getData()) {
        network_.addEdge(NetworkPoint(v.at(0)), NetworkPoint(v.at(1)),
                         stod(v.at(2)));
        if (v.at(3) == "0") {
            network_.addEdge(NetworkPoint(v.at(0)), NetworkPoint(v.at(1)),
                             stod(v.at(2)));
        }
    }

    menu();
}

void Application::menu() {
    int choice;

    do {
        cout << endl << "+-------------------------------------------------------------+" << endl;
        cout << "|  Welcome to the Analysis Tool for Water Supply Management!  |" << endl;
        cout << "|                    We hope to be useful!                    |" << endl;
        cout << "+-------------------------------------------------------------+" << endl << endl;
        cout << "| Basic Service Metrics |" << endl;
        cout << "    T2.1. Maximum Flow" << endl;
        cout << "    T2.2. Water Demand vs Actual Flow" << endl;
        cout << "    T2.3. Metrics before and after load balancing heuristic" << endl << endl;

        cout << "| Reliability and Sensitivity to Failures |" << endl;
        cout << "    T3.1. Reservoir" << endl;
        cout << "    T3.2. Pumping Stations" << endl;
        cout << "    T3.3. Pipelines" << endl << endl;

        cout << "0. Exit" << endl << endl;
        cout << "Enter your choice and press ENTER: ";
        cin >> choice;

        string sel;
        switch (choice) {
            case 1:
                cout << "Enter the city, or enter the string \"all\" for all cities: ";
                cin >> sel;
                maxFlow(sel);
                break;
            case 2:
                waterSupply();
                break;
            case 3:
                metrics();
                break;
            case 4:
                cout << "Enter the reservoir to take out.";
                cin >> sel;
                reservoir(sel);
                break;
            case 5:
                stations();
                break;
            case 6:
                pipelines();
                break;
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void Application::maxFlow(string c) {
    std::cout << std::endl;
    double flow;
    if (c == "all") {
        for (const auto &city: cities_) {
            flow = network_.getMaxFlow(NetworkPoint(city));
            maxFlows_.emplace(city, double);
            std::cout << "Max flow to city " << city << " is " << flow << std::endl;
        }
        goBack();
        return;
    } else if (auto v = network_.findVertex(NetworkPoint(c)) != nullptr) {
        flow = network_.getMaxFlow(NetworkPoint(c));
        std::cout << "Max flow to city " << c << " is " << flow << std::endl;
        goBack();
        return;
    } else {
        std::cout << "City not found!" << std::endl;
        goBack();
        return;
    }
}

void Application::waterSupply() {
    // calculate water supply
    std::vector<std::pair<std::string, std::pair<double, double>>> waterSupply = network_.checkWaterSupply();
    // PRINT WATER SUPPLY
    network_.printWaterSupply(waterSupply);
    goBack();
}

void Application::metrics() {
    // calculate initial metrics
    std::vector<double> initialMetrics = network_.calculateMetrics();
    // PRINT METRICS
    std::cout << std::endl << "| Initial Metrics |" << std::endl;
    network_.printMetrics(initialMetrics);

    // balance load
    double averageDifference = initialMetrics.at(0);
    network_.balanceLoad(averageDifference);

    // calculate final metrics
    std::vector<double> finalMetrics = network_.calculateMetrics();
    // PRINT METRICS
    std::cout << "| Metrics after Load Balancing |" << std::endl;
    network_.printMetrics(finalMetrics);
    goBack();
}

void Application::reservoir(string r) {
    maxFlow("all");

    unordered_map<string, double> newFlows;

    auto source = network_.findVertex(NetworkPoint("source"));

    if (source == nullptr) return;

    for (const auto &edge : source->getAdj()) {
        if (edge->getDest()->getInfo().getCode() == r) {
            edge->setWeight(0.0);
        }
    }



    goBack();
}

void Application::stations() {

    goBack();
}

void Application::pipelines() {

    goBack();
}

void Application::goBack() {
    int choice;

    do {
        cout << endl << "0. Back" << endl;
        cout << "Enter your choice and press ENTER: ";
        cin >> choice;

        if (choice == 0)
            return;
        else
            cout << "Invalid choice. Please try again." << endl;

    } while (choice != 0);
}

const Graph &Application::getNetwork() const {
    return network_;
}
