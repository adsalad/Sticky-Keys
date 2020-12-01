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
    float checkpointX;
    float checkpointY;
    bool canMoveLeft;
    bool canMoveRight;
    bool canJump;
    bool onGround;
    bool isDead;
    bool facingRight;
    bool flagPassed;
    bool atGoal;
    olc::Sprite *playerSprite;
    olc::Sprite *playerMoveRight;
    olc::Sprite *playerMoveLeft;
    olc::Sprite *playerJumpRight;
    olc::Sprite *playerJumpLeft;

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
    void setFlag(bool val);
    bool getFlag();
    bool getDeathStatus();
    bool isAtGoal();
    void setDeathStatus(bool val);
    void death();
    void win();
};


#endif //OOP_PLAYER_H
