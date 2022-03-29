#ifndef RNDM_H
#define RNDM_H

#include <time.h> // для clock_t
#include "cnst.h"

// рандом done
int rndmk(clock_t tmbgn, int n, int j);

// выбор действия
int rndmd(int (*rndmk) (clock_t, int, int), clock_t tmbgn, int j);

	/* рандомный выбор файла / папки (начальный путь path; cntfls(path); склейка нужный строк;
	рандом для выбора искомого пуми; fl == 0 => поиск папки, fl == 1 => поиск файла */
char *rndmfl(char *folder, //done
long int (*cntfls) (char*),
char* (*strpls) (char*, ...),
int rnmb, int fl);

#endif // RNDM_H
