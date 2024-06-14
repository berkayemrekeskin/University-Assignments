#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Node {
    void *data;
    struct Node *next;
} Node;
typedef struct {
    char type[20];  //Asset1
    int ivals[1];
    double svals[1];
} Asset1;
typedef struct {
    char type[20];  //asset2
    int ivals[2];
    double svals[2];
} Asset2;
typedef struct {
    char type[20];  //Asset3
    char string1[50];
    char string2[50];
} Asset3;
typedef struct {
    char type[20];  //Asset4
    double value1;
    float value2;
    double value3;
} Asset4;

//This function creates random assets and adds them into the linked list
void fillLinkedList(Node **head) {
    switch(rand() % 4) {    //Random number between 0-3 to create random assets
        case 0:
            Asset1 *asset1 = (Asset1 *)malloc(sizeof(Asset1));  //Creating the asset
            //Assignments
            strcpy(asset1->type, "ASSET1");
            asset1->ivals[0] = rand() % 10; 
            asset1->svals[0] = (double)(rand() % 10);
            //Adding to head
            if(*head == NULL) {
                (*head) = (Node *)malloc(sizeof(Node));
                (*head)->data = asset1;
                (*head)->next = NULL;
                printf("Type: %s\n", ((Asset1 *)(*head)->data)->type);
                printf("Integer: %d\n", ((Asset1 *)(*head)->data)->ivals[0]);
                printf("Double: %lf\n", ((Asset1 *)(*head)->data)->svals[0]);
                printf("----------------------\n");
            }
            else { 
                Node *current = *head;
                while(current->next != NULL) {  //Traverse the list until the end
                    current = current->next;
                }
                Node *new = (Node *)malloc(sizeof(Node));
                new->data = asset1;
                new->next = NULL;
                current->next = new;
                printf("Type: %s\n", ((Asset1 *)new->data)->type);
                printf("Integer: %d\n", ((Asset1 *)new->data)->ivals[0]);
                printf("Double: %lf\n", ((Asset1 *)new->data)->svals[0]);
                printf("----------------------\n");
            }
            break;
        case 1:
            Asset2 *asset2 = (Asset2 *)malloc(sizeof(Asset2));  //Creating the asset
            //Assignments
            strcpy(asset2->type, "ASSET2");
            asset2->ivals[0] = rand() % 10;
            asset2->ivals[1] = rand() % 10;
            asset2->svals[0] = (double)(rand() % 10);
            asset2->svals[1] = (double)(rand() % 10);
            //Adding to head
            if(*head == NULL) {
                (*head) = (Node *)malloc(sizeof(Node));
                (*head)->data = asset2;
                (*head)->next = NULL;
                printf("Type: %s\n", ((Asset2 *)(*head)->data)->type);
                printf("Integer1: %d\n", ((Asset2 *)(*head)->data)->ivals[0]);
                printf("Integer2: %d\n", ((Asset2 *)(*head)->data)->ivals[1]);
                printf("Double1: %lf\n", ((Asset2 *)(*head)->data)->svals[0]);                
                printf("Double2: %lf\n", ((Asset2 *)(*head)->data)->svals[1]);
                printf("----------------------\n");
            }
            else {
                Node *current = *head;
                while(current->next != NULL) {
                    current = current->next;
                }
                Node *new = (Node *)malloc(sizeof(Node));
                new->data = asset2;
                new->next = NULL;
                current->next = new;
                printf("Type: %s\n", ((Asset2 *)new->data)->type);
                printf("Integer1: %d\n", ((Asset2 *)new->data)->ivals[0]);
                printf("Integer2: %d\n", ((Asset2 *)new->data)->ivals[1]);
                printf("Double1: %lf\n", ((Asset2 *)new->data)->svals[0]);                
                printf("Double2: %lf\n", ((Asset2 *)new->data)->svals[1]);
                printf("----------------------\n");
            }
            break;
        case 2:
            Asset3 *asset3 = (Asset3 *)malloc(sizeof(Asset3));  //Creating the asset
            //Assignments
            strcpy(asset3->type, "ASSET3");
            for(int i = 0 ; i < 19 ; i++) {
                asset3->string1[i] = (rand() % 25) + 97;    
                asset3->string2[i] = (rand() % 25) + 97;    
            }
            asset3->string1[19] = '\0';
            asset3->string2[19] = '\0';
            //Adding to head
            if(*head == NULL) {
                (*head) = (Node *)malloc(sizeof(Node));
                (*head)->data = asset3;
                (*head)->next = NULL;
                printf("Type: %s\n", ((Asset3 *)(*head)->data)->type);
                printf("STR1: %s\n", ((Asset3 *)(*head)->data)->string1);
                printf("STR2: %s\n", ((Asset3 *)(*head)->data)->string2);
                printf("----------------------\n");
            }
            else {
                Node *current = *head;
                while(current->next != NULL) {
                    current = current->next;
                }
                Node *new = (Node *)malloc(sizeof(Node));
                new->data = asset3;
                new->next = NULL;
                current->next = new;
                printf("Type: %s\n", ((Asset3 *)new->data)->type);
                printf("STR1: %s\n", ((Asset3 *)new->data)->string1);
                printf("STR2: %s\n", ((Asset3 *)new->data)->string2);
                printf("----------------------\n");
            }
            break;
        case 3:
            Asset4 *asset4 = (Asset4 *)malloc(sizeof(Asset4));  //Creating the asset
            //Assignments
            strcpy(asset4->type, "ASSET4");
            asset4->value1 = (double)(rand() % 10);
            asset4->value2 = (float)(rand() % 10);
            asset4->value3 = (double)(rand() % 10);
            //Adding to head
            if(*head == NULL) {
                (*head) = (Node *)malloc(sizeof(Node));
                (*head)->data = asset4;
                (*head)->next = NULL;
                printf("Type: %s\n", ((Asset4 *)(*head)->data)->type);
                printf("DOUBLE1: %lf\n", ((Asset4 *)(*head)->data)->value1);
                printf("FLOAT: %f\n", ((Asset4 *)(*head)->data)->value2);
                printf("DOUBLE2: %lf\n", ((Asset4 *)(*head)->data)->value3);
                printf("----------------------\n");
            }
            else {
                Node *current = *head;
                while(current->next != NULL) {
                    current = current->next;
                }
                Node *new = (Node *)malloc(sizeof(Node));
                new->data = asset4;
                new->next = NULL;
                current->next = new;
                printf("Type: %s\n", ((Asset4 *)new->data)->type);
                printf("DOUBLE1: %lf\n", ((Asset4 *)new->data)->value1);
                printf("FLOAT: %f\n", ((Asset4 *)new->data)->value2);
                printf("DOUBLE2: %lf\n", ((Asset4 *)new->data)->value3);
                printf("----------------------\n");
            }
            break;
    }
}
//This function serializes the linked list. It writes the list to the binary file
void serializeLinkedList(Node *head) {
    FILE *fptr = fopen("linkedlist.bin" , "wb");
    while(head != NULL) {
        //Checking the asset names and writing the assets to the binary file
        if(strcmp(head->data, "ASSET1") == 0) {
            fwrite(head->data, sizeof(Asset1), 1, fptr);
        }
        else if(strcmp(head->data, "ASSET2") == 0) {
            fwrite(head->data, sizeof(Asset2), 1, fptr);
        }
        else if(strcmp(head->data, "ASSET3") == 0) {
            fwrite(head->data, sizeof(Asset3), 1, fptr);
        }
        else if(strcmp(head->data, "ASSET4") == 0) {
            fwrite(head->data, sizeof(Asset4), 1, fptr);
        }
        head = head->next;
    }
    fclose(fptr);
}
//Free head function
void freeHead(Node *head) {
    Node *temp = NULL;
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}
//This function deserializes the linked list. It reads from the binary file
//and fills the head with the assets
void deserializeLinkedList(Node **head) {
    FILE *fptr = fopen("linkedlist.bin" , "rb");
    char type[20];
    freeHead(*head);    //I am freeing the head before filling it. Because if it is not free it will add to the tail
    *head = NULL;

    while(fread(type, sizeof(type), 1, fptr) > 0) { //First, we read the type of the asset
        if(strcmp(type, "ASSET1") == 0) {   //Then we compare it, if it is equal
            fseek(fptr, -sizeof(type), SEEK_CUR);   //Then we take the cursor to the head of the asset (Head of the line) We move back as we moved forward
            Asset1 *asset1 = (Asset1 *)malloc(sizeof(Asset1));  //After that we create new asset to fill
            if(fread(asset1, sizeof(Asset1), 1, fptr) > 0) {    //If fread reads, we fill the new linked list
                if(*head == NULL) {
                    (*head) = (Node *)malloc(sizeof(Node));
                    (*head)->data = asset1;
                    (*head)->next = NULL;
                }
                else {
                    Node *current = *head;
                    while(current->next != NULL) {
                        current = current->next;
                    }
                    Node *new = (Node *)malloc(sizeof(Node));
                    new->data = asset1;
                    new->next = NULL;
                    current->next = new;
                }
            }
        }
        //Same procedure for the other assets.
        else if(strcmp(type, "ASSET2") == 0) {
            fseek(fptr, -sizeof(type), SEEK_CUR);
            Asset2 *asset2 = (Asset2 *)malloc(sizeof(Asset2));
            if(fread(asset2, sizeof(Asset2), 1, fptr) > 0) {
                if(*head == NULL) {
                    (*head) = (Node *)malloc(sizeof(Node));
                    (*head)->data = asset2;
                    (*head)->next = NULL;
                }
                else {
                    Node *current = *head;
                    while(current->next != NULL) {
                        current = current->next;
                    }
                    Node *new = (Node *)malloc(sizeof(Node));
                    new->data = asset2;
                    new->next = NULL;
                    current->next = new;
                }
            }
        }
        else if(strcmp(type , "ASSET3") == 0) {
            fseek(fptr, -sizeof(type), SEEK_CUR);
            Asset3 *asset3 = (Asset3 *)malloc(sizeof(Asset3));
            if(fread(asset3, sizeof(Asset3), 1, fptr) > 0) {
                if(*head == NULL) {
                    (*head) = (Node *)malloc(sizeof(Node));
                    (*head)->data = asset3;
                    (*head)->next = NULL;
                }
                else {
                    Node *current = *head;
                    while(current->next != NULL) {
                        current = current->next;
                    }
                    Node *new = (Node *)malloc(sizeof(Node));
                    new->data = asset3;
                    new->next = NULL;
                    current->next = new;
                }
            }
        }
        else if(strcmp(type, "ASSET4") == 0) {
            fseek(fptr, -sizeof(type), SEEK_CUR);
            Asset4 *asset4 = (Asset4 *)malloc(sizeof(Asset4));
            if(fread(asset4, sizeof(Asset4), 1, fptr) > 0) {
                if(*head == NULL) {
                    (*head) = (Node *)malloc(sizeof(Node));
                    (*head)->data = asset4;
                    (*head)->next = NULL;
                }
                else {
                    Node *current = *head;
                    while(current->next != NULL) {
                        current = current->next;
                    }
                    Node *new = (Node *)malloc(sizeof(Node));
                    new->data = asset4;
                    new->next = NULL;
                    current->next = new;
                }
            }
        }
    }
    
}
int main() {
    srand(time(NULL));
    int size;
    size = (rand() % 10) + 10;  //Creating the linked list size between 10 and 19
    Node *head = NULL;  //Creating the node
    printf("\n\n----------------------  CREATING RANDOM ASSETS  ----------------------\n\n");
    printf("----------------------\n");
    while(size > 0) {   //Filling the linked list in random size each time we start
        fillLinkedList(&head);
        size--;
    }
    printf("\n");
    serializeLinkedList(head);  //Serialize link list
    printf("----------------------  SERIALIZED THE LIST ------------------------\n\n");
    deserializeLinkedList(&head);   //Deserialize link list
    printf("----------------------  DESERIALIZED THE LIST ----------------------\n\n");
    Node *current = head;   //This current is for the traverse while we print the assets
    printf("----------------------  AFTER DESERIALIZATION ----------------------\n\n");
    printf("----------------------\n");
    //Print the assets that read from the binary file
    while(current != NULL) {
        if(strcmp(current->data, "ASSET1") == 0) {
            printf("Type: %s\n", ((Asset1 *)(current)->data)->type);
            printf("Integer: %d\n", ((Asset1 *)(current)->data)->ivals[0]);
            printf("Double: %lf\n", ((Asset1 *)(current)->data)->svals[0]);
            printf("----------------------\n");
        }
        else if(strcmp(current->data, "ASSET2") == 0) {
            printf("Type: %s\n", ((Asset2 *)current->data)->type);
            printf("Integer1: %d\n", ((Asset2 *)current->data)->ivals[0]);
            printf("Integer2: %d\n", ((Asset2 *)current->data)->ivals[1]);
            printf("Double1: %lf\n", ((Asset2 *)current->data)->svals[0]);                
            printf("Double2: %lf\n", ((Asset2 *)current->data)->svals[1]);
            printf("----------------------\n");
        }
        else if(strcmp(current->data, "ASSET3") == 0) {
            printf("Type: %s\n", ((Asset3 *)current->data)->type);
            printf("STR1: %s\n", ((Asset3 *)current->data)->string1);
            printf("STR2: %s\n", ((Asset3 *)current->data)->string2);
            printf("----------------------\n");
        }
        else if(strcmp(current->data, "ASSET4") == 0) {
            printf("Type: %s\n", ((Asset4 *)current->data)->type);
            printf("Double1: %lf\n", ((Asset4 *)current->data)->value1);
            printf("Float: %f\n", ((Asset4 *)current->data)->value2);
            printf("Double2: %lf\n", ((Asset4 *)current->data)->value3);
            printf("----------------------\n");
        }
        current = current->next;
    }
    return 0;
}