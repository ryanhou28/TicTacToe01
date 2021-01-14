//game cpp


#include "game.h"

//Private Functions


void Game::initVariables()
{
    //Initializes Game Variables

    //Initialize Game Grid
    
    for (int i = 0;i < 9; ++i){
        Object object;
        gamegrid.push_back(object);
        this->gamegrid[i].symbol = '_';

    }
    

    //TEST
    /*
    for (int i = 0; i < 10; ++i)
    {
        Object object;
        gamegrid.push_back(object);
    }
    this->gamegrid[0].symbol = '_';
    this->gamegrid[1].symbol = 'X';
    this->gamegrid[2].symbol = 'X';
    this->gamegrid[3].symbol = 'O';
    this->gamegrid[4].symbol = 'X';
    this->gamegrid[5].symbol = 'X';
    this->gamegrid[6].symbol = 'O';
    this->gamegrid[7].symbol = 'O';
    this->gamegrid[8].symbol = '_';
    */

    /*
    GAMEGRID:
    [0, 1, 2]
    [3, 4, 5]
    [6, 7, 8]
    */

    this->endGame = false;

    this->player1 = 'p';
    this->player2 = 'p';
    //p - player, e - easy AI, m - medium AI, h - hard AI

    this->currentPlayer = 1;

    this->mouseHeld = false;

    this->replayYesNo = 0;

    this->startScreen = true;

    //Initialize Start Screen Text Button Object
    double collisionBoxWidth = 800.f;
    double collisionBoxHeight = 100.f;

    for (int i = 0; i < this->startScreenColumn1Text.size(); i++)
    {
        //First Column of Text Buttons
        TextButtonObject textButton;
        textButton.text = this->startScreenColumn1Text[i];

        if (i == 0)
        {
            textButton.selected = true;
        }
        else
        {
            textButton.selected = false;
        }
        
        sf::RectangleShape colBox;
        colBox.setSize(sf::Vector2f(collisionBoxWidth,collisionBoxHeight));
        colBox.setFillColor(sf::Color::Transparent);
        colBox.setPosition(this->startScreenColumn1Text[i].getPosition());

        textButton.collisionBox = colBox;

        startScreenTextButtons.push_back(textButton);
    }

    for (int i = 0; i < this->startScreenColumn2Text.size(); i++)
    {
        //Second Column of Text Buttons
        TextButtonObject textButton;
        textButton.text = this->startScreenColumn2Text[i];

        if (i == 0)
        {
            textButton.selected = true;
        }
        else
        {
            textButton.selected = false;
        }

        sf::RectangleShape colBox;
        colBox.setSize(sf::Vector2f(collisionBoxWidth,collisionBoxHeight));
        colBox.setFillColor(sf::Color::Transparent);
        colBox.setPosition(this->startScreenColumn2Text[i].getPosition());

        textButton.collisionBox = colBox;

        startScreenTextButtons.push_back(textButton);
    }

}



void Game::initWindow()
{
    //Enable Antialiasing

    sf::ContextSettings settings;
    settings.antialiasingLevel = 10;

    //Initializes Game Window

    this->videoMode.height = this->screenwidth + 200.f;
    this->videoMode.width = this->screenwidth;
    this->window = new sf::RenderWindow(this->videoMode, "TIC TAC TOE", sf::Style::Default, settings);
    this->window->setFramerateLimit(60);

}

void Game::initFonts()
{
    //Initializes Fonts
    if (this->font.loadFromFile("Fonts/LEMONMILK-Regular.otf"))
    {
        std::cout << "Font loaded!" << std::endl;
    }
    else
    {
        std::cout << "ERROR LOADING FONT!" << std::endl;
    }
}

