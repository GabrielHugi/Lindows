#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int ls (char* dirString) {

}

int main (int argc, char** argv) {
    setlocale(LC_ALL, "");
    WIN32_FIND_DATA findData;
    HANDLE fileHandler = NULL;

    char pathString[2048];
    char dirString[2048];
    // for now for testing n shit
    sprintf(dirString, "%s", "C:\\Users\\20240192\\Downloads");
    sprintf(pathString, "%s\\*.*", dirString);

    if((fileHandler = FindFirstFile(pathString, &findData)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found: [%s]\n", dirString);
        return 0;
    }
}