#ifndef SCREENFUNCTIONS_H
#define SCREENFUNCTIONS_H

class ScreenFunctions
{
public:
    void clearScreen();
    void clearLine(int line, int column);
    void moveCursor(int line, int column);
};

#endif