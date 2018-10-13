#include <simplePath.h>

int main()
{
    //Create your Grid
    simplePath::grid * PathGrid = new simplePath::grid(20,20,true);
    //Give your Pathfinding Object a Navagent
    simplePath::navAgent * navComponent = new simplePath::navAgent(PathGrid);
    //find your path
    navComponent->findPath(0,0,19,19);
    //Show Result
    PathGrid->drawMap();

    return 0;
}
