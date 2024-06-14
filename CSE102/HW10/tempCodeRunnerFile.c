#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//book struct
struct Book {
    char isbn[30];
    char title[30];
    char author[30];
    char status;
    int publish_year;
    int LL_flag;    //Linked list flag
    int text_flag;  //Text file flag
    struct Book *next;
};

//student struct
struct Student {
    char name[30];
    char borrowed_books[30];
    int id;
    int text_flag;          //Text file flag
    int LL_flag;            //Linked list flag
    struct Student *next;
};

//filter struct for filter and sort function
struct Filter {
    char isbn[30];
    char title[30];
    char author[30];
    char status;
    int publish_year;
    int flag;
    struct Filter *next;
};

//printing the sorted list
void print_sorted(struct Filter *head) {
    if(head == NULL) {
        printf("List is empty\n");
    }
    struct Filter *p;
    p = head;
    int num = 0;
    printf("\nFiltered and Sorted Book List: \n");
    while(p != NULL) {
        printf("%s , %s , %s , %d\n", p->isbn , p->title , p->author , p->publish_year);
        p = p->next;
        num++;
    }
    printf("\n");
}
//swap function for filter and sort function
void swap(struct Filter *a, struct Filter *b){

	char c_temp[30];
    int i_temp;
    strcpy(c_temp , a->isbn);
    strcpy(a->isbn , b->isbn);
    strcpy(b->isbn , c_temp);
    strcpy(c_temp , a->title);
    strcpy(a->title , b->title);
    strcpy(b->title , c_temp);
    strcpy(c_temp , a->author);
    strcpy(a->author , b->author);
    strcpy(b->author , c_temp);
    i_temp = a->publish_year;
	a->publish_year = b->publish_year;
	b->publish_year = i_temp;

}
//bubble sort function for filter and sort function
void bubble_sort(struct Filter *filt , int sort_choice){
	int swapped, i;
	struct Filter *ptr1;
	struct Filter *ptr2 = NULL;
	do
	{
		swapped = 0;
		ptr1 = filt;
        
		while (ptr1->next != ptr2)
		{
            if(sort_choice == 2) {
                if (ptr1->publish_year > ptr1->next->publish_year) // checking the publish year
			    {
				    swap(ptr1, ptr1->next);
				    swapped = 1;
			    }
			ptr1 = ptr1->next;
            }
            else if(sort_choice == 1) {
                if (strcmp(ptr1->author , ptr1->next->author) > 0)  // comparing the authors
			    {
				    swap(ptr1, ptr1->next);
				    swapped = 1;
			    }
			ptr1 = ptr1->next;
            }
            else if(sort_choice == 0) {
                if (strcmp(ptr1->title , ptr1->next->title) > 0)    //comparing the titles.
			    {
				    swap(ptr1, ptr1->next);
				    swapped = 1;
			    }
			ptr1 = ptr1->next;
            }
        }
		ptr2 = ptr1;
	}
	while (swapped);

}
//printing the borrowed list
void borrowed_list(struct Student *stu_head , int id) {
    
    struct Student *ps;
    ps = stu_head;
    int flag = 0;

    printf("%d numbered Students Borrowed Books:\n" , id);
    while(ps != NULL) {
        if(ps->id == id) {  //if input is equal to id
            flag = 1;
            printf("%s\n" ,ps->borrowed_books);
        }
        ps = ps->next;
    }
    if(flag == 0) {
        printf("There is no borrowed books for %d\n" , id);
    }
}
//Adding student to linked list and text file.
void add_student(struct Student *stu_head , struct Book *lib_head, int id, char *name, char *isbn) {

    struct Student *ps , *temp;
    struct Book *pb;
    pb = lib_head;
    ps = stu_head;
    //if LL is empty.
    if(stu_head->LL_flag == 0) {    
        strcpy(stu_head->borrowed_books , isbn);
        strcpy(stu_head->name , name);
        stu_head->id = id;
        stu_head->next = NULL;
        stu_head->LL_flag = 1;      //change it to not empty
    }
    else {  
        //creating new memory for the new student.
        temp = (struct Student *)malloc(sizeof(struct Student));
        strcpy(temp->borrowed_books , isbn);
        strcpy(temp->name , name);
        temp->id = id;
        while(ps->next != NULL) {
            ps = ps->next;
        }
        ps->next = temp;
        temp->next = NULL;
    }
    //adding the new student to the students.txt file
    if(stu_head->text_flag == 0) {
        FILE *stu_ptr = fopen("students.txt" , "a");
        fprintf(stu_ptr , "%s, %d, %s\n" , name , id , isbn);
        fclose(stu_ptr);
    }
}
//removing student from list and file
struct Student * remove_student(struct Student *stu_head , char *isbn , int id) {

