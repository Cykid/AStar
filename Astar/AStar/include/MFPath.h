#ifndef MFPATH_H
#define MFPATH_H
#include <mapManager.h>
#include <node.h>

#include <iostream>
#include <list>
class MFPath
{
    public:
        MFPath(mapManager * _mapManager);
        mapManager * tileMap;
        virtual ~MFPath();

        std::list<node*>oList;
        std::list<node*>cList;

        std::list<node*> findPath(int startX,int startY,int endX, int endY);

        void expandNodes();


    protected:

    private:
};

#endif // MFPATH_H
