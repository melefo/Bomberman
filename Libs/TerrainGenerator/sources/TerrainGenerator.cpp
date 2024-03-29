/*
** EPITECH PROJECT, 2021
** temp
** File description:
** TerrainGenerator
*/

#include "TerrainGenerator.hpp"
#include <map>
#include <cstdlib>
#include <algorithm>
#include <iostream>

TerrainGenerator::TerrainGenerator(int playersNbr, const MapType mapType, int boxPercentage)
    : _playersNbr(playersNbr % 2 == 0 ? playersNbr : playersNbr+1), _boxPercentage(boxPercentage),
    _height(13), _mapType(mapType), _map(_height), _isGenerated(false)
{
    _playersNbr = _playersNbr < 2 ? 2 : _playersNbr;
    _playersNbr = _playersNbr > 8 ? 8 : _playersNbr;
    std::map<int, int> mapSizes = {
        {2, 13},
        {4, 15},
        {6, 17},
        {8, 19}
    };

    _width = mapSizes[_playersNbr];
    generateMap();
}

TerrainGenerator::TerrainGenerator(int playersNbr, int width, int height, const MapType mapType, int boxPercentage)
    : _playersNbr(playersNbr), _boxPercentage(boxPercentage), _height(height), _width(width), _mapType(mapType), _map(_height), _isGenerated(false)
{
    //generateMap();
}

/**
 * Getters
 */

const std::vector<std::string>& TerrainGenerator::getMap() const
{
    return _map;
}

/**
 * Public
 */

void TerrainGenerator::displayMap()
{
    for (auto it = _map.begin(); it != _map.end(); it++)
        std::cout << *it << std::endl;
}

void TerrainGenerator::generateBaseMap(int seed)
{
    int index = 0;

    clearMap();
    if (seed != -1)
        std::srand(seed);
    for (; index < _height; index++)
        _map[index] = std::string(_width, static_cast<char>(mapTexture::OWALL));
    index = 0;
    for (auto &it : _map) {
        if (index == 0 || index == _height - 1)
            it = std::string(_width, static_cast<char>(mapTexture::OWALL));
        else
            it = generateMapLine(index);
        index++;
    }
    _isGenerated = true;
}

void TerrainGenerator::generateRandomMap(int seed)
{
    int index = 0;
    static std::vector<std::vector<std::string>> tiles = {
        {
            {"***xx"},
            {"*o*xx"},
            {"*o***"},
            {"*ooo*"},
            {"*o***"},
            {"*o*xx"},
            {"***xx"}
        },{
            {"******"},
            {"*oooo*"},
            {"*o****"},
            {"*o*xxx"},
            {"***xxx"}
        },{
            {"x***x"},
            {"**o**"},
            {"*ooo*"},
            {"**o**"},
            {"x***x"}
        },{
            {"*****xx"},
            {"*ooo*xx"},
            {"***o***"},
            {"xx*ooo*"},
            {"xx*****"}
        },{
            {"***"},
            {"*o*"},
            {"*o*"},
            {"*o*"},
            {"***"}
        }
    };

    if (seed != -1)
        std::srand(seed);
    for (auto &it : _map) {
        it.clear();
        if (index == 0 || index == _height-1)
            it = std::string(_width, static_cast<char>(mapTexture::OWALL));
        else {
            it = static_cast<char>(mapTexture::OWALL);
            it += std::string(_width-2, ' ');
            it += static_cast<char>(mapTexture::OWALL);
        }
        index++;
    }
    while (!isMapFull()) {
        if (!addTetrOnMap(tiles))
            break;
    }
    //fillHoles();
    trimMap();
    cloneReverseMap();
    _isGenerated = true;
}

void TerrainGenerator::clearMap()
{
    int index = 0;

    for (auto &it : _map) {
        it.clear();
        if (index == 0 || index == _height-1) {
            it = std::string(_width, static_cast<char>(mapTexture::OWALL));
        } else {
            it += static_cast<char>(mapTexture::OWALL);
            it += std::string(_width-2, ' ');
            it += static_cast<char>(mapTexture::OWALL);
        }
        index++;
    }
    _isGenerated = false;
}

void TerrainGenerator::addTileOnMap(int y, int x)
{
    _map[y][x] = static_cast<char>(mapTexture::INWALL);
}

void TerrainGenerator::generateXMLFile()
{
    //XMLGenerator xmlFile(_map);
}

void TerrainGenerator::setPlayersNumber(int newSize) 
{
    _playersNbr = newSize;
}

void TerrainGenerator::setMapSize(RayLib::Vector2<int> mapSize)
{
    this->_height = mapSize.y;
    this->_width = mapSize.x;
    this->_map.resize(mapSize.y);
}

