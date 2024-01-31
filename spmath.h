#pragma once
#include <SFML/Graphics.hpp>

namespace seekpoint {
    class Math
    {
    public:
        static constexpr float PI = 3.14159265358979323846F;
        static float unitsToMetric(const float units);
        static float metricToUnits(const float meters);
        static sf::Vector2f unitsToMetric(const sf::Vector2f units);
        static sf::Vector2f metricToUnits(const sf::Vector2f meters);
        static float vectorDistance(const sf::Vector2f& v1, const sf::Vector2f& v2);
        static std::string displayVector(const sf::Vector2f& v1);
        static std::string displayVector(const sf::Vector2i& v1);
        template<typename T>
        static sf::Vector2<T> normalize(const sf::Vector2<T>& vector);
        static float rotateTowards(const sf::Vector2f& subject, const sf::Vector2f& target);
        static float shortestAngle(float start, float end);
        static float lerp(const float a, const float b, const float t);
        static sf::Vector2f calculateDirection(const sf::Vector2f& source, const sf::Vector2f& target);
        static bool inRange(const float x, const float a, const float b);
        static float lineSlope(const sf::VertexArray& line);
        static int randomRange(int min, int max);
        static std::pair<unsigned int, unsigned int> reduceLargeRotation(const int rotation);
        static std::string convertReducedRotationToString(const std::pair<unsigned int, unsigned int>& reducedRotation);
        static std::string getColorDigitFormat(const unsigned int value);
        static std::string numericalColorFormat(const sf::Color& col);
        static sf::Color numericalColorToColor(const std::string& str);
    };
}