#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct data {
	int key;
}DATA;

typedef struct table {
	int size;
	DATA **arr;
}TABLE;

void insertToTable(TABLE *t, int key);
void expandTable(TABLE *t);
unsigned long hash_f(unsigned int key, TABLE *ht);
DATA* searchD(TABLE *t, int key);

unsigned long hash_f(unsigned int key, TABLE *ht)
{
	unsigned int hash;
	hash = key % ht->size;
	if(hash > 0) return hash;
	else return -hash;
}

DATA* createData(int key)
{
	DATA *new_node = (DATA*)malloc(sizeof(DATA));
	new_node->key = key;
}

void expandTable(TABLE *ht)
{	
	TABLE *new_table = (TABLE*)malloc(sizeof(TABLE));
	new_table->size = ht->size*2;
	new_table->arr = (DATA**)calloc(new_table->size, sizeof(DATA*));
	
	int i;
	for(i=0;i<ht->size;i++){
		if(ht->arr[i]!=NULL){
			insertToTable(new_table,ht->arr[i]->key);
		}
	}
	
	ht->size = new_table->size;
	free(ht->arr);
	ht->arr = new_table->arr;
}

void insertToTable(TABLE *ht, int key)
{
	int status = 0;
	int i, index;
	int hashkey= hash_f(key,ht); 
	for(i=0;i<ht->size;i++)
	{
		index = (hashkey+i)%ht->size;
		DATA* curr = ht->arr[index];
		if(curr==NULL){
			ht->arr[index] = createData(key);
			status = 1;
			break;
		}
		if(curr->key == key){
			status = 1;
			break;
		}
	}
	if(status==0){
		expandTable(ht);
		insertToTable(ht,key);
	}
}

DATA* searchD(TABLE *t, int key)
{
	int i, index;
	int hashkey= hash_f(key,t); 
	for(i=0;i<t->size;i++)
	{
		index = (hashkey+i)%t->size;
		DATA* curr = t->arr[index];
		if(curr!=NULL && curr->key == key)
			return curr;
		else continue;
	}
	return NULL;
}

void test_VlastnyHash()
{
	int *arr = (int*)malloc(100 * sizeof(int));
	TABLE *ht = (TABLE*)malloc(sizeof(TABLE));
	ht->size = 100;
	ht->arr = (DATA**)calloc(ht->size, sizeof(DATA*));
	DATA *searchData;
	clock_t t;
	int k;
	
	printf("Hash - Open-adressing linear probing method (vlastna implementacia)\n\n");
	printf ("Inserting sorted array of 5000000 values ...\n");
	t = clock();
	for(k=0;k<5000000;k++)
	{
		insertToTable(ht,k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching array of 5000000 values ...\n");
	t = clock();
	for(k=0;k<5000000;k++)
	{
		searchD(ht,k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test2_VlastnyHash(int N)
{
	int *arr = (int*)malloc(100 * sizeof(int));
	TABLE *ht = (TABLE*)malloc(sizeof(TABLE));
	ht->size = 100;
	ht->arr = (DATA**)calloc(ht->size, sizeof(DATA*));
	DATA *searchData;
	clock_t t;
	int k;
	
	printf("Hash - Open-adressing linear probing method (vlastna implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
	for(k=N;k>=1;k--)
	{
		insertToTable(ht,k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(k=N;k>=1;k--)
	{
		searchD(ht,k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test3_VlastnyHash(int N)
{
	int *arr = (int*)malloc(100 * sizeof(int));
	TABLE *ht = (TABLE*)malloc(sizeof(TABLE));
	ht->size = 100;
	ht->arr = (DATA**)calloc(ht->size, sizeof(DATA*));
	DATA *searchData;
	clock_t t;
	int k;
	
	printf("Hash - Open-adressing linear probing method (vlastna implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
	for(k=N/2;k>=1;k--)
	{
		if(N%2==0)insertToTable(ht,k);
		if(N%2==1)insertToTable(ht,N-k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(k=N;k>=1;k--)
	{
		if(N%2==0)searchD(ht,k);
		if(N%2==1)searchD(ht,N-k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test4_VlastnyHash(int N)
{
	int *arr = (int*)malloc(100 * sizeof(int));
	TABLE *ht = (TABLE*)malloc(sizeof(TABLE));
	ht->size = 100;
	ht->arr = (DATA**)calloc(ht->size, sizeof(DATA*));
	DATA *searchData;
	clock_t t;
	int k;
	printf("Hash - Open-adressing linear probing method (vlastna implementacia)\n\n");
	printf ("Inserting & searching values ...\n");
	t = clock();
	for(k=0;k<N;k++)
	{
		insertToTable(ht,k);
		searchD(ht,k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test5_VlastnyHash(int N)
{
	int *arr = (int*)malloc(100 * sizeof(int));
	TABLE *ht = (TABLE*)malloc(sizeof(TABLE));
	ht->size = 100;
	ht->arr = (DATA**)calloc(ht->size, sizeof(DATA*));
	DATA *searchData;
	clock_t t;
	int k;
	
	printf("Hash - Open-adressing linear probing method (vlastna implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
	for(k=0;k<N/2;k++)
	{
		insertToTable(ht,k*3);
		insertToTable(ht,k*2);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(k=0;k<N/2;k++)
	{
		searchD(ht,k*3);
		searchD(ht,k*2);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test6_VlastnyHash(int N)
{
	int *arr = (int*)malloc(100 * sizeof(int));
	TABLE *ht = (TABLE*)malloc(sizeof(TABLE));
	ht->size = 100;
	ht->arr = (DATA**)calloc(ht->size, sizeof(DATA*));
	DATA *searchData;
	clock_t t;
	int k;
	
	printf("Hash - Open-adressing linear probing method (vlastna implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
	for(k=0;k<N;k++)
	{
		insertToTable(ht,k);
		insertToTable(ht,-k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(k=0;k<N;k++)
	{
		searchD(ht,k);
		searchD(ht,-k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test7_VlastnyHash(int N)
{
	int *arr = (int*)malloc(100 * sizeof(int));
	TABLE *ht = (TABLE*)malloc(sizeof(TABLE));
	ht->size = 100;
	ht->arr = (DATA**)calloc(ht->size, sizeof(DATA*));
	DATA *searchData;
	clock_t t;
	int k;
	
	printf("Hash - Open-adressing linear probing method (vlastna implementacia)\n\n");
	printf ("Inserting values ...\n");
	t = clock();
	for(k=0;k<N;k++)
	{
		insertToTable(ht,k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
	for(k=N;k>0;k--)
	{
		searchD(ht,k);
	}
	t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}
