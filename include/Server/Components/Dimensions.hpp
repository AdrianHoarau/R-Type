/*
** Dimensions.hpp for B-CPP-501-NAN-5-1-rtype-arthur.bertaud in /home/arthurbertaud/Third_year/R-Type/B-CPP-501-NAN-5-1-rtype-arthur.bertaud/include/Server/Components
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Tue Nov 10 3:27:15 PM 2020 arthurbertaud
** Last update Tue Nov 10 3:27:15 PM 2020 arthurbertaud
*/

#ifndef DIMENSIONS_HPP_
#define DIMENSIONS_HPP_

#include "IComponents.hpp"

namespace ECS {
    struct Dimensions : public IComponents {
        Dimensions() = default;
        Dimensions(const unsigned int x, const unsigned int y);
        Dimensions(const Dimensions& other) = default;
        Dimensions& operator=(const Dimensions& other) = default;
        ~Dimensions() = default;
        unsigned int _x;
        unsigned int _y;
    };
}

#endif /* !DIMENSIONS_HPP_ */
