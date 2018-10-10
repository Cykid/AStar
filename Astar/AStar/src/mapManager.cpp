#include "mapManager.h"

mapManager::mapManager(int _width, int _height, bool _diagonal)
{
    this->width = _width;
    this->height = _height;
    this->diagonal = _diagonal;

    for(int x = 0; x < this->width; x++)
    {
        for(int y = 0; y < this->height; y++)
        {
            this->tileMap[x][y]=new node(x,y);
        }
    }

    this->tileMap[0][0]->walkable = false;
    this->tileMap[1][0]->walkable = false;
    this->tileMap[0][1]->walkable = false;
    this->tileMap[2][2]->walkable = false;
    this->tileMap[2][1]->walkable = false;
    this->tileMap[2][0]->walkable = false;


    this->initMap();
}

mapManager::~mapManager()
{

}

void mapManager::drawMap()
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

void mapManager::initMap()
{
    for(int x = 0 ; x < this->width; x++)
    {
        for(int y = 0; y < this->height; y++)
        {
            std::list<node*> nbList;
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
