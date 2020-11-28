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
    playerSprite = new olc::Sprite("/home/jtorreal/CLionProjects/StickyKeys2.0/Images/MarioSkidding.png");
    canMoveLeft = true;
    canMoveRight = true;
    canJump = true;
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

void Player::processInput(olc::PixelGameEngine* pge, Level* currentLevel, float fElapsedTime) {
        if(pge->GetKey(olc::Key::UP).bPressed && canJump){
            if(yVelocity == 0)
                yVelocity = -12.0f;
        }
        if(pge->GetKey(olc::Key::LEFT).bHeld && canMoveLeft){
            xVelocity = -6.0f;
        }
        if(pge->GetKey(olc::Key::A).bHeld && canMoveLeft){
            xVelocity = -6.0f;
        }
        if(pge->GetKey(olc::Key::LEFT).bReleased){
            xVelocity = 0.0f;
        }
        if(pge->GetKey(olc::Key::A).bReleased){
            xVelocity = 0.0f;
        }
        if(pge->GetKey(olc::Key::RIGHT).bHeld && canMoveRight) {
            xVelocity = 6.0f;
        }
        if(pge->GetKey(olc::Key::D).bHeld && canMoveRight) {
            xVelocity = 6.0f;
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

    if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 0.0f) == L'o')
        currentLevel->setTile(fNewPlayerX + 0.0f, fNewPlayerY + 0.0f, L'.');

    if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f) == L'o')
        currentLevel->setTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f, L'.');

    if (currentLevel->getTile(fNewPlayerX + 1.0f, fNewPlayerY + 0.0f) == L'o')
        currentLevel->setTile(fNewPlayerX + 1.0f, fNewPlayerY + 0.0f, L'.');

    if (currentLevel->getTile(fNewPlayerX + 1.0f, fNewPlayerY + 1.0f) == L'o')
        currentLevel->setTile(fNewPlayerX + 1.0f, fNewPlayerY + 1.0f, L'.');

    //Check Collision
    if(xVelocity <= 0){ //Moving Left
        if (currentLevel->getTile(fNewPlayerX + 0.0f, yPos + 0.0f) != '.' || currentLevel->getTile(fNewPlayerX + 0.0f, yPos + 0.9f) != '.'){
            fNewPlayerX = (int)fNewPlayerX + 1;
            xVelocity = 0;
        }
    }
    else{ //Moving Right
        if (currentLevel->getTile(fNewPlayerX + 1.0f, yPos + 0.0f) != '.' || currentLevel->getTile(fNewPlayerX + 1.0f, yPos + 0.9f) != '.'){
            fNewPlayerX = (int)fNewPlayerX;
            xVelocity = 0;
        }
    }

    if(yVelocity <= 0){
        if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY) != '.' || currentLevel->getTile(fNewPlayerX + 0.9f, fNewPlayerY) != '.'){
            fNewPlayerY = (int)fNewPlayerY + 1;
            yVelocity = 0;
        }
    }
    else{
        if (currentLevel->getTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f) != '.' || currentLevel->getTile(fNewPlayerX + 0.9f, fNewPlayerY + 1.0f) != '.'){
            fNewPlayerY = (int)fNewPlayerY;
            yVelocity = 0;
        }
    }

    xPos = fNewPlayerX;
    yPos = fNewPlayerY;


}
void Player::draw(Level* currentLevel, olc::PixelGameEngine* pge){
    pge->DrawPartialSprite((xPos - currentLevel->getOffsetX()) * 16, (yPos - currentLevel->getOffsetY()) * 16, playerSprite, 0 * 16, 0 * 16, 1*16, 1*16);
}