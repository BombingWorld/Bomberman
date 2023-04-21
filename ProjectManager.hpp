
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
#include "MenuAccueil.hpp"
#include "MenuParametrePartie.hpp"

class ProjectManager
{
public:
    ProjectManager()
    {
        nbJoueur = 2;
        for (int i = 0; i < 4; i++) {
            SkinJoueurs[i] = i + 1; // Choix du skin entre 1 et 6, avec i=joueur entre 0 et 3
        }
        puissanceBombes = 1;
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

        /// Ajout des menus ///
        MenuAccueil* ManuA = new MenuAccueil(screenWidth, screenHeight);
        if(ManuA->AfficheMenuAccueil()){
            return 0;
        }
        delete ManuA;


        MenuParametrePartie* MenuP = new MenuParametrePartie(screenWidth, screenHeight);
        if(MenuP->AfficheParametrePartie(nbJoueur, SkinJoueurs, puissanceBombes)){
            return 0;
        }
        delete MenuP;

        /// fin des menus ///
        

        this->init();

        while (!WindowShouldClose())
        { // Detect window close button or ESC key
            if (this->update(puissanceBombes) == 0) {
                CloseAudioDevice();
                CloseWindow();
                return 1;
            }
             
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

    int update(int puissanceJoueurs);

    void event();

    void render2D();

    std::vector<std::string> getMap()
    {

        std::vector<std::vector<std::string>> map = {};

        map.push_back(
            {"xxxxxxxxxxxxxxxx",
             "xp xx x xx xx px",
             "x bbbbbbbbbbbb x",
             "xbbxxbxxbbxbxxbx",
             "xbbbbbbbbbbbbbbx",
             "xbxbxbxbxbxbxbbx",
             "xbbbbbbbbbbbbbbx",
             "xbxbxbxbxbxbxbbx",
             "xbbbbbbbbbbbbbbx",
             "x xbxbxbxbxbxb x",
             "xp bbbxbbbbbb px",
             "xxxxxxxxxxxxxxxx"});

             map.push_back(
            {"xxxxxxxxxxxxxxxx",
             "x              x",
             "x              x",
             "xb             x",
             "x              x",
             "x              x",
             "x              x",
             "x              x",
             "x              x",
             "x              x",
             "x              x",
             "xxxxxxxxxxxxxxx"});



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

/*
"xxxxxxxxxxxxxxx"
            "xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
"xxxxxxxxxxxxxxx"
*/




                
                 

        // fait moxxxxxxandom pour choisir une map dans le vector
        //std::srand(std::time(nullptr));

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
    Image imagePlayer[6];
    Image imageBackground;
    Image imageBomb;
    Image imageFire;
    Music music;
    Sound soundPreExplosion;
    Sound soundExplosion;
    
    int nbJoueur;
    int SkinJoueurs[4]; //Recoie l'ID du skin en fonction du joueur 
    unsigned int puissanceBombes;
};

#endif /* !ECS_COMPONENT_HPP_ */
