#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <iostream>

#include "./src/ReadOnlyEditor.h"

int main(int argc, char **argv)
{
    int screenHeight = Fl::h(), screenWidth = Fl::w();

    std::cout << "screenHeight: "   << screenHeight 
              << ", screenWidth: "  << screenWidth
              << std::endl;

    Fl_Window *window 
        = new Fl_Window(screenWidth / 2, screenHeight / 2, "Text Editor");
    Editor *e 
        = new Editor(10, 10, window->w() - 2*10, window->h() - 2*10);

    window->resizable(window);
    window->end();
    window->show(argc, argv);

    return Fl::run();
}
