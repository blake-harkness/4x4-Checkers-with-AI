#include <iostream>
#include "checkers.h"

int main()
{

    game_state game;
    game.display();

    move b;
    while (game.is_game_over() != 1){

        if(game.is_red_turn() && game.ai != 3) {
            game.computer_move(game);
            game.display();
       }
        else{
            if(game.is_game_over() == false) b.get_move();
            game.make_move(b);
            game.display();
        }
    }
}


