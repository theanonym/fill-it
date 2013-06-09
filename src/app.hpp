#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>
#include <queue>

#include <SDL.h>
#include <SDL_ttf.h>

#include "yobadraw.hpp"
#include "types.hpp"

class App
{
public:
   App();

   int exec();

private:
   bool init();
   void cleanup();

   void loop();
   void render() const;

   bool onEvent(SDL_Event *);
   void onKeyDown(SDLKey);
   void onLButtonDown(int, int);
   void onExit();

private:
   void reset();
   bool checkVictory() const;
   void changeColor(int, int, int, int);

private:
   bool mIsRunning;
   SDL_Surface * mScreenSurface;
   SDL_Surface * mIconSurface;
   TTF_Font * mFont;

   static const int GRID_SIZE = 20;
   static const int CELL_SIZE = 30;

   std::vector<std::vector<int> > mGrid;
   Color mColors[7];
   int mCurrentStep;
   std::queue<int> mNextColors;
};

#endif // APP_HPP
