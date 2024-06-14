#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//defining rock,paper,scissors according to three's divisors.
#define ROCK 0
#define PAPER 1
#define SCISSORS 2

//functions for the first part.
int check_student();
int number_and_time();
int read_menu();
int dish_choose();
int print_receipt();
int find_digit(double price);
int total_price(double total);
double print_menu(int product , int number_of_product);

//functions.
int part1();
int part2();

int main(){

	part1();
	part2();

}
int part1()
{
printf("--------------MENU and RECEIPT--------------\n");
//calling the functions part by part.
number_and_time();
read_menu();
dish_choose();
}

int part2()
{
printf("--------- ROCK - PAPER - SCISSORS ---------\n");
    //declaring variables.
    int comp_choose , user_choice , flag;
    char select;
    flag = 1;

    //starting an endless loop until the user wants to quit.
    while(1){
        
    //making random choices for computer.
        srand(time(NULL));
        comp_choose = ((rand() % 10) % 3);

    //asking the user for the input.
        printf("Please make a choice!\n");
        printf("1.Rock 2.Paper 3.Scissors\n");
            scanf("%d" , &user_choice);

    //checking if the user_choice is in my interval. 
        if(user_choice > 3 || user_choice < 1)
        {
        	printf("Enter a valid number!");
        	return 0;
        }
            
    //switch cases for rock,paper,scissors
        switch(user_choice - 1){
            case ROCK:
                if(comp_choose == ROCK)
                {
                    printf("You chose Rock. I chose Rock. It's a tie!\n");
                }
                else if(comp_choose == PAPER)
                {
                    printf("You chose Rock. I chose Paper. I won!\n");
                }
                else if(comp_choose == SCISSORS)
                {
                    printf("You chose Rock. I chose Scissors. You won!\n");
                }
                break;
            
            case PAPER:
                if(comp_choose == ROCK)
                {
                    printf("You chose Paper. I chose Rock. You won!\n");
                }
                else if(comp_choose == PAPER)
                {
                    printf("You chose Paper. I chose Paper. It is a tie!\n");
                }
                else if(comp_choose == SCISSORS)
                {
                    printf("You chose Paper. I chose Scissors. I won!\n");
                }
                break;
            
            case SCISSORS:
                if(comp_choose == ROCK)
                {
                    printf("You chose Scissors. I chose Rock. I won!\n");
                }
                else if(comp_choose == PAPER)
                {
                    printf("You chose Scissors. I chose Paper. You won!\n");
                }
                else if(comp_choose == SCISSORS)
                {
                    printf("You chose Scissors. I chose Scissors. It is a tie!\n");
                }
                break;
        }

        //asking the user to play again or not.
        printf("Do you want to play again? (Y/N)\n");
            scanf(" %c" , &select);
            if(select == 'N')
            {
                printf("Goodbye!\n");
                flag = 0;
            }
            if(select == 'Y')
            {
                flag == 1;
            }
            if(flag == 0)
            {
                break;
            }
    }
}
//i created this function for printing the time and my student number.
int number_and_time()
{
    time_t t = time(NULL);
    FILE *receipt_ptr;
    receipt_ptr = fopen("receipt.txt" , "w");
    fprintf(receipt_ptr ,"210104004032  %s\n" , ctime(&t));
    fprintf(receipt_ptr ,"------------------------------------\n");
    fprintf(receipt_ptr ,"Product                    Price(TL)\n");
    fprintf(receipt_ptr ,"------------------------------------\n");
    fclose(receipt_ptr);
}