    //if list is empty
    if(stu_head->LL_flag == 0) {
        printf("There is no student!\n");
    }
    else {
        struct Student *pc , *pp;
        pc = stu_head;
        pp = stu_head;
        //check until the end of the list.
        while(pc != NULL) {
            //check if the id numbers match.
            if(pc->id == id){
                if(stu_head->id == id) {
                    stu_head = stu_head->next;
                    free(pc);
                    free(pp);
                }
                pp->next = pc->next;
                pc->next = NULL;
                free(pc);
                break;
            }
            pp = pc;
            pc = pc->next;
        }
    }

    //removing from the file
    FILE *temp_ptr = fopen("temp_students.txt" , "a");
    FILE *status_ptr = fopen("status.txt" , "r");
    FILE *temp_status_ptr = fopen("temp_status.txt" , "a");

    struct Student *ps;
    ps = stu_head;
    char name[30] , borrowed[30] , c;
    char status , temp_isbn[30];
    int stu_id , line = 0;

    //getting the line count in status file.
    while((c = fgetc(status_ptr)) != EOF) {
        if(c == '\n') {
            line++;
        }
    }
    rewind(status_ptr);
    
    //changing the status of the borrowed book.
    while(line > 0) {
        fscanf(status_ptr ,"%[^,], %c\n" , temp_isbn , &status);
        if(strcmp(isbn , temp_isbn) != 0) {
            fprintf(temp_status_ptr , "%s, %c\n" , temp_isbn , status);
        }
        line--;
    }
    //changing the student file 
    while(ps != NULL) {
        fprintf(temp_ptr, "%s, %d, %s\n" , ps->name , ps->id, ps->borrowed_books);
        ps = ps->next;
    }

    fclose(temp_ptr);
    fclose(status_ptr);
    fclose(temp_status_ptr);
    remove("status.txt");
    rename("temp_status.txt" , "status.txt");
    remove("students.txt");
    rename("temp_students.txt" , "students.txt");
    
