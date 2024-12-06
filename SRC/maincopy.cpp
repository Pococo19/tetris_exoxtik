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

void draw_intro_1(Font font, float scale) {
    DrawTextEx(font, "T", {140 * scale - 6, 275 * scale}, 80 * scale, 1, RED);
    DrawTextEx(font, "E", {185 * scale - 6, 275 * scale}, 80 * scale, 1, GREEN);
    DrawTextEx(font, "T", {230 * scale - 6, 275 * scale}, 80 * scale, 1, YELLOW);
    DrawTextEx(font, "R", {280 * scale - 6, 275 * scale}, 80 * scale, 1, PURPLE);
    DrawTextEx(font, "I", {325 * scale - 6, 275 * scale}, 80 * scale, 1, ORANGE);
    DrawTextEx(font, "S", {375 * scale - 6, 275 * scale}, 80 * scale, 1, BLUE);
}

void draw_logo(Font font, float scale, int new_pos) {
    DrawTextEx(font, "T", {(345 + new_pos)* scale  + 2,( 27 + new_pos)* scale },( 55 + new_pos)* scale , 2.1, RED);
    DrawTextEx(font, "E", {(370 + new_pos)* scale  + 2,( 27 + new_pos)* scale },( 55 + new_pos)* scale , 2.1, GREEN);
    DrawTextEx(font, "T", {(395 + new_pos)* scale  + 2,( 27 + new_pos)* scale },( 55 + new_pos)* scale , 2.1, YELLOW);
    DrawTextEx(font, "R", {(420 + new_pos)* scale  + 2,( 27 + new_pos)* scale },( 55 + new_pos)* scale , 2.1, PURPLE);
    DrawTextEx(font, "I", {(445 + new_pos)* scale  + 2,( 27 + new_pos)* scale },( 55 + new_pos)* scale , 2.1, ORANGE);
    DrawTextEx(font, "S", {(470 + new_pos)* scale  + 2,( 27 + new_pos)* scale },( 55 + new_pos)* scale , 2.1, BLUE);
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

    Font font = LoadFontEx("SRC/monogram.ttf", 64, 0, 0);
    Texture2D arrows = LoadTexture("SRC/arrows1.png");

    Game game = Game();

    game.game_score = 0;

    while(WindowShouldClose() == false)
    {
        int s_width = GetScreenWidth();
        int s_height = GetScreenHeight();
        float scaleX = (float)s_width / baseWidth;
        float scaleY = (float)s_height / baseHeight;
        float scale = std::min(scaleX, scaleY);

        if (IsWindowResized()) {
        int newWidth = GetScreenWidth();
        int newHeight = GetScreenHeight();
            if (newWidth == 2548 && newHeight == 1359)
                new_pos = 300;
            else
                new_pos = 0;
        }
        UpdateMusicStream(game.music);
        double elapsed_time = GetTime() - time_start;
        BeginDrawing();
        game.handle_input();
        if (elapsed_time < time_limit && !game.start && !game.skip) {
                if (elapsed_time < 3.5)
                    DrawTextEx(font, "Pococo Studios Presents", {65 * scale, 290* scale}, 34 * scale, 2 * scale, WHITE);
                else
                    draw_intro_1(font, scale);
                ClearBackground(Color(BLACK));
        }
        else {
            if (event_triggered(0.4) && !game.pause && game.start)
                game.move_block_down();
            ClearBackground(Color{84, 44, 155, 255});
            draw_logo(font, scale, new_pos);
            DrawTextEx(font, "Score", {(378+ new_pos)* scale , (90+ new_pos)* scale }, (35+ new_pos)* scale , (2+ new_pos)* scale , WHITE);
            DrawRectangleRounded({340+ new_pos* scale , 140+ new_pos* scale , 170+ new_pos* scale , 60+ new_pos* scale }, 0.3+ new_pos* scale , 6+ new_pos* scale , Color{59, 85, 162, 255});
            DrawTextEx(font, "Next Block", {345+ new_pos* scale , 230+ new_pos* scale }, 30+ new_pos* scale , 2+ new_pos* scale , WHITE);
            DrawRectangleRounded({340+ new_pos* scale , 270+ new_pos* scale , 170+ new_pos* scale , 170+ new_pos* scale }, 0.3+ new_pos* scale , 6+ new_pos* scale , Color{59, 85, 162, 255});
            game.draw();
            DrawTextEx(font, TextFormat(" %i", game.game_score), {390+ new_pos* scale , 147+ new_pos* scale }, 45+ new_pos* scale , 2+ new_pos* scale , WHITE);
            if (game.game_o)
                DrawTextEx(font, "GAME OVER :(", {70+ new_pos* scale , 130+ new_pos* scale }, 50+ new_pos* scale , 2+ new_pos* scale , WHITE);
            if (game.pause)
                DrawTextEx(font, "PAUSE", {95+ new_pos* scale , 290+ new_pos* scale }, 50+ new_pos* scale , 2+ new_pos* scale , WHITE);
            if (!game.start) {
                fc++;
                if (((fc/30)%2)) {
                    DrawTextEx(font, "Tap ENTER", {355+ new_pos* scale , 450+ new_pos* scale }, 30+ new_pos* scale , 2+ new_pos* scale , WHITE);
                    DrawTextEx(font, "to start", {360+ new_pos* scale , 475+ new_pos* scale }, 30+ new_pos* scale , 2+ new_pos* scale , WHITE);
                }
            }
            DrawTextureEx(arrows, Vector2{320 + new_pos* scale , 550 + new_pos* scale }, 0+ new_pos, scale , WHITE);
            if (game.game_score == 100)
                DrawTextEx(font, TextFormat("Score : %i !!!", game.game_score), {325+ new_pos* scale , 290+ new_pos* scale }, 30+ new_pos* scale , 2+ new_pos* scale , WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
