/*
                An implementation of top-down splaying
                    D. Sleator <sleator@cs.cmu.edu>
    	                     March 1992

  "Splay trees", or "self-adjusting search trees" are a simple and
  efficient data structure for storing an ordered set.  The data
  structure consists of a binary tree, without parent pointers, and no
  additional fields.  It allows searching, insertion, deletion,
  deletemin, deletemax, splitting, joining, and many other operations,
  all with amortized logarithmic performance.  Since the trees adapt to
  the sequence of requests, their performance on real access patterns is
  typically even better.  Splay trees are described in a number of texts
  and papers [1,2,3,4,5].

  The code here is adapted from simple top-down splay, at the bottom of
  page 669 of [3].  It can be obtained via anonymous ftp from
  spade.pc.cs.cmu.edu in directory /usr/sleator/public.

  The chief modification here is that the splay operation works even if the
  item being splayed is not in the tree, and even if the tree root of the
  tree is NULL.  So the line:

                              t = splay(i, t);

  causes it to search for item with key i in the tree rooted at t.  If it's
  there, it is splayed to the root.  If it isn't there, then the node put
  at the root is the last one before NULL that would have been reached in a
  normal binary search for i.  (It's a neighbor of i in the tree.)  This
  allows many other operations to be easily implemented, as shown below.

  [1] "Fundamentals of data structures in C", Horowitz, Sahni,
       and Anderson-Freed, Computer Science Press, pp 542-547.
  [2] "Data Structures and Their Algorithms", Lewis and Denenberg,
       Harper Collins, 1991, pp 243-251.
  [3] "Self-adjusting Binary Search Trees" Sleator and Tarjan,
       JACM Volume 32, No 3, July 1985, pp 652-686.
  [4] "Data Structure and Algorithm Analysis", Mark Weiss,
       Benjamin Cummins, 1992, pp 119-130.
  [5] "Data Structures, Algorithms, and Performance", Derick Wood,
       Addison-Wesley, 1993, pp 367-375.
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int size;  /* number of nodes in the tree */
           /* Not actually needed for any of the operations */

typedef struct tree_node Tree;
struct tree_node {
    Tree * left, * right;
    int item;
};

Tree * splay (int i, Tree * t) {
/* Simple top down splay, not requiring i to be in the tree t.  */
/* What it does is described above.                             */
    Tree N, *l, *r, *y;
    if (t == NULL) return t;
    N.left = N.right = NULL;
    l = r = &N;

    for (;;) {
	if (i < t->item) {
	    if (t->left == NULL) break;
	    if (i < t->left->item) {
		y = t->left;                           /* rotate right */
		t->left = y->right;
		y->right = t;
		t = y;
		if (t->left == NULL) break;
	    }
	    
	    r->left = t;                               /* link right */
	    r = t;
	    t = t->left;
	    
	} else if (i > t->item) {
	    if (t->right == NULL) break;
	    if (i > t->right->item) {
		y = t->right;                          /* rotate left */
		t->right = y->left;
		y->left = t;
		t = y;
		if (t->right == NULL) break;
	    }
	    
	    l->right = t;                              /* link left */
	    l = t;
	    t = t->right;
	    
	} else {
	    break;
	}
    }
    l->right = t->left;                                /* assemble */
    r->left = t->right;
    t->left = N.right;
    t->right = N.left;
    return t;
}

/* Here is how sedgewick would have written this.                    */
/* It does the same thing.                                           */
Tree * sedgewickized_splay (int i, Tree * t) {
    Tree N, *l, *r, *y;
    if (t == NULL) return t;
    N.left = N.right = NULL;
    l = r = &N;

    for (;;) {
	if (i < t->item) {
	    if (t->left != NULL && i < t->left->item) {
		y = t->left; t->left = y->right; y->right = t; t = y;
	    }
	    if (t->left == NULL) break;
	    r->left = t; r = t; t = t->left;
	} else if (i > t->item) {
	    if (t->right != NULL && i > t->right->item) {
		y = t->right; t->right = y->left; y->left = t; t = y;
	    }
	    if (t->right == NULL) break;
	    l->right = t; l = t; t = t->right;
	} else break;
    }
    l->right=t->left; r->left=t->right; t->left=N.right; t->right=N.left;
    return t;
}

