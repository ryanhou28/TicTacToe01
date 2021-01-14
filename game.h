#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>



#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>



/*

    Game header file

*/


struct Object
{
    char symbol;
    sf::RectangleShape emptyBlock;
};

struct TextButtonObject
{
    sf::Text text;
    sf::RectangleShape collisionBox;
    bool selected;
};

class Game
{
private:
    //Window

    sf::RenderWindow* window;
    sf::Event ev;
    sf::VideoMode videoMode;

    //Mouse Positions - Relative to Window
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //Font & Texts
    sf::Font font;
    sf::Text uiText;

    //Start Screen Texts
    sf::Text startScreenTitle;
    sf::Text startScreenText;
    std::vector<sf::Text> startScreenColumn1Text;
    std::vector<sf::Text> startScreenColumn2Text;
    
    std::vector<TextButtonObject> startScreenTextButtons;

    //End Screen Text
    sf::Text endScreenText;

    //Grid Variables
    const double screenwidth = 1920.f;
    const double linewidth = 20.f;

    //Logic
    std::vector<Object> gamegrid;
    bool endGame;
    bool mouseHeld;
    

    char player1;
    char player2;

    int currentPlayer;

    bool startScreen;

    //Game Objects


    //Private Functions
    void initVariables();
    void initWindow();
    void initFonts();
    void initText();

    char checkTerminalState();
    int checkEmptySpots();
    void updateTerminalState();

        //AI Moves

    void randomMove();
    int check1MoveAway(char mark);
    void easyAIMove();
    void mediumAIMove();
    void hardAIMove();

        //Minimax Algorithm

    int minimax(bool maximize,char maximizerMark, std::vector<Object> grid);

        //Minimax Helper Functions
    char minimaxCheckTerminalState(std::vector<Object> grid);
    int minimaxCheckEmptySpots(std::vector<Object> grid);

    //Debug Functions
    void printGamegrid();
    void printIntVector(std::vector<int> intVector);
    void printPlayerModes();


public:
    //Constructor
    Game();
    //Destructor
    virtual ~Game();


    //Public Variable
    int replayYesNo; //0 for None, 1 for true, 2 for false

    //Accessors
    const bool running() const;
    const bool getEndGame() const;
    const bool getStartScreen() const;

    //Functions

    void pollEvents();
    void updateMousePositions();

    void getPlayerMode();

        //Update Functions
    void update();
    void updateShapes();
    void updateText();
    void updateStartScreen();

        //Render Functions
    void renderGrid();
    void renderShapes();
    void renderText();
    void render();

    void startScreenRender();
    void endScreenRender();

};