#include "repls.h"
// #include "rndm.h" // rndmk, rndmfl
// #include "tm.h" // tmpr, cntfls, strpls, namege

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
#include <malloc.h>


// перемещение файла (1) done
int repls (long int (*cntfls) (char*),
char* (*strpls) (char*, ...),
char* (*rndmfl) (char*, long int (*)(char *), char* (*)(char *, ...), int, int),
int (*rndmk) (clock_t, int, int),
void (*tmpr) (const char*, const char*, int),
char* (*namege) (char*, char*, char*),
int *nfl, int *nfldr, clock_t tmbgn) {

	// показатель корректного выхода из программы, рандом, счетчик, показатель выбора папки/файла
	int e = 1, rnd, j = 0, rndm;
	// начальное имя файла, искомое имя файла, локальное имя файла
	char *fl, *fldr, *name, *nameloc, *name1;

	//что перемещать:
	// rndm = rndmk(tmbgn, 2, j);
	// rnd = rndmk(tmbgn, (*nfldr)*(rndm == 0) + (*nfl)*(rndm == 1), j);
	rndm = 1;
	rnd = rndmk(tmbgn, (*nfl), j) + 1;
	fl = rndmfl(CONSTPATH, cntfls, strpls, rnd, 1); // выбор папки(rndm == 0) или файла(rndm == 1)

	// куда перемещать:
	rnd = rndmk(tmbgn, *nfldr, j) + 1;
	fldr = rndmfl(CONSTPATH, cntfls, strpls, rnd, 0); // выбор рандомной папки

	// создание нового полного имени файла
	// длина начального имени файла, индекс последнего элемента в начальном имени файла, длина искомого имени файла
	int nac = strlen(fl), nac1 = nac - 1, nacfldr = strlen(fldr);
	while (fl[nac1] != '/') // нахождение локального имени файла
		nac1--;

	int nacc = nac1; // положение последнего '/' в строке fl
	name = (char*)malloc((nac - nac1)*sizeof(char));
	while (nac1 < nac - j) {
		name[j] = fl[nac1 + j + 1];
		fldr[nacfldr + j] = fl[nac1 + j];
		j++;
	}
	name[j - 1] = '\0';

	if (!(strcmp(fl, fldr))) { // проверка на изменение каталога файла
		int rnd1 = rnd;
		while (rnd == rnd1) { // выполнение пока (fl == fldr)
			rnd = rndmk(tmbgn, *nfldr, j) + 1;
			j++;
		}
		// создание нового полного имени файла
		free(fldr);
		fldr = rndmfl(CONSTPATH, cntfls, strpls, rnd, 0); // выбор рандомной папки
		nacfldr = strlen(fldr);
	}
	fldr[nacfldr] = '\0';

	name1 = namege(fldr, name, name1);

	fldr = strpls(fldr, fldr, "/", name1, NULL);
	free(name1);

	tmpr(fl, fldr, 1);
	rename (fl, fldr);
	free(fl);
	free(fldr);
	free(name);
	return e;
}


