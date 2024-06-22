#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>
#include <string>
#include <cstdio>
#include <allegro5/color.h>

#include "Engine/Point.hpp"

std::string floatToStr(float num);

Engine::Point pxToBlock(const Engine::Point& px);
Engine::Point blockToPx(const Engine::Point& block);
Engine::Point blockToMiddlePx(const Engine::Point& block);

std::string timeString(float sec);

double findAngle(Engine::Point center, Engine::Point point);

// 0: blue, 1: red, 2: bridge
int whichSide(Engine::Point pos);

#endif // HELPER_HPP