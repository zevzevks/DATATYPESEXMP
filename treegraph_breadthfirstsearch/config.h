
#define NUMBER_OF_DEFINED_FUNCTION_IN_MENU 10		// Needed for UI not important
#define MINUS_ONE	-1    
#define SIZE 200            // MEM OF QUEUE

typedef struct word {
	int index;
	char value[5];
} word;


typedef struct queue {
    int items[SIZE];
    int front;
    int rear;
}queue;

/* QUEUE BASED FUNCTIONS SOME MIGHT NOT BE USED*/

struct queue* createQueue();
void enqueue(struct queue* q, int);
int dequeue(struct queue* q);
void display(struct queue* q);
int isEmpty(struct queue* q);
void printqueue(struct queue* q);


queue* createQueue() 
{
    queue* q = malloc(sizeof(queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

int isFull(queue *q)
{
    if(q->rear == SIZE-1) {
        printf("<---------QUEUE IS FULL!!---->\n");
        return 1;
        }else return 0;
}


int isEmpty(queue *q) 
{
    if(q->rear == -1) 
        return 1;
    else 
        return 0;
}

void enqueue(queue* q, int value)
{
    printf("adding %d into queue\n",value );
    if(q->front == -1)
    q->front = 0;
    q->rear++;
    q->items[q->rear] = value; 
}

int pop_queue(queue* q)
{	
	int item;
	if(isEmpty(q)){
        printf("Queue is empty");
        return item = -1;
    }
    else
    {
    	return q->items[q->front];
    }
}

int dequeue(queue* q)
{
    int item;
    if(isEmpty(q)){
        printf("Queue is empty");
        item = -1;
    }
    else
    {
        item = q->items[q->front];
        q->front++;
        if(q->front > q->rear){
            printf("front > rear error");
            return -1;
        }
    printf("%d VALUE HAS DEQUEUED\n",item );
    }
    return item;
}

void printqueue(queue *q) 
{
    int i = q->front;

    if(isEmpty(q)) {
        printf("Queue is empty");
    } else {
        printf("\nQueue contains \n");
        for(i = q->front; i < q->rear + 1; i++) {
                printf("%d -", q->items[i]);
        }
        printf("\n");
    }    
}

int countqueue(queue *q)
{
	int total = 0;
	
	if(isEmpty(q))
	{
		printf("Queue is empty\n");
		return -1;
	}
	else
	{
		printf("Total number of elements : ");
		total = q->front+1-q->rear;
			printf("%d\n",total );
			return total;
	}
return total;
}