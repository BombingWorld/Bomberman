#include "raylib.h"

class ProjectManager {
    public:
        ProjectManager() {

        }

        ~ProjectManager() = default;

        int Start() {
            const int screenWidth = 800;
            const int screenHeight = 450;

            InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
            SetTargetFPS(60);
            while (!WindowShouldClose()) // Detect window close button or ESC key
            {
                BeginDrawing();
                    ClearBackground(RAYWHITE);
                    DrawText("Congrats! You created your first window!", 190, 200, 20,(Color){LIGHTGRAY});
                EndDrawing();
            }
            CloseWindow();
            return 0;
        }

};