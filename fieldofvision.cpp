#include "fieldofvision.h"
#include "spmath.h"
namespace seekpoint {
    FieldOfVision::FieldOfVision(float viewDistance, float fov, float rotation, const sf::Vector2f& origin)
        : viewDistance(viewDistance), fov(fov), rotation(rotation), origin(origin) {}

    std::pair<sf::Vector2f, sf::Vector2f> FieldOfVision::calculateConePoints() const {
        float radians = fov * (Math::PI / 180);
        float x1 = origin.x;
        float y1 = origin.y;
        sf::Vector2f p1 = sf::Vector2f(
            x1 + viewDistance * cos(radians),
            y1 + viewDistance * sin(radians)
        );
        sf::Vector2f p2 = sf::Vector2f(
            x1 + viewDistance * cos(radians),
            y1 - viewDistance * sin(radians)
        );
        return std::make_pair(p1, p2);
    }

    bool FieldOfVision::isInFieldOfVision(const sf::Vector2f& point) const {
        sf::ConvexShape tri;
        sf::Transform rot;
        rot.rotate(rotation, origin);
        std::pair<sf::Vector2f, sf::Vector2f> conePoints = this->calculateConePoints();
        sf::Vector2f p1r = rot.transformPoint(conePoints.first);
        sf::Vector2f p2r = rot.transformPoint(conePoints.second);
        tri.setPointCount(3);
        tri.setPoint(0, origin);
        tri.setPoint(1, p1r);
        tri.setPoint(2, p2r);
        sf::Vector2f A = tri.getPoint(0);
        sf::Vector2f B = tri.getPoint(1);
        sf::Vector2f C = tri.getPoint(2);
        float areaABC = abs((A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y)) / 2.0f);
        float areaPBC = abs((point.x * (B.y - C.y) + B.x * (C.y - point.y) + C.x * (point.y - B.y)) / 2.0f);
        float areaPCA = abs((A.x * (point.y - C.y) + point.x * (C.y - A.y) + C.x * (A.y - point.y)) / 2.0f);
        float areaPAB = abs((A.x * (B.y - point.y) + B.x * (point.y - A.y) + point.x * (A.y - B.y)) / 2.0f);
        float totalArea = areaABC;
        float pointAreas = areaPBC + areaPCA + areaPAB;
        return abs(totalArea - pointAreas) < (viewDistance / 1000);
    }

    void FieldOfVision::drawFieldOfVision(sf::RenderWindow& window) {
        sf::VertexArray cone1(sf::Lines, 2);
        sf::VertexArray cone2(sf::Lines, 2);
        std::pair<sf::Vector2f, sf::Vector2f> cone_points = this->calculateConePoints();
        cone1[0].position = origin;
        cone2[0].position = origin;
        cone1[0].color = cone2[0].color = cone1[1].color = cone2[1].color = sf::Color::White;
        cone1[1].position = cone_points.first;
        cone2[1].position = cone_points.second;
        sf::Transform rot;
        rot.rotate(rotation, origin);
        cone1[1].position = rot.transformPoint(cone1[1].position);
        cone2[1].position = rot.transformPoint(cone2[1].position);
        window.draw(cone1);
        window.draw(cone2);
    }

    void FieldOfVision::drawFieldOfVisionArea(sf::RenderWindow& window) {
        sf::ConvexShape tri;
        sf::Transform rot;
        rot.rotate(rotation, origin);
        std::pair<sf::Vector2f, sf::Vector2f> cone_points = this->calculateConePoints();
        sf::Vector2f p1r = rot.transformPoint(cone_points.first);
        sf::Vector2f p2r = rot.transformPoint(cone_points.second);
        tri.setPointCount(3);
        tri.setPoint(0, origin);
        tri.setPoint(1, p1r);
        tri.setPoint(2, p2r);
        tri.setFillColor(sf::Color(255, 255, 255, 16));
        window.draw(tri);
    }

    float FieldOfVision::getViewDistance() const {
        return viewDistance;
    }

    void FieldOfVision::setViewDistance(float distance) {
        viewDistance = distance;
    }

    float FieldOfVision::getFov() const {
        return fov;
    }

    void FieldOfVision::setFov(float angle) {
        fov = angle;
    }

    float FieldOfVision::getRotation() const {
        return rotation;
    }

    void FieldOfVision::setRotation(float rotation) {
        this->rotation = rotation;
    }

    sf::Vector2f FieldOfVision::getOrigin() const {
        return origin;
    }

    void FieldOfVision::setOrigin(const sf::Vector2f& origin) {
        this->origin = origin;
    }
}