    return stu_head;



}
void borrow_book(struct Book *lib_head , struct Student *stu_head, char *isbn){

    struct Book *pb;
    pb = lib_head;

    FILE *status_ptr = fopen("status.txt" , "r");
    FILE *temp_status_ptr = fopen("temp_status.txt" , "w");

    char name[30], temp_isbn[30] , status , c;
    int id , flag = 0 , line = 0;
    
    printf("Enter the name of the student: ");
        scanf("%s" , name);
    printf("Enter the id of the student: ");
        scanf("%d" , &id);

    while(pb != NULL) {
        //checking the isbn numbers.
        if(strcmp(pb->isbn , isbn) == 0) {
            flag = 1;   //changing the flag.
            //if the book is available.
            if(pb->status == 'A') {
                pb->status = 'B';
                //adding the student to the list.
                add_student(stu_head,lib_head,id,name,isbn);
                
                while((c = fgetc(status_ptr)) != EOF) {
                    if(c == '\n') {
                        line++;
                    }
                }
                rewind(status_ptr);
                //changing the status file.
                while(line > 0) {
                    fscanf(status_ptr , "%[^,], %c\n" , temp_isbn , &status);
                    if(strcmp(temp_isbn , isbn) != 0) {
                        fprintf(temp_status_ptr , "%s, %c\n" , temp_isbn , status);
                    }
                    else {
                        fprintf(temp_status_ptr , "%s, %c\n" , temp_isbn , pb->status);
                    }
                    line--;
                }
            }
            else {
                printf("Book is not available!\n");
            }
        }
        pb = pb->next;
    }
    if(flag == 0) {
        printf("Book does not exits!\n");
    }

    fclose(status_ptr);
    fclose(temp_status_ptr);
    remove("status.txt");
    rename("temp_status.txt" , "status.txt");

}
void return_book(struct Book *lib_head, struct Student *stu_head , char *isbn){
    
    struct Book *pb;
    pb = lib_head;

    FILE *status_ptr = fopen("status.txt" , "r");
    FILE *temp_status_ptr = fopen("temp_status.txt" , "w");
    char name[30], temp_isbn[30] , status , c;
    int id , flag = 0 , line = 0;
    printf("Enter the name of the student: ");
        scanf("%s" , name);
    printf("Enter the id of the student: ");
        scanf("%d" , &id);

    while(pb != NULL) {
        //cheking the isbn numbers
        if(strcmp(pb->isbn , isbn) == 0) {
            flag = 1; //changing the flag
            //if book is borrowed
            if(pb->status == 'B') {
                pb->status = 'A';
                //removing the student
                stu_head = remove_student(stu_head,isbn,id);
                while((c = fgetc(status_ptr)) != EOF) {
                    if(c == '\n') {
                        line++;
                    }
                }
                rewind(status_ptr);
                //changing the status file
                while(line > 0) {
                    fscanf(status_ptr , "%[^,], %c\n" , temp_isbn , &status);
                    if(strcmp(temp_isbn , isbn) != 0) {
                        fprintf(temp_status_ptr , "%s, %c\n" , temp_isbn , status);
                    }
                    else {
                        fprintf(temp_status_ptr , "%s, %c\n" , temp_isbn , pb->status);
                    }
                    line--;
                }
            }
            else {
                printf("Book is not booked!\n");
            }
        }
        pb = pb->next;
    }
    if(flag == 0) {
        printf("Book does not exits!\n");
    }
    fclose(status_ptr);
    fclose(temp_status_ptr);
    remove("status.txt");
    rename("temp_status.txt" , "status.txt");
    

}
void search_book(struct Book *lib_head , int search_choice , char *search_value){
    
    struct Book *p;
    p = lib_head;

    //checking the search choice
    if(search_choice == 0) {
        while(p != NULL) {
            //printing according to isbn number 
            if(strcmp(p->isbn , search_value) == 0) {
                printf("%s, %s, %s, %d\n", p->isbn , p->title , p->author , p->publish_year);
            }
            p = p->next;
        }
    }
    else if(search_choice == 1) {
        while(p != NULL) {
            //printing according to author            
            if(strcmp(p->author , search_value) == 0) {
                printf("%s, %s, %s, %d\n", p->isbn , p->title , p->author , p->publish_year);
            }
            p = p->next;
        }
    }
            //printing according to title
    else if(search_choice == 2) {
        while(p != NULL) {
            if(strcmp(p->title , search_value) == 0) {
                printf("%s, %s, %s, %d\n", p->isbn , p->title , p->author , p->publish_year);
            }
            p = p->next;
        }
    }
}

struct Book * reverse_book_list(struct Book * lib_head) {

