#include "AddVector.h"

#include <iostream>

#include "Device.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void addVector(float* ptrDevV1, float* ptrDevV2, float* ptrDevW,int n);

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
 |*		Constructeur			*|
 \*-------------------------------------*/

AddVector::AddVector(float* ptrV1, float* ptrV2, float* ptrW, int n) :
	ptrV1(ptrV1), ptrV2(ptrV2), ptrW(ptrW), n(n)
    {
    this->sizeOctet = n * sizeof(float); // octet

    // MM
	{
	// MM (malloc Device)
	    {
	    HANDLE_ERROR(cudaMalloc(&ptrDevV1, sizeOctet));
	    HANDLE_ERROR(cudaMalloc(&ptrDevV2, sizeOctet));
	    HANDLE_ERROR(cudaMalloc(&ptrDevW, sizeOctet));
	    }

	// MM (memset Device)
	    {
	    HANDLE_ERROR(cudaMemset(ptrDevW, 0, sizeOctet));
	    }

	// MM (copy Host->Device)
	    {
	    HANDLE_ERROR(cudaMemcpy(ptrDevV1, ptrV1, sizeOctet, cudaMemcpyHostToDevice));
	    HANDLE_ERROR(cudaMemcpy(ptrDevV2, ptrV2, sizeOctet, cudaMemcpyHostToDevice));
	    }

	Device::lastCudaError("AddVector MM (end allocation)"); // temp debug
	}

    // Grid
	{
	this->dg = dim3(16, 2, 1); // disons, a optimiser selon le gpu
	this->db = dim3(32, 4, 1); // disons, a optimiser selon le gpu

	Device::gridHeuristic(dg, db);
	}
    }

AddVector::~AddVector(void)
    {
    //MM (device free)
	{
	HANDLE_ERROR(cudaFree(ptrDevV1));
	HANDLE_ERROR(cudaFree(ptrDevV2));
	HANDLE_ERROR(cudaFree(ptrDevW));

	Device::lastCudaError("AddVector MM (end deallocation)"); // temp debug
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void AddVector::run()
    {
    Device::lastCudaError("addVecteur (before)"); // temp debug
    addVector<<<dg,db>>>(ptrDevV1, ptrDevV2, ptrDevW, n); // assynchrone
    Device::lastCudaError("addVecteur (after)"); // temp debug

    Device::synchronize(); // Temp, only for printf in  GPU

    // MM (Device -> Host)
	{
	HANDLE_ERROR(cudaMemcpy(ptrW, ptrDevW, sizeOctet, cudaMemcpyDeviceToHost)); // barriere synchronisation implicite
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
