#pragma once

#include <iostream>
#include "PerlinNoise.hpp"

std::vector<float> generateNoiseMap(int width, int depth, int octaves, long unsigned int heightmapseed);
