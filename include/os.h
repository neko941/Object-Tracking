#ifndef __OS_H__
#define __OS_H__

#include <stdio.h>
#include <direct.h> // mkdir
#include <dirent.h>
#include <sys/stat.h> // check is dir exist

#include "./stringplus.h"
#include "./print.h"

char *_separator()
{
#ifdef _WIN32
    return "\\";
#else
    return "/";
#endif
}

int pathExists(char *path)
{
    struct stat sb;
    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        success(stringConcatenate("******************** Path exists: ", path));
        puts("\n");
        return 1;
    }
    else
    {
        printf("******************** Path not exists: %s\n", path);
        return 0;
    }
}

void makeDir(char *path)
{
    if (!pathExists(path))
    {
        if (!mkdir(path))
        {
            success(stringConcatenate("******************** Directory created: ", path));
            puts("\n");
        }
        else
        {
            error(stringConcatenate("Unable to create directory: ", path));
        }
    }
}

char *getFileName(char *path)
{
    char *p;
    for (p = path; *p; p++)
    {
        if (*p == '/' || *p == '\\' || *p == ':')
        {
            return ++p;
        }
    }
}

char *pathJoin(char *path1, char *path2)
{
    return stringConcatenate(stringConcatenate(path1, _separator()), path2);
}

char **listAllFiles(char *path, int *length)
{
    char resultTemp[1000][1000];
    char temp[1000];
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    *length = 0;
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (dir->d_type == DT_REG)
            {
                strcat(resultTemp[(*length)++], dir->d_name);
            }
        }
        closedir(d);
    }

    char **result = c_arrayNew_2d(*length, 100);
    for (int i = 0; i < *length; i++)
    {
        strcpy(result[i], resultTemp[i]);
    }

    // for (int i = 0; i < count; ++i)
    // {
    //     for (int j = i + 1; j < count; ++j)
    //     {

    //         // swapping strings if they are not in the lexicographical order
    //         if (strcmp(resultTemp[i], resultTemp[j]) > 0)
    //         {
    //             strcpy(temp, resultTemp[i]);
    //             strcpy(resultTemp[i], resultTemp[j]);
    //             strcpy(resultTemp[j], temp);
    //         }
    //     }
    // }
    // for (int i = 0; i < *length; i++)
    // {
    //     printf("%s\n", result[i]);
    // }
    return result;
}

#endif