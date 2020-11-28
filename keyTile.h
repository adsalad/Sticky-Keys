//
// Created by jtorreal on 11/24/20.
//

#ifndef OOP_KEYTILE_H
#define OOP_KEYTILE_H
#include "olcPixelGameEngine.h"
#include "player.h"
#include "level.h"

class KeyTile{
private:
    int xPos;
    int yPos;
    char direction;
    int tileWidth;
    int tileHeight;
    bool clicked;
    bool placed;
    olc::Sprite *spriteEntity;

public:
    KeyTile();
    KeyTile(int xP, int yP, char direction);
    int getXPos();
    int getYPos();
    bool isClicked();
    bool isPlaced();
    void setIsClicked(bool val);
    void setIsPlaced(bool val);
    void processInput(float mouseX, float mouseY, Player* player, Level* currentLevel, float offsetX, float offsetY);
    void draw(olc::PixelGameEngine* pge);
};

#endif //OOP_KEYTILE_H
