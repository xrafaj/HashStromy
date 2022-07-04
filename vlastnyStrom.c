#include<stdio.h> 
#include<stdlib.h> 
#include<time.h>

struct HEAD 
{ 
  int key; 
  struct HEAD *left; 
  struct HEAD *right; 
  int height; 
}; 

struct HEAD *rightRotate(struct HEAD *goDown) 
{ 
	int max = 0;
	struct HEAD *goUp = goDown->left; 
	struct HEAD *temp = goUp->right; 
	
	goUp->right = goDown; 
	goDown->left = temp; 
		
	if(goDown->left!=NULL)max = goDown->left->height;
	if(goDown->right!=NULL)
	{
		if(max<goDown->right->height)max=goDown->right->height;
	}
	goDown->height = max;
	
	max = 0;
	
	if(goUp->left!=NULL)max = goUp->left->height;
	if(goUp->right!=NULL)
	{
		if(max<goUp->right->height)max=goUp->right->height;
	}
	goUp->height = max;
	return goUp; 
} 

struct HEAD *leftRotate(struct HEAD *goDown) 
{ 
	int max = 0;
	struct HEAD *goUp = goDown->right; 
	struct HEAD *temp = goUp->left; 
	
	goUp->left = goDown; 
	goDown->right = temp; 

	if(goUp->left!=NULL)max = goUp->left->height;
	if(goUp->right!=NULL)
	{
		if(max<goUp->right->height)max=goUp->right->height;
	}
	goUp->height = max;
	
	max = 0;
	
	if(goDown->left!=NULL)max = goDown->left->height;
	if(goDown->right!=NULL)
	{
		if(max<goDown->right->height)max=goDown->right->height;
	}
	goDown->height = max;
  	return goUp; 
} 

struct HEAD* placeKey(struct HEAD* head, int key) 
{ 

	if (head == NULL){
  	  	struct HEAD* head = (struct HEAD*) malloc(sizeof(struct HEAD)); 
	  	head->key = key; 
	  	head->left = head->right = NULL; 
	  	head->height = 1;
		return head; 
	}
	int balanceFactor;
	int max = 0;
	
	if(key == head->key)return head;
	if(key < head->key)head->left = placeKey(head->left, key); 
	if(key > head->key)head->right = placeKey(head->right, key); 
	
    if(head->left!=NULL)max= head->left->height;
 	if(head->right!=NULL)
	{
		if(max<head->right->height)max = head->right->height;
	}
 	head->height = 1 + max;

	if(head->left!=NULL && head->right!=NULL) balanceFactor = head->left->height - head->right->height;
	else if(head->left!=NULL) balanceFactor = head->left->height;
	else if(head->right!=NULL) balanceFactor = - head->right->height;
	else balanceFactor = 0;

	if (balanceFactor <= -2)
	{
		if (key > head->right->key)
		{
			return leftRotate(head);
		}
		else if (key < head->right->key)
		{
			head->right = rightRotate(head->right);
			return leftRotate(head);
		}
	}

	if (balanceFactor >= 2)
	{
		if (key < head->left->key)
		{
			return rightRotate(head);
		}
		else if (key > head->left->key)
		{
			head->left = leftRotate(head->left);
		return rightRotate(head);
		}
	}
	

	
	return head; 
} 

void printPreOrder(struct HEAD *root) 
{ 
  if(root != NULL) 
  { 
    printf("%d ", root->key); 
    printPreOrder(root->left); 
    printPreOrder(root->right); 
  } 
} 

int keySearch(struct HEAD *head, int key)
{
	if(head==NULL)return -1;
	else{
		if(key==head->key){
			return 1;
		}
		if(key<head->key)
		{
			return keySearch(head->left, key);
		}
		if(key>head->key)
		{
			return keySearch(head->right,key);
		}
	}
}

void test_VlastnyStrom()
{
  struct HEAD *head = NULL; 
  clock_t t;	
  int k;
  printf("Tree - AVL method (vlastna implementacia)\n\n");
  printf ("Inserting sorted array of 5000000 values ...\n");
  t = clock();
  head = placeKey(head, 1);
  for(k=1;k<5000000;k++)
  {
  	placeKey(head,k);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  
  printf ("Searching array of 5000000 values ...\n");
  t = clock();
  for(k=1;k<5000000;k++)
  {
  	keySearch(head,k);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test2_VlastnyStrom(int N)
{  
  struct HEAD *head = NULL; 
  int k;
  clock_t t;
  printf("Tree - AVL method (vlastna implementacia)\n\n");
  printf ("Inserting values ...\n");
  t = clock();
  head = placeKey(head, N);
  for( k = N-1 ; k >= 1 ; k-- )
  {
  	placeKey(head,k);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  
  printf ("Searching values ...\n");
  t = clock();
  keySearch(head,N);
  for( k = N-1 ; k >= 1 ; k-- )
  {
  	keySearch(head,k);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test3_VlastnyStrom(int N)
{  
  struct HEAD *head = NULL; 
  int k;
  clock_t t;
  printf("Tree - AVL method (vlastna implementacia)\n\n");
  printf ("Inserting values ...\n");
  t = clock();
  head = placeKey(head, N/2);
  for( k = N/2 ; k >= 1 ; k-- )
  {
  	if(N%2==0)placeKey(head,k);
  	if(N%2==1)placeKey(head,N-k);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  
  printf ("Searching values ...\n");
  t = clock();
  for( k = N/2 ; k >= 1 ; k-- )
  {
  	if(N%2==0)keySearch(head,k);
  	if(N%2==1)keySearch(head,N-k);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test4_VlastnyStrom(int N)
{  
  struct HEAD *head = NULL; 
  int k;
  clock_t t;
  printf("Tree - AVL method (vlastna implementacia)\n\n");
  printf ("Inserting & searching values ...\n");
  t = clock();
  head = placeKey(head, 0);
  for( k=1 ; k<N ; k++)
  {
	placeKey(head,k);
	keySearch(head,k);
  }
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test5_VlastnyStrom(int N)
{  
  struct HEAD *head = NULL; 
  int k;
  clock_t t;
  printf("Tree - AVL method (vlastna implementacia)\n\n");
  printf ("Inserting values ...\n");
  t = clock();
  head = placeKey(head, 0);
  for(k=0;k<N/2;k++)
  {
	placeKey(head,k*3);
	placeKey(head,k*2);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  
  printf ("Searching values ...\n");
  t = clock();
  for(k=0;k<N/2;k++)
  {
	keySearch(head,k*3);
	keySearch(head,k*2);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test6_VlastnyStrom(int N)
{  
  struct HEAD *head = NULL; 
  int k;
  clock_t t;
  printf("Tree - AVL method (vlastna implementacia)\n\n");
  printf ("Inserting values ...\n");
  t = clock();
  head = placeKey(head, N);
  for(k=N;k>0;k--)
  {
	if(k%2==0)placeKey(head,k);
	else placeKey(head,k*2);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  
  printf ("Searching values ...\n");
  t = clock();
  for(k=N;k>0;k--)
  {
	if(k%2==0)keySearch(head,k);
	else keySearch(head,k*2);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test7_VlastnyStrom(int N)
{
  struct HEAD *head = NULL; 
  clock_t t;	
  int k;
  printf("Tree - AVL method (vlastna implementacia)\n\n");
  printf ("Inserting values ...\n");
  t = clock();
  head = placeKey(head, 1);
  for(k=1;k<N;k++)
  {
  	placeKey(head,k);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  
  printf ("Searching values ...\n");
  t = clock();
  for(k=N;k>0;k--)
  {
  	keySearch(head,k);
  }  
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

