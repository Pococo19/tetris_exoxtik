#pragma once
#include <iostream>
#include <vector>
#include "../raylib.h"
#include "../raymath.h"
#include <deque>
#include "grid.h"
#include "../SRC/blockscopy.cpp"
#include "block.h"

class Game
{
public:
    Game();
    ~Game();
    Block get_random_block();
    std::vector<Block> get_all_blocks();
    void draw();
    void handle_input();
    void move_block_left();
    void move_block_right();
    void move_block_down();
    void game_over();
    void update();
    bool outside_block();
    bool pause;
    bool game_o;
    bool skip;
    bool start;
    int game_score;
    float g_scale;
    Music music;
    Grid grid;

private:
    void rotate_block();
    void reset_game();
    void update_score(int line_cleared, int basic_points);
    void lock_block();
    bool block_collision();
    std::vector<Block> blocks;
    Block curr_block;
    Block next_block;
};
