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
simplePath::grid::grid(std::string pathTofile,bool _diagonal)
{
    std::ifstream infile(pathTofile);
    std::string line;

    std::getline(infile,line);
    this->width = std::atoi(line.c_str());
    std::getline(infile,line);
    this->height = std::atoi(line.c_str());


    this->diagonal = _diagonal;

    this->tileMap = new  node** [this->width];
    for(int x=0; x < this->width; x++)
    {
        this->tileMap[x] = new  node*[this->height] ;
        for(int y = 0; y < this->height; y++)
        {
            this->tileMap[x][y]=new node(x,y);
            std::getline(infile,line);
            this->tileMap[x][y]->walkable = (bool)std::atoi(line.c_str());
        }
    }
    this->initMap();
}

simplePath::grid::grid(int _width, int _height, bool _diagonal)
{
    this->width = _width;
    this->height = _height;
    this->diagonal = _diagonal;

    this->tileMap = new  node** [_width];
    for(int x=0; x < _width; x++)
    {
        this->tileMap[x] = new  node*[_height] ;
        for(int y = 0; y < this->height; y++)
        {
            this->tileMap[x][y]=new node(x,y);
        }
    }

    for(int i = 0; i < 14; i++)
    {
        this->tileMap[4][i]->walkable = false;
    }

    for(int i = 14; i > 0; i--)
    {
        this->tileMap[7][i]->walkable = false;
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
            node * tile = this->tileMap[x][y];
            char tileChar;

            if(!tile->walkable) tileChar = '#';
            else if(tile->pathTile)
            {
                tileChar = 'P';

            }
            else if(tile->closedtile) tileChar = 'c';
            else if(tile->openTile) tileChar = 'o';

            else tileChar = ' ';
            if(tile->startTile) tileChar = 'S';
            if(tile->endTile) tileChar = 'E';

            std::cout<<"["<<tileChar<<"]";
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

            // optimized algorithm to calculate neighbors
            for (int i = -1; i <= 1; i++)
            {
                int nX = x + i;
                // check if nX is inside of the map
                if (nX < 0 || nX >= this->width) continue;
                for (int ii = -1; ii <= 1; ii++)
                {
                    int nY = y + ii;
                    // check if nY is inside the map ||    skip own node    || check if diagonals are allowed
                    if (nY < 0 || nY >= this->height || (ii == 0 && i == 0) || (i * ii != 0 && !this->diagonal)) continue;
                    nbList.push_back(this->tileMap[nX][nY]);
                }
            }
            this->tileMap[x][y]->neighbors = nbList;
        }
    }
}

//navAgent IMPLEMENTATION
simplePath::navAgent::navAgent(grid* _mapManager)
{
    this->tileMap = _mapManager;
}

simplePath::navAgent::~navAgent()
{

}

std::future<std::list<simplePath::node *>> simplePath::navAgent::findPathAsync(int _startX, int _startY, int _endX, int _endY)
{
    std::cout<<_startX<<" "<<_startY<<" "<<_endX<<" "<<_endY<<std::endl;
    //auto t1 = std::async([&]{return this->findPath(_startX,_startY,_endX,_endY);});
   // auto t1 = std::async(&this->findPath,this,_startX,_startY,_endX,_endY);
//    return t1;
}

std::list<simplePath::node *> simplePath::navAgent::findPath(int startX, int startY, int endX, int endY)
{
    //std::cout<<startX<<" "<<startY<<" "<<endX<<" "<<endY<<std::endl;
    std::list<node*> finalPath;
    this->oList.clear();
    this->cList.clear();
    int counter = 0;
    int mapWidth = this->tileMap->width;
    int mapHeigth = this->tileMap->height;
    node * startNode = this->tileMap->tileMap[startX][startY];
    node * endNode = this->tileMap->tileMap[endX][endY];

    startNode->startTile = true;
    startNode->pathTile = true;
    endNode->endTile = true;

    if(startX < 0 || startX >= mapWidth || startY < 0 || startY >= mapHeigth)
    {
        std::cout<<"Start point out of range."<<std::endl;
        return finalPath;
    }
    if(endX < 0 || endX >= mapWidth || endY < 0 || endY >= mapHeigth)
    {
        std::cout<<"End point out of range."<<std::endl;
        return finalPath;
    }

    //Expand first Node
    this->oList.push_back(startNode);
    //Calc first Costs
    startNode->gCost = startNode->oCost;
    startNode->hCost = std::abs(startX - endX) + std::abs(startY - endY);
    while(!this->oList.empty())
    {
        this->expandNodes(endX,endY);
        //this->tileMap->drawMap();
        //Sleep(300);
        //system("cls");
        counter++;
    }

   // std::cout<<"Iterationen :"<<counter<<std::endl;
    //std::cout<<"still alive"<<std::endl;

    finalPath = this->buildPath(endX,endY);
    return finalPath;
}

std::list<simplePath::node *> simplePath::navAgent::buildPath(int _endPosX, int _endPosY)
{
    int count = 0;
    std::list<node*> finalPath;

    node * tmp;
    //Suche Endknoten
    for(std::list<node*>::iterator sIT = this->cList.begin(); sIT != this->cList.end(); sIT++)
    {
        tmp = *sIT;
        if(tmp->posX == _endPosX && tmp->posY == _endPosY) break;
    }

    while(tmp->parent != 0)
    {
        finalPath.push_front(tmp);
        tmp->pathTile = true;
        tmp=tmp->parent;
        count++;
    }

    //std::cout<<"Length: "<<count<<std::endl;
    return finalPath;
}

void simplePath::navAgent::expandNodes(int _endPosX, int _endPosY)
{
    bool nodeChecked;
    this->oList.sort([](node* a, node*b)
    {
        return a->getFcost() < b->getFcost();
    });
    node * currentNode = *(this->oList.begin());
    node * endNode = this->tileMap->tileMap[_endPosX][_endPosY];

    if(currentNode == endNode)
    {
        std::list<node*>::iterator i = std::find(this->oList.begin(),this->oList.end(),currentNode);
        if(i != this->oList.end())
        {
            this->cList.splice(this->cList.end(),this->oList,i);
        }
        this->oList.clear();
        return;
    }

    for(std::list<node*>::iterator nIT = currentNode->neighbors.begin(); nIT != currentNode->neighbors.end(); nIT++)
    {
        node* thisNode = *nIT;
        if(!thisNode->walkable) continue;

        //Check better Path
        if(currentNode->gCost + thisNode->oCost + (abs(thisNode->posX - _endPosX) + abs(thisNode->posY - _endPosY)) < thisNode->getFcost())
        {
            thisNode->parent = currentNode;
        }

        nodeChecked = true;
        //Pr�fe Ob Node schon gepr�ft wurde
        std::list<node*>::iterator findO = std::find(this->oList.begin(),this->oList.end(),thisNode);
        std::list<node*>::iterator findC = std::find(this->cList.begin(),this->cList.end(),thisNode);
        if(findO == this->oList.end() && findC == this->cList.end()) nodeChecked = false;

        if(!nodeChecked)
        {
            this->oList.push_back(*nIT);
            thisNode->openTile = true;
            thisNode->parent = currentNode;
            thisNode->gCost = thisNode->oCost + thisNode->parent->gCost;
            thisNode->hCost = abs(thisNode->posX - _endPosX) + abs(thisNode->posY - _endPosY);
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

