#ifndef EDITOR_H
#define EDITOR_H

#include <FL/Fl_Widget.H>
#include <string>
#include <vector>
#include "./EditorChar.h"

class Editor : public Fl_Widget
{
    public:

        // Constructor
        Editor(int x, int y, int w, int h, const char *label = 0);

        // Override
        void draw() override;
        int handle(int event) override;

        // Other

        std::vector<EditorChar> calculatePositions();

    private:

        unsigned int padding;
        size_t viewportY;
        std::string text;
};

#endif
