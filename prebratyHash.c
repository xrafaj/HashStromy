#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 100000

/*

Prebraté z 
http://enthusiaststudent.blogspot.com/2017/03/hashing-with-separate-chaining-c-program.html
Urobené menšie úpravy z dôvodu testovania:
Posielanie argumentu, namiesto scanf. 
Zväèšenie tabu¾ky z hodnoty 10 na 100000.
Zmena na returny namiesto výpisov.

*/

struct node
{
	int data;
	struct node *next;
};

struct node *head[TABLE_SIZE]={NULL},*c;

void insertKey(int key)
{
    int i;
    i=key%TABLE_SIZE;
    struct node * newnode=(struct node *)malloc(sizeof(struct node));
    newnode->data=key;
    newnode->next = NULL;
    if(head[i] == NULL)
        head[i] = newnode;
    else
    {
        c=head[i];
        while(c->next != NULL)
        {
           c=c->next;
        }
        c->next=newnode;
    }
}
int search(int key)
{
    int index;
    index=key%TABLE_SIZE;
    if(head[index] == NULL)
        return 0;
    else
    {
        for(c=head[index];c!=NULL;c=c->next)
        {
            if(c->data == key)
                {
                    return 1;
                    break;
                }
        }
        if(c==NULL)
            return 0;
   
    }
}
void display()
{
    int i;
    for(i=0;i<TABLE_SIZE;i++)
          {
           printf("\nentries at index %d\n",i);
               if(head[i] == NULL)
               {
               printf("No Hash Entry");
               return;
               }
               else
               {
                              for(c=head[i];c!=NULL;c=c->next)
                              printf("%d->",c->data);
               }
          }
         
}

void test_PrebratyHash()
{
	clock_t t;
	printf("Hash - chaining method (prebrata implementacia)\n\n");
	printf ("Inserting sorted array of 5000000 values ...\n");
	t = clock();
  	int i = 0;
	for(i=0;i<5000000;i++)
	{
		insertKey(i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching array of 5000000 values ...\n");
	t = clock();
	for(i=0;i<5000000;i++)
	{
		search(i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test2_PrebratyHash(int N)
{
	clock_t t;
	printf("Hash - chaining method (prebrata implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
  	int i = 0;
	for(i=N;i>=1;i--)
	{
		insertKey(i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(i=N;i>=1;i--)
	{
		search(i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test3_PrebratyHash(int N)
{
	clock_t t;
	printf("Hash - chaining method (prebrata implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
  	int i = 0;
	for(i=N/2;i>=1;i--)
	{
		if(N%2==0)insertKey(i);
		if(N%2==1)insertKey(N-i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(i=N/2;i>=1;i--)
	{
		if(N%2==0)search(i);
		if(N%2==1)search(N-i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test4_PrebratyHash(int N)
{
	clock_t t;
	printf("Hash - chaining method (prebrata implementacia)\n\n");
	printf ("Inserting & searching values ...\n");
	t = clock();
  	int i = 0;
	for( i=0 ; i<N ; i++)
	{
		insertKey(i);
		search(i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test5_PrebratyHash(int N)
{
	clock_t t;
	printf("Hash - chaining method (prebrata implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
  	int i = 0;
	for(i=0;i<N/2;i++)
	{
		insertKey(i*3);
		insertKey(i*2);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(i=0;i<N/2;i++)
	{
		search(i*3);
		search(i*2);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test6_PrebratyHash(int N)
{
	clock_t t;
	printf("Hash - chaining method (prebrata implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
  	int i = 0;
	for(i=N;i>0;i--)
	{
		if(i%2==0)insertKey(i);
		else insertKey(2*i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(i=N;i>0;i--)
	{
		if(i%2==0)search(i);
		else search(2*i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test7_PrebratyHash(int N)
{
	clock_t t;
	printf("Hash - chaining method (prebrata implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
  	int i = 0;
	for(i=0;i<N;i++)
	{
		insertKey(i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(i=N;i>0;i--)
	{
		search(i);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}
