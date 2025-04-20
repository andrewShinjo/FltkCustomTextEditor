#include "./EditorChar.h"

EditorChar::EditorChar(char c, int x, int y)
{
    this->c = c;
    this->x = x;
    this->y = y;
}

char EditorChar::getChar() const
{
    return c;
}

int EditorChar::getX() const
{
    return x;
}

int EditorChar::getY() const
{
    return y;
}
