#include <stdio.h>
#include <math.h>

int leap_year();
int sci_format(double result , int m , int n);
int output_format();
int grade_func();



int main(){

	leap_year();
	output_format();
	grade_func();

return 0;
}
//*******************************LEAP YEAR FUNCTION*******************************************************************************

int leap_year(){

	
    //declaring variables
    int year;
    //getting the year
        printf("Enter your year:");
            scanf("%d" , &year);
    // comparing
        if(year % 4 == 0 && year % 100 != 0 || year % 400 == 0){
            printf("%d is a leap year\n" , year);
        }
        else{
            printf("%d is not a leap year\n" , year);
        }

}

//FORMAT OF OUTPUT FUNCTIONS
//**********************************SCIENTIFIC FORMAT******************************************************************************* 
	
// I MADE THIS FUNCTION FOR RESPRESENTING THE SCIENTIFIC FORMAT.
int sci_format(double result , int m , int n){

        //declaring variables.

                int i , j , k;
                int count_after = 0 , count_before = 0 , counter = 0 , total_count = 0;
                int temp_result = result;
                double f_result = result;
                int i_result = f_result;

        //finding the digit number before decimal point.

                    while(i_result != f_result){
                    f_result *= 10;
                    i_result = f_result;
                    count_before++;
                    }
        //finding the digit number after decimal point.

                    while(temp_result > 0){
                    temp_result = temp_result / 10;
                    count_after++;
                    }

        //finding total digit number.

                    total_count = count_before + count_after;

        //if statement for checking m and total digit number

                if(total_count > m){
                printf("Error! M is less than digit number!");
                return 0;
                }           
   
        //creating an array for the resultant number.

                int arr_result[total_count];

        //printing 0 according to m and n

                for(j = 0 ; j < m - total_count ; j++){
                    printf("0");
                    counter++;
                    //checking for printing "." 
                    if(counter == m - n){
                    printf(".");
                    }
                }
                for(i = 0 ; i < total_count ; i++){
                    arr_result[i] = i_result % 10;
                    i_result = i_result / 10;
                }
                for(i = total_count - 1 ; i >= 0 ; i--){
                    printf("%d" , arr_result[i]);
                    counter++;
                    //checking for printing "."
                    if(counter == m - n){
                    printf(".");
                    }
                }
                if(count_before == 0){
                	printf("e%d" , n);
                	}
                else{
                printf("e%d" , count_before);
}		}
//********************FORMAT OF OUTPUT*******************************************************************************
		
