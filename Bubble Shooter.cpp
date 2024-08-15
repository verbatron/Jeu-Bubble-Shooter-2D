																		// *** Bubble Shooter *** //
																		//   C++ Natif (OPENGL)   //
																		//      Fin Juin 2024	  //
																		////////////////////////////



#include <Windows.h>													// Pour Masquer la Fenêtre Console //
#include <iostream>
#include <string>														// Pour Affichage des Textes //
#include <cstdbool>														// Pour Booléens //
#include <ctime>														// Pour Fonction rand() //
#include <fstream>														// Inclusion Pour les Fichiers externes //
#include <cmath>
#include <playsoundapi.h>												// Pour Jouer les Sons avec Fonction PlaySound() //
#include <cstdio>														// Bib. Standard E/S C //
#include <cstdlib>														// Idem //


#include "Cercles.h"													// Inclusion Fichier 'Cercles.h' //
#include "GL/glut.h"													// Inclusion Bib. GLUT (OPENGL) //



using namespace std;													// Inclusion Espace de Noms Standard //


GLboolean ValidFin = false;												// Variable Booléenne Validation Fin Jeu //
GLboolean ValidTir = false;												// Variable Booléenne Validation Tir Cercle Joueur //
GLboolean ValidPositionInit = true;										// Variable Booléenne Validation Position Initiale Cercles Joueur //
GLuint CerclesRestant = 52;												// Variable Valeur Nombre Cercles Restant à Détruire //
GLint AngleRotation = 0;												// Variable Valeur Angle de Rotation Ligne de Tir  //
GLint AngleDeplac = 0;													// Variable Valeur Angle de Déplacement Joueur  //
GLuint ChoixCouleurJoueur = 1;											// Variable Valeur Aléatoire Choix Couleur Cercle Joueur en Cours //
GLint NbColonnes = 15;													// Variable Nombre de Colonnes Tableau //
GLint NbLignes = 11;													// Variable Nombre de Lignes Tableau //
const int TimerMillis = 60;												// Variable Valeur Temps entre 2 Evenements Timer //



int PosXRougeTableau, PosYRougeTableau;
GLdouble PosXRougeJoueur, PosYRougeJoueur;
int PosXVertTableau, PosYVertTableau;
GLdouble PosXVertJoueur, PosYVertJoueur;
int PosXBleuTableau, PosYBleuTableau;									// Variables Coordonnées Elements de la Scène (Cercles Tableau et Joueur) //
GLdouble PosXBleuJoueur, PosYBleuJoueur;
int PosXGrisTableau, PosYGrisTableau;
GLdouble PosXGrisJoueur, PosYGrisJoueur;
int PosXNoirTableau, PosYNoirTableau;
GLdouble PosXNoirJoueur, PosYNoirJoueur;


Cercles MonJoueur;
Cercles LeCercleRouge;
Cercles LeCercleVert;
Cercles LeCercleBleu;													// Objets Globaux de la Classe Cercles //
Cercles LeCercleGris;
Cercles LeCercleNoir;


GLint Tableau[11][15] = {{0,1,1,3,3,4,4,1,1,2,2,5,5,3,3},
						 {0,2,2,4,4,1,1,2,2,3,3,1,1,0,0},
						 {0,5,5,3,3,5,5,1,1,3,3,2,2,3,3},
						 {0,3,3,4,4,1,1,2,2,5,5,4,4,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},				// Tableau Initial du Jeu //
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
						 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};



void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);									// On Efface Ecran avec Couleur Blanche //
	glShadeModel(GL_FLAT);												// Colorisation Unie (Modèle de Dégradé) //
}



double EnRadians(GLint AngleRotation)
{
	return (GLdouble)((AngleRotation * 3.1415) / 180);					// On Retourne la Valeur en Radians de L'angle de Rotation //
}



void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);							// Transformation de Cadrage //
	glMatrixMode(GL_PROJECTION);										// Matrice Active -> Projection //
	glLoadIdentity();													// On Vide la Matrice //
	gluOrtho2D(0.0,(double)NbColonnes,(double)NbLignes,0.0);			// Perspective Cavalière //
}



