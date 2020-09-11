//
// Created by Cindy Ngo on 8/3/20.
//
#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Board.h"

using std::vector;
class Program{
    //=======Board States=======
    Board board;
    bool win = false;
    bool neutral = true;
    bool lose = false;
    bool debug = false;

    //=======Textures=======
    sf::Sprite DebugSprite;
    sf::Sprite DigitsSprite;
    sf::Sprite FaceHappySprite;
    sf::Sprite FaceLoseSprite;
    sf::Sprite FaceWinSprite;
    sf::Sprite Test1Sprite;
    sf::Sprite Test2Sprite;
    sf::Sprite Test3Sprite;
    sf::Sprite TileRevealedSprite;
    sf::Sprite FlagSprite;
    sf::Sprite MineSprite;
    sf::Sprite Number1Sprite;
    sf::Sprite Number2Sprite;
    sf::Sprite Number3Sprite;
    sf::Sprite Number4Sprite;
    sf::Sprite Number5Sprite;
    sf::Sprite Number6Sprite;
    sf::Sprite Number7Sprite;
    sf::Sprite Number8Sprite;
    sf::Sprite TileHiddenSprite;

    //Tile Layers
    vector<sf::Sprite> baseTiles;
    vector<sf::Sprite> contentTiles;
    sf::Sprite HiddenTilesTemp[16][25];
    sf::Sprite *HiddenTiles[16][25];
    sf::Sprite WinFlagsTemp[16][25];
    sf::Sprite *WinFlags[16][25];
    vector<sf::Sprite> CounterTiles;
    vector<sf::Sprite> DebugTiles;
    vector<sf::Sprite> flaggedTiles;
    vector<sf::Sprite> LosingTiles;
    vector<sf::Sprite> WinningTiles;

    //Counters
    int mines;
    int flags;

    sf::RenderWindow* mainWindow;
    void LoadSprites(sf::RenderWindow& window);
    void DrawStaticUI();
public:
    void Initialize(sf::RenderWindow& window);
    void LeftMouseClick(sf::Vector2i& mousePosition);
    void RightMouseClick(sf::Vector2i& mousePosition);
    void CheckWinLose();
    void Shutdown();

    void Draw();
    void DrawContent();
    void DrawALLHidden();
    void RevealRecursion(int _x, int _y);
    void DrawFlagged(sf::Vector2i &mousePosition);
    void DrawDebug();

    void LosingInterface();
    void WinningInterface();
    void Counter();

    bool CheckWin();
};
