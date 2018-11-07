// passenger.c -- implements a linked list of TTC subway passengers
// Farhang Tarlan, Winter 2013

#include "ttc.h"

struct passenger* make_passenger()
{
	// creates a new passenger node using malloc. Sets the waiting time to 0 and the next to to NULL
	struct passenger* new_passenger = (struct passenger*) malloc(sizeof(struct passenger*));
	new_passenger -> waiting = 0;
	new_passenger -> next = NULL;
	return new_passenger;
}

void insert_passenger_after(struct passenger *node, struct passenger *new_node)
{
	// inserts a passenger node (new_node) after an already existing passenger node (node) in the linked list
	assert (node);
	assert (new_node);
	
	struct passenger* temp = node -> next;
	node -> next = new_node;
	new_node -> next = temp;
}


void print_passenger(struct passenger *node)
{
	// prints a single passenger node
	if (node == NULL)
		printf("NULL\n");
	
	else
	{
		printf("%d\n", node -> waiting);	
	}
	
}

void print_passenger_list(struct passenger *first)
{
	// prints the entire passenger linked list pointed to by first
	struct passenger* curr = first;
	printf("Waiting times: \n");
	
	while (curr)
	{
		print_passenger(curr);
		curr = curr -> next;
	}
}

void remove_first_passenger(struct passenger **node)
{
	// removes the first node in the linked list and updates the head of the linked list.
	// frees the memory associated with that node. 
	assert (*node != NULL);
	
	struct passenger* temp = *node;
	(*node) = (*node) -> next;
	free(temp);
}

void clear_passenger_list(struct passenger **first)
{
	// frees the memory of all the nodes in the linked list pointed to by first
	while (*first)
	{
		remove_first_passenger(first);
	}
	
	*first = NULL;
}

void increment_passenger_list(struct passenger *first)
{
	// increments the waiting time of all the passengers in the linked list pointed to by first by one minute
	struct passenger* curr = first; 
	
	while (curr)
	{
		curr -> waiting += 1;
		curr = curr -> next;
	}
}

double average_passenger_list(struct passenger *first)
{
	// returns the average waiting time of the passengers in the linked list pointed to by first
	if (first == NULL)
		return -1;
	
	int num = 0;
	double avg = 0.0;
	struct passenger* curr = first;
	
	while (curr)
	{
		num += 1;
		avg += curr -> waiting;
		curr = curr -> next;
	}
	
	return avg/num;
}

int num_passengers(struct passenger *first)
{
	// returns the number of passenger nodes in the linked list pointed to by first
	int num = 0;
	struct passenger* curr = first;
	
	while (curr)
	{
		num += 1;
		curr = curr -> next;
	}
	
	return num;
}
