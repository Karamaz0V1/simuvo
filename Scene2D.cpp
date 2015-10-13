/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "Scene2D.h"
#include <visp/vpImage.h>
#include <visp/vpDisplayX.h>

using std::vector;

Scene2D::Scene2D() {}
Scene2D::~Scene2D() {}
void Scene2D::setCameraPosition(const vpHomogeneousMatrix & cMs) {
    _cMs = cMs;
}

void Scene2D::addPoint(const vpColVector & sX) {
    _sXi.push_back(sX);
}

vpColVector Scene2D::getPointToFramePosition(int pointId) {
    // TODO: test pointId
    // TODO: test cMs
    // TODO: pull request sur visp pour const vpCV
    return _cMs.inverse() * _sXi[pointId];
}

void Scene2D::display() const {
    vpImage<vpRGBa> image(512, 512);
    vpDisplayX disp(image, 10, 10, "simuvo");
    vpDisplay::display(image);

    for (vector<vpColVector>::const_iterator it = _sXi.begin(); it != _sXi.end(); it++) {
        // TODO vpImagePoint <- vpColVector
        vpImagePoint ip;//(i, j);
        vpDisplay::displayCross(image, ip, 5, vpColor::blue);
    vpImagePoint ip1;
    }

    vpDisplay::flush(image);
    vpDisplay::getClick(image);
}
