#pragma once
#include <SFML/Graphics.hpp>
#include "FieldOfVision.h"
namespace seekpoint {
    class Seeker {
    public:
        Seeker(const sf::Vector2f& target, const sf::Vector2f& location, float rotation, float visionDistance, float fovAngle, float rotationSpeed, float movementSpeed, bool seeksMouse = false, const sf::Color seekerColor = sf::Color::Green, unsigned int seekerSize = 8, unsigned int renderPoints = 12);

        void update(sf::RenderWindow& window, const sf::Time& dt);
        void render(sf::RenderWindow& window);
        bool canSee(const sf::Vector2f& position);
        FieldOfVision getFieldOfVision();
        float getRotation();
        float getVisionDistance();
        float getFovAngle();
        float getRotationSpeed();
        sf::Color getSeekerColor();
        unsigned int getSeekerSize();
        unsigned int getRenderPoints();
        float getSeekerSpeed();
        sf::Vector2f getLocation();
        sf::Vector2f getCurrentTarget();
        void updateCurrentTarget(const sf::Vector2f& newTarget);
        void setRotation(const float rotation);
        void setVisionDistance(const float visionDistance);
        void setFovAngle(const float fovAngle);
        void setRotationSpeed(const float rotationSpeed);
        void setSeekerSpeed(const float speed);
        void setSeekerColor(const sf::Color& seekerColor);
        void setSeekerSize(const unsigned int seekerSize);
        void setRenderPoints(const unsigned int renderPoints);
        void setLocation(const sf::Vector2f& location);

    private:
        void rotateTowardsMouse(sf::RenderWindow& window, const sf::Time& dt);
        void rotateTowardsTarget(sf::RenderWindow& window, const sf::Time& dt, const sf::Vector2f& target);
        sf::Vector2f moveTowards(const sf::Vector2f& point);
        void updateFov();

        sf::Vector2f location;
        sf::Vector2f target;
        FieldOfVision fov;
        float teachRot;
        float teachVision;
        float teachFovAngle;
        float teachRotationSpeed;
        float teachMoveSpeed;
        bool seeksMouse;
        sf::Color seekerColor;
        unsigned int seekerSize;
        unsigned int teachRenderPoints;
        bool reachedLastFrame;
    };
}