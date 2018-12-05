#include <simplePath.h>
#include <chrono>
#include <windows.h>



using namespace std::chrono;
int main()
{
     LONGLONG g_Frequency, g_CurentCount, g_LastCount;
     if (!QueryPerformanceFrequency((LARGE_INTEGER*)&g_Frequency))
        std::cout << "Performance Counter nicht vorhanden" << std::endl;

    double messungen[10000];
    double dTimeDiff;




    //Create your Grid
    simplePath::grid * PathGrid = new simplePath::grid("map25x40.txt",true);
    //PathGrid = new simplePath::grid(25,40,false);
    //Give your Pathfinding Object a Navagent
    simplePath::navAgent * navComponent = new simplePath::navAgent(PathGrid);

    for(int i = 0 ; i < 10000 ; i ++){
        QueryPerformanceCounter((LARGE_INTEGER*)&g_CurentCount);
        navComponent->findPath(0,0,23,2);
        QueryPerformanceCounter((LARGE_INTEGER*)&g_LastCount);
        messungen[i] = (((double)(g_LastCount-g_CurentCount))/((double)g_Frequency));
    }
    dTimeDiff = 0.0;
    for(int i = 0; i < 10000; i++){
        dTimeDiff += messungen[i];
    }
    dTimeDiff /= 10000;


    std::cout <<"Duration: "<< dTimeDiff;


    //Show Result
    //PathGrid->drawMap();
    system("Pause");

    return 0;
}
