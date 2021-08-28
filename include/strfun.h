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

/*
 * Assorted string functions.
 */

#ifndef STRFUN_H
#define STRFUN_H

/**
 * Convert the first character of a string to upper case.
 * @param destination Converted string.
 * @param source String to convert.
 */
char* firstCharToUpper(char* destination, char* source);

/**
 * Convert a string to lower case.
 * @param destination String to store the result in.
 * @param source String to convert.
 * @param num Maximum number of characters to copy to the destination.
 */
char* convertToLower(char* destination, char* source, int num);

/**
 * Test whether one string begins with another.
 * @param string String to test.
 * @param target Target string to search for.
 */
int startsWith(char* string, char* target);

/**
 * Trim whitespace surrounding a string.
 * @param str String to trim.
 */
char* trim(char* str);

#endif
