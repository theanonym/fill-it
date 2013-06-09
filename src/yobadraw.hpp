#ifndef YOBADRAW_HPP
#define YOBADRAW_HPP

#include <iostream>
#include <cassert>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

#include "types.hpp"

class YobaDraw
{
public:
   static SDL_Surface * loadImage(const std::string &);

   static void draw(SDL_Surface *, const Rect &, SDL_Surface *, const Rect &);
   static void draw(SDL_Surface *, const Rect &, SDL_Surface *);
   static void drawRect(SDL_Surface *, const Rect &, const Color &);
   static void drawText(SDL_Surface *, const Rect &, const std::string &, TTF_Font *, const Color &);
   static void fill(SDL_Surface *, const Color &);
};

#endif // YOBADRAW_HPP
