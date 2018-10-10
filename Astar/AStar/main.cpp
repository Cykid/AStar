#include <iostream>
#include <mapManager.h>
#include <MFPath.h>
using namespace std;

int main()
{
    mapManager * myMap = new mapManager(5,5,true);
    MFPath* pathfinder = new MFPath(myMap);
    myMap->drawMap();

    pathfinder->findPath(0,4,4,0);
    myMap->drawMap();


    return 0;
}
