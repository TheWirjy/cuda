#include <iostream>
#include <assert.h>

#include "Device.h"
#include "Raytracing.h"
#include "Sphere.h"
#include "AleaTools.h"

using std::cout;
using std::endl;

#define USE_SM false

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void raytracing(uchar4* ptrDevPixels, Sphere* ptrDevSphere, uint nbSphere, uint w, uint h, float t);

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

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Raytracing::Raytracing(const Grid& grid, uint w, uint h, float dt, uint nbSphere) : Animable_I<uchar4>(grid, w, h, "RayTracing_Cuda_RGBA_uchar4")
    {
        this->nbSphere = nbSphere;
        this->tabSphere = new Sphere[nbSphere];

        // Dimension
        this->w = w;
        this->h = h;
        this->dt = dt;
        this->t = 0;

        AleaTools aleaTools = AleaTools();
        float bord = 200;
        for(int i=0;i<nbSphere;i++)
    	    {
    	    float rayon = aleaTools.uniformeAB(20, this->w / 10);
    	    float x = aleaTools.uniformeAB(bord, this->h - bord);
    	    float y = aleaTools.uniformeAB(bord, this->w - bord);
    	    float z = aleaTools.uniformeAB(10, 2 * this->w);
    	    float hue = aleaTools.uniforme01();
    	    tabSphere[i] = Sphere(x,y,z,rayon,hue);
    	    }
    }

Raytracing::~Raytracing()
    {
    delete[] tabSphere;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void Raytracing::process(uchar4* ptrDevPixels, uint w, uint h, const DomaineMath& domaineMath)
    {
    Sphere* ptrDevSphere=NULL;
    size_t size = this->nbSphere*sizeof(Sphere);
    HANDLE_ERROR(cudaMalloc(&ptrDevSphere,size));
    HANDLE_ERROR(cudaMemcpy(ptrDevSphere, this->tabSphere,size,cudaMemcpyHostToDevice));

    #if USE_SM
	raytracing<<<dg, db, size>>>(ptrDevPixels, ptrDevSphere, this->nbSphere, w, h, this->t);
    #else
	raytracing<<<dg, db>>>(ptrDevPixels,ptrDevSphere,this->nbSphere, w, h, this->t);
    #endif

    Device::lastCudaError("raytracing rgba uchar4 (after)"); // facultatif, for debug only, remove for release

    HANDLE_ERROR(cudaFree(ptrDevSphere));
    }

/**
 * Override
 * Call periodicly by the API
 */
void Raytracing::animationStep()
    {
    this->t += this->dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