void Game::initText()
{

    //Initialize Start Screen Title

    this->startScreenTitle.setFont(this->font);
    this->startScreenTitle.setCharacterSize(240);
    this->startScreenTitle.setFillColor(sf::Color::White);
    this->startScreenTitle.setString("Tic Tac Toe");
    this->startScreenTitle.setPosition(sf::Vector2f(100.f, 810.f));


    //Initialize Start Screen Text
    this->startScreenText.setFont(this->font);
    this->startScreenText.setCharacterSize(96);
    this->startScreenText.setFillColor(sf::Color::White);
    this->startScreenText.setString("Player 1 (X)   vs   Player 2 (O)\n\n\n\n\n\t\tPress Enter to Start");
    this->startScreenText.setPosition(sf::Vector2f(100.f, this->screenwidth / 2.f + 130.f));

    //Initializes Start Screen Column 1
    for (int i = 0; i < 4; i++)
    {
        sf::Text optionText;
        optionText.setFont(this->font);
        optionText.setCharacterSize(64);
        optionText.setFillColor(sf::Color::White);
        optionText.setPosition(sf::Vector2f(100.f, this->screenwidth / 2.f + 250.f + i * 120.f));
        this->startScreenColumn1Text.push_back(optionText);
    }

    this->startScreenColumn1Text[0].setString("Player");
    this->startScreenColumn1Text[1].setString("Easy (Computer)");
    this->startScreenColumn1Text[2].setString("Medium (Computer)");
    this->startScreenColumn1Text[3].setString("Hard (Computer)");

    //Initializes Start Screen Column 2
    this->startScreenColumn2Text = this->startScreenColumn1Text;
    for (int i = 0; i < 4; i++)
    {
        this->startScreenColumn2Text[i].setPosition(sf::Vector2f(1000.f, this->screenwidth / 2.f + 250.f + i * 120.f));
    }



    //Initializes UI Text
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(64);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");

    this->uiText.setPosition(sf::Vector2f(0.f, this->screenwidth + 110.f));


    //Initialize End Screen Text
    this->endScreenText.setFont(this->font);
    this->endScreenText.setCharacterSize(192);
    this->endScreenText.setFillColor(sf::Color::Magenta);
    this->endScreenText.setString("");

}

char Game::checkTerminalState()
{
    /*Checks and returns whether the game is in terminal state
    N = Not in terminal State
    X = X (Player 1) Wins
    O = O (Player 2) Wins
    T = Tied/Draw - No spots left on grid and neither has won
    */
    if (this->gamegrid[0].symbol == this->gamegrid[3].symbol && this->gamegrid[3].symbol == this->gamegrid[6].symbol && this->gamegrid[6].symbol != '_')
    {
        //TEST
        //std::cout << "0, 3, 6 WIN!" << std::endl;

        return this->gamegrid[0].symbol;
    }
    else if (this->gamegrid[1].symbol == this->gamegrid[4].symbol && this->gamegrid[4].symbol == this->gamegrid[7].symbol && this->gamegrid[7].symbol != '_')
    {
        //TEST
        //std::cout << "1, 4, 7 WIN!" << std::endl;
        return this->gamegrid[1].symbol;
        
    }
    else if (this->gamegrid[2].symbol == this->gamegrid[5].symbol && this->gamegrid[5].symbol == this->gamegrid[8].symbol && this->gamegrid[8].symbol != '_')
    {
        //TEST
        //std::cout << "2, 5, 8 WIN!" << std::endl;
        return this->gamegrid[2].symbol;
    }
    else if (this->gamegrid[0].symbol == this->gamegrid[1].symbol && this->gamegrid[1].symbol == this->gamegrid[2].symbol && this->gamegrid[2].symbol != '_')
    {
        //TEST
        //std::cout << "0, 1, 2 WIN!" << std::endl;
        return this->gamegrid[0].symbol;
    }
    else if (this->gamegrid[3].symbol == this->gamegrid[4].symbol && this->gamegrid[4].symbol == this->gamegrid[5].symbol && this->gamegrid[5].symbol != '_')
    {
        //TEST
        //std::cout << "3, 4, 5 WIN!" << std::endl;
        return this->gamegrid[3].symbol;
    }
    else if (this->gamegrid[6].symbol == this->gamegrid[7].symbol && this->gamegrid[7].symbol == this->gamegrid[8].symbol && this->gamegrid[8].symbol != '_')
    {
        //TEST
        //std::cout << "6, 7, 8 WIN!" << std::endl;
        return this->gamegrid[6].symbol;
    }
    else if (this->gamegrid[0].symbol == this->gamegrid[4].symbol && this->gamegrid[4].symbol == this->gamegrid[8].symbol && this->gamegrid[8].symbol != '_')
    {
        //TEST
        //std::cout << "0, 4, 8 WIN!" << std::endl;
        return this->gamegrid[0].symbol;
    }
    else if (this->gamegrid[6].symbol == this->gamegrid[4].symbol && this->gamegrid[4].symbol == this->gamegrid[2].symbol && this->gamegrid[2].symbol != '_')
    {
        //TEST
        //std::cout << "6, 4, 2 WIN!" << std::endl;
        return this->gamegrid[6].symbol;
    }

    if (checkEmptySpots() == 0)
    {
        //Tied
        return 'T';
    }


    return 'N';
}

