#include "Vector3D.h"
#include <sstream>
#include <iomanip>

std::string Vector3D::toString() const noexcept {
    std::stringstream ss;
    
    ss << std::fixed << std::setprecision(4);
    ss << "[" << x() << "," << y() << "," << w() << "]";
    return ss.str();
}
