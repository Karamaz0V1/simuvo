/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#include "kvisp.h"

vpColVector vpColVector3(const double x, const double y, const double z) {
    vpColVector cv(3);
    cv[0] = x;
    cv[1] = y;
    cv[2] = z;
    return cv;
}

