
#ifndef ECS_MANAGER_HPP_
    #define ECS_MANAGER_HPP_

    // std
    #include <type_traits> // std::is_same_v
    #include <iostream>

    // ProjectManager
    #include "EcsComponent.hpp"
    #include "Ecs.hpp"
    #include "raylib.h"

class ProjectManager {
    public:

        ProjectManager()
        {
            config_extractor<project_config::components_list>::function(_ecs); //sys
        };

        ~ProjectManager() = default;

        /**
        * @brief Client
        *
        * @param ip
        * @param port
        * @return int
        */
        int Start()  {
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

    protected:

        /**
        * @brief Config Extractor (default will make the compilation failed) [Dark C++]
        * @def the config extractor is used to extract all component need at the start of the program
        */
        template <class T>
        struct config_extractor { // ne devrait jamais être instancié sauf erreur => gestion d'erreur
            static_assert(std::is_same<T, std::tuple<>>::value, "component_list in ComponentManager.hpp should be a tuple of Components"); // empeche la compilation si T n'est pas std::tuple<int> (ce qui ne peux jamais arriver)
        };

        /**
        * @brief Config Extractor (specification won't make the compilation failed) [Dark C++]
        * @def the config extractor is used to extract all component need at the start of the program
        */
        template <class ... Components>
        struct config_extractor<std::tuple<Components...>> { // overload si T est un tuple de choses. Ne clash pas avec la def précédentes

            /**
            * @brief this function will extract all component need at the start of the program and register them in the ECS
            */
            static void function(registry &r) {
                (r.register_component<Components>(), ...);
            }
        };

    protected:
        registry _ecs;

    public:
};

#endif /* !ECS_COMPONENT_HPP_ */
