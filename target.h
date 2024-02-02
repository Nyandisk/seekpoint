#pragma once
#include <SFML/Graphics.hpp>
#include "seeker.h"
#include <vector>
namespace seekpoint{
	class Seeker;
	class Target {
	public:
		Target(
			const std::vector<Seeker>& activeSeekers,
			const sf::Vector2f& position,
			const sf::Color& seenColor = sf::Color::Red,
			const sf::Color& unseenColor = sf::Color::Cyan,
			const unsigned int targetSize = 4U,
			const unsigned int renderPoints = 12U
		);
		sf::Vector2f getLocation() const;
		sf::Color getColor() const;
		sf::Color getSeenColor() const;
		sf::Color getUnseenColor() const;
		unsigned int getSize() const;
		unsigned int getRenderPoints() const;
		void setLocation(const sf::Vector2f& v1);
		void setColor(const sf::Color& color);
		void setSeenColor(const sf::Color& color);
		void setUnseenColor(const sf::Color& color);
		void setSize(const unsigned int targetSize);
		void setRenderPoints(const unsigned int renderPoints);
		void update(sf::RenderWindow& window, const sf::Time& dt);
		void render(sf::RenderWindow& window);
		bool seenBy(const Seeker& seeker) const;
		void drawSeekerLine(const Seeker& seeker) const;
		Target& operator=(const Target& other);
	private:
		sf::Vector2f location;
		sf::Color targetColor;
		sf::Color seenColor;
		sf::Color unseenColor;
		const std::vector<Seeker>& activeSeekers;
		unsigned int targetSize;
		unsigned int targetRenderPoints;
	};
}