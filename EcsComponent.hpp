#ifndef ECS_COMPONENT_HPP_
    #define ECS_COMPONENT_HPP_

    #include <tuple>
    #include "raylib.h"

    struct Position {
        float x;
        float y;
    };

    struct Drawable
    {
        bool is_drawable;
        Texture2D texture;

    };
    


struct project_config {
    using components_list = std::tuple<Position, Drawable>;
};


#endif /* !ECS_COMPONENT_HPP_ */
