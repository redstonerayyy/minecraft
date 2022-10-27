#include "world.hpp"
#include "primitives.hpp"
#include "utils.hpp"
#include "blocks.hpp"

#include <iostream>

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

void World::LoadChunks(int xstart, int xend, int zstart, int zend){
    for(int i = xstart; i < xend; ++i){
        for(int j = zstart; j < zend; ++j){
            if( this->IsChunkLoaded(i, j) ){
                std::cout << "StartLoadChunks\n";
                this->chunks.push_back(this->GetChunk(i, j));                
                std::cout << "EndLoadChunks\n";
            }
        }
    }

    std::cout << "Chunks: " << this->chunks.size() << "\n";
}

WorldMesh World::GetWorldMesh(){
    std::vector<Vertex> worldverts;
    std::vector<unsigned int> worldinds;
    int verticecount = 0;
    for(auto chunk : this->chunks){
        worldverts.insert(worldverts.end(), chunk.vertices.begin(), chunk.vertices.end());
        std::cout << "startinds\n";
        for(int indice : chunk.indices){
            worldinds.emplace_back(indice + verticecount);
        }
        std::cout << "endinds\n";
        // worldinds.insert(worldinds.end(), chunk.indices.begin(), chunk.indices.end());
        verticecount += chunk.vertices.size();
    }

    WorldMesh wmesh;
    wmesh.chunkcount = this->chunks.size();
    wmesh.vertices = worldverts;
    wmesh.indices = worldinds;
    std::cout << "Vertices: " << wmesh.vertices.size() << "\n";
    return wmesh;
}

Chunk World::GetChunk(int xoffset, int zoffset){
    Chunk newchunk;
    newchunk.xoffset = xoffset;
    newchunk.zoffset = zoffset;
    newchunk.blocks = std::vector<std::vector<std::vector<int>>>(16, std::vector<std::vector<int>>(256, std::vector<int>(16, 0)));
    
    std::vector<std::vector<float>> chunknoise = this->SampleChunkNoise(xoffset, zoffset);
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    //fill blocks
    for(int i = 0; i < this->chunksize; i++){ // x
		for(int j = 0; j < this->chunksize; j++){ // z
            float y = Utils::froundf(100.0f * chunknoise[i][j]);
            for(int k = 0; k < y; ++k){
                newchunk.blocks.at(i).at(k).at(j) = MC_STONE;
            }
        }
	}
    // std::cout << xoffset * this->chunksize << " :: " << zoffset * this->chunksize << "\n";
    for(int i = 0; i < this->chunksize; i++){ // x
		for(int j = 0; j < this->chunksize; j++){ // z
            for(int k = 0; k < this->chunkheight; ++k){
                if(newchunk.blocks.at(i).at(k).at(j) == MC_STONE){
                    //float y = Utils::froundf(100.0f * chunknoise[i][j]);
                    float transvec[3] = { i * 1.0f + xoffset * this->chunksize, float(k), j * 1.0f + zoffset * this->chunksize};
			        std::array<int, 6> cubesides = this->ChunkBlockSides(newchunk.blocks, i, k, j);
                    // int cubesides[6] = { 1, 1, 1, 1, 1, 1};
			        generateCube(vertices, indices, transvec, cubesides);
                };
            }
        }
	}

    newchunk.vertices = vertices;
    newchunk.indices = indices;

    return newchunk;
}

bool World::IsChunkLoaded(int xoffset, int zoffset){
    return std::all_of( this->chunks.cbegin(), this->chunks.cend(), [xoffset, zoffset](auto chunk){ return ! (chunk.xoffset == xoffset && chunk.zoffset == zoffset); } );
}

std::array<int, 6> World::ChunkBlockSides(std::vector<std::vector<std::vector<int>>> &blocks, int x, int y, int z){
    std::array<int, 6> sides;
    sides.fill(0);
    if(x - 1 >= 0){ // left
        if(blocks.at(x - 1).at(y).at(z) == MC_AIR){
            sides.at(0) = 1;
        }
    } else {// is at chunk edge
        sides[0] = 0;
    }
    if(y - 1 >= 0){ // bottom
        if(blocks.at(x).at(y - 1).at(z) == MC_AIR){
            sides[1] = 1;
        }
    } else {// is at chunk edge
        sides[1] = 1;
    }
    if(z - 1 >= 0){//front
        if(blocks.at(x).at(y).at(z - 1) == MC_AIR){
            sides[2] = 1;
        }
    } else {// is at chunk edge
        sides[2] = 0;
    }
    if(x + 1 < this->chunksize){ // right
        if(blocks.at(x + 1).at(y).at(z) == MC_AIR){
            sides[3] = 1;
        }
    } else { // is at chunk edge
        sides[3] = 0;
    }
    if(y + 1 < this->chunkheight){ // top
        if(blocks.at(x).at(y + 1).at(z) == MC_AIR){
            sides[4] = 1;
        }
    } else { // is at chunk edge
        sides[4] = 1;
    }
    if(z + 1 < this->chunksize){ //back
        if(blocks.at(x).at(y).at(z + 1) == MC_AIR){
            sides[5] = 1;
        }
    } else {
        sides[5] = 0;
    }
    return sides;
}