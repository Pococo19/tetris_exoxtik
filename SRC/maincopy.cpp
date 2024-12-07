#include "../include/block.h"
#include "../include/grid.h"
#include "../include/game.h"
#include <iostream>
#include "../raylib.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>

using namespace std;
double last_update_time = 0.0;

bool event_triggered(double interval)
{
    double current_time = GetTime();

    if(current_time - last_update_time >= interval) {
        last_update_time = current_time;
        return true;
    }
    return false;
}

void draw_intro_1(Font font, float scale, int pos)
{
    DrawTextEx(font, "T", {(140 + pos - 6) * scale, 240 * scale}, 80 * scale, 1, RED);
    DrawTextEx(font, "E", {(185 + pos - 6) * scale, 240 * scale}, 80 * scale, 1, GREEN);
    DrawTextEx(font, "T", {(230 + pos - 6) * scale, 240 * scale}, 80 * scale, 1, YELLOW);
    DrawTextEx(font, "R", {(280 + pos - 6) * scale, 240 * scale}, 80 * scale, 1, PURPLE);
    DrawTextEx(font, "I", {(325 + pos - 6) * scale, 240 * scale}, 80 * scale, 1, ORANGE);
    DrawTextEx(font, "S", {(375 + pos - 6) * scale, 240 * scale}, 80 * scale, 1, BLUE);
}

void draw_logo(Font font, float scale, int new_pos) {
    
    DrawTextEx(font, "T", {(345+ new_pos + 2)* scale, 27 * scale }, 55 * scale , 2.1, RED);
    DrawTextEx(font, "E", {(370+ new_pos + 2)* scale, 27 * scale }, 55 * scale , 2.1, GREEN);
    DrawTextEx(font, "T", {(395+ new_pos + 2)* scale, 27 * scale }, 55 * scale , 2.1, YELLOW);
    DrawTextEx(font, "R", {(420+ new_pos + 2)* scale, 27 * scale }, 55 * scale , 2.1, PURPLE);
    DrawTextEx(font, "I", {(445+ new_pos + 2)* scale, 27 * scale }, 55 * scale , 2.1, ORANGE);
    DrawTextEx(font, "S", {(470+ new_pos + 2)* scale, 27 * scale }, 55 * scale , 2.1, BLUE);
}

// Main function to setup and run the game
int main(int ac, char **av)
{
    std::cout << "Hello World" << std::endl;
    const int baseWidth = 530;
    const int baseHeight = 620;
    InitWindow(baseWidth, baseHeight, "TETRIS");
    SetTargetFPS(30);

    RenderTexture2D renderTexture = LoadRenderTexture(baseWidth, baseHeight);

    double time_limit = 7.0;
    double time_start = GetTime();
    int fc = 0;
    int new_pos = 0;
    int pos = 0;

    Font font = LoadFontEx("SRC/monogram.ttf", 64, 0, 0);
    Texture2D arrows = LoadTexture("SRC/arrows1.png");
    int s_width = GetScreenWidth();
    int s_height = GetScreenHeight();

    Game game = Game();

    game.game_score = 0;

    while(WindowShouldClose() == false)
    {
        float scaleX = (float)s_width / baseWidth;
        float scaleY = (float)s_height / baseHeight;
        float scale = std::min(scaleX, scaleY);

        if (IsWindowFullscreen()) {
            new_pos = 400;
            pos = 290;
            scale = scale / 1.2;
        } else {
            scale = 1.0f;
            new_pos = 0;
            pos = 0;
        }
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
            s_height = 1300;
            s_width = 1700;
        }
        UpdateMusicStream(game.music);
        double elapsed_time = GetTime() - time_start;
        BeginDrawing();
        game.handle_input();
        if (elapsed_time < time_limit && !game.start && !game.skip) {
                if (elapsed_time < 3.5)
                    DrawTextEx(font, "Pococo Studios Presents", {(65 + pos) * scale, 270 * scale}, 34 * scale, 2 * scale, WHITE);
                else
                    draw_intro_1(font, scale, pos);
                ClearBackground(Color(BLACK));
        }
        else {
            if (event_triggered(0.4) && !game.pause && game.start)
                game.move_block_down();
            ClearBackground(Color{84, 49, 179, 255});
            draw_logo(font, scale, new_pos);
            DrawTextEx(font, "Score", {(378+ new_pos)* scale , 90 * scale }, 35 * scale , 2 *scale, WHITE);
            DrawRectangleRounded({(340+ new_pos)* scale , 140 * scale , 170 * scale, 60 *scale}, 0.3  , 6 , Color{59, 85, 162, 255});
            DrawTextEx(font, "Next Block", {(345+ new_pos)* scale , 230 * scale }, 30 * scale , 2 * scale , WHITE);
            DrawRectangleRounded({(340+ new_pos)* scale , 270 * scale , 170 * scale , 170 * scale}, 0.3 * scale , 6 * scale , Color{59, 85, 162, 255});
            game.draw();
            DrawTextEx(font, TextFormat(" %i", game.game_score), {(390+ new_pos) * scale , 147* scale }, 45 * scale , 2 * scale , WHITE);
            if (game.game_o)
                DrawTextEx(font, "GAME OVER :(", {(70+ new_pos) * scale , 130 * scale}, 50* scale , 2* scale , WHITE);
            if (game.pause)
                DrawTextEx(font, "PAUSE", {(95+ new_pos) * scale , 290 * scale }, 50* scale , 2* scale , WHITE);
            if (!game.start) {
                fc++;
                if (((fc/30)%2)) {
                    DrawTextEx(font, "Tap ENTER", {(355+ new_pos)* scale , 450 * scale }, 30* scale , 2* scale , WHITE);
                    DrawTextEx(font, "to start", {(360+ new_pos)* scale , 475 * scale }, 30* scale , 2* scale , WHITE);
                }
            }
            DrawTextureEx(arrows, {(320 + new_pos)* scale , 550 * scale}, 0, scale , WHITE);
            if (game.game_score == 100)
                DrawTextEx(font, TextFormat("Score : %i !!!", game.game_score), {(325+ new_pos) * scale , 290 * scale }, 30 * scale , 2 * scale , WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
