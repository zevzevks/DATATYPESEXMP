#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <config.h>


#define MAT_LENGTH 2415			//		based on total number of words


/****************************************************************************
 * Function Name  : trim
 * Inputs         : char pointer of words
 * Outputs        : returns string
 * Returns        : 1
 * Description    : To get rid off blanks of given words used while reading 
 					txt file in read_words_from_file function
 ****************************************************************************/
char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if( str + len - 1 != endp )
            *(endp + 1) = '\0';
    else if( frontp != str &&  endp == frontp )
            *str = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }


    return str;
}

/****************************************************************************
 * Function Name  : read_words_from_file
 * Inputs         : words : Struct array
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : This function fills the input of words matrix based on kelimeler.txt
 ****************************************************************************/
void read_words_from_file(word *pwords)
{

	for (int i = 0; i < MAT_LENGTH; ++i)
	{
		pwords[i].index = i;
	}

	FILE * fp_kelimeler = NULL;
	int MAX_LEN = 10+1;		//parameter needed by fgets function to set better input min = 10 rec. (strlen+NULL+2)
	int counter = 0;		//holds count of words that have been read
	char line[10];			//holds each line in txt

	fp_kelimeler = fopen("kelime.txt","r");

	if(fp_kelimeler != NULL)
	{
		while (fgets ( line, MAX_LEN, fp_kelimeler ) != NULL ) /* read a line */
		{
			strcpy(pwords[counter].value,trim(line));
			counter++;
		}
	}	
	else	printf("ERROR -> Kelimeler.txt not found -> %d %s\n",__LINE__,__FUNCTION__ );


	if(counter == MAT_LENGTH ) printf("All Words have been successfully read\n");
	else printf("There must be a mistake maybe? \n");
}


/****************************************************************************
 * Function Name  : find_exact_word_index
 * Inputs         : pdest  : word to search for
 					pwords : total word set of ours 
 * Outputs        : Currently None
 * Returns        : return_value :  index of that word
 * Description    : to reach certain element of word struct , to fetch index
 ****************************************************************************/
int find_exact_word_index(char *pdest,word *pwords)
{
	int return_value = 0;
	for (int i = 0; i < MAT_LENGTH; ++i)
	{
		if(strcmp(pwords[i].value,pdest) == 0)
		{
			return return_value = i;
			// return return_value;
		}
	}
	return return_value = -1;
	// return return_value;
}


/****************************************************************************
 * Function Name  : display_words
 * Inputs         : struct array
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : To print entire word set based on kelimeler.txt
 ****************************************************************************/
void display_words(word *pwords)
{
	for(int i=0;i<MAT_LENGTH;i++)
	{
			printf("Struct Index : %d | Struct Value : %s\n",pwords[i].index,pwords[i].value);
	}
}

/****************************************************************************
 * Function Name  : is_adjacent
 * Inputs         : source and dest char pointers 
 * Outputs        : Currently None
 * Returns        : 1 when success / 0 when failure
 * Description    : This function checks if adjacency occurs between 
 					two given words returns integer, to fill graph
 					4 chars must be matching to adjacency condition
 ****************************************************************************/
int is_adjacent(char *psource,char *pdest)
{
	int return_value = 0;
	int adjc_counter = 0;
	for (int i = 0; i < 5; ++i)
	{
		if ( psource[i] == pdest[i] )
		{
			adjc_counter++;
		}
	}

	// PROVE - PROSE -> TO MEET CONDITIONS EXACTLY 4 CHARS MATCH AT SAME INDEX

	if(adjc_counter == 4)
	{
		return_value = 1;
	}

return return_value;
}

/****************************************************************************
 * Function Name  : find_pattern_between_two_words
 * Inputs         : ppAdj :Pointer-Pointer to our graph
 					pwords:our word struct filled with kelimeler.txt
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : BFS TO FIND ADJCACENCY BETWEEN CONSOLE GIVEN 2 WORDS 
 ****************************************************************************/
int is_searched_before(int pindex,int *p_search_array, int last)
{
	for (int i = 0; i <= last; ++i)
 	{
 		if(p_search_array[i] == pindex) return 1;
 	}
 return 0;
}


/****************************************************************************
 * Function Name  : print_search_array
 * Inputs         : ppAdj :
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : Print our way to reach destination
 ****************************************************************************/
 void print_search_array(int *p_search_array,word *pwords,int last)
 {
 	for (int i = 0; i < last; ++i)
 	{
 		printf("array item 		:		%s\n",pwords[p_search_array[i]].value );
 	}
 }

/****************************************************************************
 * Function Name  : find_adjacents_add_to_queue
 * Inputs         : ppAdj :Pointer-Pointer to our adjcacency graph
 					psource : we give index of that node
 					q : our queue
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : based on given psource int, we fetch adjacents of that node
 					and put them into the que if it is not full
 ****************************************************************************/
void find_adjacents_add_to_queue(int ***p_adj_mat,int psource,queue* q)
{
	printf("FINDING ADJACENTS\n");

	for (int i = 0; i < MAT_LENGTH; ++i)
	{
		if((*p_adj_mat)[psource][i]) 
		{
				enqueue(q,i);		
		}
	}
}


