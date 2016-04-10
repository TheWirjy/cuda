#pragma once
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "MathTools.h"
#include "FractaleMath.h"

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

class JuliaMath : public FractaleMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:
	__device__
	JuliaMath(uint n, float re, float im) : FractaleMath(n)
	    {
	    this->c.x = re;
	    this->c.y = im;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF
	__device__
	virtual ~JuliaMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    protected:

	__device__
	virtual int getIndice(float x, float y)
	    {
	    float a, b, aCopy;
	    int k = 0;

	    a = x;
	    b = y;
	    aCopy = 0.0;

	    while(k <= this->n  && !isDivergent(a, b))
		{
		aCopy = a;
		a = ((a*a) - (b * b)) + this->c.x;
		b = 2 * aCopy * b + this->c.y;
		k++;
		}

	    return k;
	    }

    private:

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

	//Input
	float2 c;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
