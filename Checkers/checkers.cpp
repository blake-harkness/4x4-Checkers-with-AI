#include <checkers.h>
#include <iostream>
#include <algorithm>
// Name: Blake Harkness
// ID: 21004652

// Header file for checkers game.
// This version is for the submission at the start of week 3.

//---------------------------------------------------------------------
// Represents a square on the checkers board, for example A2, or B4
//---------------------------------------------------------------------

    position::position(void ){ // Default constructor
        col = 1;
        row = 1;
    };

    void position::from_text( const char *str ){ 	// Sets a position from a string
        col = str[0]- 65;
        row = str[1]- 49;
    };

    char * position::to_text( void ){			// Converts the internal representation to a string
        static char arr[10] = {};
        arr[0] = col +65;
        arr[1] = row +49;
        return arr;
    };

    bool position::is_valid(void){           // Returns true if the position is valid
        bool validity = false;
        if((col >= 0 && col < 4) && (row >= 0 && row <4)){
            validity = true;
        }
        return validity;
    };


    void position::operator = ( const position &p ){  // Copies the contents of a position into this one
        col = p.col;
        row = p.row;
    };

    void position::offset( const int x, const int y ){ // Offsets a position by x in the alpha value and y in the numeric value.
        col = col + x;
        row = row + y;
    };
;

//---------------------------------------------------------------------
// Represents a move to be made
//---------------------------------------------------------------------

    move::move( void ){          // Default constructor

    }
    move::move( position &from, position &to )   // From two positions need function to convert hmm
    {
        fromP = from;
        toP = to;
    }

    void move::from_text( const char *str ){ // Converts a string to a move String must be in the form "A4-B3"
        char str1[3];
        char str2[3];
        for(int i=0; i<=1; i++){
            str1[i] = str[i];
            str2[i] = str[i+3];
        }

        fromP.from_text(str1);
        toP.from_text(str2);
    }

    char * move::to_text( void ){ // Converts the internal representation to a string
        static char str[7];
        str[0] = fromP.to_text()[0];
        str[1] = fromP.to_text()[1];
        str[2] = '-';
        str[3] = toP.to_text()[0];
        str[4] = toP.to_text()[1];

        return str;
    }

    void move::set_from( const position &from ){ // Sets the from using a position
        fromP =from;
    }

    void move::set_to( const position &to ) { 	// Sets the to using a position
        toP = to;
    }

    position &move::get_from( void ){    // Gets either the starting
        return fromP;
    }
    position &move::get_to( void ){  // or ending position
        return toP;
    }


    void move::get_move(void){ //Prompts user to enter a move and stores it
        char input[80];
        std::cout << "Please enter a move" << std::endl;
        std::cin >>  input;
        from_text(input);
    }





