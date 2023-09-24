#include "Monster.h"
#include "MonsterAiScript.h"
#include "MonsterStateScript.h"
#include "BoneAnimator.h"

Monster::Monster()
	: DynamicObject()
	, mMonsterState(eMonsterState::Idle)
	, mRecognizeRadius(10.f)
	, mFoundPlayer(false)
{
	//StateInfoSetting
	mStateInfo.resize(static_cast<int>(eMonsterState::Die) + 1);

	// 캡처 클래스의 자신의 포인터전달
	CaptureObj::SetObject(this);
}

Monster::~Monster()
{
}

void Monster::Initialize()
{
	// Animator
	BoneAnimator* animator = AddComponent<BoneAnimator>(eComponentType::BoneAnimator);
	if (animator != nullptr)
	{
		boneAnimatorInit(animator);
	}

	// OffsetScale Setting
	Transform* tr = GetComponent<Transform>();
	if (tr)
		tr->SetOffsetScale(0.01f);

	GameObj::Initialize();
}

void Monster::Update()
{
	CaptureObj::Update();
	GameObj::Update();
}

void Monster::FixedUpdate()
{
	GameObj::FixedUpdate();
}

void Monster::SetMonsterState(eMonsterState monsterState)
{
	std::set<UINT>::iterator iter;
	iter = mStateInfo[static_cast<UINT>(mMonsterState)].mLockState.find(static_cast<UINT>(monsterState));
	if (iter != mStateInfo[static_cast<UINT>(mMonsterState)].mLockState.end())
		return;

	mMonsterState = monsterState;

	MonsterStateScript* script = GetScript<MonsterStateScript>();
	if (script)
		script->Reset();
}
