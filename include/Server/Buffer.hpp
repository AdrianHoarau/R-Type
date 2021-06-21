/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Buffer.hpp
*/


#ifndef BUFFER_HPP_
#define BUFFER_HPP_

#include <vector>
#include <string>
#include <map>
#include <boost/uuid/uuid.hpp>

class Buffer
{
public:
    Buffer();
    Buffer(const Buffer& other) = default;
    Buffer& operator=(const Buffer& other) = default;
    void addData(boost::uuids::uuid& uuid, const std::string& data);
    std::vector<std::string>& getData(boost::uuids::uuid& uuid);
    bool isDataAvailable(boost::uuids::uuid& uuid) const;
    ~Buffer() = default;
private:
    std::map<boost::uuids::uuid, std::vector<std::string>> _sBuffer;
};

#endif /* !BUFFER_HPP_ */
