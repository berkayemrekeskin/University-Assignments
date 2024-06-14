#include <stdio.h>
#include "util.h"

void gcdfunc(){
	
	printf("---FINDING GCD OF 2 NUMBERS---\n");

	// Declaring the variables.
	
	int i , gcd , n1 , n2;
	gcd = 0;
	
	// Getting the numbers from user.
	
	printf("Enter your first number:");
		scanf("%d" , &n1);
	printf("Enter your second number:");
		scanf("%d" , &n2);
	
	// Comparing these numbers for getting the GCD.	

	if(n1 >= n2){
		for(i = 1 ; i <= n1 ; i++){
			if(n1 % i == 0 && n2 % i == 0){
				gcd = i;
			}
		}
		printf("GCD: %d\n" , gcd);
	}
	else{
		for(i = 1 ; i < n2 ; i++){
			if(n1 % i == 0 && n2 % i == 0){
				gcd = i;
			}
		}
		
		printf("GCD: %d\n" , gcd);
	}
	
}


// PART 2

void arithmeticSum(){
	
	printf("---FINDING ARITHMETIC SUM OF 2 NUMBERS---\n");
	
	// Declaring the variables.
	
	int sum , n1 , n2;
	
	// Getting the numbers from user.
	
	printf("Enter your first number:");
		scanf("%d" , &n1);
	printf("Enter your second number:");
		scanf("%d" , &n2);
		
	// Addition and printing.
	
	sum = n1 + n2;

	printf("Sum:\n%4d\n%4d\n+\n----\n%4d\n" , n1 , n2 , sum);


}

// PART 3 



void arithmeticMult(){

	
	printf("---FINDING ARITHMETIC MULTIPLICATION OF 2 NUMBERS---\n");
	
	// Declaring the variables.
	
	int num1 , num2 , result , temp1 , temp2 , first , second , third;
        
        // Getting the numbers.
        
        printf("Enter your first number:");
            scanf("%d" , &num1);
        printf("Enter your second number:");
            scanf("%d" , &num2);
            
        // Equations.
        result = num1 * num2;
        temp1 = num1;
        temp2 = num2;
        
        //Creating the intervals for the numbers and printing the result.
        
        if(num2 > 99 && num2 < 1000){
                first = (num2 % 10) * num1;
                num2 = num2 / 10;
                second = (num2 % 10) * num1;
                num2 = num2 / 10;
                third = (num2 % 10) * num1;
                num2 = num2 / 10;
                printf("Result:\n%6d\n%6d\n*\n-----\n%6d\n%5d\n%4d\n+\n------\n%6d\n" , temp1 , temp2 , first , second , third , result);
        }
        else if(num2 > 9 && num2 < 100){
                first = (num2 % 10) * num1;
                num2 = num2 / 10;
                second = (num2 % 10) * num1;
                num2 = num2 / 10;
                printf("Result:\n%6d\n%6d\n*\n-----\n%6d\n%5d\n+\n------\n%6d\n" , temp1 , temp2 , first , second , result );
        }
        else if(num2 >= 0 && num2 < 10){
                first = (num2 % 10) * num1;
                num2 = num2 / 10;
                printf("Result:\n%6d\n%6d\n*\n-----\n%6d\n+\n------\n%6d\n" , temp1 , temp2 , first , result );
        }
        else if(num2 < 0 && num2 > -10){
                first = (num2 % 10) * num1;
                num2 = num2 / 10;
                printf("Result:\n%6d\n%6d\n*\n-----\n%6d\n+\n------\n%6d\n" , temp1 , temp2 , first , result );
        }
        else if(num2 < -9 && num2 > -100){
                first = (num2 % 10) * num1;
                num2 = num2 / 10;
                second = (num2 % 10) * num1;
                num2 = num2 / 10;
                printf("Result:\n%6d\n%6d\n*\n-----\n%6d\n%5d\n+\n------\n%6d\n" , temp1 , temp2 , first , second , result );
        }
        else if(num2 < -99 && num2 > -1000){
                first = (num2 % 10) * num1;
                num2 = num2 / 10;
                second = (num2 % 10) * num1;
                num2 = num2 / 10;
                third = (num2 % 10) * num1;
                num2 = num2 / 10;
                printf("Result:\n%6d\n%6d\n*\n-----\n%6d\n%5d\n%4d\n+\n------\n%6d\n" , temp1 , temp2 , first , second , third , result);
        }
	
// PART 4

}
void comparisonFunc(){
	
	printf("---COMPARING THE INPUT WITH 5---\n");
	
	// Declaring the variables.
	
	int n;
	
	// Getting the number from user.
	
	printf("Enter your number:");
		scanf("%d" , &n);
	
	if(n > 5 && n <= 10){
		printf("The integer you entered is greater than 5");
	}
	else if(n <= 5 && n >= 1){
		printf("The integer you entered is less than or equal to 5");
	}
	else if(n < 1 || n > 10){
		printf("Invalid input\n");
	}

} /* end fraction_div */
