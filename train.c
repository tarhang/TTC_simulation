// train.c -- implements a linked list of TTC subway trains
// Farhang Tarlan, Winter 2013

#include "ttc.h"

struct train* make_train(int iden, int position)
{
	// creates a new train node with the given id (iden) and position on the track (position)
	struct train* new_train = (struct train*) malloc(sizeof(struct train*));
	new_train -> id = iden;
	new_train -> pos = position;
	new_train -> next = NULL;
	return new_train;
}

int contains_train_id(struct train *first, int value)
{	
	// returns 1 if the linked list pointed to by first has a train node with an id == value. 0 otherwise
	struct train* curr;
	for (curr = first; curr != NULL; curr = curr -> next)
	{
		if (curr -> id == value)
			return 1;
	}
	
	return 0;
}

int train_at_position(struct train *first, int pos)
{
	// Returns 1 if there exists a train at position pos (given to students)
	struct train *curr = first;
	int contains_pos = 0;
	while(curr)
	{
		if(curr->pos == pos)
		{
			return 1;
		}
		curr = curr->next;
	}
	return contains_pos;
}

void prepend_train(struct train **first, struct train *new_node)
{
	// inserts a new train node (new_node) at the beginning of the linked list pointed to by first
	assert (*first);
	assert (new_node);
	
	struct train* curr = *first;
	
	while (curr)
	{
		assert (new_node -> pos < curr -> pos);
		curr = curr -> next;
	}
	
	assert (contains_train_id(*first, new_node -> id) == 0);
	
	new_node -> next = *first;
	*first = new_node;
}

void print_train(struct train *node)
{
	// This method is provided to students.
	// Prints a single train, and what it points to (if it points to another train)
	assert(node);
	printf("Train %d at %d", node->id, node->pos);
	if(node->next)
	{
		printf("; next is %d at %d", node->next->id, node->next->pos);
	}
	printf("\n");
}

void print_trains(struct train *first)
{
	struct train* curr = first;
	
	printf("---------- The trains ---------- \n");
	
	while (curr)
	{
		print_train(curr);
		curr = curr -> next;
	}
}

int can_advance(struct train *current, int passengers_on_platform)
{
	// returns whether a train can safely advance 
	// for a train to advance, the next train on the track must be more than one position unit ahead on the track, 
	// and there must be no passengers on the platform.
	assert (current);
	assert (passengers_on_platform >= 0);
	
	int	can = 0;
	
	if (current -> next -> pos - current -> pos > 1)
	{
		if (passengers_on_platform == 0)
		{
			can = 1;	
		}
	}
	
	return can; 
}

void advance_train(struct train *current, int passengers_on_platform)
{
	// increases a train's position if and only if the train can advance
	if (can_advance(current, passengers_on_platform) == 1)
		current -> pos += 1;
}

int num_trains(struct train *first)
{
	// returns the number of train nodes in the linked list pointed to by first. Returns 0 if first is NULL
	int num = 0;
	struct train* curr = first;
	
	while (curr)
	{
		num += 1;
		curr = curr -> next;
	}
	
	return num;
}

double avg_train_dist(struct train *first)
{
	// returns the average distance between trains. Returns 0 if first is NULL. Assumes a train is 1 km long 
	if (!first)
		return 0;
		
	struct train* curr = first;
	double dist = 0.0;
	int num = 0;
	
	while (curr -> next)
	{
		dist += (curr -> next -> pos - curr -> pos - 1);
		num += 1;
		curr = curr -> next;
	}
	
	return dist/num;
}


void remove_train_after(struct train *node)
{
	// removes the node directly after the given train node (node)
	// this preserves the rest of the linked list and frees the memory of the removed node.
	assert (node);
	
	struct train* temp = node -> next;
	node -> next = temp -> next;
	free(temp);
}

void clear_all_trains(struct train **first)
{
	// removes all train nodes from the linked list that *first points to, freeing their memory.
	while ((*first) -> next)
	{
		remove_train_after(*first);
	}
	
	*first = NULL;
}
