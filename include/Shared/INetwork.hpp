/*
** EPITECH PROJECT, 2020
** B-CPP-501-NAN-5-1-rtype-arthur.bertaud
** File description:
** INetwork.hpp
*/


#ifndef INETWORK_HPP_
#define INETWORK_HPP_

#include <boost/system/error_code.hpp>

class INetwork {
    public:
        virtual ~INetwork() = default;
        virtual void start() = 0;
        virtual void stop() = 0;
    protected:
    private:
        virtual void startReceive() = 0;
        virtual void send(const std::string&) = 0;
        virtual void handleReceive(const boost::system::error_code&, std::size_t) = 0;
};

#endif /* !INETWORK_HPP_ */
