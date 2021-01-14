
#include "game.h"

int main() {

    bool stillPlaying = true;

    while (stillPlaying)
    {

        Game game;

        //game.getPlayerMode();

        while(game.running() && game.getStartScreen())
        {
            //Start Screen

            //Update Game

            game.updateStartScreen();

            //Render Start Screen

            game.startScreenRender();
        }

        while(game.running() && !game.getEndGame())
        {
            //Update Game

            game.update();

            //Render Game

            game.render();
        }

        while(game.running() && game.replayYesNo != 1)
        {
            //END SCREEN

            //Poll Events

            game.pollEvents();

            //Render End Screen

            game.endScreenRender();

            if (game.replayYesNo == 1)
            {
                stillPlaying = true;
            }
        }

        if (game.replayYesNo == 0)
        {
            stillPlaying = false;
        }

    }

    return 0;
}