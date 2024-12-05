#include "../include/block.h"
#include "../raylib.h"
#include "../include/colors.h"

Block::Block()
{
    cell_size = 30;
    rotation_state = 0;
    colors = get_cell_color();
    row_offset = 0;
    cols_offset = 0;
}

void Block::draw(int offsetx, int offsety)
{
    std::vector<Positioning> tiles = get_cell_pos();

    for (Positioning item : tiles) {
        DrawRectangle(item.cols * cell_size + (int)offsetx, item.row * cell_size + (int)offsety, cell_size - 1, cell_size - 1, colors[id]);
    }
}

void Block::move(int row, int col)
{
    row_offset += row;
    cols_offset += col;
}

std::vector<Positioning> Block::get_cell_pos()
{
    std::vector<Positioning> tiles = cells[rotation_state];
    std::vector<Positioning> moved_tiles;
    for (Positioning item : tiles) {
        Positioning new_pos = Positioning(item.row + row_offset, item.cols + cols_offset); 
        moved_tiles.push_back(new_pos);
    }
    return moved_tiles;
}

void Block::rotate()
{
    rotation_state++;
    if (rotation_state == (int)cells.size())
        rotation_state = 0;
}

void Block::undo_rotation()
{
    rotation_state--;
    if (rotation_state == -1)
        rotation_state = (int)cells.size() - 1;
}

Positioning::Positioning(int row, int cols)
{
    this->row = row;
    this->cols = cols;
}
