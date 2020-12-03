/**
 * @authors Jose Torrealba, Cole Chang
 * @brief This class represents each level in the game
 * @details This class represents each level in the game. In total, there will be five instances of said object, but more
 * can be created down the line. The actual layout of a level is represented by characters in a text file stored in a
 * working directory folder called Levels. This class deals with the reading of the corresponding text file and deals
 * with scenarios in which the composition of the layout may change (if a player places a keyTile in a particular spot,
 * for example). This class also determines the position of the camera by determining which subsection of the available
 * tiles in the game to display on the screen at any given time.
 */

//
// Created by jtorreal on 11/24/20.
//

#ifndef OOP_LEVEL_H
#define OOP_LEVEL_H
#include "olcPixelGameEngine.h"

class Level{
    private:
            int levelWidth;
            int levelHeight;
            int tileWidth;
            int tileHeight;
            bool fixTiles;
            float offsetX;
            float offsetY;
            std::string levelMap;
            std::string fileName;
            olc::Sprite *groundSprite;
            olc::Sprite *checkpointSprite;
            olc::Sprite *checkpointPassedSprite;
            olc::Sprite *finishSprite;
            olc::Sprite *fireSprite;
            olc::Sprite *rightPlacedSprite;
            olc::Sprite *leftPlacedSprite;
            olc::Sprite *upPlacedSprite;

    public:
            /**
             * The default constructor for the Level class (doesn't get used)
             */
            Level();
            /**
             * @brief Level Constructor
             * @details The main constructor for the Level class
             * @param lW the width of the level being created (# number of tiles)
             * @param lH the height of the level being created (# number of tiles)
             * @param tW the width of each tile (in pixels)
             * @param tH the height of each tile (in pixels)
             * @param fName the name of the text file that contains the text representation of the level
             */
            Level(int lW, int lH, int tW, int tH, std::string fName);
            /**
             * @brief getLevelWidth
             * @details This function returns the width of the level (in # of tiles)
             * @return the width of the level (in # of tiles)
             */
            int getLevelWidth();
            /**
             * @brief getLevelHeight
             * @details This function returns the height of the level (in # of tiles)
             * @return the height of the level (in # of tiles)
             */
            int getLevelHeight();
            /**
             * @brief getTileWidth
             * @details This function returns the width of the tiles (in # of pixels)
             * @return width of each tile (in # of pixels)
             */
            int getTileWidth();
            /**
             * @brief getTileHeight
             * @details This function returns the height of the tiles (in # of pixels)
             * @return height of each tile (in # of pixels)
             */
            int getTileHeight();
            /**
             * @brief getOffsetX
             * @details This function returns the horizontal offset used to keep the player in the center of view when traversing the level
             * @return the horizontal offset value relative to the player
             */
            float getOffsetX();
            /**
             * @brief getOffsetY
             * @details This function returns the vertical offset used to keep the player in the center of view when traversing the level
             * @return the vertical offset value relative to the player
             */
            float getOffsetY();
            /**
             * @brief getLevelMap
             * @details This function returns the string representation of the level
             * @return the string representation of the level
             */
            std::string getLevelMap();
            /**
             * @brief getTile
             * @details This function traverses the string representation of the level and returns the corresponding character (or tile) at a given x and y coordinate
             * @param x the x coordinate of the desired tile
             * @param y the y coordinate of the desired tile
             * @return the character (or tile) at the specified x and y coordinates
             */
            char getTile(int x, int y);
            /**
             * @brief setTile
             * @details This function sets the value of a certain tile in the level at a specified location to a specified value/character
             * @param x the x coordinate of the tile to be set
             * @param y the y coordinate of the tile to be set
             * @param c the character that the tile will be set to
             */
            void setTile(int x, int y, char c);
            /**
             * @brief draw
             * @details This function handles all the calculations necessary to display the relevant portion of the level to the window
             * @param camX the current X position of the camera
             * @param camY the current Y position of the camera
             * @param pge a pointer to the current PixelGameEngine object that allows us to use window-related methods
             */
            void draw(float camX, float camY, olc::PixelGameEngine* pge);
            /**
             * @brief setFixTiles
             * @details This function sets the value of the boolean that represents whether the keyTiles need to be recalled/replaced back in their default positions
             * @param fix  the boolean value to set whether keyTiles need to be recalled/replaced back in their default positions
             */
            void setFixTiles(bool fix);
            /**
             * @brief getFixTiles
             * @details This function returns a boolean that represents whether the keyTiles need to be recalled/replaced back in their default positions
             * @return boolean that represents whether keyTiles need to be "fixed" and placed back in default positions
             */
            bool getFixTiles();
};

#endif //OOP_LEVEL_H
