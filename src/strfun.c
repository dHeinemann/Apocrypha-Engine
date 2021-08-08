#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "limits.h"

char* convertToLower(char* destination, char* source, int num)
{
    int i;

    strncpy(destination, source, num);
    for (i = 0; i < (int) strlen(destination); i++)
    {
        if (isupper(destination[i]))
        {
            destination[i] = tolower(destination[i]);
        }
    }

    return destination;
}

char* firstCharToUpper(char* destination, char* source)
{
    if (source == NULL)
    {
        destination = NULL;
    }
    else if (strlen(source) == 0)
    {
        destination = "";
    }
    else
    {
        strncpy(destination, source, NPC_NAME_MAX_LENGTH);
        if (islower(destination[0]))
            destination[0] = toupper(destination[0]);
    }

    return destination;
}

int startsWith(char* string, char* target)
{
    return strncmp(string, target, strlen(target)) == 0;
}

char* trim(char* str)
{
    int i;

    /* Trim start */
    for (i = 0; (size_t) i < strlen(str); i++)
    {
        if (!isspace(str[i]))
            break;
        str++;
    }

    /* Trim end */
    for (i = (int) strlen(str) - 1; i >= 0; i--)
    {
        if (!isspace(str[i]))
            break;
        str[i] = '\0';
    }

    return str;
}
