#include "Buffer.hpp"

void Buffer::insert(std::string text)
{
    if (this->cursor.row >= this->lines.size())
    {
        std::cout << "Buffer::insert: cursor.row > lines.size()" << std::endl;
        this->lines.push_back("");
    }

    this->lines[this->cursor.row].insert(this->cursor.col, text);
    this->cursor.col += text.length();
}

void Buffer::erase()
{
    if (this->cursor.row > this->lines.size())
    {
        return;
    }
    if (this->lines[this->cursor.row].length() < 0)
    {
        return;
    }

    if (this->cursor.col > 1)
    {
        this->lines[this->cursor.row].erase(this->cursor.col - 1, 1);
    }
    else if (this->cursor.col == 1)
    {
        this->lines[this->cursor.row].erase(0, 1);
    }

    if (this->cursor.col > 0)
    {
        this->cursor.col -= 1;
    }
}

void Buffer::del()
{
    if (this->cursor.row > this->lines.size())
    {
        return;
    }
    if (this->lines[this->cursor.row].length() < 0)
    {
        return;
    }

    this->lines[this->cursor.row].erase(this->cursor.col, 1);
}

void Buffer::move(Cursor cursor)
{
    std::cout << "Cursor" << cursor.row << ", " << cursor.col << std::endl;
    std::cout << "Lines" << this->lines.size() << std::endl;
    if (cursor.row < 0)
    {
        cursor.row = 0;
    }
    else if (cursor.row > this->lines.size())
    {
        cursor.row = this->lines.size();
        cursor.row -= 1;
    }

    if (cursor.col < 0)
    {
        cursor.col = 0;
    }
    else if (cursor.col > this->lines[cursor.row].length())
    {
        cursor.col = this->lines[cursor.row].length();
    }

    this->cursor = cursor;
}
void Buffer::move(size_t row, size_t col)
{
    std::cout << "Cursor" << row << ", " << col << std::endl;
    std::cout << "Lines" << this->lines.size() << std::endl;
    if (this->cursor.row + row < 0)
    {
        this->cursor.row = 0;
    }
    else if (this->cursor.row + row > this->lines.size())
    {
        this->cursor.row = this->lines.size() - 1;
    }
    else
    {
        this->cursor.row += row;
    }

    if (this->cursor.col + col < 0)
    {
        this->cursor.col = 0;
    }
    else if (this->cursor.col + col > this->lines[this->cursor.row].length())
    {
        this->cursor.col = this->lines[this->cursor.row].length();
    }
    else
    {
        this->cursor.col += col;
    }
}