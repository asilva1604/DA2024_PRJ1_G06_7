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
        cout << endl << "Menu:" << endl << endl;
        cout << "| Basic Service Metrics |" << endl;
        cout << "    T2.1. Maximum Flow" << endl;
        cout << "    T2.2. Water Demand vs Actual Flow" << endl;
        cout << "    T2.3. Metrics before and after load balancing heuristic" << endl << endl;

        cout << "| Reliability and Sensitivity to Failures |" << endl;
        cout << "    T3.1. Reservoir" << endl;
        cout << "    T3.2. Pumping Stations" << endl;
        cout << "    T3.3. Pipelines" << endl << endl;

        cout << "0. Exit" << endl << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                maxFlow();
                break;
            case 2:
                waterSupply();
                break;
            case 3:
                metrics();
                break;
            case 4:
                reservoir();
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

void Application::maxFlow() {
    std::cout << std::endl;
    network_.getMaxFlow(NetworkPoint("C_9"));
    goBack();
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

void Application::reservoir() {

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
        cout << "Enter your choice: ";
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
