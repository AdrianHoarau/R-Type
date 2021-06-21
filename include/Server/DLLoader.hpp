/*
** DLLoader.hpp for OOP_Bootstrap_Arcade_2019 in /home/arthurbertaud/Second_year/OOP/OOP_Bootstrap_Arcade_2019
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Tue Mar 3 11:21:01 AM 2020 arthurbertaud
** Last update Mon Nov 1 4:37:08 PM 2020 arthurbertaud
*/
#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_
#include <iostream>
#include "Error.hpp"
#ifdef __linux__
    #include <dlfcn.h>
    #define LIBTYPE void*
    #define OPENLIB(libname) dlopen((libname), RTLD_NOW)
    #define LIBFUNC(lib, fn) dlsym((lib), (fn))
    #define CLOSELIB(handler) dlclose(handler)
#elif defined(_WIN32)
    #include <winsock2.h>
    #include <windows.h>
    #define LIBTYPE HMODULE
    #define OPENLIB(libname) LoadLibraryA(libname)
    #define LIBFUNC(lib, fn) GetProcAddress((lib), (fn))
    #define CLOSELIB(handler) CloseHandle(handler)
#endif
class DLLoader
{
public:
    DLLoader(const std::string& libpath)
    try : _handler(nullptr)
    {
        _handler = OPENLIB(libpath.c_str());
        #if defined(_WIN32)
            if (!_handler)
                throw ErrorDLLoader("Error while opening lib");
        #else
            if (!_handler)
                throw ErrorDLLoader(dlerror());
        #endif
    }
    catch (ErrorDLLoader const& err)
    {
        throw err;
    }
    template <typename T>
    std::unique_ptr<T> getInstance(const std::string& name) const
    {
        std::unique_ptr<T>(*sample)();
        sample = reinterpret_cast<std::unique_ptr<T>(*)()>(LIBFUNC(_handler, name.c_str()));
        #if defined(_WIN32)
            if (!sample)
                throw ErrorDLLoader("Error while ");
        #else
            char* error;
            if ((error = dlerror()) != NULL)
                throw ErrorDLLoader(error);
        #endif
        return (sample());
    }
    DLLoader(const DLLoader& other) = default;
    DLLoader& operator=(const DLLoader& other) = default;
    ~DLLoader()
    {
        int ret = 0;
        ret = CLOSELIB(_handler);
        #if defined(_WIN32)
            if (ret == 0)
                std::cerr << "Error while closing lib" << std::endl;
        #else
            if (ret != 0)
                std::cerr << dlerror() << std::endl;
        #endif
    }
private:
    LIBTYPE _handler;
};
#endif /* !DLLOADER_HPP_ */
