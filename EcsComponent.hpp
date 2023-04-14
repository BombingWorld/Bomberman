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
        Texture2D texture; // texture de l'entité
    };

    struct Killable {
    };
    
    struct Collidable {

    };

    struct Movable {
        char up;      // si l'entité peux se déplacer en avant ou non
        char down;    // si l'entité peux se déplacer en arrière ou non
        char left;     // si l'entité peux se déplacer à gauche ou non
        char right;     // si l'entité peux se déplacer à droite ou non
    };


struct project_config {
    using components_list = std::tuple<Position, Drawable, Killable, Movable, Collidable>;
};


#endif /* !ECS_COMPONENT_HPP_ */