    struct Book *prev = NULL;
    struct Book *after = NULL;
    //reversing the list.
    while(lib_head != NULL) {
        after = lib_head->next;
        lib_head->next = prev;
        prev = lib_head;
        lib_head = after;
    }
    lib_head = prev;
    return lib_head;
}
void filter_and_sort(int filter_choice , char *filter , int sort_choice) {

    FILE *book_ptr = fopen("books.txt" , "r");
    char isbn[30], title[30], author[30];
    int publish_year;
    int line = 0;
    char c;

    struct Filter *filt = (struct Filter *)malloc(sizeof(struct Filter));
    struct Filter *p , *pc;
    
    p = filt;
    pc = filt;
    filt->flag = 0;

    while((c = fgetc(book_ptr)) != EOF) {
            if(c == '\n') {
                line++;
            }
        }
    rewind(book_ptr);

    //cheking the filter choice
    if(filter_choice == 0) {
        while(line > 0) {
            fscanf(book_ptr , "%[^,], %[^,], %[^,], %d\n" , isbn , title , author , &publish_year );
            if(strcmp(author , filter) == 0) {
                //cheking the flag
                if(filt->flag == 0) {
                    strcpy(filt->isbn,isbn);
                    strcpy(filt->title,title);
                    strcpy(filt->author,author);
                    filt->publish_year = publish_year;
                    filt->next = NULL;
                }
                else {
                    struct Filter *temp = malloc(sizeof(struct Filter));
                    strcpy(temp->isbn,isbn);
                    strcpy(temp->title,title);
                    strcpy(temp->author,author);
                    temp->publish_year = publish_year;
                    while(p->next != NULL) {
                        p = p->next;
                    }
                    p->next = temp;
                    temp->next = NULL;
                }
                filt->flag = 1;
            }
            line--;
        }
    }
    else if(filter_choice == 1) {
        int temp_year = atoi(filter);
        while(line > 0) {
            fscanf(book_ptr , "%[^,], %[^,], %[^,], %d\n" , isbn , title , author , &publish_year);
            if(publish_year == temp_year) {
                if(filt->flag == 0) {
                    strcpy(filt->isbn,isbn);
                    strcpy(filt->title,title);
                    strcpy(filt->author,author);
                    filt->publish_year = publish_year;
                    filt->next = NULL;
                }
                else {
                    struct Filter *temp = malloc(sizeof(struct Filter));
                    strcpy(temp->isbn,isbn);
                    strcpy(temp->title,title);
                    strcpy(temp->author,author);
                    temp->publish_year = publish_year;
                    while(p->next != NULL) {
                        p = p->next;
                    }
                    p->next = temp;
                    temp->next = NULL;
                }
                filt->flag = 1;
            }
            line--;
        }
    }
    //calling the sort function
    bubble_sort(filt , sort_choice);
    print_sorted(filt);
    
}
void update_book(struct Book *lib_head, char *isbn, char *feature, char *value)  {

    char t_isbn[30], title[30], author[30];
    int publish_year;
    int line = 0;
    char c;

    FILE *book_ptr = fopen("books.txt", "r");
    FILE *temp = fopen("temp_books.txt" , "w");

    //updating in the LL and text file at the same time
    struct Book *pc;
    pc = lib_head;
    if(strcmp(feature , "title") == 0) {
        while(strcmp(pc->isbn , isbn) != 0){
            pc = pc->next;
        }
        strcpy(pc->title , value);

        while((c = fgetc(book_ptr)) != EOF) {
            if(c == '\n') {
                line++;
            }
        }
        rewind(book_ptr);
        //changing the books text file
        while(line > 0) {
            fscanf(book_ptr , "%[^,], %[^,], %[^,], %d\n" , t_isbn , title , author , &publish_year);
            if(strcmp(t_isbn , isbn) != 0) {
                fprintf(temp ,"%s, %s, %s, %d\n" , t_isbn , title , author , publish_year);
            }
            else {
                fprintf(temp ,"%s, %s, %s, %d\n" , t_isbn , value , author , publish_year);
            }
            line--;
        }
    }
    //checking the feature
    if(strcmp(feature , "author") == 0) {
        while(strcmp(pc->isbn , isbn) != 0){
            pc = pc->next;
        }
        strcpy(pc->author , value);

        while((c = fgetc(book_ptr)) != EOF) {
            if(c == '\n') {
                line++;
            }
        }
        rewind(book_ptr);
        while(line > 0) {
            fscanf(book_ptr , "%[^,], %[^,], %[^,], %d\n" , t_isbn , title , author , &publish_year);
            if(strcmp(t_isbn , isbn) != 0) {
                fprintf(temp ,"%s, %s, %s, %d\n" , t_isbn , title , author , publish_year);
            }
            else {
                fprintf(temp ,"%s, %s, %s, %d\n" , t_isbn , title , value , publish_year);
            }
            line--;
        }
    }
    //checking the feature
    if(strcmp(feature , "year") == 0) {

        int pub_year = atoi(value);
        while(strcmp(pc->isbn , isbn) != 0){
            pc = pc->next;
        }
        pc->publish_year = pub_year;

        while((c = fgetc(book_ptr)) != EOF) {
            if(c == '\n') {
                line++;
            }
        }
        rewind(book_ptr);

        while(line > 0) {
            fscanf(book_ptr , "%[^,], %[^,], %[^,], %d\n" , t_isbn , title , author , &publish_year);
            if(strcmp(t_isbn , isbn) != 0) {
                fprintf(temp ,"%s, %s, %s, %d\n" , t_isbn , title , author , publish_year);
            }
            else {
                fprintf(temp ,"%s, %s, %s, %d\n" , t_isbn , title , author , pub_year);
            }
            line--;
        }
    }
    fclose(book_ptr);
    fclose(temp);
    remove("books.txt");
    rename("temp_books.txt" , "books.txt");

    
}
struct Book * delete_book(struct Book *lib_head , char *isbn) {

    //deleting from the LL
    //if the list is empty.
    if(lib_head->LL_flag == 0) {
        printf("List is empty!\n");
    }
    else {
        struct Book *pc , *pp;
        int check;
        pc = lib_head;
        pp = lib_head;
        //check until the end of the list.
        while(pc != NULL) {
            //check if the isbn numbers match.
            check = strcmp(pc->isbn , isbn);   
            if(check == 0){
                if(strcmp(lib_head->isbn , isbn) == 0) {
                    lib_head = lib_head->next;
                    free(pc);
                    free(pp);
                }
                pp->next = pc->next;
                pc->next = NULL;
                free(pc);
                break;
            }
            pp = pc;
            pc = pc->next;
        }
    }

