/**
 * @file ThirdBeast.cpp
 * @author mathew Saxby David Celesti
 * @brief The starter file
 * @date 2024-5-06
 */

#include "ThirdBeast.h"

#include <cstdlib> 
#include <ctime>   


// Write your AI's name here. Please don't make it more than 64 bytes.
#define AI_NAME "ThirdBeast"

// Write your name(s) here. Please don't make it more than 64 bytes.
#define AUTHOR_NAMES "David Celesti, Mathew Saxby"


/*================================================================================
 * Starts up the entire match. Do NOT change anything here unless you really understand
 * what you are doing.
 *================================================================================*/
int main(int argc, char *argv[]) {
    // player must have the socket path as an argument.
    if ( argc != 2 ) {
        printf("%s Error: Requires socket name! (line: %d)\n", AI_NAME, __LINE__);
        return -1;
    }
    char *socket_path = argv[1];
    
    // set random seed
    srand(getpid());

    ThirdBeast my_player = ThirdBeast();
    return my_player.play_match(socket_path, AI_NAME, AUTHOR_NAMES);
}

ThirdBeast::ThirdBeast():Player() {
    return;
}

ThirdBeast::~ThirdBeast() {
    return;
}

/*================================================================================
 * This is like a constructor for the entire match.
 * You probably don't want to make changes here unless it is something that is done once at the beginning 
 * of the entire match..
 *================================================================================*/
void ThirdBeast::handle_setup_match(PlayerNum player, int board_size) {
    this->player = player;
    this->board_size = board_size;
    create_boards();
    create_shot_count_board();
    return;
}

/*================================================================================
 * This is like a constructor for one game/round within the entire match.
 * Add anything here that you need to do at the beginning of each game.
 *================================================================================*/
void ThirdBeast::handle_start_game() {
    clear_boards();
    return;
}

/*================================================================================
placing Ships
 *================================================================================*/

