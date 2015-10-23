/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __KVISP_H__
#define __KVISP_H__
#include <visp/vpColVector.h>
#include <visp/vpImagePoint.h>

vpColVector vpColVector3(const double x, const double y, const double z);
vpImagePoint vpColVectorToVpImagePoint(vpColVector & vect);


#endif /* __KVISP_H__ */
