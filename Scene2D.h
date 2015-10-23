/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __SCENE2D_H__
#define __SCENE2D_H__
#include <visp/vpMatrix.h>
#include <visp/vpColVector.h>
#include <visp/vpHomogeneousMatrix.h>
#include <vector>

class Scene2D {
    public:
        Scene2D();
        ~Scene2D();
        void setCameraPosition(const vpHomogeneousMatrix & cMs);
        void addPoint(const vpColVector & sX);
        vpColVector getPointToFramePosition(int pointId = 0);
        vpColVector getPointToFramePosition(vpColVector & vect);
        void display();

    private:
        vpHomogeneousMatrix _cMs;
        std::vector<vpColVector> _sXi;
        vpMatrix _cameraParam;
        vpMatrix _pi;

};

#endif /* __SCENE2D_H__ */
