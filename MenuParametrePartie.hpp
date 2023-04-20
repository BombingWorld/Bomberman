#include <unistd.h>
#include "raylib.h"
#include <string>

class MenuParametrePartie {
private:
    const int screenWidth;
    const int screenHeight;
public:
    MenuParametrePartie(const int screenWidth, const int screenHeight)
    : screenWidth(screenWidth), screenHeight(screenHeight){} 
    
    bool AfficheParametrePartie(int &nbJoueur, int (&SkinJoueurs)[4], unsigned int &puissanceBombes){
        bool isClosed = true;

        // Charger l'image de fond
        Texture2D backgroundTexture = LoadTexture("../assets/lava.png");


        ////////// Chargement des texture des boutons leurs dimensions //////////
        // Image du Bouton Joueur
        const int hauteurBtnJouer = 50;
        const int largeurBtnJouer = 100;
        Texture2D textureBtnJouer = FabriqueTexture("../assets/wall.png", hauteurBtnJouer, largeurBtnJouer);

        // Image des Boutons Choix du joueur
        const int tailleBtnChoixNbJoueur = 40;
        Texture2D textureBtnChoix_1_Joueur = FabriqueTexture("../assets/play.png", tailleBtnChoixNbJoueur, tailleBtnChoixNbJoueur);
        Texture2D textureBtnChoix_2_Joueur = FabriqueTexture("../assets/wall.png", tailleBtnChoixNbJoueur, tailleBtnChoixNbJoueur);
        Texture2D textureBtnChoix_3_Joueur = FabriqueTexture("../assets/wall.png", tailleBtnChoixNbJoueur, tailleBtnChoixNbJoueur);

        // Image du Bouton Puissance Bombe
        const int tailleBtnChoixPuissanceBombe = 40;
        Texture2D textureBtnPlusPuissanceBombe = FabriqueTexture("../assets/wall.png", tailleBtnChoixPuissanceBombe, tailleBtnChoixPuissanceBombe);
        Texture2D textureBtnMoinsPuissanceBombe = FabriqueTexture("../assets/wall.png", tailleBtnChoixPuissanceBombe, tailleBtnChoixPuissanceBombe);
        
        // Image choix skin
        const int tailleSkinPlayer = 40;
        //Texture2D textureSkinJoueur_1 = FabriqueTexture("../assets/player1.png", tailleSkinPlayer, tailleSkinPlayer);
        Texture2D textureSkinJoueur_1 = FabriqueSkin("../assets/player1.png");


        //////////////// Définir la position des boutons /////////////
        Rectangle btnChoix1Joueur = {70,180,tailleBtnChoixNbJoueur,tailleBtnChoixNbJoueur}; //Paramètre : Position X, Position Y, Epaisseur, Largeur
        Rectangle btnChoix2Joueur = {120,180,tailleBtnChoixNbJoueur,tailleBtnChoixNbJoueur};
        Rectangle btnChoix3Joueur = {170,180,tailleBtnChoixNbJoueur,tailleBtnChoixNbJoueur};
        Rectangle btnJouer = {100, 500, largeurBtnJouer, hauteurBtnJouer};
        Rectangle btnPlusPuissanceBombe = {200,330,tailleBtnChoixPuissanceBombe,tailleBtnChoixPuissanceBombe};
        Rectangle btnMoinsPuissanceBombe = {80,330,tailleBtnChoixPuissanceBombe,tailleBtnChoixPuissanceBombe};


        /////////// Boucle de mise à jour de la fenêtre /////////
        while (!WindowShouldClose())
        {
            // Effacer le fond d'écran et afficher l'image de fond
            ClearBackground(WHITE);
            DrawTexture(backgroundTexture, 0, 0, WHITE);

            // Afficher elements
            DrawText("Nombre de joueur :", 50, 150, 20, WHITE); // Afficher le texte "Nombre de joueur :"
            DrawText("Puissance des bombes :", 50, 300, 20, WHITE);// Afficher le texte "Puissance bombe :"
            DrawTexture(textureBtnChoix_1_Joueur, btnChoix1Joueur.x, btnChoix1Joueur.y, WHITE); // choix nb de joueur
            DrawTexture(textureBtnChoix_2_Joueur, btnChoix2Joueur.x, btnChoix2Joueur.y, WHITE); // choix nb de joueur
            DrawTexture(textureBtnChoix_3_Joueur, btnChoix3Joueur.x, btnChoix3Joueur.y, WHITE); // choix nb de joueur
            DrawTexture(textureBtnJouer, btnJouer.x, btnJouer.y, WHITE); // Bouton jouer
            DrawTexture(textureBtnPlusPuissanceBombe, btnPlusPuissanceBombe.x, btnPlusPuissanceBombe.y, WHITE); // choix + puissance bombe
            DrawText(std::to_string(puissanceBombes).c_str(), 153, 340, 20, WHITE); // val puissance de bombe
            DrawTexture(textureBtnMoinsPuissanceBombe, btnMoinsPuissanceBombe.x, btnMoinsPuissanceBombe.y, WHITE); // choix - puissance bombe
            DrawText("Joueur 1 :", 400, 20, 20, WHITE);// Afficher le texte "Joueur 1"
            DrawTexture(textureSkinJoueur_1, 700, 30, WHITE); // choix - puissance bombe
            DrawText("Déplacement: Z, Q, S, D", 400, 50, 20, WHITE);// Afficher le texte "Joueur 1"
            DrawText("Bombe : E", 400, 80, 20, WHITE);// Afficher le texte "Joueur 1"

            DrawText("Joueur 2 :", 400, 170, 20, WHITE);// Afficher le texte "Joueur 1"
            DrawText("Déplacement: T, F, G, H", 400, 200, 20, WHITE);// Afficher le texte "Joueur 1"
            DrawText("Bombe : Y", 400, 230, 20, WHITE);// Afficher le texte "Joueur 1"

            DrawText("Joueur 3 :", 400, 320, 20, WHITE);// Afficher le texte "Joueur 1"
            DrawText("Déplacement: I, J, K, L", 400, 350, 20, WHITE);// Afficher le texte "Joueur 1"
            DrawText("Bombe : O", 400, 280, 20, WHITE);// Afficher le texte "Joueur 1"

            DrawText("Joueur 4 :", 400, 470, 20, WHITE);// Afficher le texte "Joueur 1"
            DrawText("Déplacement: les flèches", 400, 500, 20, WHITE);// Afficher le texte "Joueur 1"
            DrawText("Bombe : ENTER", 400, 530, 20, WHITE);// Afficher le texte "Joueur 1"


            // Vérifier si le bouton est cliqué
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                float mouseX = GetMouseX();
                float mouseY = GetMouseY();

                if (CheckCollisionPointRec({ mouseX, mouseY }, btnJouer))
                {
                    isClosed = false;
                    break; // Arrêter la boucle si le bouton est cliqué
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnChoix1Joueur))
                {
                    nbJoueur = 2;
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnChoix3Joueur))
                {
                    nbJoueur = 3;
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnChoix3Joueur))
                {
                    nbJoueur = 4;
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnPlusPuissanceBombe))
                {
                    if(puissanceBombes<50)
                        puissanceBombes++;
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnMoinsPuissanceBombe))
                {
                    if(puissanceBombes>1)
                        puissanceBombes--;
                }
            }

            // Mettre à jour la fenêtre
            EndDrawing();
        }

        // Libérer les ressources à la fin
        UnloadTexture(backgroundTexture);
        UnloadTexture(textureBtnJouer);
        UnloadTexture(textureBtnChoix_1_Joueur);
        UnloadTexture(textureBtnChoix_2_Joueur);
        UnloadTexture(textureBtnChoix_3_Joueur);

        return isClosed;
    }

    Texture2D FabriqueTexture(const char* cheminImage, int hauteur, int largeur){
        Image image = LoadImage(cheminImage);
        ImageResize(&image, largeur, hauteur); // Redimensionner l'image
        Texture2D texture = LoadTextureFromImage(image);
        UnloadImage(image); // Libérer l'image redimensionnée
        return texture;
    }

    Texture2D FabriqueSkin(const char* cheminImage){
        Image image = LoadImage(cheminImage);
        ImageResize(&image, 240, 160); // Redimensionner l'image
        ImageCrop(&image, {200, 120, 240, 160});
        Texture2D texture = LoadTextureFromImage(image);
        UnloadImage(image);
        return texture;
    }
};


//Reste a gerer
//- nombre de joueur : choix entre 4 boutons
//- puissance : un bouton +, un bouton - et le nombre qui s'affiche entre 0 et 50