#include "yobadraw.hpp"

SDL_Surface * YobaDraw::loadImage(const std::string & fname)
{
   return IMG_Load(fname.c_str());
}

void YobaDraw::draw(SDL_Surface * dstSurface, const Rect & dstRect, SDL_Surface * srcSurface, const Rect & srcRect)
{
   assert(dstSurface);
   assert(srcSurface);

   SDL_BlitSurface(srcSurface, const_cast<Rect *>(&srcRect), dstSurface, const_cast<Rect *>(&dstRect));
}

void draw(SDL_Surface * dstSurface, const Rect & dstRect, SDL_Surface * srcSurface)
{
   assert(dstSurface);
   assert(srcSurface);

   SDL_BlitSurface(srcSurface, 0, dstSurface, const_cast<Rect *>(&dstRect));
}

void YobaDraw::drawRect(SDL_Surface * dstSurface, const Rect & dstRect, const Color & color)
{
   assert(dstSurface);

   SDL_FillRect(dstSurface, const_cast<Rect *>(&dstRect), color.mapRGB(dstSurface->format));
}

void YobaDraw::drawText(SDL_Surface * dstSurface, const Rect & dstRect, const std::string & text, TTF_Font * font, const Color & color)
{
   assert(dstSurface);

   SDL_Surface * textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
   assert(textSurface);

   SDL_BlitSurface(textSurface, 0, dstSurface, const_cast<Rect *>(&dstRect));

   SDL_FreeSurface(textSurface);
}

void YobaDraw::fill(SDL_Surface * dstSurface, const Color & color)
{
   assert(dstSurface);

   SDL_FillRect(dstSurface, 0, color.mapRGB(dstSurface->format));
}
