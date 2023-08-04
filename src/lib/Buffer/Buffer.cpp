#include "Buffer.hpp"

void Buffer::newLine()
{
    if (this->cursor.y > this->linesCount() - 1)
    {
        this->lines.push_back("");
    }
    else
    {
        std::string line = this->lines[this->cursor.y].substr(this->cursor.x);
        this->lines[this->cursor.y].erase(this->cursor.x);
        this->lines.insert(this->lines.begin() + this->cursor.y + 1, line);
    }

    this->cursor.y += 1;
    this->cursor.x = 0;
}

void Buffer::insert(std::string text)
{
    if (this->cursor.y > this->linesCount() - 1)
    {
        this->lines.push_back("");
    }

    this->lines[this->cursor.y].insert(this->cursor.x, text);
    this->cursor.x += text.length();
}

void Buffer::erase()
{
    if (this->cursor.y > this->linesCount() - 1)
    {
        return;
    }
    if (this->lines[this->cursor.y].length() <= 0)
    {
        return;
    }

    if (this->cursor.x > 1)
    {
        this->lines[this->cursor.y].erase(this->cursor.x - 1, 1);
    }
    else if (this->cursor.x == 1)
    {
        this->lines[this->cursor.y].erase(0, 1);
    }

    if (this->cursor.x > 0)
    {
        this->cursor.x -= 1;
    }
}

void Buffer::del()
{
    if (this->cursor.y > this->linesCount() - 1)
    {
        return;
    }
    if (this->lines[this->cursor.y].length() < 0)
    {
        return;
    }

    this->lines[this->cursor.y].erase(this->cursor.x, 1);
}

void Buffer::move(Vec2<int> cursor)
{
    if (cursor.y < 0)
    {
        cursor.y = 0;
        cursor.x = 0;
    }
    else if (cursor.y > this->linesCount() - 1)
    {
        cursor.y = this->linesCount() - 1;
        cursor.x = this->lines[cursor.y].length();
    }

    if (cursor.x < 0)
    {
        cursor.x = 0;
    }
    else if (cursor.x > this->lines[cursor.y].length())
    {
        cursor.x = this->lines[cursor.y].length();
    }

    this->cursor = cursor;
}
void Buffer::move(int row, int col)
{
    if (this->cursor.y + row < 0)
    {
        this->cursor.y = 0;
        this->cursor.x = 0;
    }
    else if (this->cursor.y + row > this->linesCount() - 1)
    {
        this->cursor.y = this->linesCount() - 1;
        this->cursor.x = this->lines[this->cursor.y].length();
    }
    else
    {
        this->cursor.y += row;
    }

    if (this->cursor.x + col < 0)
    {
        this->cursor.x = 0;
    }
    else if (this->cursor.x + col > this->lines[this->cursor.y].length())
    {
        this->cursor.x = this->lines[this->cursor.y].length();
    }
    else
    {
        this->cursor.x += col;
    }
}