//
// Created by jtorreal on 11/24/20.
//

#ifndef OOP_PLAYER_H
#define OOP_PLAYER_H
#include "olcPixelGameEngine.h"
#include "level.h"

class Player{
private:
    float xPos;
    float yPos;
    float xVelocity;
    float yVelocity;
    bool canMoveLeft;
    bool canMoveRight;
    bool canJump;
    olc::Sprite *playerSprite;

public:
    Player();
    Player(float xP, float yP, float xV, float yV);
    float getXPos();
    float getYPos();
    float getXVel();
    float getYVel();
    void setXPos(float xPos);
    void setYPos(float yPos);
    void setXVel(float xVel);
    void setYVel(float yVel);
    void setMoveLeft(bool val);
    void setMoveRight(bool val);
    void setCanJump(bool val);
    void processInput(olc::PixelGameEngine* pge, Level* currentLevel, float fElapsedTime);
    void draw(Level* currentLevel, olc::PixelGameEngine* pge);
};


#endif //OOP_PLAYER_H
