#include "simplePath.h"

simplePath::simplePath()
{
    //ctor
}

simplePath::~simplePath()
{
    //dtor
}

//NODE IMPLEMENTATION
simplePath::node::node(int _posX, int _posY)
{
    this->posX = _posX;
    this->posY = _posY;
    this->parent = 0;
}

simplePath::node::~node()
{

}

int simplePath::node::getFcost()
{
    return this->gCost + this->hCost;
}


//GRID IMPLEMENTATION

simplePath::grid::grid(int _width, int _height, bool _diagonal)
{
    this->width = _width;
    this->height = _height;
    this->diagonal = _diagonal;

    this->tileMap = new  node** [_width];
    for(int x=0; x < _width;x++)
    {
        this->tileMap[x] = new  node*[_height] ;
        for(int y = 0; y < this->height; y++)
        {
            this->tileMap[x][y]=new node(x,y);
        }
    }

    this->initMap();
}

simplePath::grid::~grid()
{

}

void simplePath::grid::drawMap()
{
    for(int y = 0; y < this->height; y++)
    {
        for(int x = 0; x < this->width; x++)
        {
            if(this->tileMap[x][y]->walkable == true)
            {
                if(this->tileMap[x][y]->pathTile == true){
                    if(this->tileMap[x][y]->startTile == true)
                    {
                        std::cout<<"[S]";
                    }
                    else if(this->tileMap[x][y]->endTile == true){
                        std::cout<<"[E]";
                    }
                    else
                    {
                        std::cout<<"[P]";
                    }
                }
                else if(this->tileMap[x][y]->closedtile == true)
                {
                    //std::cout<<"["<<tileMap[x][y]->getFcost()<<"]";
                    std::cout<<"[c]";
                }
                else if(this->tileMap[x][y]->openTile == true)
                {
                    std::cout<<"[o]";
                }
                else{
                    std::cout<<"[ ]";
                }

            }
            else
            {
                std::cout<<"[#]";
            }
        }
        std::cout<<std::endl;
    }

}

void simplePath::grid::initMap()
{
    for(int x = 0 ; x < this->width; x++)
    {
        for(int y = 0; y < this->height; y++)
        {
            std::list<node*> nbList;
            nbList.clear();
            int nX = 0;
            int nY = 0;
            //Oben
            nX = x;
            nY = y -1;
            if(nX >= 0 && nX < this->width && nY >= 0 && nY < this->height)
            {
                nbList.push_back(this->tileMap[nX][nY]);
            }
            //Rechts
            nX = x+1;
            nY = y;
            if(nX >= 0 && nX < this->width && nY >= 0 && nY < this->height)
            {
                nbList.push_back(this->tileMap[nX][nY]);
            }
            //unten
            nX = x;
            nY = y +1;
            if(nX >= 0 && nX < this->width && nY >= 0 && nY < this->height)
            {
                nbList.push_back(this->tileMap[nX][nY]);
            }
            //links
            nX = x -1;
            nY = y;
            if(nX >= 0 && nX < this->width && nY >= 0 && nY < this->height)
            {
                nbList.push_back(this->tileMap[nX][nY]);
            }

            if(this->diagonal==true)
            {
                nX = x +1;
                nY = y -1;
                if(nX >= 0 && nX < this->width && nY >= 0 && nY < this->height)
                {
                    nbList.push_back(this->tileMap[nX][nY]);
                }

                nX = x +1;
                nY = y +1;
                if(nX >= 0 && nX < this->width && nY >= 0 && nY < this->height)
                {
                    nbList.push_back(this->tileMap[nX][nY]);
                }

                nX = x -1;
                nY = y +1;
                if(nX >= 0 && nX < this->width && nY >= 0 && nY < this->height)
                {
                    nbList.push_back(this->tileMap[nX][nY]);
                }

                nX = x -1;
                nY = y -1;
                if(nX >= 0 && nX < this->width && nY >= 0 && nY < this->height)
                {
                    nbList.push_back(this->tileMap[nX][nY]);
                }

            }

            this->tileMap[x][y]->neighbors = nbList;

        }
    }

}


//navAgent Implemention

simplePath::navAgent::navAgent(grid* _mapManager)
{
    this->tileMap = _mapManager;
}

simplePath::navAgent::~navAgent()
{

}

std::list<simplePath::node *> simplePath::navAgent::findPath(int startX, int startY, int endX, int endY)
{
    std::list<node*> finalPath;
    this->oList.clear();
    this->cList.clear();
    int counter = 0;

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

                //this->tileMap->drawMap();


                //Sleep(300);
                //system("cls");
                counter++;
            }

            std::cout<<"Iterationen :"<<counter<<std::endl;

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



std::list<simplePath::node *> simplePath::navAgent::buildPath(int _endPosX, int _endPosY)
{
    int count = 0;
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


    while(tmp->parent != 0)
    {
        finalPath.push_front(tmp);
        tmp->pathTile = true;
        tmp=tmp->parent;
        count++;
    }

    std::cout<<"Length: "<<count<<std::endl;
    return finalPath;

}

void simplePath::navAgent::expandNodes(int _endPosX, int _endPosY)
{
    bool nodeChecked;
    this->oList.sort([](node* a, node*b){return a->getFcost() < b->getFcost();});
    node * currentNode = *(this->oList.begin());

    if(currentNode->posX == _endPosX && currentNode->posY == _endPosY)
    {
        std::list<node*>::iterator i = std::find(this->oList.begin(),this->oList.end(),currentNode);
        if(i != this->oList.end())
        {
            this->cList.splice(this->cList.end(),this->oList,i);
        }
        this->oList.clear();

        return;
    }
    else
    {
        for(std::list<node*>::iterator nIT = currentNode->neighbors.begin(); nIT != currentNode->neighbors.end(); nIT++){
            node* thisNode = *nIT;
            //Check better Path
            if(currentNode->gCost + thisNode->oCost + (abs(thisNode->posX - _endPosX) + abs(thisNode->posY - _endPosY)) < thisNode->getFcost())
            {
                thisNode->parent = currentNode;
            }

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
                    thisNode->openTile = true;
                    thisNode->parent = currentNode;
                    thisNode->gCost = thisNode->oCost + thisNode->parent->gCost;
                    thisNode->hCost = abs(thisNode->posX - _endPosX) + abs(thisNode->posY - _endPosY);
                }
            }
        }
    }

    //Pack CurrentNode in die ClosedList
    std::list<node*>::iterator i = std::find(this->oList.begin(),this->oList.end(),currentNode);
    if(i != this->oList.end())
    {
        node * ac = *i;
        ac->closedtile = true;
        this->cList.splice(this->cList.end(),this->oList,i);
    }
}

