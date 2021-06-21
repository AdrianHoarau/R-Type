/*
** Zipper.hpp for B-CPP-501-NAN-5-1-rtype-arthur.bertaud in /home/arthurbertaud/Third_year/R-Type/B-CPP-501-NAN-5-1-rtype-arthur.bertaud/include/Server
**
** Made by arthurbertaud
** Login   <EPITECH>
**
** Started on  Thu Nov 5 11:54:24 AM 2020 arthurbertaud
** Last update Thu Nov 5 11:54:24 AM 2020 arthurbertaud
*/

#ifndef ZIPPER_HPP_
# define ZIPPER_HPP_

#include <boost/iterator/zip_iterator.hpp>
#include <boost/range.hpp>

class Zipper {
    public:
        Zipper() = default;
        Zipper(const Zipper& other) = default;
        Zipper& operator=(const Zipper& other) = default;
        ~Zipper() = default;
        template <typename... T>
        static auto zip(T&&... containers) -> boost::iterator_range<boost::zip_iterator<decltype(boost::make_tuple(std::begin(containers)...))>>
        {
            auto zip_begin = boost::make_zip_iterator(boost::make_tuple(std::begin(containers)...));
            auto zip_end = boost::make_zip_iterator(boost::make_tuple(std::end(containers)...));
            return (boost::make_iterator_range(zip_begin, zip_end));
        }
    protected:
    private:
};

#endif /* !ZIPPER_HPP_ */
