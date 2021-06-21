/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** dirReader.hpp
*/
#ifndef dirReader_HPP_
#define dirReader_HPP_
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include "Error.hpp"
class dirReader {
    public:
        dirReader(const std::string& name);
        dirReader(const dirReader& other) = default;
        dirReader& operator=(const dirReader& other) = default;
        ~dirReader() = default;
        std::vector<std::string> findLibraries();
    private:
        std::string _path;
        void pushLibPath(const std::string& name, std::vector<std::string>& libPaths);
};
#endif /* !dirReader_HPP_ */
