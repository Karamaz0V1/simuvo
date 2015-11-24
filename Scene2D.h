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
#include <visp/vpImage.h>
#include <vector>

class Scene2D {
    public:
        Scene2D();
        ~Scene2D();
        void setCameraPosition(const vpHomogeneousMatrix & cMs);
        void setDesiredCameraPosition(const vpHomogeneousMatrix & cMs);
        void addPoint(const vpColVector & sX);
        void addDesiredPoint(const vpColVector & sXe);
        vpColVector getPointToFramePosition(int pointId = 0);
        vpColVector getPointToFramePosition(vpColVector & vect);
        void displayPt(const vpImage<vpRGBa> & image, const std::vector<vpColVector> & points);
        double ptError(const vpColVector & p1, const vpColVector & p2) const;
        void display();
        void command();

    private:
        vpHomogeneousMatrix _cMs;
        std::vector<vpColVector> _sXi;
        std::vector<vpColVector> _sXie;
        vpMatrix _cameraParam;
        vpMatrix _pi;

    private:
        virtual vpColVector computeV();

};

#endif /* __SCENE2D_H__ */
