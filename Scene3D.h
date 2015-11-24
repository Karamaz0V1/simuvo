/***************************************************************************
 *
 * TODO: Project Title
 *
 * Author: Florent Guiotte <guiotte.florent@gmail.com>
 *
 **************************************************************************/

#ifndef __SCENE3D_H__
#define __SCENE3D_H__
#include "Scene2D.h"

class Scene3D: public Scene2D {
    public:
        virtual vpColVector computeV();
};


#endif /* __SCENE3D_H__ */
