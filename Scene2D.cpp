/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "Scene2D.h"

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
