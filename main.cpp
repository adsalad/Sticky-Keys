#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "level.h"
#include "player.h"
#include "keyTile.h"
#include <string>
using namespace std;

//Create the actual Game Engine
class StickyKeys : public olc::PixelGameEngine
{
public:
    StickyKeys()
    {
        sAppName = "Sticky Keys Engine";
    }

private:
    Level currentLevel =  Level(64, 16, 16, 16, "/home/jtorreal/CLionProjects/StickyKeys2.0/Levels/LevelOne.txt");
    Player player = Player(0, 0, 0, 0);
    KeyTile leftTile = KeyTile(20, 50, 'l');
    KeyTile rightTile = KeyTile(leftTile.getXPos()+16+20, 50, 'r');
    KeyTile jumpTile = KeyTile(rightTile.getXPos()+16+20, 50, 'j');
    string currentMap = currentLevel.getLevelMap();

    int coinCounter = 0;
    int totalCoins = 0;

    float cameraX = 0.0f;
    float cameraY = 0.0f;

public:
    //Create initial level and load any Sprites needed at this stage
    bool OnUserCreate() override
    {
        currentMap = currentLevel.getLevelMap();
        for (int i; i<currentMap.length();i++){
            if(currentMap[i]=='o') {
                totalCoins = totalCoins + 1;
            }
        }
        // Called once at the start, so create things here
        return true;
    }

    bool OnUserUpdate(float fElapsedTime) override
    {
        currentMap = currentLevel.getLevelMap();
        SetPixelMode(olc::Pixel::ALPHA);


        //Handle Input
        if(IsFocused()){
            player.processInput(this, &currentLevel, fElapsedTime);
            if(GetKey(olc::Key::R).bPressed) {
                leftTile.setIsPlaced(false);
                leftTile.setIsClicked(false);
                rightTile.setIsPlaced(false);
                rightTile.setIsClicked(false);
                jumpTile.setIsPlaced(false);
                jumpTile.setIsClicked(false);
                currentLevel.setFixTiles(true);
            }
        }

        int ingameCoins = 0;
        for (int i = 0; i < currentMap.length();i++){
            if(currentMap[i]=='o') {
                ingameCoins = ingameCoins+1;
            }
        }

        //Camera Properties
        cameraX = player.getXPos();
        cameraY = player.getYPos();

        currentLevel.draw(cameraX, cameraY, this);
        float offsetX = currentLevel.getOffsetX();
        float offsetY = currentLevel.getOffsetY();

        //Draw Left Keyboard Key
        leftTile.draw(this);
        rightTile.draw(this);
        jumpTile.draw(this);

        //Check to see if mouse clicks on keyboard key
        if(IsFocused()){
            if(GetMouse(0).bPressed){
                int mouseClickX = GetMouseX();
                int mouseClickY = GetMouseY();
                leftTile.processInput(mouseClickX, mouseClickY, &player, &currentLevel, offsetX, offsetY);
                rightTile.processInput(mouseClickX, mouseClickY, &player, &currentLevel, offsetX, offsetY);
                jumpTile.processInput(mouseClickX, mouseClickY, &player, &currentLevel, offsetX, offsetY);
            }
        }

        //Draw Amount of Coins
        coinCounter = totalCoins - ingameCoins;
        string coinString = to_string(coinCounter);
        DrawString(leftTile.getXPos()-10,leftTile.getYPos()+150,"Coins:"+coinString,olc::YELLOW);

        //Draw player
        player.draw(&currentLevel, this);
        SetPixelMode(olc::Pixel::NORMAL);
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