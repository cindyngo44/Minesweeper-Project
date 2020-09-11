//
// Created by Cindy Ngo on 8/3/20.
//
#include "Program.h"
#include "TextureManager.h"
#include <cstdlib>
void Program::Initialize(sf::RenderWindow &window) {
    mainWindow = &window;
    LoadSprites(window);
    //initializes the HiddenTiles, will be updated later
    DrawALLHidden();
}

void Program::CheckWinLose() {
    win = CheckWin();
    if(win && !lose && !neutral){
        Draw();
    }
    //lose and not win
    else if(lose && !win && !neutral){
        Draw();
    }
    //neutral, no win and no lose
    else if(neutral && !win && !lose){
        Draw();
    }
}

void Program::Shutdown() {
    TextureManager::Clear();
}

void Program::LoadSprites(sf::RenderWindow &window) {
    DebugSprite.setTexture(TextureManager::GetTexture("debug"));
    DigitsSprite.setTexture(TextureManager::GetTexture("digits"));
    FaceHappySprite.setTexture(TextureManager::GetTexture("face_happy"));
    FaceLoseSprite.setTexture(TextureManager::GetTexture("face_lose"));
    FaceWinSprite.setTexture(TextureManager::GetTexture("face_win"));
    FlagSprite.setTexture(TextureManager::GetTexture("flag"));
    MineSprite.setTexture(TextureManager::GetTexture("mine"));
    Number1Sprite.setTexture(TextureManager::GetTexture("number_1"));
    Number2Sprite.setTexture(TextureManager::GetTexture("number_2"));
    Number3Sprite.setTexture(TextureManager::GetTexture("number_3"));
    Number4Sprite.setTexture(TextureManager::GetTexture("number_4"));
    Number5Sprite.setTexture(TextureManager::GetTexture("number_5"));
    Number6Sprite.setTexture(TextureManager::GetTexture("number_6"));
    Number7Sprite.setTexture(TextureManager::GetTexture("number_7"));
    Number8Sprite.setTexture(TextureManager::GetTexture("number_8"));
    TileHiddenSprite.setTexture(TextureManager::GetTexture("tile_hidden"));
    Test1Sprite.setTexture(TextureManager::GetTexture("test_1"));
    Test2Sprite.setTexture(TextureManager::GetTexture("test_2"));
    Test3Sprite.setTexture(TextureManager::GetTexture("test_3"));
    TileRevealedSprite.setTexture(TextureManager::GetTexture("tile_revealed"));

    FaceHappySprite.setPosition(368, 512);
    DebugSprite.setPosition(504, 512);
    Test1Sprite.setPosition(568, 512);
    Test2Sprite.setPosition(632, 512);
    Test3Sprite.setPosition(695, 512);
}
//smiley restarts, testboard loads, debug, revealing tiles
void Program::LeftMouseClick(sf::Vector2i &mousePosition) {
    sf::Vector2f fposition(mousePosition.x, mousePosition.y);
    //resetting boards
    if (FaceHappySprite.getGlobalBounds().contains(fposition)) {
        board.BoardShuffle();
        flags = 0;
        flaggedTiles.clear();
        lose = false;
        win = false;
        neutral = true;
        DrawALLHidden();
    }
    if (win == true && neutral == false && lose == false &&  FaceWinSprite.getGlobalBounds().contains(fposition)) {
        board.BoardShuffle();
        flags = 0;
        flaggedTiles.clear();
        WinningTiles.clear();
        lose = false;
        win = false;
        neutral = true;
        DrawALLHidden();
    }
    if (win == false && neutral == false && lose == true &&  FaceLoseSprite.getGlobalBounds().contains(fposition)) {
        board.BoardShuffle();
        flags = 0;
        flaggedTiles.clear();
        LosingTiles.clear();
        lose = false;
        win = false;
        neutral = true;
        DrawALLHidden();
    }
    //test boards
    if (Test1Sprite.getGlobalBounds().contains(fposition)) {
        board.testBoard1();
        flaggedTiles.clear();
        WinningTiles.clear();
        LosingTiles.clear();
        flags = 0;
        lose = false;
        win = false;
        neutral = true;
        DrawALLHidden();
    }
    if (Test2Sprite.getGlobalBounds().contains(fposition)) {
        board.testBoard2();
        flaggedTiles.clear();
        WinningTiles.clear();
        LosingTiles.clear();
        flags = 0;
        lose = false;
        win = false;
        neutral = true;
        DrawALLHidden();
    }
    if (Test3Sprite.getGlobalBounds().contains(fposition)) {
        board.testBoard3();
        flaggedTiles.clear();
        WinningTiles.clear();
        LosingTiles.clear();
        flags = 0;
        lose = false;
        win = false;
        neutral = true;
        DrawALLHidden();
    }
    if (DebugSprite.getGlobalBounds().contains(fposition) && win == false && lose == false) {
        if (debug == false) {
            debug = true;
            Draw();
        } else if (debug == true) {
            debug = false;
            DebugTiles.clear();
            Draw();
        }
    }
    if (neutral == true && lose == false && win == false &&
                    mousePosition.x < 800 && mousePosition.y < 512) {
        //takes in the mouse location
        RevealRecursion(mousePosition.x, mousePosition.y);
        //check wins and loses from one left click
        CheckWinLose();
    }
}
//right click only deals with flags
void Program::RightMouseClick(sf::Vector2i &mousePosition) {
        DrawFlagged(mousePosition);
        Draw();
    }