void TerrainGenerator::SetIsGenerated(bool value)
{
    this->_isGenerated = value;
}

/**
 * Private
 */

void TerrainGenerator::placePlayers()
{
    _map[1][1] = static_cast<char>(mapTexture::PLAYER);
    _map[_height-2][_width-2] = static_cast<char>(mapTexture::PLAYER);
    if (_playersNbr > 2) {
        _map[1][_width-2] = static_cast<char>(mapTexture::PLAYER);
        _map[_height-2][1] = static_cast<char>(mapTexture::PLAYER);
    }
    if (_playersNbr > 4) {
        _map[1][_width/2] = static_cast<char>(mapTexture::PLAYER);
        _map[_height-2][_width/2] = static_cast<char>(mapTexture::PLAYER);
    }
    if (_playersNbr > 6) {
        _map[_height/2][1] = static_cast<char>(mapTexture::PLAYER);
        _map[_height/2][_width-2] = static_cast<char>(mapTexture::PLAYER);
    }
    makeSpaceForPlayers();
}

char TerrainGenerator::generateBoxLevel()
{
    int twoPercentage = 50;
    int threePercentage = 20;

    if (std::rand() % 100 + 1 < threePercentage)
        return static_cast<char>(mapTexture::STRONGBOX);
    else if (std::rand() % 100 + 1 < twoPercentage)
        return static_cast<char>(mapTexture::MEDIUMBOX);
    return static_cast<char>(mapTexture::WEAKBOX);
}

void TerrainGenerator::generateBoxes()
{
    for (std::vector<std::string>::iterator it = _map.begin()+1; it != _map.end()-1; it++) {
        for (std::size_t index = 1; index != it->length()-1; index++) {
            if ((*it)[index] == ' ')
                (*it)[index] = std::rand() % 100+1 < _boxPercentage ? generateBoxLevel() : ' ';
        }
    }
}

void TerrainGenerator::generateMap()
{
    std::srand(static_cast<unsigned int>(time(NULL)));

    if (_mapType == MapType::Basic)
        generateBaseMap(0);
    else if (_mapType == MapType::Random)
        generateRandomMap(0);
    else {
        if (std::rand() % 3 == 0)
            generateBaseMap(0);
        else
            generateRandomMap(0);
    }
    generateBoxes();
    placePlayers();
}

/**
 * Private - Basic Map
 */

std::string TerrainGenerator::generateMapLine(int hPos)
{
    std::string result;

    result += static_cast<char>(mapTexture::OWALL);
    if (hPos % 2 == 0) {
        for (int index = 1; index < _width - 1; index++) {
            if (index % 2 == 0)
                result += static_cast<char>(mapTexture::INWALL);
            else
                result += ' ';
        }
    } else {
        for (int index = 1; index < _width - 1; index++)
            result += ' ';
    }
    result += static_cast<char>(mapTexture::OWALL);
    return result;
}

/**
 * Private - Random Map
 */

void TerrainGenerator::cloneReverseMap()
{
    int index = 0;
    std::string tempString;

    for (auto &it : _map) {
        if (index != 0 && index < _height - 1) {
                tempString = std::string(it.rbegin() + 1, it.rend() - 1);
            // tempString.erase(0, 2); si problème rencontré debug e tenvisager de décommanter cette ligne
            tempString += static_cast<char>(mapTexture::OWALL);
            it += tempString;
        } else {
            it += std::string(_width/2, static_cast<char>(mapTexture::OWALL));
        }
        index++;
    }
}

bool TerrainGenerator::blocksPath(int y, int x)
{
    if ((_map[y-1][x-1] != ' '
    && _map[y-1][x] == ' '
    && _map[y-1][x+1] != ' ')
    || (_map[y][x-1] != ' '
    && _map[y][x] == ' '
    && _map[y][x+1] != ' ')
    || (_map[y+1][x-1] != ' '
    && _map[y+1][x] == ' '
    && _map[y+1][x+1] != ' ')
    || (_map[y-1][x-1] != ' '
    && _map[y][x-1] == ' '
    && _map[y+1][x-1] != ' ')
    || (_map[y-1][x] != ' '
    && _map[y][x] == ' '
    && _map[y+1][x] != ' ')
    || (_map[y-1][x+1] != ' '
    && _map[y][x+1] == ' '
    && _map[y+1][x+1] != ' '))
        return true;
    return false;
}

void TerrainGenerator::fillHoles()
{
    for (int y = 0; y < _height-1; y++) {
        for (int x = 0; x < _width-1; x++) {
            if (_map[y][x] == ' ' && !blocksPath(y, x))
                _map[y][x] = static_cast<char>(mapTexture::INWALL);
        }
    }
}

