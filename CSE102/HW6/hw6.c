#include <stdio.h>
#include <stdlib.h>

int main_menu();
int selection_func();
int file_operations_menu();
int search_product_menu();
int search_product();
int list_all();
int file_operations(int select);
int add_product();
int rem_product();
int update_product();
int add_stock();
int rem_stock();
int update_stock();
int add_feature();

int main()
{
main_menu();
}

//menu for choosing the first operations.
int main_menu()
{
    int select;
    printf("1- File operations\n2- Query opeartions\n3- Check stock status\n4- Stock control by hand\n5- Export report\n");
    printf("Welcome operator, please select an option to continue: ");
    scanf("%d" , &select);
    selection_func(select);
}
//selection function gets the integer from main_menu func.
int selection_func(int select)
{
    switch(select)
    {
        case 1: file_operations_menu(); break;
        case 2: search_product_menu(); break;
        case 3: break;
        case 4: break;
        case 5: break;
        default:
        printf("Enter a valid number!\n"); main_menu();
    }
}
//file operations menu
int file_operations_menu()
{
    printf("\nFILE OPERATIONS\n");

    int select;
    printf("1- Add new product\n2- Delete a product\n3- Update a product\n4- Add feature to products");
    printf("\n5- Add new stock entry\n6- Delete a stock entry\n7- Update a stock entry\n8- Back to main menu\n");
    printf("Select: ");
    scanf("%d" , &select);
    file_operations(select);
}
//file operations func. for the switch cases it gets the integer form file_operations_menu func.
int file_operations(int select)
{
    switch(select)
    {

        case 1: add_product(); break;
        case 2: rem_product(); break;
        case 3: update_product(); break;
        case 4: add_feature(); break;
        case 5: add_stock(); break;
        case 6: rem_stock(); break;
        case 7: update_stock(); break;
        case 8: main_menu(); break;
    }
}
//file operations
int add_product()
{
    FILE *product_ptr;
    int pID = 0;
    char type , name[8] , brand[5] , ch;
    double price;
        
    product_ptr = fopen("products.txt" , "r");

        if(product_ptr == NULL)
        {
            printf("Error opening file!");                                                      //error if file cannot be opened.
            fclose(product_ptr);
            return 0;
        }
        
        ch = fgetc(product_ptr);
        while(ch != EOF)
        {
            if(ch == '\n')
            {
                pID++;                                                                          //counting pID.
            }
            ch = fgetc(product_ptr);
        }
        
    fclose(product_ptr);
        
        printf("Enter Type Name Brand Price: ");                                                //getting the inputs.
            scanf(" %c  %s  %s %lf" , &type , name , brand , &price);  
            

    product_ptr = fopen("products.txt" , "a");
        pID++;                                                                                  //incrementing by one because of the first line.

    fprintf(product_ptr , "\n%d,%c,%s,%s,%.1lf" , pID , type , name , brand , price);           //putting the inputs.
    fclose(product_ptr);
}
int rem_product()
{ 
    FILE *product_ptr, *temp_product_ptr;
    int pID = 0 , line_number , count = 0 , temp_pID;
    char ch;


        printf("Enter the pID number you want to delete: ");                            //getting the pID number which will be deleted.
            scanf("%d" , &line_number);

    product_ptr = fopen("products.txt" , "r");
        
        if(product_ptr == NULL)
        {
            printf("Error opening file!");
            fclose(product_ptr);                                                        //error if file cannot be opened.
            return 0;
        }
 
    temp_product_ptr = fopen("temp_products.txt" , "w");
        
        ch = fgetc(product_ptr);
        while(ch != EOF)
        {
            if(ch == '\n')
            {
                count++;                                                                //incrementing count by one
            }
            if(line_number != count)
            {
                putc(ch,temp_product_ptr);                                              //if line number is equal to counter , do not write that line in the temporary file.
            }
            
            ch = fgetc(product_ptr);
        }
    rewind(temp_product_ptr);
    fclose(product_ptr);
    fclose(temp_product_ptr);
    remove("products.txt");                                                             //changing the name of the temporary file and deleting the first file.
    rename("temp_products.txt" , "products.txt");
    
    
}
int update_product()
{
    FILE *product_ptr , *temp_product_ptr , *feature_find_ptr;
    int pID , temp_pID , feature_point , count = 0, comma_count = 0 , feature_find = 0 , i = 0;
    char feature_name[10] , updated_name[10] , ch;

    printf("Which product you want to update: ");                                       //getting the variables.
        scanf("%d", &pID);
    printf("Enter the first name of the feature: ");
        scanf("%s", feature_name);
    printf("Enter the new name: ");
        scanf("%s", updated_name);

    feature_find_ptr = fopen("products.txt", "r+");                                     
    
    ch = fgetc(feature_find_ptr);
    while (ch != '\n' && ch != EOF)
    {
        i = 0;
        while (ch == feature_name[i])                                                  //search for the feature name in the file.                               
        {
            ch = fgetc(feature_find_ptr);
            i++;
        }
        if (feature_name[i] == '\0' && (ch == ',' || ch == '\n' || ch == EOF))        //if feature name is found turn feature_found to 1.
        {
            fclose (feature_find_ptr);
            feature_find = 1;
        }
        ch = fgetc(feature_find_ptr);
    }
    fclose(feature_find_ptr);
    

    product_ptr = fopen("products.txt", "r+");
    temp_product_ptr = fopen("temp_products.txt", "w+");


    ch = fgetc(product_ptr);                                                          //copying the lines until the feature to update.
    while (ch != '\n')
    {
        if (ch == ',')
        {
            count++;                                                                 //counting commas tot  determine the index of the feature to update.
        }
        if (ch == feature_name[0] && feature_find == 1)                              //If the feature to update is found set the feature_point variable to the index of the feature.
        {
            feature_point = count;
        }            
        fprintf(temp_product_ptr, "%c", ch);
        ch = fgetc(product_ptr);
    }
    fprintf(temp_product_ptr, "\n");
    while (ch != EOF)                                                               //updating the feature.
    {
        fscanf(product_ptr, "%d", &temp_pID);
        if (pID != temp_pID)                                                        //if the IDs do not match, copy the line as it is.
        {
            fprintf(temp_product_ptr, "%d", temp_pID);
            ch = fgetc(product_ptr);
            while (ch != '\n' && ch != EOF)
            {
                fprintf(temp_product_ptr, "%c", ch);
                ch = fgetc(product_ptr);
            }
            if (ch == '\n')
            {
                fprintf(temp_product_ptr, "\n");
            }
        }
        else
        {
            fprintf(temp_product_ptr, "%d", temp_pID);                              //printing the updated name.
            ch = fgetc(product_ptr);
            while (ch != '\n' && ch != EOF)
            {
                if (comma_count != feature_point)
                {
                    fprintf(temp_product_ptr, "%c", ch);
                    if (ch == ',')
                    {
                        comma_count++;
                    }
                    ch = fgetc(product_ptr);
                }
                else if (comma_count == feature_point)
                {
                    fprintf(temp_product_ptr, "%s", updated_name);             
                    ch = fgetc(product_ptr);
                    while (ch != ',' && ch != EOF && ch != '\n')
                    {
                        ch = fgetc(product_ptr);
                    }
                    comma_count++;                                              
                }
                if (ch == '\n')
                {
                    fprintf(temp_product_ptr, "\n");
                }
            }
        }
    }
    fclose(product_ptr);
    fclose(temp_product_ptr);
    remove("products.txt");
    rename("temp_products.txt" , "products.txt");
}
int add_feature()
{
    FILE *product_ptr , *temp_product_ptr;
    char ch , new_feature[9];
    int count = 0 , flag = 0;

    printf("Enter the new feature: ");
    scanf("%s", new_feature);

    product_ptr = fopen("products.txt", "r+");
    temp_product_ptr = fopen("temp_products.txt", "w+");

    ch = fgetc(product_ptr);
    while (ch != EOF)
    {
        while (ch != '\n' && ch != EOF)
        {
            fprintf(temp_product_ptr, "%c", ch);                    //copying the contents to temporary file.
            ch = fgetc(product_ptr);
        }
        if (ch == '\n')
        {
            flag = 1;                                               //if end of the line is reached change to 1.
        }
        
        if (count == 0)
        {
            fprintf(temp_product_ptr, ",%s", new_feature);          //add the new feature.
        }
        if (flag == 1)
        {
            fprintf(temp_product_ptr, "\n");                        //add new line.        
            ch = fgetc(product_ptr);
        }
        count++;
    }
    fclose(product_ptr);
    fclose(temp_product_ptr);
    remove("products.txt");
    rename("temp_products.txt" , "products.txt");
}
int add_stock()
{
    FILE *stock_ptr;
    int sID = 0 , pID , current_stock  , count = 0;
    char branch[15] , ch;
    
    stock_ptr = fopen("stocks.txt" , "a+");

    if(stock_ptr == NULL)
        {
            printf("Error opening file!");
            fclose(stock_ptr);
            return 0;
        }

    ch = fgetc(stock_ptr);
        while(ch != EOF)
        {
            if(ch == '\n')
            {
                sID++;                              //counting the sID.
            }
            ch = fgetc(stock_ptr);
        }
    fclose(stock_ptr);
    
    printf("Enter pID:");                           //getting the variables.
        scanf("%d" , &pID);
    printf("Enter Branch:");
        scanf("%s" , branch);
    printf("Enter Current Stock:");
        scanf("%d" , &current_stock);

    stock_ptr = fopen("stocks.txt" , "a+");

    fprintf(stock_ptr , "\n%d,%d,%s,%d" , sID , pID , branch , current_stock);              //printing in the file.
    fclose(stock_ptr);
    
}
int rem_stock()
{
    FILE *stock_ptr, *temp_stock_ptr;
    int sID = 0 , line_number , count = 0 , temp_sID;
    char ch;

        printf("Enter the sID number you want to delete: ");                    //same process with the rem_product.
            scanf("%d" , &line_number);

    stock_ptr = fopen("stocks.txt" , "r");
        
        if(stock_ptr == NULL)
        {
            printf("Error opening file!");
            fclose(stock_ptr);
            return 0;
        }
 
    temp_stock_ptr = fopen("temp_stocks.txt" , "w");
        
        ch = fgetc(stock_ptr);
        while(ch != EOF)
        {
            if(ch == '\n')
            {
                count++;
            }
            if(line_number != count)
            {
                putc(ch,temp_stock_ptr);
            }
            
            ch = fgetc(stock_ptr);
        }
    rewind(temp_stock_ptr);
    fclose(stock_ptr);
    fclose(temp_stock_ptr);
    remove("stocks.txt");
    rename("temp_stocks.txt" , "stocks.txt");
    
}
int update_stock()
{
    FILE *stock_ptr , *temp_stock_ptr , *feature_find_ptr;
    int sID , temp_sID , count = 0 , comma_count = 0 , feature_point , feature_find = 0 ,  i = 0;
    char feature_name[20] , updated_name[20] , ch;

    printf("Which product you want to update: ");                                   //same process with update_product.
    scanf("%d", &sID);
    printf("Enter the first name of the feature: ");
    scanf("%s", feature_name);
    printf("Enter the new name: ");
    scanf("%s", updated_name);
    
    feature_find_ptr = fopen("stocks.txt", "r+");

    ch = fgetc(feature_find_ptr);
    while (ch != '\n' && ch != EOF)
    {
        i = 0;
        while (ch == feature_name[i])
        {
            ch = fgetc(feature_find_ptr);
            i++;
        }
        if (feature_name[i] == '\0' && (ch == ',' || ch == '\n' || ch == EOF))
        {
            fclose (feature_find_ptr);
            feature_find = 1;
        }
        ch = fgetc(feature_find_ptr);
    }
    fclose(feature_find_ptr);
    

    stock_ptr = fopen("stocks.txt", "r+");
    temp_stock_ptr = fopen("temp_stocks.txt", "w+");

    ch = fgetc(stock_ptr);
    while (ch != '\n')
    {
        if (ch == ',')
        {
            count++;
        }
        if (ch == feature_name[0] && feature_find == 1)
        {
            feature_point = count;
        }            
        fprintf(temp_stock_ptr, "%c", ch);
        ch = fgetc(stock_ptr);
    }
    fprintf(temp_stock_ptr, "\n");
    while (ch != EOF)
    {
        fscanf(stock_ptr, "%d", &temp_sID);
        if (sID != temp_sID)
        {
            fprintf(temp_stock_ptr, "%d", temp_sID);
            ch = fgetc(stock_ptr);
            while (ch != '\n' && ch != EOF)
            {
                fprintf(temp_stock_ptr, "%c", ch);
                ch = fgetc(stock_ptr);
            }
            if (ch == '\n')
            {
                fprintf(temp_stock_ptr, "\n");
            }
        }
        else
        {
            fprintf(temp_stock_ptr, "%d", temp_sID);
            ch = fgetc(stock_ptr);
            while (ch != '\n' && ch != EOF)
            {
                if (comma_count != feature_point)
                {
                    fprintf(temp_stock_ptr, "%c", ch);
                    if (ch == ',')
                    {
                        comma_count++;
                    }
                    ch = fgetc(stock_ptr);
                }
                else if (comma_count == feature_point)
                {
                    fprintf(temp_stock_ptr, "%s", updated_name);
                    ch = fgetc(stock_ptr);
                    while (ch != ',' && ch != EOF && ch != '\n')
                    {
                        ch = fgetc(stock_ptr);
                    }
                    comma_count++;
                }
                if (ch == '\n')
                {
                    fprintf(temp_stock_ptr, "\n");
                }
            }
        }
    }
    fclose(stock_ptr);
    fclose(temp_stock_ptr);
    remove("stocks.txt");
    rename("temp_stocks.txt" , "stocks.txt");
}
//search products menu
int search_product_menu()
{
    int select;
    printf("1. List all products\n2. Filter products by brand, type, price, or a user-defined feature\n3. Back to main menu.\n");
    printf("Select: ");
        scanf("%d" , &select);
    search_product(select);
}
//search products functions.
int list_all()
{
    FILE *product_ptr;                              //printing the file.
    char ch;
    product_ptr = fopen("products.txt" , "r");
    if (product_ptr == NULL)
    {
        printf("Cannot open file \n");
        return 0;
    }
    ch = fgetc(product_ptr);
    while(ch != EOF)
    {
        printf("%c" , ch);
        ch = fgetc(product_ptr);
    }
    fclose(product_ptr);
}
int search_product(int select)
{
    switch(select)
    {
        case 1: list_all(); break;
        case 2: break;
        case 3: main_menu(); break;
    }
}
