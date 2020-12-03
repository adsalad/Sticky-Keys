/**
 * @authors Jose Torrealba, Cole Chang
 * @brief This class represents the player object. There will only be one of these that exist in a game at any time as
 * this object is what the user will control. Through keyboard input (using WASD, arrow keys and spacebar), the user can
 * control the movement and position of this player character throughout the game. This class deals with the various input
 * and corresponding changes to the player position, velocity and death/win status throughout the game.
 */
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
    /// Default constructor for the player class (doesn't get used)
    Player();
    /**
     * This constructor for the player class takes in parameters to set key instance variables
     * @param xP the x position of the player object
     * @param yP the y position of the player object
     * @param xV the x/horizontal velocity of the player object
     * @param yV the y/vertical velocity of the player object
     */
    Player(float xP, float yP, float xV, float yV);
    /**
     * Function that returns the current x position of this player object
     * @return x position of this player object
     */
    float getXPos();
    /**
     * Function that returns the current y position of this player object
     * @return y position of this player object
     */
    float getYPos();
    /**
     * Function that returns the current x velocity of this player object
     * @return x velocity of this player object
     */
    float getXVel();
    /**
     * Function that returns the current y velocity of this player object
     * @return y velocity of this player object
     */
    float getYVel();
    /**
     * Function that sets the x position of this player object to the specified value
     * @param xPos the value that this player's x position will be set to
     */
    void setXPos(float xPos);
    /**
     * Function that sets the y position of this player object to the specified value
     * @param yPos the value that this player's y position will be set to
     */
    void setYPos(float yPos);
    /**
     * Function that sets the x velocity of this player object to the specified value
     * @param xVel the value that this player's x velocity will be set to
     */
    void setXVel(float xVel);
    /**
     * Function that sets the y velocity of this player object to the specified value
     * @param yVel the value that this player's y velocity will be set to
     */
    void setYVel(float yVel);
    /**
     * Function that sets the boolean that determines whether the player can move left to the specified value
     * @param val the value that the boolean representing whether the player can move left will be set to
     */
    void setMoveLeft(bool val);
    /**
     * Function that sets the boolean that determines whether the player can move right to the specified value
     * @param val the value that the boolean representing whether the player can move right will be set to
     */
    void setMoveRight(bool val);
    /**
     * Function that sets the boolean that determines whether the player can jump to the specified value
     * @param val the value that the boolean representing whether the player can jump will be set to
     */
    void setCanJump(bool val);
    /**
     * Function that processes the keyboard input from the user to determine how the player object moves
     * @param pge reference to the pixelGameEngine object to provide access to input-related methods
     * @param currentLevel reference to the current level
     * @param fElapsedTime reference to the amount of frames in elapsed time (used for equal performance purposes across machines)
     */
    void processInput(olc::PixelGameEngine* pge, Level* currentLevel, float fElapsedTime);
    /**
     * Function that draws the player object
     * @param currentLevel reference to the current level
     * @param pge reference to the current pixelGameEngine object to provide access to window-drawing methods
     */
    void draw(Level* currentLevel, olc::PixelGameEngine* pge);
    /**
     * Function that sets the boolean that represents whether or not checkpoint flag has been passed to specified value
     * @param val the value that the boolean representing whether the player has passed the checkpoint will be set to
     */
    void setFlag(bool val);
    /**
     * Function that returns the current value of the boolean that represents whether the checkpoint has been passed by the player
     * @return the boolean that represents whether the checkpoint has been passed by the player
     */
    bool getFlag();
    /**
     * Function that returns the current value of the boolean that represents whether the player has died
     * @return the boolean that represents whether the player has died
     */
    bool getDeathStatus();
    /**
     * Function that returns the current value of the boolean that represents whether the player has reached the end of the level
     * @return the boolean that represents whether the player has reached the end of the level
     */
    bool isAtGoal();
    /**
     * Function that sets the boolean representing whether the player has died to the specified value
     * @param val the value that the boolean representing whether the player has died will be set to
     */
    void setDeathStatus(bool val);
    /**
     * Function that is called when the player has died. Resets the position of the player and restores all movement
     */
    void death();
    /**
     * FUnction that is called when the player has reached the end of the level. Resets the position of the player, restores all movement and resets flag booleans
     */
    void win();
};


#endif //OOP_PLAYER_H