int Game::checkEmptySpots()
{
    //Checks and return ths number of empty spots on the board
    int numEmptySpots = 0;
    for(int i = 0; i < 10; ++i)
    {
        if(this->gamegrid[i].symbol == '_')
        {
            numEmptySpots++;
        }
    }

    return numEmptySpots;

}

void Game::updateTerminalState()
{
    //Check for Terminal States
    if (this->checkTerminalState() == 'T') {
        //Tied
        std::cout << "Draw!" << std::endl;
        this->endScreenText.setString("Draw!");
        this->endGame = true;
    }
    else if (this->checkTerminalState() == 'X') {
        //Player 1 Wins
        std::cout << "Player 1 (X) wins!" << std::endl;
        this->endScreenText.setString("Player 1 (X) Wins!");
        this->endGame = true;
    }
    else if (this->checkTerminalState() == 'O') {
        //Player 2 Wins
        std::cout << "Player 2 (O) wins!" << std::endl;
        this->endScreenText.setString("Player 2 (O) Wins!");
        this->endGame = true;
    }
    else if (checkTerminalState() == 'N') {
        //Not at terminal state yet
        this->endGame = false;
    }
    
}


//AI MOVES

void Game::randomMove()
{
    //Makes a random move
    bool validMove = false;

    while (!validMove && this->checkEmptySpots() != 0)
    {
        int randNum = std::rand() % 9;
        if (this->gamegrid[randNum].symbol == '_')
        {
            validMove = true;
            if (this->currentPlayer == 1)
            {
                this->gamegrid[randNum].symbol = 'X';
                this->currentPlayer = 2;
            }
            else
            {
                this->gamegrid[randNum].symbol = 'O';
                this->currentPlayer = 1;
            }
            
        }
    }
}

int Game::check1MoveAway(char mark)
{
    //Checks if any player is one move away
    //returns the index of the empty grid that is one move away
    //If none is found, returns -1

    for(int i = 0; i < 9; ++i)
    {
        if (this->gamegrid[i].symbol == '_')
        {
            this->gamegrid[i].symbol = mark;

            if(this->checkTerminalState() == mark)
            {
                this->gamegrid[i].symbol = '_';
                return i;
            }
            else
            {
                this->gamegrid[i].symbol = '_';
            }
        }
    }
    
    //If none are one move away
    return -1;
}

void Game::easyAIMove()
{
    //Easy AI makes a move
    this->randomMove();
}

void Game::mediumAIMove()
{
    //Medium AI makes a move

    

    //If AI can win with 1 move
    int aiCheck1Move;
    if (currentPlayer == 1)
    {
        aiCheck1Move = this->check1MoveAway('X');

        if (aiCheck1Move != -1)
        {
            this->gamegrid[aiCheck1Move].symbol = 'X';
            this->currentPlayer = 2;
            return;
        }
    }
    else
    {
        aiCheck1Move = this->check1MoveAway('O');

        if (aiCheck1Move != -1)
        {
            this->gamegrid[aiCheck1Move].symbol = 'O';
            this->currentPlayer = 1;
            return;
        }
    }


    //If opponent can win with 1 move
    int oppoCheck1Move;
    if (currentPlayer == 1)
    {
        oppoCheck1Move = this->check1MoveAway('O');

        if (oppoCheck1Move != -1)
        {
            this->gamegrid[oppoCheck1Move].symbol = 'X';
            this->currentPlayer = 2;
            return;
        }
    }
    else
    {
        oppoCheck1Move = this->check1MoveAway('X');

        if (oppoCheck1Move != -1)
        {
            this->gamegrid[oppoCheck1Move].symbol = 'O';
            this->currentPlayer = 1;
            return;
        }
    }

    //If neither - Make random move

    this->randomMove();
    
}

