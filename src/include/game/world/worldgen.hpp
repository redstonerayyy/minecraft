#pragma once

#include <iostream> // for loggin
#include "PerlinNoise.hpp" // header only library for perlin noise needed for noisemaps

//configure noisemap generation
std::vector<std::vector<float>> generateNoiseMap(int width, int depth, int octaves, long unsigned int heightmapseed);
