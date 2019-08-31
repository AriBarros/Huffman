#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int item;
	struct node* next;
} node;

node* create_linked_list()
{
	return NULL; 
}

int is_empty(node *head)
{
	return (head == NULL);
}

node* add_list(node *head, int item)
{
	node *new_node = (node*) malloc(sizeof(node));
	new_node->item = item;
	new_node->next = head;
	return new_node;
}

int search_list(node *head, int item)
{
	int cont = 1;
	
	while(head != NULL)
	{
		if(head->item == item)
		{
			return cont;
		}
		cont++;
		head = head->next;
	}
	return -1;
}