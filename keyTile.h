/**
 * @author Jose Torrealba
 * @brief This class represents the KeyTile object. In our game, these are the three tiles you see hovering in the top left
 * view of your screen. Each of these tiles represent a particular direction/movement option for the player. While in their
 * default position, the player can move freely around the game. However, if an extra platform is needed for a puzzle, the user
 * can click on these keyTile platforms and place them into the game world, thus being able to use them for extra mobility.
 * However, this now locks the corresponding movement option for the player. This class contains the implementation of said
 * concept below.
 */
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
    ///Default constructor for KeyTile object
    KeyTile();
    /**
     * Constructor for KeyTile object with parameters for key instance variables
     * @param xP x position of this keyTile object
     * @param yP y position of this keyTile object
     * @param direction character representing movement this keyTile is associated with ('l' for left, 'r' for right and 'j' for jump)
     */
    KeyTile(int xP, int yP, char direction);
    /**
     * Function that returns the default x position of this keyTile object
     * @return the x position of this keyTile object
     */
    int getXPos();
    /**
     * Function that returns the default y position of this keyTile object
     * @return the y position of this keyTile object
     */
    int getYPos();
    /**
     * Function that checks if this keyTile object has been clicked
     * @return boolean that represents whether this keyTile has been clicked
     */
    bool isClicked();
    /**
     * Function that checks if this keyTile object has been placed
     * @return boolean that represents whether this keyTile has been placed
     */
    bool isPlaced();
    /**
     * Function that sets the isClicked boolean of this keyTile object to the specified boolean
     * @param val the boolean value to be set
     */
    void setIsClicked(bool val);
    /**
     * Function that sets the isPlaced value of this keyTile object to the specified boolean
     * @param val the boolean value to be set
     */
    void setIsPlaced(bool val);
    /**
     * Function that processes the user mouse input to determine whether this keyTile has been clicked, placed or is still at its default location
     * @param mouseX the x position of the mouse after a click has been registered
     * @param mouseY the y position of the mouse after a click has been registered
     * @param player reference to the player object (to be able to modify the player canMove boolean values)
     * @param currentLevel reference to the current level to be able to set tiles if needed
     * @param offsetX the horizontal offset in reference to the player
     * @param offsetY the vertical offset in reference to the player
     */
    void processInput(float mouseX, float mouseY, Player* player, Level* currentLevel, float offsetX, float offsetY);
    /**
     * Function to draw this keyTile object
     * @param pge a pointer to the current PixelGameEngine object that allows us to call window-related drawing methods
     */
    void draw(olc::PixelGameEngine* pge);
};

#endif //OOP_KEYTILE_H