int output_format(){


	
    //declaring variables.

    int m , n , i , temp = 1;
    double result , num1 , num2;
    char format,ops;

    //asking for the format of output.

    printf("Enter the format of output (S or I)");
            scanf(" %c" , &format);
        
     

    //if else statements for checking the format.

        if(format == 'I'){

    //asking for the operation.

            printf("Enter the operation:");
                scanf(" %c" , &ops);

    //switch cases.

            switch(ops){
            
                case '+' :
                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);
                result = num1 + num2;
                printf("%lf + %lf = %lf", num1 , num2 , result);
                printf("\n");
                break;

                case '-' :
                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);
                result = num1 - num2;
                printf("%lf - %lf = %lf", num1 , num2 , result);
                printf("\n");
                break;

                case '*' : 
                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);
                result = num1 * num2;
                printf("%lf * %lf = %lf", num1 , num2 , result);
                printf("\n");
                break;

                case '/' :
                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);
                result = num1 / num2;
                printf("%lf / %lf = %lf", num1 , num2 , result);
                printf("\n");
                break;

                case '!' :
                printf("Enter the operand:");
                    scanf("%lf" , &num1);
                    for(i = 1 ; i <= num1 ; i++){
                        temp = temp * i;
                    }
                printf("%lf! = %d" , num1 , temp);
                printf("\n");
                break;

                case '^' : 
                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);
                result = pow(num1 , num2);
                printf("%lf ^ %lf = %lf" , num1 , num2 , result);
                printf("\n");
                break;

                case '%' :
                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);
                result = fmod(num1,num2);
                printf("%lf %% %lf = %lf" , num1 , num2 , result);
                printf("\n");
                break;

            }

        }
        else if(format == 'S'){
            
    //asking for the operation.

            printf("Enter the operation:");
                scanf(" %c" , &ops);

    //switch cases.

            switch(ops){

                case '+' :
                printf("Enter your m:");
                    scanf("%d" , &m);
                printf("Enter your n:");
                    scanf("%d" , &n);

    //checking for n > m situation.

                if(n > m){
                printf("Error! N is bigger than M!");
                printf("\n");
                return 0;
                }
    //getting the numbers for operation.

                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);
    //finding the result.

                result = num1 + num2;

    //printing the result as scientific format.
    
                printf("%lf + %lf = " , num1 , num2);
                sci_format(result , m , n);
             	printf("\n");
                    break;

                case '-' :
                printf("Enter your m:");
                    scanf("%d" , &m);
                printf("Enter your n:");
                    scanf("%d" , &n);

                        if(n > m){
                        printf("Error! N is bigger than M!");
                        printf("\n");
                        return 0;
                        }

                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);

                result = num1 - num2;

                printf("%lf - %lf = " , num1 , num2);
                sci_format(result , m , n);
		printf("\n");
                    break;

                case '*' :
                printf("Enter your m:");
                    scanf("%d" , &m);
                printf("Enter your n:");
                    scanf("%d" , &n);

                        if(n > m){
                            printf("Error! N is bigger than M!");
                            printf("\n");
                            return 0;
                        }
                        
                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);

                result = num1 * num2;

                printf("%lf * %lf = " , num1 , num2);
                sci_format(result , m , n);
		printf("\n");
                    break;

                case '/' :
                printf("Enter your m:");
                    scanf("%d" , &m);
                printf("Enter your n:");
                    scanf("%d" , &n);

                        if(n > m){
                            printf("Error! N is bigger than M!");
                            printf("\n");
                            return 0;
                        }

                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);

                result = num1 / num2;

                printf("%lf / %lf = " , num1 , num2);
                sci_format(result , m , n);
		printf("\n");
                    break;

                case '!' :
                printf("Enter your m:");
                    scanf("%d" , &m);
                printf("Enter your n:");
                    scanf("%d" , &n);

                        if(n > m){
                            printf("Error! N is bigger than M!");
                            printf("\n");
                            return 0;
                        }

                printf("Enter your operand:");
                    scanf("%lf" , &num1);

                for(i = 1 ; i <= num1 ; i++){
                        temp = temp * i;
                    }

                result = temp;

                printf("%lf! = " , num1);
                sci_format(result , m , n);
		printf("\n");
                    break;

                case '^' :
                printf("Enter your m:");
                    scanf("%d" , &m);
                printf("Enter your n:");
                    scanf("%d" , &n);

                        if(n > m){
                            printf("Error! N is bigger than M!");
                            printf("\n");
                            return 0;
                        }

                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);

                result = pow(num1 , num2);
                
                printf("%lf ^ %lf = " , num1 , num2);
                sci_format(result , m , n);
		printf("\n");
                    break;
                
                case '%' :
                printf("Enter your m:");
                    scanf("%d" , &m);
                printf("Enter your n:");
                    scanf("%d" , &n);

                        if(n > m){
                        printf("Error! N is bigger than M!");
                        printf("\n");
                        return 0;
                        }

                printf("Enter the first operand:");
                    scanf("%lf" , &num1);
                printf("Enter the second operand:");
                    scanf("%lf" , &num2);

                result = fmod(num1,num2);
                
                printf("%lf %% %lf = " , num1 , num2);
                sci_format(result , m , n);
                printf("\n");
                    break;
                }

        }

}

//*****************************************GRADE FUNCTION*******************************************************************************
		
int grade_func(){

	

    //declaring variables.
    int exam1, exam2, exam3, as1, as2;
    double grade;
        printf("Enter your three exam notes:");
            scanf("%d %d %d" , &exam1, &exam2, &exam3);
        printf("Enter your two assignment notes:");
            scanf("%d %d" , &as1, &as2);
    
    //calculating the grade
        grade = (6 * ((exam1 + exam2 + exam3) / 3) / 10) + (4 * ((as1 + as2) / 2) / 10);
    
    //comparing
            if(grade >= 60){
                printf("Final grade: %.1lf Passed!\n", grade);
            }
            else if(grade < 60){
                printf("Final grade: %.1lf Failed!\n" , grade);
            }


}

