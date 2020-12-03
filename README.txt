HOW TO PLAY

Hi, welcome to the Sticky Keys game demo! You will be able to play through 5 levels of our game today and we hope you enjoy it! The objective of each level is to control your player and avoid fire/lava tiles while you make your way to each level's goal (denoted by a yellow checkered flag). You may notice there are other flags that exist in the game as well, these are checkpoint flags. There will be one per level. A checkpoint flag is red until you touch it, at which point it becomes green and if you die afterwards, you will respawn at the checkpoint rather than all the way at the beginning of the level.

To compile and run this demo, you will need a working version of the g++ compiler. 
You will also need to install a set number of libraries. You can do all of this with 
the following commands:

sudo apt-get install libpng-dev libglu1-mesa-dev libx11-dev build-essential libasound2

Please follow the corresponding prompts and indicate "Y" (Yes) if asked if you'd like to
install the respective packages. If you are already up to date, there should be no issues!


Now to download the files needed to run the code. Included on Bitbucket are 4 .cpp files, 5 .h files and three folders containing .png files, .txt files and .wav files. Please download all of these files and folders to your local system. 

Depending on where you download these files, you will need to change a few lines
in the .cpp files to reflect the filepath of the PNG images. Please modify the filepath entries
in lines... 

58-63 of the keyTile.cpp file to match with where you've stored the images.
20-27 of the level.cpp file to match with where you've stored the images.
12-15 of the player.cpp file to match with where you've stored the images.

34-38 of the main.cpp file to match with where you've stored the .txt files.
75-79 of the main.cpp file to match with where you've stored the .wav files.


If done correctly, you will see a player character and visual representations for the 
environmental blocks when you compile and run. Otherwise, you may need to double check 
the accuracy of your specified filepath.

You can now boot up your terminal, and change directory into where you've stored both 
the .cpp and .h files. To compile, please use the following command:

g++ -o testComp main.cpp level.cpp player.cpp keyTile.cpp -lX11 -lGL -lpthread -lpng -lasound -lstdc++fs -std=c++17

This will create an executable called "testComp" in that same directory. To run it, simply
enter the following command into your terminal:

./testComp

You should now be able to access the demo, enjoy!


IMPORTANT THINGS TO NOTE

/***The olcPixelEngine header file and its extension olcPGEX_Sound in use with this project are free to use, online resources meant to be an alternative to bulkier software development libraries like SDL & SFML (both of which we explored) intended to aid in some of the more complicated tasks of creating graphical and audio elements to a working game. As we do not aim to use this game for any public distribution or profit, we are in accordance with the OLC-3 License provided***/
