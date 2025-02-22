#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>

int main (int argc, char** argv) {
    setlocale(LC_ALL, "");
    FILE* fileptr;
    struct optionsBitField {
        unsigned a:1;
        unsigned m:1;
        unsigned c:1;
        unsigned t:1;
        unsigned h:1;
        unsigned r:1;
        unsigned d:1;
        unsigned any:1;
    } modifiers;
    modifiers.a = 0; modifiers.m = 0; modifiers.c = 0; modifiers.t = 0; modifiers.h = 0; modifiers.r = 0; modifiers.d = 0; modifiers.any = 0;
    short modnum = 0;
    // getting the modifiers cuz touch touches in different ways
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'a' && strlen(argv[i]) >= 2) {
                modifiers.a = 1;
                modifiers.any = 1;
                modnum++;
            }
            if (argv[i][1] == 'm' && strlen(argv[i]) >= 2) {
                modifiers.m = 1;
                modifiers.any = 1;
                modnum++;
            }
            if (argv[i][1] == 'm' && argv[i][2] == 'a' && strlen(argv[i]) >= 3) {
                modifiers.a = 1;
                modifiers.m = 1;
                modifiers.any = 1;
                modnum++;
            }
            if (argv[i][1] == 'a' && argv[i][2] == 'm' && strlen(argv[i]) >= 3) {
                modifiers.a = 1;
                modifiers.m = 1;
                modifiers.any = 1;
                modnum++;
            }
            if (argv[i][1] == 'c' && strlen(argv[i]) >= 2) {
                modifiers.c = 1;
                modifiers.any = 1;
                modnum++;
            }
            if (argv[i][1] == 't' && strlen(argv[i]) >= 2) {
                modifiers.t = 1;
                modifiers.any = 1;
                modnum++;
            }
            if (argv[i][1] == 'h' && strlen(argv[i]) >= 2) {
                modifiers.h = 1;
                modifiers.any = 1;
                modnum++;
            }
            if (argv[i][1] == 'r' && strlen(argv[i]) >= 2) {
                modifiers.r = 1;
                modifiers.any = 1;
                modnum++;
            }
            if (argv[i][1] == 'd' && strlen(argv[i]) >= 2) {
                modifiers.d = 1;
                modifiers.any = 1;
                modnum++;
            }
        }
    }
    // now the real deal
    for (int i = 1; i < argc; i++) {
            if (modifiers.any == 0) {
                for (int i = 1; i < argc; i++) {
                    fileptr = fopen(argv[i], "w");
                    fclose(fileptr);
                }
            }
            else {
            if (modifiers.a == 1 && modifiers.m != 1) {
                for (int i = 1+modnum; i < argc; i++) {
                    fileptr = fopen(argv[i], "r");
                    if (fileptr == NULL) fopen(argv[i], "w");
                    fclose(fileptr);
                    struct stat tm;
                    struct utimbuf newtime;
                    stat(argv[i], &tm);
                    newtime.actime = time(NULL);
                    newtime.modtime = tm.st_mtime;
                    utime(argv[i], &newtime);
                }

            }
            if (modifiers.m == 1 && modifiers.a != 1) {
                for (int i = 1+modnum; i < argc; i++) {
                    fileptr = fopen(argv[i], "r");
                    if (fileptr == NULL) fopen(argv[i], "w");
                    fclose(fileptr);
                    struct stat tm;
                    struct utimbuf newtime;
                    stat(argv[i], &tm);
                    newtime.actime = tm.st_atime;
                    newtime.modtime = time(NULL);
                    utime(argv[i], &newtime);
                    fclose(fileptr);
                }
            }
            if (modifiers.a == 1 && modifiers.m == 1) {
                for (int i = 1+modnum; i < argc; i++) {
                    fileptr = fopen(argv[i], "r");
                    if (fileptr == NULL) fopen(argv[i], "w");
                    fclose(fileptr);
                    struct stat tm;
                    struct utimbuf newtime;
                    stat(argv[i], &tm);
                    newtime.actime = tm.st_atime;
                    newtime.modtime = tm.st_mtime;
                    utime(argv[i], &newtime);
                    fclose(fileptr);
                }
            }
            if (modifiers.c == 1) {
                
            }
            if (modifiers.t == 1) {
                
            }
            if (modifiers.h == 1) {
                
            }
            if (modifiers.r == 1) {
                
            }
            if (modifiers.d == 1) {
                
            }
        }
    }

    //fileptr = fopen(argv[1], "a");
    //fprintf(fileptr, result);
    //fclose(fileptr);
}