#include "app.hpp"

App::App()
{
   mIsRunning = true;

   mGrid = std::vector<std::vector<int> >(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));

   mColors[0] = Color(0, 0, 0);      // Чёрный
   mColors[1] = Color(225, 25, 25);  // Красный (R)
   mColors[2] = Color(25, 175, 75);  // Зелёный (G)
   mColors[3] = Color(75, 100, 255); // Синий (B)
   mColors[4] = Color(225, 225, 0);  // Жёлтый (Y)
   mColors[5] = Color(125, 50, 125); // Фиолетовый (V)
   mColors[6] = Color(255, 125, 0);  // Оранжевый (O)

   mCurrentStep = 0;
}

int App::exec()
{
   if(!init())
      return 1;

   reset();
   render();

   SDL_Event event;

   while(mIsRunning)
   {
      SDL_WaitEvent(&event);
      if(!onEvent(&event))
         continue;

      loop();
      render();
   }

   cleanup();

   return 0;
}

bool App::init()
{
   if(SDL_Init(SDL_INIT_VIDEO) < 0)
      return false;

   if(!(mScreenSurface = SDL_SetVideoMode(GRID_SIZE * CELL_SIZE + 200, GRID_SIZE * CELL_SIZE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)))
      return false;

   if(!(mIconSurface = YobaDraw::loadImage("res/icon.png")))
      return false;

   SDL_WM_SetIcon(mIconSurface, 0);
   SDL_WM_SetCaption("Заполни это", 0);

   if(TTF_Init() < 0)
      return false;

   if(!(mFont = TTF_OpenFont("res/DejaVuSansMono.ttf", 40)))
      return false;

   return true;
}

void App::cleanup()
{
   TTF_CloseFont(mFont);
   TTF_Quit();

   SDL_FreeSurface(mScreenSurface);
   SDL_Quit();
}

void App::loop()
{
   while(!mNextColors.empty())
   {
      int currentColor = mGrid[0][0];
      int newColor = mNextColors.front();
      mNextColors.pop();

      if(currentColor == newColor)
         continue;

      mCurrentStep++;

      changeColor(0, 0, currentColor, newColor);
   }
}

void App::render() const
{
   YobaDraw::fill(mScreenSurface, Color(0, 0, 0));

   for(int y = 0; y < GRID_SIZE; y++)
      for(int x = 0; x < GRID_SIZE; x++)
         YobaDraw::drawRect(mScreenSurface, Rect(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE), mColors[mGrid[y][x]]);

   const char * letters[] = { "", ":R", ":G", ":B", ":Y", ":V", ":O" };
   for(int i = 1; i < 7; i++)
   {
      YobaDraw::drawRect(mScreenSurface, Rect(GRID_SIZE * CELL_SIZE + 10, 250 + (i * (CELL_SIZE + 20)), CELL_SIZE * 1.3, CELL_SIZE * 1.3), mColors[i]);
      YobaDraw::drawText(mScreenSurface, Rect(GRID_SIZE * CELL_SIZE + 10 + (CELL_SIZE * 1.3 + 5), 250 + (i * (CELL_SIZE + 20)), 0, 0), letters[i], mFont, mColors[i]);
   }

   std::stringstream statusString;
   statusString << "Ход:" << mCurrentStep;

   YobaDraw::drawText(mScreenSurface, Rect(GRID_SIZE * CELL_SIZE + 10, CELL_SIZE, 0, 0), statusString.str(), mFont, mColors[mGrid[0][0]]);

   SDL_Flip(mScreenSurface);
}

bool App::onEvent(SDL_Event * event)
{
   assert(event);

   switch(event->type)
   {
      case SDL_KEYDOWN:
         if(event->key.keysym.sym == SDLK_ESCAPE)
         {
            onExit();
            return false;
         }
         else
         {
            onKeyDown(event->key.keysym.sym);
            return true;
         }

      case SDL_MOUSEBUTTONDOWN:
         switch(event->button.button)
         {
            case SDL_BUTTON_LEFT:
               onLButtonDown(event->button.x, event->button.y);
               break;
         }
         return true;

      case SDL_QUIT:
         onExit();
         return false;
   }

   return false;
}

void App::onKeyDown(SDLKey key)
{
   switch(key)
   {
      case SDLK_r:
         mNextColors.push(1);
         break;
      case SDLK_g:
         mNextColors.push(2);
         break;
      case SDLK_b:
         mNextColors.push(3);
         break;
      case SDLK_y:
         mNextColors.push(4);
         break;
      case SDLK_v:
         mNextColors.push(5);
         break;
      case SDLK_o:
         mNextColors.push(6);
         break;
      default:
         break;
   }
}

void App::onLButtonDown(int x, int y)
{
   x /= CELL_SIZE;
   y /= CELL_SIZE;

   if(x < 0 || y < 0 || x >= GRID_SIZE || y >= GRID_SIZE)
      return;

   mNextColors.push(mGrid[y][x]);
}

void App::onExit()
{
   mIsRunning = false;
}

void App::reset()
{
   for(int y = 0; y < GRID_SIZE; y++)
      for(int x = 0; x < GRID_SIZE; x++)
         mGrid[y][x] = (rand() % 6) + 1;
}

bool App::checkVictory() const
{
   int currentColor = mGrid[0][0];

   for(int y = 0; y < GRID_SIZE; y++)
      for(int x = 0; x < GRID_SIZE; x++)
         if(mGrid[y][x] != currentColor)
            return false;

   return true;
}

void App::changeColor(int x, int y, int currentColor, int newColor)
{
   mGrid[y][x] = newColor;

   // Слева
   if(x > 0 && mGrid[y][x - 1] == currentColor)
      changeColor(x - 1, y, currentColor, newColor);

   // Справа
   if(x < GRID_SIZE - 1 && mGrid[y][x + 1] == currentColor)
      changeColor(x + 1, y, currentColor, newColor);

   // Сверху
   if(y > 0 && mGrid[y - 1][x] == currentColor)
      changeColor(x, y - 1, currentColor, newColor);

   // Снизу
   if(y < GRID_SIZE - 1 && mGrid[y + 1][x] == currentColor)
      changeColor(x, y + 1, currentColor, newColor);
}