void Program::Draw() {
    mainWindow->clear(sf::Color(255, 255, 255));
    contentTiles.clear();
    //layer orders: UI, Content, Hidden Tiles, Flags, Debugs
    Counter();
    DrawStaticUI();
    DrawContent();
    DrawDebug();
    for (int i = 0; i < baseTiles.size(); i++) {
        mainWindow->draw(baseTiles[i]);
    }
    for (int i = 0; i < CounterTiles.size(); i ++){
            mainWindow->draw(CounterTiles[i]);
    }
    if(lose == true){
        LosingInterface();
        for (int i = 0; i < LosingTiles.size(); i++) {
            mainWindow->draw(LosingTiles[i]);
        }
    }
    if(win == true){
        WinningInterface();
        for (int i = 0; i < WinningTiles.size(); i++) {
            mainWindow->draw(WinningTiles[i]);
        }
    }
    if(lose == true){
        for (int i = 0; i < flaggedTiles.size(); i++) {
            mainWindow->draw(flaggedTiles[i]);
        }
    }
    //draw content
    for (int i = 0; i < contentTiles.size(); i++) {
        mainWindow->draw(contentTiles[i]);
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if(HiddenTiles[i][j] == nullptr){
                continue;
            }
            else{
                mainWindow->draw(*HiddenTiles[i][j]);
            }
        }
    }
    if(lose == false){
        for (int i = 0; i < flaggedTiles.size(); i++) {
            mainWindow->draw(flaggedTiles[i]);
        }
    }
    if(win == true){
        WinningInterface();
        Counter();
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 25; j++) {
                if (WinFlags[i][j] == nullptr) {
                    continue;
                } else {
                    mainWindow->draw(*WinFlags[i][j]);
                }
            }
        }
    }
    //draw debug on top of everything (if neutral??)
    for (int i = 0; i < DebugTiles.size(); i++) {
        mainWindow->draw(DebugTiles[i]);
    }
    mainWindow->display();
}

void Program::DrawALLHidden() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            int x = j * 32;
            int y = i * 32;
            TileHiddenSprite.setPosition(x,y);
            HiddenTilesTemp[i][j] = TileHiddenSprite;
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
        HiddenTiles[i][j] = &HiddenTilesTemp[i][j];
        }
    }
}

void Program::RevealRecursion(int _x, int _y) {
    //process pixels into 16x25 (note pixels are flipped with array)
    int y = (_x / 32);
    int x = (_y / 32);

    //if mined and not flagged (LOSE)
    if (board.boardTiles[x][y].mined == true && board.boardTiles[x][y].flagged == false) {
        board.boardTiles[x][y].revealed = true;
        board.boardTiles[x][y].checked = true;
        HiddenTiles[x][y] = nullptr;
        lose = true;
        neutral = false;
    }
    //if checked, don't do anything
    if(board.boardTiles[x][y].checked == true){
    }
    //if flagged don't reveal
    else if(board.boardTiles[x][y].flagged == true){
    }
    //if has single num just reveal that one
    else if(board.boardTiles[x][y].hasNum == true && board.boardTiles[x][y].flagged == false){
        board.boardTiles[x][y].revealed = true;
        board.boardTiles[x][y].checked = true;
        HiddenTiles[x][y] = nullptr;
    }
    else {
        //cannot reveal a flagged
        if (board.boardTiles[x][y].checked == false && board.boardTiles[x][y].flagged == false) {
            board.boardTiles[x][y].revealed = true;
            board.boardTiles[x][y].checked = true;
            HiddenTiles[x][y] = nullptr;
            //check its neighbors
            if ((x != 0) && (y != 0) && (board.GetDisplay()[x - 1][y - 1] != 9)) { //top left
                RevealRecursion((y - 1) * 32, (x - 1) * 32);
            }
            if ((x != 0) && (board.GetDisplay()[x - 1][y] != 9)) { //top mid
                RevealRecursion(y  * 32, (x - 1) * 32);
            }
            if ((x != 0) && (y != 24) && (board.GetDisplay()[x - 1][y + 1] != 9)) { //top right
                RevealRecursion((y + 1) * 32, (x - 1) * 32);
            }
            if ((y != 0) && (board.GetDisplay()[x][y - 1] != 9)) { //mid left
                RevealRecursion((y - 1) * 32, x * 32);
            }
            if ((y != 24) && (board.GetDisplay()[x][y + 1] != 9)) { //mid right
                RevealRecursion((y + 1) * 32, x * 32);
            }
            if ((x != 15) && (y != 0) && (board.GetDisplay()[x + 1][y - 1] != 9)) { //bot left
                RevealRecursion((y - 1) * 32, (x + 1) * 32);
            }
            if ((x != 15) && (board.GetDisplay()[x + 1][y] != 9)) { //bot mid
                RevealRecursion(y * 32, (x + 1) * 32);
            }
            if ((x != 15) && (y != 24) && (board.GetDisplay()[x + 1][y + 1] != 9)) { //bot right
                RevealRecursion((y + 1) * 32, (x + 1) * 32);
            }
        }
    }

}

