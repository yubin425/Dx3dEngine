#pragma once
#include "GameObj.h"

class MeshRenderer;
class FenceA : public GameObj
{
public:
	FenceA();
	FenceA(const FenceA& Obj);
	virtual ~FenceA();


	virtual FenceA* Clone() const;
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;

public:
	virtual void OnCollisionEnter(GameObj* gameObject) override;
	virtual void OnTriggerEnter(GameObj* gameObject) override;
	virtual void OnTriggerPersist(GameObj* gameObject) override;
	virtual void OnTriggerExit(GameObj* gameObject) override;

private:
};