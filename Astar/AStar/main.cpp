#include <iostream>
#include <mapManager.h>
#include <MFPath.h>
using namespace std;

int main()
{
    mapManager * myMap = new mapManager(20,20,true);
    MFPath* pathfinder = new MFPath(myMap);

    pathfinder->findPath(0,19,8,0);
    myMap->drawMap();

    return 0;
}
