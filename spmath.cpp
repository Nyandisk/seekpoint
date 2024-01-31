#include "spmath.h"
#include <random>
#include <iomanip>
#include <sstream>

namespace seekpoint {
    float Math::unitsToMetric(const float units) {
        return units / 10;
    }

    float Math::metricToUnits(const float meters) {
        return meters * 10;
    }

    sf::Vector2f Math::unitsToMetric(const sf::Vector2f units) {
        return sf::Vector2f(units.x / 10, units.y / 10);
    }

    sf::Vector2f Math::metricToUnits(const sf::Vector2f meters) {
        return sf::Vector2f(meters.x * 10, meters.y * 10);
    }

    float Math::vectorDistance(const sf::Vector2f& v1, const sf::Vector2f& v2) {
        float dx = v1.x - v2.x;
        float dy = v1.y - v2.y;
        return std::sqrt(dx * dx + dy * dy);
    }

    std::string Math::displayVector(const sf::Vector2f& v1) {
        return std::string("x=" + std::to_string(v1.x) + " ; y=" + std::to_string(v1.y));
    }

    std::string Math::displayVector(const sf::Vector2i& v1) {
        return std::string("x=" + std::to_string(v1.x) + " ; y=" + std::to_string(v1.y));
    }

    template<typename T>
    sf::Vector2<T> Math::normalize(const sf::Vector2<T>& vector) {
        T length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
        if (length != 0) {
            return sf::Vector2<T>(vector.x / length, vector.y / length);
        }
        else {
            return sf::Vector2<T>(0, 0);
        }
    }

    float Math::rotateTowards(const sf::Vector2f& subject, const sf::Vector2f& target) {
        float dx = target.x - subject.x;
        float dy = target.y - subject.y;
        return atan2(dy, dx) * 180 / Math::PI + 180.0F;
    }

    float Math::shortestAngle(float start, float end) {
        float difference = std::fmod(end - start + 360.0f, 360.0f);
        return difference < 180.0f ? difference : difference - 360.0f;
    }

    float Math::lerp(const float a, const float b, const float t) {
        return a + shortestAngle(a, b) * t;
    }

    sf::Vector2f Math::calculateDirection(const sf::Vector2f& source, const sf::Vector2f& target) {
        sf::Vector2f direction = target - source;
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0) {
            direction /= length;
        }
        return direction;
    }

    bool Math::inRange(const float x, const float a, const float b) {
        return x <= b && x >= a;
    }

    float Math::lineSlope(const sf::VertexArray& line) {
        sf::Vector2f p1 = line[0].position;
        sf::Vector2f p2 = line[1].position;
        return (p2.y - p1.y) / (p2.x - p1.x);
    }

    int Math::randomRange(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(gen);
    }

    std::pair<unsigned int, unsigned int> Math::reduceLargeRotation(const int rotation) {
        const unsigned int absRotation = std::abs(rotation);
        const auto divResult = std::div(absRotation, 360);
        const unsigned int revolutions = divResult.quot;
        const unsigned int remainder = divResult.rem;
        return std::make_pair(revolutions, remainder);
    }

    std::string Math::convertReducedRotationToString(const std::pair<unsigned int, unsigned int>& reducedRotation) {
        return std::string((reducedRotation.first != 0 ? ("360*" + std::to_string(reducedRotation.first) + " + ") : "") + std::to_string(reducedRotation.second));
    }

    std::string Math::getColorDigitFormat(const unsigned int value) {
        std::stringstream ss;
        ss << std::setw(3) << std::setfill('0') << value;
        return ss.str();
    }

    std::string Math::numericalColorFormat(const sf::Color& col) {
        return getColorDigitFormat(col.r) + getColorDigitFormat(col.g) + getColorDigitFormat(col.b);
    }

    sf::Color Math::numericalColorToColor(const std::string& str) {
        int r = atoi(str.substr(0, 3).c_str());
        int g = atoi(str.substr(3, 3).c_str());
        int b = atoi(str.substr(6, 3).c_str());
        return sf::Color(r, g, b);
    }
}