#include "target.h"
namespace seekpoint {
	Target::Target(const std::vector<Seeker>& activeSeekers, const sf::Vector2f& position,const sf::Color& unseenColor, const sf::Color& seenColor, const unsigned int targetSize, const unsigned int renderPoints)
		: activeSeekers(activeSeekers), location(position), targetColor(unseenColor), unseenColor(unseenColor), targetSize(targetSize), seenColor(seenColor), targetRenderPoints(renderPoints) {}
	void Target::update(sf::RenderWindow& window, const sf::Time& dt) {

	}
	void Target::render(sf::RenderWindow& window) {
		sf::CircleShape targetShape = sf::CircleShape(this->targetSize);
		for (const Seeker& seeker : this->activeSeekers) {
			if (this->seenBy(seeker)) {
				this->drawSeekerLine(seeker);
				this->setColor(this->seenColor);
			}
			else {
				this->setColor(this->unseenColor);
			}
		}
		targetShape.setPointCount(this->targetRenderPoints);
		targetShape.setFillColor(this->getColor());
		targetShape.setOrigin(this->targetSize, this->targetSize);
		targetShape.setPosition(this->location);
		window.draw(targetShape);
	}
	void Target::drawSeekerLine(const Seeker& seeker) const {
		sf::VertexArray seekerLine(sf::Lines, 2);
		seekerLine[0].position = this->location;
		seekerLine[1].position = seeker.getLocation();
		seekerLine[0].color = seekerLine[1].color = this->seenColor;
	}
	sf::Vector2f Target::getLocation() const {
		return this->location;
	}
	sf::Color Target::getColor() const {
		return this->targetColor;
	}
	sf::Color Target::getSeenColor() const {
		return this->seenColor;
	}
	sf::Color Target::getUnseenColor() const {
		return this->unseenColor;
	}
	unsigned int Target::getSize() const {
		return this->targetSize;
	}
	unsigned int Target::getRenderPoints() const {
		return this->targetRenderPoints;
	}
	void Target::setLocation(const sf::Vector2f& v1){
		this->location = v1;
	}
	void Target::setColor(const sf::Color& color){
		this->targetColor = color;
	}
	void Target::setSeenColor(const sf::Color& color) {
		this->seenColor = color;
	}
	void Target::setUnseenColor(const sf::Color& color) {
		this->unseenColor = color;
	}
	void Target::setSize(const unsigned int targetSize){
		this->targetSize = targetSize;
	}
	void Target::setRenderPoints(const unsigned int renderPoints){
		this->targetRenderPoints = renderPoints;
	}
	bool Target::seenBy(const Seeker& seeker) const{
		return seeker.canSee(this->getLocation());
	}
	Target& Target::operator=(const Target& other) {
		if (this != &other) {
			this->location = other.location;
			this->targetColor = other.targetColor;
			this->unseenColor = other.unseenColor;
			this->seenColor = other.seenColor;
			this->targetSize = other.targetSize;
			this->targetRenderPoints = other.targetRenderPoints;
		}
		return *this;
	}
}