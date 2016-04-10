#pragma once
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "MathTools.h"
#include "FractaleMath.h"

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

class MandelbrotMath : public FractaleMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	MandelbrotMath(uint n) : FractaleMath(n)
	    {
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	virtual ~MandelbrotMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    protected:


	virtual int indiceArret(float x, float y)
	    {
	    float a, b, aCopy;
	    int k = 0;

	    a = b = aCopy = 0.0;

	    while(k <= n  && (pow(a, 2.0) + pow(b, 2.0)) <= 4.0)
		{
		aCopy = a;
		a = pow(a, 2.0) - pow(b, 2.0) + x;
		b = 2 * aCopy * b + y;
		k++;
		}

	    return k;
	    }
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
