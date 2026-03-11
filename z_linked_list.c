#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

void insertend(node **head, int data)
{
    node *new_node= malloc(sizeof(node));
    new_node->data=data;
    new_node->next=NULL;

    if(*head == NULL)
    {
        *head=new_node;
        return;
    }

    node *tmp=*head;
    while(tmp->next != NULL)
        tmp=tmp->next;

    tmp->next=new_node;

}

void print_list(node *head)
{
    node *tempp = head;
    while(tempp !=NULL)
    {
        printf("%d-->", tempp->data);
        tempp=tempp->next;
    }
    printf("NULL \n");


}

// Delete a node by value using double pointer
void delete_node(node **head, int data)
{
node *curr = *head;
    node *prev = NULL;

    // Traverse the list
    while (curr != NULL)
    {
        if (curr->data == data)
        {
            // If deleting the head node
            if (prev == NULL)
            {
                *head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
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