    //deleting from the txt file.
    FILE *temp_book_ptr = fopen("temp_books.txt" , "a");
    FILE *temp_status_ptr = fopen("temp_status.txt" , "a");

    struct Book *pb;
    pb = lib_head;

    char b_isbn[30] , s_isbn[30], title[30], author[30];
    int publish_year;
    int line = 0;
    char c , status;

    lib_head->text_flag = 1;
    while(pb != NULL) {
    fprintf(temp_book_ptr ,"%s, %s, %s, %d\n" , pb->isbn , pb->title , pb->author , pb->publish_year);
    fprintf(temp_status_ptr , "%s, %c\n" , pb->isbn, pb->status);
    pb = pb->next;
    }

    fclose(temp_book_ptr);
    fclose(temp_status_ptr);
    remove("status.txt");
    rename("temp_status.txt" , "status.txt");
    remove("books.txt");
    rename("temp_books.txt" , "books.txt");
    return lib_head;

}
struct Book * add_book(struct Book * lib_head , char *isbn , char *title , char *author , int publish_year , int method) {

    struct Book *p , *temp;
    p = lib_head;

    //checking the method.
    //LIFO - FIFO
    if(method == 1) {
        if(lib_head->LL_flag == 0) {
        strcpy(lib_head->isbn,isbn);
        strcpy(lib_head->title,title);
        strcpy(lib_head->author,author);
        lib_head->publish_year = publish_year;
        lib_head->status = 'A';
        lib_head->next = NULL;
        lib_head->LL_flag = 1;
    }
    else {
        temp = (struct Book *)malloc(sizeof(struct Book));
        strcpy(temp->isbn,isbn);
        strcpy(temp->title,title);
        strcpy(temp->author,author);
        temp->publish_year = publish_year;
        temp->status = 'A';
        while(p->next != NULL) {
            p = p->next;
        }
        p->next = temp;
        temp->next = NULL;
    }
    }
    if(method == 0) {
        if(lib_head->LL_flag == 0) {
        strcpy(lib_head->isbn,isbn);
        strcpy(lib_head->title,title);
        strcpy(lib_head->author,author);
        lib_head->publish_year = publish_year;
        lib_head->status = 'A';
        lib_head->next = NULL;
        lib_head->LL_flag = 1;
    }
    else {
        temp = (struct Book *)malloc(sizeof(struct Book));
        strcpy(temp->isbn,isbn);
        strcpy(temp->title,title);
        strcpy(temp->author,author);
        temp->publish_year = publish_year;
        temp->status = 'A';

        temp->next = lib_head;
        lib_head = temp;
        return lib_head;
    }
    }
        //checking the text flag and printing to the file
        if(lib_head->text_flag == 0) {
            FILE *book_ptr = fopen("books.txt" , "a");
            fprintf(book_ptr ,"%s, %s, %s, %d\n" , isbn , title , author , publish_year );
            fclose(book_ptr);
        }
        //adding the book available to the status file
        FILE *status_ptr = fopen("status.txt" , "a");
        fprintf(status_ptr ,"%s, A\n" , isbn);
        fclose(status_ptr);

        

}

