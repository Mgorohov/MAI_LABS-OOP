#include "../include/Five.hpp"
#include <string>
#include <exception>
#include <stdexcept>

Five::Five()
{
    _size = 0;
    _num = new unsigned char[0]{};
}

Five::Five(const size_t &n, unsigned char t)
{
    if (t != 0 and (t < 48 or t > 52))
    {
        throw std::invalid_argument("Your symbol is not in five-digit number system!\n");
    }

    _size = n;
    _num = new unsigned char[n]{};
    std::fill(_num, _num + _size, t);
}

Five::Five(const std::initializer_list<unsigned char> &t)
{
    _size = t.size();
    _num = new unsigned char[_size]{};
    size_t position = _size - 1;
    for (const unsigned char &letter : t)
    {
        if (letter != 0 and (letter < 48 or letter > 52))
        {
            throw std::invalid_argument("Your symbol is not in five-digit number system!\n");
        }
        _num[position--] = letter;
    }
}

Five::Five(const std::string &t)
{
    _size = t.size();
    _num = new unsigned char[_size]{};
    size_t position = _size - 1;
    for (const unsigned char &letter : t)
    {
        if (letter != 0 and (letter < 48 or letter > 52))
        {
            throw std::invalid_argument("Your symbol is not in five-digit number system!\n");
        }
        _num[position--] = letter;
    }
}

Five::Five(const Five &other)
{
    _size = other._size;
    _num = new unsigned char[_size];

    for (size_t i = 0; i != _size; ++i)
    {
        _num[i] = other._num[i];
    }
}

Five::Five(Five &&other) noexcept
{
    _size = other._size;
    _num = new unsigned char[_size];

    for (size_t i = 0; i != _size; ++i)
    {
        _num[i] = other._num[i];
    }

    delete other._num;
    other._size = 0;
}

Five::~Five() noexcept
{
    _size = 0;
    delete _num;
}

Five &Five::operator=(const Five &other)
{
    _size = other._size;
    _num = new unsigned char[_size];

    for (size_t i = 0; i < _size; ++i)
    {
        _num[i] = other._num[i];
    }

    return *this;
}

Five Five::operator+(const Five &other)
{
    bool longer = _size >= other._size;
    size_t maxSize, minSize;

    if (longer)
    {
        maxSize = _size;
        minSize = other._size;
    }
    else
    {
        maxSize = other._size;
        minSize = _size;
    }

    Five result = Five(maxSize);

    int ost = 0, ans, num1, num2, sum;
    for (size_t i = 0; i < minSize; ++i)
    {
        num1 = _num[i] - 48;
        num2 = other._num[i] - 48;
        sum = num1 + num2 + ost;
        ost = sum / 5;
        ans = sum % 5;
        result._num[i] = ans + 48;
    }

    for (size_t i = minSize; i < maxSize; ++i)
    {
        num1 = longer ? _num[i] - 48 : other._num[i] - 48;
        sum = num1 + ost;
        ost = sum / 5;
        ans = sum % 5;
        result._num[i] = ans + 48;
    }

    if (ost != 0)
    {
        ++result._size;
        result._resize();
        result._num[maxSize] = ost + 48;
    }

    return result;
}

Five Five::operator-(const Five &other)
{
    if (other._size > _size)
    {
        throw std::invalid_argument("The result will be negative!\n");
    }

    Five answer = Five(*this);

    for (size_t i = other._size - 1; i < other._size; --i)
    {
        answer._num[i] = _num[i] - other._num[i] + '0';

        if (answer._num[i] < '0')
        {
            answer._num[i] += 5;

            size_t index = i + 1;
            while (index < answer._size and answer._num[index] == '0')
            {
                answer._num[index] = '4';
                index++;
            }

            if (index == answer._size)
            {
                throw std::invalid_argument("The result will be negative!\n");
            }

            answer._num[index]--;
            if (index + 1 == answer._size && answer._num[index] == '0')
            {
                --answer._size;
                answer._resize();
            }
        }
    }
    return answer;
}

bool Five::operator==(const Five &other)
{
    if (_size != other._size)
    {
        return false;
    }

    for (size_t i = 0; i < _size; ++i)
    {
        if (_num[i] != other._num[i])
        {
            return false;
        }
    }
    return true;
}

bool Five::operator<(const Five &other)
{
    if (_size < other._size)
    {
        return true;
    }

    if (_size > other._size)
    {
        return false;
    }

    for (size_t i = _size - 1; i < _size; --i)
    {
        if (_num[i] > other._num[i])
        {
            return false;
        }
        if (_num[i] < other._num[i])
        {
            return true;
        }
    }
    return false;
}

bool Five::operator>(const Five &other)
{
    if (_size > other._size)
    {
        return true;
    }
    if (_size < other._size)
    {
        return false;
    }

    for (size_t i = _size - 1; i < _size; --i)
    {
        if (_num[i] > other._num[i])
            return true;
        if (other._num[i] > _num[i])
            return false;
    }

    return false;
}

unsigned char *Five::get_value()
{
    return _num;
}

std::string Five::get_value_string()
{
    std::string answer = "";
    for (size_t i = _size - 1; i < _size; --i)
    {
        answer += _num[i];
    }
    return answer;
}

size_t Five::get_size()
{
    return _size;
}

void Five::_resize()
{
    unsigned char *resized = new unsigned char[_size]{};

    for (size_t i = 0; i < _size; ++i)
    {
        resized[i] = _num[i];
    }
    delete _num;
    _num = resized;
}