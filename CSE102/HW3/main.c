#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//defining directions.
#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define NEW_GAME 1
#define HELP 2
#define EXIT 3

int game_screen();
int gameplay_function();
int room_create(int n, int coord_c_x , int coord_c_y ,int coord_d_x , int coord_d_y);
int control_status(int coord_c_x , int coord_c_y ,int coord_d_x , int coord_d_y);


int main(){

    //calling the game screen function.
    game_screen();

    return 0;
}

int game_screen(){
    //defining variables.
    int select , flag_exit;
    flag_exit = 0;
    while(1){

        printf("Welcome to the 2D puzzle game!\n");
        printf("1. New Game\n2. Help\n3. Exit\n");
            scanf("%d" , &select);

        switch(select){

            case NEW_GAME:
            gameplay_function();
            break;

            case HELP:
            printf("The character is able to move one space in any of the four cardinal directions: up, down, left, and right.\n");
            printf("The user will input their desired move using the following keys: 'a' for left, 'd' for right, 'w' for up, and 's' for down.\n");
            break;

            case EXIT:
            printf("Goodbye!\n");
            flag_exit = 1;
            break;
            
            default:
            flag_exit = 1;
        }
        if(flag_exit == 1){
            break;
        }
    }
    
    
}

int gameplay_function(){
    //declaring variables.
    int n , i , j , counter , flag , coord_c_x , coord_c_y , coord_d_x , coord_d_y;
    char space = ' ';
    char character = 'C';
    char door = 'D';
    char move;
    counter = 0;
    flag = 0;
    //getting the n.
    printf("Write the size (Between 5-10) :");
            scanf("%d" , &n);
        if(n > 10 || n < 5){
            printf("Please enter a valid n!\n");
            return 0;
        }
    
    
    //creating coordinates for door and character
    srand(time(NULL));
    coord_c_x = (rand() % n);
    coord_c_y = (rand() % n);
    coord_d_x = (rand() % n);
    coord_d_y = (rand() % n);

    //creating the first unique room.
    room_create(n,coord_c_x, coord_c_y, coord_d_x , coord_d_y);
    //while loop
    while(1){

        printf("Please enter your move (w,a,s,d) :");
            scanf(" %c" , &move);

    //switch cases for the movements.
    switch(move){
       
        case UP:
            //checking if the character is trying to go past the edges.
            if(coord_c_y == 0){
                printf("You can't go upwards! You are at the top!\n");

            }
            else{
            //decreasing the coordinates according to the movement.
                coord_c_y--;
            //creating the new room with new location of character.
                room_create(n,coord_c_x, coord_c_y , coord_d_x , coord_d_y);
            //increasing the counter.
                counter++;
            //using control_status function to check whether the character reached the door or not.
                if(control_status(coord_c_x ,coord_c_y ,coord_d_x ,coord_d_y) == 1){
                        printf("You have reached the door!\n");
                        printf("You finished the game in %d steps!\n" , counter);
                        flag = 1;
                        break;
                    }
                
            }
            break;

        //i used the same algorithm on the top with the other cases.
        case DOWN:
            if(coord_c_y == n-1){
                printf("You can't go downwards! You are at the bottom!\n");
                
            }
            else{
                coord_c_y++;
                room_create(n,coord_c_x, coord_c_y, coord_d_x , coord_d_y);
                counter++;
                if(control_status(coord_c_x ,coord_c_y ,coord_d_x ,coord_d_y) == 1){
                        printf("You have reached the door!\n");
                        printf("You finished the game in %d steps!\n" , counter);
                        flag = 1;
                        break;
                    }
                
            }
            break;

        case RIGHT:
            if(coord_c_x == n-1){
                printf("You can't go right! You are at the right edge!\n");
                
            }
            else{
                coord_c_x++;
                room_create(n,coord_c_x, coord_c_y, coord_d_x , coord_d_y);
                counter++;
                if(control_status(coord_c_x ,coord_c_y ,coord_d_x ,coord_d_y) == 1){
                        printf("You have reached the door!\n");
                        printf("You finished the game in %d steps!\n" , counter);
                        flag = 1;
                        break;
                    }
                
            }
            break;

        case LEFT:
            if(coord_c_x == 0){
                printf("You can't go left! You are at the left edge!\n");
                
            }
            else{
                coord_c_x--;
                room_create(n,coord_c_x, coord_c_y, coord_d_x , coord_d_y);
                counter++;
                    if(control_status(coord_c_x ,coord_c_y ,coord_d_x ,coord_d_y) == 1){
                        printf("You have reached the door!\n");
                        printf("You finished the game in %d steps!\n" , counter);
                        flag = 1;
                        break;
                    }
                
            }
            break;
        }
        if(flag == 1){
            break;
        }
    }
}

int room_create(int n, int coord_c_x , int coord_c_y ,int coord_d_x , int coord_d_y){
    //declaring variables.
    int i, j;
    char space = ' ';
    char character = 'C';
    char door = 'D';
    //for loop for creating the room.
    for(i = 0 ; i < n; i++){
    	printf("--");
    }
    printf("-");
    printf("\n");
    for(i = 0 ; i < n ; i++){
        for(j = 0 ; j < n ; j++){
            if (j == coord_c_x && i == coord_c_y) {
                printf("|%c", character);
            } 
            else if (j == coord_d_x && i == coord_d_y) {
                printf("|%c", door);
            } 
            else {
                printf("|%c", space);
            }
        }
        printf("|\n");
    }
    for(i = 0 ; i < n; i++){
    	printf("--");
    }
    printf("-");
    printf("\n");
}

int control_status(int coord_c_x , int coord_c_y ,int coord_d_x , int coord_d_y){
    //controlling whether the game is over or not by checking the coordinates.
    if(coord_c_x == coord_d_x && coord_c_y == coord_d_y){
        return 1;
    }
    else{
        return 0;
    }
}
