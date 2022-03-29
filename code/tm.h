#ifndef TM_H
#define TM_H

#include <dirent.h>
#include "cnst.h"

// запись time в history.txt ("tm.h")
void tmpr(const char* message1, const char* message2, int code);

// подсчет файлов, папок в текущем каталоге ("main.c") done
long int cntfls(char *folder);

// склейка строк done
char *strpls (char *str, ...);

// проверка на совпадение имени файлов done
char *namege (char *folder, char *file, char *name);

// создание имени файла
char *namefl (char *name1,
char* (*strpls) (char*, ...),
int (*rndmk) (clock_t, int, int),
clock_t tmbgn);
// // логгер
// void logger(const char* tag, const char* message);

#endif // TM_H
