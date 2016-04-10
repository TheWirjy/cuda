#pragma once
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
using namespace cpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class FractaleMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	FractaleMath(uint _n) : calibreur(Interval<float>(0.0, _n), Interval<float>(0.0, 1.0))
	    {
	    this->n = _n;
	    }

	virtual ~FractaleMath() {}

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, float x, float y, float t)
	    {
	    float k = indiceArret(x, y);

	    if(k <= n)
		{
		calibreur.calibrer(k);

		float hue01 = k;

		ColorTools::HSB_TO_RVB(hue01, ptrColor); // update color
		}
	    else
		{
		ptrColor->x = 0;
		ptrColor->y = 0;
		ptrColor->z = 0;
		}

	    ptrColor->w = 255; // opaque
	    }

    protected:

	virtual int indiceArret(float x, float y) = 0;

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
