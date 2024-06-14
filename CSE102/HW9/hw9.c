#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Point {
    int row;
    int col;
} Point;

typedef struct Block {
    char type;
    int value;
} Block;

typedef struct Snake {
    Point* coord;
    char l_move;
    int len;
} Snake;

Block*** init_board() {
    Block*** board = (Block***)malloc(10 * sizeof(Block**));
    for (int i = 0; i < 10; i++) {
        board[i] = (Block**)malloc(10 * sizeof(Block*));
        for (int j = 0; j < 10; j++) {
            board[i][j] = (Block*)malloc(1 * sizeof(Block));
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            board[i][j][0].type = 'e';
            board[i][j][0].value = 0;
        }
    }
    int obstacleRow, obstacleCol, baitRow, baitCol;
    srand(time(NULL));
    obstacleRow = rand() % 10;
    obstacleCol = rand() % 10;
    baitRow = rand() % 10;
    baitCol = rand() % 10;
    board[obstacleRow][obstacleCol][0].type = 'o';
    board[obstacleRow][obstacleCol][0].value = rand() % 9 + 1;
    board[baitRow][baitCol][0].type = 'b';
    board[baitRow][baitCol][0].value = 0;
    return board;
}

void draw_board(Block*** board, Snake* snake) {
    int temp = 0;
    int flag = 0;
    printf("-----------------------------------------\n");
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            flag = 0;
            for (temp = 0; temp < snake->len; temp++)
            {
                if (snake->coord[temp].col == j && snake->coord[temp].row == i && temp == 0)
                {
                	printf("| O ");
                	flag = 1;
                }
                else if (snake->coord[temp].col == j && snake->coord[temp].row == i && temp != 0)
                {
                	printf("| X ");
                	flag = 1;
                }
            }
            if (board[i][j][0].type == 'e' && flag == 0) {
                printf("|   ");
            } 
            else if (board[i][j][0].type == 'b' && flag == 0) {
                printf("| . ");
            } 
            else if (board[i][j][0].type == 'o' && flag == 0) {
                if (board[i][j][0].value > 9) {
                    printf("| %d" , board[i][j][0].value);
                } else {
                    printf("| %d " , board[i][j][0].value);
                }
            }
        }
        printf("|\n");
        printf("-----------------------------------------\n");
    }
}

