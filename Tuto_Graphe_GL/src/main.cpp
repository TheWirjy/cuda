#include <stdlib.h>

#include "GLUTWindowManagers.h"

// Sans animation
#include "DiscretCurveGlut.h"
#include "SinusGlut.h"
#include "LinesGlut.h"
#include "PolyligneGlut.h"
#include "NuagePointGlut.h"
#include "HistoGlut.h"
#include "HistoAdjustGlut.h"
#include "SpiraleGlut.h"

// Animation
#include "SinusAnimatedGlut.h"
#include "AnimateManuelGlut.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/



/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char **argv);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

static void useSimple(void);
static void useAdvanced(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char **argv)
    {
    // Session1
   	{
   	GLUTWindowManagers::init(argc, argv);
   	useSimple(); // Bloqaunt tant que all window pas close
   	}

       // Session2
   	{
   	// Commence des que la session1 est finie, ie que toute les fenetres sont fermees
   	// Note : session2 ne fonctionne pas sous Linux avec bureau � distance (L'api crash � la fermeture de la premi�re fen�tre)
	GLUTWindowManagers::init(argc, argv);
	useAdvanced();
   	}


    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


void useSimple(void)
    {
    int frameWidth = 800;
    int frameHeight = 600;
    int pxFrame = 10;
    int pyFrame = 10;

    // Use Static
    DiscretCurveGlut discretCurveGlut(frameWidth, frameHeight, pxFrame, pyFrame);

    SinusGlut sinus(frameWidth, frameHeight, pxFrame + 20, pyFrame + 20);

    LinesGlut lines(frameWidth, frameHeight, pxFrame + 40, pyFrame + 40);
    PolyligneGlut polyline(frameWidth, frameHeight, pxFrame + 60, pyFrame + 60);
    NuagePointGlut nuagePoint(frameWidth, frameHeight, pxFrame + 80, pyFrame + 80);

    HistoGlut histo(frameWidth, frameHeight, pxFrame + 100, pyFrame + 100);
    HistoAdjustGlut HistoAdjust(frameWidth, frameHeight, pxFrame + 120, pyFrame + 120);

    // Use Animation Simple
    SinusGlut sinusAnimated(frameWidth, frameHeight, pxFrame + 140, pyFrame + 140);
    sinusAnimated.getSinusGraphe()->getSinusCurve()->setAnimationEnable(true); // seul changement pour l'animation, false par defaut, Toute les fen�tre emploie le meme thread, celui de glut, ie le main.

    SinusAnimatedGlut animateMultiThread(frameWidth, frameHeight, pxFrame + 180, pyFrame + 180); // Chaque fenetre possede son thread de calcul

    SpiraleGlut spirale(frameWidth,frameHeight,pxFrame+200,pyFrame+200);

    GLUTWindowManagers::getInstance()->runALL();
    }

void useAdvanced(void)
    {
    int w=800;
    int h=400;
    int px=50;
    int py=10;

    AnimateManuelGlut animateManuel( w,  h,  px,  py);
    animateManuel.run(); // bloquant tant que fenetre ouverte
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

