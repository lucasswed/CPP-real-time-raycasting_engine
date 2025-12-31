#ifndef MAPLOADER_H
#define MAPLOADER_H
#include <vector>
#include <string>
#include <fstream>

class MapLoader
{
public:
    MapLoader();
    ~MapLoader();

    bool loadMapFromFile(const std::string &filename);
    bool validate_map();

    const std::vector<std::string> &getMapMatrix() const;

private:
    std::vector<std::string> map_matrix;
};

#endif // MAPLOADER_H