Tree * insert(int i, Tree * t) {
/* Insert i into the tree t, unless it's already there.    */
/* Return a pointer to the resulting tree.                 */
    Tree * new;
    
    new = (Tree *) malloc (sizeof (Tree));
    if (new == NULL) {
		printf("Ran out of space\n");
		exit(1);
    }
    new->item = i;
    if (t == NULL) {
		new->left = new->right = NULL;
		size = 1;
		return new;
    }
    t = splay(i,t);
    if (i < t->item) {
		new->left = t->left;
		new->right = t;
		t->left = NULL;
		size ++;
		return new;
    } else if (i > t->item) {
		new->right = t->right;
		new->left = t;
		t->right = NULL;
		size++;
		return new;
    } else { /* We get here if it's already in the tree */
             /* Don't add it again                      */
			free(new);
			return t;
    }
}

Tree * delete(int i, Tree * t) {
/* Deletes i from the tree if it's there.               */
/* Return a pointer to the resulting tree.              */
    Tree * x;
    if (t==NULL) return NULL;
    t = splay(i,t);
    if (i == t->item) {               /* found it */
	if (t->left == NULL) {
	    x = t->right;
	} else {
	    x = splay(i, t->left);
	    x->right = t->right;
	}
	size--;
	free(t);
	return x;
    }
    return t;                         /* It wasn't there */
}

void test_PrebratyStrom()
{
	Tree * root = NULL;
    Tree * findKey = NULL;
    int i;
    size = 0;
    clock_t t;
    printf("Tree - SPLAY method (prebrata implementacia)\n\n");
  	printf ("Inserting sorted array of 5000000 values ...\n");
	t = clock();
    for (i = 0; i < 5000000 ; i++) {
		root = insert(i, root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching array of 5000000 values ...\n");
	t = clock();
    for (i = 0; i < 5000000 ; i++) {
		splay(i,root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    int count=0;
}

void test2_PrebratyStrom(int N)
{
	Tree * root = NULL;
    Tree * findKey = NULL;
    int i;
    size = 0;
    clock_t t;
    printf("Tree - SPLAY method (prebrata implementacia)\n\n");
  	printf ("Inserting values ...\n");
	t = clock();
    for (i = N; i >= 1 ; i--) {
		root = insert(i, root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
    for (i = N; i >= 1 ; i--) {
		splay(i,root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    int count=0;
}

void test3_PrebratyStrom(int N)
{
	Tree * root = NULL;
    Tree * findKey = NULL;
    int i;
    size = 0;
    clock_t t;
    printf("Tree - SPLAY method (prebrata implementacia)\n\n");
  	printf ("Inserting values ...\n");
	t = clock();
    for (i = N/2; i >= 1 ; i--) {
		if(N%2==0)root = insert(i, root);
		if(N%2==1)root = insert(N-i,root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
    for (i = N/2; i >= 1 ; i--) {
    	if(N%2==0)splay(i,root);
    	if(N%2==1)splay(N-i,root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    int count=0;
}

void test4_PrebratyStrom(int N)
{
	Tree * root = NULL;
    Tree * findKey = NULL;
    int i;
    size = 0;
    clock_t t;
    printf("Tree - SPLAY method (prebrata implementacia)\n\n");
  	printf ("Inserting & searching values ...\n");
	t = clock();
	for( i=0 ; i<N ; i++)
	{
		root = insert(1,root);
		splay(1,root);
	}
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}

void test5_PrebratyStrom(int N)
{
	Tree * root = NULL;
    Tree * findKey = NULL;
    int i;
    size = 0;
    clock_t t;
    printf("Tree - SPLAY method (prebrata implementacia)\n\n");
  	printf ("Inserting values ...\n");
	t = clock();
	for(i=0;i<N/2;i++)
	{
		root = insert(i*3,root);
		root = insert(i*2,root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
    for(i=0;i<N/2;i++)
	{
		splay(i*3,root);
		splay(i*2,root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    int count=0;
}

void test6_PrebratyStrom(int N)
{
	Tree * root = NULL;
    Tree * findKey = NULL;
    int i;
    size = 0;
    clock_t t;
    printf("Tree - SPLAY method (prebrata implementacia)\n\n");
  	printf ("Inserting values ...\n");
	t = clock();
	for(i=N;i>0;i--)
	{
		if(i%2==0)root = insert(i,root);
		else root = insert(i*2,root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
    for(i=N;i>0;i--)
	{
		if(i%2==0)splay(i,root);
		else splay(i*2,root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    int count=0;
}

void test7_PrebratyStrom(int N)
{
	Tree * root = NULL;
    Tree * findKey = NULL;
    int i;
    size = 0;
    clock_t t;
    printf("Tree - SPLAY method (prebrata implementacia)\n\n");
  	printf ("Inserting values ...\n");
	t = clock();
    for (i = 0; i < N ; i++) {
		root = insert(i, root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    printf ("Searching values ...\n");
	t = clock();
    for(i=N;i>0;i--)
	{
		splay(i,root);
    }
    t = clock() - t;
    printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    
    int count=0;
}
