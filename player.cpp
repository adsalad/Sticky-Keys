//
// Created by jtorreal on 11/24/20.
//
#include "olcPixelGameEngine.h"
#include "player.h"

Player::Player(float xP, float yP, float xV, float yV){
    xPos = xP;
    yPos = yP;
    xVelocity = xV;
    yVelocity = yV;
    playerMoveRight = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/MarioSkidding.png");
    playerMoveLeft = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/MarioLeft.png");
    playerJumpRight = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/MarioJumping.png");
    playerJumpLeft = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys/Images/MarioJumpingLeft.png");
    onGround = false;
    facingRight = true;
    canMoveLeft = true;
    canMoveRight = true;
    canJump = true;
    flagPassed = false;
    isDead = false;
    atGoal = false;
}
Player::Player(){}
float Player::getXPos() {return xPos;}
float Player::getYPos() {return yPos;}
float Player::getXVel() {return xVelocity;}
float Player::getYVel() {return yVelocity;}
void Player::setXPos(float xP) {xPos = xP;}
void Player::setYPos(float yP) {yPos = yP;}
void Player::setXVel(float xVel) {xVelocity = xVel;}
void Player::setYVel(float yVel) {yVelocity = yVel;}
void Player::setMoveLeft(bool val) {canMoveLeft = val;}
void Player::setMoveRight(bool val) {canMoveRight = val;}
void Player::setCanJump(bool val) {canJump = val;}
void Player::setFlag(bool val){flagPassed = val;}
bool Player::getFlag(){return flagPassed;}
bool Player::getDeathStatus(){return isDead;}
bool Player::isAtGoal() {return atGoal;}
void Player::setDeathStatus(bool val){isDead = val;}

