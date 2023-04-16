
#ifndef ECS_MANAGER_HPP_
    #define ECS_MANAGER_HPP_

    // std
    #include <type_traits> // std::is_same_v
    #include <iostream>
    #include <vector>
    #include <any>
    #include <map>

    // ProjectManager
    #include "EcsComponent.hpp"
    #include "Ecs.hpp"
    #include "raylib.h"

    #include "data.hpp"

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
            const int screenWidth = 1080;
            const int screenHeight = 600;

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
                    //DrawText ("Congrats! You created your first window!", 190, 200, 20,(Color){LIGHTGRAY});
                EndDrawing();
            }
            CloseWindow();
            return 0;
        }

//////////////////////////////////////////////////////////////////////////////////////////////

        void init() {

            //taille du terrain
            const int TAILLE_MUR = 50;
            const int TAILLE_PLAYER = 25;

            const std::vector<std::string> map = {
                "xxxxxxxxxxxxxxxx",
                "x             px",
                "x   x          x",
                "xbbbbbbbbbbbbbbx",
                "x              x",          
                "x              x",
                "x              x",
                "xxxxxxxxxxbbbbxx",
                "x            b x",
                "x .          b x",
                "x            b x",
                "x              x",
                "xp            px",
                "xxxxxxxxxxxxxxxx",
            };

            // Charger l'image
            this->imageMur = LoadImage("../assets/wall.png");
            this->imageBox = LoadImage("../assets/box.png");
            this->imagePlayer1 = LoadImage("../assets/player1.png");
            this->imagePlayer2 = LoadImage("../assets/player2.png");
            this->imagePlayer3 = LoadImage("../assets/player3.png");
            this->imagePlayer4 = LoadImage("../assets/player4.png");
            this->imageBackground = LoadImage("../assets/background.png");

            // Redimensionner l'image en 15x15
            ImageResize(&imageMur, TAILLE_MUR, TAILLE_MUR / 1.2);
            ImageResize(&imageBox, TAILLE_MUR, TAILLE_MUR / 1.2);
            ImageResize(&imagePlayer1, TAILLE_PLAYER, TAILLE_PLAYER);
            ImageResize(&imagePlayer2, TAILLE_PLAYER, TAILLE_PLAYER);
            ImageResize(&imagePlayer3, TAILLE_PLAYER, TAILLE_PLAYER);
            ImageResize(&imagePlayer4, TAILLE_PLAYER, TAILLE_PLAYER);

            auto background = _ecs.spawn_entity();
            _ecs.add_component<Position>(background, {0, 0});
            _ecs.add_component<Drawable>(background, {LoadTextureFromImage(imageBackground)});
           
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
            const int nbPlayer = 4;
            const int playerKeys[][5] = {{KEY::Z, KEY::Q, KEY::S, KEY::D, KEY::E}} ;
            for (int i = 0, p = 0; i < map.size(); i++) {
                for (int j = 0; j < map[i].size(); j++) {
                    if (map[i][j] != 'p') { continue; }
                    if (p > nbPlayer) { break; }

                    auto player = _ecs.spawn_entity();

                    _ecs.add_component<Position>(player, {float(j * TAILLE_MUR), float(i * (TAILLE_MUR / 1.2))});
                    _ecs.add_component<Drawable>(player, {LoadTextureFromImage(imagePlayer1)});
                    _ecs.add_component<Movable>(player, {playerKeys[p][0], playerKeys[p][2], playerKeys[p][1], playerKeys[p][3]});
                    _ecs.add_component<Collidable>(player, {});
                    _ecs.add_component<Dropable>(player, {playerKeys[0][4]});
                }
            }


            

        }

        void update() {

        }

        void event() {

//            if (IsKeyPressed(KEY::Z))

            // Update les entités avec le composant Movable
            auto &movables = _ecs.get_components<Movable>();
            auto &positions = _ecs.get_components<Position>();
            auto &dropables = _ecs.get_components<Dropable>();

            

            for (int i = 0; i < movables.size() && i < movables.size(); i++) {
                if (movables[i] && positions[i]) {
                    std::cout << "idx=" << i << std::endl;
                    std::cout << "KEY::Z=" << KEY::Z << " == " << "movables[i]->up=" << movables[i]->up << std::endl;
                    if (IsKeyDown(KEY::Z))
                        std::cout << "key Z pressed" << std::endl;
                    if (IsKeyDown(movables[i]->up)) {
                        std::cout << ">" << positions[i]->y << std::endl;
                        positions[i]->y -= 5;
                    }
                     if (IsKeyDown(movables[i]->down)) {
                        positions[i]->y += 5;
                    }
                    if (IsKeyDown(movables[i]->left)) {
                        positions[i]->x -= 5;
                    }
                    if (IsKeyDown(movables[i]->right)) {
                        positions[i]->x += 5;
                    }

                    if (IsKeyDown(movables[i]->right)) {
                        positions[i]->x += 5;
                    }

                    if (IsKeyDown(dropables[i]->drop))
                    {
                        // creation image bombe
                        Image imageBomb = LoadImage("../assets/dogs.png");
                        ImageResize(&imageBomb, 50, 50);


                        auto bomb = _ecs.spawn_entity();
                        _ecs.add_component<Position>(bomb, { positions[i]->x , positions[i]->y });
                        _ecs.add_component<Drawable>(bomb, {LoadTextureFromImage(imageBomb)});
                        
                    }
                    
                }
            }
        }


        void render2D() {
                        
            // Dessiner les entités avec le composant Drawable
            auto &drawables = _ecs.get_components<Drawable>();
            auto &positions = _ecs.get_components<Position>();
            auto &movables = _ecs.get_components<Movable>();

            for (int i = 0; i < drawables.size(); i++) {
                if (drawables[i] && positions[i]) {
//                    if (movables[i])
//                        std::cout << positions[i]->y << std::endl;                    
                    DrawTexture(drawables[i]->texture, positions[i]->x, positions[i]->y, WHITE);
                }
            }

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

    protected:
        Image imageMur;
        Image imageBox;
        Image imagePlayer1;
        Image imagePlayer2;
        Image imagePlayer3;
        Image imagePlayer4;
        Image imageBackground;
};

#endif /* !ECS_COMPONENT_HPP_ */
