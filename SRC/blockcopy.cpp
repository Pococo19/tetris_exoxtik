#include "../include/block.h"
#include "../raylib.h"
#include "../include/colors.h"

Block::Block()
{
    new_pos = 0;
    cell_size = 30;
    rotation_state = 0;
    colors = get_cell_color();
    row_offset = 0;
    cols_offset = 0;
}

void Block::draw(int offsetx, int offsety)
{
    int window_width = GetScreenWidth();
    int window_height = GetScreenHeight();
    if (IsWindowResized()) {
        int newWidth = GetScreenWidth();
        int newHeight = GetScreenHeight();
            if (newWidth == 2548 && newHeight == 1359)
                new_pos = 300;
            else
                new_pos = 0;
        }
    // Calculate the scaling factor
    float scale_x = (float)window_width / (10 * cell_size); // Assuming 10 columns
    float scale_y = (float)window_height / (20 * cell_size); // Assuming 20 rows
    float scale = (scale_x < scale_y) ? scale_x : scale_y;

    // Calculate scaled cell size
    float scaled_cell_size = cell_size * scale;

    std::vector<Positioning> tiles = get_cell_pos();

    for (Positioning item : tiles) {
        DrawRectangle(
            item.cols * scaled_cell_size + ((offsetx+ new_pos) * scale), // X position scaled
            item.row * scaled_cell_size + ((offsety+ new_pos) * scale), // Y position scaled
            scaled_cell_size - 1,                             // Width scaled
            scaled_cell_size - 1,                             // Height scaled
            colors[id]                                        // Cell color
        );
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
