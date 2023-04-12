
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
            SetTargetFPS(30);

            this->init();

            while (!WindowShouldClose()) // Detect window close button or ESC key
            {
                BeginDrawing();
                    ClearBackground(BLACK);
                    
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
            float hauteur = 450.0;
            float largeur = 800.0;
            int tailleMur = 15;

            // Charger l'image
            Image image = LoadImage("../assets/mur.png");

            // Redimensionner l'image en 15x15
            ImageResize(&image, 15, 15);

           

            std::vector<std::any> tabWall; 
    
            for (float x = 0; x < largeur; x+= 15)
            {
                auto wall = _ecs.spawn_entity();
                _ecs.add_component<Position>(wall, {x, 0.0});
                _ecs.add_component<Drawable>(wall, {true, LoadTextureFromImage(image)});
                _ecs.add_component<Killable>(wall, {true});
                _ecs.add_component<Movable>(wall, {false, 'z', 's', 'q', 'd'});
                tabWall.push_back(wall);
            }
    
            for (float x = 0; x < largeur; x+= 15)
            {
                auto wall = _ecs.spawn_entity();
                _ecs.add_component<Position>(wall, {x, hauteur-tailleMur});
                _ecs.add_component<Drawable>(wall, {true, LoadTextureFromImage(image)});
                _ecs.add_component<Killable>(wall, {true});
                _ecs.add_component<Movable>(wall, {false, 'z', 's', 'q', 'd'});
                tabWall.push_back(wall);
            }
    
            for (float y = 0; y < hauteur; y+= 15)
            {
                auto wall = _ecs.spawn_entity();
                _ecs.add_component<Position>(wall, {0.0, y});
                _ecs.add_component<Drawable>(wall, {true, LoadTextureFromImage(image)});
                _ecs.add_component<Killable>(wall, {true});
                _ecs.add_component<Movable>(wall, {false, 'z', 's', 'q', 'd'});
                tabWall.push_back(wall);
            }

             for (float y = 0; y < hauteur; y+= 15)
            {
                auto wall = _ecs.spawn_entity();
                _ecs.add_component<Position>(wall, {largeur-tailleMur, y});
                _ecs.add_component<Drawable>(wall, {true, LoadTextureFromImage(image)});
                _ecs.add_component<Killable>(wall, {true});
                _ecs.add_component<Movable>(wall, {false, 'z', 's', 'q', 'd'});
                tabWall.push_back(wall);
            }
            
            auto background = _ecs.spawn_entity();
            _ecs.add_component<Position>(background, {0, 0});
            _ecs.add_component<Drawable>(background, {true, LoadTexture("../assets/background.png")});
            _ecs.add_component<Killable>(background, {true});
            _ecs.add_component<Movable>(background, {false, 'z', 's', 'q', 'd'});


/*
            //box a explosé    
            auto box = _ecs.spawn_entity();
            _ecs.add_component<Position>(box, {0, 0});
            _ecs.add_component<Drawable>(box, {true, LoadTexture("../assets/box.png")});
            _ecs.add_component<Killable>(box, {true});
            _ecs.add_component<Movable>(box, {false, 'z', 's', 'q', 'd'});


            auto player1 = _ecs.spawn_entity();
            _ecs.add_component<Position>(player1, {0, 10});
            _ecs.add_component<Drawable>(player1, {true, LoadTexture("../assets/player.png")});
            _ecs.add_component<Killable>(player1, {true});
            _ecs.add_component<Movable>(player1, {true, 'z', 's', 'q', 'd'});

            auto player2 = _ecs.spawn_entity();
            _ecs.add_component<Position>(player2, {10, 0});
            _ecs.add_component<Drawable>(player2, {true, LoadTexture("../assets/player.png")});
            _ecs.add_component<Killable>(player2, {true});
            _ecs.add_component<Movable>(player2, {true, 'z', 's', 'q', 'd'});


            // ??? initialisation des bombes pour le/les joueurs ? 
            auto bomb = _ecs.spawn_entity();
            _ecs.add_component<Position>(bomb, {0, 0});
            _ecs.add_component<Drawable>(bomb, {true, LoadTexture("../assets/bomb.png")});
            _ecs.add_component<Killable>(bomb, {true});
            _ecs.add_component<Movable>(bomb, {false, 'z', 's', 'q', 'd'});


*/
        }

        void update() {

        }

        void render2D() {
            
            //BeginDrawing(); // faut pas le mettre ici sinon le programme essaye de dessiner 2 fois
            
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

            //EndDrawing(); // faut pas le mettre ici sinon le programme essaye d'arreter de dessiner 2 fois
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
