/*
** Life.hpp for B-CPP-501-NAN-5-1-rtype-arthur.bertaud in /home/arthurbertaud/Third_year/R-Type/B-CPP-501-NAN-5-1-rtype-arthur.bertaud/include/Server/Components
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Wed Nov 4 11:38:36 PM 2020 arthurbertaud
** Last update Wed Nov 4 11:38:36 PM 2020 arthurbertaud
*/

#ifndef LIFE_HPP_
#define LIFE_HPP_

#include "IComponents.hpp"

namespace ECS {
    struct Life : public IComponents {
        Life() = default;
        Life(const unsigned int hp);
        Life(const Life& other) = default;
        Life& operator=(const Life& other) = default;
        ~Life() = default;
        unsigned int _hp;
    };
}

#endif /* !LIFE_HPP_ */
