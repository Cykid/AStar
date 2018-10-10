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
    std::list<node*> finalPath;
    this->oList.clear();
    this->cList.clear();

    this->tileMap->tileMap[startX][startY]->startTile = true;
    this->tileMap->tileMap[startX][startY]->pathTile = true;
    this->tileMap->tileMap[endX][endY]->endTile = true;

    if(startX >= 0 && startX < this->tileMap->width && startY >= 0 && startY < this->tileMap->height)
    {
        if(endX >= 0 && endX < this->tileMap->width && endY >= 0 && endY < this->tileMap->height)
        {
            //Expand first Node
            this->oList.push_back(this->tileMap->tileMap[startX][startY]);
            //Calc first Costs
            this->tileMap->tileMap[startX][startY]->gCost = this->tileMap->tileMap[startX][startY]->oCost;
            this->tileMap->tileMap[startX][startY]->hCost = std::abs(startX - endX) + std::abs(startY - endY);
            while(!this->oList.empty())
            {
                this->expandNodes(endX,endY);
            }



            this->buildPath(endX,endY);
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

    return finalPath;
}

void MFPath::expandNodes(int _endPosX, int _endPosY)
{

    bool nodeChecked;
    node * tmp;
    this->oList.sort([](node* a, node*b){return a->getFcost() < b->getFcost();});
    node * currentNode = *(this->oList.begin());

    for(std::list<node*>::iterator nIT = currentNode->neighbors.begin(); nIT != currentNode->neighbors.end(); nIT++){
        node* thisNode = *nIT;
        if(thisNode->walkable == true)
        {
            nodeChecked = true;
            //Prüfe Ob Node schon geprüft wurde
            std::list<node*>::iterator findO = std::find(this->oList.begin(),this->oList.end(),thisNode);
            if(findO == this->oList.end())
            {
                std::list<node*>::iterator findC = std::find(this->cList.begin(),this->cList.end(),thisNode);
                if(findC == this->cList.end())
                {
                    nodeChecked = false;
                }
            }



            if(nodeChecked==false){
                this->oList.push_back(*nIT);
                thisNode->parent = currentNode;
                thisNode->gCost = thisNode->oCost + thisNode->parent->gCost;
                thisNode->hCost = abs(thisNode->posX - _endPosX) + abs(thisNode->posY - _endPosY);
            }
        }
    }
    //Pack CurrentNode in die ClosedList
    std::list<node*>::iterator i = std::find(this->oList.begin(),this->oList.end(),currentNode);
    if(i != this->oList.end())
    {
        this->cList.splice(this->cList.end(),this->oList,i);
    }

}

std::list<node*> MFPath::buildPath(int _endPosX, int _endPosY)
{
    std::list<node*> finalPath;

    node * tmp;
    //Suche Endknoten
    for(std::list<node*>::iterator sIT = this->cList.begin(); sIT != this->cList.end(); sIT++){
        tmp = *sIT;
        if(tmp->posX == _endPosX && tmp->posY == _endPosY)
        {
            break;

        }
    }


    while(tmp->parent != nullptr)
    {
        finalPath.push_front(tmp);
        tmp->pathTile = true;
        tmp=tmp->parent;
    }


    return finalPath;
}


