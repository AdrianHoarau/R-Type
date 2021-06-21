/*
** Client.cpp for B-CPP-501-NAN-5-1-rtype-arthur.bertaud in /home/arthurbertaud/Third_year/R-Type/B-CPP-501-NAN-5-1-rtype-arthur.bertaud/include/Server
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Sat Oct 31 4:45:59 PM 2020 arthurbertaud
** Last update Fri Nov 5 8:23:57 AM 2020 arthurbertaud
*/

#include "Client.hpp"

Client::Client(const boost::asio::ip::address& adr, const unsigned short port) : _uuid(boost::uuids::random_generator()()), _endpoint(adr, port), _state(NONE)
{
}

boost::uuids::uuid& Client::getUuid()
{
    return (_uuid);
}

boost::asio::ip::udp::endpoint& Client::getEndpoint()
{
    return (_endpoint);
}

void Client::setState(const Client::clientState state)
{
    _state = state;
}

Client::clientState Client::getState() const
{
    return (_state);
}