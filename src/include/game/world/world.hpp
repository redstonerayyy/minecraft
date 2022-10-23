#pragma once

// https://github.com/Reputeless/PerlinNoise
#include "PerlinNoise.hpp"

#include <vector>

class World {
public:

    unsigned long GetSeed();

    World(unsigned long seed);

private:
    unsigned long seed;
    unsigned int chunksize = 16;
    float scale = 0.01f;
    unsigned int octaves = 4;
    siv::PerlinNoise::seed_type perlinnoiseseed;
    siv::PerlinNoise perlinnoise;

    void SetSeed(unsigned long seed);
    std::vector<std::vector<float>> SampleChunkNoise(int xoffset, int zoffset);
};