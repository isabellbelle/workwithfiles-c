#include "rndm.h"
#include "tm.h" // cntfls, strpls
#include "repls.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>

// выбор действия
int rndmd(int (*rndmk) (clock_t, int, int), clock_t tmbgn, int j) {

return rndmk(tmbgn, NKD, j) + 1;
}

// рандом done
int rndmk(clock_t tmbgn, int n, int j) {

	// int tm, *rnd, *rnd1, rand;
	// long int rand1, rand2;
	// rnd = (int*)calloc(1, sizeof(int));
	// rnd1 = (int*)malloc(sizeof(int));
	// // rand1 = &rnd[0];
	// // rand2 = &rnd1[0];
	// rand1 = 12345;
	// rand2 = 12345678;
	// rand = abs(2*rand1 + 3*rand2 + 37*j)%147;
	// free(rnd);
	// free(rnd1);
	int tm, rnd;
	rnd = rand()%147;
	tm = (double)((clock() + (tmbgn)) * 1000 / CLOCKS_PER_SEC);
	tm = (tm + rnd) / 1;
	tm = tm % n;
	return tm;
}


// рандомный выбор файла, папки done
char *rndmfl(char *folder, long int (*cntfls) (char*), char* (*strpls) (char*, ...),
int rnmb, int fl) {

	// printf("rndmfl1\n");
	int rnmb1, len = 0, lenn, cfls; // количество файлов в папке scan, cntfls(path1), счетчик 1, 2
	char *scan, *path = folder, *pathh; // проверяемый объект, путь к folder, путь к scan(итоговый)
	// pathh = (char*)calloc(50, sizeof(char));
	DIR *dp, *dp2; // текущая, проверочная папка
	FILE *dp1; // проверочный файл
    struct dirent *files; // файлы в текущем каталоге
	pathh = strpls(pathh, path, NULL);

	dp = opendir(path);

	// для поиска папки
	if (fl == 0) {
		if (rnmb == 1) {    // данная папка является искомой?
			rnmb = -1;
		} else {
		   	(rnmb)--;
		}
	}
	
	while (files = readdir(dp)) {    // скан файлов в каталогн folder
		// pathh[len] = '\0';
		if (rnmb < 0) {
			break;
		}
		
    	while(files[0].d_name[0] == '.') {
    		if (!(files = readdir(dp))) {
    			rnmb = -1;
    			break;
			}
		}
		// printf("-------------------rndmfl2-------------------\n");
		pathh = strpls(pathh, path, "/", files->d_name, NULL);
		// printf("%s rndmfl3\n", pathh);
		dp1 = fopen(pathh, "r");
		if (dp1 != NULL) {    // проверка: dp1-файл?
			rnmb -= (fl == 1);
			if (rnmb == 0) {
				rnmb = -1;
				fclose(dp1);
				break;
			}
		} else {
			dp2 = opendir(pathh);
			if (dp2 != NULL) {    // проверка: dp1-папка?
				cfls = cntfls(pathh);
				rnmb1 = (fl == 1)*cfls/MAX + (fl == 0)*(cfls%MAX + 1);
				if (rnmb1 < rnmb) {
					rnmb -= rnmb1;
   				} else {
					if (rnmb > 0) {
						if (rnmb == 1 && fl == 0) {    // данная папка является искомой?
							rnmb = -1;
							break;
						}
						pathh = rndmfl(pathh, cntfls, strpls, rnmb, fl);
						rnmb = -1;
						break;
					}
				}
			}
			closedir(dp2);	
		}
		fclose(dp1);
	}
	closedir(dp);
	return pathh;
}


/*
// выбор действия
int rndmk(void) {
	int k;
	srand(time(NULL));
	k = (rand()%NKD)+1;
	printf("%d", k);
	return k;
}

// выбор файла
char *rndmfl() {
	int cnt;
	char* folder, file;
	DIR *dp, *folder2;
    struct dirent *files;
//    dp = opendir ('./');
	dp = opendir (path);
	// просмотр файлов в каталоге dp
    while (files = readdir (dp)) {
    	// рандомный выбор папки
		srand(time(NULL));
		cnt = rand() % 2;
//		puts (files->d_name);
		if (cnt == 1) {
			folder2 = opendir(path/files);
			if (folder2 != NULL)
				folder = files;
			else
				file = files;
    		closedir(folder2);
		}
	}
    (void) closedir(dp);
    return path;
}

// выбор папки
char *rndmfldr() {
	char *path = {};
	DIR *folder = opendir("../files");
	strcat(path, "../files");
	closedir(folder);
	
	while (cnt == 1 && /* в папке есть папки ) {
		cnt = rand()%2;
		
		DIR *folder = opendir(path);
		// поиск папки fldr в каталоге path, проверкаб является ли fldr пустой папкой
		if (fldr != 0) {
			strcat(path, fldr);
			closedir(folder);
		} else {
			cnt = 0;
		}
		fldr = NULL;
	}
	
	
	closedir(folder);
	return path;
}


*/
