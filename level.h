//
// Created by jtorreal on 11/24/20.
//

#ifndef OOP_LEVEL_H
#define OOP_LEVEL_H
#include "olcPixelGameEngine.h"

class Level{
    private:
            int levelWidth;
            int levelHeight;
            int tileWidth;
            int tileHeight;
            bool fixTiles;
            float offsetX;
            float offsetY;
            std::string levelMap;
            std::string fileName;
            olc::Sprite *groundSprite;
            olc::Sprite *coinSprite;

    public:
            Level();
            Level(int lW, int lH, int tW, int tH, std::string fName);
            int getLevelWidth();
            int getLevelHeight();
            int getTileWidth();
            int getTileHeight();
            float getOffsetX();
            float getOffsetY();
            std::string getLevelMap();
            char getTile(int x, int y);
            void setTile(int x, int y, char c);
            void draw(float camX, float camY, olc::PixelGameEngine* pge);
            void setFixTiles(bool fix);
            bool getFixTiles();
};

#endif //OOP_LEVEL_H
