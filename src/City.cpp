//
// Created by alexandre on 05-03-2024.
//

#include "City.h"

City::City(const std::string &name, const unsigned int &id, const std::string &code,
           const unsigned int &demand, const unsigned int &population)
    : name_(name), id_(id), code_(code), demand_(demand), population_(population) {}

const std::string &City::getName() const {
    return name_;
}

const unsigned int &City::getId() const {
    return id_;
}

const std::string &City::getCode() const {
    return code_;
}

const unsigned int &City::getDemand() const {
    return demand_;
}

const unsigned int &City::getPopulation() const {
    return population_;
}
