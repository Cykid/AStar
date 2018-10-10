#include "node.h"
node::node(int _posX, int _posY)
{
    this->posX = _posX;
    this->posY = _posY;

}

node::~node()
{

}

int node::getFcost()
{
    return this->gCost + this->hCost;
}
