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
        int up;      // si l'entité peux se déplacer en avant ou non
        int down;    // si l'entité peux se déplacer en arrière ou non
        int left;     // si l'entité peux se déplacer à gauche ou non
        int right;     // si l'entité peux se déplacer à droite ou non
    };

    struct Dropable {
        int drop;
    };

    struct Size {
        float width;
        float height;
    };

    struct Animable {
        float x;
        float y;
        float width;
        float height;
        float offsetX;
        float offsetY;
        float frameX;
        float frameY;
        float maxFrameX;
        float maxFrameY;
    };

struct project_config {
    using components_list = std::tuple<Position, Drawable, Killable, Movable, Collidable, Dropable, Size, Animable>;
};


#endif /* !ECS_COMPONENT_HPP_ */
