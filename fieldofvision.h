#pragma once

#include <SFML/Graphics.hpp>
namespace seekpoint {
    class FieldOfVision {
    public:
        FieldOfVision(float viewDistance, float fov, float rotation, const sf::Vector2f& origin);

        std::pair<sf::Vector2f, sf::Vector2f> calculateConePoints() const;

        bool isInFieldOfVision(const sf::Vector2f& point) const;

        void drawFieldOfVision(sf::RenderWindow& window);

        void drawFieldOfVisionArea(sf::RenderWindow& window);

        float getViewDistance() const;
        void setViewDistance(float distance);

        float getFov() const;
        void setFov(float angle);

        float getRotation() const;
        void setRotation(float rotation);

        sf::Vector2f getOrigin() const;
        void setOrigin(const sf::Vector2f& origin);

    private:
        float viewDistance;
        float fov;
        float rotation;
        sf::Vector2f origin;
    };
}