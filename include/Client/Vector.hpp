/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** Vector.hpp
*/

#ifndef _VECTOR_HPP_
# define _VECTOR_HPP_


struct posVector {
    posVector() = default;
    posVector(const posVector& other) = default;
    posVector& operator=(const posVector& other) = default;
    ~posVector() = default;
    float x;
    float y;
};


#endif