/****************************************************************************
 * Function Name  : breadth_first_search
 * Inputs         : pwords 		: struct pointer to our word set
 					p_adj_mat   : int pointer to our adjacacency graph
 					psource 	: char pointer to source string that given in console
 					pdest 		: char pointer to dest string that given in console
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : BFS algorith to reach destination , first input (psource) puts into
 					queue , then its adjacents found and putted into queue similarly then
 					we pop the element from queue , we do this until we find our dest,
 					or given queue mem stack is full
 ****************************************************************************/
void breadth_first_search(word *pwords, int ***p_adj_mat, char *psource, char *pdest)
{
	printf("\nIN BFS FUNCTION\n");

	int search_array[100];
	int found = 0;
	int temp_index = 0;
	int cycle_index = 0;

	queue *q = createQueue();	
	int searching_index = find_exact_word_index(pdest,pwords);
	int first_index = find_exact_word_index(psource,pwords);
	
	printf("first_index->%d ,searching_index ->%d\n",first_index,searching_index );
	enqueue(q,first_index);
	
	// printf("isEmpty->%d found->%d isFull->%d\n", !isEmpty(q) ,!found ,!isFull(q));

	while(!isEmpty(q) && !found && !isFull(q))
	{		
		temp_index = q->items[q->front];
		search_array[cycle_index] = temp_index;
		if(temp_index == searching_index)
		{
			break;
		}
		else if (!is_searched_before(searching_index,search_array,cycle_index)) 
		{
		find_adjacents_add_to_queue(p_adj_mat,q->items[q->front],q);
		dequeue(q);
		cycle_index++;
		} 
		else
		{
			printf("%d HAS ADDED TO QUEUE BEFORE\n",searching_index );
		}
	}

// if(isFull(q)) printf("QUEUE IS FULL EXITING\n");
// else print_search_array(search_array,pwords,cycle_index);
}


/****************************************************************************
 * Function Name  : find_pattern_between_two_words
 * Inputs         : ppAdj :Pointer-Pointer to our graph
 					pwords:our word struct filled with kelimeler.txt
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : BFS TO FIND ADJCACENCY BETWEEN CONSOLE GIVEN 2 WORDS 
 ****************************************************************************/
void find_pattern_between_two_words(word *pwords,int ***p_adj_mat)
{
	char source[5+1],dest[5+1];
	printf("To look if there is any link given 2 strings\n");
	printf("Waiting for 1 st word\n");
	scanf("%s",source);
	printf("Waiting for 2 nd word\n");
	scanf("%s",dest);
	breadth_first_search(pwords,p_adj_mat,source,dest);
}

/****************************************************************************
 * Function Name  : display_adjacency_matrix
 * Inputs         : word struck array
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : Prints out adjacency graph
 					How am i suppose to print 2415x2415 
 ****************************************************************************/
void display_adjacency_matrix(int ***p_adj_mat)
{
	unsigned short int number_of_ones = 0;

	printf("DISPLAYING ADJ MATRIX\n");

	for (int i = 0; i < MAT_LENGTH; ++i)
	{
		for (int j = 0; j < MAT_LENGTH; ++j)
		{
			printf("%d ",(*p_adj_mat)[i][j] );

			if ((*p_adj_mat)[i][j] == 1)
				number_of_ones++;

		}
		printf("\n");
	}

printf("\n Number of ones in matrix = %d",number_of_ones);
printf("\nYou should be seeing some 1's in massive 0's\n");
}

/****************************************************************************
 * Function Name  : init_adjacency_matrix
 * Inputs         : adj graph
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : to init matrix
 ****************************************************************************/
void init_adjacency_matrix(int ***p_adj_mat)
{
	for (int i = 0; i < MAT_LENGTH; ++i)
		for (int j = 0; j < MAT_LENGTH; ++j)
			(*p_adj_mat)[i][j] = 0;
}

/****************************************************************************
 * Function Name  : fill_adjacency_matrix
 * Inputs         : word struck array,p_adj_mat to fill it in here
 * Outputs        : Currently None
 * Returns        : Currently None
 * Description    : This function fills adjacency matrix based on words 
 					adjaceceny matches that output feedback from is_adjacent
 					function
 ****************************************************************************/
void fill_adjacency_matrix(word *pword,int ***p_adj_mat)
{
	printf("STARTED FILLING OF ADJACENCY MATRIX\n");
	for(int i=0;i<MAT_LENGTH;i++)
	{
		if(i%500 == 0)
		printf("fill_adjacency_matrix function is still on going\n");
		for(int j=0;j<MAT_LENGTH;j++)
		{
			if(i != j)
			{
				(*p_adj_mat)[i][j] = is_adjacent(pword[i].value,pword[j].value);
			}						
		}
	}	
	printf("END OF FILLING ADJACENCY MATRIX\n");
}

