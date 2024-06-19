#include "raylib.h"
#include "lib/local_lib.h"
#include "lib/objects.h"
#include "lib/scene_constructor.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

using namespace std;

int main() {
    // int window_width = GetScreenWidth();
    // int window_height = GetScreenHeight();

    constexpr int window_width = 1280;
    constexpr int window_height = 960;

    constexpr int render_width = 320;
    constexpr int render_height = 240;


    InitWindow(window_width, window_height, "debug");

    const RenderTexture2D target = LoadRenderTexture(render_width, render_height);

    // ToggleFullscreen();
    // ToggleBorderlessWindowed();
    HideCursor();

    SetTargetFPS(10000);

    SetWindowState(FLAG_WINDOW_RESIZABLE);

    scene.load_scene();

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime() * 100;

        if (deltaTime > 5) {
            deltaTime = 0;
        }
        const float scale = MIN((float)GetScreenWidth()/render_width, (float)GetScreenHeight()/render_height);


        BeginDrawing();

        BeginTextureMode(target);
        player.update_player(deltaTime);
        ClearBackground(BLACK);

        player.draw();
        scene.draw_scene();
        EndTextureMode();
        ClearBackground(BLACK);
        DrawTexturePro(target.texture,
                       (Rectangle){
                           0.0f, 0.0f, static_cast<float>(target.texture.width),
                           static_cast<float>(-target.texture.height)
                       },
                       (Rectangle){
                           (static_cast<float>(GetScreenWidth()) - (static_cast<float>(render_width) * scale)) * 0.5f,
                           (static_cast<float>(GetScreenHeight()) - (static_cast<float>(render_height) * scale)) * 0.5f,
                           static_cast<float>(render_width) * scale, static_cast<float>(render_height) * scale
                       }, (Vector2){0, 0}, 0.0f, WHITE);

        debug_menu();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