void GestionAngle(void)
{
	if (AngleRotation < -80.0)											// Si Angle < -80° //
	{
		AngleRotation = -80.0;											// Angle = -80° //
	}

	if (AngleRotation > 80.0)											// Si Angle > 80° //
	{
		AngleRotation = 80.0;											// Angle = +80° //
	}
}



void DessinerTableau(void)
{
	for(int i = 0; i < NbLignes; i++)									// On Parcoure le Tableau avec des Boucles Itératives //
		for (int j = 0; j < NbColonnes; j++)
		{
			if (Tableau[i][j] == 1)										// Cas Cercle Tableau Rouge //
			{
				PosXRougeTableau = j;
				PosYRougeTableau = i;
				LeCercleRouge.DessinerRougeTableau();					// On Affiche un Cercle de cette Couleur a cet Endroit là //
			}

			if (Tableau[i][j] == 2)										// Cas Cercle Tableau Vert //
			{
				PosXVertTableau = j;
				PosYVertTableau = i;
				LeCercleVert.DessinerVertTableau();						// On Affiche un Cercle de cette Couleur a cet Endroit là //
			}

			if (Tableau[i][j] == 3)										// Cas Cercle Tableau Bleu //
			{
				PosXBleuTableau = j;
				PosYBleuTableau = i;
				LeCercleBleu.DessinerBleuTableau();						// On Affiche un Cercle de cette Couleur a cet Endroit là //
			}

			if (Tableau[i][j] == 4)										// Cas Cercle Tableau Gris //
			{
				PosXGrisTableau = j;
				PosYGrisTableau = i;
				LeCercleGris.DessinerGrisTableau();						// On Affiche un Cercle de cette Couleur a cet Endroit là //
			}

			if (Tableau[i][j] == 5)										// Cas Cercle Tableau Noir //
			{
				PosXNoirTableau = j;
				PosYNoirTableau = i;
				LeCercleNoir.DessinerNoirTableau();						// On Affiche un Cercle de cette Couleur a cet Endroit là //
			}

		}

}



void keyboard(int key, int x, int y)
{
	switch (key)														// Commutation Touche Appuyée //
	{
	case GLUT_KEY_F1:													// Appui sur 'F1' //
	{
		AngleDeplac = AngleRotation;
		ValidTir = true;												// On Valide le Tir Cercle Joueur en Cours //
		break;
	}

	case GLUT_KEY_F10:													// Appui sur 'F10' //
	{
		exit(0);														// On Quitte le Logiciel //
		break;
	}

	case GLUT_KEY_LEFT:													// Appui sur 'GAUCHE' //
	{
		if (!ValidTir && !ValidFin)										// Si on n'est pas en Cours de Tir //
		{
			AngleRotation--;											// On Diminue de 1 Unité l'angle de Rotation Ligne de Tir //
			GestionAngle();												// On Execute la Fonction Gestion de l'angle //
			glutPostRedisplay();										// On Raffraichit l'affichage //
		}
		break;
	}

	case GLUT_KEY_RIGHT:												// Appui sur 'DROITE' //
	{
		if (!ValidTir && !ValidFin)										// Si on n'est pas en Cours de Tir //
		{
			AngleRotation++;											// On Augmente de 1 Unité l'angle de Rotation Ligne de Tir //
			GestionAngle();												// On Execute la Fonction Gestion de l'angle //
			glutPostRedisplay();										// On Raffraichit l'affichage //
		}
		break;
	}

	}

}


void PositionInit(void)
{
	if (ValidPositionInit)												// Si on a Validé la Position Initiale des Cercles Joueur //
	{
		PosXRougeJoueur = 7;
		PosYRougeJoueur = 9;

		PosXVertJoueur = 7;
		PosYVertJoueur = 9;

		PosXBleuJoueur = 7;												// On Définit la Position Initiale des Cercles Joueur //
		PosYBleuJoueur = 9;

		PosXGrisJoueur = 7;
		PosYGrisJoueur = 9;

		PosXNoirJoueur = 7;
		PosYNoirJoueur = 9;

	}

	ValidPositionInit = false;											// Pour Pouvoir par la Suite Déplacer les Cercles Joueur //
}



