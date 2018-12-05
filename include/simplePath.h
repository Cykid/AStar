#ifndef SIMPLEPATH_H
#define SIMPLEPATH_H
#include <list>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <windows.h>
#include <future>
#include <string>
#include <fstream>
#include <cstdlib> strtol(s.c_str(),0,10)

class simplePath
{
    public:
        simplePath();
        virtual ~simplePath();


    //Node
    class node{
        public:
            node(int _posX, int _posY);
            virtual ~node();
            int oCost = 1;
            int gCost = 0;
            int hCost = 0;
            int fCost = 0;
            int posX = 0;
            int posY = 0;
            bool walkable = true;
            bool pathTile = false;
            bool startTile = false;
            bool endTile = false;
            bool openTile = false;
            bool closedtile = false;
            node * parent;
            std::list<node*> neighbors;
            int getFcost();
    };

    //Grid of Nodes
    class grid{
        public:
            grid(int _width, int _height,bool _diagonal);
            grid(std::string pathTofile, bool _diagonal);
            virtual ~grid();
            int width = 5;
            int height = 5;
            class node *** tileMap;


            void drawMap();
            bool diagonal = false;
            void initMap();
};

    class navAgent{
        public:
            navAgent(grid * _mapManager);
            virtual ~navAgent();
            class grid * tileMap;

            std::list<class node*>oList;
            std::list<class node*>cList;

            std::list<simplePath::node *> findPath(int startX,int startY,int endX, int endY);
            std::future<std::list<simplePath::node *>> findPathAsync(int _startX, int _startY, int _endX, int _endY);
            std::list<simplePath::node *> buildPath(int _endPosX, int _endPosY);
            void expandNodes(int _endPosX, int _endPosY);
    };


    protected:

    private:
};

#endif // SIMPLEPATH_H
