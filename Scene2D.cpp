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
#include <visp/vpExponentialMap.h>
#define WIDTH 512
#define HEIGHT 512

using std::vector;
using std::cout;
using std::endl;

Scene2D::Scene2D() : _cameraParam(3, 3), _pi(3, 4) {
    double f = 300;
    _cameraParam[0][0] = f;
    _cameraParam[1][1] = f;
    _cameraParam[2][2] = 1;
    _cameraParam[0][2] = WIDTH / 2;
    _cameraParam[1][2] = HEIGHT / 2;

    _pi[0][0] = 1;
    _pi[1][1] = 1;
    _pi[2][2] = 1;
}
Scene2D::~Scene2D() {}
void Scene2D::setCameraPosition(const vpHomogeneousMatrix & cMs) {
    _cMs = cMs;
}

void Scene2D::setDesiredCameraPosition(const vpHomogeneousMatrix & cMs) {
    for (vector<vpColVector>::iterator it = _sXi.begin(); it != _sXi.end(); it++) {
        auto tmp = cMs * (*it);
        addDesiredPoint(tmp);
        std::cout << "Point desiré: " << tmp.t() << endl;
    }
}

void Scene2D::addPoint(const vpColVector & sX) {
    _sXi.push_back(sX);
}

void Scene2D::addDesiredPoint(const vpColVector & sXe) {
    _sXie.push_back(sXe);
}

vpColVector Scene2D::getPointToFramePosition(int pointId) {
    // TODO: pull request sur visp pour const vpCV
    return getPointToFramePosition(_sXi[pointId]);
}

vpColVector Scene2D::getPointToFramePosition(vpColVector & vect) {
    return _cameraParam * (_pi * (_cMs * vect));
    return _cameraParam * (_pi * (_cMs.inverse() * vect));
}

void Scene2D::display() {
    vpImage<vpRGBa> image(WIDTH, HEIGHT);
    vpDisplayX disp(image, 10, 10, "simuvo");
    vpDisplay::display(image);

    for (vector<vpColVector>::iterator it = _sXi.begin(); it != _sXi.end(); it++) {
        vpColVector tmp = getPointToFramePosition(*it);
        vpImagePoint ip(tmp[1] / tmp[2],tmp[0] / tmp[2]);
        vpDisplay::displayCross(image, ip, 5, vpColor::green);
    }

    vpDisplay::flush(image);
    vpDisplay::getClick(image);
}

double Scene2D::ptError(const vpColVector & p1, const vpColVector & p2) const {
    return sqrt((p1[0]-p2[0]) * (p1[0]-p2[0]) + (p1[1]-p2[1]) * (p1[1]-p2[1]) + (p1[2]-p2[2]) * (p1[2]-p2[2]));
}

void Scene2D::displayPt(const vpImage<vpRGBa> & image, const vector<vpColVector> & points) {
    for (vector<vpColVector>::iterator it = _sXi.begin(); it != _sXi.end(); it++) {
        vpColVector tmp = getPointToFramePosition(*it);
        vpImagePoint ip(tmp[1] / tmp[2],tmp[0] / tmp[2]);
        vpDisplay::displayCross(image, ip, 5, vpColor::blue);
    }
}

void Scene2D::command() {
    double dt = 0.001;
    vpImage<vpRGBa> image(WIDTH, HEIGHT);
    vpDisplayX disp(image, 10, 10, "simuvo");
    vpDisplay::display(image);

    displayPt(image, _sXie);
    vpDisplay::flush(image);
    vpDisplay::getClick(image);

    for (int i = 0; i < 10000; i++) {
        vpColVector v = computeV();
        std::cout << "Vitesses : " <<  v.t() << endl;

        // Is that normal v.sum() isn't working ?
        //v.sum();

        _cMs = vpExponentialMap::direct(v, dt).inverse() * _cMs;

        // DISPLAY
        for (vector<vpColVector>::iterator it = _sXi.begin(); it != _sXi.end(); it++) {
            vpColVector tmp = getPointToFramePosition(*it);
            cout << "P1: " << (*it).t() << endl;
            cout << "P2: " << (_cMs * (*it)).t() << endl;
            cout << "Error: " << ptError(tmp, *it) << endl;
            // Compare sXi & sXie 

            vpImagePoint ip(tmp[1] / tmp[2],tmp[0] / tmp[2]);
            if (i == 0)
                vpDisplay::displayCross(image, ip, 5, vpColor::green);
            else
                vpDisplay::displayCross(image, ip, 5, vpColor(0,255,i/40));
        }
        vpDisplay::flush(image);
    }
    vpDisplay::getClick(image);
}

vpColVector Scene2D::computeV() {
    vpColVector s(8);
    vpColVector se(8);

    // s & s*
    for (int i = 0; i < 4; i++) {
        // TODO: need /[2]
        vpColVector S = _cMs * _sXi[i];
        s[2*i] = S[0] / S[2];
        s[2*i+1] = S[1] / S[2];
        se[2*i] = _sXie[i][0] / _sXie[i][2];
        se[2*i+1] = _sXie[i][1] / _sXie[i][2];
        //cout << "sXi:  " << _sXi[i].t() << endl;
        //cout << "sXie: " << _sXie[i].t() << endl;
    }

    //cout << "s: " << s.t() << endl;
    //cout << "se: " << se.t() << endl;
    // e
    vpColVector e = s - se;
    //cout << "ERREUR: " << e.t() << endl;

    // L
    vpMatrix L(8, 6);
    for (int i = 0; i < 4; i++) {
        vpColVector C = _cMs * _sXi[i];
        auto x = C[0] / C[2];
        auto y = C[1] / C[2];
        auto z = C[2];
        L[2*i][0]   = -1 / z;
        L[2*i+1][0] = 0;
        L[2*i][1]   = 0;
        L[2*i+1][1] = -1/ z;
        L[2*i][2]   = x / z;
        L[2*i+1][2] = y / z;
        L[2*i][3]   = x * z;
        L[2*i+1][3] = 1 + y*y;
        L[2*i][4]   = -(1 + x*x);
        L[2*i+1][4] = -x * y;
        L[2*i][5]   = y;
        L[2*i+1][5] = -x;
    }

    // L+
    L = L.pseudoInverse();

    // v
    vpColVector v = -L * e;

    return v;
}
