//
// Created by alexandre on 05-03-2024.
//

#include "PumpingStation.h"

PumpingStation::PumpingStation(const unsigned &id, const std::string &code) : id_(id), code_(code) {}

const unsigned int PumpingStation::getId() const {
    return id_;
}

const std::string PumpingStation::getCode() const {
    return code_;
}
