
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

class ProjectManager
{
public:
    ProjectManager()
    {
        config_extractor<project_config::components_list>::function(_ecs); // sys
    }

    ~ProjectManager() = default;

    /**
     * @brief Client
     *
     * @param ip
     * @param port
     * @return int
     */
    int Run()
    {
        const int screenWidth = 800;
        const int screenHeight = 600;
        InitWindow(screenWidth, screenHeight, "Bomberman");
        InitAudioDevice(); // Initialize audio device

        // Chargement de l'image pour l'icône de fenêtre
        Image icon = LoadImage("../assets/icon.png");
        SetWindowIcon(icon);
        SetTargetFPS(30);

        this->init();

        while (!WindowShouldClose())
        { // Detect window close button or ESC key
            this->update();

            BeginDrawing();
            ClearBackground(BLACK);
            this->event();

            this->render2D();
            // DrawText ("Congrats! You created your first window!", 190, 200, 20,(Color){LIGHTGRAY});
            EndDrawing();
        }

        CloseAudioDevice();
        CloseWindow();
        return 0;
    }

    void init();

    void update();

    void event();

    void render2D();

    std::vector<std::string> getMap()
    {

        std::vector<std::vector<std::string>> map = {};

        map.push_back(
            {"xxxxxxxxxxxxxxxx",
             "xp bbbbxbbbbb px",
             "x  bbbbxbbbbb  x",
             "xbbbbbbxbbbbbbbx",
             "xbbb bbxbbb bbbx",
             "xxxxxxbbbxxxxxxx",
             "xbbbbbbxbbbbbbbx",
             "xbbb bbxbbb bbbx",
             "xbbbbbbxbbbbbbbx",
             "x  bbbbxbbbbb  x",
             "xp bbbbxbbbbb px",
             "xxxxxxxxxxxxxxxx"});

        map.push_back(
            {"xxxxxxxxxxxxxxxx",
             "xp   b  x   b px",
             "x    b  x   x  x",
             "xbbbbb  xbbbxxxbx",
             "x xxxxxxx   x  x",
             "x       x   b  x",
             "xxxxxxxbbbxxxxxx",
             "x    b  x   b px",
             "x    x  x   x  x",
             "xbbbxxxbbbbbxxxx",
             "xp   b  x   b  x",
             "xxxxxxxxxxxxxxxx"});

        map.push_back(
            {"xxxxxxxxxxxxxxxx",
             "xp  bbbbxbbb  px",
             "xxxxxxxbxbxxxxxx",
             "xbbbbbbbbbbbbbbx",
             "xxxxxxxxxxxxxbbx",
             "xbbbbbbbbbbbbbbx",
             "xxxxxxxbxxxxxxxx",
             "xbbbbbbbbbbbbbbx",
             "xxbxxxxxxxxxxbxx",
             "xbbbbbbxbbbbbbbx",
             "xp  bbbxbbbb  px",
             "xxxxxxxxxxxxxxxx"});

        // fait moxxxxxxandom pour choisir une map dans le vector
        std::srand(std::time(nullptr));

        // Sélectionner un vecteur de chaînes de caractères aléatoire
        std::vector<std::string> randomVector = map[std::rand() % map.size()];
        return randomVector;
    }

protected:
    template <class T>
    struct config_extractor
    {                                                                                                                                  // ne devrait jamais être instancié sauf erreur => gestion d'erreur
        static_assert(std::is_same<T, std::tuple<>>::value, "component_list in ComponentManager.hpp should be a tuple of Components"); // empeche la compilation si T n'est pas std::tuple<int> (ce qui ne peux jamais arriver)
    };
    template <class... Components>
    struct config_extractor<std::tuple<Components...>>
    { // overload si T est un tuple de choses. Ne clash pas avec la def précédentes

        static void function(registry &r)
        {
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
    Image imageFire;
    Music music;
    Sound soundPreExplosion;
    Sound soundExplosion;
};

#endif /* !ECS_COMPONENT_HPP_ */
