// station.c -- simulates a doubly-linked list of TTC stations
// Farhang Tarlan, winter 2013
#include "ttc.h"


struct station* make_station(char *name, int pos)
{
	// Creates a new station node in our doubly-linked list, setting its name and position to name and pos.
	// The new node is unlinked (prev and next are both NULL).
	// PRE: none
	// POST: none

	struct station *new_node = (struct station*) malloc(sizeof(struct station));
	new_node->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
	strcpy(new_node->name, name);

	new_node->pos = pos;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->passengers = NULL;

	return new_node;
}


int passengers_at_station(struct station *curr_station)
{
	// Number of passengers waiting at a given station, curr_station. If station == NULL, returns 0.
	// PRE: none
	// POST: none

	if(curr_station && curr_station->passengers)
	{
		return num_passengers(curr_station->passengers);
	}

	return 0;
}


void print_station(struct station *current)
{
	// Prints a single station. If current == NULL, prints "No station. \n".
	// PRE: none.
	// POST: none
	if(!current)
	{
		printf("No station. \n");
	}
	else
	{
		if(current->prev)
		{
			printf("%13s -> ", current->prev->name);
		}
		else
		{
			printf("                 ");
		}

		printf("%s (%d)", current->name, num_passengers(current->passengers) );
		if(current->next)
		{
			printf("-> %-13s \n", current->next->name);
		}
		else
		{
			printf("\n");
		}
	}
}


void print_stations(struct station *first)
{
	// Prints all stations in a linked list
	// PRE: none
	// POST: none

	printf("\nThe stations: \n");
	struct station *curr = first;
	while(curr)
	{
		print_station(curr);
		curr = curr->next;
	}
}


void insert_station_after(struct station *node, struct station *new_node)
{
	// inserts a new station new_node after node, linking node into the doubly-linked list.
	new_node -> next = node -> next;
	new_node -> prev = node;
	node -> next = new_node;
	if (new_node -> next)
		(new_node -> next) -> prev = new_node;
}


struct station* read_stations()
{	
	// reads the file bloor_line.txt, converts each line into a doubly-linked list of stations
	char* name;
	int pos, i = 0;
	struct station* prev = NULL;
	struct station* new_station = NULL;
	struct station* first;
	FILE* fop = fopen("bloor_line.txt", "r");
	
	while (fscanf(fop, "%s %d\n", name, &pos) != EOF)
	{
		if (i == 0)
		{
			new_station = make_station(name, pos);
			first = new_station;
		}
		
		else
		{
			prev = new_station;
			new_station = make_station(name, pos);
			insert_station_after(prev, new_station);
		}
				
		i += 1;
	}
	
	fclose(fop);
	return first; 
}


void add_passenger(struct station *curr_station)
{
	// adds a new passenger to the station given by curr_station
	struct passenger* new_passenger = make_passenger();
	
	new_passenger -> next = curr_station -> passengers;
	curr_station -> passengers = new_passenger;
}
		
		
void add_n_passengers(struct station *curr_station, int n)
{
	// adds n passengers to the station given by curr_station
	int i;
	
	for (i = 0; i < n; i += 1)
	{
		add_passenger(curr_station);
	}
}


int total_passengers(struct station *first)
{
	// returns the total number of passengers at all stations in the linked list pointed to by first
	struct station* curr;
	struct passenger* pass;
	int num = 0;
	
	for (curr = first; curr != NULL; curr = curr -> next)
	{
		for (pass = curr -> passengers; pass != NULL; pass = pass -> next)
		{
			num += 1;
		}
	}
	
	return num;
}


double average_wait_time(struct station *first)
{
	// returns the average wait time for all the passengers at all stations in the linked list pointed to by first
	int num = 0;
	double wait = 0.0;
	struct station* curr;
	struct passenger* pass;
	
	for (curr = first; curr != NULL; curr = curr -> next)
	{
		for (pass = curr -> passengers; pass != NULL; pass = pass -> next)
		{
			num += 1;
			wait += pass -> waiting;
		}
	}
	return (wait / num);
}

struct station* get_station_at_pos(int position, struct station *first)
{
	// returns the station located at the position given by position, NULL if a station is not found.
	if (first -> pos == position)
		return first;
	
	return get_station_at_pos(position, first -> next);
}
    

void remove_all_stations(struct station **first)
{
	// removes and frees the memory of all the stations in the linked list beginning with first.
	struct station* curr_station = *first;
    struct passenger* curr_passenger;

    // looping through stations:
    while (curr_station -> next != NULL)
    {
        free(curr_station -> name);

        // freeing the passenger list by calling clear_passenger_list
        curr_passenger = curr_station -> passengers;
        clear_passenger_list(&curr_passenger);

        // freeing the statoin itself
        curr_station = curr_station -> next;
        free(*first);
        *first = curr_station;
    }
}

