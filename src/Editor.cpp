#include <FL/fl_draw.H>
#include <iostream>
#include "./Editor.h"

// Constructor

Editor::Editor(int x, int y, int w, int h, const char *label)
    : Fl_Widget(x, y, w, h, label)
{
    fl_font(FL_COURIER, 16);
    padding = 10;
    text = "When in the course of human events, it becomes necessary for one people to dissolve the political bands which have connected them with another, and to assume among the powers of the earth, the separate and equal station to which the Laws of Nature and of Nature's God entitle them, a decent respect to the opinions of mankind requires that they should declare the causes which impel them to the separation.";
}

// Override

void Editor::draw() 
{

    // Draw black border.
    fl_color(FL_BLACK);
    fl_rect(x(), y(), w(), h());

    // Draw text.
    // fl_draw(text.c_str(), x() + padding, y() + padding + 14);

    int x0 = x() + padding;
    int y0 = y() + padding + 16;

    int x = x0;
    int y = y0;

    for(size_t i=0; i < text.size(); i++)
    {
        float charWidth = fl_width(text[i]);

        if(x + charWidth > w() - padding)
        {
            x = x0;
            y += 16;
        }

        if(x == x0 && text[i] == ' ')
        {
            continue;
        }

        fl_draw(&text[i], 1, x, y);
        x += charWidth;
    }

}