Ship ThirdBeast::choose_ship_place(int ship_length) {
        Ship ship;
        ship.len = ship_length;
        ship.len = ship_length;
        ship.row = 1;
        ship.col = 1;
        ship.dir = VERTICAL;
        bool ship_okay = false;

        // for(int i=0; i<board_size; i++){
        //     for(int j=0; j<board_size; j++){
        //         cout << ship_board[i][j];
        //     }
        //     cout << endl;
        // }
        // cout << endl;

        while (true) {
            ship.row = rand() % (this->board_size); 
            ship.col = rand() % (this->board_size); 
            ship.dir = rand() % 2 == 0 ? HORIZONTAL : VERTICAL; // Random direction
            ship_okay = true;



    //1st set of games==== smaller board size, and  not touching.
            if(game_number<100){    

            //make sure in bounds 
                if (ship.dir == HORIZONTAL) {
                    if (ship.col + ship.len > this->board_size -1 ) {
                        ship_okay = false;
                    } 
                    else {
                        for (int len = 0; len < ship.len; len++) {
                            //check overlap
                            if (this->ship_board[ship.row][ship.col + len] != WATER) {
                                ship_okay = false;
                                break;
                            }
                            
                        }
                        for (int len = 0; len < ship.len; len++) {
                            // dont let ships be near eachother
                            if (ship.col + len > 0 && ship.col + len < this->board_size - 1 &&
                                (this->ship_board[ship.row][ship.col + len - 1] == SHIP ||
                                this->ship_board[ship.row][ship.col + len + 1] == SHIP ||
                                this->ship_board[ship.row][ship.col + len] == SHIP)) {

                                ship_okay = false;
                                break;
                            }
                        }
                    } 
                } 
                
                // inbounds but for vertical
                else {
                    //make sure in bounds
                    if (ship.row + ship.len > this->board_size  -1 ) {
                        ship_okay = false;} 
                    else {
                        for (int len = 0; len < ship.len; len++) {
                            // make sure not overlapping
                            if (this->ship_board[ship.row + len][ship.col] != WATER) {
                                ship_okay = false;
                                break;
                            }
                        }
                        for (int len = 0; len < ship.len; len++) {
                            // dont let ships be near eachother
                            if (ship.row + len > 0 && ship.row + len < this->board_size - 1 &&
                                (this->ship_board[ship.row + len - 1][ship.col] == SHIP ||
                                this->ship_board[ship.row + len + 1][ship.col] == SHIP ||
                                this->ship_board[ship.row + len][ship.col] == SHIP)) {

                                    ship_okay = false;
                                    break;
                            }
                        }
                    } 
                }


                //if placement is good then go forr it
                //PUTTING SHIP
                if (ship_okay == true ) {
                    if (ship.dir == HORIZONTAL) {
                        for (int len = 0; len < ship.len; len++) {
                            this->ship_board[ship.row][ship.col + len] = SHIP;
                        }
                    } 
                    if(ship.dir == VERTICAL) {
                        for (int len = 0; len < ship.len; len++) {
                            this->ship_board[ship.row + len][ship.col] = SHIP;
                        }
                    }  
                    return ship;
                }
            } 
            
    
     //game set 2================ bigger board size not touching(game_number>150)&&(game_number<=250)
           if(game_number>=100 && game_number<250){    
            //make sure in bounds
                if (ship.dir == HORIZONTAL) {
                    if (ship.col + ship.len > this->board_size ) {
                        ship_okay = false;
                    } 
                    else {
                        for (int len = 0; len < ship.len; len++) {
                            //check overlap
                            if (this->ship_board[ship.row][ship.col + len] != WATER) {
                                ship_okay = false;
                                break;
                            }
                        }
                        for (int len = 0; len < ship.len; len++) {
                            // dont let ships be near eachother
                            if (ship.col + len > 0 && ship.col + len < this->board_size - 1 &&
                                (this->ship_board[ship.row][ship.col + len - 1] == SHIP ||
                                this->ship_board[ship.row][ship.col + len + 1] == SHIP ||
                                this->ship_board[ship.row][ship.col + len] == SHIP)) {

                                ship_okay = false;
                                break;
                            }
                        }
                    }

                } //for vertical
                else {
                    //make sure in bounds
                    if (ship.row + ship.len > this->board_size ) {
                        ship_okay = false;} 
                    else {
                        for (int len = 0; len < ship.len; len++) {
                            // make sure not overlapping
                            if (this->ship_board[ship.row + len][ship.col] != WATER) {
                                ship_okay = false;
                                break;
                            } 
                            
                        }
                        for (int len = 0; len < ship.len; len++) {
                            // dont let ships be near eachother
                            if (ship.row + len > 0 && ship.row + len < this->board_size - 1 &&
                                (this->ship_board[ship.row + len - 1][ship.col] == SHIP ||
                                this->ship_board[ship.row + len + 1][ship.col] == SHIP ||
                                this->ship_board[ship.row + len][ship.col] == SHIP)) {

                                    ship_okay = false;
                                    break;
                            }
                        }
                    }  
                }
                
                //if placement is good then go forr it
                if (ship_okay == true ) {
                    if (ship.dir == HORIZONTAL) {
                        for (int len = 0; len < ship.len; len++) {
                            this->ship_board[ship.row][ship.col + len] = SHIP;
                        }
                    } 
                    if(ship.dir == VERTICAL) {
                        for (int len = 0; len < ship.len; len++) {
                            this->ship_board[ship.row + len][ship.col] = SHIP;
                        }
                    }  
                    return ship;
                }
            }      

    //third half of games=========  no middle board and yes touching.
            if(game_number>=250){  
                // //code to make sure ships are not in middle square 
                if((ship.dir == VERTICAL)&& (
                   ((ship.row > board_size / 2 -1 && ship.row <= board_size / 2 + 2) && 
                   (ship.col > board_size / 2 -1 && ship.col <= board_size / 2 + 2))|| 
                   (((ship.row + ship.len) > board_size / 2 -1 && (ship.row + ship.len) <= board_size / 2 + 2) && 
                   (ship.col > board_size / 2 -1 && ship.col <= board_size / 2 + 2)))){

                    ship_okay = false;
                   }
                if((ship.dir == HORIZONTAL)&& (
                   ((ship.row > board_size/2-1 && ship.row <= board_size/2+2) && 
                   (ship.col > board_size/2-1 && ship.col <= board_size/2+2)) || 
                   (((ship.col + ship.len) > board_size/2-1 && (ship.col + ship.len) <= board_size/2+2) && 
                   (ship.row > board_size/2-1 && ship.row <= board_size/2+2)))){

                    ship_okay = false;
                }      

                //make sure in bounds
                if (ship.dir == HORIZONTAL) {
                    
                    //in boundaries
                    if  (ship.col + ship.len > this->board_size) {
                        ship_okay = false;
                    } 
                    else {
                        for (int len = 0; len < ship.len; len++) {
                            //check overlap
                            if (this->ship_board[ship.row][ship.col + len] != WATER) {
                                ship_okay = false;
                                break;
                            }
                        }
                        for (int len = 0; len < ship.len; len++) {
                            // dont let ships be near eachother
                            if (ship.col + len > 0 && ship.col + len < this->board_size - 1 &&
                                (this->ship_board[ship.row][ship.col + len - 1] == SHIP ||
                                this->ship_board[ship.row][ship.col + len + 1] == SHIP ||
                                this->ship_board[ship.row][ship.col + len] == SHIP)) {

                                ship_okay = false;
                                break;
                            }
                        }
                    } 
                }
                //for vertical
                else{
                    //make sure in bounds
                    if  (ship.row + ship.len > this->board_size) {
                        ship_okay = false;
                    } 
                    else {
                        for (int len = 0; len < ship.len; len++) {
                            // make sure not overlapping
                            if (this->ship_board[ship.row + len][ship.col] != WATER) {
                                ship_okay = false;
                                break;
                            }
                        }
                        for (int len = 0; len < ship.len; len++) {
                            // dont let ships be near eachother
                            if (ship.row + len > 0 && ship.row + len < this->board_size - 1 &&
                                (this->ship_board[ship.row + len - 1][ship.col] == SHIP ||
                                this->ship_board[ship.row + len + 1][ship.col] == SHIP ||
                                this->ship_board[ship.row + len][ship.col] == SHIP)) {

                                    ship_okay = false;
                                    break;
                            }
                        }
                    }

                }

                //if placement is good then go forr it
                if (ship_okay == true ) {
                    if (ship.dir == HORIZONTAL) {
                        for (int len = 0; len < ship.len; len++) {
                            this->ship_board[ship.row][ship.col + len] = SHIP;
                        }
                    } 
                    if(ship.dir == VERTICAL) {
                        for (int len = 0; len < ship.len; len++) {
                            this->ship_board[ship.row + len][ship.col] = SHIP;
                        }
                    }  
                    return ship;
                }
            }
        
         }
        ship.row=-1;
        ship.col=-1;
        return ship;

}

