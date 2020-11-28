//
// Created by jtorreal on 11/24/20.
//
#include "level.h"
#include <iostream>
#include <fstream>
#include "olcPixelGameEngine.h"

Level::Level(int lW, int lH, int tW, int tH, std::string fName) {
    levelWidth = lW;
    levelHeight = lH;
    tileWidth = tW;
    tileHeight = tH;
    /*std::ifstream file;
    std::string line;
    file.open(fName);
    while(std::getline(file, line)){
        levelMap += line;
    }*/

    levelMap += "................................................................";
    levelMap += "................................................................";
    levelMap += "................................................................";
    levelMap += ".......#####....................................................";
    levelMap += "........###..............ooo....................................";
    levelMap += ".......................########.................................";
    levelMap += ".....##########.......###..............#.#......................";
    levelMap += "....................###................#.#......................";
    levelMap += "...................####.........................................";
    levelMap += "####################################.##############.....########";
    levelMap += "...................................#.#...............###........";
    levelMap += "........................############.#............###...........";
    levelMap += "........................#............#.........###..............";
    levelMap += "........................#.############.....####.................";
    levelMap += "........................#................##.....................";
    levelMap += "........................#################.......................";

    groundSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys2.0/Images/tut_tiles.png");
    coinSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys2.0/Images/coin.png");
    fixTiles = false;
}
Level::Level(){}
int Level::getLevelWidth() {return levelWidth;}
int Level::getLevelHeight() {return levelHeight;}
int Level::getTileWidth() {return tileWidth;}
int Level::getTileHeight() {return tileHeight;}
std::string Level::getLevelMap() {return levelMap;}
bool Level::getFixTiles() {return fixTiles;}
void Level::setFixTiles(bool fix) {fixTiles = fix;}
float Level::getOffsetX() {return offsetX;}
float Level::getOffsetY() {return offsetY;}

char Level::getTile(int x, int y) {
    if (x >= 0 && x < levelWidth && y >= 0 && y < levelHeight)
    return levelMap[y * levelWidth + x];
    else
    return ' ';
}

void Level::setTile(int x, int y, char c) {
    if (x >= 0 && x < levelWidth && y >= 0 && y < levelHeight)
        levelMap[y * levelWidth + x] = c;
}
void Level::draw(float cameraX, float cameraY, olc::PixelGameEngine* pge) {
    //Draw Level
    int nVisibleTilesX = pge->ScreenWidth() / tileWidth;
    int nVisibleTilesY = pge->ScreenHeight() / tileHeight;

    //Calculate Topleft tile
    offsetX = cameraX - (float) nVisibleTilesX / 2.0f;
    offsetY = cameraY - (float) nVisibleTilesY / 2.0f;

    //Prevent Camera from going outside of game limits
    if(offsetX < 0) offsetX = 0;
    if(offsetY < 0) offsetY = 0;
    if(offsetX > levelWidth - nVisibleTilesX) offsetX = levelWidth - nVisibleTilesX;
    if(offsetY > levelHeight - nVisibleTilesY) offsetY = levelHeight - nVisibleTilesY;

    //Offsets for smoother movement
    float tileOffsetX = (offsetX - (int)offsetX) * tileWidth;
    float tileOffsetY = (offsetY - (int) offsetY) * tileHeight;

    //Draw actual tile map
    if(fixTiles){
        for (int i; i<levelMap.length();i++){
            if(levelMap[i]=='l' || levelMap[i]=='r' || levelMap[i]=='j') {
                levelMap[i] = '.';
            }
        }
        fixTiles = false;
    }



    for(int i = -1; i < nVisibleTilesX+1; i++){
        for (int j = -1; j < nVisibleTilesY+1; j++){
            char tileID = getTile(i + offsetX, j + offsetY);

            switch (tileID)
            {
                case '.':
                    pge->FillRect(i * tileWidth-tileOffsetX, j * tileHeight-tileOffsetY, tileWidth, tileHeight, olc::BLACK);
                    break;
                case '#':
                    //FillRect(i * nTileWidth-tileOffsetX, j * nTileHeight-tileOffsetY, nTileWidth, nTileHeight, olc::RED);
                    pge->DrawPartialSprite(i * tileWidth - tileOffsetX, j * tileHeight - tileOffsetY, groundSprite, 0 * tileWidth, 0 * tileHeight, 2*tileWidth, 2*tileHeight);
                    break;
                case 'l':
                    pge->FillRect(i * tileWidth-tileOffsetX, j * tileHeight-tileOffsetY, tileWidth, tileHeight, olc::MAGENTA);
                    break;
                case 'r':
                    pge->FillRect(i * tileWidth-tileOffsetX, j * tileHeight-tileOffsetY, tileWidth, tileHeight, olc::BLUE);
                    break;
                case 'j':
                    pge->FillRect(i * tileWidth-tileOffsetX, j * tileHeight-tileOffsetY, tileWidth, tileHeight, olc::CYAN);
                    break;
                case 'o':
                    pge->DrawPartialSprite(i * tileWidth - tileOffsetX, j * tileHeight - tileOffsetY, coinSprite, 0 * tileWidth, 0 * tileHeight, 2*tileWidth, 2*tileHeight);
                    //DrawSprite(i*nTileWidth-tileOffsetX, j*nTileHeight-tileOffsetY, spriteCoin, 1, olc::Sprite::NONE);
                    //pge->FillRect( i * tileWidth-tileOffsetX, j * tileHeight - tileOffsetY, tileWidth, tileHeight, olc::YELLOW);
                    break;
                default:
                    break;
            }
        }
    }
}