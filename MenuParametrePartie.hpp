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
        Texture2D textureBtnJouer = FabriqueTexture("../assets/btnJouer.png", hauteurBtnJouer, largeurBtnJouer);

        // Image des Boutons Choix du joueur
        const int tailleBtnChoixNbJoueur = 40;
        Texture2D textureBtnChoix_2_Joueur = FabriqueTexture("../assets/two.png", tailleBtnChoixNbJoueur, tailleBtnChoixNbJoueur);
        Texture2D textureBtnChoix_3_Joueur = FabriqueTexture("../assets/three.png", tailleBtnChoixNbJoueur, tailleBtnChoixNbJoueur);
        Texture2D textureBtnChoix_4_Joueur = FabriqueTexture("../assets/four.png", tailleBtnChoixNbJoueur, tailleBtnChoixNbJoueur);

        Texture2D textureBtnChoix_2_JoueurSelection = FabriqueTexture("../assets/twoSelected.png", tailleBtnChoixNbJoueur, tailleBtnChoixNbJoueur);
        Texture2D textureBtnChoix_3_JoueurSelection = FabriqueTexture("../assets/threeSelected.png", tailleBtnChoixNbJoueur, tailleBtnChoixNbJoueur);
        Texture2D textureBtnChoix_4_JoueurSelection = FabriqueTexture("../assets/fourSelected.png", tailleBtnChoixNbJoueur, tailleBtnChoixNbJoueur);

        // Image du Bouton Puissance Bombe
        const int tailleBtnChoixPuissanceBombe = 40;
        Texture2D textureBtnPlusPuissanceBombe = FabriqueTexture("../assets/plus.png", tailleBtnChoixPuissanceBombe, tailleBtnChoixPuissanceBombe);
        Texture2D textureBtnMoinsPuissanceBombe = FabriqueTexture("../assets/minus.png", tailleBtnChoixPuissanceBombe, tailleBtnChoixPuissanceBombe);
        
        // Image choix skin
        const int tailleSkinPlayer = 40;
        Texture2D textureSkinJoueur_1 = FabriqueSkin("../assets/player1.png");
        Texture2D textureSkinJoueur_2 = FabriqueSkin("../assets/player2.png");
        Texture2D textureSkinJoueur_3 = FabriqueSkin("../assets/player3.png");
        Texture2D textureSkinJoueur_4 = FabriqueSkin("../assets/player4.png");
        Texture2D textureSkinJoueur_5 = FabriqueSkin("../assets/player5.png");
        Texture2D textureSkinJoueur_6 = FabriqueSkin("../assets/player6.png");

        std::vector<std::reference_wrapper<Texture2D>> tabTextureSkinJoueur {
            textureSkinJoueur_1,
            textureSkinJoueur_2,
            textureSkinJoueur_3,
            textureSkinJoueur_4,
            textureSkinJoueur_5,
            textureSkinJoueur_6
        };

        

        // Image felche choix skin
        const int tailleFecheSkin = 40;
        Texture2D textureSkinPrecedent = FabriqueTexture("../assets/minus.png", tailleFecheSkin, tailleFecheSkin);
        Texture2D textureSkinSuivant = FabriqueTexture("../assets/plus.png", tailleFecheSkin, tailleFecheSkin);

        //////////////// Définir la position des boutons /////////////
        Rectangle btnChoix2Joueur = {70,180,tailleBtnChoixNbJoueur,tailleBtnChoixNbJoueur}; //Paramètre : Position X, Position Y, Epaisseur, Largeur
        Rectangle btnChoix3Joueur = {120,180,tailleBtnChoixNbJoueur,tailleBtnChoixNbJoueur};
        Rectangle btnChoix4Joueur = {170,180,tailleBtnChoixNbJoueur,tailleBtnChoixNbJoueur};
        Rectangle btnJouer = {100, 500, largeurBtnJouer, hauteurBtnJouer};
        Rectangle btnPlusPuissanceBombe = {200,330,tailleBtnChoixPuissanceBombe,tailleBtnChoixPuissanceBombe};
        Rectangle btnMoinsPuissanceBombe = {80,330,tailleBtnChoixPuissanceBombe,tailleBtnChoixPuissanceBombe};
        Rectangle btnSkinPrecedent_Joueur1 = {590,20,tailleFecheSkin,tailleFecheSkin};
        Rectangle btnSkinSuivant_Joueur1 = {710,20,tailleFecheSkin,tailleFecheSkin};
        Rectangle btnSkinPrecedent_Joueur2 = {590,170,tailleFecheSkin,tailleFecheSkin};
        Rectangle btnSkinSuivant_Joueur2 = {710,170,tailleFecheSkin,tailleFecheSkin};
        Rectangle btnSkinPrecedent_Joueur3 = {590,330,tailleFecheSkin,tailleFecheSkin};
        Rectangle btnSkinSuivant_Joueur3 = {710,330,tailleFecheSkin,tailleFecheSkin};
        Rectangle btnSkinPrecedent_Joueur4 = {590,480,tailleFecheSkin,tailleFecheSkin};
        Rectangle btnSkinSuivant_Joueur4 = {710,480,tailleFecheSkin,tailleFecheSkin};


        /////////// Boucle de mise à jour de la fenêtre /////////
        while (!WindowShouldClose())
        {
            // Effacer le fond d'écran et afficher l'image de fond
            ClearBackground(WHITE);
            DrawTexture(backgroundTexture, 0, 0, WHITE);

            // Afficher elements de gauche
            DrawText("Nombre de joueur :", 50, 150, 20, WHITE); // Afficher le texte "Nombre de joueur :"
            DrawText("Puissance des bombes :", 50, 300, 20, WHITE);// Afficher le texte "Puissance bombe :"
            if(nbJoueur==2){
                DrawTexture(textureBtnChoix_2_JoueurSelection, btnChoix2Joueur.x, btnChoix2Joueur.y, WHITE); // choix nb de joueur
            }else{
                DrawTexture(textureBtnChoix_2_Joueur, btnChoix2Joueur.x, btnChoix2Joueur.y, WHITE); // choix nb de joueur
            }
            if(nbJoueur==3){
                DrawTexture(textureBtnChoix_3_JoueurSelection, btnChoix3Joueur.x, btnChoix3Joueur.y, WHITE); // choix nb de joueur
            }else{
                DrawTexture(textureBtnChoix_3_Joueur, btnChoix3Joueur.x, btnChoix3Joueur.y, WHITE); // choix nb de joueur
            }
            if(nbJoueur==4){
                DrawTexture(textureBtnChoix_4_JoueurSelection, btnChoix4Joueur.x, btnChoix4Joueur.y, WHITE); // choix nb de joueur
            }else{
                DrawTexture(textureBtnChoix_4_Joueur, btnChoix4Joueur.x, btnChoix4Joueur.y, WHITE); // choix nb de joueur
            }
            DrawTexture(textureBtnJouer, btnJouer.x, btnJouer.y, WHITE); // Bouton jouer
            DrawTexture(textureBtnPlusPuissanceBombe, btnPlusPuissanceBombe.x, btnPlusPuissanceBombe.y, WHITE); // choix + puissance bombe
            DrawText(std::to_string(puissanceBombes).c_str(), 153, 340, 20, WHITE); // val puissance de bombe
            DrawTexture(textureBtnMoinsPuissanceBombe, btnMoinsPuissanceBombe.x, btnMoinsPuissanceBombe.y, WHITE); // choix - puissance bombe

            //Affichage deplacement joueur et changement de skin
            DrawText("Joueur 1 :", 450, 20, 20, WHITE);
            DrawTexture(tabTextureSkinJoueur[SkinJoueurs[0]-1], 650, 20, WHITE); 
            DrawTexture(textureSkinPrecedent, btnSkinPrecedent_Joueur1.x, btnSkinPrecedent_Joueur1.y, WHITE);
            DrawTexture(textureSkinSuivant, btnSkinSuivant_Joueur1.x, btnSkinSuivant_Joueur1.y, WHITE);
            DrawText("Déplacement: Z, Q, S, D", 450, 70, 20, WHITE);
            DrawText("Bombe : E", 450, 100, 20, WHITE);

            DrawText("Joueur 2 :", 450, 170, 20, WHITE);
            DrawTexture(tabTextureSkinJoueur[SkinJoueurs[1]-1], 650, 170, WHITE); 
            DrawTexture(textureSkinPrecedent, btnSkinPrecedent_Joueur2.x, btnSkinPrecedent_Joueur2.y, WHITE);
            DrawTexture(textureSkinSuivant, btnSkinSuivant_Joueur2.x, btnSkinSuivant_Joueur2.y, WHITE);
            DrawText("Déplacement: les flèches", 450, 230, 20, WHITE);
            DrawText("Bombe : ENTER", 450, 260, 20, WHITE);

            DrawText("Joueur 3 :", 450, 330, 20, WHITE);
            DrawTexture(tabTextureSkinJoueur[SkinJoueurs[2]-1], 650, 330, WHITE); 
            DrawTexture(textureSkinPrecedent, btnSkinPrecedent_Joueur3.x, btnSkinPrecedent_Joueur3.y, WHITE);
            DrawTexture(textureSkinSuivant, btnSkinSuivant_Joueur3.x, btnSkinSuivant_Joueur3.y, WHITE);
            DrawText("Déplacement: I, J, K, L", 450, 380, 20, WHITE);
            DrawText("Bombe : O", 450, 410, 20, WHITE);

            DrawText("Joueur 4 :", 450, 480, 20, WHITE);
            DrawTexture(tabTextureSkinJoueur[SkinJoueurs[3]-1], 650, 480, WHITE); 
            DrawTexture(textureSkinPrecedent, btnSkinPrecedent_Joueur4.x, btnSkinPrecedent_Joueur4.y, WHITE);
            DrawTexture(textureSkinSuivant, btnSkinSuivant_Joueur4.x, btnSkinSuivant_Joueur4.y, WHITE);
            DrawText("Déplacement: T, F, G, H", 450, 530, 20, WHITE);
            DrawText("Bombe : Y", 450, 560, 20, WHITE);

            // Vérifier si le bouton est cliqué
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                float mouseX = GetMouseX();
                float mouseY = GetMouseY();

                if (CheckCollisionPointRec({ mouseX, mouseY }, btnJouer)) // Jouer
                {
                    isClosed = false;
                    break; // Arrêter la boucle si le bouton est cliqué
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnChoix2Joueur)) // Nb joueur
                {
                    nbJoueur = 2;
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnChoix3Joueur))
                {
                    nbJoueur = 3;
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnChoix4Joueur))
                {
                    nbJoueur = 4;
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnPlusPuissanceBombe)) // Puissance bombe
                {
                    if(puissanceBombes<50)
                        puissanceBombes++;
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnMoinsPuissanceBombe))
                {
                    if(puissanceBombes>1)
                        puissanceBombes--;
                }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnSkinPrecedent_Joueur1)){ // Choix Skin{
                    if(SkinJoueurs[0]>1){SkinJoueurs[0]--;} }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnSkinSuivant_Joueur1)){ 
                    if(SkinJoueurs[0]<6){SkinJoueurs[0]++;} }
                    
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnSkinPrecedent_Joueur2)){
                    if(SkinJoueurs[1]>1){SkinJoueurs[1]--;} }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnSkinSuivant_Joueur2)){ 
                    if(SkinJoueurs[1]<6){SkinJoueurs[1]++;} } 

                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnSkinPrecedent_Joueur3)){
                    if(SkinJoueurs[2]>1){SkinJoueurs[2]--;} }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnSkinSuivant_Joueur3)){ 
                    if(SkinJoueurs[2]<6){SkinJoueurs[2]++;} }
                         
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnSkinPrecedent_Joueur4)){
                    if(SkinJoueurs[3]>1){SkinJoueurs[3]--;} }
                else if (CheckCollisionPointRec({ mouseX, mouseY }, btnSkinSuivant_Joueur4)){ 
                    if(SkinJoueurs[3]<6){SkinJoueurs[3]++;} }
                
                
            }

            // Mettre à jour la fenêtre
            EndDrawing();
        }

        // Libérer les ressources à la fin
        UnloadTexture(backgroundTexture);
        UnloadTexture(textureBtnJouer);
        UnloadTexture(textureBtnChoix_2_Joueur);
        UnloadTexture(textureBtnChoix_3_Joueur);
        UnloadTexture(textureBtnChoix_4_Joueur);

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