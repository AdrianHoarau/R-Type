/*
** EPITECH PROJECT, 2020
** client
** File description:
** SignalHandler
*/

#ifndef SIGNALHANDLER_HPP_
#define SIGNALHANDLER_HPP_

#include <signal.h>
#include <iostream>
#include <atomic>

extern bool isInterrupt;

class SignalHandler {
    public:
        SignalHandler();
        SignalHandler(const SignalHandler& other) = default;
        SignalHandler& operator=(const SignalHandler& other) = default;
        ~SignalHandler() = default;
        bool isInterrupted();
    private:
        static void signal_callback_handler(int signum);
};

#endif /* !SIGNALHANDLER_HPP_ */