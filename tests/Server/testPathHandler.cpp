/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** testPathHandler.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "pathHandler.hpp"
#include <iostream>

Test(testIsDirValid, pathHandler)
{
    pathHandler hdl(pathType::DIR);

    hdl.setPath("noexistantdirectory/");
    cr_assert_eq(hdl.isDirValid(), false);
}

Test(testIsFileValid, pathHandler)
{
    pathHandler hdl(pathType::REGULAR_FILE);

    hdl.setPath("noexistantfile");
    cr_assert_eq(hdl.isFileValid(), false);
}

Test(testGetPath, pathHandler)
{
    pathHandler hdl(pathType::DIR);

    hdl.setPath("noexistantdirectory/");
    cr_assert_eq(strcmp(hdl.getPath().c_str(), "noexistantdirectory/"), 0);
}

Test(testDefaultDirPath, pathHandler)
{
    pathHandler hdl(pathType::DIR);

    cr_assert_eq(strcmp(hdl.getPath().c_str(), "./lib/"), 0);
}

Test(testDefaultFilePath, pathHandler)
{
    pathHandler hdl(pathType::REGULAR_FILE);

    cr_assert_eq(strcmp(hdl.getPath().c_str(), "../config.txt"), 0);
}