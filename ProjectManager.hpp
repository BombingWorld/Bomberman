
#ifndef ECS_MANAGER_HPP_
    #define ECS_MANAGER_HPP_

    // std
    #include <type_traits> // std::is_same_v
    #include <iostream>
    #include <vector>
    #include <any>

    // ProjectManager
    #include "EcsComponent.hpp"
    #include "Ecs.hpp"
    #include "raylib.h"

class ProjectManager {
    public:

        ProjectManager() {
            config_extractor<project_config::components_list>::function(_ecs); //sys
        }

        ~ProjectManager() = default;

        /**
        * @brief Client
        *
        * @param ip
        * @param port
        * @return int
        */
        int Run()  {
            const int screenWidth = 1900;
            const int screenHeight = 1000;

            InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
//            ToggleFullscreen();
            SetTargetFPS(30);

            this->init();

            while (!WindowShouldClose()) { // Detect window close button or ESC key
                this->update();
                BeginDrawing();
                    ClearBackground(BLACK);
                    this->event();
                    
                    this->render2D();
                    DrawText ("Congrats! You created your first window!", 190, 200, 20,(Color){LIGHTGRAY});
                EndDrawing();
            }
            CloseWindow();
            return 0;
        }

//////////////////////////////////////////////////////////////////////////////////////////////

        void init() {

            //taille du terrain
            const int TAILLE_MUR = 50;

            const std::vector<std::string> map = {
                "xxxxxxxxxx",
                "xp      px",
                "x     x  x",
                "xbbbbbbbbx",
                "x        x",
                "x        x",
                "x        x",
                "xp      px",
                "xxxxxxxxxx",
            };

            // Charger l'image
            Image imageMur = LoadImage("../assets/mur.png");
            Image imageBox = LoadImage("../assets/box.png");

            // Redimensionner l'image en 15x15
            ImageResize(&imageMur, TAILLE_MUR, TAILLE_MUR / 1.2);
            ImageResize(&imageBox, TAILLE_MUR, TAILLE_MUR / 1.2);

            auto background = _ecs.spawn_entity();
            _ecs.add_component<Position>(background, {0, 0});
            _ecs.add_component<Drawable>(background, {LoadTexture("../assets/background.png")});
           
            //MUR{{{}}}
            for (int i = 0; i < map.size(); i++) {
                for (int j = 0; j < map[i].size(); j++) {
                    if (map[i][j] != 'x') { continue; }
                    auto wall = _ecs.spawn_entity();
                    _ecs.add_component<Position>(wall, {float(j * TAILLE_MUR), float(i * (TAILLE_MUR / 1.2))});
                    _ecs.add_component<Collidable>(wall, {});
                    _ecs.add_component<Drawable>(wall, {LoadTextureFromImage(imageMur)});
                }
            }

            //BOX
            for (int i = 0; i < map.size(); i++) {
                for (int j = 0; j < map[i].size(); j++) {
                    if (map[i][j] != 'b') { continue; }
                    auto box = _ecs.spawn_entity();
                    _ecs.add_component<Position>(box, {float(j * TAILLE_MUR), float(i * (TAILLE_MUR / 1.2))});
                    _ecs.add_component<Collidable>(box, {});
                    _ecs.add_component<Drawable>(box, {LoadTextureFromImage(imageBox)});
                }
            }
            //Player
            const nbPlayer = 4;
            const Movable playerKeys[] = [{'z','q','s','d'}, {'i','j','k','l'}, {'t','f','g','h'}, {'o','l','p','m'}int  ];
            for (int i = 0; i < map.size(); i++) {
                for (int j = 0; j < map[i].size(); j++) {
                    if (map[i][j] != 'b') { continue; }
                    auto player = _ecs.spawn_entity();
                    _ecs.add_component<Position>(player, {float(0), float(0)});
                    _ecs.add_component<Drawable>(player, {LoadTexture("../assets/player" + string(i) + ".png")});
                    _ecs.add_component<Movable>(player, playerKeys[]);
                    _ecs.add_component<Collidable>(player, {});
                }
            }

            

        }

        void update() {
            // Update les entités avec le composant Movable
            auto &movables = _ecs.get_components<Movable>();
            auto &positions = _ecs.get_components<Position>();

            for (int i = 0; i < movables.size(); i++) {
                if (movables[i] && positions[i]) {
                        if (IsKeyDown(movables[i]->up)) {
                            positions[i]->y -= 1;
                        }
                        if (IsKeyDown(movables[i]->down)) {
                            positions[i]->y += 1;
                        }
                        if (IsKeyDown(movables[i]->left)) {
                            positions[i]->x -= 1;
                        }
                        if (IsKeyDown(movables[i]->right)) {
                            positions[i]->x += 1;
                        }
                }
            }
        }

        void render2D() {
                        
            // Dessiner les entités avec le composant Drawable
            auto &drawables = _ecs.get_components<Drawable>();
            auto &positions = _ecs.get_components<Position>();

            for (int i = 0; i < drawables.size(); i++) {
                if (drawables[i] && positions[i]) {
                    DrawTexture(drawables[i]->texture, positions[i]->x, positions[i]->y, WHITE);
                }
            }

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