void Game::hardAIMove()
{
    //Hard AI makes a move
    int bestScore = -10000;
    int bestMove = -1;
    
    std::vector<Object> grid;
    grid = this->gamegrid;

    char myMark;
    int score;

    if (this->currentPlayer == 1)
    {
        myMark = 'X';
    }
    else
    {
        myMark = 'O';
    }
    
    
    //For every grid in the game grid
    for (int i = 0; i < 9; i++)
    {
        //If the current grid is a possible move
        if (grid[i].symbol == '_')
        {
            //TEST
            //std::cout << "-----" << std::endl;
            //std::cout << "Possible Move at " << i << std::endl;


            grid[i].symbol = myMark;
            score = minimax(false, myMark, grid);
            grid[i].symbol = '_';

            if (score > bestScore)
            {
                bestScore = score;
                bestMove = i;
            }
            
        }

        //TEST
        //std::cout << "Current Best Score: " << bestScore << std::endl;
        //std::cout << "Current Best Move: " << bestMove << std::endl;
        //std::cout << "-----" << std::endl;
    }

    //TEST
    //std::cout << "------" << std::endl;

    //Makes move at bestMove
    if (this->currentPlayer == 1)
    {
        this->gamegrid[bestMove].symbol = 'X';
        this->currentPlayer = 2;
    }
    else
    {
        this->gamegrid[bestMove].symbol = 'O';
        this->currentPlayer = 1;
    }


}

//Minimax Implementation

int Game::minimax(bool maximize, char maximizerMark, std::vector<Object> grid)
{
    //Minimax Algorithm

    char myMark = maximizerMark;
    char oppoMark;
    if (maximizerMark == 'X')
    {
        oppoMark = 'O';
    }
    else
    {
        oppoMark = 'X';
    }
    

    //If there is a draw in the grid
    if (this->minimaxCheckTerminalState(grid) == 'T')
    {
        return 0;
    }
    //If my mark is winning
    else if (this->minimaxCheckTerminalState(grid) == myMark)
    {
        return 10;
    }
    //If opponents mark is winning
    else if (this->minimaxCheckTerminalState(grid) == oppoMark)
    {
        return -10;
    }

    std::vector<int> scores;

    for (int i = 0; i < 9; i++)
    {
        //If the current grid is a possible move
        if (grid[i].symbol == '_')
        {

            /*
            Original:

            std::vector<Object> newGrid;
            newGrid = grid;

            newGrid[i].symbol = myMark;
            scores.push_back(this->minimax(!maximize, maximizerMark, newGrid));
            newGrid[i].symbol = '_';
            */
            //Test

            //grid[i].symbol = myMark;

            if(maximize)
            {
                grid[i].symbol = myMark;
            }
            else
            {
                grid[i].symbol = oppoMark;
            }
            

            scores.push_back(this->minimax(!maximize, maximizerMark, grid));
            grid[i].symbol = '_';

        }
    }

    //TEST
    //printIntVector(scores);
    
    if (maximize)
    {
        //Returns the max score in scores
        int highScore = scores[0];
        for (int i = 0; i < scores.size(); i++)
        {
            if (scores[i] > highScore)
            {
                highScore = scores[i];
                //Test
                //std::cout << "High Score found at index: " << i << std::endl;
            }
        }

        //Test
        //std::cout << "Returning High Score - " << highScore << std::endl;

        return highScore;
        
    }
    else
    {
        //Returns the min score in scores
        int lowScore = scores[0];
        for (int i = 0; i < scores.size(); i++)
        {
            if (scores[i] < lowScore)
            {
                lowScore = scores[i];
                //Test
                //std::cout << "Low Score found at index: " << i << std::endl;
            }
        }

        //Test
        //std::cout << "Returning Low Score - " << lowScore << std::endl;

        return lowScore;
    }
    
}

    //Minimax Helper Functions

