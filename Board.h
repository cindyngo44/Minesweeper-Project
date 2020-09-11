//
// Created by Cindy Ngo on 8/4/20.
//
#pragma once
#include <iostream>
#include <vector>

class Board {
    struct Tile{
        bool revealed;
        bool mined;
        bool hasNum;
        bool flagged;
        int num;
        bool checked;

        Tile();
        Tile(bool _revealed, bool _mined, bool _hasNum, bool _flagged, int _num);
    };

    int width = 25;
    int height = 16;
    //initialize board with 1's ad 0's
    std::vector<std::vector<int>> boardLogic;
    //initializes board for numbers to be displayed
    std::vector<std::vector<int>> boardDisplay;

public:
    std::vector<std::vector<Tile>> boardTiles;
    int mineCount = 0;
    Board();
    void BoardShuffle();
    void BoardDisplay();
    void BoardTiles();
    std::vector<std::vector<int>> GetDisplay();

    void testBoard1();
    void testBoard2();
    void testBoard3();
};