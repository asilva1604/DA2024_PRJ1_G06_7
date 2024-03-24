#include <iostream>

#include "Application.h"
#include "FileReader.h"

int main() {
    Application a;

    for (const auto &v : a.getNetwork().getVertexSet()) {
        std::cout << v.second->getInfo().getPointType() << "||" << v.second->getInfo().getId() << "\n";
    }
    return 0;
}
