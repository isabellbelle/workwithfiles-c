#include "tm.h"
#include "rndm.h"
#include "repls.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
// #include <stdarg.h>
#include <dirent.h>

// запись time в history.txt ("tm.h")
void tmpr(const char* message1, const char* message2, int code) {

	time_t t = time(NULL);
	struct tm *tml = localtime(&t);
	FILE *file = fopen("../history.txt", "a");
	fprintf(file, "%-5d | %35s | %35s | %02d/%02d/%02d %02d:%02d:%02d\n", code, message1, message2, tml[0].tm_mday, tml[0].tm_mon + 1, tml[0].tm_year % 100,
	tml[0].tm_hour, tml[0].tm_min, tml[0].tm_sec);
//	printf("%02d/%02d/%02d %02d:%02d:%02d (%01d %03d %01d)\n", tml->tm_mday, tml->tm_mon + 1, tml->tm_year % 100,
//	tml->tm_hour, tml->tm_min, tml->tm_sec, tml->tm_wday, tml->tm_yday + 1, tml->tm_isdst);
	fclose(file);
}

// подсчет всех файлов и папок в каталоге done
long int cntfls(char *folder) {

	int nfls = 0, nflds = 0, b = 1; // количество файлов, папок в текущем каталоге, показатель ".*" папок
	long int cnt = 0;
	char *scan, *path = folder, path1[100]; // проверяемый объект, путь к текущей папке, путь до scan
	DIR *dp, *dp2; // текущая папка, проверочная папка
	FILE *dp1; // проверочный файл
    struct dirent *files; // файлы в текущем каталоге
	dp = opendir (path);
	// просмотр файлов в каталоге dp
    while (files = readdir(dp)) {
    	// исключение "." и ".." папок
    	while (b == 1 && files->d_name[0] == '.') {
    	 	if (!(files = readdir(dp))) {
    	 		b = 0;
			}
    	}
    	if (b) {
//    	if (files->d_name != NULL) {
			// создание пути для проверки файла
			scan = files->d_name;
			int len = 0, lenn = 0;
			while(path[len] != 0) {
				path1[len] = path[len];
				len++;
			}
			path1[len] = '/';
				len++;
			while(scan[lenn] != 0) {
				path1[len] = scan[lenn];
				lenn++;
				len++;
			}
			
			path1[len] = '\0';
			// конец создания пути для проверки файла
			dp1 = fopen(path1, "r");
			if (dp1 != NULL) {
				nfls++;
			} else {
				dp2 = opendir(path1);
				if (dp2 != NULL)
					nflds++;
				closedir(dp2);
				if (files->d_name != NULL) {
				 cnt = cntfls(path1);
				 nfls += cnt/MAX;
				 nflds += cnt%MAX;
			}
			}
			fclose(dp1);
		}
	}
    closedir(dp);
    return MAX*nfls + nflds;
}

// склейка строк done
char* strpls (char *str, ...) {

	char **cp = &str + 1;
	int len = 0;
	str = (char*)malloc(sizeof(char));
	str[0] = '\0';
	while (*cp != NULL) {
		// printf("while\n");
		// printf("%s strpls2\n", *cp);
		len += strlen(*cp);
		str = (char*)realloc(str, (len + 1)*sizeof(char));
		strcat(str, *cp);
		// str[len] = '\0';
		cp++;
		// printf("%s strpls3\n", str);
	}
	return str;
}

