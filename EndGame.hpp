#include <unistd.h>
#include "raylib.h"

class EndGame {
private:
    const int screenWidth;
    const int screenHeight;
public:
    EndGame(const int screenWidth, const int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight){} 
    
    bool AfficheEndGame(){

        const char* buttonImagePath = "../assets/wall.png";
        const int buttonWidth = 100;
        const int buttonHeight = 50;
        bool isClosed = true;

        // Charger l'image du bouton en utilisant les dimensions du bouton
        Image buttonImage = LoadImage(buttonImagePath);
        ImageResize(&buttonImage, buttonWidth, buttonHeight); // Redimensionner l'image
        Texture2D buttonTexture = LoadTextureFromImage(buttonImage);
        UnloadImage(buttonImage); // Libérer l'image redimensionnée

        // Définir la position du bouton au centre de la fenêtre
        Rectangle buttonRect = {
            350.0,
            275.0,
            buttonWidth,
            buttonHeight
        };

        // Boucler la mise à jour de la fenêtre
        while (!WindowShouldClose())
        {
          
          
            // Afficher le bouton centré sur la fenêtre
            DrawText("PARTIE FINIE MOTHER FUCK", 50, 150, 50, WHITE); // Afficher le texte "Nombre de joueur :"
            DrawTexture(buttonTexture, buttonRect.x, buttonRect.y, WHITE);

            // Vérifier si le bouton est cliqué
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                float mouseX = GetMouseX();
                float mouseY = GetMouseY();

                if (CheckCollisionPointRec({ mouseX, mouseY }, buttonRect))
                {
                    isClosed = false;
                    break; // Arrêter la boucle si le bouton est cliqué
                }
            }

            // Mettre à jour la fenêtre
            EndDrawing();
        }

        // Libérer les ressources à la fin
        UnloadTexture(buttonTexture);

        return isClosed;
    }
};
