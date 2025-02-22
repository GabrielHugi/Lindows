#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, char** argv) {
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
    // getting the modifiers cuz touch touches in different ways
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'a') {
                modifiers.a = 1;
                modifiers.any = 1;
            }
            if (argv[i][2] == 'a') {
                modifiers.a = 1;
                modifiers.any = 1;
            }
            if (argv[i][1] == 'm') {
                modifiers.m = 1;
                modifiers.any = 1;
            }
            if (argv[i][2] == 'm') {
                modifiers.m = 1;
                modifiers.any = 1;
            }
            if (argv[i][1] == 'c') {
                modifiers.c = 1;
                modifiers.any = 1;
            }
            if (argv[i][1] == 't') {
                modifiers.t = 1;
                modifiers.any = 1;
            }
            if (argv[i][1] == 'h') {
                modifiers.h = 1;
                modifiers.any = 1;
            }
            if (argv[i][1] == 'r') {
                modifiers.r = 1;
                modifiers.any = 1;
            }
            if (argv[i][1] == 'd') {
                modifiers.d = 1;
                modifiers.any = 1;
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
                
            }
            if (modifiers.m == 1 && modifiers.a != 1) {

            }
            if (modifiers.a == 1 && modifiers.m == 1) {

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