#include "Vector3D.h"
#include <sstream>
#include <iomanip> // For setting the precision

std::string Vector3D::toString() const noexcept {
    std::stringstream ss;
    // Set precision to 4 decimal points
    ss << std::fixed << std::setprecision(4);
    ss << "[" << x() << "," << y() << "," << w() << "]";
    return ss.str();
}
