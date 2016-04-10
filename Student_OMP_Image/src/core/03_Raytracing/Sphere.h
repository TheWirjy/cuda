#ifndef SPHERE_H
#define SPHERE_H

#include "OmpTools.h"
#include <math.h>
#include "MathTools.h"

#ifndef PI
#define PI 3.141592653589793f
#endif
using namespace cpu;

class Sphere
{
    public:

	Sphere(float x, float y, float z, float rayon, float hue)
	    {
	    // Inputs
	    this->centre.x = x;
	    this->centre.y = y;
	    this->centre.z = z;
	    this->r = rayon;
	    this->hueStart = hue;
	    // Tools
	    this->rCarre = rayon * rayon;
	    }

	 /**
	 * required by example for new Sphere[n]
	 */
	 Sphere()
	     {
	     // rien
	     }

	 float hCarre(float2 xySol)
	     {
	     float a = (centre.x - xySol.x);
	     float b = (centre.y - xySol.y);
	     return a * a + b * b;
	     }

	 bool isEnDessous(float hCarre)
	     {
	     return hCarre < rCarre;
	     }

	 float dz(float hCarre)
	     {
	     return sqrtf(rCarre - hCarre);
	     }

	 float brightness(float dz)
	     {
	     return dz / r;
	     }

	 float distance(float dz)
	     {
	     return centre.z - dz;
	     }

	float getHueStart()
	    {
	    return hueStart;
	    }

	float hue(float t)// usefull for animation
	    {
	    return 0.5 + 0.5 * sin(t + T + 3 * PI / 2);
	    }

    private:

	// Inputs
	float r;
	float3 centre;
	float hueStart;

	// Tools
	float rCarre;
	float T ; // usefull for animation
    };
#endif
