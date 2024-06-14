#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Family {
	struct Family *mother;
	struct Family *father;
	int age;
	char name[20];
} Family;

typedef struct Tree {
		int familyCount;	//Number of families (used for txt files)
		int familySize;		//Size of a family tree
		struct Family **people; //2D array of people
} Tree;

//GENERAL FUNCTIONS
int mainMenu(int familySize);	//Main menu
void addPerson(Tree *root, char name[20], int age, char father[20], char mother[20]);	//Adding new person 
int getFileName(char *filename, int fileNumber);	//Creating the filename 
int findPerson(Tree *root, char *name);	//Finding the index number of a person
void freeTree(Tree *root);	//Freeing the family tree

//PART 1 FUNCTIONS
void removeFamilyTree();	//Removing a family tree
void saveFamilyTree(Tree *root);	//Saving the family tree to a file
int addFamilyTree(int familyCount);		//Add family tree general menu

//PART 2 FUNCTIONS
void loadFamilyTree(int familyCount);	//Load family tree general menu
void readPeople(const char filename[20], Tree *root);	//Reading people from the family tree file
void nuclearFamily(Tree *root, char name[20]);	//Printing the nuclear family of a person
void searchRelative(Tree *root, char name[20]);	//Searching for relatives general menu
void searchParents(Tree *root, char name[20]);	//Searching the parents of a person
void searchSpouse(Tree *root, char name[20]);	//Searching the spouse of a person
void searchChildren(Tree *root, char name[20]);	//Searching the children of a person
void searchGrandparents(Tree *root, char name[20]);	//Searching the grandparents of a person
void searchCousins(Tree *root, char name[20]);	//Searching the cousins of a person
void deletePerson(Tree *root, char name[20], char father[20], char mother[20], char filename[20]);	//Delete a person
void readForDelete(Tree *root, char filename[20], char removeName[20], int checkKids, char removeKids[][20]);	//Read from the file for deletePerson
void save(Tree *root, const char filename[20]);	//Saving the new family tree to the family tree file after deleting.

/*---------------------------------------------*/

