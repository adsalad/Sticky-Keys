//
// Created by jtorreal on 11/24/20.
//

#include "keyTile.h"

KeyTile::KeyTile(int xP, int yP, char dir){
    xPos = xP;
    yPos = yP;
    tileWidth = 16;
    tileHeight = 16;
    direction = dir;
    clicked = false;
    placed = false;
}
KeyTile::KeyTile(){}
int KeyTile::getXPos() {return xPos;}
int KeyTile::getYPos() {return yPos;}
bool KeyTile::isClicked() {return clicked;}
bool KeyTile::isPlaced() {return placed;}
void KeyTile::setIsClicked(bool val) {clicked = val;}
void KeyTile::setIsPlaced(bool val) {placed = val;}
void KeyTile::processInput(float mouseClickX, float mouseClickY, Player* player, Level* currentLevel, float offsetX, float offsetY){
    //Update isPlaced and isClicked based on mouseClicked position
    if(mouseClickX >= xPos && mouseClickX <= xPos + tileWidth && mouseClickY >= yPos && mouseClickY <= yPos+tileHeight && !clicked){
        clicked = true;
    }
    else{
        if(clicked){
            if (currentLevel->getTile((int) ((mouseClickX)/tileWidth + offsetX), (int) ((mouseClickY)/tileHeight) + offsetY) == '.') {
                currentLevel->setTile((int) ((mouseClickX)/tileWidth + offsetX), (int) ((mouseClickY)/tileHeight) + offsetY, direction);
                placed = true;
                switch(direction){
                    case 'l':
                        player->setXVel(0.0f);
                        player->setMoveLeft(false);
                        break;
                    case 'r':
                        player->setXVel(0.0f);
                        player->setMoveRight(false);
                        break;
                    case 'j':
                        player->setCanJump(false);
                        break;
                }
            }
        }
        clicked = false;
    }
}
void KeyTile::draw(olc::PixelGameEngine* pge){
    //Check isPlaced and isClicked to determine where to draw
    if(!placed && !clicked && direction == 'l'){
        pge->FillRect(xPos, yPos, tileWidth, tileHeight, olc::MAGENTA);
    }
    if(!placed && clicked && direction == 'l'){
        pge->FillRect(xPos, yPos, tileWidth, tileHeight, olc::DARK_MAGENTA);
    }
    if(!placed && !clicked && direction == 'r'){
        pge->FillRect(xPos, yPos, tileWidth, tileHeight, olc::BLUE);
    }
    if(!placed && clicked && direction == 'r'){
        pge->FillRect(xPos, yPos, tileWidth, tileHeight, olc::DARK_BLUE);
    }
    if(!placed && !clicked && direction == 'j'){
        pge->FillRect(xPos, yPos, tileWidth, tileHeight, olc::CYAN);
    }
    if(!placed && clicked && direction == 'j'){
        pge->FillRect(xPos, yPos, tileWidth, tileHeight, olc::DARK_CYAN);
    }
}