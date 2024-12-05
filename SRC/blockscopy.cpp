#include "../include/block.h"

class LBlock :public Block{
public:
    LBlock() {
        id = 1;
        cells[0] = {Positioning(0, 2), Positioning(1, 0), Positioning(1, 1), Positioning(1, 2)};
        cells[1] = {Positioning(0, 1), Positioning(1, 1), Positioning(2, 1), Positioning(2, 2)};
        cells[2] = {Positioning(1, 0), Positioning(1, 1), Positioning(1, 2), Positioning(2, 0)};
        cells[3] = {Positioning(0, 0), Positioning(0, 1), Positioning(1, 1), Positioning(2, 1)};
        move(0, 3);
    }
};

class OBlock :public Block{
public:
    OBlock() {
        id = 2;
        cells[0] = {Positioning(0, 0), Positioning(0, 1), Positioning(1, 0), Positioning(1, 1)};
        cells[1] = {Positioning(0, 0), Positioning(0, 1), Positioning(1, 0), Positioning(1, 1)};
        cells[2] = {Positioning(0, 0), Positioning(0, 1), Positioning(1, 0), Positioning(1, 1)};
        cells[3] = {Positioning(0, 0), Positioning(0, 1), Positioning(1, 0), Positioning(1, 1)};
        move(0, 3);
    }
};

class IBlock :public Block{
public:
    IBlock() {
        id = 3;
        cells[0] = {Positioning(1, 0), Positioning(1, 1), Positioning(1, 2), Positioning(1, 3)};
        cells[1] = {Positioning(0, 2), Positioning(1, 2), Positioning(2, 2), Positioning(3, 2)};
        cells[2] = {Positioning(2, 0), Positioning(2, 1), Positioning(2, 2), Positioning(2, 3)};
        cells[3] = {Positioning(0, 1), Positioning(1, 1), Positioning(2, 1), Positioning(3, 1)};
        move(0, 3);
    }
};

class JBlock :public Block{
public:
    JBlock() {
        id = 4;
        cells[0] = {Positioning(0, 0), Positioning(1, 0), Positioning(1, 1), Positioning(1, 2)};
        cells[1] = {Positioning(0, 1), Positioning(0, 2), Positioning(1, 1), Positioning(2, 1)};
        cells[2] = {Positioning(1, 0), Positioning(1, 1), Positioning(1, 2), Positioning(2, 2)};
        cells[3] = {Positioning(0, 1), Positioning(2, 1), Positioning(2, 0), Positioning(1, 1)};
        move(0, 4);
    }
};

class TBlock : public Block{
public:
    TBlock() {
        id = 5;
        cells[0] = {Positioning(0, 1), Positioning(1, 0), Positioning(1, 1), Positioning(1, 2)};
        cells[1] = {Positioning(0, 1), Positioning(1, 1), Positioning(1, 2), Positioning(2, 1)};
        cells[2] = {Positioning(1, 0), Positioning(1, 1), Positioning(1, 2), Positioning(2, 1)};
        cells[3] = {Positioning(0, 1), Positioning(1, 0), Positioning(1, 1), Positioning(2, 1)};
        move(0, 3);
    }
};

class SBlock : public Block{
public:
    SBlock() {
        id = 6;
        cells[0] = {Positioning(0, 1), Positioning(0, 2), Positioning(1, 0), Positioning(1, 1)};
        cells[1] = {Positioning(0, 1), Positioning(1, 1), Positioning(1, 2), Positioning(2, 2)};
        cells[2] = {Positioning(1, 1), Positioning(1, 2), Positioning(2, 0), Positioning(2, 1)};
        cells[3] = {Positioning(0, 0), Positioning(1, 0), Positioning(1, 1), Positioning(2, 1)};
        move(0, 3);
    }
};

class ZBlock : public Block{
public:
    ZBlock() {
        id = 7;
        cells[0] = {Positioning(0, 0), Positioning(0, 1), Positioning(1, 1), Positioning(1, 2)};
        cells[1] = {Positioning(0, 2), Positioning(1, 1), Positioning(1, 2), Positioning(2, 1)};
        cells[2] = {Positioning(1, 0), Positioning(1, 1), Positioning(2, 1), Positioning(2, 2)};
        cells[3] = {Positioning(0, 1), Positioning(1, 0), Positioning(1, 1), Positioning(2, 0)};
        move(0, 4);
    }
};
