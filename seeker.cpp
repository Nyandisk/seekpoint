#include "seeker.h"
#include "spmath.h"
#include "definitions.hpp"
#include <cmath>

namespace seekpoint {
    Seeker::Seeker(const Target& target, const sf::Vector2f& location, float rotation, float visionDistance, float fovAngle, float rotationSpeed, float movementSpeed, bool seeksMouse, const sf::Color seekerColor, unsigned int seekerSize, unsigned int renderPoints)
        : location(location), target(const_cast<Target&>(target)), teachRot(rotation), seekerSize(seekerSize), seekerColor(seekerColor), teachVision(visionDistance), teachMoveSpeed(movementSpeed), seeksMouse(seeksMouse), teachFovAngle(fovAngle), teachRotationSpeed(rotationSpeed), teachRenderPoints(renderPoints), fov(FieldOfVision(visionDistance, fovAngle, rotation, location)), reachedLastFrame(false) {}

    void Seeker::update(sf::RenderWindow& window, const sf::Time& dt) {
        if (this->seeksMouse) {
            this->rotateTowardsMouse(window, dt);
        }
        else {
            this->rotateTowardsTarget(window, dt, this->target.getLocation());
        }
        this->updateFov();
        sf::Vector2f movement = this->moveTowards(this->target.getLocation());
        constexpr float threshold = 1.0f;
        if (seekpoint::Math::vectorDistance(this->getLocation(), this->target.getLocation()) <= threshold) {
            this->setLocation(this->target.getLocation());
            if (!reachedLastFrame) {
                reachedLastFrame = true;
            }
        }
        else {
            this->setLocation(this->getLocation() + movement);
            if (reachedLastFrame) {
                reachedLastFrame = false;
            }
        }
    }

    void Seeker::render(sf::RenderWindow& window) {
        this->fov.drawFieldOfVision(window);
        this->fov.drawFieldOfVisionArea(window);
        sf::CircleShape teach = sf::CircleShape(this->seekerSize);
        teach.setPointCount(this->teachRenderPoints);
        teach.setFillColor(this->seekerColor);
        teach.setOrigin(this->seekerSize, this->seekerSize);
        teach.setPosition(this->location);
        teach.setRotation(this->teachRot);
        window.draw(teach);
    }

    void Seeker::updateFov() {
        this->fov.setFov(this->teachFovAngle);
        this->fov.setRotation(this->teachRot);
        this->fov.setViewDistance(this->teachVision);
        this->fov.setOrigin(this->location);
    }

    bool Seeker::canSee(const sf::Vector2f& position) const{
        return this->getFieldOfVision().isInFieldOfVision(position);
    }

    seekpoint::FieldOfVision Seeker::getFieldOfVision() const{
        return this->fov;
    }

    float Seeker::getRotation()  const {
        return this->teachRot;
    }

    float Seeker::getVisionDistance()  const {
        return this->teachVision;
    }

    float Seeker::getFovAngle()  const {
        return this->teachFovAngle;
    }

    float Seeker::getRotationSpeed()  const {
        return this->teachRotationSpeed;
    }

    sf::Color Seeker::getSeekerColor()  const {
        return this->seekerColor;
    }

    unsigned int Seeker::getSeekerSize()  const {
        return this->seekerSize;
    }

    unsigned int Seeker::getRenderPoints()  const {
        return this->teachRenderPoints;
    }

    float Seeker::getSeekerSpeed()  const {
        return this->teachMoveSpeed;
    }

    sf::Vector2f Seeker::getLocation()  const {
        return this->location;
    }

    Target& Seeker::getCurrentTarget()  const {
        return this->target;
    }

    void Seeker::updateCurrentTarget(Target& newTarget) {
        this->target = newTarget;
    }

    void Seeker::setRotation(const float rotation) {
        this->teachRot = rotation;
    }

    void Seeker::setVisionDistance(const float visionDistance) {
        this->teachVision = std::clamp(visionDistance, 0.01F, MAX_VIEW);
    }

    void Seeker::setFovAngle(const float fovAngle) {
        this->teachFovAngle = fovAngle;
    }

    void Seeker::setRotationSpeed(const float rotationSpeed) {
        this->teachRotationSpeed = rotationSpeed;
    }

    void Seeker::setSeekerSpeed(const float speed) {
        this->teachMoveSpeed = speed;
    }

    void Seeker::setSeekerColor(const sf::Color& seekerColor) {
        this->seekerColor = seekerColor;
    }

    void Seeker::setSeekerSize(const unsigned int seekerSize) {
        this->seekerSize = seekerSize;
    }

    void Seeker::setRenderPoints(const unsigned int renderPoints) {
        this->teachRenderPoints = renderPoints;
    }

    void Seeker::setLocation(const sf::Vector2f& location) {
        this->location = location;
    }

    void Seeker::rotateTowardsMouse(sf::RenderWindow& window, const sf::Time& dt) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(mousePosition);
        float target_angle = Math::rotateTowards(this->location, worldMousePosition);
        this->teachRot = Math::lerp(this->teachRot, target_angle, this->teachRotationSpeed * dt.asSeconds());
    }

    void Seeker::rotateTowardsTarget(sf::RenderWindow& window, const sf::Time& dt, const sf::Vector2f& target) {
        float target_angle = Math::rotateTowards(this->location, target);
        this->teachRot = Math::lerp(this->teachRot, target_angle, this->teachRotationSpeed * dt.asSeconds());
    }

    sf::Vector2f Seeker::moveTowards(const sf::Vector2f& point) {
        sf::Vector2f direction = Math::calculateDirection(this->location, point);
        return direction * this->getSeekerSpeed();
    }
}