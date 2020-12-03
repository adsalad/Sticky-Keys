//
// Created by jtorreal on 11/24/20.
//
#include "level.h"
#include <iostream>
#include <fstream>

Level::Level(int lW, int lH, int tW, int tH, std::string fName) {
    levelWidth = lW;
    levelHeight = lH;
    tileWidth = tW;
    tileHeight = tH;
    std::ifstream file;
    std::string line;
    file.open(fName);
    while(std::getline(file, line)){
        levelMap += line;
    }

    groundSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/stone.png");
    checkpointSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/checkpoint.png");
    checkpointPassedSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/passed.png");
    finishSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/finish.png");
    fireSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/fire.png");
    rightPlacedSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/rightPlaced.png");
    leftPlacedSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/leftPlaced.png");
    upPlacedSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/upPlaced.png");
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
                    pge->DrawSprite(i*tileWidth-tileOffsetX, j*tileHeight-tileOffsetY, groundSprite);
                    break;
                case 'l':
                    pge->DrawSprite(i*tileWidth-tileOffsetX, j*tileHeight-tileOffsetY, leftPlacedSprite);
                    break;
                case 'r':
                    pge->DrawSprite(i*tileWidth-tileOffsetX, j*tileHeight-tileOffsetY, rightPlacedSprite);
                    break;
                case 'j':
                    pge->DrawSprite(i*tileWidth-tileOffsetX, j*tileHeight-tileOffsetY, upPlacedSprite);
                    break;
                case 'f':
                    pge->DrawSprite(i*tileWidth-tileOffsetX, j*tileHeight-tileOffsetY, checkpointSprite);
                    break;
                case 'F':
                    pge->DrawSprite(i*tileWidth-tileOffsetX, j*tileHeight-tileOffsetY, checkpointPassedSprite);
                    break;
                case 'd':
                    pge->DrawSprite(i*tileWidth-tileOffsetX, j*tileHeight-tileOffsetY, fireSprite);
                    break;
                case 'g':
                    pge->DrawSprite(i*tileWidth-tileOffsetX, j*tileHeight-tileOffsetY, finishSprite);
                    break;
                default:
                    break;
            }
        }
    }
}