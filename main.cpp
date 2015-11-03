/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include <iostream>
#include "kvisp.h"
#include "Scene2D.h"
#include <visp/vpTranslationVector.h>
#include <visp/vpThetaUVector.h>

int main( int argc, char* argv[] )
{
    Scene2D s;
    s.setCameraPosition(vpHomogeneousMatrix(3, 0, 10, 0, 0, 0));
    //s.setCameraPosition(vpHomogeneousMatrix(vpTranslationVector(0,0,10), vpThetaUVector()));
    double L = 0.5;
    s.addPoint(vpColVector4(L,L,0,1));
    s.addDesiredPoint(vpColVector4(L,L,0,1));
    s.addDesiredPoint(vpColVector4(L,L,0,1));
    s.addDesiredPoint(vpColVector4(L,L,0,1));
    s.addDesiredPoint(vpColVector4(L,L,0,1));
    s.addPoint(vpColVector4(-L,L,0,1));
    s.addPoint(vpColVector4(-L,-L,0,1));
    s.addPoint(vpColVector4(L,-L,0,1));
    s.addPoint(vpColVector4(2*L,L,0,1));
    s.command();
    s.display();
    return 0;
}
