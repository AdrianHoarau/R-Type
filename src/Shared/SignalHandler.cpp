/*
** EPITECH PROJECT, 2020
** client
** File description:
** SignalHandler
*/

#include "SignalHandler.hpp"

bool isInterrupt = false;

SignalHandler::SignalHandler()
{
    signal(SIGINT, signal_callback_handler);
}

bool SignalHandler::isInterrupted()
{
    return (isInterrupt);
}

void SignalHandler::signal_callback_handler(int signum)
{
    (void)signum;
    isInterrupt = true;
}