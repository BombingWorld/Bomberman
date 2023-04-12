#ifndef ECS_COMPONENT_HPP_
    #define ECS_COMPONENT_HPP_

    #include <tuple>
    #include "raylib.h"

    struct Position {
        float x;    // position de l'entité en x
        float y;    // position de l'entité en y
    };

    struct Drawable
    {
        bool is_drawable;  // si l'entité peux être dessiné ou non
        Texture2D texture; // texture de l'entité

    };

    struct Killable
    {
        bool is_killable; // si le joueur peux mourir ou non
    };
    
    struct Movable
    {
        bool is_movable; // si l'enetité peux se déplacer ou non
        char avant;      // si l'entité peux se déplacer en avant ou non
        char arriere;    // si l'entité peux se déplacer en arrière ou non
        char gauche;     // si l'entité peux se déplacer à gauche ou non
        char droite;     // si l'entité peux se déplacer à droite ou non
    };

    
    


struct project_config {
    using components_list = std::tuple<Position, Drawable, Killable, Movable>;
};


#endif /* !ECS_COMPONENT_HPP_ */
