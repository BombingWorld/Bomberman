
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

    #include "cmath"

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
            InitWindow(screenWidth, screenHeight, "Bomberman");

            // Chargement de l'image pour l'icône de fenêtre
            Image icon = LoadImage("../assets/icon.png");
            SetWindowIcon(icon);
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
            const int TAILLE_PLAYER = 40;

            const std::vector<std::string> map = {
                "xxxxxxxxxxxxxxxx",
                "xp            px",
                "x   x    xx xx x",
                "xbbbbbbbbbb bbbx",
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
            for (int i = 0; i < 4; i++)
                this->imagePlayer[i] = LoadImage(std::string("../assets/player" + std::to_string(i + 1) + ".png").c_str());
            this->imageBackground = LoadImage("../assets/background.png");
            this->imageBomb = LoadImage("../assets/bomb.png");
            

            // Redimensionner l'image en 15x15
            ImageResize(&imageMur, TAILLE_MUR, TAILLE_MUR / 1.2);
            ImageResize(&imageBox, TAILLE_MUR, TAILLE_MUR / 1.2);
            for (int i = 0; i < 4; i++)
                ImageResize(&imagePlayer[i], TAILLE_PLAYER * 6, TAILLE_PLAYER * 4);
            ImageResize(&imageBomb, 50, 50);

            auto background = _ecs.spawn_entity();
            _ecs.add_component<Position>(background, {0, 0});
            _ecs.add_component<Drawable>(background, {LoadTextureFromImage(imageBackground)});
           DrawTextureRec(LoadTextureFromImage(imageBackground), {0, 0, 1080, 600}, {0, 0}, WHITE);
            //init from map
            const int NBPLAYERMAX = 4;
            int nbPlayer = 0;
            const int playerKeys[][5] = {{KEY::Z, KEY::Q, KEY::S, KEY::D, KEY::E},{KEY::T, KEY::F, KEY::G, KEY::H, KEY::Y}, {KEY::I, KEY::J, KEY::K, KEY::L, KEY::O}, {KEY::UP, KEY::LEFT, KEY::DOWN, KEY::RIGHT, KEY::ENTER}} ;
            for (int i = 0; i < map.size(); i++) {
                for (int j = 0; j < map[i].size(); j++) {
                    if (map[i][j] == 'x') {
                        auto wall = _ecs.spawn_entity();
                        _ecs.add_component<Position>(wall, {float(j * TAILLE_MUR), float(i * (TAILLE_MUR / 1.2))});
                        _ecs.add_component<Collidable>(wall, {});
                        _ecs.add_component<Drawable>(wall, {LoadTextureFromImage(imageMur)});
                        _ecs.add_component<Size>(wall, {float(TAILLE_MUR), float(TAILLE_MUR / 1.2)});
                    } else if (map[i][j] == 'b') {
                        auto box = _ecs.spawn_entity();
                        _ecs.add_component<Position>(box, {float(j * TAILLE_MUR), float(i * (TAILLE_MUR / 1.2))});
                        _ecs.add_component<Collidable>(box, {});
                        _ecs.add_component<Drawable>(box, {LoadTextureFromImage(imageBox)});
                        _ecs.add_component<Size>(box, {float(TAILLE_MUR), float(TAILLE_MUR / 1.2)});
                    } else if (map[i][j] == 'p') {
                        if (nbPlayer > NBPLAYERMAX) { break; }
                        auto player = _ecs.spawn_entity();
                        _ecs.add_component<Position>(player, {float(j * TAILLE_MUR), float(i * (TAILLE_MUR / 1.2))});
                        _ecs.add_component<Drawable>(player, {LoadTextureFromImage(imagePlayer[nbPlayer])});
                        _ecs.add_component<Movable>(player, {playerKeys[nbPlayer][0], playerKeys[nbPlayer][2], playerKeys[nbPlayer][1], playerKeys[nbPlayer][3]});
                        _ecs.add_component<Collidable>(player, {});
                        _ecs.add_component<Dropable>(player, {playerKeys[nbPlayer][4]});
                        _ecs.add_component<Size>(player, {float(TAILLE_PLAYER), float(TAILLE_PLAYER)});
                        _ecs.add_component<Animable>(player, {0,0,40,40,40,40,0,0,6,4});
                        nbPlayer++;
                    }
                }
            }            
        }

        void update() {

        }

        void event() {
            // Update les entités avec le composant Movable
            auto &positions =  _ecs.get_components<Position>();
            auto &sizes     =  _ecs.get_components<Size>();            

            auto &movables  =  _ecs.get_components<Movable>();
            auto &dropables =  _ecs.get_components<Dropable>();
            auto &collidables =  _ecs.get_components<Collidable>();
            auto &animables = _ecs.get_components<Animable>();

            for (int i = 0; i < movables.size() && i < positions.size(); i++) {
                Position velocity = {0, 0};
                if (movables[i] && positions[i]) {
                    if (IsKeyDown(movables[i]->up)) {
                       velocity.y = -5;
                    }
                    if (IsKeyDown(movables[i]->down)) {
                        velocity.y = +5;
                    }
                    if (IsKeyDown(movables[i]->left)) {
                        velocity.x = -5;
                    }
                    if (IsKeyDown(movables[i]->right)) {
                        velocity.x = 5;
                    }
                } 

                for (int j = 0; j < collidables.size() && j < positions.size() && j < sizes. size(); j++) {
                    if (i != j && CheckCollisionRecs({positions[i]->x + velocity.x , positions[i]->y, sizes[i]->width, sizes[i]->height},
                                                    {positions[j]->x ,positions[j]->y, sizes[j]->width, sizes[j]->height}))
                        velocity.x = 0;
                    if (i != j && CheckCollisionRecs({positions[i]->x, positions[i]->y + velocity.y, sizes[i]->width, sizes[i]->height},
                                                    {positions[j]->x ,positions[j]->y, sizes[j]->width, sizes[j]->height}))
                        velocity.y = 0;
                };
                positions[i]->x += velocity.x;
                positions[i]->y += velocity.y;
                if (movables[i] && velocity.x != 0)
                    animables[i]->y = animables[i]->offsetY * ((velocity.x < 0)? 1: 2);
                if (movables[i] && velocity.y != 0)
                    animables[i]->y = animables[i]->offsetY * ((velocity.y < 0)? 0: 3);

                if ((velocity.x != 0 || velocity.y != 0) && i < animables.size() && animables[i] ) {
                    if (animables[i]->frameX < animables[i]->maxFrameX)
                        animables[i]->x += animables[i]->offsetX;
                    else
                        animables[i]->x = 0;
                }
                    

                if (dropables[i] && positions[i] && IsKeyDown(dropables[i]->drop)) { //create bomb
                        auto bomb = _ecs.spawn_entity();
                        _ecs.add_component<Position>(bomb, { positions[i]->x - fmod(positions[i]->x, float(50)) , positions[i]->y - fmod(positions[i]->y, float(50))});
                        _ecs.add_component<Drawable>(bomb, {LoadTextureFromImage(imageBomb)});
                        _ecs.add_component<Animable>(bomb, {0,0,50,50,50,50,0,0,3,1});
                }
            }
        }

        void render2D() {
                        
            // Dessiner les entités avec le composant Drawable
            auto &drawables = _ecs.get_components<Drawable>();
            auto &positions = _ecs.get_components<Position>();
            auto &movables = _ecs.get_components<Movable>();
            auto &animables = _ecs.get_components<Animable>(); 

            for (int i = 0; i < drawables.size(); i++) {
                if (drawables[i] && positions[i] && !movables[i]) {
                    DrawTexture(drawables[i]->texture, positions[i]->x, positions[i]->y, WHITE);
                }
            }
            for (int i = 0; i < drawables.size(); i++) {
                if (drawables[i] && positions[i] && movables[i]) {
                    DrawTextureRec(drawables[i]->texture, {animables[i]->x, animables[i]->y, animables[i]->width, animables[i]->height},{positions[i]->x, positions[i]->y},  WHITE);
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
        Image imagePlayer[4];
        Image imageBackground;
        Image imageBomb;

};

#endif /* !ECS_COMPONENT_HPP_ */
