/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "Scene2D.h"
#include "kvisp.h"
#include <visp/vpImage.h>
#include <visp/vpDisplayX.h>
#define WIDTH 512
#define HEIGHT 512

using std::vector;

Scene2D::Scene2D() : _cameraParam(3, 3), _pi(3, 4) {
    double f = 300;
    _cameraParam[0][0] = f;
    _cameraParam[1][1] = f;
    _cameraParam[2][2] = 1;
    _cameraParam[0][2] = WIDTH / 2;
    _cameraParam[1][2] = HEIGHT / 2;

    std::cout << _cameraParam << std::endl;

    _pi[0][0] = 1;
    _pi[1][1] = 1;
    _pi[2][2] = 1;
}
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
    return getPointToFramePosition(_sXi[pointId]);
}

vpColVector Scene2D::getPointToFramePosition(vpColVector & vect) {
    std::cout << "Dans le meilleur des mondes : " << _pi * (_cMs * vect) << std::endl;
    return _cameraParam * (_pi * (_cMs * vect));
    return _cameraParam * (_pi * (_cMs.inverse() * vect));
}

void Scene2D::display() {
    vpImage<vpRGBa> image(WIDTH, HEIGHT);
    vpDisplayX disp(image, 10, 10, "simuvo");
    vpDisplay::display(image);

    for (vector<vpColVector>::iterator it = _sXi.begin(); it != _sXi.end(); it++) {
        // TODO vpImagePoint <- vpColVector
        vpColVector tmp = getPointToFramePosition(*it);
        vpImagePoint ip = vpColVectorToVpImagePoint(tmp);
        std::cout << ip << std::endl;
        vpDisplay::displayCross(image, ip, 5, vpColor::green);
    }

    vpDisplay::flush(image);
    vpDisplay::getClick(image);
}