char Game::minimaxCheckTerminalState(std::vector<Object> grid)
{
    /*Checks and returns whether the game is in terminal state
    Takes game grid as input
    Returns:
    N = Not in terminal State
    X = X (Player 1) Wins
    O = O (Player 2) Wins
    T = Tied/Draw - No spots left on grid and neither has won
    */
    if (grid[0].symbol == grid[3].symbol && grid[3].symbol == grid[6].symbol && grid[6].symbol != '_')
    {
        //TEST
        //std::cout << "0, 3, 6 WIN!" << std::endl;

        return grid[0].symbol;
    }
    else if (grid[1].symbol == grid[4].symbol && grid[4].symbol == grid[7].symbol && grid[7].symbol != '_')
    {
        //TEST
        //std::cout << "1, 4, 7 WIN!" << std::endl;
        return grid[1].symbol;
        
    }
    else if (grid[2].symbol == grid[5].symbol && grid[5].symbol == grid[8].symbol && grid[8].symbol != '_')
    {
        //TEST
        //std::cout << "2, 5, 8 WIN!" << std::endl;
        return grid[2].symbol;
    }
    else if (grid[0].symbol == grid[1].symbol && grid[1].symbol == grid[2].symbol && grid[2].symbol != '_')
    {
        //TEST
        //std::cout << "0, 1, 2 WIN!" << std::endl;
        return grid[0].symbol;
    }
    else if (grid[3].symbol == grid[4].symbol && grid[4].symbol == grid[5].symbol && grid[5].symbol != '_')
    {
        //TEST
        //std::cout << "3, 4, 5 WIN!" << std::endl;
        return grid[3].symbol;
    }
    else if (grid[6].symbol == grid[7].symbol && grid[7].symbol == grid[8].symbol && grid[8].symbol != '_')
    {
        //TEST
        //std::cout << "6, 7, 8 WIN!" << std::endl;
        return grid[6].symbol;
    }
    else if (grid[0].symbol == grid[4].symbol && grid[4].symbol == grid[8].symbol && grid[8].symbol != '_')
    {
        //TEST
        //std::cout << "0, 4, 8 WIN!" << std::endl;
        return grid[0].symbol;
    }
    else if (grid[6].symbol == grid[4].symbol && grid[4].symbol == grid[2].symbol && grid[2].symbol != '_')
    {
        //TEST
        //std::cout << "6, 4, 2 WIN!" << std::endl;
        return grid[6].symbol;
    }

    if (this->minimaxCheckEmptySpots(grid) == 0)
    {
        //Tied
        return 'T';
    }


    return 'N';
}

int Game::minimaxCheckEmptySpots(std::vector<Object> grid)
{
    //Checks and return ths number of empty spots on the board
    int numEmptySpots = 0;
    for(int i = 0; i < 10; ++i)
    {
        if(grid[i].symbol == '_')
        {
            numEmptySpots++;
        }
    }

    return numEmptySpots;
}




//Debug Functions
void Game::printGamegrid()
{
    //Function that prints the game grid to the command line

    std::cout << "------" << std::endl;
    for (int i = 0; i < 3; ++i){
        std::cout << gamegrid[i].symbol << " ";
    }
    std::cout << std::endl;
    for (int i = 3; i < 6;++i){
        std::cout << gamegrid[i].symbol << " ";
    }
    std::cout << std::endl;
    for (int i = 6; i < 9;++i){
        std::cout << gamegrid[i].symbol << " ";
    }
    std::cout << std::endl;
    std::cout << "------" << std::endl;

}  

void Game::printIntVector(std::vector<int> intVector)
{
    //Function that prints a vector of integers to the command line
    
    std::cout << "vector: ";
    for (int i = 0; i < intVector.size(); i++)
    {
        std::cout << i << "[" << intVector[i] << "]";
    }
    std::cout << std::endl;
}

void Game::printPlayerModes()
{
    //Function that prints the currently selected modes of the two players

    std::cout << "Player 1 Mode: " << this->player1 << std::endl;
    std::cout << "Player 2 Mode: " << this->player2 << std::endl;
}

//Constructor
Game::Game()
{
    this->initText();
    this->initVariables();
    this->initWindow();
    this->initFonts();
}


//Destructor
Game::~Game()
{
    delete this->window;
}

//Accessors

const bool Game::running() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}

const bool Game::getStartScreen() const
{
    return this->startScreen;
}

//Public Functions



void Game::pollEvents()
{
    //Check all the window's events that were triggered since the last iteration of the loop
    while(this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            //Close button is pressed
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            //Escape Key is pressed
            if(this->ev.key.code == sf::Keyboard::Escape)
            {
                this->window->close();

                this->replayYesNo = 0;

                break;
            }
            //R Key is pressed
            else if(this->ev.key.code == sf::Keyboard::R)
            {
                this->replayYesNo = 1;
                break;
            }
            //Enter Key is pressed
            else if(this->ev.key.code == sf::Keyboard::Enter)
            {
                this->startScreen = false;
                break;
            }
        }
    }
}

