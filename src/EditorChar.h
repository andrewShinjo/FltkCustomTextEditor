#ifndef EDITOR_CHAR_H
#define EDITOR_CHAR_H

class EditorChar
{
    public:

        // Constructor
        EditorChar(char c, int x, int y);

        // Methods

        char getChar() const;
        int getX() const;
        int getY() const;

    private:

        char c;
        int x;
        int y;
};

#endif
