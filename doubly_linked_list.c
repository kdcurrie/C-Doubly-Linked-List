//Name: Keaton Currie
//ID: 20402879
/* doubly_linked_list.c
 *
 * Implement a sorted linked list of strings with operations Insert
 * in alphabetical order, Print, Member, Delete, Free_list.
 * The list nodes are doubly linked.
 *
 * Input:    Single character lower case letters to indicate operations,
 *           possibly followed by value needed by operation -- e.g. 'i'
 *           followed by "hello" to insert the string "hello" -- no
 *           double or single quotes.
 *
 * Output:   Results of operations.
 *
 * Compile:  gcc -g -Wall -o doubly_linked_list doubly_linked_list.c
 *
 * Run:      ./doubly_linked_list
 *
 */

/* You may not add any new header file */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Max 99 chars + '\0' */
#define STRING_MAX 100

struct list_node_s {
    char*  data;
    struct list_node_s* prev_p;
    struct list_node_s* next_p;
};

/* Pointers to the head and tail of the list */
struct list_s {
    struct list_node_s* h_p;
    struct list_node_s* t_p;
};

void Insert(struct list_s* list_p, char string[]);
void Print(struct list_s* list_p);
int  Member(struct list_s* list_p, char string[]);
void Delete(struct list_s* list_p, char string[]);
void Free_list(struct list_s* list_p);
char Get_command(void);
void Get_string(char string[]);
void Free_node(struct list_node_s* node_p);
struct list_node_s* Allocate_node(int size);
void Print_node(char title[], struct list_node_s* node_p);


/*-----------------------------------------------------------------*/
int main(void) {
    char          command;
    char          string[STRING_MAX];
    struct list_s list ;

    list.h_p = list.t_p = NULL;
    /* start with empty list */

    command = Get_command();
    while (command != 'q' && command != 'Q') {
        switch (command) {
            case 'i':
            case 'I':
                Get_string(string);
                Insert(&list, string);
                break;
            case 'p':
            case 'P':
                Print(&list);
                break;
            case 'm':
            case 'M':
                Get_string(string);
                if (Member(&list, string))
                    printf("%s is in the list\n", string);
                else
                    printf("%s is not in the list\n", string);
                break;
            case 'd':
            case 'D':
                Get_string(string);
                Delete(&list, string);
                break;
            case 'f':
            case 'F':
                Free_list(&list);
                break;
            default:
                printf("There is no %c command\n", command);
                printf("Please try again\n");
        }
        command = Get_command();
    }
    Free_list(&list);

    return 0;
}  /* main */


/*-----------------------------------------------------------------*/
/* Function:   Allocate_node
 * Purpose:    Allocate storage for a list node
 * Input arg:  size = number of chars needed in data member (including
 *                storage for the terminating null)
 * Return val: Pointer to the new node
 */
struct list_node_s* Allocate_node(int size) {

//TODO: Complete me

    struct list_node_s* listNode = (struct list_node_s*) malloc(sizeof(struct list_node_s)); //allocate the struct and typeCast
    listNode->data = (char*) malloc(size*sizeof(char)); //multiply size of string by size of one char

    return listNode; //return pointer to new node
}  /* Allocate_node */


/*-----------------------------------------------------------------*/
/* Function:   Insert
 * Purpose:    Insert new node in correct alphabetical location in list
 * Input arg:  string = new string to be added to list
 * In/out arg: list_p = pointer to struct storing head and tail ptrs
 * Note:       If the string is already in the list, print a message
 *                and return, leaving list unchanged
 */
void Insert(struct list_s* list_p, char string[]) {

//TODO: Complete me

    if (Member(list_p, string)){// checks if already in list
        printf("This string is already in the list.\n");
        return;
    }
    struct list_node_s* curr_p = list_p-> h_p;
    struct list_node_s* newNode = Allocate_node(strlen(string) + 1); //allocate node for new String node
    if(newNode == NULL){
        printf("Failed to allocate memory for new node.\n");
        exit(-1); //exit program
    }
    //insert string into new node
    strcpy(newNode->data, string);

    if (curr_p == NULL){//if head is null, create new head in case of empty list
        list_p->h_p = newNode; //make list head point to new head
        newNode->next_p = NULL;
    }
    else if(strcmp(curr_p->data, string) > 0){ //in case of inserting at head(new head)
        newNode->next_p = curr_p; //set new node points to old head
        newNode->prev_p = NULL;
        curr_p->prev_p = newNode; //set old head_previous to new head
        list_p->h_p = newNode;//set list head points to new node
    }
    else {
        while(strcmp(curr_p->data, string) <= 0 && curr_p->next_p != NULL){ //if the new node is the same or should come after as the curr_node
            if (strcmp(curr_p->data, string) == 0){ // if node already exists, then free node, and done
                Free_node(newNode);
                return;
            }
            //in this case, the string must be placed in the middle of the curr and next
            if (strcmp(curr_p->next_p->data, string ) > 0){
                newNode->next_p = curr_p->next_p;
                newNode->next_p->prev_p = newNode;//next nodes_prev being set to the new node
                curr_p->next_p = newNode;//curr_nodes next being set to new node
                newNode->prev_p = curr_p; //set new nodes_previous to curr node
                return;
            }

            curr_p = curr_p->next_p;//all else, advance curr pointer
        }
        if(curr_p->next_p == NULL){ //if there's no next, we are at the tail
            curr_p->next_p = newNode; // set tail points to new node
            newNode->prev_p = curr_p; //set new nodes_prev to curr tail
            newNode->next_p = NULL; //set new node_next to null, because tail doesn't point to anything
            list_p->t_p = newNode; //the lists_tail pointer now points to new node

        }
    }

}  /* Insert */

