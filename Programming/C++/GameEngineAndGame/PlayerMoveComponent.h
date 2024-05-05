#pragma once

#include "IComponent.h"

class PlayerMoveComponent : public IComponent
{
public:
	using ptr = std::shared_ptr<PlayerMoveComponent>;

	PlayerMoveComponent(GameObject& gameObject, int playerIndex);

	bool init() override;
	void update(float delta_time) override;

private:
	int mPlayerIndex;
};
