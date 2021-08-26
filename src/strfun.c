/*
 * Apocrypha, a text adventure game engine
 * Copyright (C) 2021 David Heinemann
 * 
 * This file is part of Apocrypha.
 *
 * Apocrypha is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Apocrypha is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Apocrypha. If not, see <https://www.gnu.org/licenses/>.
 */

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