void Game::updateMousePositions()
{
    //Updates the mouse poistions relative to the window (Vector2i)
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);

    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}



void Game::getPlayerMode()
{
    char player1Type;
    char player2Type;
    //Gets Player Modes from Command Line

    //Player 1:
    std::cout << "Choose Player 1 Mode:\n1)Player\n2)Easy AI\n3)Medium AI\n4)Hard AI\n";
    while (true)
    {
        std::cout << "Enter an option:" << std::endl;
        std::cin >> player1Type;
        bool inputValid = true;
        switch (player1Type)
        {
        case '1':
            this->player1 = 'p';
            break;
        case '2':
            this->player1 = 'e';
            break;
        case '3':
            this->player1 = 'm';
            break;
        case '4':
            this->player1 = 'h';
            break;
        default:
            std::cout << "Invalid Input!" << std::endl;
            inputValid = false;
        }
        
        if (inputValid)
        {
            break;
        }
    }

    //Player 2:
    std::cout << "Choose Player 2 Mode:\n1)Player\n2)Easy AI\n3)Medium AI\n4)Hard AI\n";
    while (true)
    {
        std::cout << "Enter an option:" << std::endl;
        std::cin >> player2Type;
        bool inputValid = true;
        switch (player2Type)
        {
        case '1':
            this->player2 = 'p';
            break;
        case '2':
            this->player2 = 'e';
            break;
        case '3':
            this->player2 = 'm';
            break;
        case '4':
            this->player2 = 'h';
            break;
        default:
            std::cout << "Invalid Input!" << std::endl;
            inputValid = false;
        }
        
        if (inputValid)
        {
            break;
        }
    }

    std::cout << "Press Enter in the Window to begin game!" << std::endl;
}

void Game::update()
{
    //Update Game Logic


    this->pollEvents();

    if(this->endGame == false)
    {

        if (this->currentPlayer == 1)
        {
            switch (this->player1)
            {
            case 'e':
                this->easyAIMove();
                break;
            case 'm':
                this->mediumAIMove();
                break;
            case 'h':
                this->hardAIMove();
                break;
            default:
                break;
            }

        }

        this->updateMousePositions();

        this->updateShapes();

        this->updateText();

        this->updateTerminalState();

        if (endGame == false)
        {
            //If end game hasn't been reached after the first player moves
        

            if (this->currentPlayer == 2)
            {
                switch (this->player2)
                {
                case 'e':
                    this->easyAIMove();
                    break;
                case 'm':
                    this->mediumAIMove();
                    break;
                case 'h':
                    this->hardAIMove();
                    break;
                default:
                    break;
                }

            }

            this->updateTerminalState();
        }


    }

}


void Game::updateShapes()
{
    /*Updates the shapes in the grid
    Changes shape of empty block when it is pressed
    Keeps track of who the current player is
    */


   //Check if mouse is pressed

   if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
   {
       if (this->mouseHeld == false)
       {
           this->mouseHeld = true;

           for (int i = 0; i < this->gamegrid.size(); ++i)
           {

               if(this->gamegrid[i].symbol == '_' && this->gamegrid[i].emptyBlock.getGlobalBounds().contains(this->mousePosView))
               {
                    //If the grid is empty and the empty block is being pressed

                    //If the current player is player 1
                    if (this->currentPlayer == 1)
                    {
                        this->gamegrid[i].symbol = 'X';
                        this->currentPlayer = 2;

                        //TEST
                        //this->printGamegrid();
                    }
                    else    //if the current player is player 2
                    {
                        this->gamegrid[i].symbol = 'O';
                        this->currentPlayer = 1;
                        

                        //TEST
                        //this->printGamegrid();
                    }


               }
           }
       }
   }
   else
   {
       this->mouseHeld = false;
   }

}

void Game::updateText()
{
    //Updates Text
    std::stringstream ss;
    ss << "Player 1: X\t\t\t" << "Player " << this->currentPlayer << "'s Turn\t\t\t" << "Player 2: O";

    this->uiText.setString(ss.str());

}