bool TerrainGenerator::tryPlacingTile(const std::vector<std::string> &tile, int mapPos)
{
    int tileWidth = static_cast<int>(tile[0].size());
    int tileHeight = static_cast<int>(tile.size());
    bool mayPlaceIt = false;
    size_t offset = 0;

    for (; !mayPlaceIt && offset < _map.size()/2;) {
        mayPlaceIt = true;
        for (int y = 0; y < tileHeight && mayPlaceIt; y++) {
            for (int x = 0; x < tileWidth && mayPlaceIt; x++) {
                if (tile[y][x] != 'x') {
                    if (_map[mapPos+y][offset+x] != ' ')
                        mayPlaceIt = false;
                }
            }
        }
        if (!mayPlaceIt)
            offset++;
    }
    if (!mayPlaceIt && offset >= _map.size()/2)
        return false;
    for (int y = 0; y < tileHeight; y++) {
        for (int x = 0; x < tileWidth; x++) {
            if (tile[y][x] == 'o')
                _map[mapPos+y][offset+x] = tile[y][x];
        }
    }
    return true;
}

std::vector<std::string> TerrainGenerator::rotateTile(std::vector<std::string> rotatedTile) const
{
    std::vector<std::string> tempTile(rotatedTile[0].size());

    for (size_t x = 0; x < rotatedTile[0].size(); x++)
        for (size_t y = 0; y < rotatedTile.size(); y++)
            tempTile[x].insert(0, 1, rotatedTile[y][x]);
    rotatedTile = tempTile;
    tempTile.clear();
    return rotatedTile;
}

bool TerrainGenerator::tryTetrPositions(const std::vector<std::string> &chosenTile)
{
    bool tetrPlaced = false;

    for (int tilePosition = 1; tilePosition < _height-1 && !tetrPlaced; tilePosition++)
        tetrPlaced = tryPlacingTile(chosenTile, tilePosition);
    return tetrPlaced;
}

bool TerrainGenerator::addTetrOnMap(const std::vector<std::vector<std::string>> &tiles)
{
    size_t baseId = std::rand() % tiles.size();
    std::vector<std::string> chosenTile;
    bool tetrPlaced = false;

    for (size_t tileId = baseId+1; tileId != baseId && !tetrPlaced; tileId++) {
        if (tileId == tiles.size()) {
            if (baseId == 0)
                break;
            else
                tileId = 0;
        }
        chosenTile = tiles[tileId];
        for (int rotate = 0; rotate < 4 && !tetrPlaced; rotate++) {
            if (rotate != 0)
                chosenTile = rotateTile(chosenTile);
            tetrPlaced = tryTetrPositions(chosenTile);
        }
    }
    return tetrPlaced;
}

size_t TerrainGenerator::lineGetWidth(int linePos)
{
    size_t index = _map[linePos].size();

    for (std::string::reverse_iterator it = _map[linePos].rbegin(); it != _map[linePos].rend(); it++) {
        if (index != _map[linePos].size() && *it != ' ')
            return index;
        index--;
    }
    return index;
}

bool TerrainGenerator::isMapFull()
{
    size_t maxSize = _width/2;
    int counter = 0;
    int index = 0;

    for (auto it = _map.begin(); it != _map.end(); it++) {
        if (index > 0 && index < _height-1 && lineGetWidth(static_cast<int>(it-_map.begin())) >= maxSize)
            counter++;
        index++;
    }
    if (counter > 5)
        return true;
    return false;
}

void TerrainGenerator::trimMap()
{
    for (auto &it : _map)
        if (it.size() > static_cast<size_t>(_width/2+1))
            it = it.substr(0, _width/2+1);
}

void TerrainGenerator::makeSpaceForPlayers()
{
    for (size_t y = 1; y < _map.size()-1; y++) {
        for (size_t x = 1; x < _map[y].size(); x++) {
            if (_map[y][x] == 'P') {
                if (_map[y-1][x] != static_cast<char>(mapTexture::OWALL))
                    _map[y-1][x] = ' ';
                if (_map[y+1][x] != static_cast<char>(mapTexture::OWALL))
                    _map[y+1][x] = ' ';
                if (_map[y][x-1] != static_cast<char>(mapTexture::OWALL))
                    _map[y][x-1] = ' ';
                if (_map[y][x+1] != static_cast<char>(mapTexture::OWALL))
                    _map[y][x+1] = ' ';
            }
        }
    }
}

bool TerrainGenerator::isGenerated()
{
    return _isGenerated;
}

void TerrainGenerator::SetMap(std::vector<std::string> map)
{
    _isGenerated = true;
    _map = map;
}
