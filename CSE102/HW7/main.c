#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_WORD_COUNT 100
#define MAX_WORD_SIZE 13
#define VECTOR_SIZE 200
#define WORD_SIZE 1000

int print_dict(const char *filename , char dict[][MAX_WORD_SIZE]){
    FILE *fptr = fopen(filename , "r");
    char ch , search_word[MAX_WORD_SIZE];
    int line , i , j , flag;
    
    while((ch = fgetc(fptr)) != '\n') {
        flag = 0;
    }
    line = 1;
    while(1) {
        i = 0 , j = 0;
        while((ch = fgetc(fptr)) != EOF) {
            search_word[i] = ch;
            i++;
            if(ch == ' ') {
                search_word[i-1] = '\0';
                break;
            }
        }
        printf("%d.%s\n" , line , dict[j]);
        if(strcmp(search_word , "END") == 0) {
            strcpy(dict[j] , "-");
            break;
        }
        strcpy(dict[j] , search_word);
        while((ch = fgetc(fptr)) != '\n') {
            flag = 0;
        }
        line++;
        j++;
    }
}
int read_dict(const char *filename , char dict[][MAX_WORD_SIZE]){
    FILE *fptr = fopen(filename , "r");
    char ch , search_word[MAX_WORD_SIZE];
    int line , i , j , flag;
    
    while((ch = fgetc(fptr)) != '\n') {
        flag = 0;
    }
    line = 1;
    while(1) {
        i = 0 , j = 0;
        while((ch = fgetc(fptr)) != EOF) {
            search_word[i] = ch;
            i++;
            if(ch == ' ') {
                search_word[i-1] = '\0';
                break;
            }
        }
        if(strcmp(search_word , "END") == 0) {
            strcpy(dict[j] , "-");
            break;
        }
        strcpy(dict[j] , search_word);
        while((ch = fgetc(fptr)) != '\n') {
            flag = 0;
        }
        line++;
        j++;
    }
    printf("THIS DICTIONARY HAS %d WORDS!"  , line-1);
    

}
int func(char word_arr[][MAX_WORD_SIZE] , int read_arr[] , int vector_arr[] , int size , char vectored_word[][30] , int ignored_count[], int scale){

    int i , j ;
    for(i = 0  ; i < size ; i++){
        if(ignored_count[i] != 0){
            printf("%s is ignored!\n" , word_arr[i]);
        }
        else if(read_arr[i] == 0 && vector_arr[i] == -1){
            printf("%s does not appear in 'input.txt'.\n" , word_arr[i]);
        }
        else if(read_arr[i] != 0){
            if(size > 1){
                printf("'%s'    " , word_arr[i]);
                for(j = 0 ; j < read_arr[i] / scale ; j++){
                    printf("*");
                }
                printf("\n");
            }
            if(size == 1){
                printf("'%s' appears %d times.\n" , word_arr[i] , read_arr[i]);
            }
        }
        else if(vector_arr[i] != -1 && read_arr[i] == 0){
            if(size > 1) {
                printf("'%s' --> '%s'   " , word_arr[i] , vectored_word[i]);
                if(vector_arr[i] != 0){
                    for(j = 0 ; j < vector_arr[i] / scale ; j++){
                        printf("+");
                    }
                    printf("\n");
                }
                else{
                    printf("Does not appears!\n");
                }
            }
        }
    }

    

    
    

}
int search(const char searched_word[]){

    FILE *text_ptr = fopen("input.txt" , "r");
    if(text_ptr == NULL){
        printf("Error opening file!");
        return 0;
    }
    int i , j , counter;
    char ch , comp_word[MAX_WORD_SIZE];

    counter = 0;

    while(1){
        i = 0;
        while((ch = fgetc(text_ptr)) != EOF) 
        {
            comp_word[i] = ch;
            i++;
            if(
            ch == ',' || ch == ' ' || ch == ';' || ch == '\n' || ch == '\t' || ch == '.' || ch == '"' || 
            ch == '/' || ch == ':' || ch == '!' || ch == '-'  || ch == '<'  || ch == '>' || ch == '|' ||
            ch == '&' || ch == '_' || ch == '*' || ch == '\0' || ch == '?'  || ch == '-' ||ch == '\''
            ){
                comp_word[i-1] = '\0'; 
                break;
            }
        }

        if(strcmp(comp_word,searched_word) == 0){
            counter++;
        }
        if(ch == EOF){
            break;
        }
    }
    return counter;
    fclose(text_ptr);
}
int calculate_similarity(double word_vector[200] , double other_vectors[200][1000]){

    int i , j , line;
    double total[1000] ,temp_total[1000], temp;

    for(i = 0 ; i < 1000 ; i++) {
        total[i] = 0.0;
        temp_total[i] = 0.0;
    }

    for(i = 0 ; i < 1000 ; i++) {
        for(j = 0 ; j < 200 ; j++) {
            total[i] = total[i] + (fabs(word_vector[j] - other_vectors[j][i]) * fabs(word_vector[j] - other_vectors[j][i]));
            temp_total[i] = total[i];
        }
    }

    for(i = 0 ; i < 1000 ; i++) {
        for(j = 0 ; j < 1000 ; j++){
            if(total[j] > total[j+1]){
                temp = total[j+1];
                total[j+1] = total[j];
                total[j] = temp;
            }
        }
    }
    for(i = 0 ; i < 1000 ; i++) {
        if(total[0] == temp_total[i]){
            line = i;    
        }
    }
    /*+3 line (487 - 490)*/
    return line;

}
int check_vectors(const char word[][MAX_WORD_SIZE], const int size , char *vectored_word) {

    FILE *vectors_ptr = fopen("dictionary.txt" , "r");
    int i , j , k , line , flag , count , searched_line , searched_count , turn_flag = 0;
    char ch , search_word[13] ;
    double word_vector[200] , other_vectors[200][1000];

    /*GİRİLEN KELİMEYİ ALMA*/

    while((ch = fgetc(vectors_ptr)) != '\n') {
        flag = 0;
    }
    line = 1;
    while(1) {
        i = 0;
        while((ch = fgetc(vectors_ptr)) != EOF) {
            search_word[i] = ch;
            i++;
            if(ch == ' ') {
                search_word[i-1] = '\0';
                break;
            }
        }
        if(strcmp(search_word , "END") == 0) {
            return -1;
            turn_flag = 1;
            break;
        }
        if(strcmp(search_word , word[0]) == 0) {
            flag = 1;
        }
        if(flag == 1){
            break;
        }
        while((ch = fgetc(vectors_ptr)) != '\n') {
            flag = 0;
        }
        line++;
    }

if(turn_flag == 0){

        i = 0;
    while((ch = fgetc(vectors_ptr)) != '\n') {
            fscanf(vectors_ptr , "%lf" , &word_vector[i]);
            i++;
        }

    rewind(vectors_ptr);

    /*DİĞERLERİNİ ALMA*/

    count = 0;
    while((ch = fgetc(vectors_ptr)) != '\n') {
        flag = 0;
    }
    k = 0;
    while(1) {
        i = 0;
        while((ch = fgetc(vectors_ptr)) != EOF) {
            search_word[i] = ch;
            i++;
            if(ch == ' ') {
                search_word[i-1] = '\0';
                break;
            }
        }
        if(strcmp(search_word , "END") == 0) {
            break;
        }
        count++;
            if(count != line) {
                for(i = 0 ; i < 200 ; i++) {
                    fscanf(vectors_ptr , "%lf" , &other_vectors[i][k]);
                }
                k++;
            }
            else{
                flag = 0;
            }
        
        while((ch = fgetc(vectors_ptr)) != '\n') {
            flag = 0;
        }
    }
    rewind(vectors_ptr);
    
    /*VECTORDEN ALINANI BULMA*/

    searched_line = calculate_similarity(word_vector , other_vectors);


    while((ch = fgetc(vectors_ptr)) != '\n') {
        flag = 0;
    }

    count = 0;
    while(1){
        i = 0;
        while((ch = fgetc(vectors_ptr)) != EOF) {
            search_word[i] = ch;
            i++;
            if(ch == ' ') {
                search_word[i-1] = '\0';
                break;
            }
        }
        if(strcmp(search_word , "END") == 0) {
            break;
        }
        count++;
        if(count == searched_line + 2 ){
            flag = 1;
        }
        if(flag == 1){
            break;
        }
        while((ch = fgetc(vectors_ptr)) != '\n') {
            flag = 0;
        }
    }
    searched_count = search(search_word);
    strcpy(vectored_word,search_word);
    fclose(vectors_ptr); 
    return searched_count;
    }
    

}
int read_text(const char textfile[] , const char ignorefile[] , char word[][MAX_WORD_SIZE] , const int size , int changer) {

    FILE *text_ptr = fopen(textfile , "r");
    FILE *ignore_ptr = fopen(ignorefile , "r");

    if(text_ptr == NULL ||ignore_ptr == NULL) {
        printf("Error opening file!");
        return 0;
    }
 
    int i , j , k ,  occurences[size] , ignored_count[size] ;
    char ch , c , comp_word[MAX_WORD_SIZE] , ignored_word[MAX_WORD_SIZE] , searched_word[MAX_WORD_SIZE];

    for(i = 0 ; i < size ; i++) {
        occurences[i] = 0;
        ignored_count[i] = 0;
    }
    while(1)
    {
        i = 0;
        while((ch = fgetc(text_ptr)) != EOF) 
        {
            comp_word[i] = ch;
            i++;
            if(
            ch == ',' || ch == ' ' || ch == ';' || ch == '\n' || ch == '\t' || ch == '.' || ch == '"' || 
            ch == '/' || ch == ':' || ch == '!' || ch == '-'  || ch == '<'  || ch == '>' || ch == '|' ||
            ch == '&' || ch == '_' || ch == '*' || ch == '\0' || ch == '?'  || ch == '-' ||ch == '\''
            ){
                comp_word[i-1] = '\0'; 
                break;
            }
        }
            if(strcmp(comp_word , word[0]) == 0) 
            {
                occurences[0]++;
            }
        if(ch == EOF) {
            break;
        }
    }
    
    return occurences[0];
    fclose(text_ptr);
    fclose(ignore_ptr);
}
int main(){


    FILE *ignore_ptr;
    int size;
    int changer;
    int read = -2  , vector = -2;
    int scale;
    char ch , textfile[30] , ignorefile[30], select;
    int i , j , k;
    char c , ignored_word[MAX_WORD_SIZE];

    printf("Enter file name : ");
        scanf("%s" , textfile);
    printf("Enter ignored words file name : ");
        scanf("%s" , ignorefile);
    printf("Enter how many input you will enter: ");
        scanf("%d" , &size);
    printf("Enter scale: ");
        scanf("%d" , &scale);

    if(size > MAX_WORD_COUNT) {
        printf("Out of bounds!");
    }

    char word[size][MAX_WORD_SIZE];
    char vectored_word[30];
    char vectored_word_arr[size][30];
    char word_arr[size][MAX_WORD_SIZE];
    char dict[size][MAX_WORD_SIZE];

    int read_arr[size] , vector_arr[size];
    int ignored_count[size];

    for(i = 0 ; i < size ; i++){
        ignored_count[i] = 0;
    }

    changer = size;

    if(size == 1) 
    {                                                                         
        printf("Enter your word: ");
            scanf("%s" , word );
        for(i = 0 ; i < size ; i++) 
        {
            strcpy(word_arr[i],word[0]);
            read = read_text(textfile,ignorefile,word,size,changer);
            read_arr[i] = read;
                if(read == 0){
                    vector = check_vectors(word,size,vectored_word);
                    vector_arr[i] = vector;
                    strcpy(vectored_word_arr[i], vectored_word);
                }
        while(1)
        {
            k = 0 ;
            while((c = fgetc(ignore_ptr)) != EOF) {
                ignored_word[k] = c;
                k++;
                if(c == '\n') {
                ignored_word[k-1] = '\0';
                break;
                }
            }
            if(strcmp(ignored_word , word_arr[i]) == 0) {
                ignored_count[i]++;

            }

        if(c == EOF) {
            break;
        }
        }
        rewind(ignore_ptr);
        }
        func(word_arr,read_arr,vector_arr,size,vectored_word_arr,ignored_count,scale);
    }
    else if(size <= 0) 
    {
        printf("Enter a valid number!");
        return 0;
    }
    else{
        ignore_ptr = fopen("ignore.txt" , "r");
        for(i = 0 ; i < size ; i++) 
        {
            printf("Enter your %d. word: " , i + 1);
                scanf("%s" , word );
            strcpy(word_arr[i],word[0]);
            read = read_text(textfile,ignorefile,word,size,changer);
            read_arr[i] = read;
                if(read == 0){
                    vector = check_vectors(word,size,vectored_word);
                    vector_arr[i] = vector;
                    strcpy(vectored_word_arr[i], vectored_word);
                }
        while(1)
        {
            k = 0 ;
            while((c = fgetc(ignore_ptr)) != EOF) {
                ignored_word[k] = c;
                k++;
                if(c == '\n') {
                ignored_word[k-1] = '\0';
                break;
                }
            }
            if(strcmp(ignored_word , word_arr[i]) == 0) {
                ignored_count[i]++;

            }

        if(c == EOF) {
            break;
        }
        }
        rewind(ignore_ptr);
        }
        func(word_arr,read_arr,vector_arr,size,vectored_word_arr,ignored_count,scale);
        read_dict("dictionary.txt" , dict);
        printf("DO YOU WANT TO SEE THE DICTIONARY? (Y/N)");
            scanf(" %c", &select);
        if(select == 'Y'){
            print_dict("dictionary.txt" , dict);
        }
        fclose(ignore_ptr);
    }
}
