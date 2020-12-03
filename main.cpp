/**
 * @authors Jose Torrealba, Cole Chang, Cameron Railton, Adam Salaymeh
 * @brief This file/class is a representation of the engine to our StickyKeys game. It is where the player, keyTile and level classes all come together.
 * One player object, five level objects and three keyTile objects are all created and continuously updated in this class. The three main functions:
 * OnUserCreate, OnUserUpdate & OnUserDestroy are all inherited from the olcPixelGameEngine header file and determine what code gets run on initial
 * bootup, continuously throughout the game, and when the window closes, respectively.
 */
#define OLC_PGE_APPLICATION
#define OLC_PGEX_SOUND
#include "olcPixelGameEngine.h"
#include "olcPGEX_Sound.h"
#include "level.h"
#include "player.h"
#include "keyTile.h"
#include <string>
#include <vector>

//Create the actual Game Engine
class StickyKeys : public olc::PixelGameEngine
{
public:
    /**
     * Default constructor for our GameEngine object
     */
    StickyKeys()
    {
        sAppName = "Sticky Keys Engine";
    }

private:
    int levelCount;
    Level levelOne = Level(64, 16, 16, 16, "/home/jtorreal/CLionProjects/StickyKeys/Levels/level1.txt");
    Level levelTwo = Level(64, 16, 16, 16, "/home/jtorreal/CLionProjects/StickyKeys/Levels/level2.txt");
    Level levelThree = Level(64, 16, 16, 16, "/home/jtorreal/CLionProjects/StickyKeys/Levels/level3.txt");
    Level levelFour = Level(64, 16, 16, 16, "/home/jtorreal/CLionProjects/StickyKeys/Levels/level4.txt");
    Level levelFive = Level(64, 16, 16, 16, "/home/jtorreal/CLionProjects/StickyKeys/Levels/level5.txt");
    std::vector<Level> levelList;

    Level* currentLevel;
    Player player = Player(1, 1, 0, 0);
    KeyTile leftTile = KeyTile(20, 50, 'l');
    KeyTile rightTile = KeyTile(leftTile.getXPos()+16+20, 50, 'r');
    KeyTile jumpTile = KeyTile(rightTile.getXPos()+16+20, 50, 'j');
    std::string currentMap;

    float cameraX = 0.0f;
    float cameraY = 0.0f;

    int jumpSound;
    int backSound;
    int deathSound;
    int placeKeySound;
    int recallSound;

public:
    /**
     * This function runs only once when the window is created. It initializes all of our levels and audio samples to be used later on in the program
     * @return true to signify this process has been completed
     */
    bool OnUserCreate() override
    {
        levelCount = 0;
        levelList.push_back(levelOne);
        levelList.push_back(levelTwo);
        levelList.push_back(levelThree);
        levelList.push_back(levelFour);
        levelList.push_back(levelFive);


        //initializing format and sound samples
        olc::SOUND::InitialiseAudio(44100, 1, 8, 512);
        backSound = olc::SOUND::LoadAudioSample("/home/jtorreal/CLionProjects/StickyKeys/Music/GameBackground.wav");
        jumpSound = olc::SOUND::LoadAudioSample("/home/jtorreal/CLionProjects/StickyKeys/Music/Jump_03.wav");
        deathSound = olc::SOUND::LoadAudioSample("/home/jtorreal/CLionProjects/StickyKeys/Music/Roblox-death-sound (online-audio-converter.com).wav");
        placeKeySound = olc::SOUND::LoadAudioSample("/home/jtorreal/CLionProjects/StickyKeys/Music/mixkit-player-jumping-in-a-video-game-2043.wav");
        recallSound = olc::SOUND::LoadAudioSample("/home/jtorreal/CLionProjects/StickyKeys/Music/mixkit-explainer-video-game-alert-sweep-236.wav");

        olc::SOUND::PlaySample(backSound, true);



        // Called once at the start, so create things here
        return true;
    }

