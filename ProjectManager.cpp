
#include "ProjectManager.hpp"
#include "raylib.h"

void ProjectManager::init()
{
    // musique
    music = LoadMusicStream("../assets/music/musicFon.mp3");
    soundPreExplosion = LoadSound("../assets/music/ala.mps3"); // Load WAV audio file
    soundExplosion = LoadSound("../assets/explosion.mp3");   // Load OGG audio file

    PlayMusicStream(music);
    SetMusicVolume(music, 1);

    // Charger l'image
    this->imageMur = LoadImage("../assets/wall.png");
    this->imageBox = LoadImage("../assets/box.png");
    for (int i = 0; i < 4; i++)
        this->imagePlayer[i] = LoadImage(std::string("../assets/player" + std::to_string(i + 1) + ".png").c_str());
    this->imageBackground = LoadImage("../assets/lava.png");
    this->imageBomb = LoadImage("../assets/bomb.png");
    this->imageFire = LoadImage("../assets/fire.png");

    // Redimensionner l'image en 15x15
    ImageResize(&imageMur, TAILLE_MUR, TAILLE_MUR);
    ImageResize(&imageBox, TAILLE_MUR, TAILLE_MUR);
    for (int i = 0; i < 4; i++)
        ImageResize(&imagePlayer[i], TAILLE_PLAYER * 6, TAILLE_PLAYER * 4);
    ImageResize(&imageBomb, 150, 50);
    ImageResize(&imageFire, 250, 200);

    /* auto background = _ecs.spawn_entity();
     _ecs.add_component<Position>(background, {0, 0});
     _ecs.add_component<Drawable>(background, {LoadTextureFromImage(imageBackground)});*/

    // init from map
    const int NBPLAYERMAX = 4;
    const std::vector<std::string> map = getMap();
    int nbPlayer = 0;
    const int playerKeys[][5] = {{KEY::Z, KEY::Q, KEY::S, KEY::D, KEY::E}, {KEY::T, KEY::F, KEY::G, KEY::H, KEY::Y}, {KEY::I, KEY::J, KEY::K, KEY::L, KEY::O}, {KEY::UP, KEY::LEFT, KEY::DOWN, KEY::RIGHT, KEY::ENTER}};
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == 'x')
            {
                auto wall = _ecs.spawn_entity();
                _ecs.add_component<Position>(wall, {float(j * TAILLE_MUR), float(i * (TAILLE_MUR))});
                _ecs.add_component<Collidable>(wall, {});
                _ecs.add_component<Drawable>(wall, {LoadTextureFromImage(imageMur)});
                _ecs.add_component<Size>(wall, {float(TAILLE_MUR), float(TAILLE_MUR)});
                _ecs.add_component<Scene>(wall, {1});
            }
            else if (map[i][j] == 'b')
            {
                auto box = _ecs.spawn_entity();
                _ecs.add_component<Position>(box, {float(j * TAILLE_MUR), float(i * (TAILLE_MUR))});
                _ecs.add_component<Collidable>(box, {});
                _ecs.add_component<Drawable>(box, {LoadTextureFromImage(imageBox)});
                _ecs.add_component<Size>(box, {float(TAILLE_MUR), float(TAILLE_MUR)});
                _ecs.add_component<Killable>(box, {});
                _ecs.add_component<Scene>(box, {1});
            }
            else if (map[i][j] == 'p')
            {
                if (nbPlayer > NBPLAYERMAX)
                {
                    break;
                }
                auto player = _ecs.spawn_entity();
                _ecs.add_component<Position>(player, {float(j * TAILLE_MUR), float(i * (TAILLE_MUR))});
                _ecs.add_component<Drawable>(player, {LoadTextureFromImage(imagePlayer[nbPlayer])});
                _ecs.add_component<Movable>(player, {playerKeys[nbPlayer][0], playerKeys[nbPlayer][2], playerKeys[nbPlayer][1], playerKeys[nbPlayer][3]});
                _ecs.add_component<Collidable>(player, {});
                _ecs.add_component<Dropable>(player, {playerKeys[nbPlayer][4]});
                _ecs.add_component<Size>(player, {float(TAILLE_PLAYER), float(TAILLE_PLAYER)});
                _ecs.add_component<Animable>(player, {0, 0, 40, 40, 40, 40, 0, 0, 6, 4});
                _ecs.add_component<Power>(player, {1});
                _ecs.add_component<Killable>(player, {});
                _ecs.add_component<Scene>(player, {1});

                nbPlayer++;
            }
        }
    }
}