void Player::processInput(olc::PixelGameEngine* pge, Level* currentLevel, float fElapsedTime) {
        if(pge->GetKey(olc::Key::UP).bPressed && canJump){
            if(yVelocity == 0)
                yVelocity = -12.0f;
        }
        if(pge->GetKey(olc::Key::LEFT).bHeld && canMoveLeft){
            xVelocity = -6.0f;
            facingRight = false;
        }
        if(pge->GetKey(olc::Key::A).bHeld && canMoveLeft){
            xVelocity = -6.0f;
            facingRight = false;
        }
        if(pge->GetKey(olc::Key::LEFT).bReleased){
            xVelocity = 0.0f;
        }
        if(pge->GetKey(olc::Key::A).bReleased){
            xVelocity = 0.0f;
        }
        if(pge->GetKey(olc::Key::RIGHT).bHeld && canMoveRight) {
            xVelocity = 6.0f;
            facingRight = true;
        }
        if(pge->GetKey(olc::Key::D).bHeld && canMoveRight) {
            xVelocity = 6.0f;
            facingRight = true;
        }
        if(pge->GetKey(olc::Key::RIGHT).bReleased){
            xVelocity = 0.0f;
        }
        if(pge->GetKey(olc::Key::D).bReleased){
            xVelocity = 0.0f;
        }
        if(pge->GetKey(olc::Key::SPACE).bPressed && canJump) {
            if(yVelocity == 0){
                yVelocity = -12.0f;
            }
        }
        if(pge->GetKey(olc::Key::W).bPressed && canJump) {
            if(yVelocity == 0){
                yVelocity = -12.0f;
            }
        }

        if(pge->GetKey(olc::Key::R).bPressed) {
            canJump = true;
            canMoveRight = true;
            canMoveLeft = true;
        }

    yVelocity += 20.0f * fElapsedTime;

    float fNewPlayerX = xPos + xVelocity * fElapsedTime;
    float fNewPlayerY = yPos + yVelocity * fElapsedTime;

    if(xVelocity > 10.0f)
        xVelocity = 10.0f;
    if(xVelocity < -10.0f)
        xVelocity = -10.0f;
    if(yVelocity > 100.0f)
        yVelocity = 100.0f;
    if(yVelocity < -100.0f)
        yVelocity = -100.0f;

    //Check if player has collided with the checkpoint flag
    if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 0.0f) == 'f'){
        currentLevel->setTile(fNewPlayerX + 0.0f, fNewPlayerY + 0.0f, 'F');
        checkpointX = fNewPlayerX + 0.0f;
        checkpointY = fNewPlayerY + 0.0f;
        flagPassed = true;
    }

    if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f) == 'f'){
        currentLevel->setTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f, 'F');
        checkpointX = fNewPlayerX + 0.0f;
        checkpointY = fNewPlayerY + 1.0f;
        flagPassed = true;
    }

    if (currentLevel->getTile(fNewPlayerX + 1.0f, fNewPlayerY + 0.0f) == 'f') {
        currentLevel->setTile(fNewPlayerX + 1.0f, fNewPlayerY + 0.0f, 'F');
        checkpointX = fNewPlayerX+1.0f;
        checkpointY = fNewPlayerY+0.0f;
        flagPassed = true;
    }
    if (currentLevel->getTile(fNewPlayerX + 1.0f, fNewPlayerY + 1.0f) == L'f') {
        currentLevel->setTile(fNewPlayerX + 1.0f, fNewPlayerY + 1.0f, 'F');
        checkpointX = fNewPlayerX+1.0f;
        checkpointY = fNewPlayerY+1.0f;
        flagPassed = true;
    }

    //Check if player has reached the end of the level
    if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 0.0f) == 'g')
        atGoal = true;
    if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f) == 'g')
        atGoal = true;
    if (currentLevel->getTile(fNewPlayerX + 1.0f, fNewPlayerY + 0.0f) == 'g')
        atGoal = true;
    if (currentLevel->getTile(fNewPlayerX + 1.0f, fNewPlayerY + 1.0f) == 'g')
        atGoal = true;

    //Check if player has collided with a tile that should kill it
    if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 0.0f) == 'd')
        isDead = true;
    if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f) == 'd')
        isDead = true;
    if (currentLevel->getTile(fNewPlayerX + 1.0f, fNewPlayerY + 0.0f) =='d')
        isDead = true;
    if (currentLevel->getTile(fNewPlayerX + 1.0f, fNewPlayerY + 1.0f) == 'd')
        isDead = true;


    //Check Collision
    if(xVelocity <= 0){ //Moving Left
        if ((currentLevel->getTile(fNewPlayerX + 0.0f, yPos + 0.0f) != '.' || currentLevel->getTile(fNewPlayerX + 0.0f, yPos + 0.9f) != '.') && (currentLevel->getTile(fNewPlayerX + 0.0f, yPos + 0.0f) != 'F' || currentLevel->getTile(fNewPlayerX + 0.0f, yPos + 0.9f) != 'F')){
            fNewPlayerX = (int)fNewPlayerX + 1;
            xVelocity = 0;
        }
    }
    else{ //Moving Right
        if ((currentLevel->getTile(fNewPlayerX + 1.0f, yPos + 0.0f) != '.' || currentLevel->getTile(fNewPlayerX + 1.0f, yPos + 0.9f) != '.') && (currentLevel->getTile(fNewPlayerX + 1.0f, yPos + 0.0f) != 'F' || currentLevel->getTile(fNewPlayerX + 1.0f, yPos + 0.9f) != 'F')){
            fNewPlayerX = (int)fNewPlayerX;
            xVelocity = 0;
        }
    }

    onGround = false;
    if(yVelocity <= 0){
        if ((currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY) != '.' || currentLevel->getTile(fNewPlayerX + 0.9f, fNewPlayerY) != '.') && (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY) != 'F' || currentLevel->getTile(fNewPlayerX + 0.9f, fNewPlayerY) != 'F')){
            fNewPlayerY = (int)fNewPlayerY + 1;
            yVelocity = 0;
        }
    }
    else{
        if ((currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f) != '.' || currentLevel->getTile(fNewPlayerX + 0.9f, fNewPlayerY + 1.0f) != '.') && (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f) != 'F' || currentLevel->getTile(fNewPlayerX + 0.9f, fNewPlayerY + 1.0f) != 'F')){
            fNewPlayerY = (int)fNewPlayerY;
            yVelocity = 0;
            onGround = true;
        }
    }

    xPos = fNewPlayerX;
    yPos = fNewPlayerY;


}

void Player::death() {
    if (isDead) {
        isDead = false;
        if (!flagPassed) {
            xPos=1;
            yPos=1;
        }
        else {
            xPos = checkpointX;
            yPos = checkpointY;
        }
        canJump = true;
        canMoveRight = true;
        canMoveLeft = true;
    }
}

void Player::win(){
    if(atGoal){
        atGoal = false;
        flagPassed = false;
        canJump = true;
        canMoveRight = true;
        canMoveLeft = true;
        xPos = 1;
        yPos = 1;
    }
}

void Player::draw(Level* currentLevel, olc::PixelGameEngine* pge){
    if (!onGround && facingRight){
        pge->DrawPartialSprite((xPos - currentLevel->getOffsetX()) * 16, (yPos - currentLevel->getOffsetY()) * 16, playerJumpRight, 0 * 16, 0 * 16, 1*16, 1*16);
    }
    else if (!onGround && !facingRight){
        pge->DrawPartialSprite((xPos - currentLevel->getOffsetX()) * 16, (yPos - currentLevel->getOffsetY()) * 16, playerJumpLeft, 0 * 16, 0 * 16, 1*16, 1*16);
    }
    else if (facingRight){
        pge->DrawPartialSprite((xPos - currentLevel->getOffsetX()) * 16, (yPos - currentLevel->getOffsetY()) * 16, playerMoveRight, 0 * 16, 0 * 16, 1*16, 1*16);
    }
    else{
        pge->DrawPartialSprite((xPos - currentLevel->getOffsetX()) * 16, (yPos - currentLevel->getOffsetY()) * 16, playerMoveLeft, 0 * 16, 0 * 16, 1*16, 1*16);
    }
}