/*-----------------------------------------------------------------*/
/* Function:   Print
 * Purpose:    Print the contents of the nodes in the list
 * Input arg:  list_p = pointers to first and last nodes in list
 *
 * Hint: The implementation of this function (below) shows how
 * to traverse a linked list.
 */
void Print(struct list_s* list_p) {
    struct list_node_s* curr_p = list_p->h_p;

    printf("list = ");

    while (curr_p != NULL) {
        printf("%s ", curr_p->data);
        curr_p = curr_p->next_p;
    }
    printf("\n");
}  /* Print */


/*-----------------------------------------------------------------*/
/* Function:   Member
 * Purpose:    Search list for string
 * Input args: string = string to search for
 *             list_p = pointers to first and last nodes in list
 * Return val: 1, if string is in the list, 0 otherwise
 */
int  Member(struct list_s* list_p, char string[]) {

//TODO: Complete me

    struct list_node_s* curr_p = list_p-> h_p;//pointer to curr node

    while(curr_p != NULL){
        int compareValue = strcmp(curr_p->data, string); //compares the curr node to the string
        if (compareValue == 0){ //if the string and curr are the same (= to each other)
            return 1;
        }
        else if(compareValue > 0){// this means string can't come before curr
            return 0;
        }

        curr_p = curr_p->next_p; //set curr to next
    }

    return 0;
}  /* Member */


/*-----------------------------------------------------------------*/
/* Function:   Free_node
 * Purpose:    Free storage used by a node of the list
 * In/out arg: node_p = pointer to node to be freed
 */
void Free_node(struct list_node_s* node_p) {
    node_p->prev_p = NULL;
    free(node_p->prev_p);
    free(node_p->data);
    free(node_p);
}  /* Free_node */


/*-----------------------------------------------------------------*/
/* Function:   Delete
 * Purpose:    Delete node containing string.
 * Input arg:  string = string to be deleted
 * In/out arg  list_p = pointers to head and tail of list
 * Note:       If the string is in the list, it will be unique.  So
 *             at most one node will be deleted.  If the string isn't
 *             in the list, the function just prints a message and
 *             returns, leaving the list unchanged.
 */
void Delete(struct list_s* list_p, char string[]) {

//TODO: Complete me

    if (!Member(list_p, string)){ //if the string does not exist as a node in the list
        printf("That string does not exist in the list.\n");
        return;
    }
    else { //else the string is in the list, then
        struct list_node_s* curr_p = list_p-> h_p;//set curr node
        if(strcmp(curr_p->data, string) == 0){ //if what we want to delete is the head
            if (curr_p->next_p == NULL){ //if the list is only one string
                list_p->h_p = NULL; //set head equal to null
                Free_node(curr_p); //free memory for first node
                return;
            }
            struct list_node_s* new_head = curr_p->next_p; //if list contains more than one string, must replace head
            Free_node(curr_p); //free old head memory
            new_head->prev_p = NULL; //set new head previous to NULL
            list_p->h_p = new_head; //set list head pointer to new head
            return;
        }
    }
    struct list_node_s* curr_p = list_p-> h_p;//set curr node to go through list

    while(strcmp(curr_p->data, string) != 0 ){ //while we haven't found the string
        curr_p = curr_p->next_p; //keep advancing curr
    }

    if (curr_p->next_p != NULL){//middle of list
        curr_p->next_p->prev_p = curr_p->prev_p;
        curr_p->prev_p->next_p = curr_p->next_p;
        Free_node(curr_p);
    }
    else { //in case of deleting the tail
        curr_p->prev_p->next_p = NULL; //set node_before_tail_next to NULL
//        curr_p->next_p = NULL;
        list_p->t_p = curr_p->prev_p; //set list tail pointer to new tail
        Free_node(curr_p);
    }

}  /* Delete */

/*-----------------------------------------------------------------*/
/* Function:   Free_list
 * Purpose:    Free storage used by list
 * In/out arg: list_p = pointers to head and tail of list
 */
void Free_list(struct list_s* list_p) {

    struct list_node_s* curr_p = list_p-> h_p; //create curr node to iterate through list
    struct list_node_s* next; //create next node

    while (curr_p != NULL)
    {
        next = curr_p->next_p; //while not NULL, iterate to next node, and then free the curr node
        Free_node(curr_p);
        curr_p = next;
    }
        list_p->h_p = NULL; //set head and tail pointers to NULL
        list_p->t_p = NULL;
    }
//}  /* Free_list */


/*-----------------------------------------------------------------*/
/* Function:   Get_command
 * Purpose:    Find and return the next non-whitespace character in
 *             the input stream
 * Return val: The next non-whitespace character in stdin
 */
char Get_command(void) {
    char c;

    printf("Please enter a command (i, d, m, p, f, q):  ");
    /* Put the space before the %c so scanf will skip white space */
    scanf(" %c", &c);
    return c;
}  /* Get_command */

/*-----------------------------------------------------------------*/
/* Function:   Get_string
 * Purpose:    Read the next string in stdin (delimited by whitespace)
 * Out arg:    string = next string in stdin
 */
void Get_string(char string[]) {

    printf("Please enter a string:  ");
    scanf("%s", string);
}  /* Get_string */


/*-----------------------------------------------------------------*/
/* Function:  Print_node
 * Purpose:   Print the data member in a node or NULL if the
 *            pointer is NULL
 * In args:   title:  name of the node
 *            node_p:  pointer to node
 */
void Print_node(char title[], struct list_node_s* node_p) {
    printf("%s = ", title);
    if (node_p != NULL)
        printf("%s\n", node_p->data);
    else
        printf("NULL\n");
}  /* Print_node */

