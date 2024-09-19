
#include "Polygon.h"
#include <cassert>


float Polygon::getSignedArea() const noexcept {
    assert(fNumberOfVertices >= 3);  

    float area = 0.0f;
    for (size_t i = 0; i < fNumberOfVertices; ++i) {
        const Vector2D& current = fVertices[i];
        const Vector2D& next = fVertices[(i + 1) % fNumberOfVertices];  
        area += (current.y() + next.y()) * (current.x() - next.x());
    }

    return area * 0.5f;  
}


Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept {
    Polygon transformedPolygon;
    for (size_t i = 0; i < fNumberOfVertices; ++i) {
        Vector3D homogenousVertex(fVertices[i].x(), fVertices[i].y(), 1.0f);
        Vector3D transformedVertex = aMatrix * homogenousVertex;
        transformedPolygon.fVertices[i] = Vector2D(transformedVertex.x(), transformedVertex.y());
    }

    transformedPolygon.fNumberOfVertices = fNumberOfVertices;
    return transformedPolygon;
}
