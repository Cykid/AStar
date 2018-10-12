#ifndef NODE_H
#define NODE_H
#include <list>

class node
{
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
    protected:

    private:
};

#endif // NODE_H
