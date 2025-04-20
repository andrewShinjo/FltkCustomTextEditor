#include <FL/fl_draw.H>
#include <iostream>
#include <fstream>
#include <sstream>
#include "./ReadOnlyEditor.h"

// Constructor

Editor::Editor(int x, int y, int w, int h, const char *label)
    : Fl_Widget(x, y, w, h, label)
{
    padding = 10;

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

    // Draw border.

    fl_color(FL_BLACK);
    fl_rect(x(), y(), w(), h());

    // Draw text that's in the view.

    std::vector<EditorChar> positions = calculatePositions(); 

    for(EditorChar position : positions)
    {
        char c = position.getChar();
        int currentX = position.getX();
        int currentY = position.getY();
        bool textOutOfView = currentY > y() + h() - padding;

        if(textOutOfView)
        {
            break;
        }

        fl_draw(&c, 1, currentX, currentY); 
    }

    // Draw scrollbar.

    int textHeight = positions.back().getY() + fl_height() + padding;
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

// Other

std::vector<EditorChar> Editor::calculatePositions()
{

    std::vector<EditorChar> result;

    int leftBound = x() + padding;
    int rightBound = x() + w() - padding;

    int currentX = x() + padding;
    int currentY = y() + padding + fl_height();
    
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