// переимен-е файла (2)
int renm(long int (*cntfls) (char*),
char* (*strpls) (char*, ...),
char* (*rndmfl) (char*, long int (*)(char *), char* (*)(char *, ...), int, int),
int (*rndmk) (clock_t, int, int),
void (*tmpr) (const char*, const char*, int),
char* (*namege) (char*, char*, char*),
char* (*namefl) (char*, char* (*) (char*, ...), int (*) (clock_t, int, int), clock_t),
int *nfl, int *nfldr, clock_t tmbgn) {

	// показатель корректного выхода из программы, рандом, счетчик, длина fl - 1, длина fl - 1 (const), индекс '\0' в name1
	int e = 1, rnd, j = 0, len, len1, lennm1, rlc;
	// файл для изменения имени, локальное имя файла, искомое имя файла
	char *fl, *fldr, *name1, *name, *rash;
	rnd = rndmk(tmbgn, *nfl, j) + 1;
	fl = rndmfl(CONSTPATH, cntfls, strpls, rnd, 1); // выбор рандомного файла
	name1 = namefl(name1, strpls, rndmk, tmbgn);
	len = strlen(fl) - 1;
	lennm1 = strlen(name1);
	len1 = len;
	while (fl[len] != '/' && len >= 0 && fl[len] != '.') {
		len--; // индекс последнего '/'
	}
	if (len == -1) {
		printf("wrong in renm\n");
	} else {
		if (fl[len] == '.') {
			j = 0;
			rash = (char*)malloc((len1 - len + 1)*sizeof(char));
			while (fl[len + j] != '\0') {
				rash[j] = fl[len + j];
				j++;
			}
			rash[j] = '\0';
			name1 = strpls(name1, name1, rash, NULL);
			free(rash);
			while (fl[len] != '/')
				len--;
		}
		fldr = strpls(fldr, fl, NULL);
		fldr[len] = '\0';
		fldr = strpls(fldr, fldr, "/", name1, NULL);
	}
	free(name1);

	tmpr(fl, fldr, 2);
	rename(fl, fldr);

	free(fl);
	free(fldr);
	return e;
}


// создание *.txt файла (3) done
int add(long int (*cntfls) (char*),
char* (*strpls) (char*, ...),
char* (*rndmfl) (char*, long int (*)(char *), char* (*)(char *, ...), int, int),
int (*rndmk) (clock_t, int, int),
void (*tmpr) (const char*, const char*, int),
char* (*namege) (char*, char*, char*),
char* (*namefl) (char*, char* (*) (char*, ...), int (*) (clock_t, int, int), clock_t),
int *nfl, int *nfldr, clock_t tmbgn) {

	// показатель корректного выхода из программы, рандом, счетчик
	int e = 1, rnd, j = 0;
	// папка для создания файла, локальное имя файла, искомое имя файла
	char *fldr, *name1, *name;
	FILE *fl;
	*nfl = *nfl + 1;
	rnd = rndmk(tmbgn, *nfldr, j) + 1;
	fldr = rndmfl(CONSTPATH, cntfls, strpls, rnd, 0); // выбор рандомной папки
	name1 = namefl(name1, strpls, rndmk, tmbgn); // генератор имени нового файла без ".txt"
	name1 = strpls(name1, name1, ".txt", NULL); // добавлеение ".txt" к имени нового файла
	name = namege(fldr, name1, name); // проверка name1 на нахождение в каталоге fldr, коррекция имени нового *.txt файла
	free(name1);
	name = strpls(name, fldr, "/", name, NULL);
	free(fldr);
	fl = fopen(name, "w");
	fclose(fl);
	tmpr("file doesn't exist", name, 3);
	free(name);
	return e;
	}


// удаление файла (4) done
int dlt(long int (*cntfls) (char*),
char* (*strpls) (char*, ...),
char* (*rndmfl) (char*, long int (*)(char *), char* (*)(char *, ...), int, int),
int (*rndmk) (clock_t, int, int),
void (*tmpr) (const char*, const char*, int),
int *nfl, int *nfldr, clock_t tmbgn) {
	// показатель корректного выхода из программы, рандом, счетчик
	int e = 1, rnd, j = 0;
	char *fl;
	*nfl = *nfl - 1;
	rnd = rndmk(tmbgn, *nfl, j) + 1;
	fl = rndmfl(CONSTPATH, cntfls, strpls, rnd, 1); // выбор рандомного файла
	tmpr(fl, "file doesn't exist", 4);
	remove(fl);
	free(fl);
	return e;
}













// 	DIR *files = opendir("files");
// 	rename("files.txt", "files/files.txt");
	
	
// 	DIR *files1 = opendir("files1");
// 	rename("files/files.txt", "files/files1/files.txt");
// 	DIR *files2 = opendir("files2");
// 	rename("files.txt", "files2/files.txt");
// 	closedir(files);
// 	closedir(files1);
// 	closedir(files2);
	

// //	rename("files.txt", "../files.txt");
// //	rename("files.txt", "files/files.txt");
