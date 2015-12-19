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
    if (_player_plane->GetCurrentHP() > 0) {
	return (_player_plane->getPosition() - _owner->getPosition());
    } else {
        return Vec2(0, -1);
    }
    
}

float AbstractPlaneBehavoiur::angleToPlayer()
{
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

KamikazePlaneBehaviour::KamikazePlaneBehaviour(DefaultPlane* owner, DefaultPlane* player_plane) : AbstractPlaneBehavoiur(owner, player_plane)
{
    _owner->setMaximumSpeed(110);
    _owner->ApplyDamage(40);
	_already_fled_past_player = false;
}

void KamikazePlaneBehaviour::Behave(float deltaT)
{
	_owner->StopPlane();
	if (!_already_fled_past_player)
	{
		// Or move at player.
		_owner->MovePlane(directionToPlayer());

		if (_owner->getPosition().y < _player_plane->getPosition().y)
			_already_fled_past_player = true;
	}
	else
	{
		_owner->MovePlane(Vec2(.0f, -1.0f));
	}
    
    
    
}

