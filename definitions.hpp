#pragma once
//^(?([^\r\n])\s)*[^\s+?/]+[^\n]*$
//trust me bro
namespace seekpoint {
    #define DEBUG_PATH std::string("x64\\Release\\assets\\")
    #define NORMAL_PATH std::string("assets\\")
    #define DEBUG true
    #define PADDING 128
    #define WINDOW_WIDTH 256
    #define WINDOW_HEIGHT 256
    #define WINDOW_MULTIPLIER 3.0F
    #define FOV_ORIGIN sf::Vector2f(PADDING,WINDOW_HEIGHT/2)
    #define MAX_VIEW 1024.0F
}