/****************************************************************************
 * Function Name  : check_words_adjacency_in_graph
 * Inputs         : pdest   : 1 st word
 					psource : 2 nd word
 					pwords  : adj graph 
 * Outputs        : Currently None
 * Returns        : 1 for adjancaceny occurs
					0 for adjancaceny not occurs
					-1 for words are not found
 * Description    : To test adj graph
 					for e.g. check_words_adjacency_in_graph("prove","prose",p_adj_mat,words);
 ****************************************************************************/
int check_words_adjacency_in_graph(char *psource, char *pdest, word *pwords, int ***p_adj_mat)
{
	int psource_index,pdest_index;
	
	psource_index = find_exact_word_index(psource,pwords);
	printf("FIRST INDEX %d string : %s\n",psource_index,psource );

	pdest_index = find_exact_word_index(pdest,pwords);
	printf("SECOND INDEX %d string : %s\n",pdest_index,pdest );

	if(psource_index == (-1) || pdest_index == (-1))
	{
		return -1;
	}
	else
	{
		return (*p_adj_mat)[psource_index][pdest_index];
	}
}

/****************************************************************************
 * Description    : Takes 2 scanf and uses function above as src and dest
 ****************************************************************************/
int check_words_adjacency_in_graph_console(word *pwords, int ***p_adj_mat)
{
	char source[5+1],dest[5+1];
	int return_value;

	memset(&source, 0x00, 5+1);
	memset(&dest, 0x00, 5+1);

	printf("To look if there is adjaceny give 2 strings\n");
	printf("Results are : 1 for baglanti var ,2 for baglanti yok,-1 for word not found\n");
	
	printf("Waiting for 1 st word\n");
	scanf("%s",source);
	
	printf("Waiting for 2 nd word\n");
	scanf("%s",dest);

	return_value = check_words_adjacency_in_graph(source,dest,pwords,p_adj_mat);
	printf("Result -> %d\n",return_value );
	return return_value;
}

void intro_page()
{
	printf ("\n\n");
	printf("###########################\n");
	printf("########## GRAPH ##########\n");
	printf("###########################\n\n\n");
}

void welcome_screen(unsigned int *p_menu_selection)
{

	printf("\n--------------------------------\n");
	printf("Select Operation to Continue\n");
	printf("1 - display words\n");
	printf("2 - display adjacency\n");
	printf("3 - Test adjacency matrix\n");
	printf("4 - Find Pattern Between 2 Words\n");
	printf("5 - 	\n");
	printf("6 - 	\n");
	printf("7 - 	\n");
	printf("0 - 	\n\n");
	printf("Seçilen işlem:");
	scanf("%d",p_menu_selection);	
	printf("--------------------------------\n");
	printf ("\n");

	if (*p_menu_selection >= NUMBER_OF_DEFINED_FUNCTION_IN_MENU || *p_menu_selection == 0)
				printf("Program has been terminated!\n\n");
}

/****************************************************************************
 * Function Name  : main_page
 * Inputs         : word struck array
 * Outputs        : Currently None
 * Returns        : 1
 * Description    : A Basic UI
 ****************************************************************************/
int main_page(word *pwords,int ***p_adj_mat){

		unsigned int menu_selection 	= 0;
		unsigned int * p_menu_selection = &menu_selection;

	do{
		welcome_screen(p_menu_selection);
		switch (menu_selection) {
			case 1:
				printf("Display All Words\n");
				display_words(pwords);
				break;
			case 2:
				printf("Print adjacency matrix -> its absurd\n\n");
				display_adjacency_matrix(p_adj_mat);
				break;
			case 3:
				printf("Check adjacency of 2 words in graph to Test Graph\n\n");			
				check_words_adjacency_in_graph_console(pwords,p_adj_mat);				
				break;
			case 4:
				printf("Find Pattern Between 2 Words\n\n");			
				find_pattern_between_two_words(pwords,p_adj_mat);
				break;
			case 5:
				// printf("%s\n", );
				break;
			case 6:
				// printf("GUessing\n\n");			
				// guessing_menu(pst_AllTeam);
				break;
			case 7:
				// printf("Reset Scenario\n");
				// reset_scenario(pst_AllTeam);
			default:
				break;
		}

	}while(menu_selection < NUMBER_OF_DEFINED_FUNCTION_IN_MENU && menu_selection != 0);
return 1;
}

int main(void)
{
	
	// had to use malloc to allocate mem for graph otherwise program gets runtime error
	// adjaceceny_matrix is our graph and  word struct is string inputs

	struct word st_word_array[MAT_LENGTH];
	memset(st_word_array,0x00,sizeof(st_word_array));		
	read_words_from_file(st_word_array);		
	printf("WORDS successfully READ FROM FILE\n");

	int **adjaceceny_matrix;
	adjaceceny_matrix = (int **)malloc(MAT_LENGTH * sizeof(int *));
	for (int i = 0; i < MAT_LENGTH; ++i)
		adjaceceny_matrix[i] = (int *)malloc(MAT_LENGTH*sizeof(int));
 
	printf("ALLOCATED MEM FOR ADJ MATRIX\n");
	
	init_adjacency_matrix(&adjaceceny_matrix);
	fill_adjacency_matrix(st_word_array,&adjaceceny_matrix);
	intro_page();
	main_page(st_word_array,&adjaceceny_matrix);

	return 0;	
}