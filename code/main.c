#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>

#include "rndm.h"
#include "tm.h"
#include "repls.h"
#include "cnst.h"

// #define TOCK(X, Y) Y = (clock()) * 1000 / CLOCKS_PER_SEC - (X)
// #define PRINTTOCK(X) printf("time %s: %g msec.\n", (#X), (double)(clock() - (X)) * 1000 / CLOCKS_PER_SEC)

// // копия файла ("repls.h")
// void cp(void);

// // переимен-е файла
// void renm(void);

// // удаление файла
// void dlt(void);




int main() {	
	// int g;
	int nfls1 = 4, nflds1 = 8, nfls, nflds, flg, rnd;
	// char *fl, *fldr;
	long int cnt;

	cnt = cntfls(CONSTPATH);
	nfls = cnt/MAX;
	nflds = cnt%MAX + 1;
	TICK(tmbgn);

	printf("%d %d\n", nfls, nflds);
	for (int j = 0; j < 24; j++) {
		repls(cntfls, strpls, rndmfl, rndmk, tmpr, namege, &nfls, &nflds, tmbgn);
		// printf("%d %d\n", nfls, nflds);
		renm(cntfls, strpls, rndmfl, rndmk, tmpr, namege, namefl, &nfls, &nflds, tmbgn);
		// printf("%d %d\n", nfls, nflds);
		add(cntfls, strpls, rndmfl, rndmk, tmpr, namege, namefl, &nfls, &nflds, tmbgn);
		// printf("%d %d\n", nfls, nflds);
		dlt(cntfls, strpls, rndmfl, rndmk, tmpr, &nfls, &nflds, tmbgn);
		// printf("%d %d\n", nfls, nflds);
	}
	printf("abc\n");
	return 0;
}







/*


// создание файла / папки
int add(long int (*cntfls) (char *folder), char* (*strpls) (char *str,...),
char (*rndmfl) (char *folder, long int (*cntfls) (char *folder), char (*strpls) (char *str,...), int rnmb, int fl),
int rndmk(clock_t tmbgn, int n), long int *nobj, clock_t tmbgn) {
	int e = 1, obj;
	char *xobj;
	obj = rndmk(tmbgn, 2);     
	printf("%d obj\n", obj);
	int b = rndmk(tmbgn, (obj == 0)*((*nobj)%MAX + 1) + (obj == 1)*((*nobj)/MAX) + 1);     
	printf("%d nobj\n", b);     
	printf("%s xobj\n", xobj);
	xobj = rndmfl(CONSTPATH, cntfls, strpls, b, obj);     
	printf("%s xobj\n", xobj);
	*nobj += (obj == 0) + (obj == 1)*MAX;
	free(xobj);
	return e;
}


*/



/*


int add(long int (*cntfls) (char *folder), char (*strpls) (char *str,...),
char *rndmfl(char *folder, long int (*cntfls) (char *folder), char (*strpls) (char *str,...), int rnmb, int fl),
int rndmk(clock_t tmbgn, int n), long int *nobj, clock_t tmbgn)




int add(long int (*cntfls) (char *folder), char (*strpls) (char *str,...),
char (*rndmfl) (char *folder, long int (*cntfls) (char *folder), char (*strpls) (char *str,...), int rnmb, int fl),
int rndmk(clock_t tmbgn, int n), long int *nobj, clock_t tmbgn)


*/






