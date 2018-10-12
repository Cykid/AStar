#include "mapManager.h"

mapManager::mapManager(int _width, int _height, bool _diagonal)
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


    this->tileMap[0][18]->walkable = false;
    this->tileMap[1][18]->walkable = false;
    this->tileMap[2][18]->walkable = false;
    this->tileMap[3][18]->walkable = false;
    this->tileMap[4][18]->walkable = false;
    this->tileMap[5][18]->walkable = false;
    this->tileMap[6][18]->walkable = false;
    this->tileMap[7][18]->walkable = false;
    this->tileMap[8][18]->walkable = false;
    this->tileMap[9][18]->walkable = false;
    this->tileMap[10][18]->walkable = false;
    this->tileMap[11][18]->walkable = false;
    this->tileMap[12][18]->walkable = false;
    this->tileMap[13][18]->walkable = false;
    this->tileMap[14][18]->walkable = false;

    this->tileMap[0][5]->walkable = false;
    this->tileMap[1][5]->walkable = false;
    this->tileMap[2][5]->walkable = false;
    this->tileMap[3][5]->walkable = false;
    this->tileMap[4][5]->walkable = false;
    this->tileMap[5][5]->walkable = false;
    this->tileMap[6][5]->walkable = false;
    this->tileMap[7][5]->walkable = false;
    this->tileMap[8][5]->walkable = false;
    this->tileMap[9][5]->walkable = false;
    this->tileMap[10][5]->walkable = false;
    this->tileMap[11][5]->walkable = false;
    this->tileMap[12][5]->walkable = false;
    this->tileMap[13][5]->walkable = false;
    this->tileMap[14][5]->walkable = false;


    this->tileMap[1][8]->walkable = false;
    this->tileMap[2][8]->walkable = false;
    this->tileMap[3][8]->walkable = false;
    this->tileMap[4][8]->walkable = false;
    this->tileMap[5][8]->walkable = false;
    this->tileMap[6][8]->walkable = false;
    this->tileMap[7][8]->walkable = false;
    this->tileMap[8][8]->walkable = false;
    this->tileMap[9][8]->walkable = false;
    this->tileMap[10][8]->walkable = false;
    this->tileMap[11][8]->walkable = false;
    this->tileMap[12][8]->walkable = false;
    this->tileMap[13][8]->walkable = false;
    this->tileMap[14][8]->walkable = false;
    this->tileMap[15][8]->walkable = false;
    this->tileMap[16][8]->walkable = false;
    this->tileMap[17][8]->walkable = false;
    this->tileMap[18][8]->walkable = false;
    this->tileMap[19][8]->walkable = false;




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

void mapManager::initMap()
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
