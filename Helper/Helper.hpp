#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>
#include <cstdio>
#include <allegro5/color.h>

#include "Engine/Point.hpp"

std::string floatToStr(float num);

Engine::Point pxToBlock(const Engine::Point& px);
Engine::Point blockToPx(const Engine::Point& block);

double findAngle(Engine::Point center, Engine::Point point);

#endif // HELPER_HPP