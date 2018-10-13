# [C++] A* Class
A simple class collection to realize pathfinding.

## Status
The collection is currently under development. Important functions such as converting 2D arrays into pathfinding grids are still missing, as well as the implementation in a single class.

## ToDo:

 - Wrap code into one class
 - Situation-dependent heuristic
 - Algorithm optimization
 - 2D Array into grid 
 - Memoryleak fixing
 
 ## Features
- If there is a way, it will be found
- Optionally, diagonal pathfinding can be allowed

## Thanks to
- Flo 
- Lars

## Usage

```cpp
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
```

 

