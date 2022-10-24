#include "world.hpp"

unsigned long World::GetSeed(){
    return this->seed;
}

World::World(unsigned long seed){
    this->SetSeed(seed);
}

void World::SetSeed(unsigned long seed){
    this->seed = seed;
}

std::vector<std::vector<float>> World::SampleChunkNoise(int xoffset, int zoffset){
    //2 dimensional vector
    std::vector<std::vector<float>> noisemap;
    // make noise object
    siv::PerlinNoise perlinnoise { this->seed };
    //scale and octaves as parameters
    for (int x = 0; x < this->chunksize; x++) {
        // fill vector with noise floats between 0 and 1
        noisemap.push_back(std::vector<float>{});
        for (int z = 0; z < this->chunksize; z++) {
            // sample noise at given position
            float noise = perlinnoise.octave2D_01(
                    ((xoffset * this->chunksize) + x) * this->scale,
                    ((zoffset * this->chunksize) + z) * this->scale,
                    this->octaves
                    );
            noisemap[x].push_back(noise);
        }
    }
    return noisemap;
}
