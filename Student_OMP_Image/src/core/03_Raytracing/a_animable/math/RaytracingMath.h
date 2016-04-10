#pragma once
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "MathTools.h"

#include "Calibreur_CPU.h"
#include "ColorTools_CPU.h"
#include "Sphere.h"
using namespace cpu;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RaytracingMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	RaytracingMath(uint _n) : calibreur(Interval<float>(0.0, _n), Interval<float>(0.0, 1.0))
	    {
	    this->n = _n;
	    }

	virtual ~RaytracingMath() {}

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(uchar4* ptrColor, Sphere* ptrDevSphere, int nbSphere, float x, float y,int t)
	    {

	    float2 xy;
	    xy.x = x;
	    xy.y = y;
	    float h = 0;
	    float b = 0;
	    float smallestDistance = 999999;
	    for (int i = 0; i < nbSphere; i++)
		{

		float h2 = ptrDevSphere[i].hCarre(xy);
		if (ptrDevSphere[i].isEnDessous(h2))
		    {
		    float dZ = ptrDevSphere[i].dz(h2);
		    float dist = ptrDevSphere[i].distance(dZ);
		    h = ptrDevSphere[i].hue(t);
		    b = ptrDevSphere[i].brightness(dZ);
		    }

		}
	    float3 hsb;
	    hsb.x = h;
	    hsb.y = 1.0;
	    hsb.z = b;
	    ColorTools::HSB_TO_RVB(hsb ,ptrColor);

	    ptrColor->w = 255; // opaque
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