// проверка на совпадение имени файлов done
char *namege (char *folder, char *file, char *name1) {
	int cnt = 0, // количестко файлов с именем вида a1.txt/a1[2].txt/a1[15].txt для file == a1.txt,
	len = 0, // индекс последнего элемента имени файла ( до '[' ) file без расширения (не const),
	len1, // индекс последнего элемента имени файла ( до '[' ) file без расширения (const)
	num = 0, num1 = 0, j = 0, slnfl, // a1[num].txt num для name, num для file, счетчик, индекс последнего элемента имени файла file,
	slnnm, save = 1; // индекс последнего элемента имени файла name папки folder, показатель наличия name: name == file

	int *nmbr = (int*)malloc(10*sizeof(int));
	char *name, *rash = (char*)malloc(10*sizeof(char));
	rash[0] = '\0';
	DIR *dr = opendir(folder);
	struct dirent *names; // файлы в текущем каталоге
	slnfl = strlen(file) - 1;

	while ((file[len] != '.') && (file[len] != '[') && (len <= slnfl))
		len++; // индекс '.', '[' или '\0'
	len1 = len - 1; // индекс символа перед '['
	name1 = strpls(name1, file, NULL);
	name1[len] = '\0';

	if (file[len] == '[') { // проверка имени файла на вид *[num].*
		len++;
		while (file[len] != ']') {
			num1 = 10*num1 + file[len] - '0';
			len++;
		}
		len++; // индекс '.'
	}
	j = 0;
	if (file[len] == '.') { // проверка наличия точки в имени файла
		while (file[len] != '\0') {
			// rash = (char*)realloc(rash, (j + 2)*sizeof(char));
			rash[j] = file[len];
			j++;
			len++; // индекс '\0'
		}
		rash[j] = '\0';
	}

	len = len1;


	while (names = readdir(dr)) {
		name = names->d_name;
		if (strcmp(file, name) == 0) {
			save = 0;
			cnt++;
			if (num1 == 0)
				nmbr[cnt - 1] = 1;
			else
				nmbr[cnt - 1] = num1;
		} else {
			if ((strcmp(name, name1) == 1) && ((name[len1 + 1] == '[') || (name[len1 + 1] == '.'))) {
				slnnm = strlen(name) - 1;
				len = slnfl;
				j = slnnm;
				int sv = 0;
				while((name[j] == file[len]) && j && len) { // создание проверки совпадения расширений file и name
					j--, len--;
					if (name[j] == '.') {
						sv = 1;
						break;
					}
				}
				if (sv) { // проверка совпадения расширений file и name
					len = len1;
					cnt++;
					nmbr = (int*)realloc(nmbr, cnt*sizeof(int));
					len += 2;
					num = 0;
					if (name[len1 + 1] == '[') {
						while (name[len] != ']') {
							num = 10*num + (int)(name[len] - '0');
							len++;
						}
					} else {
						num = 1;
					}
					nmbr[cnt - 1] = num;
				}
			}
		}
	}
	if (save == 0 || num1 != 0) {
		int *fndnm = (int*)malloc(cnt*sizeof(int));
		// fndnm[cnt] = {1};
		for(j = 0; j < cnt; j++)
			fndnm[j] = 1;
		for(int j = 0; j < cnt; j++)
			if (nmbr[j] <= cnt)
				fndnm[nmbr[j] - 1] = -1;
		j = 0;
		while ((fndnm[j] == -1) && (j < cnt))
			j++;
		if (j == 0) {
			name1 = strpls(name1, name1, rash, NULL);
		} else {
			free(fndnm);
			char nm[10];
			// itoa(cnt, nm, 10);
			sprintf(nm, "%d", j + 1);
			name1 = strpls(name1, name1, "[", nm, "]", rash, NULL);
		}
	} else {
		free(name1);
		name1 = strpls(name1, file, NULL);
	}
	free(rash);
	free(nmbr);
	closedir(dr);
	return name1;
}


// создание имени файла
char *namefl (char *name1,
char* (*strpls) (char*, ...),
int (*rndmk) (clock_t, int, int),
clock_t tmbgn) {

	int j = 2, len;
	len = rndmk(tmbgn, 3, j) + 2;
	j = rndmk(tmbgn, len - 1, j) + 1; // индекс первой цифры в name1
	name1 = (char*)malloc(len*sizeof(char));
	for (int i = 0; i < j; i++)
		name1[i] = 'a' + rndmk(tmbgn, 26, i);
	for (int i = j; i < len; i++)
		name1[i] = '1' + rndmk(tmbgn, 9, i);
	name1[len] = '\0';
	// name1 = strpls(name1, name1, ".txt", NULL);
	return name1;
}







// // логгер
// void logger(const char* tag, const char* message) {
//    time_t now;
//    time(&now);
//    FILE *file = fopen(FILELOG, "a");
//    fprintf(file, "%s [%s]: %s", ctime(&now), tag, message);
//    fclose(file);
// }
