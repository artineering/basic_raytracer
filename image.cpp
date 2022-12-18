#include "image.hpp"

using namespace strangeloop;

Image::Image()
    :_header("P3"),_width(0),_height(0)
{
}

Image::Image(int width, int height)
    :_header("P3"),_width(width),_height(height),_buffer(width*height*3,0)
{
}

void Image::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    _buffer[x * _width + y] = red;
    _buffer[x * _width + y + 1] = green;
    _buffer[x * _width + y + 2] = blue;
}

void Image::setPixel(int x, int y, Vector3 vec)
{
    _buffer[x * _width + y] = vec[0];
    _buffer[x * _width + y + 1] = vec[1];
    _buffer[x * _width + y + 2] = vec[2];
}

const Color Image::getPixel(int x, int y) const
{
    Color c(_buffer[x * _width + y],_buffer[x * _width + y
            + 1],_buffer[x * _width + y + 2]);
    return c;
}

const std::string &Image::header() const
{
    return _header;
}

int Image::width() const
{
    return _width;
}

int Image::height() const
{
    return _height;
}

