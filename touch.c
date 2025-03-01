#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>

/*
Linux terminal command "touch" ported to windows
Tell me if I missed some feature
This code is under the GNU General Public Liscense, meaning, in short, that you can basically do wathever as long as you give credits
UTF-8
*/

int main (int argc, char** argv) {
    setlocale(LC_ALL, "");
    FILE* fileptr;
    struct optionsBitField {
        unsigned a:1;
        unsigned m:1;
        unsigned c:1;
        unsigned t:1;
        unsigned h:1;
        // maybe im stupid but it seems to me that h for windows is pratically just a and m so I will ignore, but if that is stupid please tell me 
        // for this reason will make it work as help ig
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
            // help
            if (argc == 1 || modifiers.h == 1) {
                printf("help")
                return 1;
            }
            if (modifiers.any == 0) {
                for (int i = 1; i < argc; i++) {
                    fileptr = fopen(argv[i], "w");
                    fclose(fileptr);
                }
            }
            else {
            if ((modifiers.a == 1 && modifiers.t != 1) || (modifiers.m == 1 && modifiers.t != 1)) {
                for (int i = 1+modnum; i < argc; i++) {
                    fileptr = fopen(argv[i], "r");
                    if (fileptr == NULL && modifiers.c == 0) { 
                        fileptr = fopen(argv[i], "w");
                    }
                    if (fileptr != NULL) {
                        fclose(fileptr);
                        struct stat tm;
                        struct utimbuf newtime;
                        stat(argv[i], &tm);
                        if (modifiers.a == 1) {
                            newtime.actime = time(NULL);
                            newtime.modtime = tm.st_mtime;
                        }
                        if (modifiers.m == 1) {
                            newtime.actime = tm.st_atime;
                            newtime.modtime = time(NULL);
                        }
                        if (modifiers.m == 1 && modifiers.a ==1) {
                            newtime.actime = tm.st_atime;
                            newtime.modtime = tm.st_mtime;
                        }
                        utime(argv[i], &newtime);
                    }
                }

            }
            if (modifiers.t == 1) {
                int pos = 1+modnum;
                int size = strlen(argv[pos]);
                short year = 2000, month = 0, day = 0, hour = 0, minute = 0, second = 0;
                time_t epochconv;
                struct tm resulttime;
                struct stat tmm;
                stat(argv[pos+1], &tmm);
                struct utimbuf sendtime;
                if (pos < argc) {
                    //MMddhhmm 
                    if(size == 8) {
                        month += (argv[pos][0]-48)*10; month += (argv[pos][1]-48);
                        day += (argv[pos][2]-48)*10; day += (argv[pos][3]-48);
                        hour += (argv[pos][4]-48)*10; hour += (argv[pos][5]-48);
                        minute += (argv[pos][6]-48)*10; minute += (argv[pos][7]-48);
                    }
                    if (size > 8) {
                        // [yy] || [[cc]yy] || full
                        if (argv[pos][0] = '[') {
                            // [[cc]yy]
                            if (argv[pos][1] = '[') {
                                // full
                                if (size == 21) {
                                    year = (argv[pos][2]-48) * 1000; year += (argv[pos][3]-48) * 100;
                                    year += (argv[pos][5]-48)*10; year += (argv[pos][6]-48);
                                    month += (argv[pos][8]-48)*10; month += (argv[pos][9]-48);
                                    day += (argv[pos][10]-48)*10; day += (argv[pos][11]-48);
                                    hour += (argv[pos][12]-48)*10; hour += (argv[pos][13]-48);
                                    minute += (argv[pos][14]-48)*10; minute += (argv[pos][15]-48);
                                    second += (argv[pos][18]-48)*10; second += (argv[pos][19]-48);
                                }
                            }
                            else {
                                // [yy] + [.ss]
                                if (size == 17) {
                                    year += (argv[pos][1]-48)*10; year += (argv[pos][2]-48);
                                    month += (argv[pos][4]-48)*10; month += (argv[pos][5]-48);
                                    day += (argv[pos][6]-48)*10; day += (argv[pos][7]-48);
                                    hour += (argv[pos][8]-48)*10; hour += (argv[pos][9]-48);
                                    minute += (argv[pos][10]-48)*10; minute += (argv[pos][11]-48);
                                    second += (argv[pos][14]-48)*10; second += (argv[pos][15]-48);
                                }
                                //[yy]
                                if (size == 12) {
                                    year += (argv[pos][1]-48)*10; year += (argv[pos][2]-48);
                                    month += (argv[pos][4]-48)*10; month += (argv[pos][5]-48);
                                    day += (argv[pos][6]-48)*10; day += (argv[pos][7]-48);
                                    hour += (argv[pos][8]-48)*10; hour += (argv[pos][9]-48);
                                    minute += (argv[pos][10]-48)*10; minute += (argv[pos][11]-48);
                                }
                            }
                        }
                        // [.ss]
                        else if(size == 13) {
                            month += (argv[pos][0]-48)*10; month += (argv[pos][1]-48);
                            day += (argv[pos][2]-48)*10; day += (argv[pos][3]-48);
                            hour += (argv[pos][4]-48)*10; hour += (argv[pos][5]-48);
                            minute += (argv[pos][6]-48)*10; minute += (argv[pos][7]-48);
                            second += (argv[pos][10]-48)*10; second += (argv[pos][11]-48);
                        }
                    }
                }
                resulttime.tm_year = year-1900;
                resulttime.tm_mon = month-1;
                resulttime.tm_mday = day;
                if (hour == 24) hour = 0;
                resulttime.tm_hour = (hour-1);
                resulttime.tm_min = minute;
                resulttime.tm_sec = second;
                resulttime.tm_isdst = -1;
                epochconv = mktime(&resulttime);
                // I dont know if this is how it works on linux im just guessing but either way it
                // seems like good behavior to me and im too lazy to hop off windows to test it out
                if (modnum == 1) { //means this is the only mod
                sendtime.actime = epochconv;
                sendtime.modtime = epochconv;
                }
                if (modifiers.a == 1) {
                    sendtime.actime = epochconv;
                    sendtime.modtime = tmm.st_mtime;
                }
                if (modifiers.m == 1) {
                    if (modifiers.a != 1) sendtime.actime = tmm.st_atime;
                    sendtime.modtime = epochconv;
                }
                utime(argv[pos+1], &sendtime);
            }
            if (modifiers.r == 1) {
                for (int i = 1+modnum; i < argc; i++) {
                    fileptr = fopen(argv[i], "r");
                    if (fileptr == NULL && modifiers.c == 0) { 
                        fileptr = fopen(argv[i], "w");
                    }
                    if (fileptr != NULL) {
                        fclose(fileptr);
                        struct stat tm;
                        struct utimbuf newtime;
                        stat(argv[i], &tm);
                        if (modifiers.a == 1) {
                            newtime.actime = time(NULL);
                            newtime.modtime = tm.st_mtime;
                        }
                        if (modifiers.m == 1) {
                            newtime.actime = tm.st_atime;
                            newtime.modtime = time(NULL);
                        }
                        if (modifiers.m == 1 && modifiers.a ==1) {
                            newtime.actime = tm.st_atime;
                            newtime.modtime = tm.st_mtime;
                        }
                        utime(argv[i], &newtime);
                    }
                }
            }
            if (modifiers.d == 1) {
                
            }
        }
    }
}