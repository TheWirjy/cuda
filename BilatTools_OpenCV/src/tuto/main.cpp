#include <iostream>

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Importation 					*|
 \*---------------------------------------------------------------------*/

extern bool useCapture();
extern bool useShapeOverlay();

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char **argv);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static bool work();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int main(int argc, char **argv)
    {
    bool isOk=true;
    isOk&=work();

    return isOk?EXIT_SUCCESS:EXIT_FAILURE;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool work()
    {
    bool isOk = true;

    isOk &= useCapture();
    isOk &= useShapeOverlay();

    return isOk;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
