#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int queueofRollno[501]; //! queue of deleted Enrollment numbers.
int position=0; //! points the last element of the queue.


//! for making a new node .
struct Node {

	int roll_no;  
    char Name[50];
    char dob[20];
    char address[100];
    long long int phone_no;
    struct Node *prev;
    struct Node *next;   
};

typedef struct Node* Node;   //! define the datatype of a node.
Node start = NULL;   //! initilise the head of the circular linked list.

 //! To insert a new node in the circular linked list.
void insert (int roll_no, char Name[], char dob[],char address[] , long long int phone_no);

//! Returns the pointer pointing to the node having given Enrollment number.
Node searchByRollno (int roll_no);

//! store the deleted enrollment number in the queue.
void storeUnusedRollNo(int roll_no);

//! function to delete the node of given Enrollment number.
void Delete(int roll_no);

//! Modify the information of a student.
void Modify( int roll_no, int choice , char value[]);

//!Swap two given numbers.
void Swap(Node node1 , Node node2);

//! sort the circular linked list by name.
void sortByName();

//! sort the circular linked list by Enrollment number. 
void sortByRollNo();

//!print the whole list.
void printList();

 //! To insert a new node in the circular linked list.
void insert (int roll_no, char Name[], char dob[],char address[] , long long int phone_no){

	Node new_node = (Node)malloc (sizeof ( struct Node));
	
	new_node -> roll_no = roll_no;
	strcpy(new_node -> Name , Name);
	strcpy(new_node -> dob , dob);
	strcpy(new_node -> address , address);
	new_node -> phone_no = phone_no;

	if (start == NULL){
		new_node -> prev = new_node;
		new_node -> next = new_node;
		start = new_node;
	}
	else {

		start -> prev -> next = new_node;
		new_node -> prev = start -> prev;
		new_node -> next = start;
		start -> prev = new_node;

	}
} 
//! Returns the pointer pointing to the node having given Enrollment number.
Node searchByRollno (int roll_no){
   
   int t = 1;
   Node temp = (Node)malloc (sizeof(struct Node));
   temp = start;
   while(t || (temp != start)){
   	t = 0 ;
   	if (temp -> roll_no == roll_no){
   		return temp;
   	}
   	temp = temp -> next;
   }
   return NULL;
}
//! store the deleted enrollment number in the queue.
void storeUnusedRollNo(int roll_no){

	if (position == 500)
    {
    	printf("storage full !\n");
        return;
    }
    if (start != NULL){
    queueofRollno[position] = roll_no;
    position++;
   }
}
//! function to delete the node of given Enrollment number.
void Delete(int roll_no){
	if ( start == NULL ){
		printf("No  element is present in the list\n");
		return;
	}

   Node temp = searchByRollno(roll_no);
   if (temp ==NULL) {
   	printf("Enrollment number not found !\n");
   	return;
   }
   if (temp == start){
   	 start -> prev -> next = temp -> next;
     start = temp -> next;
     start -> prev = temp -> prev;
     printf("Enrollment number %d successfully deleted ! \n", roll_no);
     return;
   }
   temp -> prev -> next = temp -> next;
   temp -> next -> prev = temp -> prev;
   free(temp);
   printf("Enrollment number %d successfully deleted ! \n",roll_no);

}
//! Modify the information of a student.
void Modify( int roll_no, int choice , char value[]){

   Node temp = searchByRollno(roll_no);

   if ( temp == NULL) 
   	{ 
   		printf("Enrollment number not found\n"); 
   		return; 
   	}
    
    if (choice == 1) 
    	strcpy( temp -> Name , value);
    else if ( choice == 2) 
    	strcpy( temp -> dob , value);
    else if ( choice == 3) 
    	strcpy( temp -> address , value);
    else if ( choice == 4) 
    	temp -> phone_no = atoll(value);
    else 
    	{
    		printf("Read the instructions carefully !\n");
    		return;
    	}

    printf("Given instruction is successfully Updated!\n");
}
//!Swap two given numbers.
void Swap(Node node1 , Node node2){
	
	char Name[50], dob[20], address[200];
	int roll_no; long long int phone_no;
    strcpy(Name, node1->Name);
    strcpy(address, node1->address);
    strcpy(dob, node1->dob);
    phone_no = node1->phone_no;
    roll_no = node1->roll_no;

    strcpy(node1->Name, node2->Name);
    strcpy(node1->address, node2->address);
    strcpy(node1->dob, node2->dob);
    node1->phone_no = node2->phone_no;
    node1-> roll_no = node2->roll_no;

    strcpy(node2->Name, Name);
    strcpy(node2->address, address);
    strcpy(node2->dob, dob);
    node2->phone_no = phone_no;
    node2->roll_no = roll_no; 

}
//! sort the circular linked list by name.
void sortByName(){

	Node temp1;
    Node temp2;

    if(start == NULL) 
    	printf("No element in the list !");
    temp1 = start;
    int roll_no1; int roll_no2;
    for(temp1=start;temp1->next!=start;temp1=temp1->next)
    {
    	for(temp2=temp1->next;temp2!=start;temp2=temp2->next)
    	{
    		if(strcmp(temp1->Name,temp2->Name)>0)
    		{
    			Swap(temp1,temp2);
    		}
    	}
    }
    printf(" Sorted successfully !\n");
}
//! sort the circular linked list by Enrollment number. 
void sortByRollNo(){

	Node temp1;
    Node temp2;

    if(start == NULL) 
    	printf("No element in the list !");
    temp1 = start;
    int roll_no1; int roll_no2;
    for(temp1=start;temp1->next!=start;temp1=temp1->next)
    {
    	for(temp2=temp1->next;temp2!=start;temp2=temp2->next)
    	{
    		if(temp1->roll_no > temp2->roll_no)
    		{
    			Swap(temp1,temp2);
    		}
    	}
    }
    printf(" Sorted successfully !\n");
}
//!print the whole list.
void printList() {

    Node temp = (Node)malloc(sizeof(struct Node));
    temp = start;    
    int p = 1;
    while(temp != start || p) {
        p = 0;
        printf("Name : %s \n", temp->Name);
        printf("Enrollment no. : %d\n", temp->roll_no);
        printf("Date of Birth : %s \n", temp->dob);
        printf("Contact No. : %lld \n", temp -> phone_no );
        printf("Address : %s \n\n", temp -> address);
        temp = temp->next;
    }
} 

