//
// Created by alexandre on 05-03-2024.
//

#include "WaterReservoir.h"

WaterReservoir::WaterReservoir(const std::string &name, const std::string &municipality, const unsigned &id,
const std::string &code, const unsigned &maxDelivery) : name_(name), municipality_(municipality),
id_(id), code_(code), maxDelivery_(maxDelivery){}

const std::string & WaterReservoir::getName() const {
    return name_;
}

const std::string & WaterReservoir::getMunicipality() const {
    return municipality_;
}

const unsigned int & WaterReservoir::getId() const {
    return id_;
}

const std::string & WaterReservoir::getCode() const {
    return code_;
}

const unsigned int & WaterReservoir::getMaxDelivery() const {
    return maxDelivery_;
}

