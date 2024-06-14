#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int board[3][3];
} puzzleBoard;

typedef struct {
    int board[3][3];
} checkBoard;

int menu();
void swap(int *num1 , int *num2);
void shuffle_board(puzzleBoard *puzzle);
int print_board(puzzleBoard *puzzle);
int save_board(puzzleBoard *puzzle);
int check_solved(puzzleBoard *puzzle , checkBoard *check_board);
int calculate_score(int numofMoves);
int update_score(int score);
int find_tile_coord(puzzleBoard *puzzle, int *row, int *col);
int move_tile(puzzleBoard *puzzle , int number , char direction);
int auto_finish(puzzleBoard *puzzle , int *numofMoves , checkBoard *check_board);
int play_as_user();
int play_as_pc();
int show_best_score();

int main(){

    menu();

    return 0;
}
//game menu.
int menu(){ 
    int select;

    printf("Welcome to the 8-Puzzle Game!\n");
    printf("1. Play game as a user\n");
    printf("2. Finish the game with PC\n");
    printf("3. Show the best score\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d" , &select);

    switch(select) {
        case 1: play_as_user(); break;
        case 2: play_as_pc(); break;
        case 3: show_best_score(); break;
        case 4: printf("Goodbye!\n"); break;
    }
}
//basic swap function.
void swap(int *num1 , int *num2) {                                                                          
    int temp;
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}
//this function is for creating random puzzles.
void shuffle_board(puzzleBoard *puzzle) {                           
    int i , randnum;
    srand(time(NULL));

    for(i = 8 ; i > 0 ; i--) {
        randnum = rand() % (i+1);          //creating random positions.
        swap(&puzzle -> board[i/3][i%3] , &puzzle -> board[randnum/3][randnum%3]);
    }    
}
//printing the board to terminal.
int print_board(puzzleBoard *puzzle) {
    int i , j;
    for(i = 0 ; i < 3 ; i++) {
        for(j = 0 ; j < 3 ; j++) {
            if(puzzle -> board[i][j] == 0) {       //changing 0 to _
                printf("_ ");
            }
            else {
                printf("%d " , puzzle -> board[i][j]);
            }
        }
        printf("\n");
    }
}
//saving the board to txt file.
int save_board(puzzleBoard *puzzle) {
    FILE *fptr = fopen("puzzle_board.txt" , "w");
    int i , j;
    for(i = 0 ; i < 3 ; i++) {
        for(j = 0 ; j < 3 ; j++) {
            if(puzzle -> board[i][j] == 0) {
                fprintf(fptr , "_ ");
            }
            else {
                fprintf(fptr ,"%d " , puzzle -> board[i][j]);
            }
        }
        fprintf(fptr ,"\n");
    }
    fclose(fptr);
}
//checking if the puzzle is solved or not.
int check_solved(puzzleBoard *puzzle , checkBoard *check_board) {
    int i , j;
    int check = 1;
    for(i = 0 ; i < 3 ; i++) {
        for(j = 0 ; j < 3 ; j++) {
            if(puzzle -> board[i][j] != check_board -> board[i][j]) {    //checking every coordinate to match with the final puzzle.
                return 0;
            }
            check = (check + 1) % 9;
        }
    }
    return 1;
}
//score function.
int calculate_score(int numofMoves) {
    return 1000 - (10 * numofMoves);
}
//updating the score in the txt file.
int update_score(int score){
    FILE *fptr = fopen("best_score.txt" , "r+");
    int bestScore;
    if(fptr == NULL) {
        printf("Error opening best_score.txt file!");
        return 0;
    }
    fscanf(fptr , "%d" , &bestScore);
    if(score > bestScore){
        fprintf(fptr , "%d" , bestScore);
    }
    fclose(fptr);
}
//finding the coordinate of _ to move.
int find_tile_coord(puzzleBoard *puzzle, int *row, int *col) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzle->board[i][j] == 0) {     //if board_coord == tile_coord take the i and j.
                *row = i;
                *col = j;
                return 0;
            }
        }
    }
}
//moving the tile.
int move_tile(puzzleBoard *puzzle , int number , char direction){
    int row , col , newRow , newCol;
    find_tile_coord(puzzle , &row , &col);      //getting the coord of tile to move.
    newRow = row;
    newCol = col;

    switch(direction){
        case 'U': newRow++; break;              //changing the coord of the tile due to direction given in input.
        case 'D' : newRow--; break;
        case 'R' : newCol--; break;
        case 'L' : newCol++; break;
        default : printf("Enter valid direction!\n");
    }

    if((newRow >= 0 && newRow < 3) && (newCol >= 0 && newCol < 3)) {
        if(puzzle -> board[newRow][newCol] == number){                              
            swap(&puzzle -> board[row][col] , &puzzle -> board[newRow][newCol]);            //swapping the tile and the number given in input.
            return 1;
        }
    }
    return 0;
}
//auto finish function for finishing with pc
int auto_finish(puzzleBoard *puzzle , int *numofMoves , checkBoard *check_board) {
    if(check_solved(puzzle,check_board)) {
        printf("PC solved the puzzle in %d moves!" , *numofMoves);
        return 0;
    }
    int num;
    char direction;
    num = (rand() % 8) + 1;                 //random number.

    switch(rand() % 4) {                    //random direction.
        case 0: direction = 'U'; break;
        case 1: direction = 'D'; break;
        case 2: direction = 'R'; break;
        case 3: direction = 'L'; break;
    }

    //sending the random number and random direction to move_tile func.
    if(move_tile(puzzle , num , direction)) {                                       //if it is a valid move, numofMoves++;
        (*numofMoves)++;
        printf("PC AUTO MOVE %d : %d-%c\n" , *numofMoves , num , direction);        //printing the move.
        print_board(puzzle);                                                        //printing the new board.
        save_board(puzzle);                                                         //saving the new board.
        auto_finish(puzzle,numofMoves,check_board);                                             //calling the function again with new numofMoves.
    }
    else{
        auto_finish(puzzle,numofMoves,check_board);                                             //if it is not a valid move try again with another direction and number.
    }
    
}
int play_as_user(){
    puzzleBoard puzzle;
    checkBoard check_board;
    int i , j;
    int num , score;
    int numofMoves = 0;
    char direction;

    puzzle.board[0][0] = 1;
    puzzle.board[0][1] = 2;
    puzzle.board[0][2] = 3;
    puzzle.board[1][0] = 4;
    puzzle.board[1][1] = 5;
    puzzle.board[1][2] = 6;
    puzzle.board[2][0] = 7;
    puzzle.board[2][1] = 8;
    puzzle.board[2][2] = 0;

    check_board.board[0][0] = 1;
    check_board.board[0][1] = 2;
    check_board.board[0][2] = 3;
    check_board.board[1][0] = 4;
    check_board.board[1][1] = 5;
    check_board.board[1][2] = 6;
    check_board.board[2][0] = 7;
    check_board.board[2][1] = 8;
    check_board.board[2][2] = 0;

    shuffle_board(&puzzle);                                 //shuffling the board.

    

    while(!check_solved(&puzzle , &check_board)) {                         //while it is not solved...
        print_board(&puzzle);                               //print the board.
        save_board(&puzzle);                                //save the board.
        printf("Enter your move (NUMBER-DIRECTION): ");     //get the number and direction.
        scanf("%d-%c" , &num , &direction);
        
        if(move_tile(&puzzle , num , direction)) {          //if it is a valid move, numofMoves++ and make the move.
            numofMoves++;
        }
        else {
            printf("Invalid move!\n");
        }
    }
    if (check_solved(&puzzle , &check_board)) {                            //if it is solved...
        print_board(&puzzle);                               //print the board.
        score = calculate_score(numofMoves);                //get the score.
        update_score(score);                                //update the score.

        printf("Congratulations! You solved the puzzle in %d moves.\n", numofMoves);
        printf("Your score is %d\n" , score);
    }
}
int play_as_pc(){

    puzzleBoard puzzle;
    checkBoard check_board;
    int i , j;
    int score;
    int numofMoves = 0;
    char direction;

    puzzle.board[0][0] = 1;
    puzzle.board[0][1] = 2;
    puzzle.board[0][2] = 3;
    puzzle.board[1][0] = 4;
    puzzle.board[1][1] = 5;
    puzzle.board[1][2] = 6;
    puzzle.board[2][0] = 7;
    puzzle.board[2][1] = 8;
    puzzle.board[2][2] = 0;

    check_board.board[0][0] = 1;
    check_board.board[0][1] = 2;
    check_board.board[0][2] = 3;
    check_board.board[1][0] = 4;
    check_board.board[1][1] = 5;
    check_board.board[1][2] = 6;
    check_board.board[2][0] = 7;
    check_board.board[2][1] = 8;
    check_board.board[2][2] = 0;

    shuffle_board(&puzzle);

    auto_finish(&puzzle , &numofMoves , &check_board);                  //recursive auto_finish function.
    score = calculate_score(numofMoves);                                //get the score.
    update_score(score);                                                //update the score.
    
    printf("Congratulations! PC solved the puzzle in %d moves.\n", numofMoves);
    printf("PC score is %d\n" , score);

}
int show_best_score() {
    FILE *fptr = fopen("best_score.txt" , "r");
    int bestScore;
    fscanf(fptr, "%d" , &bestScore);
    printf("BEST SCORE: %d\n" , bestScore);
    fclose(fptr);
}