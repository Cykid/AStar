#ifndef MAPMANAGER_H
#define MAPMANAGER_H
#include <node.h>
#include <iostream>
#include <list>

class mapManager
{
    public:
        mapManager(int _width, int _height,bool _diagonal);
        virtual ~mapManager();
        int width = 5;
        int height = 5;
        node * tileMap[20][20];
        void drawMap();
        bool diagonal = false;
        void initMap();
    protected:

    private:
};

#endif // MAPMANAGER_H
