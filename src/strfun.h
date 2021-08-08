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