//---------------------------------------------------------------------
// Represents the state of a game
//---------------------------------------------------------------------

    game_state::game_state( void ){ // Default constructor
        new_game();
    };

    game_state::game_state( game_state &g ){ ;	// Copy constructor
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                squares[i][j] = g.squares[i][j];
            }
        }
        moveNum = g.moveNum;
        gameStatus = g.gameStatus;
        whoTurn = g.whoTurn;
    }

    game_state::~game_state(){// Destructor: do any tidying up required

    }

    void game_state::new_game( void ){ 		// Initialises state for the start of a new game
        std::cout << "Hello! Welcome to Blake's Checkers"<< std::endl << "There are three different gamemodes, Beginner AI, Advanced AI or 2 Player"<< std::endl <<
        std::endl << "For Beginner AI please press 1, For Advanced AI please press 2, For 2 Player please press 3" << std::endl;

        ai = get_ai();

        moveNum = 0;
        whoTurn = 1;
        gameStatus = true;
        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                squares[i][j] = EMPTY;
            }
        }
        squares[1][0] = GREEN_PAWN;  // 1 less than intending as array starts at 0
        squares[3][0] = GREEN_PAWN;
        squares[0][3] = RED_PAWN;
        squares[2][3] = RED_PAWN;
    }

    bool game_state::is_game_over( void ){ // Check the game status
        if(moveNum >= 40 || gameStatus == 0){
            whoTurn =0;
            return true;
        }
        else {
            return false;
        }
    }

    int game_state::get_ai(void){ //works out what AI the players wants to go against (Or player vs player)

        char aichar =  'k'; // generic initilising
        std::cin >> aichar;
        aichar = aichar - 48; // conversion to 1 2 or 3
        if(aichar != 1 && aichar != 2 && aichar !=3) {
            std::cout << "Invalid AI type, please enter 1 for Beginner, 2 for Advanced" << std::endl;
            get_ai();
        }

        std::cout << std::endl << "Perfect! You are now playing ";
        if(aichar == 1) std::cout << "Beginner AI" << std::endl << std::endl;
        if(aichar == 2) std::cout << "Advanced AI" << std::endl << std::endl;
        if(aichar == 3) std::cout << "Player vs Player" << std::endl << std::endl;

        return aichar;
    }
    bool game_state::is_red_turn( void ){  //checks red turn
        if(whoTurn == 2){
            return true;
        }
        else{
            return false;
        }
    }

    bool game_state::is_green_turn( void ){ //checks green turn
        if(whoTurn == 1){
            return true;
        }
        else{
            return false;
        }
    }

    int game_state::get_move_number( void ){ // How many moves have been played?
        return moveNum;
    };
    void game_state::increment_move( void )	{// Increment move number (and state)
        moveNum += 1;
    }

    piece game_state::get_piece( const position& p ){// What piece is at the specified position
        int xpos = p.col;
        int ypos = p.row;
        return squares[xpos][ypos];
    }

    void game_state::display(void){                //displays current game board
        int red_pieces = 0;
        int green_pieces = 0;

        if(moveNum != 0) std::cout <<" " << std::endl;

        if(ai == 1) std::cout << "Beginner AI" << std::endl;
        if(ai == 2) std::cout << "Advanced AI" << std::endl;

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                if(squares[i][j] == RED_KING || squares[i][j] == RED_PAWN){
                    red_pieces = red_pieces +1;
                }
                if(squares[i][j] == GREEN_KING || squares[i][j] == GREEN_PAWN){
                    green_pieces = green_pieces +1;
                }
            }
        }

        if(green_pieces == 0 || red_pieces == 0) whoTurn =0;

        std::cout <<"Numbers of moves made : " <<  moveNum << std::endl;
        std::cout << "Players Turn : ";
        if(whoTurn ==0 ){std::cout << "Nobody" << std::endl;};
        if(whoTurn ==1 ){std::cout << "Green" << std::endl;};
        if(whoTurn ==2 ){std::cout << "Red" << std::endl;};

        std::cout << " " << std::endl << "     A      B      C      D   ";
        for(int i =3; i>-1; i--){
           std::cout << " " << std::endl << "  ---------------------------";

           if(i == 3) {std::cout << std::endl << "4";}
           if(i == 2) {std::cout << std::endl << "3";}
           if(i == 1) {std::cout << std::endl << "2";}
           if(i == 0) {std::cout << std::endl << "1";}

            for(int j = 0; j<4; j++){

                if(squares[j][i] == RED_PAWN){
                    std::cout << " | rp |";
                }
                if(squares[j][i] == GREEN_PAWN ){
                    std::cout << " | gp |";
                }
                if(squares[j][i] == EMPTY){
                    std::cout << " |    |";
                }
                if(squares[j][i] == RED_KING){
                    std::cout << " | RK |";
                }
                if(squares[j][i] == GREEN_KING){
                    std::cout << " | GK |";
                }
            }

        }
        std::cout << std::endl;
        std::cout << "  ---------------------------";
        std::cout << " " << std::endl;

        winner_print();

        move_list *head = find_moves();
        if(gameStatus == 1) head -> print(head);       // prints available moves if game is continuing

    }

    void game_state::winner_print(){             // checks if there is a winner if so prints who
        int red_pieces = 0;
        int green_pieces = 0;

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                if(squares[i][j] == RED_KING || squares[i][j] == RED_PAWN){
                    red_pieces = red_pieces +1;
                }
                if(squares[i][j] == GREEN_KING || squares[i][j] == GREEN_PAWN){
                    green_pieces = green_pieces +1;
                }
            }
        }

        if(red_pieces == 0){
            gameStatus =0;
            std::cout << "Green has won the game, thanks for playing" << std::endl;
        }
        if(green_pieces == 0){
            gameStatus = 0;
            std::cout << "Red has won the game, thanks for playing" << std::endl;
        }
    }

    bool game_state::check_move(move &m){        //Checks moves are valid
        position fromP = m.get_from();
        position toP = m.get_to();
        position temp2 = toP;

        //check if there is a piece on the tile return false
        if (m.get_from().is_valid() == false || m.get_to().is_valid() == false) {return false;};

        //check if they are trying to use the other persons piece
        if(is_green_turn() == true){
            if(get_piece(m.get_from()) == RED_KING){ return false;};
            if(get_piece(m.get_from()) == RED_PAWN){return false;};
        }
        if(is_red_turn() == true){
            if(get_piece(m.get_from()) == GREEN_KING){ return false;};
            if(get_piece(m.get_from()) == GREEN_PAWN){return false;};
        }

        //Checking positions are not empty
        if(get_piece(m.get_to()) != EMPTY) {return false;};
        if(get_piece(m.get_from()) == EMPTY) {return false;};

        //Checking not moving to current position
        if(toP.row - fromP.row == 0 || toP.col - fromP.col ==0) {return false;};

        //Checking not moving 3 or more away
        if(abs(toP.col - fromP.col) >= 3) return false;
        if(abs(toP.row - fromP.row) >= 3) return false;

        //if it is green pw cannot go backwards
        if((get_piece(m.get_from()) == GREEN_PAWN) && (toP.row < fromP.row)){return false;};
        if((get_piece(m.get_from()) == RED_PAWN) && (toP.row > fromP.row)){return false;};

        //Checking jumps are valid
        if((abs(fromP.row - toP.row) == 2) && (abs(fromP.col - toP.col) == 2)){

            if(toP.col - fromP.col == -2 && toP.row - fromP.row == -2 ){
                temp2.col = toP.col+1;
                temp2.row = toP.row+1;
            }
            if(toP.col - fromP.col == -2 && toP.row - fromP.row == 2 ){
                temp2.col = toP.col+1;
                temp2.row = toP.row-1;
            }
            if(toP.col - fromP.col == 2 && toP.row - fromP.row == -2 ){
                temp2.col = toP.col-1;
                temp2.row = toP.row+1;
            }
            if(toP.col - fromP.col == 2 && toP.row - fromP.row == 2 ){
                temp2.col = toP.col-1;
                temp2.row = toP.row-1;
            }
            if(is_red_turn() == true){
                if((get_piece(temp2) == RED_PAWN) || (get_piece(temp2) == RED_KING) || (get_piece(temp2)== EMPTY) ) {return false;};
            }
           if(is_green_turn() == true){
                if((get_piece(temp2) == GREEN_PAWN) || (get_piece(temp2) == GREEN_KING) || (get_piece(temp2) == EMPTY) ) {return false;};
            }

}
        //Checks diagonality of a move
        if(abs(toP.col - fromP.col) == 2 && !(abs(toP.row - fromP.row) == 2)) return false;
        if(abs(toP.col - fromP.col) == 1 && !(abs(toP.row - fromP.row) == 1)) return false;
        if(abs(toP.row - fromP.row) == 2 && !(abs(toP.col - fromP.col) == 2)) return false;
        if(abs(toP.row - fromP.row) == 1 && !(abs(toP.col - fromP.col) == 1)) return false;

        return true;
}

    void game_state::make_move(class move &m){              //Makes move and alters game board and state
        if (check_move(m) == false){
            std::cout << "Invalid Move, Please enter a valid move" << std::endl;
            display();
            move temp;
            temp.get_move();
            make_move(temp);
            return;
        }

        else{

        position temp;
        temp.row = m.get_to().row;
        temp.col = m.get_to().col;

        moveNum = moveNum +1;

        squares[m.get_to().col][m.get_to().row] = get_piece(m.get_from());
        squares[m.get_from().col][m.get_from().row] = EMPTY;

        //if the jump was offset by 2 then set the middle tile to empty
        if(m.get_to().col - m.get_from().col == 2 && m.get_to().row - m.get_from().row == 2 ){
            temp.col = m.get_to().col-1;
            temp.row = m.get_to().row-1;
            squares[temp.col][temp.row] = EMPTY;
        }
        if(m.get_to().col - m.get_from().col == -2 && m.get_to().row - m.get_from().row == 2 ){
            temp.col = m.get_to().col+1;
            temp.row = m.get_to().row-1;
            squares[temp.col][temp.row] = EMPTY;
        }
        if(m.get_to().col - m.get_from().col == 2 && m.get_to().row - m.get_from().row == -2 ){
            temp.col = m.get_to().col-1;
            temp.row = m.get_to().row+1;
            squares[temp.col][temp.row] = EMPTY;
        }
        if(m.get_to().col - m.get_from().col == -2 && m.get_to().row - m.get_from().row == -2 ){
            temp.col = m.get_to().col+1;
            temp.row = m.get_to().row+1;
            squares[temp.col][temp.row] = EMPTY;
        }

        //If it was red turn switch to green visa versa
        if(whoTurn == 1 )
        {
            whoTurn = 2;
        }
        else if(whoTurn == 0){

        }
        else
        {
            whoTurn = 1;
        }

       // if pawn reaches end change it to a king
        if(squares[0][3] == GREEN_PAWN) {squares[0][3] = GREEN_KING;};
        if(squares[2][3] == GREEN_PAWN) {squares[2][3] = GREEN_KING;};
        if(squares[1][0] == RED_PAWN) {squares[1][0] = RED_KING;};
        if(squares[3][0] == RED_PAWN) {squares[3][0] = RED_KING;};
        }

        int red_pieces{0}, green_pieces{0};

        for(int i = 0; i<4; i++){
            for(int j = 0; j<4; j++){
                if(squares[i][j] == RED_KING || squares[i][j] == RED_PAWN){
                    red_pieces = red_pieces +1;
                }
                if(squares[i][j] == GREEN_KING || squares[i][j] == GREEN_PAWN){
                    green_pieces = green_pieces +1;
                }
            }
        }
}

    move_list * game_state::find_moves(void){ //Finds all the possible moves and stores into linked list

        move_list *head = NULL;
        position tempF, tempT;

        for(int i =3; i>-1; i--){
            for(int j = 0; j<4; j++){
                if(is_green_turn() == true){
                   if(squares[i][j] == GREEN_KING || squares[i][j] == GREEN_PAWN){
                       tempF.col = i;
                       tempF.row = j;

                       for(int z = 3; z >-1; z--){
                           for(int t = 0; t <4; t++){
                               tempT.col = z;
                               tempT.row = t;
                               move temp(tempF, tempT);
                               if(check_move(temp) == true){
                                    if(head == NULL){head = new move_list(temp);}
                                    else{head = head->add(new move_list(temp));}
                               }
                           }
                       }
                   }
                }

                if(is_red_turn() == true){
                   if(squares[i][j] == RED_KING || squares[i][j] == RED_PAWN){
                       tempF.col = i;
                       tempF.row = j;

                       for(int z = 3; z >-1; z--){
                           for(int t = 0; t <4; t++){
                               tempT.col = z;
                               tempT.row = t;
                               move temp(tempF, tempT);
                               if(check_move(temp) == true){
                                    if(head == NULL){head = new move_list(temp);}
                                    else{head = head->add(new move_list(temp));}
                               }
                           }
                       }
                   }
                }
            }
        }

        return head;

    }



    int game_state::evaluate(void){                              //Evaluates current board
        int rking = 0; int rpawn =0; int gking = 0; int gpawn = 0; int score = 0;

         for(int i = 0; i<4; i++){
             for(int j = 0; j<4; j++){
                 if(squares[i][j] == RED_KING) rking = rking + 1;
                 if(squares[i][j] == RED_PAWN) rpawn = rpawn + 1;
                 if(squares[i][j] == GREEN_KING) gking = gking + 1;
                 if(squares[i][j] == GREEN_PAWN) gpawn = gpawn + 1;
             }
         }
         score = (rpawn - gpawn) + 2*(rking - gking); //Score gives extra weighting to kings as they are more desired

         return score;
    }

    void game_state::computer_move(game_state &g){           //Makes the best move for the computer player

        if (g.ai == 1) {
            beginner_move();
            return;
        }
        else{
         int bestScore = -1000;
         move bestMove;
         move_list * test = find_moves();
         game_state gstate = g;

         for(move_list * p = test; p != NULL; p = p-> next){
                 gstate.make_move(p->mm);
                 int score = gstate.minimax(gstate, 10,-1000,1000, false); // set depth of 10 which is more than sufficent for this size of board and has no speed issues
                 gstate = g;
                 if (score > bestScore){
                     bestScore = score;
                     bestMove = (p->mm);
                 }
         }
          make_move(bestMove);
        }
    }

    void game_state::beginner_move(void){ //Selects a random move from movelist
        move arraymoves[10];
        move bestMove;
        move_list * test = find_moves();
        int availableMoves = 0;

        for(move_list * p = test; p != NULL; p = p-> next){   //for each avaialble move store the move in array and add count to available moves
            arraymoves[availableMoves] = (p->mm);
            availableMoves = availableMoves + 1;
            }

        int randomMove = rand()%(availableMoves-1 + 1)+1;  //Picks a random number between the min 1 and max availableMoves
        bestMove = arraymoves[randomMove-1];
        if(availableMoves == 1) bestMove = arraymoves[0];   //Had strange bug where it wouldn't work if there was only 1 move so this fixed

        make_move(bestMove);
    }

    int game_state::minimax(game_state &g, int depth, int alpha, int beta, bool maxplay){ //Finds the best possible computer move

        //Time complexity without Alpha-Beta pruning is O(b^m) where b is number of legal moves and m is maximum depth
        //With Alpha-Beta pruning we can speed up this process to be O(b^(d/2))

         game_state gstate = g;
         move_list* test = find_moves();

         if (depth == 0 || gstate.gameStatus == 0){
             return g.evaluate();
         }

         if (maxplay == true){           //If it is computer turn wants to find best move / max
             int maxEval = -10000;

             for(move_list * p = test; p != NULL; p = p-> next){
                 gstate.make_move(p->mm);
                 int eval = gstate.minimax(gstate, depth -1, alpha, beta, false);
                 gstate = g;

                 maxEval = std::max(maxEval, eval);
                 alpha = std::max(alpha, eval);
                 if (beta <= alpha) break;
                 }

             return maxEval;
             }

         else{                       //else is players move so wants to find worst move / min
             int minEval = 10000;

             for(move_list * p = test; p != NULL; p = p-> next){
                 gstate.make_move(p->mm);
                 int eval = gstate.minimax(gstate, depth -1, alpha, beta, true);
                 gstate = g;

                 minEval = std::min(minEval, eval);
                 beta = std::min(beta, eval);
                 if (beta <= alpha) break;
                 }

             return minEval;
             }
         }

    //---------------------------------------------------------------------
    // Represents the list of possible moves
    //---------------------------------------------------------------------

    move_list::move_list( const move &m ){// Constructor
        mm = m;
        next = NULL;
    }

    move_list::~move_list(){ // Destructor – removes all items  in the list.
        if(next != NULL) delete next;
    };

   move_list* move_list::add( move_list* m ){// Inserts m into the start of the list, and returns the new start.

        m->next = this;

        return m;
    }

   void move_list::print(move_list * m){                     //Prints out potential moves from linked list
       std::cout << "Here is a list of potential moves" << std::endl;
       for(move_list * p = m; p != NULL;p = p-> next){
           std::cout << p->mm.to_text() << std::endl;
       }
   }
