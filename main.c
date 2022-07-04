#include "prebratyStrom.c"
#include "prebratyHash.c"
#include "vlastnyHash.c"
#include "vlastnyStrom.c"
#include <stdio.h>
#include <stdlib.h>

/*
int main()
{
	// testovanie 50M prvkov sortnutych od najmensieho po najvacsi
	test_VlastnyStrom();
	printf("\n------------------------\n");
	test_PrebratyStrom();
	printf("\n------------------------\n");
	test_VlastnyHash();	
	printf("\n------------------------\n");
	test_PrebratyHash();
	return 0;
}
*/


/*
int main()
{
	// testovanie N prvkov sortnutych od najvacsieho po najmensi
	int N = 2000000;
	test2_VlastnyStrom(N);
	printf("\n------------------------\n");
	test2_PrebratyStrom(N);
	printf("\n------------------------\n");
	test2_VlastnyHash(N);	
	printf("\n------------------------\n");
	test2_PrebratyHash(N);
	
	return 0;
}
*/

/*
int main()
{
	//  METODA TESTOVANIA
	//	for( i = N/2 ; i >= 1 ; i--)
	//	{
	//		if( N%2 == 0)insertKey(i);
	//		if( N%2 == 1)insertKey(N-i);
	//  }

	int N = 100000;
	
	test3_VlastnyStrom(N);
	printf("\n------------------------\n");
	test3_PrebratyStrom(N);
	printf("\n------------------------\n");
	test3_VlastnyHash(N);	
	printf("\n------------------------\n");
	test3_PrebratyHash(N);
	
	return 0;
}
*/

/*
int main()
{
	// testovanie vkladania & citania N sortnutch cisel(najm->najv) na striedacku, t.j. vlozim, dam vyhladat, vlozim, dam vyhladat,...
	
	int N = 200000;
	
	test4_VlastnyStrom(N);
	printf("\n------------------------\n");
	test4_PrebratyStrom(N);
	printf("\n------------------------\n");
	test4_VlastnyHash(N);	
	printf("\n------------------------\n");
	test4_PrebratyHash(N);
	
	return 0;
}
*/

/*
int main(){
	// insertovanie skoro sortnuteho pola
	// t.j.
	// i*3 i*2
	// 0 0 3 2 6 4 9 6 atd.
	
	int N = 600000;
	
	test5_VlastnyStrom(N);
	printf("\n------------------------\n");
	test5_PrebratyStrom(N);
	printf("\n------------------------\n");
	test5_VlastnyHash(N);	
	printf("\n------------------------\n");
	test5_PrebratyHash(N);
	
	return 0;
}
*/

/*
int main()
{
	// testovanie vkladania skoro sortnuteho velkeho pola odzadu 
	
	int N = 50000;
	
	test6_VlastnyStrom(N);
	printf("\n------------------------\n");
	test6_PrebratyStrom(N);
	printf("\n------------------------\n");
	test6_VlastnyHash(N);	
	printf("\n------------------------\n");
	test6_PrebratyHash(N);
	
	return 0;
}
*/


int main(){
   	// insertnutie N dlhého po¾a a potom preh¾adávanie štruktúr Nkami odzadu 
	int N = 5000000;
	
	test7_VlastnyStrom(N);
	printf("\n------------------------\n");
	test7_PrebratyStrom(N);
	printf("\n------------------------\n");
	test7_VlastnyHash(N);	
	printf("\n------------------------\n");
	test7_PrebratyHash(N);

	return 0;
}



