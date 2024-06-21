#ifndef HELPER_HPP
#define HELPER_HPP

#include <iostream>
#include <cstdio>
#include "Engine/Point.hpp"

#include "Engine/Point.hpp"

std::string floatToStr(float num);
double findAngle(Engine::Point center, Engine::Point point);

Engine::Point pxToBlock(const Engine::Point& px);
Engine::Point blockToPx(const Engine::Point& block);

#endif // HELPER_HPP