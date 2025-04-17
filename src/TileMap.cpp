#include "TileMap.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "Component.h"
#include<bits/stdc++.h>


TileMap::TileMap(GameObject& associated, std::string file, TileSet* tileSet) : 
    Component(associated), tileSet(tileSet) {
    Load(file);
}

void TileMap::Load(std::string file) {
    std::ifstream mapFile(file);
    if(!mapFile.is_open()) {
        std::cerr << "Erro ao abrir arquivo de mapa: " << file << std::endl;
        exit(1);
    }

    // Lê a primeira linha com as dimensões
    std::string line;
    std::getline(mapFile, line);
    
    // Remove vírgulas e converte para espaços
    std::replace(line.begin(), line.end(), ',', ' ');
    std::istringstream dimensions(line);
    dimensions >> mapWidth >> mapHeight >> mapDepth;

    // Limpa o vetor de tiles
    tileMatrix.clear();
    
    // Lê os tiles restantes
    int tile;
    char comma;
    while(mapFile >> tile) {
        tileMatrix.push_back(tile);
        // Consome a vírgula se existir
        if(mapFile.peek() == ',') {
            mapFile >> comma;
        }
    }

    // Verificação básica
    if(tileMatrix.size() != (unsigned)(mapWidth * mapHeight * mapDepth)) {
        std::cerr << "Erro: Número de tiles não corresponde às dimensões do mapa" << std::endl;
        std::cerr << "Esperado: " << mapWidth*mapHeight*mapDepth 
                 << ", Encontrado: " << tileMatrix.size() << std::endl;
        exit(1);
    }

    mapFile.close();
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet.reset(tileSet);
}

int& TileMap::At(int x, int y, int z) {
    int index = x + y*mapWidth + z*mapWidth*mapHeight;
    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer) {
    std::cout << "Renderizando camada " << layer << std::endl;

    for(int y = 0; y < mapHeight; y++) {
        for(int x = 0; x < mapWidth; x++) {
            int tileIndex = At(x, y, layer);
            if(tileIndex >= 0) { // -1 é tile vazio
                float posX = associated.box.x + x * tileSet->GetTileWidth();
                float posY = associated.box.y + y * tileSet->GetTileHeight();
                tileSet->RenderTile(tileIndex, posX, posY);
            }
        }
    }
}

void TileMap::Render() {
    for(int z = 0; z < mapDepth; z++) {
        RenderLayer(z);
    }
}

void TileMap::Update(float dt) {}

bool TileMap::Is(std::string type) {
    return type == "TileMap";
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}