#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include "vector3.hpp"
#include "common.hpp"

namespace strangeloop {
class Image
{
public:
    Image();
    Image(int width, int height);

    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
    void setPixel(int x, int y, Vector3 vec);
    const Color getPixel(int x, int y) const;

    const std::string &header() const;
    int width() const;
    int height() const;

protected:
    std::string _header;
    int _width;
    int _height;
    std::vector<uint8_t> _buffer;
};
}

#endif // IMAGE_H