//vertical weight =======================
//========================================
int ThirdBeast::vVal(int row, int col) {
    if (row < 0 || row >= board_size || col < 0 || col >= board_size || shot_board[row][col] != WATER)
        return -100; // Out of bounds or already shot at

    int height = 1;
    double bonus = 0;

    // Check upwards
    for (int i = 1; i < 4; i++) {
        if (row + i < board_size) {
            char ch = shot_board[row + i][col];
            if (ch == MISS || ch == KILL)
                break;
            if (ch == WATER || ch == HIT)
                height++;
            if (ch == HIT)
                bonus += 1.0 /i;
        }
    }

    // Check downwards
    for (int i = 1; i < 4; i++) {
        if (row - i >= 0) {
            char ch = shot_board[row - i][col];
            if (ch == MISS || ch == KILL)
                break;
            if (ch == WATER || ch == HIT)
                height++;
            if (ch == HIT)
                bonus += 1.0 /i;
        }
    }

    if (height < 3)
        return 0;
    else
        return height + static_cast<int>(bonus*110);

}
//horizontal weight =======================
//========================================
int ThirdBeast::hVal(int row, int col) {
    if (row < 0 || row >= board_size || col < 0 || col >= board_size || shot_board[row][col] != WATER)
        return -100; // Out of bounds or already shot at

    int width = 1;
    double bonus = 0;

    // Check upwards
    for (int i = 1; i < 4; i++) {
        if (col + i < board_size) {
            char ch = shot_board[row][col+i];
            if (ch == MISS || ch == KILL)
                break;
            if (ch == WATER || ch == HIT)
                width++;
            if (ch == HIT)
                bonus += 1.0 /i;
        }
    }

    // Check downwards
    for (int i = 1; i < 4; i++) {
        if (col- i >= 0) {
            char ch = shot_board[row][col-i];
            if (ch == MISS || ch == KILL)
                break;
            if (ch == WATER || ch == HIT)
                width++;
            if (ch == HIT)
                bonus += 1.0 /i;
        }
    }

    if (width < 3)
        return 0;
    else
        return width + static_cast<int>(bonus*110);
}

/*================================================================================
 how to decide where to shoot and inform the contest controller
 *================================================================================*/

Shot ThirdBeast::choose_shot() {
    Shot shot;
    shot.row = 0;
    shot.col = 0;
    double best_val= -2000;
    

    for (int row = 0; row < this->board_size; row++) {
        for (int col = 0; col < this->board_size; col++) {
            double val = hVal(row,col) + vVal(row,col);
            //if there is something valid in val, its not a miss, and not a horrible idea(surrounded by misses) then apply learning
            // take val and += history heatmap divide by 10


            //sets value to very low if all shots surrounding it are misses
            if (row > 0 && row < this->board_size - 1 && col > 0 && col < this->board_size - 1 &&
                shot_board[row - 1][col] == MISS && shot_board[row + 1][col] == MISS &&
                shot_board[row][col - 1] == MISS && shot_board[row][col + 1] == MISS) {
                    val = -5000;
            }

         else{   
            // Access the shot count at position (row, col) on the shot_count_board
            double learnedIt = shot_count_board[row][col];
                
            val+=(learnedIt / 100);

            if (val > 0) {
                int remaining_enemy_ships = count_remaining_enemy_ships();
                val *= (1 + (remaining_enemy_ships * 0.1)); // Increase value based on remaining enemy ships
            }
         } 

            if( val > best_val ){
                best_val=val;
                shot.row=row;
                shot.col=col;
            }
        }
    }
    return shot;
 
} 


