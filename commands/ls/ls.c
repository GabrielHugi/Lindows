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
    //console text formatting
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    // https://learn.microsoft.com/pt-br/windows/console/console-screen-buffers#character-attributes
    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    do
    {
        if(strcmp(findData.cFileName, ".") != 0
                && strcmp(findData.cFileName, "..") != 0)
        {
            // if full path then
            //sprintf(pathString, "%s\\%s", dirString, findData.cFileName);
            //else
            sprintf(pathString, "%s", findData.cFileName);
            
            if(findData.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY)
            {         
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                printf("Directory: %s\n", pathString);
                SetConsoleTextAttribute(hConsole, saved_attributes);
                //ls(pathString); activate this at any case idk maybe later i will need for listing everything that falls under the directory
            }
            else{
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
                printf("File: %s\n", pathString);
                SetConsoleTextAttribute(hConsole, saved_attributes);
            }
        }
    }
    while(FindNextFile(fileHandler, &findData));
    return 0;
}

int main (int argc, char** argv) {
    setlocale(LC_ALL, "");
    if (argc == 1) {
        DWORD len = 2048;
        LPTSTR dir;
        GetCurrentDirectory(len, dir);
        ls(dir);
    }
    ls(argv[2]);
}