void Program::DrawStaticUI() {
        int x = 0;
        int y = 0;
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 25; j++) {
                TileRevealedSprite.setPosition(x, y);
                baseTiles.push_back(TileRevealedSprite);
                x += 32;
            }
            x = 0;
            y += 32;
        }
        baseTiles.push_back(DebugSprite);
        baseTiles.push_back(FaceHappySprite);
        baseTiles.push_back(Test1Sprite);
        baseTiles.push_back(Test2Sprite);
        baseTiles.push_back(Test3Sprite);
    }

void Program::DrawContent() {
    contentTiles.clear();
    int x;
        int y;
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 25; j++) {
                if (board.GetDisplay()[i][j] == 1) {
                    x = j * 32;
                    y = i * 32;
                    Number1Sprite.setPosition(x, y);
                    contentTiles.push_back(Number1Sprite);
                }
                if (board.GetDisplay()[i][j] == 2) {
                    x = j * 32;
                    y = i * 32;
                    Number2Sprite.setPosition(x, y);
                    contentTiles.push_back(Number2Sprite);
                }
                if (board.GetDisplay()[i][j] == 3) {
                    x = j * 32;
                    y = i * 32;
                    Number3Sprite.setPosition(x, y);
                    contentTiles.push_back(Number3Sprite);
                }
                if (board.GetDisplay()[i][j] == 4) {
                    x = j * 32;
                    y = i * 32;
                    Number4Sprite.setPosition(x, y);
                    contentTiles.push_back(Number4Sprite);
                }
                if (board.GetDisplay()[i][j] == 5) {
                    x = j * 32;
                    y = i * 32;
                    Number5Sprite.setPosition(x, y);
                    contentTiles.push_back(Number5Sprite);
                }
                if (board.GetDisplay()[i][j] == 6) {
                    x = j * 32;
                    y = i * 32;
                    Number6Sprite.setPosition(x, y);
                    contentTiles.push_back(Number6Sprite);
                }
                if (board.GetDisplay()[i][j] == 7) {
                    x = j * 32;
                    y = i * 32;
                    Number7Sprite.setPosition(x, y);
                    contentTiles.push_back(Number7Sprite);
                }
                if (board.GetDisplay()[i][j] == 8) {
                    x = j * 32;
                    y = i * 32;
                    Number8Sprite.setPosition(x, y);
                    contentTiles.push_back(Number8Sprite);
                }
                if (board.GetDisplay()[i][j] == 9) {
                    x = j * 32;
                    y = i * 32;
                    MineSprite.setPosition(x, y);
                    contentTiles.push_back(MineSprite);
                }
            }
        }
    }