int main() {
	//Counting the number of family trees before starting the functions.
	//This is required for the past family trees that are saved before.
	FILE *fptr;
	int i = 0 ;
	int counter = 1;
	int familyCount = 0;
	char filename[20];
	while(i < counter) {
		getFileName(filename,i+1);
		fptr = fopen(filename,"r");
		if(fptr != NULL) {
			familyCount++;	//If file exist, increase the familyCount
			counter++;	//This counter is for infinite loop until fptr cannot open a file
		}
		else {
			break;
		}
		i++;
	}
	mainMenu(familyCount);	//Calling the mainMenu function for operaitons
	//I am sending the family count for the usage 
}
int mainMenu(int familyCount) {
	int flag = 1;
	int input;
	while (flag)
	{
		printf("Family Tree System Menu:\n");
		printf("1- Add Family Tree\n");
		printf("2- Remove Family Tree\n");
		printf("3- Load Family Tree\n");
		printf("4- Exit\n");
		printf("> ");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			addFamilyTree(familyCount);
			break;
		case 2:
			removeFamilyTree(familyCount);
			break;
		case 3:
			loadFamilyTree(familyCount);
			break;
		case 4:
			printf("Goodbye!\n");
			flag = 1;
			break;
		default:
			printf("\nInvalid Input !\n");
		}
		if(flag == 1) {
			break;
		}
	}
}
void addPerson(Tree *root, char name[20], int age, char father[20], char mother[20]) {
	if (root->people == NULL) {
		Family *new_person = (Family *)malloc(sizeof(Family));		//Creating new node
		root->people = (Family **)malloc(sizeof(Family *));		//Creating the tree
		root->people[0] = new_person;		//Assigning the first person as root
		strcpy(root->people[0]->name, name);
		root->people[0]->age = age;
		root->people[0]->mother = NULL;		//Assigning the first persons mother to NULL
		root->people[0]->father = NULL;		//Assigning the first persons father to NULL
		root->familySize++;		//Increasing the family size
		return ;
	}
	else {
		int find_mother, find_father;
		find_mother = findPerson(root, mother);		//Searching the mother if she exist
		find_father = findPerson(root, father);		//Searching the father if he exist
		Family *new_person = (Family *)malloc(sizeof(Family));	//Allocating new memory for new person
		root->people = (Family **)realloc(root->people, (sizeof(Family *) * (root->familySize + 2)));	//Reallocating the tree's memory

		root->people[root->familySize] = new_person;	//Assigning the new person to last node
		strcpy(root->people[root->familySize]->name, name);
		root->people[root->familySize]->age = age;

		if (find_mother != -1) {
			root->people[root->familySize]->mother = root->people[find_mother];		//If mother exist, assign her
		}
		else {
			Family *mom = (Family *)malloc(sizeof(Family));		//If not create new mother
			mom->mother = NULL;		//Assign grandmother to NULL
			mom->father = NULL;		//Assign grandfather to NULL
			strcpy(mom->name , mother);
			root->people[root->familySize]->mother = mom;
		}
		if (find_father != -1) {
			root->people[root->familySize]->father = root->people[find_father];		//If father exist, assign him
		}
		else {
			Family *papa = (Family *)malloc(sizeof(Family));	//If not create new father
			papa->mother = NULL;	//Assign grandmother to NULL
			papa->father = NULL;	//Assign grandfather to NULL
			strcpy(papa->name , father);
			root->people[root->familySize]->father = papa;
		}
		root->familySize++;		//Increase the family size
		return ;
	}
}
int addFamilyTree(int familyCount) {
	int flag = 1;
	int input, i;

	Tree *root = (Tree *)malloc(sizeof(Tree));	//Creating the root
	root->familySize = 0;	//Family size is 0 before adding
	root->familyCount = familyCount;	//Assigning the counted family files to family count
	root->people = NULL;

	while (flag)
	{
		printf("1. Add Node\n");
		printf("2. Save Family Tree\n");
		printf("3. Exit\n");
		printf("> ");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
			char name[20], mother[20], father[20];
			int age;
		
			printf("Enter the name of the person: ");	//Getting the information of new person
				scanf("%s", name);
			printf("Enter the age of the person: ");
				scanf("%d", &age);

			if(root->people != NULL) {	//If person is not the root get mother and father also
				printf("Enter the mother's name: ");
					scanf("%s", mother);
				printf("Enter the father's name: ");
					scanf("%s", father);
			}
			addPerson(root, name, age, father, mother);	//addPerson function to add new person
			printf("%s has been added to the family tree successfully...\n" , name);
			break;
		case 2:
			saveFamilyTree(root);	//Save the family tree to the file
			
			FILE *fptr;
			int i = 0 ;
			int counter = 1;
			int familyCount = 0;
			char filename[20];

			while(i < counter) {
				getFileName(filename,i+1);
				fptr = fopen(filename,"r");
				if(fptr != NULL) {
					familyCount++;	//Getting the new count of families
					counter++;	//Counter for infinite loop until fptr cannot open a file
				}
				else {
					break;
				}
				i++;
			}
			root->familyCount = familyCount;	//Assigning new family count
			root->familySize = 0;
			freeTree(root);	//Free the root for new families
			root->people = NULL;
			printf("Family Tree has been saved successfully...\n");
			break;
		case 3:
			printf("Returning to main menu...\n");
			flag = 0;
			break;
		default:
			printf("Invalid input!\n");
		}
		if(flag == 0) {
			break;
		}
	}
	mainMenu(root->familyCount);
}
void saveFamilyTree(Tree *root) {
	FILE *fptr;
	char filename[20];

	getFileName(filename,root->familyCount+1);	//Getting the filename for new family tree

	fptr = fopen(filename, "w");
	if (fptr == NULL) {
		printf("File does not exist!\n");
		return ;
	}
	int i = 0;
	while (i < root->familySize)
	{
		fprintf(fptr, "%s, %d, ", root->people[i]->name, root->people[i]->age);	//Printing the person
		
		if (root->people[i]->mother != NULL) {
			fprintf(fptr, "%s, ", root->people[i]->mother->name);	//If mother exist, print mother
		}
		else {
			fprintf(fptr, "NULL, ");	//Else print NULL
		}

		if(i == (root->familySize - 1)) {	//If it came to the end of the family, dont print new line
			if (root->people[i]->father) {
				fprintf(fptr, "%s", root->people[i]->father->name);	//If father exist, print father
			}
			else {
				fprintf(fptr, "NULL");	//Else print NULL
			}
		}
		else {
			if (root->people[i]->father) {	//Else print new line
				fprintf(fptr, "%s\n", root->people[i]->father->name);
			}
			else {
				fprintf(fptr, "NULL\n");
			}
		}
		i++;
	}
	fclose(fptr);
}
void removeFamilyTree(int familyCount) {
	FILE *fptr;
	FILE *move;
	FILE *temp;
	
	char filename[20];
	char ch;

	printf("Enter the name of txt file: ");	//Getting the family tree that will be removed
		scanf("%s", filename);

	fptr = fopen(filename, "r");
	if (fptr == NULL) {
		printf("File not found ! \n");
		return ;
	}

	remove(filename);	//Remove the family tree

	//Change the names of the family trees
	//If you delete family3.txt then family4.txt will turn to family3.txt
	int i = 0;
	char new_name[20] , change_name[20];
	while(i < familyCount) {
		getFileName(new_name, i+1);	//While filename is note mathced get new filename
		if(strcmp(filename,new_name) == 0) {	//If it is matched, break
			break;
		}
		i++;
	}
	
	while(i < familyCount) {
		getFileName(new_name, i+1);	//Get the filename that will be changed
		move = fopen(new_name, "r");	//Open that file
		if(move != NULL) {	//If it is not NULL
			getFileName(change_name, i);	//Get the other file
			temp = fopen("temp.txt", "w");	//Open a temporary file to copy the file that will be changed
			while(fscanf(move,"%c", &ch) > 0 && ch) {
				fprintf(temp,"%c",ch);
			}
			rename(new_name,change_name);	//Rename the file
		}
		i++;
	}
	remove("temp.txt");
	printf("%s has been removed successfully...\n", filename);
	mainMenu(familyCount);
}
void loadFamilyTree(int familyCount){
	FILE *fptr;
	int i = 0;
	char filename[20];
	int select, flag = 1;
	while(i < familyCount) {
		getFileName(filename,i+1);
		fptr = fopen(filename,"r");
		if(fptr != NULL) {
			printf("%d-%s\n" , i+1 , filename);	//Printing the filenames to choose
		}
		i++;
	}

	Tree *root = (Tree *)malloc(sizeof(Tree));	//Creating the empty root
	root->familySize = 0;
	root->familyCount = 0;
	root->people = NULL;

	printf("Choose a file to continue: ");	
		scanf("%d" , &select);

	getFileName(filename, select);	//Getting the filename according to selection
	readPeople(filename,root);	//Reading the people from that file to the root (Filling the root)

	char name[20], mother[20], father[20];
	int age;

	printf("%s has been selected\n" , filename);
	
	while(flag) {
		printf("Select an operation:\n");
		printf("1-Add new person\n");
		printf("2-Remove a person\n");
		printf("3-Print a person's nuclear family\n");
		printf("4-Search relatives of given person\n");
		printf("5-Return to main menu\n");
		printf("> ");
			scanf("%d" , &select);

		switch(select) {
			case 1:
				printf("Enter the name of the person: ");	//Getting the new person's informations
					scanf("%s", name);
				printf("Enter the age of the person: ");
					scanf("%d", &age);

				if(root->people != NULL) {	//If new person is not the root, get mother and father
					printf("Enter the mother's name: ");
						scanf("%s", mother);
					printf("Enter the father's name: ");
						scanf("%s", father);
				}
				addPerson(root,name,age,father,mother);	//Same function with the inside pf the addFamilyTree
				save(root,filename);	//Saving the new family tree to the file
				break;
			case 2:
				printf("Enter the name of the person: ");	//Getting the person's informations that will be removed
					scanf("%s" , name);
				printf("Enter the mother's name: ");
					scanf("%s", mother);
				printf("Enter the father's name: ");
					scanf("%s", father);
				deletePerson(root,name,father,mother,filename);	//Calling the deletePerson function
			break;
			case 3:
				printf("Enter the name of the person: ");
					scanf("%s" , name);
				nuclearFamily(root,name);	//Printing nuclear family
			break;
			case 4:
				printf("Enter the name of the person: ");
					scanf("%s" , name);
				searchRelative(root, name);	//Searching menu
			break;
			case 5:
			mainMenu(familyCount);
			flag = 0;
			break;
		}
		if(flag == 0) {
			break;
		}
	}
}
void readPeople(const char filename[20],Tree *root) {
	FILE *fptr = fopen(filename, "r");
	int i = 0;
	int size = 0;
	int j;
	char name[20], mother[20], father[20];
	int age;

	//Reading from the file and calling the addPerson function to fill the root
	while(fscanf(fptr ,"%[^,], %d, %[^,], %[^\n]\n", name, &age, mother, father) > 0) {
		addPerson(root,name,age,father,mother);
	}
}
void save(Tree *root, const char filename[20]) {
	//SAME SAVE FUNCTION BUT THIS ONE DOES NOT  GETS THE FILENAME INSIDE
	//IT IS ALREADY GIVEN IN INPUTS
	FILE *fptr;
	fptr = fopen(filename, "w");
	if (fptr == NULL) {
		printf("File does not exist!\n");
		return ;
	}
	int i = 0;
	while (i < root->familySize)
	{
		fprintf(fptr, "%s, %d, ", root->people[i]->name, root->people[i]->age);	
		
		if (root->people[i]->mother != NULL) {
			fprintf(fptr, "%s, ", root->people[i]->mother->name);	
		}
		else {
			fprintf(fptr, "NULL, ");
		}

		if(i == (root->familySize - 1)) {
			if (root->people[i]->father) {
				fprintf(fptr, "%s", root->people[i]->father->name);	
			}
			else {
				fprintf(fptr, "NULL");
			}
		}
		else {
			if (root->people[i]->father) {
				fprintf(fptr, "%s\n", root->people[i]->father->name);
			}
			else {
				fprintf(fptr, "NULL\n");
			}
		}
		i++;
	}
	fclose(fptr);
}
void nuclearFamily(Tree *root, char name[20]) {
	int i = 0 , flag = 0;
	char father[20], mother[20];
	//Printing the mother and  father if they exist
	while(i < root->familySize) {
		if(strcmp(root->people[i]->name, name) == 0) {
			if(root->people[i]->father != NULL) {
				printf("Father: %s\n", root->people[i]->father->name);
				strcpy(father, root->people[i]->father->name);
				flag = 1;
			}
			if(root->people[i]->mother != NULL) {
				printf("Mother: %s\n", root->people[i]->mother->name);
				strcpy(mother, root->people[i]->mother->name);
				flag = 1;
			}
		}
		i++;
	}
	if(flag == 0) {
		//If not
		printf("No father and No mother!\n");
	}
	i = 0;
	flag = 0;
	//Printing the siblings if they exist
	printf("Siblings:");
	while(i < root->familySize) {
			if(root->people[i]->father != NULL) {
				if(strcmp(root->people[i]->name, name) != 0) {
					if(strcmp(root->people[i]->father->name, father) == 0) {
						printf(" %s", root->people[i]->name);
						flag = 1;
					}
				}
			}
		i++;
	}
	if(flag == 0) {
		//If not
		printf("No siblings!");
	}
	printf("\n");

	i = 0;
	flag = 0;
	//Printing the children if they exist
	printf("Children:");
	while(i < root->familySize) {
		if(root->people[i]->father != NULL) {
			if(strcmp(root->people[i]->father->name,name) == 0 ) {
				printf(" %s", root->people[i]->name);
				flag = 1;
			}
		}
		if(root->people[i]->mother != NULL) {
			if(strcmp(root->people[i]->mother->name,name) == 0 ) {
				printf(" %s", root->people[i]->name);
				flag = 1;
			}
		}
		i++;
	}
	if(flag == 0) {
		//If not
		printf("No children!");
	}
	printf("\n");
}
void searchRelative(Tree *root, char name[20]) {
	int select;
	printf("1. Parents\n");
	printf("2. Spouse\n");
	printf("3. Children\n");
	printf("4. Grandparents\n");
	printf("5. Cousins\n");
	printf("Select type of relatives: ");
		scanf("%d" , &select);

	switch(select) {
		case 1:
			searchParents(root,name);
			break;
		case 2:
			searchSpouse(root,name);
			break;
		case 3:
			searchChildren(root,name);
			break;
		case 4:
			searchGrandparents(root,name);
			break;
		case 5:
			searchCousins(root,name);
			break;
	}

}
void searchParents(Tree *root, char name[20]) {
	int i = 0;
	int father_flag = 0, mother_flag = 0;
	while(i < root->familySize) {
		if(strcmp(root->people[i]->name, name) == 0) {	//If names matched
			if(root->people[i]->father != NULL) {	//If father exist
				printf("Father: %s\n", root->people[i]->father->name);
				father_flag = 1;
			}
			if(root->people[i]->mother != NULL) {	//If mother exist
				printf("Mother: %s\n", root->people[i]->mother->name);
				mother_flag = 1;
			}
		}
		i++;
	}
	if(father_flag == 0) {
		printf("No Father");
	}
	if(mother_flag == 0) {
		printf("No mother");
	}
	printf("\n");
}
void searchSpouse(Tree *root, char name[20]) {
	int i = 0;
	int flag = 0;
	while(i < root->familySize) {
		if(root->people[i]->father != NULL && root->people[i]->mother != NULL) {	//If father and mother exist
			if(strcmp(root->people[i]->father->name, name) == 0) {	//Fınd the child
				printf("Spouse: %s", root->people[i]->mother->name);	//Print mother name
				flag = 1;
				break;
			}
			if(strcmp(root->people[i]->mother->name, name) == 0) {	//Fınd the child
				printf("Spouse: %s", root->people[i]->father->name);	//Print father name
				flag = 1;
				break;
			}
		}
		i++;
	}
	if(flag == 0) {
		printf("No Spouse");
	}
	printf("\n");
}
void searchChildren(Tree *root, char name[20]) {
	int i = 0;
	int flag = 0;
	printf("Children:");
	while(i < root->familySize) {
		if(root->people[i]->father != NULL) {	//If father exist
			if(strcmp(root->people[i]->father->name, name) == 0) {	//Find father
				printf(" %s", root->people[i]->name);	//Print the person
				flag = 1;
			}
			
		}
		if(root->people[i]->mother != NULL) {	//If mother exist
			if(strcmp(root->people[i]->mother->name,name) == 0 ) {	//Find mother
				printf(" %s", root->people[i]->name);	//Print the person
				flag = 1;
			}
		}
		i++;
	}
	if(flag == 0) {
		printf("None");
	}
	printf("\n");
}
void searchGrandparents(Tree *root, char name[20]) {
	int i = 0;
	printf("Grandparents: ");
	while(i < root->familySize) {
		if(root->people[i]->father != NULL) {	//If father exist
			if(root->people[i]->father->father != NULL) {	//If grandfather exist
				if(strcmp(name, root->people[i]->name) == 0) {
					printf("%s ", root->people[i]->father->father->name);	//Print grandfather
				}
			}
		}
		if(root->people[i]->father != NULL) {	//If father exist
			if(root->people[i]->father->mother != NULL) {	//If grandmother exist
				if(strcmp(name , root->people[i]->name) == 0) {
					printf("%s ", root->people[i]->father->mother->name);	//Print grandmother
				}
			}
		}
		if(root->people[i]->mother != NULL) {	//If mother exist
			if(root->people[i]->mother->father != NULL) {	//If grandfather exist
				if(strcmp(name, root->people[i]->name) == 0) {
					printf("%s ", root->people[i]->mother->father->name);	//Print grandfather
				}
			}
		}
		if(root->people[i]->mother != NULL) {	//If mother exist
			if(root->people[i]->mother->mother != NULL) {	//If grandmother exist
				if(strcmp(name, root->people[i]->name) == 0) {
					printf("%s ", root->people[i]->mother->mother->name);	//Print grandmother
				}
			}
		}
		i++;
	}
	printf("\n");
}
void searchCousins(Tree *root, char name[20]) {
	int i = 0;
	int flag = 0;
	char gfather[20], gmother[20];
	char father[20], mother[20];
	while(i < root->familySize) {
			if(root->people[i]->father != NULL) {	//If father exist
				if(strcmp(root->people[i]->name, name) == 0) {
					strcpy(father, root->people[i]->father->name);	//Get father
				}
				if(root->people[i]->father->father != NULL) {	//If grandfather exist
					if(strcmp(root->people[i]->name, name) == 0) {
						strcpy(gfather, root->people[i]->father->father->name);		//Get grandfather
					}
				}
			}
			if(root->people[i]->mother != NULL) {	//If mother exist
				if(strcmp(root->people[i]->name, name) == 0) {
					strcpy(mother, root->people[i]->mother->name);	//Get mother
				}
				if(root->people[i]->mother->father!= NULL) {	//If grandfather exist
					if(strcmp(root->people[i]->name, name) == 0) {
						strcpy(gmother, root->people[i]->mother->father->name);	//Get grandfather
					}
				}
			}
		i++;
	}
	i = 0;
	printf("Cousins: ");
	//Father related cousins
	while(i < root->familySize) {
		if(root->people[i]->father != NULL) {	//If father exist
			if(root->people[i]->father->father != NULL) {	//If grandfather exist
				if(strcmp(father, root->people[i]->father->name) != 0) {	//If father names are not matched
					if(strcmp(gfather,root->people[i]->father->father->name) == 0) {	//If grandfather names matched
						printf(" %s", root->people[i]->name);	//Print cousin
						flag = 1;
					}
				}
			}
		}
		i++;
	}

	//Mother related cousins
	i = 0;
	while(i < root->familySize) {
		if(root->people[i]->mother != NULL) {	//If mother exist
			if(root->people[i]->mother->father != NULL) {	//If grandfather exist
				if(strcmp(mother, root->people[i]->mother->name) != 0) {	//If mother names are not matched
					if(strcmp(gmother,root->people[i]->mother->father->name) == 0) {	//If grandfather names matched
						printf(" %s", root->people[i]->name);	//Print cousin
						flag = 1;
					}
				}
			}
		}
		i++;
	}
	if(flag == 0) {
		printf(" None\n");
	}
	printf("\n");

}
void deletePerson(Tree *root, char name[20], char father[20], char mother[20], char filename[20]) {

	Tree *new_root = (Tree *)malloc(sizeof(Tree));	//Create new root for deletion
	new_root->people = NULL;
	new_root->familyCount = 0;
	new_root->familySize = 0;
	
	int size = root->familySize;	//Get the family size before deletion
	int i = 0, j = 0;
	int checkKids = 0;	//This variable holds the child count
	char kids[size][20];	//This char array holds the child names and it's size is equal to family size
	
	while(i < root->familySize) {
		if(root->people[i]->father != NULL && root->people[i]->mother != NULL ) {	//If father and mother exist
			if(strcmp(root->people[i]->father->name, name) == 0 || strcmp(root->people[i]->mother->name, name) == 0) {	//If the name is equal to mother or father name
				strcpy(kids[j], root->people[i]->name);	//Get the child's name
				checkKids++;	//Increase the child count
				j++;
			}
		}
		i++;
	}
	if(checkKids != 0) { //If the person we want to delete has children
		char select;
		printf("Warning! %s has children, removing %s will also remove his/her children.\n", name, name);	//Ask for permission and warn them
		printf("Do you still want to continue? (Y/N)\n");
		printf("> ");
			scanf(" %c", &select);
			if(select == 'Y') {
				readForDelete(new_root,filename,name,checkKids,kids);	//Read from the file and fill the new root
				save(new_root,filename);	//Save the new root to the file
				printf("%s and his/her children have been removed from family tree.\n" , name);
			}
			if(select == 'N'){
				return ;
			}
	}
	else {	//If not delete straight
		readForDelete(new_root,filename,name,checkKids,kids);
		save(new_root,filename);
	}


}
void readForDelete(Tree *root,char filename[20] , char removeName[20],int checkKids,char removeKids[][20]) {

	FILE *fptr = fopen(filename, "r");
	int i = 0;
	char name[20], mother[20], father[20];
	int age;
	int flag = 0;
	i = 0;

	while(fscanf(fptr ,"%[^,], %d, %[^,], %[^\n]\n", name, &age, mother, father) > 0) {	//While reading
		flag = 0;
		i = 0;
		if(strcmp(removeName, name) != 0) {	//If the person's name we want to delete is not equal to the name we read
			if(checkKids == 0) {	//If he/her has no kids
				addPerson(root,name,age,father,mother);	//Add him/her directly to the root
			}
			else {	//If he/her has kids
			while(i < checkKids) {
				if(strcmp(removeKids[i], name) == 0) {	//Compare the names, if the child of the removed person's name
					flag = 1;							//is equal to the name we read do not add that to the new root 
				}
				i++;
			}
			if(flag == 0) {
				addPerson(root,name,age,father,mother);	//If child names are not matched, add them to the new root
			}
			}
		}
	}
}
int getFileName(char *filename, int fileNumber) {
	sprintf(filename, "family%d.txt" , fileNumber);
}
int findPerson(Tree *root, char *name)
{
	int i = 0;
	while (i < root->familySize) {
		if (strcmp(root->people[i]->name, name) == 0) {	//Searching for the name
			return i;
		}
		i++;
	}
	return -1;
}
void freeTree(Tree *root)
{
	int i = 0;
	while (i < root->familySize)
	{
		free(root->people[i]);
		i++;
	}
	free(root->people);
}