void DessinerJoueur(void)
{
	switch (ChoixCouleurJoueur)											// Commutation Choix Couleur Joueur en Cours //
	{

	case 1:																// Cas Cercle Joueur Rouge //
	{
		MonJoueur.DessinerRougeJoueur();								// On l'affiche //
		glutPostRedisplay();
		break;
	}

	case 2:																// Cas Cercle Joueur Vert //
	{
		MonJoueur.DessinerVertJoueur();									// On l'affiche //
		glutPostRedisplay();
		break;
	}

	case 3:																// Cas Cercle Joueur Bleu //
	{
		MonJoueur.DessinerBleuJoueur();									// On l'affiche //
		glutPostRedisplay();
		break;
	}

	case 4:																// Cas Cercle Joueur Gris //
	{
		MonJoueur.DessinerGrisJoueur();									// On l'affiche //
		glutPostRedisplay();
		break;
	}

	case 5:																// Cas Cercle Joueur Noir //
	{
		MonJoueur.DessinerNoirJoueur();									// On l'affiche //
		glutPostRedisplay();
		break;
	}


	}

}


void GestionBords(void)
{
	switch (ChoixCouleurJoueur)											// Commutation Choix Couleur Joueur en Cours //
	{
	case 1:																// Cas Cercle Joueur Rouge //
	{
		if (PosXRougeJoueur < 0)										// Si le Cercle a Atteint la Limite Gauche //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}

		if (PosXRougeJoueur > 14)										// Si le Cercle a Atteint la Limite Droite //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}
	break;
	}

	case 2:																// Cas Cercle Joueur Vert //
	{
		if (PosXVertJoueur < 0)											// Si le Cercle a Atteint la Limite Gauche //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}

		if (PosXVertJoueur > 14)										// Si le Cercle a Atteint la Limite Droite //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}
		break;
	}

	case 3:																// Cas Cercle Joueur Bleu //
	{
		if (PosXBleuJoueur < 0)											// Si le Cercle a Atteint la Limite Gauche //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}

		if (PosXBleuJoueur > 14)										// Si le Cercle a Atteint la Limite Droite //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}
		break;
	}

	case 4:																// Cas Cercle Joueur Gris //
	{
		if (PosXGrisJoueur < 0)											// Si le Cercle a Atteint la Limite Gauche //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}

		if (PosXGrisJoueur > 14)										// Si le Cercle a Atteint la Limite Droite //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}
		break;
	}

	case 5:																// Cas Cercle Joueur Noir //
	{
		if (PosXNoirJoueur < 0)											// Si le Cercle a Atteint la Limite Gauche //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}

		if (PosXNoirJoueur > 14)										// Si le Cercle a Atteint la Limite Droite //
		{
			AngleDeplac = -AngleDeplac;									// On Inverse l'angle //
			PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
		}
		break;
	}

	}
}


void GestionTir(int value)
{
	if (ValidTir && !ValidFin)											// Si on est en Cours de Tir //
	{
		switch (ChoixCouleurJoueur)										// Commutation Choix Couleur Joueur en Cours //
		{
		case 1:															// Cas Cercle Joueur Rouge //
		{
			PosXRougeJoueur += 0.1*sin(EnRadians(AngleDeplac));			// On Déplace le Cercle en fonction de l'angle de la Ligne de Tir //
			PosYRougeJoueur -= 0.1*cos(EnRadians(AngleDeplac));
			GestionBords();
			break;
		}

		case 2:															// Cas Cercle Joueur Vert //
		{
			PosXVertJoueur += 0.1 * sin(EnRadians(AngleDeplac));		// On Déplace le Cercle en fonction de l'angle de la Ligne de Tir //
			PosYVertJoueur -= 0.1 * cos(EnRadians(AngleDeplac));
			GestionBords();
			break;
		}

		case 3:															// Cas Cercle Joueur Bleu //
		{
			PosXBleuJoueur += 0.1 * sin(EnRadians(AngleDeplac));		// On Déplace le Cercle en fonction de l'angle de la Ligne de Tir //
			PosYBleuJoueur -= 0.1 * cos(EnRadians(AngleDeplac));
			GestionBords();
			break;
		}

		case 4:															// Cas Cercle Joueur Gris //
		{
			PosXGrisJoueur += 0.1 * sin(EnRadians(AngleDeplac));		// On Déplace le Cercle en fonction de l'angle de la Ligne de Tir //
			PosYGrisJoueur -= 0.1 * cos(EnRadians(AngleDeplac));
			GestionBords();
			break;
		}

		case 5:															// Cas Cercle Joueur Rouge //
		{
			PosXNoirJoueur += 0.1 * sin(EnRadians(AngleDeplac));		// On Déplace le Cercle en fonction de l'angle de la Ligne de Tir //
			PosYNoirJoueur -= 0.1 * cos(EnRadians(AngleDeplac));
			GestionBords();
			break;
		}

		}

	}

	glutTimerFunc(TimerMillis, GestionTir, 0);							// On Réarme ce Timer //
}



