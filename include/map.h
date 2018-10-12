#ifndef MAP_H
#define MAP_H

#include <node.h>
#include <iostream>

class map
{
    public:
        map(int _width, int _height);
        virtual ~map();
        int width = 3;
        int height = 3;
        node * tileMap[5][5];
        void drawMap();
    protected:

    private:
};

#endif // MAP_H
