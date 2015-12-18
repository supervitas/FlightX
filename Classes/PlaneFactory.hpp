//
//  PlaneFactory.hpp
//  FlightX
//
//  Created by Виталий on 15.12.15.
//
//

#ifndef PlaneFactory_hpp
#define PlaneFactory_hpp

#include <stdio.h>
#include "EnemyPlane.h"

class EnemyPlaneFactory
{
public:
    EnemyPlaneFactory(DefaultPlane* player_plane);
    EnemyPlane* createSimplePlane();
    EnemyPlane* createKamikazePlane();
    EnemyPlane* createPlane(int);
private:
    DefaultPlane* _player_plane;
};


#endif /* PlaneFactory_hpp */
