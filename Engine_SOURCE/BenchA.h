#pragma once
#include "GameObj.h"

class BenchA : public GameObj
{
public:
	BenchA();
	BenchA(const BenchA& Obj);
	virtual ~BenchA();

	virtual BenchA* Clone() const;
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void FixedUpdate() override;

public:
	virtual void OnCollisionEnter(GameObj* gameObject) override;
	virtual void OnTriggerEnter(GameObj* gameObject) override;
	virtual void OnTriggerPersist(GameObj* gameObject) override;
	virtual void OnTriggerExit(GameObj* gameObject) override;
};