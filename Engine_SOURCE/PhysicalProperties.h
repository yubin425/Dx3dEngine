#pragma once
#include "Entity.h"

struct MassProperties
{
    // 정적마찰 (움직이기 전의 마찰:막 움직이기 시작할때 마찰계수                // 물체 충돌 전 후 속도 비율
    MassProperties(float staticFriction = 0.5f, float dynamicFriction = 0.2f, float restitution = 0.603f)
        : mStaticFriction(staticFriction)
        , mDynamicFriction(dynamicFriction)
        , mRestitution(restitution)
    { }

    float mStaticFriction;
    float mDynamicFriction;
    float mRestitution;
};

class PhysicalProperties : public dru::Entity
{
public:
    PhysicalProperties(const MassProperties& massProperties);
    ~PhysicalProperties();

    void ApplyToShape(PxShape& shape);
    void SetMaterialFlag(PxMaterialFlags flag) { mMaterial->setFlags(flag); }

public:
    PxMaterial* GetMaterial()   const { return mMaterial; }

    float GetStaticFriction()   const { return mStaticFriction; }
    float GetDynamicFriction()  const { return mDynamicFriction; }
    float GetRestitution()      const { return mRestitution; }

    void SetStaticFriction(float friction);
    void SetDynamicFriction(float friction);
    void SetRestitution(float restitution);

private:
    float mStaticFriction;
    float mDynamicFriction;
    float mRestitution;

private:
    PxMaterial* mMaterial;
};