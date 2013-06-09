#include <cstdlib>
#include <ctime>

#include "app.hpp"

int main()
{
   srand(time(0));

   App app;
   return app.exec();
}
