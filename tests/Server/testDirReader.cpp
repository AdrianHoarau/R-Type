/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** testDirReader.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "dirReader.hpp"
#include <iostream>

Test(testDirError, dirReader)
{
    try {
        dirReader dReader("unexistantfile");
    }
    catch (Error &e) {
        cr_assert(std::strcmp(e.what(), "Error: the path given as argument isn't a directory.") == 0);
    }
}