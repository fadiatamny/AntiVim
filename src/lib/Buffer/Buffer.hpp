#ifndef BUFFER_HPP
#define BUFFER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "../../utils/Vec2.hpp"

class Buffer
{
public:
    Buffer()
    {
        this->insert("");
        this->cursor = {0, 0};
    }
    ~Buffer() {}

    void newLine();
    void insert(std::string text);
    void erase();
    void del();

    void move(Vec2<int> cursor);
    void move(int row, int col);


    inline const char* currLine()
    {
        if (this->cursor.y >= this->lines.size())
        {
            return nullptr;
        }
        return this->lines[this->cursor.y].c_str();
    }

    inline size_t lineStart()
    {
        return 0;
    }
    inline size_t lineEnd()
    {
        return this->lines[this->cursor.y].length();
    }

    inline std::vector<std::string>::iterator linesBegin() {
        return this->lines.begin();
    }
    inline std::vector<std::string>::iterator linesEnd() {
        return this->lines.end();
    }

private:
    inline int linesCount()
    {
        return (int)this->lines.size();
    }


public:
    Vec2<int> cursor;

private:
    std::vector<std::string> lines;
};

#endif // BUFFER_HPP