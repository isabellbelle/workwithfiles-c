#ifndef CODE_REPLS_H
#define CODE_REPLS_H
#include "cnst.h"

#include "tm.h"
#include "rndm.h"

// // копия файла
// void cp(void);

// перемещение done
int repls (long int (*cntfls) (char*),
char* (*strpls) (char*, ...),
char* (*rndmfl) (char*, long int (*)(char *), char* (*)(char *, ...), int, int),
int (*rndmk) (clock_t, int, int),
void (*tmpr) (const char*, const char*, int),
char* (*namege) (char*, char*, char*),
int *nfl, int *nfldr, clock_t tmbgn);


// переимен-е файла
int renm(long int (*cntfls) (char*),
char* (*strpls) (char*, ...),
char* (*rndmfl) (char*, long int (*)(char *), char* (*)(char *, ...), int, int),
int (*rndmk) (clock_t, int, int),
void (*tmpr) (const char*, const char*, int),
char* (*namege) (char*, char*, char*),
char* (*namefl) (char*, char* (*) (char*, ...), int (*) (clock_t, int, int), clock_t),
int *nfl, int *nfldr, clock_t tmbgn);


// создание *.txt файла done
int add(long int (*cntfls) (char*),
char* (*strpls) (char*, ...),
char* (*rndmfl) (char*, long int (*)(char *), char* (*)(char *, ...), int, int),
int (*rndmk) (clock_t, int, int),
void (*tmpr) (const char*, const char*, int),
char* (*namege) (char*, char*, char*),
char* (*namefl) (char*, char* (*) (char*, ...), int (*) (clock_t, int, int), clock_t),
int *nfl, int *nfldr, clock_t tmbgn);


// удаление файла done
int dlt(long int (*cntfls) (char*),
char* (*strpls) (char*, ...),
char* (*rndmfl) (char*, long int (*)(char *), char* (*)(char *, ...), int, int),
int (*rndmk) (clock_t, int, int),
void (*tmpr) (const char*, const char*, int),
int *nfl, int *nfldr, clock_t tmbgn);


#endif // CODE_REPLS_H
