
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
        int Run()  {
            const int screenWidth = 800;
            const int screenHeight = 450;

            InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
            SetTargetFPS(244);

            this->init();

            while (!WindowShouldClose()) // Detect window close button or ESC key
            {
                BeginDrawing();
                    ClearBackground(BLACK);
                    
                    this->render2D();
                    //DrawText("Congrats! You created your first window!", 190, 200, 20,(Color){LIGHTGRAY});
                EndDrawing();
            }
            CloseWindow();
            return 0;
        }

//////////////////////////////////////////////////////////////////////////////////////////////

        void init() {
            auto background = _ecs.spawn_entity();
            _ecs.add_component<Position>(background, {0, 0});
            _ecs.add_component<Drawable>(background, {true, LoadTexture("../assets/background.png")});
        }

        void update() {

        }

        void render2D() {
            
            BeginDrawing();
            
            // Effacer l'écran avec une couleur de fond blanche
            ClearBackground(WHITE);
            
            // Dessiner les entités avec le composant Drawable
            auto &drawables = _ecs.get_components<Drawable>();
            auto &positions = _ecs.get_components<Position>();

            for (int i = 0; i < drawables.size(); i++) {
                if (drawables[i] && positions[i]) {
                    DrawTexture(drawables[i]->texture, positions[i]->x, positions[i]->y, WHITE);
                }
            }

            EndDrawing();
        }



        void render3D() {

        }

        void event() {

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