void get_student(struct Student *stu_head , struct Book *lib_head) {

    FILE *stu_ptr = fopen("students.txt" , "r");
    char name[30], isbn[30];
    int id;
    int line = 0;
    char c;

        while((c = fgetc(stu_ptr)) != EOF) {
            if(c == '\n') {
                line++;
            }
        }
        rewind(stu_ptr);
        //changint the text flag to 1
        stu_head->text_flag = 1;
        //writing to the file
        while(line > 0) {
            fscanf(stu_ptr ,"%[^,], %d, %s\n" , name , &id , isbn);
            line--;
            add_student(stu_head ,lib_head,id,name,isbn);
        }
        fclose(stu_ptr);
        if(line == 0) {
            stu_head->text_flag = 0;
        }
}
void get_books(struct Book *lib_head , int method) {

        FILE *book_ptr = fopen("books.txt" , "r");
        char isbn[30], title[30], author[30], status;
        int publish_year;
        int line = 0;
        char c;
        
        while((c = fgetc(book_ptr)) != EOF) {
            if(c == '\n') {
                line++;
            }
        }
        rewind(book_ptr);
        //changing the text flag to 1
        lib_head->text_flag = 1;
        while(line > 0) {
            fscanf(book_ptr , "%[^,], %[^,], %[^,], %d\n" , isbn , title , author , &publish_year);
            line--;
            add_book(lib_head ,isbn ,title , author ,publish_year , method);
        }
        fclose(book_ptr);
        
        if(line == 0) {
            lib_head->text_flag = 0;
        }
}
int main() {

    struct Book *lib_head = (struct Book *)malloc(sizeof(struct Book));
    struct Student *stu_head = (struct Student * )malloc(sizeof(struct Student));
    struct Book *temp_book;
    struct Student *temp_stu;
    char b_isbn[30], b_title[30], b_author[30], b_status;
    int b_public , b_method;
    char feature[30] , value[30];
    int filter_choice , sort_choice;
    char filter[30];
    int search_choice;
    char search_value[30];
    int select , flag = 0;
    int id , method;

    lib_head->LL_flag = 0;
    lib_head->text_flag = 0;
    stu_head->LL_flag = 0;
    stu_head->text_flag = 0;

    remove("status.txt");

    get_books(lib_head,1);
    get_student(stu_head,lib_head);

    while(1) {
    printf("Welcome to the Library Management System!\n");
    printf("1. Add Book\n");
    printf("2. Delete Book\n");
    printf("3. Update Book\n");
    printf("4. Filter and Sort Books\n");
    printf("5. Reverse Book List\n");
    printf("6. Search Books\n");
    printf("7. Borrow Book\n");
    printf("8. Return Book\n");
    printf("9. See Borrowed Books\n");
    printf("10. Exit\n");
    printf("Enter your selection: ");
        scanf("%d" , &select);
        switch(select) {
            case 1:
                printf("Enter the ISBN number of the book: ");
                    scanf("%s" , b_isbn);
                printf("Enter the Title of the book: ");
                    scanf("%s" , b_title);
                printf("Enter the Author of the book: ");
                    scanf("%s" , b_author);
                printf("Enter the Publication Year of the book: ");
                    scanf("%d" , &b_public);
                printf("Enter the Management Method: ");
                    scanf("%d" , &b_method);

                if(b_method == 0) {
                    lib_head = add_book(lib_head,b_isbn,b_title,b_author,b_public,b_method);
                }
                else {
                    add_book(lib_head,b_isbn,b_title,b_author,b_public,b_method);
                }
                break;
            case 2:
                printf("Enter the ISBN number of the book you want to delete: ");
                    scanf("%s" , b_isbn);
                lib_head = delete_book(lib_head , b_isbn);
                break;
            case 3:
                printf("Enter the ISBN number of the book you want to update: ");
                    scanf("%s" , b_isbn);
                printf("Enter the feature you want to change: ");
                    scanf("%s" , feature);
                printf("Enter the new value: ");
                    scanf("%s" , value);
                update_book(lib_head , b_isbn , feature , value);
                break;
            case 4:
                printf("Enter the filter you want to use (0 for author, 1 for publication year): ");
                    scanf("%d" , &filter_choice);
                printf("Enter the filter criteria in string format: ");
                    scanf("%s" , filter);
                printf("Enter the sorting choice (0 for title, 1 for author, 2 for publication year): ");
                    scanf("%d" , &sort_choice);
                filter_and_sort(filter_choice,filter,sort_choice);
                break;
            case 5:
                printf("Reversed List of the books: ");
                lib_head = reverse_book_list(lib_head);
                break;
            case 6:
                printf("Enter the choice for searching the books(0 for ISBN, 1 for Author, 2 for Title): ");
                    scanf("%d" , &search_choice);
                printf("Enter the value criteria: ");
                    scanf("%s" , search_value);
                search_book(lib_head,search_choice,search_value);
                break;
            case 7:
                printf("Enter the ISBN number of the book you want to borrow: ");
                    scanf("%s" , b_isbn);
                borrow_book(lib_head,stu_head,b_isbn);
                break;
            case 8:
                printf("Enter the ISBN number of the book you want to return: ");
                    scanf("%s" , b_isbn);
                return_book(lib_head,stu_head,b_isbn);
                break;
            case 9:
                printf("Enter the student id: ");
                    scanf("%d" , &id);
                borrowed_list(stu_head,id);
            case 10:
                flag = 1;
                break;
        }
        if(flag == 1) {
            break;
        }
    }
    //free the structs
    while(stu_head != NULL) {
        temp_stu = stu_head;
        stu_head = stu_head->next;
        free(temp_stu);
    }
    while(lib_head != NULL) {
        temp_book = lib_head;
        lib_head = lib_head->next;
        free(temp_book);
    }

    return 0;
}
