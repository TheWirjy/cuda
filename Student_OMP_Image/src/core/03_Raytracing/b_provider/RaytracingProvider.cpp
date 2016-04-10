#include "RaytracingProvider.h"
#include "Raytracing.h"
#include "MathTools.h"

#include "ImageAnimable_CPU.h"
#include "DomaineMath_CPU.h"
#include "Sphere.h"
#include "AleaTools.h"
using namespace cpu;


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Surcharge		*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* RaytracingProvider::createAnimable(void)
    {
    //DomaineMath domaineMath = DomaineMath(-2.1, -1.3, 0.8, 1.3);
    DomaineMath domaineMath = DomaineMath(-1.3, -1.4, 1.3, 1.4);

    // Animation;
    float dt = 1;
    int n = 20;
    int nbSphere = 50;
    Sphere* tabSphere = new Sphere[nbSphere];
    // Dimension
    int dw = 16 * 80;
    int dh = 16 * 60;

    AleaTools aleaTools = AleaTools();
    float bord = 200;
    for(int i=0;i<nbSphere;i++)
    	{
    	//TODO random
    	float rayon = aleaTools.uniformeAB(20, dw/10);
    	float x = aleaTools.uniformeAB(bord, dh -bord);
    	float y = aleaTools.uniformeAB(bord, dw -bord);
    	float z = aleaTools.uniformeAB(10, 2* dw);
    	float hue = aleaTools.uniforme01();
    	tabSphere[i] = Sphere(x,y,z,rayon,hue);
    	}

    return new Raytracing(dw, dh, dt, n, domaineMath, tabSphere, nbSphere);
    }

/**
 * Override
 */
Image_I* RaytracingProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(),colorTexte);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/


/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
