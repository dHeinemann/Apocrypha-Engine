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

char* firstCharToUpper(char* in, char* out)
{
    if (in == NULL)
    {
        out = NULL;
    }
    else if (strlen(in) == 0)
    {
        out = "";
    }
    else
    {
        strncpy(out, in, MOB_NAME_MAX_LENGTH);
        if (islower(out[0]))
            out[0] = toupper(out[0]);
    }

    return out;
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
