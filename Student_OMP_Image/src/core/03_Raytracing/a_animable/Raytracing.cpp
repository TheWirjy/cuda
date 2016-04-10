#include "Raytracing.h"

#include <iostream>
#include <omp.h>
#include "OmpTools.h"

#include "IndiceTools_CPU.h"
#include "math/RaytracingMath.h"
using cpu::IndiceTools;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

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

Raytracing::Raytracing(uint w, uint h, float dt, uint n, const DomaineMath& domaineMath, Sphere* tabSphere, int nbSphere) :
	Animable_I<uchar4>(w, h, "Raytracing_OMP",domaineMath), variateurAnimation(Interval<float>(30, 100), dt)
    {
    // Input
    this->dt = dt;
    this->n = n;
    this->ptrSphere = tabSphere;
    this->nbSphere = nbSphere;

    // Tools
    this->t = 0;					// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    // OMP
    cout << "\n[Raytracing] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable
    }

Raytracing::~Raytracing(void)
    {
    delete[] this->ptrSphere;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Raytracing::animationStep()
    {
    this->t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Override (code naturel omp)
 */
void Raytracing::processForAutoOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    RaytracingMath raytracingMath(t);

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    // int s = i * W + j;
	    int s = IndiceTools::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[
	    raytracingMath.colorXY(&ptrTabPixels[s],ptrSphere, nbSphere, i, j, t); // in [01]
	    //workPixel(&ptrTabPixels[s],i,j,domaineMath, &raytracingMath);
	    }
	}
    }

/**
 * Override (code entrainement cuda)
 */
void Raytracing::processEntrelacementOMP(uchar4* ptrTabPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    RaytracingMath raytracingMath(t);

    const int WH = w * h;

#pragma omp parallel
	{
	const int NB_THREAD = OmpTools::getNbThread(); // dans region parallel

	const int TID = OmpTools::getTid();
	int s = TID; // in [0,...

	int i;
	int j;
	while (s < WH)
	    {
	    IndiceTools::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

	    //workPixel(&ptrTabPixels[s],i,j,domaineMath, &raytracingMath);
	    raytracingMath.colorXY(&ptrTabPixels[s],ptrSphere, nbSphere, i, j, t); // in [01]
	    s += NB_THREAD;
	    }
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * i in [0,h[
 * j in [0,w[
 *
 * code commun a:
 * 	- entrelacementOMP
 * 	- forAutoOMP
 */
void Raytracing::workPixel(uchar4* ptrColorIJ,int i, int j,const DomaineMath& domaineMath, RaytracingMath* ptrFractalMath)
    {
    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2

    double x;
    double y;
    //domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

    //ptrFractalMath->colorXY(ptrColorIJ,x, y, t); // in [01]
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