void Game::updateStartScreen()
{
    //TEST
    //std::cout << "Updating Starting Screen" << std::endl;

    //Updates the Starting Screen

    this->pollEvents();

    this->updateMousePositions();

    for (int i = 0; i < this->startScreenTextButtons.size(); i++)
    {
        if(this->startScreenTextButtons[i].selected == true)
        {
            this->startScreenTextButtons[i].text.setFillColor(sf::Color::Red);
        }
        else
        {
            this->startScreenTextButtons[i].text.setFillColor(sf::Color::White);
        }
        
    }

    //Check if mouse is pressed

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        //TEST
        //std::cout << "Mouse Pressed!" << std::endl;
    
        if (this->mouseHeld == false)
        {
           this->mouseHeld = true;

            for (int i = 0; i < this->startScreenTextButtons.size(); ++i)
            {

                if(this->startScreenTextButtons[i].collisionBox.getGlobalBounds().contains(this->mousePosView))
                {
                    //If the mouse is being pressed and it is in the collision box's bounds

                    //TEST
                    //std::cout << i << " BUTTON IS PRESSED!" << std::endl;

                    if(i < 4)
                    {
                        for(int j = 0; j < 4; ++j)
                        {
                            this->startScreenTextButtons[j].selected = false;

                            //TEST
                            //std::cout << i << " button is reset to false" << std::endl;
                        }
                    }
                    else
                    {
                        for(int j = 4; j < 8; ++j)
                        {
                            this->startScreenTextButtons[j].selected = false;

                            //TEST
                            //std::cout << i << " button is reset to false" << std::endl;
                        }
                    }

                    this->startScreenTextButtons[i].selected = true;
                    
                    //TEST
                    //std::cout << i << " button is selected!" << std::endl;

                }
            }
        }
    }
    else
    {
        this->mouseHeld = false;
    }
    

    //Updates Player Modes based on Buttons Selected
    if (this->startScreenTextButtons[0].selected)
    {
        this->player1 = 'p';
    }
    else if (this->startScreenTextButtons[1].selected)
    {
        this->player1 = 'e';
    }
    else if (this->startScreenTextButtons[2].selected)
    {
        this->player1 = 'm';
    }
    else if (this->startScreenTextButtons[3].selected)
    {
        this->player1 = 'h';
    }
    if (this->startScreenTextButtons[4].selected)
    {
        this->player2 = 'p';
    }
    else if (this->startScreenTextButtons[5].selected)
    {
        this->player2 = 'e';
    }
    else if (this->startScreenTextButtons[6].selected)
    {
        this->player2 = 'm';
    }
    else if (this->startScreenTextButtons[7].selected)
    {
        this->player2 = 'h';
    }

    //TEST
    //this->printPlayerModes();
    
}

//Render Functions

void Game::renderGrid()
{
    //Create Grid

    //const variables

    //Create shapes
    sf::RectangleShape hLine1(sf::Vector2f(this->screenwidth, this->linewidth));
    sf::RectangleShape hLine2(sf::Vector2f(this->screenwidth, this->linewidth));
    sf::RectangleShape vLine1(sf::Vector2f(this->screenwidth, this->linewidth));
    sf::RectangleShape vLine2(sf::Vector2f(this->screenwidth, this->linewidth));

    //Set Position
    hLine1.setPosition(sf::Vector2f(0.f, this->screenwidth/3.f));
    hLine2.setPosition(sf::Vector2f(0.f, 2.f * this->screenwidth/3.f));
    vLine1.setPosition(sf::Vector2f(this->screenwidth / 3.f, 0.f));
    vLine2.setPosition(sf::Vector2f(2.f * this->screenwidth / 3.f, 0.f));
    //Set Rotation
    vLine1.setRotation(90.f);
    vLine2.setRotation(90.f);
    
    //Render Shapes
    this->window->draw(hLine1);
    this->window->draw(hLine2);
    this->window->draw(vLine1);
    this->window->draw(vLine2);
}

