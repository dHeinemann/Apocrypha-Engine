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

#ifndef ERROR_H
#define ERROR_H

/*
 * Represents a type of error that has occurred.
 */
enum Error
{
    ERROR_NONE,

    /* An argument's length is too long or too short. */
    ERROR_INVALID_ARGUMENT_LENGTH,

    /* MALLOC failed due to lack of memory. */
    ERROR_OUT_OF_MEMORY
};

/*
 * Convert an error number to a string.
 */
char* errorToString(enum Error error);

#endif
