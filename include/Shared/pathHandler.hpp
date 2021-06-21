/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** pathHandler.hpp
*/

#ifndef PATHHANDLER_HPP_
#define PATHHANDLER_HPP_

#include <string>

enum pathType {
    REGULAR_FILE,
    DIR
};

class pathHandler {
    public:
        pathHandler(const pathType& type);
        pathHandler(const pathHandler& other) = default;
        pathHandler& operator=(const pathHandler& other) = default;
        bool isDirValid() const;
        bool isFileValid() const;
        void setPath(const std::string& path);
        std::string getPath() const;
        ~pathHandler() = default;
    private:
        std::string _path;
};

#endif /* !PATHHANDLER_HPP_ */
