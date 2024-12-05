#pragma once
#include <vector>
#include <map>
#include "colors.h"
class Positioning
{
public:
    Positioning(int row, int column);
    int row;
    int cols;
};

class Block
{
public:
    Block();
    void draw(int offsetx, int offsety);
    void move(int row, int col);
    void rotate();
    void undo_rotation();
    std::vector<Positioning> get_cell_pos();
    int id;
    std::map<int, std::vector<Positioning>> cells;

private:
    int cell_size;
    int rotation_state;
    std::vector<Color> colors;
    int row_offset;
    int cols_offset;
};
