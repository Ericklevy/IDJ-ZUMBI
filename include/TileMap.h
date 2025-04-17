#ifndef TILEMAP_H
#define TILEMAP_H

#include "Component.h"
#include "TileSet.h"
#include <vector>
#include <memory>
#include<bits/stdc++.h>

class TileMap : public Component {
private:
    std::vector<int> tileMatrix;
    std::unique_ptr<TileSet> tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;
    
    void Load(std::string file);
    
    
public:
    TileMap(GameObject& associated, std::string file, TileSet* tileSet);
    
    void SetTileSet(TileSet* tileSet);
    int& At(int x, int y, int z = 0);
    void RenderLayer(int layer);
    void Render() override;
    void Update(float dt) override;
    bool Is(std::string type) override;
    
    int GetWidth();
    int GetHeight();
    int GetDepth();
};

#endif