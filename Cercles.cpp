#include "Cercles.h"													// Inclusion Fichier En-Tête 'Cercles.h' //
#include "GL/glut.h"													// Inclusion Fichier Bib. GLUT //


extern int PosXRougeTableau, PosYRougeTableau;
extern GLdouble PosXRougeJoueur, PosYRougeJoueur;
extern int PosXVertTableau, PosYVertTableau;
extern GLdouble PosXVertJoueur, PosYVertJoueur;
extern int PosXBleuTableau, PosYBleuTableau;
extern GLdouble PosXBleuJoueur, PosYBleuJoueur;
extern int PosXGrisTableau, PosYGrisTableau;
extern GLdouble PosXGrisJoueur, PosYGrisJoueur;
extern int PosXNoirTableau, PosYNoirTableau;
extern GLdouble PosXNoirJoueur, PosYNoirJoueur;



void Cercles::DessinerRougeTableau()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXRougeTableau+ 0.5, PosYRougeTableau + 0.5, 0.0);	// Position Coordonnées du Cercle Rouge Tableau dans la Scene //
	glColor3d(1.0, 0.0, 0.0);											// Couleur Rouge //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}


void Cercles::DessinerRougeJoueur()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXRougeJoueur + 0.5, PosYRougeJoueur + 0.5, 0.0);	// Position Coordonnées du Cercle Rouge Joueur dans la Scene //
	glColor3d(1.0, 0.0, 0.0);											// Couleur Rouge //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}



void Cercles::DessinerVertTableau()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXVertTableau + 0.5, PosYVertTableau + 0.5, 0.0);	// Position Coordonnées du Cercle Vert Tableau dans la Scene //
	glColor3d(0.0, 1.0, 0.0);											// Couleur Verte //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}


void Cercles::DessinerVertJoueur()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXVertJoueur + 0.5, PosYVertJoueur + 0.5, 0.0);		// Position Coordonnées du Cercle Vert Joueur dans la Scene //
	glColor3d(0.0, 1.0, 0.0);											// Couleur Verte //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}



void Cercles::DessinerBleuTableau()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXBleuTableau + 0.5, PosYBleuTableau + 0.5, 0.0);	// Position Coordonnées du Cercle Bleu Tableau dans la Scene //
	glColor3d(0.0, 0.0, 1.0);											// Couleur Bleue //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}


void Cercles::DessinerBleuJoueur()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXBleuJoueur + 0.5, PosYBleuJoueur + 0.5, 0.0);		// Position Coordonnées du Cercle Bleu Joueur dans la Scene //
	glColor3d(0.0, 0.0, 1.0);											// Couleur Bleue //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}



void Cercles::DessinerGrisTableau()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXGrisTableau + 0.5, PosYGrisTableau + 0.5, 0.0);	// Position Coordonnées du Cercle Gris Tableau dans la Scene //
	glColor3d(0.5, 0.5, 0.5);											// Couleur Grise //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}


void Cercles::DessinerGrisJoueur()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXGrisJoueur + 0.5, PosYGrisJoueur + 0.5, 0.0);		// Position Coordonnées du Cercle Gris Joueur dans la Scene //
	glColor3d(0.5, 0.5, 0.5);											// Couleur Grise //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}



void Cercles::DessinerNoirTableau()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXNoirTableau + 0.5, PosYNoirTableau + 0.5, 0.0);	// Position Coordonnées du Cercle Noir Tableau dans la Scene //
	glColor3d(0.0, 0.0, 0.0);											// Couleur Noire //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}


void Cercles::DessinerNoirJoueur()
{

	glPushMatrix();														// On Sauvegarde la Matrice active avant Translation //

	glTranslated(PosXNoirJoueur + 0.5, PosYNoirJoueur + 0.5, 0.0);		// Position Coordonnées du Cercle Noir Joueur dans la Scene //
	glColor3d(0.0, 0.0, 0.0);											// Couleur Noire //
	glutSolidSphere(0.5, 12, 12);										// Dessin du Cercle //

	glPopMatrix();														// On Restaure la Matrice active après translation //


}




