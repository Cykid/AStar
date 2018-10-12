#include <iostream>
#include <mapManager.h>
#include <MFPath.h>
using namespace std;

int main()
{
    mapManager * myMap = new mapManager(25,25,false);
    MFPath* pathfinder = new MFPath(myMap);

    pathfinder->findPath(0,0,23,23);
    myMap->drawMap();

    return 0;
}
