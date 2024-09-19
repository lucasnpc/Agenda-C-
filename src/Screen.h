#ifndef SCREEN_H
#define SCREEN_H

class Screen
{
public:
    void clearScreen();
    void clearLine(int line, int column);
    void moveCursor(int line, int column);
};

#endif