#include <stdio.h>

#include "raylib.h"
#include "GLFW/glfw3.h"
#include "lib/local_lib.h"
#include "lib/objects.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

using namespace std;

int main()
{
    int window_width = GetScreenWidth();
    int window_height = GetScreenHeight();

    int render_width = 320;
    int render_height = 240;


    InitWindow(window_width, window_height, "debug");
    const RenderTexture2D target = LoadRenderTexture(render_width, render_height);

    //ToggleFullscreen();
    HideCursor();

    float deltaTime = 0.0f;

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime()*100;
        float scale = MIN((float)GetScreenWidth()/render_width, (float)GetScreenHeight()/render_height);

        player.update(deltaTime);

        BeginTextureMode(target);
            ClearBackground(BLACK);

            player.draw();
            draw_tiles();
            debug_menu();

        EndTextureMode();


    BeginDrawing();

        ClearBackground(BLACK);
        DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                           (Rectangle){ (GetScreenWidth() - ((float)render_width*scale))*0.5f, (GetScreenHeight() - ((float)render_height*scale))*0.5f,
                           (float)render_width*scale, (float)render_height*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);
    EndDrawing();
}

    CloseWindow();

    return 0;
}