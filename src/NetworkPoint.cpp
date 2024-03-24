//
// Created by alexandre on 18-03-2024.
//

#include "NetworkPoint.h"

NetworkPoint::NetworkPoint(const std::string &city, const unsigned &id, const std::string &code, const float &demand,
    const std::string &population) {
    city_ = city;
    id_ = id;
    code_ = code;
    demand_ = demand;
    population_ = population;
    reservoir_ = "";
    municipality_ = "";
    maxDelivery_ = 0;
    pointType_ = "city";
}

NetworkPoint::NetworkPoint(const std::string &reservoir, const std::string &municipality, const unsigned &id,
    const std::string &code, const int &maxDelivery) {
    city_ = "";
    id_ = id;
    code_ = code;
    demand_ = 0;
    population_ = "";
    reservoir_ = reservoir;
    municipality_ = municipality;
    maxDelivery_ = maxDelivery;
    pointType_ = "reservoir";
}

NetworkPoint::NetworkPoint(const unsigned &id, const std::string &code) {
    city_ = "";
    id_ = id;
    code_ = code;
    demand_ = 0;
    population_ = "";
    reservoir_ = "";
    municipality_ = "";
    maxDelivery_ = 0;
    pointType_ = "station";
}

NetworkPoint::NetworkPoint(const std::string &code) {
    id_ = 0;
    city_ = "";
    code_ = code;
    demand_ = 0;
    population_ = "";
    reservoir_ = "";
    municipality_ = "";
    maxDelivery_ = 0;
    pointType_ = "";
}

const std::string& NetworkPoint::getCity() const {
    return city_;
}

unsigned NetworkPoint::getId() const {
    return id_;
}

const std::string& NetworkPoint::getCode() const {
    return code_;
}

float NetworkPoint::getDemand() const {
    return demand_;
}

const std::string& NetworkPoint::getPopulation() const {
    return population_;
}

const std::string& NetworkPoint::getReservoir() const {
    return reservoir_;
}

const std::string& NetworkPoint::getMunicipality() const {
    return municipality_;
}

int NetworkPoint::getMaxDelivery() const {
    return maxDelivery_;
}

const std::string & NetworkPoint::getPointType() const {
    return pointType_;
}

bool NetworkPoint::operator==(const NetworkPoint &other) const{
    return this->code_ == other.code_;
}
