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
    Player player = Player(1, 0, 0, 0);
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
    //Create initial level and load any Sprites needed at this stage
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

    bool OnUserUpdate(float fElapsedTime) override
    {
        if(levelCount == 0){
            FillRect(0,0,ScreenWidth(), ScreenHeight(), olc::BLUE);
            if(GetKey(olc::ENTER).bPressed){
                levelCount++;
            }
            if(GetKey(olc::ESCAPE).bPressed){
                exit(0);
            }
        }
        else if(levelCount == 6){
            FillRect(0,0,ScreenWidth(), ScreenHeight(), olc::YELLOW);
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

    bool OnUserDestroy() override
    {
        olc::SOUND::DestroyAudio();
        return true;
    }
};


int main()
{
    StickyKeys demo;
    if (demo.Construct(256, 256, 8, 8))
        demo.Start();

    return 0;
}