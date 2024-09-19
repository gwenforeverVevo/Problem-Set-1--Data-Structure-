#include <iostream>
#define _USE_MATH_DEFINES  
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix3x3.h"
#include "Polygon.h"
#include <fstream> 

void runP1();
void runP2();
void runP3();
using namespace std;
int main()
{
    Vector2D a(1.0f, 2.0f);
    Vector2D b(1.0f, 4.0f);
    Vector2D c(-2.0f, 3.0f);
    Vector2D d(0.0f, 0.0f);

    std::cout << "Test vector implementation: " << std::endl;
    std::cout << "Vector a = " << a << std::endl;
    std::cout << "Vector b = " << b << std::endl;
    std::cout << "Vector c = " << c << std::endl;
    std::cout << "Vector d = " << d << std::endl;

    Vector3D a3(a);
    Vector3D b3(b);
    Vector3D c3(c);
    Vector3D d3(d);

    std::cout << "Vector a3 = " << a3 << std::endl;
    std::cout << "Vector b3 = " << b3 << std::endl;
    std::cout << "Vector c3 = " << c3 << std::endl;
    std::cout << "Vector d3 = " << d3 << std::endl;

    std::cout << "Test homogeneous vectors:" << std::endl;
    std::cout << "Vector " << a3 << " * 3.0 = " << a3 * 3.0f << std::endl;
    std::cout << "Vector " << a3 << " + " << b3 << " = " << a3 + b3 << std::endl;
    std::cout << "Vector " << a3 << " . " << b3 << " = " << a3.dot(b3) << std::endl;
    std::cout << "Vector " << a3 << "[0] = " << a3[0] << " <=> " << a3 << ".x() = " << a3.x() << std::endl;
    std::cout << "Vector " << a3 << "[1] = " << a3[1] << " <=> " << a3 << ".y() = " << a3.y() << std::endl;
    std::cout << "Vector " << a3 << "[2] = " << a3[2] << " <=> " << a3 << ".w() = " << a3.w() << std::endl;

    std::cout << "Test 3x3 matrix:" << std::endl;

    Matrix3x3 ma(Vector3D(1.0f, 1.0f), Vector3D(1.0f, 1.0f), Vector3D(1.0f, 1.0f));

    std::cout << "ma: row 1 = " << ma.row(0) << std::endl;
    std::cout << "ma: row 2 = " << ma.row(1) << std::endl;
    std::cout << "ma: row 3 = " << ma.row(2) << std::endl;

    Matrix3x3 mb = ma * 2.0f;

    std::cout << "mb: row 1 = " << mb.row(0) << std::endl;
    std::cout << "mb: row 2 = " << mb.row(1) << std::endl;
    std::cout << "mb: row 3 = " << mb.row(2) << std::endl;

    Matrix3x3 mc = mb + ma;

    std::cout << "mc: row 1 = " << mc.row(0) << std::endl;
    std::cout << "mc: row 2 = " << mc.row(1) << std::endl;
    std::cout << "mc: row 3 = " << mc.row(2) << std::endl;

    Matrix3x3 lScale = Matrix3x3::scale(3.2f, 3.2f);
    Matrix3x3 lRotate = Matrix3x3::rotate(90.0f);
    Matrix3x3 lTranslate = Matrix3x3::translate(4.0f, -1.0f);

    std::cout << "Scale " << a3 << " by " << 3.2f << " = " << lScale * a3 << std::endl;
    std::cout << "Rotate " << b3 << " by " << 90.0f << " degrees = " << lRotate * b3 << std::endl;
    std::cout << "Translate " << c3 << " by " << lTranslate.column(2) << " = " << lTranslate * c3 << std::endl;
    std::cout << "Translate " << d3 << " by " << lTranslate.column(2) << " = " << lTranslate * d3 << std::endl;


    runP1();
    cout << "\n\n" << endl;
    runP2();
    cout << "\n\n" << endl;
    runP3();

    return 0;
}



void runP1()
{
    //gCount++;
    Vector3D a(1.0f, 2.0f, 3.0f);
    Vector3D b(static_cast<float>(M_PI), static_cast<float>(M_PI), static_cast<float>(M_PI));
    Vector3D c(1.23456789f, 9.876543210f, 12435.0987654321f);
    cout << "Vector a: " << a.toString() << endl;
    cout << "Vector b: " << b.toString() << endl;
    cout << "Vector c: " << c.toString() << endl;
}

void runP2()
{
    Matrix3x3 M(
        Vector3D(25.0f, -3.0f, -8.0f),
        Vector3D(6.0f, 2.0f, 15.0f),
        Vector3D(11.0f, -3.0f, 4.0f)
    );

    std::cout << "Test matrix M:" << std::endl;
    std::cout << M << std::endl;

    // Test multiplication
    std::cout << "M * M = " << std::endl;
    std::cout << M * M << std::endl;

    // Test determinant
    std::cout << "det M = " << M.det() << std::endl;

    // Test invertibility
    std::cout << "Has M an inverse? " << (M.hasInverse() ? "Yes" : "No") << std::endl;

    // Test transpose
    std::cout << "transpose of M:" << std::endl;
    std::cout << M.transpose() << std::endl;

    // Test inverse
    std::cout << "inverse of M:" << std::endl;
    std::cout << M.inverse() << std::endl;

    // Test inverse multiplied by scalar
    std::cout << "inverse of M * 45:" << std::endl;
    std::cout << M.inverse() * 45.0f << std::endl;
}



void runP3() {
    
    std::string fileNames[] = { "data.txt", "parallelogram.txt" };

    for (const std::string& fileName : fileNames) {
        Polygon polygon;

        
        std::ifstream inputFile(fileName);
        if (!inputFile) {
            std::cerr << "Error opening file: " << fileName << std::endl;
            continue;  
        }

        std::cout << "Processing file: " << fileName << std::endl;
        polygon.readData(inputFile);  

        std::cout << "Signed area: " << polygon.getSignedArea() << std::endl;

        
        Matrix3x3 scalingMatrix = Matrix3x3::scale(2.0f, 2.0f);
        Polygon transformedPolygon = polygon.transform(scalingMatrix);

        std::cout << "Transformed polygon's signed area: " << transformedPolygon.getSignedArea() << std::endl;
        std::cout << "------------------------------------" << std::endl;
    }
}

