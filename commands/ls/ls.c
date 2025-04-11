#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int ls (char* dirString) {
    WIN32_FIND_DATA findData;
    HANDLE fileHandler = NULL;

    char pathString[2048];
    sprintf(pathString, "%s\\*.*", dirString);

    if((fileHandler = FindFirstFile(pathString, &findData)) == INVALID_HANDLE_VALUE)
    {
        printf("Path not found: [%s]\n", dirString);
        return 0;
    }
    do
    {
        if(strcmp(findData.cFileName, ".") != 0
                && strcmp(findData.cFileName, "..") != 0)
        {
            sprintf(pathString, "%s\\%s", dirString, findData.cFileName);

            if(findData.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {
                printf("Directory: %s\n", pathString);
                ls(pathString);
            }
            else{
                printf("File: %s\n", pathString);
            }
        }
    }
    while(FindNextFile(fileHandler, &findData));
}

int main (int argc, char** argv) {
    setlocale(LC_ALL, "");
    ls("C:\\Users\\20240192\\Downloads");
}