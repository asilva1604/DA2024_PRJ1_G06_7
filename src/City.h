//
// Created by alexandre on 05-03-2024.
//

#ifndef CITY_H
#define CITY_H

#include <string>

class City {
    std::string name_;
    unsigned int id_;
    std::string code_;
    unsigned int demand_;
    unsigned int population_;
public:
    City(const std::string &name, const unsigned int &id, const std::string &code,
         const unsigned int &demand, const unsigned int &population);

    const std::string &getName() const;
    const unsigned int &getId() const;
    const std::string &getCode() const;
    const unsigned int &getDemand() const;
    const unsigned int &getPopulation() const;
};



#endif //CITY_H
