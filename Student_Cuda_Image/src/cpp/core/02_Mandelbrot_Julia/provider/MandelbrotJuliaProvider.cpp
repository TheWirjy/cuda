#include "MandelbrotJuliaProvider.h"
#include "MandelbrotJulia.h"

#include "MathTools.h"
#include "Grid.h"
#include "DomaineMath_GPU.h"
using namespace gpu;

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

/**
 * Override
 */
Animable_I<uchar4>* MandelbrotJuliaProvider::createAnimable()
    {
    DomaineMath domaineMath = DomaineMath(-1.3, -1.4, 1.3, 1.4);

    //DomaineMath domaineMath = DomaineMath(-2.1, 1.3, 0.8, -1.3);

    // Animation;
    float dt = 1;
    int n = 52;

    // Dimension
    int dw = 16 * 60;
    int dh = 16 * 60;

    dim3 dg = dim3(32, 2, 1);  		// disons a optimiser, depend du gpu
    dim3 db = dim3(16, 16, 1);   	// disons a optimiser, depend du gpu
    Grid grid(dg, db);

    return new MandelbrotJulia(grid,dw, dh, dt, n, domaineMath);
    }

/**
 * Override
 */
Image_I* MandelbrotJuliaProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }



/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
