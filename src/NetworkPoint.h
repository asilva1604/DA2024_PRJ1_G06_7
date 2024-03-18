//
// Created by alexandre on 18-03-2024.
//

#ifndef NETWORKPOINT_H
#define NETWORKPOINT_H

#include <string>

class NetworkPoint {
    std::string city_;
    unsigned id_;
    std::string code_;
    float demand_;
    std::string population_;
    std::string reservoir_;
    std::string municipality_;
    int maxDelivery_;
    std::string pointType_;
public:
    NetworkPoint(const std::string& city, const unsigned& id, const std::string& code, const float& demand, const std::string& population);
    NetworkPoint(const std::string& reservoir, const std::string& municipality, const unsigned& id, const std::string& code, const int& maxDelivery);
    NetworkPoint(const unsigned& id, const std::string& code);
    [[nodiscard]] const std::string& getCity() const;
    [[nodiscard]] unsigned getId() const;
    [[nodiscard]] const std::string& getCode() const;
    [[nodiscard]] float getDemand() const;
    [[nodiscard]] const std::string& getPopulation() const;
    [[nodiscard]] const std::string& getReservoir() const;
    [[nodiscard]] const std::string& getMunicipality() const;
    [[nodiscard]] int getMaxDelivery() const;
    [[nodiscard]] const std::string& getPointType() const;
    bool operator==(const NetworkPoint& other) const;
};



#endif //NETWORKPOINT_H
