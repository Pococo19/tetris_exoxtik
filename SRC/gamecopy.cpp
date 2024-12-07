#include "../include/game.h"
#include <random>
#include <stdlib.h>
#include "raylib.h"

Game::Game()
{
    new_pos = 0;
    grid = Grid();
    blocks = get_all_blocks();
    curr_block = get_random_block();
    next_block = get_random_block();
    pause = false;
    game_o = false;
    start = false;
    skip = false;
    InitAudioDevice();
    music = LoadMusicStream("SRC/tetris.mp3");
    PlayMusicStream(music);
}

Game::~Game()
{
    UnloadMusicStream(music);
    CloseAudioDevice();
}

Block Game::get_random_block()
{
    if (blocks.empty())
        blocks = get_all_blocks();
    int random_index = rand() % blocks.size();
    Block block =  blocks[random_index];
    blocks.erase(blocks.begin() + random_index);
    return block;
}

std::vector<Block> Game::get_all_blocks()
{
    return {IBlock(), JBlock(), OBlock(), ZBlock(), SBlock(), TBlock(), LBlock()};
}

void Game::draw()
{
    int y_pos = 0;
    if (IsWindowFullscreen()) {
        new_pos = 410;
        y_pos = 220;
    } else
        new_pos = 0;
    grid.Draw();
    curr_block.draw(11, 11);
    switch(next_block.id) {
        case 3:
            next_block.draw(275 + new_pos , 310 + y_pos);
            break;
        case 7:
            next_block.draw(260 + new_pos, 320 + y_pos);
            break;
        case 4:
            next_block.draw(260 + new_pos, 320 + y_pos);
            break;
        case 2:
            next_block.draw(305 + new_pos, 325 + y_pos);
            break;
        default:
            next_block.draw(290+ new_pos, 320 + y_pos);
            break;
    }
}

void Game::handle_input()
{
    int key_pressed = GetKeyPressed();
    if (game_o && key_pressed != 0) {
        game_o = false;
        reset_game();
    }
    if (pause && key_pressed != 0 && start)
        pause = false;
    if (!start && key_pressed == KEY_ENTER)
        start = true;
    if (!skip && !start && key_pressed == KEY_SPACE)
        skip = true;
    if (start) {
        switch(key_pressed)
        {
            case KEY_LEFT:
                move_block_left();
                break;
            case KEY_RIGHT:
                move_block_right();
                break;
            case KEY_DOWN:
                move_block_down();
                update_score(0, 1);
                break;
            case KEY_UP:
                rotate_block();
                break;
            case KEY_SPACE:
                pause = true;
                break;
        }
    }
}

void Game::move_block_left()
{
    if (!game_o) {
        curr_block.move(0, -1);
        if (outside_block()  || !block_collision())
            curr_block.move(0, 1);
    }
}

void Game::move_block_right()
{
    if (!game_o) {
        curr_block.move(0, 1);
        if (outside_block() || !block_collision())
            curr_block.move(0, -1);
    }
}

void Game::move_block_down()
{
    if (!game_o) {
        curr_block.move(1, 0);
        if (outside_block() || !block_collision()) {
            curr_block.move(-1, 0);
            lock_block();
        }
    }
}

bool Game::outside_block()
{
    std::vector<Positioning> tiles = curr_block.get_cell_pos();
    for (Positioning item: tiles)
    {
        if (grid.outside_cell(item.row, item.cols))
            return true;
    }
    return false;
}

void Game::rotate_block()
{
    curr_block.rotate();
    if (outside_block())
        curr_block.undo_rotation();
}

void Game::lock_block()
{
    std::vector<Positioning> tiles = curr_block.get_cell_pos();
    for (Positioning item: tiles) {
        grid.grid[item.row][item.cols] = curr_block.id; 
    }
    game_score++;
    curr_block = next_block;
    if (block_collision() == false)
        game_o = true;
    next_block = get_random_block();
    int row_clear = grid.clear_full_rows();
    update_score(row_clear, 0);
}

bool Game::block_collision()
{
    std::vector<Positioning> tiles = curr_block.get_cell_pos();
    for (Positioning item: tiles) {
        if (!grid.is_empty_cell(item.row, item.cols))
            return false;
    }
    return true;
}

void Game::reset_game()
{
    grid.Initialize();
    blocks = get_all_blocks();
    curr_block = get_random_block();
    next_block = get_random_block();
    game_score = 0;
}

void Game::update_score(int line_cleared, int basic_points)
{
    switch(line_cleared) {
        case 1:
            game_score += 100;
            break;
        case 2:
            game_score += 300;
            break;
        case 3:
            game_score += 500;
            break;
        default:
            break;
    }
    game_score += basic_points;
}
