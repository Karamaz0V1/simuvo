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
    s.setCameraPosition(vpHomogeneousMatrix(vpTranslationVector(0,0,1), vpThetaUVector()));
    double L = 0.5;
    s.addPoint(vpColVector3(L,L,0));
    s.addPoint(vpColVector3(-L,L,0));
    s.addPoint(vpColVector3(-L,-L,0));
    s.addPoint(vpColVector3(L,-L,0));
    return 0;
}
