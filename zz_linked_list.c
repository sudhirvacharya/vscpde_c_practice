#include <stdio.h>
#include <stdlib.h>
/*
start adress is  ptr= malloc()
end adress       node->next
new_node
   |
   v
+-------+-------+
| data  | next  |
|  20   | NULL  |
+-------+-------+

*/

// head --> [data | next] --> [data | next] --> NULL
typedef struct node
{
    int data;
    struct node *next;
}node;

//double pointer
void insertend(node **head, int data)
{
    // Allocate memory for new node
    node *new_node= malloc(sizeof(node));// new_node stores address of allocated node
    new_node->data=data;
    new_node->next=NULL;

    // If list is empty, new node becomes the head
    //its compared same as how declared in main
    if(*head == NULL)
        {
                *head=new_node;///*head=NULL
                        return;
        }
                 
      // Use a temporary pointer to traverse the list
    node *tmp=*head; // don't move *head itself!
    while(tmp->next != NULL)// move until last node
        tmp=tmp->next;

    // Attach new node at the end
    //here tmp->next is NULL
    //new_node->next is NULL so we passing whole struct adress
    tmp->next=new_node;

}

void print_list(node *head)
{
    node *tempp = head;
    while(tempp !=NULL)
    {
        printf("%d-->", tempp->data);
        tempp=tempp->next;//this hsolb be place here , this soemthing i++;
    }
    printf("NULL \n");


}

//double pointer explaination
//0x100  [int x = 2]          →  value lives here
//0x101  [int *ptr = 0x100]   →  *ptr  == 2   (single pointer: holds address of int)
//0x102  [int **pptr = 0x101] →  **pptr == 2  (double pointer: holds address of pointer)

/// Delete a node by value using double pointer
// head: pointer to the head pointer (so we can change the head if needed)
// data: the value we want to delete from the list
void delete_node(node **head, int data)
{
    node *curr = *head;  // curr starts at the first node
    node *prev = NULL;   // prev tracks the node BEFORE curr (starts as nothing)

    // Walk through the list one node at a time
    while (curr != NULL)  // stop when we reach the end of the list
    {
        if (curr->data == data)  // found the node we want to delete!
        {
            // Special case: the node to delete is the very first node (head)
            // We need to move the head forward to the next node
            if (prev == NULL)
            {
                *head = curr->next;  // head now points to the 2nd node
            }
            else
            {
                // Normal case: skip over curr by connecting prev directly to curr's next
                // Before: prev -> curr -> curr->next
                // After:  prev -> curr->next
                prev->next = curr->next;
            }

            free(curr);  // release the memory of the deleted node
            return;      // job done, exit the function
        }

        // Not found yet — move both pointers one step forward
        prev = curr;        // prev catches up to curr
        curr = curr->next;  // curr moves to the next node
    }

    // If we reach here, the value was not found in the list
    // (the function just exits quietly — no deletion happened)
}
int main()
{
    node *head=NULL;
    insertend(&head, 10);
    insertend(&head, 20);
    insertend(&head, 30);
    print_list(head);

    delete_node(&head, 20);
    printf("After delete: ");
    print_list(head);
    return 0;
}