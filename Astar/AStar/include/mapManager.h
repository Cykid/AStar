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
        int width = 3;
        int height = 3;
        node * tileMap[5][5];
        void drawMap();
        bool diagonal = false;
        void initMap();
    protected:

    private:
};

#endif // MAPMANAGER_H
