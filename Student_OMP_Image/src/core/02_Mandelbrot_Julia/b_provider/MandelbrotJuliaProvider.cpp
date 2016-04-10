#include "MandelbrotJuliaProvider.h"
#include "JuliaMath.h"
#include "MathTools.h"

#include "ImageAnimable_CPU.h"
#include "DomaineMath_CPU.h"

#include "../a_animable/MandelbrotJulia.h"
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
Animable_I<uchar4>* MandelbrotJuliaProvider::createAnimable(void)
    {
    //DomaineMath domaineMath = DomaineMath(-2.1, -1.3, 0.8, 1.3);
    DomaineMath domaineMath = DomaineMath(-1.3, -1.4, 1.3, 1.4);

    // Animation;
    float dt = 1;
    int n = 52;

    // Dimension
    int dw = 16 * 80;
    int dh = 16 * 60;

    return new MandelbrotJulia(dw, dh, dt, n, domaineMath);
    }

/**
 * Override
 */
Image_I* MandelbrotJuliaProvider::createImageGL(void)
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
