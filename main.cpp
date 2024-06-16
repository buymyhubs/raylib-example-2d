#include <stdio.h>

#include "raylib.h"
#include "GLFW/glfw3.h"
#include "lib/local_lib.h"
#include "lib/objects.h"
#include "lib/scene_constructor.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

using namespace std;

int main()
{
    // int window_width = GetScreenWidth();
    // int window_height = GetScreenHeight();

    int window_width = 1280;
    int window_height = 960;

    int render_width = 320;
    int render_height = 240;


    InitWindow(window_width, window_height, "debug");

    const RenderTexture2D target = LoadRenderTexture(render_width, render_height);

    //ToggleFullscreen();
    ToggleBorderlessWindowed();
    HideCursor();

    float deltaTime = 0.0f;

    SetTargetFPS(60);

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    scene.load_scene();

    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime()*100;
        float scale = MIN((float)GetScreenWidth()/render_width, (float)GetScreenHeight()/render_height);


        BeginDrawing();

            BeginTextureMode(target);
                player.update_player(deltaTime);
                ClearBackground(BLACK);

                player.draw();
                scene.draw_scene();
            EndTextureMode();
            ClearBackground(BLACK);
            DrawTexturePro(target.texture, (Rectangle){ 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height },
                               (Rectangle){ (GetScreenWidth() - ((float)render_width*scale))*0.5f, (GetScreenHeight() - ((float)render_height*scale))*0.5f,
                               (float)render_width*scale, (float)render_height*scale }, (Vector2){ 0, 0 }, 0.0f, WHITE);

            debug_menu();
        EndDrawing();
}

    CloseWindow();

    return 0;
}