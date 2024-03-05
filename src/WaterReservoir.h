//
// Created by alexandre on 05-03-2024.
//

#ifndef WATERRESERVOIR_H
#define WATERRESERVOIR_H

#include <string>



class WaterReservoir {
    std::string name_;
    std::string municipality_;
    unsigned int id_;
    std::string code_;
    unsigned int maxDelivery_;
public:
    WaterReservoir(const std::string &name, const std::string &municipality,
        const unsigned &id, const std::string &code, const unsigned &maxDelivery);
    const std::string &getName() const;
    const std::string &getMunicipality() const;
    const unsigned int &getId() const;
    const std::string &getCode() const;
    const unsigned int &getMaxDelivery() const;
};



#endif //WATERRESERVOIR_H