void Program::DrawFlagged(sf::Vector2i &mousePosition) {
    //add flags during a neutral game
    if (mousePosition.y < 512 && neutral == true && lose == false && win == false){
        int x = (mousePosition.x / 32);
        int y = (mousePosition.y / 32);
        //add a flag if not already flagged and is not revealed
        if(board.boardTiles[y][x].flagged == false && board.boardTiles[y][x].revealed == false){
            //std::cout << "Flag added" << std::endl;
            board.boardTiles[y][x].flagged = true;

            x *= 32;
            y *= 32;
            FlagSprite.setPosition(x, y);
            flaggedTiles.push_back(FlagSprite);
            flags++;
        }
        else if(board.boardTiles[y][x].flagged == true){
            //std::cout << "Flag Deleted" << std::endl;
            vector<sf::Sprite> tempVec;
            board.boardTiles[y][x].flagged = false;

            for(int i = 0; i < flaggedTiles.size(); i++){
                int fx = flaggedTiles[i].getPosition().x / 32;
                int fy = flaggedTiles[i].getPosition().y / 32;
                if(x == fx && y == fy){
                }
                else{
                    tempVec.push_back(flaggedTiles[i]);
                }
            }
            flaggedTiles.clear();
            for(int i = 0; i < tempVec.size(); i++){
                flaggedTiles.push_back(tempVec[i]);
            }
            tempVec.clear();
            flags--;
        }
    }
}

void Program::DrawDebug(){
    DebugTiles.clear();
    if(debug){
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 25; j++) {
                if (board.GetDisplay()[i][j] == 9) {
                    int x = j * 32;
                    int y = i * 32;
                    if (debug) {
                        MineSprite.setPosition(x, y);
                        DebugTiles.push_back(MineSprite);
                    }
                }
            }
        }
    }
}
//Pixel References:
// Starts at x = 0px y = 512px
// ___ 0, 21, 42,
// ____ 0, 21, 42, 63 (negative)
// png order: 0 1 2 3 4 5 6 7 8 9 -
//width = 21 height = 32
void Program::Counter() {
    CounterTiles.clear();
    mines = board.mineCount;
    if (win == true){
        flags = mines;
    }
    mines -= flags;
    //prints amount if positive
    if(mines >= 0) {
        int ones = mines % 10;
        int tens = mines / 10;
        int hundreds = mines / 100;
        DigitsSprite.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));
        DigitsSprite.setPosition(42, 512);
        CounterTiles.push_back(DigitsSprite);

        DigitsSprite.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
        DigitsSprite.setPosition(21, 512);
        CounterTiles.push_back(DigitsSprite);

        DigitsSprite.setTextureRect(sf::IntRect(21 * hundreds, 0, 21, 32));
        DigitsSprite.setPosition(0, 512);
        CounterTiles.push_back(DigitsSprite);
    }
    if(mines < 0){
        mines = abs(mines);
        int ones = mines % 10;
        int tens = mines / 10;
        int hundreds = mines / 100;
        DigitsSprite.setTextureRect(sf::IntRect(21 * ones, 0, 21, 32));
        DigitsSprite.setPosition(63, 512);
        CounterTiles.push_back(DigitsSprite);

        DigitsSprite.setTextureRect(sf::IntRect(21 * tens, 0, 21, 32));
        DigitsSprite.setPosition(42, 512);
        CounterTiles.push_back(DigitsSprite);

        DigitsSprite.setTextureRect(sf::IntRect(21 * hundreds, 0, 21, 32));
        DigitsSprite.setPosition(21, 512);
        CounterTiles.push_back(DigitsSprite);

        DigitsSprite.setTextureRect(sf::IntRect(210, 0, 21, 32));
        DigitsSprite.setPosition(0, 512);
        CounterTiles.push_back(DigitsSprite);
    }
}

void Program::LosingInterface() {
    FaceLoseSprite.setPosition(368, 512);
    LosingTiles.push_back(FaceLoseSprite);
    //reveal all mines
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            if (board.boardTiles[i][j].mined == true){
                HiddenTiles[i][j] = nullptr;
            }
        }
    }
}

void Program::WinningInterface() {
    FaceWinSprite.setPosition(368, 512);
    WinningTiles.push_back(FaceWinSprite);

    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            int x = j * 32;
            int y = i * 32;
            FlagSprite.setPosition(x,y);
            WinFlagsTemp[i][j] = FlagSprite;
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            WinFlags[i][j] = &WinFlagsTemp[i][j];
        }
    }
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 25; j++) {
            if(board.boardTiles[i][j].mined == false && board.boardTiles[i][j].flagged == false){
                WinFlags[i][j] = nullptr;
            }
        }
    }
}

bool Program::CheckWin(){
    //win and not lose, needs to check all tiles are revealed and no mines revealed
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 25; j++){
            //revealed and not mine
            if(board.boardTiles[i][j].revealed == false && board.boardTiles[i][j].mined == false){
                win = false;
                neutral = true;
                return win;
            }
                //win if all number and 0 tiles are revealed
            else if ((board.boardTiles[i][j].revealed == true && board.boardTiles[i][j].hasNum == true) ||
                     (board.boardTiles[i][j].revealed == true && board.boardTiles[i][j].num == 0)){
                win = true;
                neutral = false;
            }
        }
    }
    return win;
}
