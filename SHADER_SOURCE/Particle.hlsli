#include "Quaternion.hlsl"

struct Particle
{
    float4 position;
    float4 direction;
    float4 startColor;
    float4 endColor;

    float3 startScale;
    float3 endScale;
    
    float lifeTime;
    float elapsedTime;
    float speed;
    float2 gravityAcc;
    float radian;
    uint active;
    
    matrix particleWorld;
};


struct ParticleShared
{
    uint gActiveCount;
};

StructuredBuffer<Particle> particleBuffer : register(t16);
RWStructuredBuffer<Particle> ParticleBufferUAV : register(u0);
RWStructuredBuffer<ParticleShared> ParticleSharedBufferUAV : register(u1);