/*================================================================================
 * This function is called to inform your AI of the result o}f a previous shot,
 * as well as where the opponent has shot.
 *========================================================:========================*/
void ThirdBeast::handle_shot_return(PlayerNum player, Shot &shot) {
    // Results of your AI's shot was returned, store it
    if ( player == this->player ) {
        this->shot_board[shot.row][shot.col] = shot.value;
        if (shot.value == HIT){
            this->shot_count_board[shot.row][shot.col]++;
        }
    }

    // Your AI is informed of where the opponent AI shot, store it
    // NOTE: Opponent shots are stored in ship_board, not shot_board
    else {
        this->ship_board[shot.row][shot.col] = shot.value;
    }
    return;
}

/*================================================================================
 * This function is called to update your shot_board (results of your shots at
 * opponent) when an opponent ship has been killed, OR to update your ship_board
 * (where you keep track of your ships) to show that your ship was killed.
 *================================================================================*/
void ThirdBeast::handle_ship_dead(PlayerNum player, Ship &ship) {
    // store the ship that was killed
    for (int i = 0; i < ship.len; i++) {
        if ( player == this->player ) { // your ship is dead
            if      (ship.dir == HORIZONTAL) {
                this->ship_board[ship.row][ship.col+i] = KILL;
                //this->prob_board[ship.row][ship.col+i] = KILL;
            }
            else if (ship.dir == VERTICAL)   {
                this->ship_board[ship.row+i][ship.col] = KILL;
                //this->prob_board[ship.row+i][ship.col] = KILL;
            }    
        } else {             // their ship is dead
            if      (ship.dir == HORIZONTAL) {
                this->shot_board[ship.row][ship.col+i] = KILL;
               // this->prob_board[ship.row][ship.col+i] = KILL;
            }
            else if (ship.dir == VERTICAL)   {
                this->shot_board[ship.row+i][ship.col] = KILL;
               // this->prob_board[ship.row+i][ship.col] = KILL;
            }
        }

    }
    return;
}

//test to add remaining enemy ships
int ThirdBeast::count_remaining_enemy_ships() {
    int count = 0;

    // Iterate over the ship board
    for (int row = 0; row < this->board_size; row++) {
        for (int col = 0; col < this->board_size; col++) {
            if (this->ship_board[row][col] == SHIP) {
                // Increment count if the cell contains an enemy ship
                count++;
            }
        }
    }

    return count;
}

/*================================================================================
 * This function runs at the end of a particular game/round.
 * Do anything here that needs to be done at the end of a game/round in the match.
 *================================================================================*/
int ThirdBeast::game_number = 0;

void ThirdBeast::handle_game_over() {
   game_number++;
    return;
}

/*================================================================================
 * This function is called by the AI's destructor and runs at the end of the entire match.
 *================================================================================*/
void ThirdBeast::handle_match_over() {
    delete_boards();
    return;

}

/*================================================================================
 * This function sets up all boards at the beginning of the whole match.
 * Add setup here for any boards you create.
 *================================================================================*/
void ThirdBeast::create_boards() {
    int size = this->board_size;

    // dynamically create an array of pointers.
    this->ship_board = new char*[size];
    this->shot_board = new char*[size];
  
    

    // dynamically allocate memory of size `board_size` for each row.
    for (int i = 0; i < size; i++) {
        this->ship_board[i] = new char[size];
        this->shot_board[i] = new char[size];
    
    }
    return;
}
//attempt at my shot history 
void ThirdBeast::create_shot_count_board() {
        int size = this->board_size;
        this->shot_count_board = new int*[size];
        for (int i = 0; i < size; i++) {
            this->shot_count_board[i] = new int[size];
            for (int j = 0; j < size; j++) {
                this->shot_count_board[i][j] = 0; // Initialize all counts to 0
            }
        }
    }

/*================================================================================
 * This function resets boards between rounds.
 *================================================================================*/
void ThirdBeast::clear_boards() {
    // assign WATER to the boards

    for (int i = 0; i < this->board_size; i++) {
        for (int j = 0; j < this->board_size; j++) {
            this->ship_board[i][j] = WATER;
            this->shot_board[i][j] = WATER;
        }
    }
    return;
}

/*================================================================================
 * This function is called by the AI's destructor and runs at the end of the entire match.
 *================================================================================*/
void ThirdBeast::delete_boards() {
    // deallocates memory using the delete operator

    for (int i = 0; i < this->board_size; i++) {
        delete[] this->ship_board[i];
        delete[] this->shot_board[i];
        
    }
    delete[] this->ship_board;
    delete[] this->shot_board;
    
  
    return;
}