    /**
     * Called every frame and deals with all processes that require updating every frame or continuous checks such as drawing the player, processing user input, drawing the level and keyTiles, etc.
     * @param fElapsedTime fElapsedTime a time per frame value meant to be included in certain operations to allow equal performance on all machines
     * @return true to signify this process has been completed
     */
    bool OnUserUpdate(float fElapsedTime) override
    {
        if(levelCount == 0){
            FillRect(0,0,ScreenWidth(), ScreenHeight(), olc::DARK_RED);
            DrawString(45, 75, "Sticky Keys", olc::GREEN, 2);
            DrawString(55, 130, "Hit 'Enter' to Play", olc::BLACK);
            DrawString(55, 150, "Hit 'ESC' to Quit", olc::BLACK);

            if(GetKey(olc::ENTER).bPressed){
                levelCount++;
            }
            if(GetKey(olc::ESCAPE).bPressed){
                exit(0);
            }
        }
        else if(levelCount == 6){
            FillRect(0,0,ScreenWidth(), ScreenHeight(), olc::DARK_RED);
            DrawString(55, 120, "THE END!", olc::GREEN, 2);
            if(GetKey(olc::ENTER).bPressed || GetKey(olc::ESCAPE).bPressed){
                exit(0);
            }
        }
        else {
            currentLevel = &levelList.at(levelCount-1);
            currentMap = currentLevel->getLevelMap();
            SetPixelMode(olc::Pixel::ALPHA);


            //Handle Input
            if (IsFocused()) {
                player.processInput(this, currentLevel, fElapsedTime);
                if (GetKey(olc::Key::R).bPressed) {
                    leftTile.setIsPlaced(false);
                    leftTile.setIsClicked(false);
                    rightTile.setIsPlaced(false);
                    rightTile.setIsClicked(false);
                    jumpTile.setIsPlaced(false);
                    jumpTile.setIsClicked(false);
                    currentLevel->setFixTiles(true);
                    olc::SOUND::PlaySample(recallSound);
                }
                if ((GetKey(olc::Key::UP).bPressed) || (GetKey(olc::Key::SPACE).bPressed) ||
                    (GetKey(olc::Key::W).bPressed) && !jumpTile.isPlaced()) {
                    olc::SOUND::PlaySample(jumpSound);
                }
                if (player.getDeathStatus() || player.isAtGoal()) {
                    leftTile.setIsPlaced(false);
                    leftTile.setIsClicked(false);
                    rightTile.setIsPlaced(false);
                    rightTile.setIsClicked(false);
                    jumpTile.setIsPlaced(false);
                    jumpTile.setIsClicked(false);
                    currentLevel->setFixTiles(true);
                }
                if(player.getDeathStatus()){
                    player.death();
                    olc::SOUND::PlaySample(deathSound);
                }
                if(player.isAtGoal()){
                    player.win();
                    levelCount++;
                    //play win sound
                }
            }

            //Camera Properties
            cameraX = player.getXPos();
            cameraY = player.getYPos();

            currentLevel->draw(cameraX, cameraY, this);
            float offsetX = currentLevel->getOffsetX();
            float offsetY = currentLevel->getOffsetY();

            //Draw Left Keyboard Key
            leftTile.draw(this);
            rightTile.draw(this);
            jumpTile.draw(this);

            //Check to see if mouse clicks on keyboard key
            if (IsFocused()) {
                if (GetMouse(0).bPressed) {
                    int mouseClickX = GetMouseX();
                    int mouseClickY = GetMouseY();
                    leftTile.processInput(mouseClickX, mouseClickY, &player, currentLevel, offsetX, offsetY);
                    rightTile.processInput(mouseClickX, mouseClickY, &player, currentLevel, offsetX, offsetY);
                    jumpTile.processInput(mouseClickX, mouseClickY, &player, currentLevel, offsetX, offsetY);
                }
            }

            //Draw player
            player.draw(currentLevel, this);
            SetPixelMode(olc::Pixel::NORMAL);
        }
        return true;
    }

    /**
     * Called once when the window/application is terminated. Allows for any open instances of code such as Audio to be properly shut down
     * @return true to signify this process has been completed
     */
    bool OnUserDestroy() override
    {
        olc::SOUND::DestroyAudio();
        return true;
    }
};

/**
 * The main function where we create and run our game engine object
 * @return 0 to signify that our game has created and ran properly
 */
int main()
{
    StickyKeys demo;
    if (demo.Construct(256, 256, 8, 8))
        demo.Start();

    return 0;
}