void GestionCollision(void)
{
	if (!ValidFin)														// Si on est en Cours de Jeu //
	{
		switch (ChoixCouleurJoueur)										// Commutation Choix Couleur Joueur //
		{
		case 1:															// Cas Cercle Joueur Rouge //
		{
			if (Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur] == 1 && Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur - 1] == 1)
			{	// Si les Cercles Tableau du Dessus et Dessus a Gauche sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur - 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant -2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur] == 1 && Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur + 1] == 1)
			{	// Si les Cercles Tableau du Dessus et Dessus a Droite sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur + 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant - 2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur] == 1)
			{	// Si le Cercle d'en Dessus est de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur] = 0;			// On Supprime le Cercle Tableau //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant--;										// On a Supprimé un Cercle Tableau //
				glutPostRedisplay();
			}

			if ((Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur] != 1) && (Tableau[(GLint)PosYRougeJoueur][(GLint)PosXRougeJoueur] != 0))
			{	// Si le Cercle d'en Dessus n'est pas de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYRougeJoueur + 1][(GLint)PosXRougeJoueur] = 1;	// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			if (PosYRougeJoueur < 0)
			{	// Si le Joueur est sur une Case / 1ère Ligne //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[0][(GLint)PosXRougeJoueur] = 1;					// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			break;
		}


		case 2:															// Cas Cercle Joueur Vert //
		{
			if (Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur] == 2 && Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur - 1] == 2)
			{	// Si les Cercles Tableau du Dessus et Dessus a Gauche sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur - 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant - 2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur] == 2 && Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur + 1] == 2)
			{	// Si les Cercles Tableau du Dessus et Dessus a Droite sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur + 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant - 2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur] == 2)
			{	// Si le Cercle d'en Dessus est de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur] = 0;			// On Supprime le Cercle Tableau //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant--;										// On a Supprimé un Cercle Tableau //
				glutPostRedisplay();
			}

			if ((Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur] != 2) && (Tableau[(GLint)PosYVertJoueur][(GLint)PosXVertJoueur] != 0))
			{	// Si le Cercle d'en Dessus n'est pas de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYVertJoueur + 1][(GLint)PosXVertJoueur] = 2;	// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			if (PosYVertJoueur < 0)
			{	// Si le Joueur est sur une Case / 1ère Ligne //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[0][(GLint)PosXVertJoueur] = 2;					// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			break;
		}


		case 3:															// Cas Cercle Joueur Bleu //
		{
			if (Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur] == 3 && Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur - 1] == 3)
			{	// Si les Cercles Tableau du Dessus et Dessus a Gauche sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur - 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant - 2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur] == 3 && Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur + 1] == 3)
			{	// Si les Cercles Tableau du Dessus et Dessus a Droite sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur + 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant - 2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur] == 3)
			{	// Si le Cercle d'en Dessus est de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur] = 0;			// On Supprime le Cercle Tableau //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant--;										// On a Supprimé un Cercle Tableau //
				glutPostRedisplay();
			}

			if ((Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur] != 3) && (Tableau[(GLint)PosYBleuJoueur][(GLint)PosXBleuJoueur] != 0))
			{	// Si le Cercle d'en Dessus n'est pas de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYBleuJoueur + 1][(GLint)PosXBleuJoueur] = 3;	// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			if (PosYBleuJoueur < 0)
			{	// Si le Joueur est sur une Case / 1ère Ligne //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[0][(GLint)PosXBleuJoueur] = 3;					// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			break;
		}


		case 4:															// Cas Cercle Joueur Gris //
		{
			if (Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur] == 4 && Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur - 1] == 4)
			{	// Si les Cercles Tableau du Dessus et Dessus a Gauche sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur - 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant - 2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur] == 4 && Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur + 1] == 4)
			{	// Si les Cercles Tableau du Dessus et Dessus a Droite sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur + 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant - 2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur] == 4)
			{	// Si le Cercle d'en Dessus est de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur] = 0;			// On Supprime le Cercle Tableau //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant--;										// On a Supprimé un Cercle Tableau //
				glutPostRedisplay();
			}

			if ((Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur] != 4) && (Tableau[(GLint)PosYGrisJoueur][(GLint)PosXGrisJoueur] != 0))
			{	// Si le Cercle d'en Dessus n'est pas de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYGrisJoueur + 1][(GLint)PosXGrisJoueur] = 4;	// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			if (PosYGrisJoueur < 0)
			{	// Si le Joueur est sur une Case / 1ère Ligne //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[0][(GLint)PosXGrisJoueur] = 4;					// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			break;
		}


		case 5:															// Cas Cercle Joueur Noir //
		{
			if (Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur] == 5 && Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur - 1] == 5)
			{	// Si les Cercles Tableau du Dessus et Dessus a Gauche sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur - 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant - 2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur] == 5 && Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur + 1] == 5)
			{	// Si les Cercles Tableau du Dessus et Dessus a Droite sont de même Couleur que le Joueur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur] = 0;			// On Supprime les Cercles Tableau //
				Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur + 1] = 0;
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant = CerclesRestant - 2;						// On a Supprimé 2 Cercles Tableau //										
				glutPostRedisplay();
			}

			if (Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur] == 5)
			{	// Si le Cercle d'en Dessus est de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur] = 0;			// On Supprime le Cercle Tableau //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant--;										// On a Supprimé un Cercle Tableau //
				glutPostRedisplay();
			}

			if ((Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur] != 5) && (Tableau[(GLint)PosYNoirJoueur][(GLint)PosXNoirJoueur] != 0))
			{	// Si le Cercle d'en Dessus n'est pas de la Même Couleur //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[(GLint)PosYNoirJoueur + 1][(GLint)PosXNoirJoueur] = 5;	// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			if (PosYNoirJoueur < 0)
			{	// Si le Joueur est sur une Case / 1ère Ligne //
				ValidTir = false;										// On Annule le Déplacement Joueur //
				Tableau[0][(GLint)PosXNoirJoueur] = 5;					// On Ajoute un Cercle de même Couleur que le Joueur a son Emplacement //
				PlaySound(TEXT("Datas\\SonBulle.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'Bulle' //
				ValidPositionInit = true;									// On Redéfinit les Positions Initiales //
				ChoixCouleurJoueur = (rand() % 5) + 1;					// On va Afficher un Nouveau Cercle Joueur //
				CerclesRestant++;										// On a Ajouté 1 Cercle Tableau //										
				glutPostRedisplay();

			}

			break;
		}

		}

	}

}


void TestDefaite(void)
{
	if (Tableau[8][0] != 0 || Tableau[8][1] != 0 || Tableau[8][2] != 0 || Tableau[8][3] != 0 || Tableau[8][4] != 0 ||
		Tableau[8][5] != 0 || Tableau[8][6] != 0 || Tableau[8][7] != 0 || Tableau[8][8] != 0 || Tableau[8][9] != 0 ||
		Tableau[8][10] != 0 || Tableau[8][11] != 0 || Tableau[8][12] != 0 || Tableau[8][13] != 0 || Tableau[8][14] != 0)
	{	// Si pour la 8ème Ligne et n'importe quelle Colonne il y a au moins un Cercle Tableau  -> DEFAITE //

		ValidTir = false;												// On Annule le Déplacement Joueur //
		ChoixCouleurJoueur = 0;											// Pour Aucun Affichage Joueur //
		PlaySound(TEXT("Datas\\GameOver.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'DEFAITE' //

		glMatrixMode(GL_PROJECTION);									// Matrice Active -> Projection //
		glPushMatrix();													// On Copie la Matrice Active en Haut de la Pile //													
		glLoadIdentity();												// On Vide la Matrice //
		gluOrtho2D(0.0, 420.0, 330.0, 0.0);								// Transformation de Projection (Perspective Cavalière 2D) //

		glMatrixMode(GL_MODELVIEW);										// Matrice Active -> Modélisation-Visualisation //			
		glPushMatrix();													// On Copie la Matrice Active en Haut de la Pile //
		glLoadIdentity();												// On Vide la Matrice //

		glColor3d(0.0, 0.0, 0.0);										// Texte en Noir //

		glRasterPos2i(155, 160);											// Position du Texte //


		string s = "DEFAITE";											// Texte à afficher //

		void* font = GLUT_BITMAP_TIMES_ROMAN_24;						// On définit le Type de Police et sa Taille //

		for (string::iterator i = s.begin(); i != s.end(); ++i)
		{
			char c = *i;												// Fonction GLUT affichage Texte //
			glutBitmapCharacter(font, c);
		}

		glMatrixMode(GL_MODELVIEW);										// Matrice Active -> Modélisation-Visualisation //	
		glPopMatrix();													// On Retire la Matrice du Haut de la Pile //													 

		glMatrixMode(GL_PROJECTION);									// Matrice Active -> Projection //
		glPopMatrix();													// On Retire la Matrice du Haut de la Pile //

		ValidFin = true;												// On Valide la Fin du Jeu (
	}
}


void TestVictoire(void)
{
	if (Tableau[0][0] == 0 && Tableau[0][1] == 0 && Tableau[0][2] == 0	&& Tableau[0][3] == 0 && Tableau[0][4] == 0 && Tableau[0][5] == 0 && Tableau[0][6] == 0 &&
		Tableau[0][7] == 0 && Tableau[0][8] == 0 && Tableau[0][9] == 0 && Tableau[0][10] == 0 && Tableau[0][11] == 0 && Tableau[0][12] == 0 && Tableau[0][13] == 0 && Tableau[0][14] == 0 &&
		Tableau[1][0] == 0 && Tableau[1][1] == 0 && Tableau[1][2] == 0 && Tableau[1][3] == 0 && Tableau[1][4] == 0 && Tableau[1][5] == 0 && Tableau[1][6] == 0 &&
		Tableau[1][7] == 0 && Tableau[1][8] == 0 && Tableau[1][9] == 0 && Tableau[1][10] == 0 && Tableau[1][11] == 0 && Tableau[1][12] == 0 && Tableau[1][13] == 0 && Tableau[1][14] == 0 &&
		Tableau[2][0] == 0 && Tableau[2][1] == 0 && Tableau[2][2] == 0 && Tableau[2][3] == 0 && Tableau[2][4] == 0 && Tableau[2][5] == 0 && Tableau[2][6] == 0 &&
		Tableau[2][7] == 0 && Tableau[2][8] == 0 && Tableau[2][9] == 0 && Tableau[2][10] == 0 && Tableau[2][11] == 0 && Tableau[2][12] == 0 && Tableau[2][13] == 0 && Tableau[2][14] == 0 &&
		Tableau[3][0] == 0 && Tableau[3][1] == 0 && Tableau[3][2] == 0 && Tableau[3][3] == 0 && Tableau[3][4] == 0 && Tableau[3][5] == 0 && Tableau[3][6] == 0 &&
		Tableau[3][7] == 0 && Tableau[3][8] == 0 && Tableau[3][9] == 0 && Tableau[3][10] == 0 && Tableau[3][11] == 0 && Tableau[3][12] == 0 && Tableau[3][13] == 0 && Tableau[3][14] == 0)
	{	// Si on a Eliminé tous les Cercles Tableau //
		ValidTir = false;												// On Annule le Déplacement Joueur //
		ChoixCouleurJoueur = 0;											// Pour Aucun Affichage Joueur //
		PlaySound(TEXT("Datas\\Victoire.wav"), NULL, SND_FILENAME | SND_ASYNC);	// On Joue le Son 'VICTOIRE' //

		glMatrixMode(GL_PROJECTION);									// Matrice Active -> Projection //
		glPushMatrix();													// On Copie la Matrice Active en Haut de la Pile //													
		glLoadIdentity();												// On Vide la Matrice //
		gluOrtho2D(0.0,420.0,330.0, 0.0);								// Transformation de Projection (Perspective Cavalière 2D) //

		glMatrixMode(GL_MODELVIEW);										// Matrice Active -> Modélisation-Visualisation //			
		glPushMatrix();													// On Copie la Matrice Active en Haut de la Pile //
		glLoadIdentity();												// On Vide la Matrice //

		glColor3d(0.0, 0.0, 0.0);										// Texte en Noir //

		glRasterPos2i(155,160);											// Position du Texte //


		string s = "VICTOIRE";											// Texte à afficher //

		void* font = GLUT_BITMAP_TIMES_ROMAN_24;						// On définit le Type de Police et sa Taille //

		for (string::iterator i = s.begin(); i != s.end(); ++i)
		{
			char c = *i;												// Fonction GLUT affichage Texte //
			glutBitmapCharacter(font, c);
		}

		glMatrixMode(GL_MODELVIEW);										// Matrice Active -> Modélisation-Visualisation //	
		glPopMatrix();													// On Retire la Matrice du Haut de la Pile //													 

		glMatrixMode(GL_PROJECTION);									// Matrice Active -> Projection //
		glPopMatrix();													// On Retire la Matrice du Haut de la Pile //

		ValidFin = true;												// On Valide la Fin du Jeu (VICTOIRE) //

	}

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);										// On Vide le Tampon Chromatique //
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	DessinerTableau();													// On Affiche le Tableau //

	glColor3f(0.5, 0.5, 0.5);											// De Couleur Grise //
	glBegin(GL_LINES);													// Dessin Ligne de Démarquation (DEFAITE) //
	glVertex2f(0,9);													// Premiers Points de Coordonnées //
	glVertex2f(15,9);													// Deuxièmes Points de Coordonnées //
	glEnd();															// Fin Dessin Ligne //
	glFlush();															// Achèvement de toutes Commandes Précédentes //


	glColor3f(0.0, 0.0, 0.0);											// De Couleur Noire //

	glPushMatrix();														// On Copie la Matrice Active en Haut de la Pile //


	glTranslated(7.5,9.5,0.0);											// On Change le système de Coordonnées //
	glRotated(AngleRotation, 0.0, 0.0, 1.0);							// On effectue une Rotation sur l'axe des Z en fonction de l'angle //


	glRectf(-0.05,0.0,0.05,-2.0);										// On Dessine un Rectangle (Ligne de Tir) //

	glFlush();															// Achèvement de toutes Commandes Précédentes //


	glPopMatrix();														// On Retire la Matrice Active du Haut de la Pile //

	PositionInit();														// On Execute la Fonction Positions Initiale Des Cercles Joueur //

	DessinerJoueur();													// On Affiche le Joueur //

	GestionCollision();													// On Execute la Fonction Gestion des Collisions //

	TestDefaite();														// On Teste la Defaite //

	TestVictoire();														// On Teste la Victoire //


	glutSwapBuffers();													// Inversion Tampons d'affichage //


}



int main(int argc, char** argv)											// Fonction Principale //
{
	FreeConsole();														// On Masque la Console //

	srand((int)time(NULL));												// Amorçage du Pseudo-Aléatoire //

	glutInit(&argc, argv);												// Fonction Initialisation GLUT //
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);						// Modes Affichage //
	glutInitWindowPosition(750,435);									// Fonction GLUT Position Initiale Fenêtre OPENGL //
	glutInitWindowSize(420, 330);										// Fonction GLUT Taille Initiale Fenêtre OPENGL //
	glutCreateWindow("Bubble Shooter");									// Fonction GLUT Création Fenêtre OPENGL //
	init();																// Fonction Initialisation Affichage //
	glutDisplayFunc(display);											// Fonction GLUT Affichage Scène //
	glutReshapeFunc(reshape);											// Fonction GLUT Redimensionnement Fenêtre OPENGL //
	glutSpecialFunc(keyboard);											// Fonction GLUT Gestion Clavier //
	glutTimerFunc(TimerMillis, GestionTir, 0);							// Fonction GLUT Gestion Timer Déplacement Joueur //
	glutMainLoop();														// Fonction GLUT Boucle Fonction Principale //

	return 0;
}