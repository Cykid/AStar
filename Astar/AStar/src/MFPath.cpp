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
    std::cout<<"Expande nodes"<<std::endl;
    bool nodeChecked;
    node * tmp;
    this->oList.sort([](node* a, node*b){return a->getFcost() < b->getFcost();});
    node * currentNode = *(this->oList.begin());
    std::cout<<"Liste Sortiert OList"<<std::endl;


    for(std::list<node*>::iterator nIT = currentNode->neighbors.begin(); nIT != currentNode->neighbors.end(); nIT++){
        node* thisNode = *nIT;
        std::cout<<"Betrachte Nachbar: PosX = "<<thisNode->posX<<"\t PosY = "<<thisNode->posY<<std::endl;
        if(thisNode->walkable == true)
        {
            std::cout<<"Auf Nachbar kann gelaufen werden"<<std::endl;
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
                std::cout<<"Nachbar wird in der Open List hinzugefügt"<<std::endl;
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
        std::cout<<"Aktueller Node wird in die Closed List gepackt"<<std::endl;
        this->cList.splice(this->cList.end(),this->oList,i);
    }

    std::cout<<"Aktuelle  Open List"<<std::endl;
    for(std::list<node*>::iterator sIT = this->oList.begin(); sIT != this->oList.end(); sIT++){
        tmp = *sIT;
        std::cout<<"Pos X :"<<tmp->posX<<"\t Pos Y :"<<tmp->posY<<std::endl;
    }

    std::cout<<"Aktuelle  Closed List"<<std::endl;
    for(std::list<node*>::iterator sIT = this->cList.begin(); sIT != this->cList.end(); sIT++){
        tmp = *sIT;
        std::cout<<"Pos X :"<<tmp->posX<<"\t Pos Y :"<<tmp->posY<<std::endl;
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


