/*
** EPITECH PROJECT, 2020
** Codec
** File description:
** BinaryCodec
*/

#ifndef BINARYCODEC_HPP_
#define BINARYCODEC_HPP_

#include <iostream>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <iomanip>

#include <boost/array.hpp>
#include <boost/asio.hpp>

#define MAGIC_NUMBER 4242

namespace BinaryProtocol
{
    struct Packet
    {
        bool operator==(const Packet& other) const;
        uint32_t _magicNumber;
        std::string _message;
    };

    class Codec
    {
        public:
            Codec();
            ~Codec() = default;
            Codec(const Codec& other) = default;
            Codec& operator=(const Codec& other) = default;
            Packet createPacket(const std::string& message);
            bool check_packet(const Packet& toCheck);
            std::vector<uint8_t> serialize(const Packet& input);
            Packet unserialize(const boost::array<uint8_t, 1024>& input);
    };
}

#endif /* !BINARYCODEC_HPP_ */