int main() {


     int ROLL_NO = 101 ;
    while(1) 
    {
     
        printf("%s", "Enter 1 to insert information from file \n");
        printf("%s", "Enter 2 to modify the information\n");
        printf("%s", "Enter 3 to delete some information\n");
        printf("%s", "Enter 4 to sort the students name lexicographically \n");
        printf("%s", "Enter 5 to print the list \n");
        printf("%s", "Enter 6 to exit the program...\n");

        int choice;
        scanf("%d", &choice);
        int i = 1;

        switch(choice) {
           //! case for insert the information from file.
            case 1: {                  
                char Name[20], dob[20], address[200];
                long long int phone_no;
                
                char filename[31] = "StudentData.csv";
                char buff_string[1024];
        
                FILE *file = fopen(filename, "r");
                fgets(buff_string, sizeof(buff_string), file); 
                int num;
                printf("Enter the student number whose data you want to insert\n");
                scanf("%d",&num);
                	while( i<=num){
                    fgets(buff_string, sizeof(buff_string), file);
                    char *data = strtok(buff_string, ","); 
                    data = strtok(NULL, ",");
                    strcpy(Name, data);
                    data = strtok(NULL, ",");
                    strcpy(dob, data);
                    data = strtok(NULL, "\"");  
                    strcpy(address, data);
                    data = strtok(NULL, ",");
                    phone_no = atoll(data);
                    i++;
                    }
                    if(position == 0) { 
                        insert(ROLL_NO, Name, dob, address, phone_no);
                        ROLL_NO++;
                    }
                    else {
                        int enroll = queueofRollno[0];
                        insert(enroll , Name, dob, address, phone_no);
                        for (int i=0; i< position -1 ;i++)
                        	queueofRollno[i] = queueofRollno[i+1];
                        position--;

                        sortByRollNo();
                    }
                printf("Information successfully inserted in the list !\n");
                break;
            }
            //! case to modify the information of a student.
            case 2 : 
            {
                char val[200];
                int roll_no, choice;

                printf("%s\n", "Enter 1 to change the Name");
                printf("%s\n", "Enter 2 to change the Date of Birth");
                printf("%s\n", "Enter 3 to change the Address");
                printf("%s\n", "Enter 4 to change the Phone Number");
                scanf("%d", &choice);

                printf("%s\n", "Enter Roll number: ");
                scanf("%d", &roll_no);
                
                printf("%s\n", "Enter new value: ");
                scanf("%s", val);
                Modify(roll_no, choice, val);
                break;
            }
            //! case to delete a node .
            case 3 : {
                int roll_no;
                printf("%s\n", "Enter Roll number: ");
                scanf("%d", &roll_no);
                storeUnusedRollNo(roll_no);
                Delete(roll_no);
                break;
            }
            //! case to sort the students name lexicographically
            case 4 : {
                sortByName();
                break;
            }    
            //! case to print the circular linked list.
            case 5 : {
                printList();
                break;
            }
            //! case to exit the program.
            case 6 : {
                return 0;
            }

            default: {
                printf("Read the instructions carefully! \n");
            }
        }
    }            
	return 0;
}