void Game::renderShapes()
{

    double blackBlockWidth = (this->screenwidth - (2.f * this->linewidth)) / 3.f;
    double shapeDistanceApart = blackBlockWidth + this->linewidth;
    //Circle Settings
    double circleRadius = 110.f;
    double circleOutlineWidth = 40.f;


    //Cross Settings
    double lineWidth = 30.f;
    double lineLength = 300.f;


    //Render all Xs and Os
    int gridIndex = 0;
    for (int r = 0; r < 3; ++r){
        for (int c = 0; c < 3; ++c){
            if (gamegrid[gridIndex].symbol == 'X')
            {
                //Draw X

                sf::RectangleShape line1(sf::Vector2f(lineLength, lineWidth));
                sf::RectangleShape line2(sf::Vector2f(lineLength, lineWidth));

                line1.setOrigin(sf::Vector2f(lineLength / 2.f , lineWidth / 2.f));
                line2.setOrigin(sf::Vector2f(lineLength / 2.f , lineWidth / 2.f));

                line1.setRotation(45.f);
                line2.setRotation(135.f);

                line1.setPosition(sf::Vector2f(blackBlockWidth / 2.f + c * shapeDistanceApart , blackBlockWidth / 2.f + r * shapeDistanceApart));
                line2.setPosition(sf::Vector2f(blackBlockWidth / 2.f + c * shapeDistanceApart , blackBlockWidth / 2.f + r * shapeDistanceApart));

                this->window->draw(line1);
                this->window->draw(line2);

            }
            else if (gamegrid[gridIndex].symbol == 'O')
            {
                //Draw O
                sf::CircleShape circle(circleRadius);
                circle.setFillColor(sf::Color::Transparent);
                circle.setOutlineThickness(circleOutlineWidth);
                circle.setOrigin(circleRadius, circleRadius);
                circle.setPosition(sf::Vector2f(blackBlockWidth / 2.f + c * shapeDistanceApart, blackBlockWidth / 2.f + r * shapeDistanceApart));
                this->window->draw(circle);
            }
            else
            {
                //Draw Block
                sf::RectangleShape emptyBlock(sf::Vector2f(blackBlockWidth, blackBlockWidth));
                emptyBlock.setFillColor(sf::Color::Transparent);
                emptyBlock.setOrigin(blackBlockWidth / 2.f, blackBlockWidth / 2.f);
                emptyBlock.setPosition(sf::Vector2f(blackBlockWidth / 2.f + c * shapeDistanceApart, blackBlockWidth / 2.f + r * shapeDistanceApart));
                gamegrid[gridIndex].emptyBlock = emptyBlock;
                this->window->draw(emptyBlock);
            }
            
            ++gridIndex;
        }


    }

    /*
    sf::RectangleShape testRect(sf::Vector2f(blackBlockWidth, 10.f));
    testRect.setFillColor(sf::Color::Red);
    sf::RectangleShape testRect2 = testRect;
    testRect2.setRotation(90.f);
    testRect2.setPosition(sf::Vector2f(10.f, 0.f));
    this->window->draw(testRect2);
    this->window->draw(testRect);
    */


}

void Game::renderText()
{
    //Renders UI Text
    this->window->draw(this->uiText);
}


void Game::render()
{
    //Renders Game

    this->window->clear();
    this->renderGrid();
    this->renderShapes();
    this->renderText();
    this->window->display();
}


//END SCREEN FUNCTIONS


void Game::endScreenRender()
{
    //Renders Game's End Screen

    sf::Text endScreenPrompt;

    //Sets Replay Prompt
    endScreenPrompt.setFont(this->font);
    endScreenPrompt.setCharacterSize(96);
    endScreenPrompt.setFillColor(sf::Color::Blue);
    endScreenPrompt.setString("Press R to Replay");
    endScreenPrompt.setPosition(sf::Vector2f(50.f, this->screenwidth / 2.f + 200.f));

    //Sets End Screen Text

    this->endScreenText.setPosition(sf::Vector2f(15.f, this->screenwidth / 2.f - 50.f));

    this->window->draw(endScreenPrompt);
    this->window->draw(this->endScreenText);

    this->window->display();
}


void Game::startScreenRender()
{
    //Renders Game's Starting Screen

    this->window->clear();



    this->window->draw(this->startScreenTitle);
    this->window->draw(this->startScreenText);

    for (int i = 0; i < this->startScreenTextButtons.size(); i++)
    {
        this->window->draw(this->startScreenTextButtons[i].collisionBox);
        this->window->draw(this->startScreenTextButtons[i].text);
    }

    
    this->window->display();


}


