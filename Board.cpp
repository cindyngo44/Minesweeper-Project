//
// Created by Cindy Ngo on 8/4/20.
//
#include <fstream>
#include "Board.h"
#include "Random.h"
Board::Board() {
    BoardShuffle();
}

void Board::BoardShuffle() {
    boardLogic.clear();
    mineCount = 0;

    //"empty" vector of board size (no mines)
    for (int i = 0; i < height; i++) {
        std::vector<int> vec;
        for (int j = 0; j < width; j++) {
            vec.push_back(0);
        }
        boardLogic.push_back(vec);
        boardDisplay.push_back(vec);
    }
    //randomly add 50 mines by accessing random x,y locations of "empty" boardLogic
    while (mineCount < 50){
        int randomHeight = Random::Number(0, 24);
        int randomWidth = Random::Number(0, 15);
        //if already 1, skip
        if (boardLogic[randomWidth][randomHeight] == 1){
        }
        else{
            boardLogic[randomWidth][randomHeight] = 1;
            mineCount++;
        }
    }
    //print out vector and correctly count how many mines
    /*for (int i = 0; i < boardVector.size(); i++) {
        for (int j = 0; j < boardVector[i].size(); j++)
            std::cout << boardVector[i][j];
            std::cout << std::endl;
    }
    int counter = 0;
    for (int i = 0; i < boardVector.size(); i++) {
        for (int j = 0; j < boardVector[i].size(); j++)
            if(boardVector[i][j] == 1){
                counter++;
            }
    }
    std::cout << counter << std::endl;*/
    BoardDisplay();
}
void Board::BoardDisplay() {
    for (int i = 0; i < boardLogic.size(); i++) {
        for (int j = 0; j < boardLogic[i].size(); j++){
            int bombCount = 0;
            //creating the numbers + mines + empty tiles for the board via 0-9
            //checking neighbors + conditions in BoardLogic
            if((i != 0) && (j != 0) && (boardLogic[i - 1] [j - 1] == 1)){ //top left
                bombCount++;
            }
            if((i != 0) && (boardLogic[i - 1] [j] == 1)){ //top mid
                bombCount++;
            }
            if((i != 0) && (j != 24) && (boardLogic[i - 1] [j + 1] == 1)){ //top right
                bombCount++;
            }
            if((j != 0) && (boardLogic[i] [j - 1] == 1)){ //mid left
                bombCount++;
            }
            if((j != 24) && (boardLogic[i] [j + 1] == 1)){ //mid right
                bombCount++;
            }
            if((i != 15) && (j != 0) && (boardLogic[i + 1] [j - 1] == 1)){ //bot left
                bombCount++;
            }
            if((i != 15) && (boardLogic[i + 1] [j] == 1)){ //bot mid
                bombCount++;
            }
            if((i != 15) && (j != 24) && (boardLogic[i + 1] [j + 1] == 1)){ //bot right
                bombCount++;
            }
            //if equal to bomb, set to 9
            if(boardLogic[i][j] == 1){
                bombCount = 9;
            }
            boardDisplay[i][j] = bombCount;
        }
    }
    BoardTiles();
}

void Board::testBoard1() {
    boardLogic.clear();
    mineCount = 0;
    std::vector<int> tempVec;

    std::ifstream test1;
    test1.open("boards/testboard1.brd");
    std::string lineFromFile;
    this->mineCount = 0;
    while(getline(test1, lineFromFile)){
        for(int i = 0; i < lineFromFile.length(); i++){
            int temp = lineFromFile[i];
            temp = temp - 48;
            if(temp == 1){
                this->mineCount++;
            }
            tempVec.push_back(temp);
        }
        boardLogic.push_back(tempVec);
        tempVec.clear();
    }
    BoardDisplay();
}

void Board::testBoard2(){
    boardLogic.clear();
    mineCount = 0;
    std::vector<int> tempVec;

    std::ifstream test1;
    test1.open("boards/testboard2.brd");
    std::string lineFromFile;
    this->mineCount = 0;
    while(getline(test1, lineFromFile)){
        for(int i = 0; i < lineFromFile.length(); i++){
            int temp = lineFromFile[i];
            temp = temp - 48;
            if(temp == 1){
                this->mineCount++;
            }
            tempVec.push_back(temp);
        }
        boardLogic.push_back(tempVec);
        tempVec.clear();
    }
    BoardDisplay();
}

void Board::testBoard3() {
    boardLogic.clear();
    mineCount = 0;
    std::vector<int> tempVec;

    std::ifstream test1;
    test1.open("boards/testboard3.brd");
    std::string lineFromFile;
    this->mineCount = 0;
    while(getline(test1, lineFromFile)){
        for(int i = 0; i < lineFromFile.length(); i++){
            int temp = lineFromFile[i];
            temp = temp - 48;
            if(temp == 1){
                this->mineCount++;
            }
            tempVec.push_back(temp);
        }
        boardLogic.push_back(tempVec);
        tempVec.clear();
    }
    BoardDisplay();
}

std::vector<std::vector<int>> Board::GetDisplay() {
    return this->boardDisplay;
}
//process boardDisplay for boardTiles by creating a class of attributes for each Tile
void Board::BoardTiles() {
    boardTiles.clear();
    for (int i = 0; i < boardDisplay.size(); i++) {
        std::vector<Tile> tempVec;
        for (int j = 0; j < boardDisplay[i].size(); j++) {
            //Tile construct: bool _revealed, bool _mined, bool _hasNum, bool _flagged, int _num
            if (boardDisplay[i][j] == 0) {
                Tile tempTile(false, false, false, false, 0);
                tempVec.push_back(tempTile);
            }
            if (boardDisplay[i][j] == 1) {
                Tile tempTile(false, false, true, false, 1);
                tempVec.push_back(tempTile);
            }
            if (boardDisplay[i][j] == 2) {
                Tile tempTile(false, false, true, false, 2);
                tempVec.push_back(tempTile);
            }
            if (boardDisplay[i][j] == 3) {
                Tile tempTile(false, false, true, false, 3);
                tempVec.push_back(tempTile);
            }
            if (boardDisplay[i][j] == 4) {
                Tile tempTile(false, false, true, false, 4);
                tempVec.push_back(tempTile);
            }
            if (boardDisplay[i][j] == 5) {
                Tile tempTile(false, false, true, false, 5);
                tempVec.push_back(tempTile);
            }
            if (boardDisplay[i][j] == 6) {
                Tile tempTile(false, false, true, false, 6);
                tempVec.push_back(tempTile);
            }
            if (boardDisplay[i][j] == 7) {
                Tile tempTile(false, false, true, false, 7);
                tempVec.push_back(tempTile);
            }
            if (boardDisplay[i][j] == 8) {
                Tile tempTile(false, false, true, false, 8);
                tempVec.push_back(tempTile);
            }
            //mined
            if (boardDisplay[i][j] == 9) {
                Tile tempTile(false, true, false, false, 9);
                tempVec.push_back(tempTile);
            }
        }
        boardTiles.push_back(tempVec);
    }
}

Board::Tile::Tile() {

}

Board::Tile::Tile(bool _revealed, bool _mined, bool _hasNum, bool _flagged, int _num) {
    revealed = _revealed;
    mined = _mined;
    hasNum = _hasNum;
    flagged = _flagged;
    checked = false;
    num = _num;
}
