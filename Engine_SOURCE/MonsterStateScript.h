#pragma once
#include "Script.h"
#include "BoneAnimator.h"

class Monster;
class MonsterStateScript : public Script
{
public:
	MonsterStateScript();
	virtual ~MonsterStateScript();

	virtual void Update() override;
	virtual void Initialize() override;
public:
	virtual void Idle() {};
	virtual void Move() {};
	virtual void Jump() {};
	virtual void SpecialCast() {};
	virtual void Hit() {};
	virtual void Groggy() {};
	virtual void Die() {};

private:
	std::vector<std::function<void()>> mStateEventList;

protected:
	Monster* mMonster;
};

