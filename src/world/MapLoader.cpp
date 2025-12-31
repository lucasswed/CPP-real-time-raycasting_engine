#include "MapLoader.h"

MapLoader::MapLoader()
{
}

MapLoader::~MapLoader()
{
}

bool MapLoader::loadMapFromFile(const std::string &filename)
{
    std::string line;
    std::ifstream mapFile(filename);

    if (!mapFile.is_open())
    {
        return false;
    }

    while (getline(mapFile, line))
    {
        this->map_matrix.push_back(line);
    }

    if (mapFile.bad())
    {
        return false;
    }

    mapFile.close();
    return true;
}

const std::vector<std::string> &MapLoader::getMapMatrix() const
{
    return this->map_matrix;
}

bool MapLoader::validate_map()
{
    if (this->map_matrix.empty())
    {
        return false;
    }
    
    // TODO: Add more validation logic
    return true;
}