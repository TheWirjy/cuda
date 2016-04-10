#include "Indice2D.h"
#include "cudaTools.h"
#include "Device.h"

#include "IndiceTools_GPU.h"
#include "JuliaMath.h"
#include "MandelbrotMath.h"
#include "FractaleMath.h"
#include "DomaineMath_GPU.h"

using namespace gpu;

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrotJulia(uchar4* ptrDevPixels, uint w, uint h, float n, DomaineMath domaineMath);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void mandelbrotJulia(uchar4* ptrDevPixels, uint w, uint h, float n, DomaineMath domaineMath)
    {
    JuliaMath fractaleMath(n, -0.12, 0.85);
    //MandelbrotMath fractaleMath(n);

    const int TID = Indice2D::tid();
    const int NB_THREAD = Indice2D::nbThread();
    const int WH = w * h;

    uchar4 color;
    int pixelI;	// in [0,h[
    int pixelJ; // in [0,w[

    double x;
    double y;

    int s = TID;
    while (s < WH)
	{
	IndiceTools::toIJ(s, w, &pixelI, &pixelJ); 	// update (pixelI, pixelJ)

	domaineMath.toXY(pixelI, pixelJ, &x, &y);

	fractaleMath.colorXY(&color,x, y); 	// update color
	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

