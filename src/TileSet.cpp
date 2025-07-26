#include "TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : 
    tileWidth(tileWidth), tileHeight(tileHeight) {
    
    tileSet.Open(file);
    if(!tileSet.IsOpen()) {
        std::cerr << "Erro ao carregar TileSet: " << file << std::endl;
        exit(1);
    }
    
    // Calcula número de colunas e linhas
    columns = tileSet.GetWidth() / tileWidth;
    rows = tileSet.GetHeight() / tileHeight;
    
    // Configura os frames do sprite
    tileSet.SetFrameCount(columns, rows);
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index < (unsigned)(columns * rows)) {
        tileSet.SetFrame(index);
        tileSet.Render(x, y);
    }
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}