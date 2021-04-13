#include <iostream>
#include <SDL.h>
#include "Screen.h"

using namespace std;
using namespace scr;

int main(int argc, char* argv[])
{
     Screen sc1;
     if (!sc1.init())
         cout << "Initialization failed !!!" << endl;
     else
         cout << "Initialization succesfull !" << endl;
    
     //game loop
    while (true)
    {
        //update particles
        //draw particle
        //check for events (mouse clicks, events)
        if (!sc1.processEvents())
            break;
       
    }
    sc1.close();
    return 0;
}
