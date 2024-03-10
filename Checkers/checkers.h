#ifndef CHECKERS_H
#define CHECKERS_H

// Name: Blake Harkness
// ID: 21004652

// Header file for checkers game.
// This version is for the submission at the start of week 3.

//---------------------------------------------------------------------
// Represents a square on the checkers board, for example A2, or B4
//---------------------------------------------------------------------
class position {
    friend class game_state;		// Allow game state to directly access private parts
  private:         
  int row, col;                     //Internal representation

  public:
    position(void);             // Default constructor

    void from_text( const char *str );	// Sets a position from a string

    char * to_text( void );			// Converts the internal representation to a string

    bool is_valid(void);          // Returns true if the position is valid

    void operator = ( const position &p );  // Copies the contents of a position into this one

    void offset( const int x, const int y ); // Offsets a position by x in the alpha value and y in the numeric value.

};



//---------------------------------------------------------------------
// Represents a move to be made
//---------------------------------------------------------------------
class move {
  private: // Put in your internal representation
    position fromP;
    position toP;
    char moveF[3], moveT[3], amove[6];
  public:
    move( void );          // Default constructor

    move( position &from, position &to ); // From two positions need function to convert hmm

    void from_text( const char *str ); // Converts a string to a move String must be in the form "A4-B3"

    char * to_text( void ); // Converts the internal representation to a string

    void set_from( const position &from );		// Sets the from using a position

    void set_to( const position &to ) ;			// Sets the to using a position

    position &get_from( void );    // Gets either the starting

    position &get_to( void );		// or ending position

    void get_move( void ); // prompts user to input a move

};

//---------------------------------------------------------------------
// The types of pieces
//---------------------------------------------------------------------
enum piece { EMPTY, RED_PAWN, GREEN_PAWN, RED_KING, GREEN_KING };

//---------------------------------------------------------------------
// Represents the state of a game
//---------------------------------------------------------------------
class game_state {
  private:  // Put in your internal representation
    int moveNum; // tracks number of moves
    int whoTurn; // 0 nobody, 1 green, 2 red
    bool gameStatus; // 0 if finished, 1 if playing
    piece squares[4][4]; // represents game board


  public:
    int ai; // 1 for beginner 2 for advanced

    game_state( void ); // Default constructor

    game_state( game_state &g );	// Copy constructor

    ~game_state();			// Destructor: do any tidying up required

    void new_game( void ); 		// Initialises state for the start of a new game

    int get_ai(void);           //prompts user to enter the ai they want to vs

    bool is_game_over( void );	// Check the game status

    bool is_red_turn( void ); //return 1 if red turn

    bool is_green_turn( void ); // return 1 if green turn

    int get_move_number( void ); // How many moves have been played?

    void increment_move( void );	// Increment move number (and state)

    piece get_piece( const position& p ); 	// What piece is at the specified position

    void display(void);                 //displays the current board state in console

    bool check_move(move &m);           // checks if the move is valid

    void make_move(move &m);            // makes move and alters game state

    void winner_print(void);            //Checks if there is a winner, if so prints who

    class move_list * find_moves(void);     // returns movelist of all possible move in current game state

    int evaluate(void);                 // evaluates current board state

    void computer_move(game_state &g);      // makes smartest computer move

    void beginner_move(void);           //Makes random move

    int minimax(game_state&, int, int, int, bool);     //finds the best move
};

class move_list {
 private:

 public:
    move_list( const move &m ); // Constructor

    ~move_list(); // Destructor – removes all items  in the list.

    move_list * add( move_list* m ); // Inserts m into the start of the list, and returns the new start.

    void print(move_list * m); // prints out the move list

    move mm; // The move in the list

    move_list *next; // The next entry in the list.

}
;

#endif // CHECKERS_H
