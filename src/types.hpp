#ifndef TYPES_HPP
#define TYPES_HPP

#include <SDL.h>

struct Point
{
   int x, y;

   Point() : x(0), y(0) {}
   Point(int _x, int _y) : x(_x), y(_y) {}
};

struct Rect : public SDL_Rect
{
   Rect()
   {
      x = y = w = h = 0;
   }

   Rect(int _x, int _y, int _w, int _h)
   {
      x = _x;
      y = _y;
      w = _w;
      h = _h;
   }
};

struct Color : public SDL_Color
{
   Color()
   {
      r = g = b = 0;
   }

   Color(int _r, int _g, int _b)
   {
      r = _r;
      g = _g;
      b = _b;
   }

   Uint32 mapRGB(const SDL_PixelFormat * format) const
   {
      return SDL_MapRGB(format, r, g, b);
   }
};

#endif // TYPES_HPP
