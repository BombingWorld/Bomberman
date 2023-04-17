#ifndef DATA_HPP_
    #define DATA_HPP_

#include "raylib.h"

enum KEY {
    A = KEY_Q, Z = KEY_W, E = KEY_E, R = KEY_R,T = KEY_T, Y = KEY_Y, 
    U = KEY_U, I = KEY_I, O = KEY_O,P = KEY_P, Q = KEY_A, S = KEY_S, 
    D = KEY_D, F = KEY_F,G = KEY_G, H = KEY_H, J = KEY_J, K = KEY_K, 
    L = KEY_L, M = KEY_SEMICOLON, W = KEY_Z, X = KEY_X,  C = KEY_C,  
    V = KEY_V, B = KEY_B, N = KEY_N, SPACE = KEY_SPACE, ENTER = KEY_ENTER, 
    ESCAPE = KEY_ESCAPE, UP = KEY_UP, DOWN = KEY_DOWN, LEFT = KEY_LEFT, 
    RIGHT = KEY_RIGHT, SHIFT = KEY_LEFT_SHIFT, CTRL = KEY_LEFT_CONTROL,
};

const int TAILLE_MUR = 50;
const int TAILLE_PLAYER = 40;

const std::vector<std::string> map = {
    "xxxxxxxxxxxxxxxx",
    "x              x",
    "x   bbbbbxx xx x",
    "xbbbbbbbbbb bbbx",
    "x   bbbbb      x",          
    "x    p         x",
    "x    x         x",
    "xxxxxxxxxxbbbbxx",
    "x            b x",
    "x            b x",
    "xp     p      px",
    "xxxxxxxxxxxxxxxx",
};

const int bombVar[] = {-10, -1, 1, 10};

#endif /* !DATA_HPP_ */
