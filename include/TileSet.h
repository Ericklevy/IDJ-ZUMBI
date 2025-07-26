#ifndef TILESET_H
#define TILESET_H

#include "Sprite.h"
#include <string>
#include <vector>
#include<bits/stdc++.h>


class TileSet {
private:
    Sprite tileSet;
    int tileWidth;
    int tileHeight;
    int columns;
    int rows;
    
public:
    TileSet(int tileWidth, int tileHeight, std::string file);
    
    void RenderTile(unsigned index, float x, float y);
    int GetTileWidth();
    int GetTileHeight();
};

#endif