#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>
#include <string>
#include <iostream>
using namespace std;
struct rgb
{
    int r, g, b;

    rgb(const int r, const int g, const int b) : r(r), g(g), b(b)
    {
    }
};

class image
{
private :
    using rgb_container_type = std::vector<rgb>;

public :
    using const_iterator_type = typename rgb_container_type::const_iterator;
    using iterator_type = typename rgb_container_type::iterator;

private :
    rgb_container_type rgbs_;
    int width_;
public :
    image(const int width, const int height, const rgb &rgb = rgb(0, 0, 0)) : rgbs_(width * height, rgb), width_(width)
    {
    }

    int width() const
    {
        return width_;
    }

    int height() const
    {
        return rgbs_.size() / width();
    }

    const_iterator_type begin() const
    {
        return rgbs_.begin();
    }

    const_iterator_type end() const
    {
        return rgbs_.end();
    }

    iterator_type begin()
    {
        return rgbs_.begin();
    }

    iterator_type end()
    {
        return rgbs_.end();
    }

    const rgb &operator () (const int x, const int y) const
    {
		
        return *(begin() + y * width() + x);
    }

    rgb &operator () (const int x, const int y)
    {
		
        return *(begin() + y * width() + x);
    }
};

#endif
