#include <iostream>

#include "Application.h"
#include "FileReader.h"

int main() {
    Application a;

    for (const auto &v : a.getNetwork().getVertexSet()) {
        std::cout << v->getInfo().getPointType() << "||" << v->getInfo().getId() << "\n";
    }
    return 0;
}
