// Seekpoint.cpp 1/29/2024 - nyandisk :D
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <algorithm>
#include <random>

#include "spmath.h"
#include "definitions.hpp"
#include "seeker.h"
#include "target.h"

void drawCheckpoint(sf::RenderWindow& window, const sf::Vector2f& position, const float radius, bool& lfs, const seekpoint::FieldOfVision& fov) {
    sf::CircleShape teach = sf::CircleShape(radius);
    bool seen = fov.isInFieldOfVision(position);
    if (seen) {
        teach.setFillColor(sf::Color::Red);
        if (!lfs) {
            lfs = true;
            //Spotted
        }
    }
    else {
        teach.setFillColor(sf::Color::Cyan);
        if (lfs) {
            //Hidden
        }
        lfs = false;
    }
    teach.setOrigin(radius, radius);
    teach.setPosition(position);
    window.draw(teach);
}
float calculateEQ(const sf::Time& dt) {
    return 100 * (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 2.5F : 1) * dt.asSeconds();
}


void displayDebug(sf::RenderWindow& window, const sf::Font& font, const std::vector<std::string>& textValues, const sf::Vector2f& startingPosition) {
    const unsigned int fontSize = 16U;
    const float verticalSpacing = 18.0f;
    std::vector<sf::Text> debugTexts;
    sf::Vector2f currentPosition = startingPosition;
    for (const auto& text : textValues) {
        sf::Color debugTextColor = seekpoint::Math::numericalColorToColor(text.substr(0,9));
        std::string debugString = text.substr(9, text.length() - 9);
        sf::Text debugText(debugString, font, fontSize);
        debugText.setPosition(currentPosition);
        debugText.setFillColor(debugTextColor);
        debugTexts.push_back(debugText);

        currentPosition.y += verticalSpacing;
    }
    for (const auto& text : debugTexts) {
        window.draw(text);
    }
}
std::string getResource(const std::string& resourceName) {
    return (DEBUG ? DEBUG_PATH : NORMAL_PATH) + resourceName;
}
int main()
{
    bool lastframeR = false;
    bool currentframeR = false;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "class");
    window.setSize(sf::Vector2u(WINDOW_WIDTH*WINDOW_MULTIPLIER, WINDOW_HEIGHT*WINDOW_MULTIPLIER));
    sf::Font font;
    sf::View uiView = sf::View(sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(WINDOW_WIDTH * WINDOW_MULTIPLIER, WINDOW_HEIGHT * WINDOW_MULTIPLIER)));
    if (!font.loadFromFile(getResource("arial.ttf"))) {
        return EXIT_FAILURE;
    }
    sf::Time dt;
    sf::Clock deltaClock;
    sf::Clock elapsedTime;
    std::vector<seekpoint::Seeker> seekers;
    seekpoint::Target target1 = seekpoint::Target(
        seekers,
        sf::Vector2f(128.0F, 128.0F)
    );
    seekpoint::Seeker seeker1 = seekpoint::Seeker(
        target1,
        sf::Vector2f(128.0F,128.0F), // starting location
        180.0F, // starting rotation
        50.0F, // vision distance
        140.0F, // fov angle
        10.0F, // rotation speed
        1.0F // movement speed
        // color
        // size
        // render points
    );
    seekers.push_back(seeker1);

    
    bool lastFrameSpotted = false;

    float camSpeed = 69.420F;
    float zoomLevel = 1.0F;

    int startTimer = 100;
    
    int timer = startTimer;
    int fps = 0;
    sf::Vector2f cameraLocation = sf::Vector2f(0.0F,0.0F);
    sf::Vector2f checkpointPos = sf::Vector2f(0.0F,0.0F);
    auto desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(desktop.width / 2 - window.getSize().x / 2, desktop.height / 2 - window.getSize().y / 2));
    window.setFramerateLimit(165);
    while (window.isOpen()) {
        sf::View view = sf::View(sf::FloatRect(cameraLocation, sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)));
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                zoomLevel -= event.mouseWheelScroll.delta/10;
                zoomLevel = std::clamp(zoomLevel, 0.1F, 10000.0F);
            }
        }
        
        float mvspd = camSpeed * dt.asSeconds();
        if (window.hasFocus()) {
            currentframeR = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
            if (currentframeR && !lastframeR) {
                checkpointPos.x = seekpoint::Math::randomRange(-128, 256 + 128);
                checkpointPos.y = seekpoint::Math::randomRange(-128, 256 + 128);
            }
            lastframeR = currentframeR;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                mvspd *= 4;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                cameraLocation.x -= mvspd;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                cameraLocation.x += mvspd;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                cameraLocation.y -= mvspd;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                cameraLocation.y += mvspd;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                
                seeker1.setVisionDistance(seeker1.getVisionDistance() + calculateEQ(dt));
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                seeker1.setVisionDistance(seeker1.getVisionDistance() - calculateEQ(dt));
            }
            
        }
        view.zoom(zoomLevel);
        window.setView(view);
        window.clear();

        target1.update(window,dt);
        target1.render(window);
        seeker1.updateCurrentTarget(target1);
        seeker1.update(window,dt);
        seeker1.render(window);
        

        drawCheckpoint(window, checkpointPos, 4.0F, lastFrameSpotted, seeker1.getFieldOfVision());
        
        if (timer <= 0) {
            timer = startTimer;
            fps = (int)(1 / dt.asSeconds());
        }
        timer-=dt.asSeconds()/25;
        window.setView(sf::View(sf::FloatRect(cameraLocation, sf::Vector2f(WINDOW_WIDTH * WINDOW_MULTIPLIER, WINDOW_HEIGHT * WINDOW_MULTIPLIER))));
        std::vector<std::string> debugTextValues = {
            seekpoint::Math::numericalColorFormat(sf::Color::White) + "FPS: " + std::to_string(fps),
            seekpoint::Math::numericalColorFormat(sf::Color::Yellow) + "Vision distance: " + std::to_string((int)roundf(seekpoint::Math::unitsToMetric(seeker1.getVisionDistance()))) + "m",
            seekpoint::Math::numericalColorFormat(sf::Color::Green) + "Vision angle: " + std::to_string((int)roundf(seeker1.getFovAngle())) + "deg",
            seekpoint::Math::numericalColorFormat(sf::Color::Green) + "Seeker1 rotation: " + (seekpoint::Math::convertReducedRotationToString(seekpoint::Math::reduceLargeRotation((int)roundf(seeker1.getRotation())))) + "deg",
            seekpoint::Math::numericalColorFormat(sf::Color::Yellow) + "Distance from target: " + std::to_string((int)roundf(seekpoint::Math::unitsToMetric(seekpoint::Math::vectorDistance(seeker1.getLocation(), checkpointPos)))) + "m",
            seekpoint::Math::numericalColorFormat(sf::Color::Cyan) + "Seeker1 position: " + seekpoint::Math::displayVector(sf::Vector2i(seekpoint::Math::unitsToMetric(seeker1.getLocation()))),
            seekpoint::Math::numericalColorFormat(sf::Color::Cyan) + "Target position: " + seekpoint::Math::displayVector(sf::Vector2i(seekpoint::Math::unitsToMetric(checkpointPos)))
        };

        sf::Vector2f startingPosition(cameraLocation);

        displayDebug(window, font, debugTextValues, startingPosition);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            sf::Text text = sf::Text("SHIFT", font, 16U);
            text.setPosition(sf::Vector2f(cameraLocation.x, cameraLocation.y + (WINDOW_HEIGHT * WINDOW_MULTIPLIER) - 16));
            window.draw(text);
        }
        window.display();
        dt = deltaClock.restart();
    }
    return EXIT_SUCCESS;
}
