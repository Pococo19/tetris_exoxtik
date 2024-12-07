#pragma once
#include <iostream>

class Grid
{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw();
    bool outside_cell(int rows, int cols);
    bool is_empty_cell(int row, int cols);
    void read_file(char *filepath);
    int clear_full_rows();
    bool full_line;
    bool save;
    int grid[20][10];

private:
    bool is_row_full(int row);
    void clear_row(int row);
    void move_row_down(int row, int num_rows);
    int num_rows;
    int num_cols;
    int new_pos;
    int window_width;
    int window_height;
    int cell_size;
    char buffer[1024];
    std::vector<Color> colors;
};
