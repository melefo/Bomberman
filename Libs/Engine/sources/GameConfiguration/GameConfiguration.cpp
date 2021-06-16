/*
** EPITECH PROJECT, 2021
** B-YEP-400-NAN-4-1-indiestudio-victor.trencic
** File description:
** GameConfiguration
*/

#include "GameConfiguration.hpp"
#include <iostream>

namespace Engine
{
    RayLib::Vector2<int> GameConfiguration::_mapSize = {7, 7};
    int GameConfiguration::_players = 2;
    int GameConfiguration::_enemies = 0;
    bool GameConfiguration::_debugMode = false;
    unsigned int GameConfiguration::_seed = 0;
    bool GameConfiguration::_gameOver = false;
    std::map<int, playerkeys> GameConfiguration::_playerKeys = {};
    TerrainGenerator GameConfiguration::_terrainGenerator = TerrainGenerator(Engine::GameConfiguration::GetPlayers(), Engine::GameConfiguration::GetMapSize().x, Engine::GameConfiguration::GetMapSize().y);

    playerkeys::playerkeys(RayLib::Input input, int key) :
    movementInput(input), actionKey(key)
    {

    }

    playerkeys& GameConfiguration::GetPlayerKeys(int player)
    {
        if (player > _players)
            throw Engine::Exception::EngineException("There are only " + std::to_string(player) + " players");
        if (player < 1)
            throw Engine::Exception::EngineException("Invalid player index");
        return (_playerKeys[player]);
    }

    int GameConfiguration::GetPlayers(void)
    {
        return (_players);
    }

    void GameConfiguration::SetPlayers(int playersTotal)
    {
        //if (_playerKeys.size() != static_cast<std::size_t>(playersTotal))
        //    _playerKeys.resize(playersTotal, playerkeys());
        _players = playersTotal;
    }

    void GameConfiguration::SetPlayerKeys(int player, RayLib::Input& input, int actionKey)
    {
        if (player > _players)
            throw Engine::Exception::EngineException("There are only " + std::to_string(player) + " players");

        if (player < 1)
            throw Engine::Exception::EngineException("Invalid player index:");

        _playerKeys[player] = playerkeys(RayLib::Input(input), actionKey);
    }

    int GameConfiguration::GetEnemies(void)
    {
        return (_enemies);
    }

    void GameConfiguration::SetEnemies(int total)
    {
        _enemies = total;
    }

    bool GameConfiguration::GetDebugMode(void)
    {
        return (_debugMode);
    }

    void GameConfiguration::SetDebugMode(bool mode)
    {
        _debugMode = mode;
    }

    unsigned int GameConfiguration::GetSeed(void)
    {
        return (_seed);
    }

    void GameConfiguration::SetSeed(unsigned int seed)
    {
        _seed = seed;
    }

    bool GameConfiguration::GetGameOver(void)
    {
        return (_gameOver);
    }

    void GameConfiguration::SetGameOver(bool gameOver)
    {
        _gameOver = gameOver;
    }

    RayLib::Vector2<int> GameConfiguration::GetMapSize(void)
    {
        return _mapSize;
    }

    void GameConfiguration::SetMapSize(int x, int y)
    {
        _mapSize.x = x;
        _mapSize.y = y;
    }

    TerrainGenerator &GameConfiguration::GetTerrainGenerator(void)
    {
        return (_terrainGenerator);
    }
}
