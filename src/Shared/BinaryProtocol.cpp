/*
** EPITECH PROJECT, 2020
** client
** File description:
** BinaryProtocol
*/

#include "BinaryProtocol.hpp"

bool BinaryProtocol::Packet::operator==(const Packet& other) const
{
    return ((_magicNumber == other._magicNumber)
    && (_message == other._message));
}

BinaryProtocol::Codec::Codec()
{
}

BinaryProtocol::Packet BinaryProtocol::Codec::createPacket(const std::string& message)
{
    Packet ret;

    ret._magicNumber = MAGIC_NUMBER;
    ret._message = message;
    return (ret);
}

bool BinaryProtocol::Codec::check_packet(const Packet& toCheck)
{
    return (toCheck._magicNumber == MAGIC_NUMBER);
}

std::vector<uint8_t> BinaryProtocol::Codec::serialize(const Packet& input)
{
    std::size_t str_size = input._message.size();
    int index = 0;
    std::vector<uint8_t> output;
    unsigned int packet_size = sizeof(input._magicNumber) +
        (str_size * (sizeof(char) * sizeof(str_size)));

    output.resize(packet_size);

    memcpy(output.data(), &(input._magicNumber), sizeof(input._magicNumber));
    index += static_cast<int>(sizeof(input._magicNumber));

    memcpy(output.data() + index, &str_size, sizeof(str_size));
    index += static_cast<int>(sizeof(str_size));

    memcpy(output.data() + index, input._message.data(), str_size * sizeof(char));
    index += static_cast<int>(str_size * sizeof(char));

    return (output);
}

BinaryProtocol::Packet BinaryProtocol::Codec::unserialize(const boost::array<uint8_t, 1024>& input)
{
    Packet output;
    int index = 0;
    std::size_t str_size = 0;

    memcpy(&(output._magicNumber), input.data(), sizeof(output._magicNumber));
    index += static_cast<int>(sizeof(output._magicNumber));

    memcpy(&str_size, input.data() + index, sizeof(str_size));
    index += static_cast<int>(sizeof(str_size));

    output._message.resize(str_size);
    memcpy((char *)output._message.data(), input.data() + index, str_size * sizeof(char));

    return(output);
}

