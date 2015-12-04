#include "Behaviour.h"

AbstractPlaneBehavoiur::AbstractPlaneBehavoiur(DefaultPlane* owner, DefaultPlane* player_plane)
{
	_owner = owner;
	_player_plane = player_plane;
}

AbstractPlaneBehavoiur::~AbstractPlaneBehavoiur()
{

}

DefaultPlane* AbstractPlaneBehavoiur::GetOwner()
{
	return _owner;
}

DefaultPlane* AbstractPlaneBehavoiur::GetPlayerPlane()
{
	return _player_plane;
}



Vec2 AbstractPlaneBehavoiur::directionToPlayer()
{
	return vectorToPlayer().getNormalized();
}

float AbstractPlaneBehavoiur::distanceToPlayer()
{
	return vectorToPlayer().getLength();
}

Vec2 AbstractPlaneBehavoiur::vectorToPlayer()
{
	return (_player_plane->getPosition() - _owner->getPosition());
}

float AbstractPlaneBehavoiur::angleToPlayer()
{
	//return Vec2::angle(Vec2(1.0f, .0f), vectorToPlayer());
	return vectorToPlayer().getAngle();
}



SimplePlaneBehaviour::SimplePlaneBehaviour(DefaultPlane* owner, DefaultPlane* player_plane) : AbstractPlaneBehavoiur(owner, player_plane)
{
	// Reloading on spawn.
	_time_since_last_shot = 0;
}

void SimplePlaneBehaviour::Behave(float deltaT)
{
	_owner->StopPlane();
	// Or move at player.
	_owner->MovePlane(Vec2(.0f, -1.0f));

	_time_since_last_shot -= deltaT;
	if (_time_since_last_shot <= 0)
	{
		_owner->Shoot();
		_time_since_last_shot = DefaultValues::kDefaultShootCooldown;
	}

}
