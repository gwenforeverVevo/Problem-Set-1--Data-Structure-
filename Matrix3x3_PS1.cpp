// Matrix3x3_PS1.cpp
#include "Matrix3x3.h"
#include <iostream>
#include <cassert>
#include <cmath>
#include <stdexcept>

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& aOther) const noexcept {
    return Matrix3x3(
        Vector3D(row(0).dot(aOther.column(0)), row(0).dot(aOther.column(1)), row(0).dot(aOther.column(2))),
        Vector3D(row(1).dot(aOther.column(0)), row(1).dot(aOther.column(1)), row(1).dot(aOther.column(2))),
        Vector3D(row(2).dot(aOther.column(0)), row(2).dot(aOther.column(1)), row(2).dot(aOther.column(2)))
    );
}

float Matrix3x3::det() const noexcept {
    return row(0)[0] * (row(1)[1] * row(2)[2] - row(1)[2] * row(2)[1])
        - row(0)[1] * (row(1)[0] * row(2)[2] - row(1)[2] * row(2)[0])
        + row(0)[2] * (row(1)[0] * row(2)[1] - row(1)[1] * row(2)[0]);
}

Matrix3x3 Matrix3x3::transpose() const noexcept {
    return Matrix3x3(
        Vector3D(row(0)[0], row(1)[0], row(2)[0]),
        Vector3D(row(0)[1], row(1)[1], row(2)[1]),
        Vector3D(row(0)[2], row(1)[2], row(2)[2])
    );
}

bool Matrix3x3::hasInverse() const noexcept {
    return det() != 0.0f;
}

Matrix3x3 Matrix3x3::inverse() const {
    float determinant = det();
    if (determinant == 0.0f) {
        throw std::runtime_error("Matrix is not invertible");
    }

    // Calculate the adjugate matrix and divide by the determinant
    Matrix3x3 adjugate(
        Vector3D(
            row(1)[1] * row(2)[2] - row(1)[2] * row(2)[1],
            row(0)[2] * row(2)[1] - row(0)[1] * row(2)[2],
            row(0)[1] * row(1)[2] - row(0)[2] * row(1)[1]
        ),
        Vector3D(
            row(1)[2] * row(2)[0] - row(1)[0] * row(2)[2],
            row(0)[0] * row(2)[2] - row(0)[2] * row(2)[0],
            row(0)[2] * row(1)[0] - row(0)[0] * row(1)[2]
        ),
        Vector3D(
            row(1)[0] * row(2)[1] - row(1)[1] * row(2)[0],
            row(0)[1] * row(2)[0] - row(0)[0] * row(2)[1],
            row(0)[0] * row(1)[1] - row(0)[1] * row(1)[0]
        )
    );

    return adjugate * (1.0f / determinant);
}

std::ostream& operator<<(std::ostream& aOStream, const Matrix3x3& aMatrix) {
    return aOStream << "[" << aMatrix.row(0).toString() << "," << aMatrix.row(1).toString() << "," << aMatrix.row(2).toString() << "]";
}
