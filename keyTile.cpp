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
    olc::Sprite *rightTile;
    olc::Sprite *leftTile;
    olc::Sprite *upTile;
    olc::Sprite *rightClicked;
    olc::Sprite *leftClicked;
    olc::Sprite *upClicked;
    rightTile = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/right.png");
    leftTile = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/left.png");
    upTile = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/up.png");
    rightClicked = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/rightClicked.png");
    leftClicked = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/leftClicked.png");
    upClicked = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/upClicked.png");

    //Check isPlaced and isClicked to determine where to draw
    if(!placed && !clicked && direction == 'l'){
        pge->DrawSprite(xPos, yPos, leftTile);
    }
    if(!placed && clicked && direction == 'l'){
        pge->DrawSprite(xPos, yPos, leftClicked);
    }
    if(!placed && !clicked && direction == 'r'){
        pge->DrawSprite(xPos, yPos, rightTile);
    }
    if(!placed && clicked && direction == 'r'){
        pge->DrawSprite(xPos, yPos, rightClicked);
    }
    if(!placed && !clicked && direction == 'j'){
        pge->DrawSprite(xPos, yPos, upTile);
    }
    if(!placed && clicked && direction == 'j'){
        pge->DrawSprite(xPos, yPos, upClicked);
    }
}