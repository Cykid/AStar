#include <iostream>
#include <mapManager.h>
#include <MFPath.h>
using namespace std;

int main()
{
    mapManager * myMap = new mapManager(5,5,false);
    MFPath* pathfinder = new MFPath(myMap);
    myMap->drawMap();

    pathfinder->findPath(1,2,1,2);


    return 0;
}
