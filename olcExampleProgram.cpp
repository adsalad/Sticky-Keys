#define OLC_PGE_APPLICATION

#include "olcPixelGameEngine.h"
using namespace std;


class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Test Engine";
	}

private:
    string LevelOne;
	int nLevelWidth;
	int nLevelHeight;

	float fPlayerX = 0.0f;
	float fPlayerY = 0.0f;

	float playerVelX = 0.0f;
	float playerVelY = 0.0f;

	float cameraX = 0.0f;
	float cameraY = 0.0f;

	bool onGround = false;

public:
	bool OnUserCreate() override
	{
		nLevelWidth = 64;
		nLevelHeight = 16;

        LevelOne += "................................................................";
        LevelOne += "................................................................";
        LevelOne += ".......#####....................................................";
        LevelOne += "........###.....................................................";
        LevelOne += ".......................########.................................";
        LevelOne += ".....##########.......###..............#.#......................";
        LevelOne += "....................###................#.#......................";
        LevelOne += "...................####.........................................";
        LevelOne += "####################################.##############.....########";
        LevelOne += "...................................#.#...............###........";
        LevelOne += "........................############.#............###...........";
        LevelOne += "........................#............#.........###..............";
        LevelOne += "........................#.############......###.................";
        LevelOne += "........................#................###....................";
        LevelOne += "........................#################.......................";
        LevelOne += "................................................................";

	    // Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
	    auto GetTile = [&](int x, int y)
        {
	        if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
	            return LevelOne[y * nLevelWidth + x];
	        else
	            return ' ';
        };

        auto SetTile = [&](int x, int y, char c)
        {
            if (x >= 0 && x < nLevelWidth && y >= 0 && y < nLevelHeight)
                LevelOne[y * nLevelWidth + x] = c;
        };

        //No longer needed as they are updated between frames
        //playerVelY = 0.0f;
        //playerVelX = 0.0f;

        //Handle Input
        if(IsFocused()){
            if(GetKey(olc::Key::UP).bPressed){
                if(playerVelY == 0)
                    playerVelY = -12.0f;
            }
            if(GetKey(olc::Key::DOWN).bHeld){
                playerVelY = 6.0f;
            }
            if(GetKey(olc::Key::LEFT).bHeld){
                playerVelX += (onGround ? -25.0f : -15.0f) * fElapsedTime;
            }
            if(GetKey(olc::Key::RIGHT).bHeld) {
                playerVelX += (onGround ? 25.0f : 15.0f) * fElapsedTime;
            }
            if(GetKey(olc::Key::SPACE).bPressed) {
                if(playerVelY == 0){
                    playerVelY = -12.0f;
                }
            }
        }

        //Gravity
        playerVelY += 20.0f * fElapsedTime;

        //Drag
        if(onGround){
            playerVelX += -3.0f * playerVelX * fElapsedTime;
            if(fabs(playerVelX) < 0.01f)
                playerVelX = 0.0f;
        }

        float fNewPlayerX = fPlayerX + playerVelX * fElapsedTime;
        float fNewPlayerY = fPlayerY + playerVelY * fElapsedTime;

        if(playerVelX > 10.0f)
            playerVelX = 10.0f;
        if(playerVelX < -10.0f)
            playerVelX = -10.0f;
        if(playerVelY > 100.0f)
            playerVelY = 100.0f;
        if(playerVelY < -100.0f)
            playerVelY = -100.0f;

        //Check Collision
        if(playerVelX <= 0){
            if (GetTile(fNewPlayerX + 0.0f, fPlayerY + 0.0f) != '.' || GetTile(fNewPlayerX + 0.0f, fPlayerY + 0.9f) != '.'){
                fNewPlayerX = (int)fNewPlayerX + 1;
                playerVelX = 0;
            }
        }
        else{
            if (GetTile(fNewPlayerX + 1.0f, fPlayerY + 0.0f) != '.' || GetTile(fNewPlayerX + 1.0f, fPlayerY + 0.9f) != '.'){
                fNewPlayerX = (int)fNewPlayerX;
                playerVelX = 0;
            }
        }

        onGround = false;
        if(playerVelY <= 0){
            if (GetTile(fNewPlayerX + 0.0f, fNewPlayerY) != '.' || GetTile(fNewPlayerX + 0.9f, fNewPlayerY) != '.'){
                fNewPlayerY = (int)fNewPlayerY + 1;
                playerVelY = 0;
            }
        }
        else{
            if (GetTile(fNewPlayerX + 0.0f, fNewPlayerY + 1.0f) != '.' || GetTile(fNewPlayerX + 0.9f, fNewPlayerY + 1.0f) != '.'){
                fNewPlayerY = (int)fNewPlayerY;
                playerVelY = 0;
                onGround = true;
            }
        }

        fPlayerX = fNewPlayerX;
        fPlayerY = fNewPlayerY;


        cameraX = fPlayerX;
        cameraY = fPlayerY;

        //Draw Level
        int nTileWidth = 16;
        int nTileHeight = 16;
        int nVisibleTilesX = ScreenWidth() / nTileWidth;
        int nVisibleTilesY = ScreenHeight() / nTileHeight;

        //Calculate Topleft tile
        float offsetX = cameraX - (float) nVisibleTilesX / 2.0f;
        float offsetY = cameraY - (float)nVisibleTilesY / 2.0f;

        //Prevent Camera from going outside of game limits
        if(offsetX < 0) offsetX = 0;
        if(offsetY < 0) offsetY = 0;
        if(offsetX > nLevelWidth - nVisibleTilesX) offsetX = nLevelWidth - nVisibleTilesX;
        if(offsetY > nLevelHeight - nVisibleTilesY) offsetY = nLevelHeight - nVisibleTilesY;

        //Offsets for smoother movement
        float tileOffsetX = (offsetX - (int)offsetX) * nTileWidth;
        float tileOffsetY = (offsetY - (int) offsetY) * nTileHeight;

        //Draw actual tilemap
        for(int i = -1; i < nVisibleTilesX+1; i++){
            for (int j = -1; j < nVisibleTilesY+1; j++){
                char tileID = GetTile(i + offsetX, j + offsetY);
                switch (tileID)
                {
                    case '.':
                        FillRect(i * nTileWidth-tileOffsetX, j * nTileHeight-tileOffsetY, nTileWidth, nTileHeight, olc::BLACK);
                        break;
                    case '#':
                        FillRect(i * nTileWidth-tileOffsetX, j * nTileHeight-tileOffsetY, nTileWidth, nTileHeight, olc::RED);
                        break;
                    default:
                        break;
                }
            }
        }

        //Draw player
        FillRect((fPlayerX-offsetX) * nTileWidth, (fPlayerY - offsetY) * nTileHeight, nTileWidth, nTileHeight, olc::GREEN);



		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(256, 240, 8, 8))
		demo.Start();

	return 0;
}
