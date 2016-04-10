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

class JuliaMath : public FractaleMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	JuliaMath(uint n, float re, float im) : FractaleMath(n)
	    {
	    this->c.x = re;
	    this->c.y = im;
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	virtual ~JuliaMath()
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

	    a = x;
	    b = y;
	    aCopy = 0.0;

	    while(k <= n  && (pow(a, 2.0) + pow(b, 2.0)) <= 4.0)
		{
		aCopy = a;
		a = pow(a, 2.0) - pow(b, 2.0) + this->c.x;
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