void ProjectManager::update()
{
    auto &animables = _ecs.get_components<Animable>();
    auto &explodables = _ecs.get_components<Explodable>();
    auto &positions = _ecs.get_components<Position>();
    auto &powers = _ecs.get_components<Power>();
    auto &killables = _ecs.get_components<Killable>();
    auto &burnables = _ecs.get_components<Burnable>();
    auto &movables = _ecs.get_components<Movable>();

    UpdateMusicStream(music);

    for (int i = 0; i < animables.size() && i < explodables.size(); i++)
    {
        if (animables[i] && explodables[i] && positions[i] && powers[i])
        {
            std::cout << 1 << std::endl;
            if (explodables[i]->time > GetTime())
            {
                int value = static_cast<int>(2 - std::floor(explodables[i]->time - GetTime()));
                animables[i]->x = animables[i]->offsetX * value;
            }
            else
            {
                for (int compass = 0; compass < 5; compass++)
                {
                    for (int range = 1; range <= powers[i]->range; range++)
                    {
                        Position firePos = {positions[i]->x + ((bombVar[compass] / 10) * range * 50), positions[i]->y + ((bombVar[compass] % 10) * range * 50)};
                        // remove erverything
                        for (int j = 0; j < positions.size() && j < killables.size(); j++)
                        {
                            if (positions[j] && killables[j] && i != j && firePos.x == (positions[j]->x - fmod(positions[j]->x, float(50))) && firePos.y == (positions[j]->y - fmod(positions[j]->y, float(50))))
                            {
                                _ecs.kill_entity(_ecs.entity_from_index(j));
                                PlaySound(soundExplosion);
                            }
                        }
                        auto fire = _ecs.spawn_entity();
                        _ecs.add_component<Position>(fire, {firePos.x, firePos.y});
                        _ecs.add_component<Drawable>(fire, {LoadTextureFromImage(imageFire)});
                        _ecs.add_component<Animable>(fire, {100, 0, 50, 50, 50, 50, 0, 0, 1, 1});
                        _ecs.add_component<Burnable>(fire, {GetTime() + 1.0});
                        _ecs.add_component<Power>(fire, {powers[i]->range});
                        _ecs.add_component<Scene>(fire, {1});
                        
                    }
                }
                _ecs.kill_entity(_ecs.entity_from_index(i));
            }
        }
    }
    for (int i = 0; i < burnables.size(); i++)
    {
        if (burnables[i] && burnables[i]->time < GetTime())
        {
            _ecs.kill_entity(_ecs.entity_from_index(i));
        }
    }
    int howmanyplayer = 0;
    for (int i = 0, j = 0; i < movables.size(); i++)
    {
        if (movables[i])
        {
            howmanyplayer++;
        }
    }
    if (howmanyplayer < 2)
        exit(EXIT_SUCCESS);
}