//this function reads the menu.txt and prints it to terminal.
int read_menu()
{
    FILE *fptr;
    int number , i = 1;
    double price;
    char dish_name , c;

    //opening the file and printing the dishes.
    fptr = fopen("menu.txt" , "r");
    printf("Dish List:\n");
    while(c != '\n')
    {
        c = fgetc(fptr);
    }
    c = fgetc(fptr);
    while(i && c != EOF)
    {
    printf("%d. ", i);
        while(c != 32 && c != '\t' && c)
        {
            printf("%c" , c);
            c = fgetc(fptr);
        }
        printf("\n");
        while((c > 90 || c < 65) && (c > 122 || c < 97) && c != EOF)
        {
            c = fgetc(fptr);
        }
    i++;
   }
   fclose(fptr);
}
//tihs function is for choosing the dish and it consist print_menu and total_price functions.
int dish_choose()
{
    int product , number_of_product ;
    double total = 0.0 , price;
    //while loop for choosing the product and number of servings.
    while(1){
        printf("Please choose a product (1-10):");
            scanf("%d" , &product);
    
            if(product > 10 || product < 1){
                printf("Enter a valid product!\n");
                return 0;
            }
        printf("How many servings do you want? ");
            scanf("%d" , &number_of_product);
            if(number_of_product == 0){
                break;
            }

            //printing the products , their prices and calculating the total price.
            price = print_menu(product,number_of_product);
            total = price + total;

    }
    //calling the total_price function to print and calculate the discounts and price.
  	total_price(total);
  	
   
}
//printing menu line by line.
double print_menu(int product , int number_of_product)
{

    FILE *menu_ptr , *receipt_ptr;
    int counter = 0 , i;
    char c;
    double price;
    int length = 0;

    menu_ptr = fopen("menu.txt" , "r");
    //i opened the receip.txt in append mode because i opened it in write mode in number_and_time function.
    receipt_ptr = fopen("receipt.txt" , "a+"); 
                                               
    //counting to the line which user selected.
    while(counter != product)
    {
        if(c = fgetc(menu_ptr) == '\n')
        {
            counter++;
        }
    }
    c = fgetc(menu_ptr);
    //printing the number_of_product if it is greater than 1;
    if(number_of_product > 1)
    {
        fprintf(receipt_ptr , "%d* " , number_of_product);
    }
    //printing the name of dish the user selected and increasing the length each time.
    while(c != ' ' && c != '\t')
    {
        fputc(c, receipt_ptr);
        c = fgetc(menu_ptr);
        length++;
    }
    //scanning the price in the menu.txt and calculating for printing it to the receipt.txt .
    fscanf(menu_ptr , "%lf" , &price);
    price = price * number_of_product;

    //calculating the length of the price and adding it to the dish name's length.
    length = length + find_digit(price); + 3;
    
    //printing " " for making the receipt.txt in-order.
    for(i = 0 ; i < 33 - length ; i++)
    {
        fprintf(receipt_ptr , " ");
    }
    
    //printing the price.
    fprintf(receipt_ptr , "%.2lf\n" , price);
    
    fclose(menu_ptr);
    fclose(receipt_ptr);
    
    return price;

}
//this function is for calculating the discounts and total.
int total_price(double total)
{
    FILE *receipt_ptr;
    char student;
    double temp_total;
    temp_total = total;

    //checking if the user is student or not.
    printf("Are you student?");
    scanf(" %c" , &student);

    receipt_ptr = fopen("receipt.txt" , "a");
    
    //if-else statements for user.
    if(student == 'Y')
    {
        total = total - ((12.5 * temp_total) / 100);

        if(temp_total >= 150)
        {
            total = total - (temp_total / 10);
        }
        fprintf(receipt_ptr , "Student Discount:	      -%.2lf\n" , ((12.5 * temp_total) / 100));
        fprintf(receipt_ptr ,"------------------------------------\n");
        fprintf(receipt_ptr , "Price:			      %.2lf\n" , total);
        fprintf(receipt_ptr , "Price + VAT:		      %.2lf\n" , total + ((18 * temp_total) / 100));
        fclose(receipt_ptr);
        print_receipt();

    }
    else if(student == 'N')
    {
        if(temp_total >= 150)
        {
            total = total - (temp_total / 10);
        }
        fprintf(receipt_ptr ,"------------------------------------\n");
        fprintf(receipt_ptr , "Price:			      %.2lf\n" , total);
        fprintf(receipt_ptr , "Price + VAT:		      %.2lf\n" , total + ((18 * temp_total) / 100));
        fclose(receipt_ptr);
        print_receipt();
    }

    //if the user does not enter Y or N then it gives an error.
    else{
    	printf("Enter valid input!");
    	return 0;
    }
}
//this function is for printing the receipt to the terminal.
int print_receipt()
{
	FILE *fptr;
	char c;

	fptr = fopen("receipt.txt" , "r");

        if(fptr != NULL){
            printf("\n");
            //printing char by char until it comes to the EOF.
                while(1)
                {
                c = fgetc(fptr);
                    if(c == EOF)
                    {
                    break;
                    }       
                printf("%c", c);
                }
            printf("\n");
            fclose(fptr);
            }
            else{
                printf("Error opening file!");
                return 0;
            }
}
//this function is for finding the digit of the price.
int find_digit(double price)
{
	int temp_price = price;
	int count = 0;
	while(temp_price > 0)
	{
	temp_price = temp_price / 10;
	count++;
	}
	return count;

}
