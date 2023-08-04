#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <string>
#include <vector>

typedef struct cursor
{
    size_t row;
    size_t col;
} Cursor;

class Buffer
{
public:
    Buffer()
    {
        this->insert("");
        this->cursor = {0, 0};
    }
    ~Buffer() {}

    void insert(std::string text);
    void erase();
    void del();

    void move(Cursor cursor);
    void move(size_t row, size_t col);


    const char* currLine()
    {
        return this->lines[this->cursor.row].c_str();
    }

    inline size_t lineStart()
    {
        return 0;
    }
    inline size_t lineEnd()
    {
        return this->lines[this->cursor.row].length() - 1;
    }

public:
    Cursor cursor;

private:
    std::vector<std::string> lines;
};

#endif // BUFFER_HPP