void ProjectManager::event()
{
    // Update les entités avec le composant Movable
    auto &positions = _ecs.get_components<Position>();
    auto &sizes = _ecs.get_components<Size>();
    auto &movables = _ecs.get_components<Movable>();
    auto &dropables = _ecs.get_components<Dropable>();
    auto &collidables = _ecs.get_components<Collidable>();
    auto &animables = _ecs.get_components<Animable>();
    auto &powers = _ecs.get_components<Power>();

    for (int i = 0; i < movables.size() && i < positions.size(); i++)
    {
        Position velocity = {0, 0};
        if (movables[i] && positions[i])
        {
            if (IsKeyDown(movables[i]->up))
            {
                velocity.y = -5;
            }
            if (IsKeyDown(movables[i]->down))
            {
                velocity.y = +5;
            }
            if (IsKeyDown(movables[i]->left))
            {
                velocity.x = -5;
            }
            if (IsKeyDown(movables[i]->right))
            {
                velocity.x = 5;
            }
        }

        for (int j = 0; j < collidables.size() && j < positions.size() && j < sizes.size(); j++)
        {
            if (i != j && collidables[j] && CheckCollisionRecs({positions[i]->x + velocity.x, positions[i]->y, sizes[i]->width, sizes[i]->height}, {positions[j]->x, positions[j]->y, sizes[j]->width, sizes[j]->height}))
                velocity.x = 0;
            if (i != j && collidables[j] && CheckCollisionRecs({positions[i]->x, positions[i]->y + velocity.y, sizes[i]->width, sizes[i]->height}, {positions[j]->x, positions[j]->y, sizes[j]->width, sizes[j]->height}))
                velocity.y = 0;
        };
        positions[i]->x += velocity.x;
        positions[i]->y += velocity.y;
        if (movables[i] && velocity.x != 0)
            animables[i]->y = animables[i]->offsetY * ((velocity.x < 0) ? 1 : 2);
        if (movables[i] && velocity.y != 0)
            animables[i]->y = animables[i]->offsetY * ((velocity.y < 0) ? 0 : 3);

        if ((velocity.x != 0 || velocity.y != 0) && i < animables.size() && animables[i])
        {
            if (animables[i]->frameX < animables[i]->maxFrameX)
                animables[i]->x += animables[i]->offsetX;
            else
                animables[i]->x = 0;
        }

        if (dropables[i] && positions[i] && powers[i] && IsKeyDown(dropables[i]->drop))
        { // create bomb
            auto bomb = _ecs.spawn_entity();
            _ecs.add_component<Position>(bomb, {positions[i]->x - fmod(positions[i]->x, float(50)), positions[i]->y - fmod(positions[i]->y, float(50))});
            _ecs.add_component<Drawable>(bomb, {LoadTextureFromImage(imageBomb)});
            _ecs.add_component<Animable>(bomb, {0, 0, 50, 50, 50, 50, 0, 0, 3, 1});
            _ecs.add_component<Explodable>(bomb, {GetTime() + 3.0});
            _ecs.add_component<Power>(bomb, {powers[i]->range});
            _ecs.add_component<Scene>(bomb, {1});
            PlaySound(soundPreExplosion);
        }
    }
}

void ProjectManager::render2D()
{

    // Dessiner les entités avec le composant Drawable
    auto &drawables = _ecs.get_components<Drawable>();
    auto &positions = _ecs.get_components<Position>();
    auto &movables = _ecs.get_components<Movable>();
    auto &animables = _ecs.get_components<Animable>();
    // draw map
    for (int i = 0; i < drawables.size(); i++)
    {
        if (drawables[i] && positions[i] && !movables[i])
        {
            (animables[i]) ? DrawTextureRec(drawables[i]->texture, {animables[i]->x, animables[i]->y, animables[i]->width, animables[i]->height}, {positions[i]->x, positions[i]->y}, WHITE)
                           : DrawTexture(drawables[i]->texture, positions[i]->x, positions[i]->y, WHITE);
        }
    }
    for (int i = 0; i < drawables.size(); i++)
    {
        if (drawables[i] && positions[i] && movables[i])
        {
            (animables[i]) ? DrawTextureRec(drawables[i]->texture, {animables[i]->x, animables[i]->y, animables[i]->width, animables[i]->height}, {positions[i]->x, positions[i]->y}, WHITE)
                           : DrawTexture(drawables[i]->texture, positions[i]->x, positions[i]->y, WHITE);
        }
    }
}