#include <FL/fl_draw.H>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include "./ReadOnlyEditor.h"

// Constructor

Editor::Editor(int x, int y, int w, int h, const char *label)
    : Fl_Widget(x, y, w, h, label)
{
    viewportY = 0;
    viewportLength = h;

    std::ifstream inputFile("resources/declaration-of-independence.txt");

    if(!inputFile.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
    }

    std::getline(inputFile, text);
}

// Override

void Editor::draw() 
{

    // Clear drawing

    fl_color(FL_WHITE);
    box(FL_FLAT_BOX);
    fl_rectf(x(), y(), w(), h());

    // Draw border.

    fl_color(FL_BLACK);
    fl_rect(x(), y(), w(), h());

    // Draw text that's in the view.

    fl_push_clip(x(), y(), w(), h());

    std::vector<EditorChar> positions = calculatePositions(); 
    documentLength = positions.back().getY() + fl_height() - y();

    std::cout << "viewportY: " << viewportY << std::endl
              << "viewportLength: " << viewportLength << std::endl
              << "documentLength: " << documentLength << std::endl;

    for(EditorChar position : positions)
    {
        char c = position.getChar();
        int currentX = position.getX();
        int currentY = position.getY();
        bool textOutOfView = currentY > y() + h() - viewportY;

        /*
        if(textOutOfView)
        {
            break;
        }
        */

        fl_draw(&c, 1, currentX, currentY-viewportY); 
    }

    fl_pop_clip();

    // Draw scrollbar.

    int textHeight = positions.back().getY() + fl_height();
    int viewHeight = h();
    bool scrollbarVisible = viewHeight < textHeight;

    if(scrollbarVisible)
    {
        float ratio = static_cast<float>(viewHeight) / textHeight;
        int scrollbarHeight = viewHeight*ratio;
        int scrollbarWidth = 10;

        fl_color(FL_RED);
        fl_rectf(x() + w() - scrollbarWidth, y(), scrollbarWidth,
            scrollbarHeight);
    }
    
}

int Editor::handle(int event)
{
    switch(event)
    {
        case FL_FOCUS: // need FL_FOCUS to listen for keypress.
        {
            return 1;
        }
        case FL_KEYBOARD:
        {
            if(Fl::event_key() == FL_Enter)
            {
                viewportY = std::max(0, viewportY - 12);
                redraw();
            }
            if(Fl::event_key() == FL_Up)
            {
                viewportY = std::min(
                    documentLength - viewportLength, 
                    viewportY + 12
                );
                redraw();
            }
            return 1;
        }
        default:
        {
            return 0;            
        }
    }
}

// Other

std::vector<EditorChar> Editor::calculatePositions()
{

    std::vector<EditorChar> result;

    int leftBound = x();
    int rightBound = x() + w();

    int currentX = x();
    int currentY = y() + fl_height();
    
    for(size_t i = 0; i < text.size(); i++)
    {
        char c = text[i];
        float charWidth = fl_width(c);
        bool cantFit = currentX + charWidth > rightBound;
        
        if(cantFit && currentX != leftBound)
        {
            currentX = leftBound;
            currentY = currentY + fl_height();
        }
        
        EditorChar ec(c, currentX, currentY);
        result.push_back(ec);

        currentX = currentX + charWidth;
    } 

    return result;
}
