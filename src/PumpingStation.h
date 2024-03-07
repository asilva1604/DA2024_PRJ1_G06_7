//
// Created by alexandre on 05-03-2024.
//

#ifndef PUMPINGSTATION_H
#define PUMPINGSTATION_H

#include <string>

class PumpingStation {
    unsigned int id_;
    std::string code_;
public:
    PumpingStation(const unsigned &id, const std::string &code);
    const unsigned int getId() const;
    const std::string getCode() const;
};



#endif //PUMPINGSTATION_H
