#include "map.h"

map::map(int _width, int _height)
{
    this->width = _width;
    this->height = _height;

    for(int x = 0; x < this->width; x++)
    {
        for(int y = 0; y < this->height; y++)
        {
            this->tileMap[x][y]=new node(x,y);
        }
    }

    //Unwalkable
    this->tileMap[2][2]->walkable = false;
}

map::~map()
{

}

void map::drawMap()
{
    for(int y = 0; y < this->height; y++)
    {
        for(int x = 0; x < this->width; x++)
        {
            if(this->tileMap[x][y]->walkable == true)
            {
                std::cout<<"[ ]";
            }
            else
            {
                std::cout<<"[#]";
            }
        }
        std::cout<<std::endl;
    }
}
