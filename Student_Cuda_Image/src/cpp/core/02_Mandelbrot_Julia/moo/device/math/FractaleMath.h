#pragma once
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "MathTools.h"

#include "Calibreur_GPU.h"
#include "ColorTools_GPU.h"
using namespace gpu;

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

	__device__ FractaleMath(uint _n) : calibreur(Interval<float>(0.0, _n), Interval<float>(0.0, 1.0))
	    {
	    this->n = _n;
	    }

	__device__
	virtual ~FractaleMath() {}

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:
	__device__
	void colorXY(uchar4* ptrColor, float x, float y)
	    {
	    float k = getIndice(x, y);

	    if(k <= this->n)
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
	__device__
	virtual int getIndice(float x, float y) = 0;

	__device__
	bool isDivergent(float a, float b)
	    {
	    return (a * a + b * b) > 4;
	    }

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