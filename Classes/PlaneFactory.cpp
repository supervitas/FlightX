//
//  PlaneFactory.cpp
//  FlightX
//
//  Created by Виталий on 15.12.15.
//
//

#include "PlaneFactory.hpp"

EnemyPlaneFactory::EnemyPlaneFactory(DefaultPlane* player_plane)
{
    _player_plane = player_plane;
}

EnemyPlane* EnemyPlaneFactory::createSimplePlane()
{
    EnemyPlane* new_plane = EnemyPlane::create(_player_plane);
    new_plane->ChangeBehavoiur(_player_plane);
    return new_plane;
}

EnemyPlane* EnemyPlaneFactory::createKamikazePlane()
{
    EnemyPlane* new_plane = EnemyPlane::create(_player_plane);
    new_plane->ChangeBehavoiur(_player_plane, 1);
    return new_plane;
}

EnemyPlane* EnemyPlaneFactory::createPlane(int plane_type)
{
    EnemyPlane* new_plane = NULL;
    switch (plane_type) {
        case 0:
            new_plane = createSimplePlane();
            break;
            
        case 1:
            new_plane = createKamikazePlane();
            break;
            
        default:
            break;
    }
    return new_plane;
}