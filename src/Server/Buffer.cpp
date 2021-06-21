/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** Buffer.cpp
*/

#include "Buffer.hpp"
#include <boost/uuid/uuid_generators.hpp>

Buffer::Buffer()
{
}

bool Buffer::isDataAvailable(boost::uuids::uuid& uuid) const
{
    if (_sBuffer.find(uuid) != _sBuffer.end() && _sBuffer.find(uuid)->second.size() > 0)
        return (true);
    return (false);
}

std::vector<std::string>& Buffer::getData(boost::uuids::uuid& uuid)
{
    return (_sBuffer[uuid]);
}

void Buffer::addData(boost::uuids::uuid& uuid, const std::string& data)
{
    std::vector<std::string>& buff = _sBuffer[uuid];
    buff.push_back(data);
}