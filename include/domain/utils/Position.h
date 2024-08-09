#ifndef POSITION_H
#define POSITION_H

#define MAX_SIZE 7
#define MIN_SIZE 0

class Position {
private:
    int x;
    int y;

public:
    Position();

    Position(int x, int y);

    ~Position();

    int getX() const ;

    int getY() const ;
};

#endif