void update(Block*** board, Snake* snake, int counter) {
    int i , j , k;
    int b_row, b_col;
    int o_row, o_col;
    int t_row, t_col;
    int temp_obs , temp = 0;
    int ate_bait = 0;
    int flag = 0;
    int headRow = snake->coord[0].row;
    int headCol = snake->coord[0].col;

    counter++;
    if(board[snake->coord[0].row][snake->coord[0].col][0].type == 'b') {
        ate_bait = 1;
        board[snake->coord[0].row][snake->coord[0].col][0].type = 'e';
        board[snake->coord[0].row][snake->coord[0].col][0].value = 0;
    }

    if(ate_bait == 1) {
        srand(time(NULL));
        b_row = rand() % 9;
        b_col = rand() % 9;
        i = 0;
        while(i < snake->len){
            if(b_row == snake->coord[i].row && b_col == snake->coord[i].col){
                b_row = rand() % 9;
                b_col = rand() % 9;
            }
            else {
                i++;
            }
        }
        board[b_row][b_col][0].type = 'b';
        board[b_row][b_col][0].value = 0;
        snake->len++;
        snake->coord = realloc(snake->coord, snake->len * sizeof(Point));
    }

    for (i = snake->len - 1; i >= 1; i--) {
        snake->coord[i].row = snake->coord[i - 1].row;
        snake->coord[i].col = snake->coord[i - 1].col;
    }

    switch(snake->l_move){
        case 'w' : 
        snake->coord[1].row++; 
        break;
        case 's' : 
        snake->coord[1].row--; 
        break;
        case 'd' : 
        snake->coord[1].col--; 
        break;
        case 'a' : 
        snake->coord[1].col++; 
        break;
    }

    srand(time(NULL));
    if(counter % 5 == 0 && counter != 0 && counter < 15){
        i = 0;
        o_row = rand() % 10;
        o_col = rand() % 10;
        while(i < snake->len){
            if((o_row == snake->coord[i].row && o_col == snake->coord[i].col) && o_row == b_row && o_col == b_col){
                o_row = rand() % 10;
                o_col = rand() % 10;
            }
            else {
                i++;
            }
        }
        board[o_row][o_col][0].type = 'o';
        board[o_row][o_col][0].value = rand() % 9 + 1;

    }
    else if(counter % 5 == 0 && counter != 0 && counter > 15){
        temp_obs = rand() % 3 + 1;
        temp = rand() % 3;
        for(i = 0 ; i < 10 ; i++) {
            for(j = 0 ; j < 10 ; j++) {
                if(board[i][j][0].type == 'o' && board[i][j][0].value < 9) {
                    temp++;
                }
                if(temp == temp_obs) {
                    board[i][j][0].value = board[i][j][0].value + (rand() %  - ((9 - board[i][j][0].value) + 1));
                    flag = 1;
                    break;
                }
            }
            if(flag == 1) {
                break;
            }
        }
    }
    if(board[snake->coord[0].row][snake->coord[0].col][0].value > 0 && snake->len >= board[snake->coord[0].row][snake->coord[0].col][0].value) {
        board[snake->coord[0].row][snake->coord[0].col][0].type = 'e';
        board[snake->coord[0].row][snake->coord[0].col][0].value = 0;
        i = 0;
        o_row = rand() % 10;
        o_col = rand() % 10;
        while(i < snake->len){
            if(o_row == snake->coord[0].row && o_col == snake->coord[0].col && o_row == b_row && o_col == b_col){
                o_row = rand() % 10;
                o_col = rand() % 10;
            }
            else {
                i++;
            }
        }
        board[o_row][o_col][0].type = 'o';
        board[o_row][o_col][0].value = rand() % 9 + 1;

    }
}

int check_status(Block*** board, Snake* snake){
    int headRow = snake->coord[0].row;
    int headCol = snake->coord[0].col;
    int obstacleSize = board[headRow][headCol][0].value;

    for(int i = 1; i < snake->len; i++) {
        if (snake->coord[i].row == headRow && snake->coord[i].col == headCol) {
            return 1;
        }
    }

    if (headRow < 0 || headRow >= 10 || headCol < 0 || headCol >= 10) {
        return 1;
    }

    if (board[headRow][headCol][0].type == 'o' && obstacleSize > snake->len) {
        return 1;
    }

    return 0;
}

void move(Snake* snake) {
    char movement;
    printf("Enter your move (w,a,s,d): ");
    scanf(" %c", &movement);

    switch (movement) {
        case 'w':
            snake->coord[0].row--;
            break;
        case 's':
            snake->coord[0].row++;
            break;
        case 'd':
            snake->coord[0].col++;
            break;
        case 'a':
            snake->coord[0].col--;
            break;
    }
    snake->l_move = movement;
}

void play() {
    int counter = 0;
    int snakeLength = 1;
    Block*** board = init_board();
    Snake *snake = malloc(sizeof(Snake));
    snake->coord = malloc(snakeLength * sizeof(Point));
    snake->coord[0].col = 0;
    snake->coord[0].row = 0;
    snake->len = snakeLength;

    while (1) {
        draw_board(board, snake);
        move(snake);
        update(board, snake, counter);
        counter++;
        if (check_status(board, snake) == 1) {
            break;
        }

    }

    printf("GAME OVER!\n");
    free(snake->coord);
    free(snake);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            free(board[i][j]);
        }
        free(board[i]);
    }

    free(board);

}

int main() {
    play();

    return 0;
}