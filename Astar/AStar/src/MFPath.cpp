#include "MFPath.h"

MFPath::MFPath(mapManager* _mapManager)
{
    this->tileMap = _mapManager;
}

MFPath::~MFPath()
{

}

std::list<node*> MFPath::findPath(int startX, int startY, int endX, int endY)
{
    this->tileMap->drawMap();
    if(startX >= 0 && startX < this->tileMap->width && startY >= 0 && startY < this->tileMap->height)
    {
        if(endX >= 0 && endX < this->tileMap->width && endY >= 0 && endY < this->tileMap->height)
        {
            //Expand first Node

            //this->oList.push_back(this->tileMap->tileMap[startX][startY]);
            //std::cout<<"In der Liste"<<std::endl;
            //this->expandNodes();
        }
        else
        {
            std::cout<<"End Punkt out of Range"<<std::endl;
        }
    }
    else
    {
            std::cout<<"End Punkt out of Range"<<std::endl;
    }
}

void MFPath::expandNodes()
{
    //std::list<node*>::iterator nodeIT;
    //this->oList.sort([](node* a, node*b){return a->fCost < b->fCost;});
    //nodeIT = this->oList.begin();


}
