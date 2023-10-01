#include "global.hlsli"

struct VSOut
{
    float4 Position : SV_Position;
    float2 UV : TEXCOORD;
    float3 WorldPos : POSITION; // Worldspace fragmentPos

    float3 WorldTangent : TANGENT; // World Space tangent
    float3 WorldNormal : NORMAL; // World Space normal
};

float4 main(VSOut vsIn) : SV_Target
{
    float3 outColor = (float3) 0.f;

    float3 directLighting = (float3) 0.f;
    float3 ambientLighting = (float3) 0.f;
    
    float4  albedo = float4(0.25f, 0.25f, 0.25f, 1.f);
    float3  normal = vsIn.WorldNormal;
    float   metallic = 0.f; 
    float   roughness = 0.f;
    float3  emission = (float3) 0.f;
    float3  A0 = (float3) 1.f;

    float pixelToCam = distance(cameraWorldPos.xyz, vsIn.WorldPos);

    albedo = cbbAlbedo ? TextureMapping_albedo(vsIn.UV, pixelToCam) : albedo;
    normal = cbbNormal ? TextureMapping_normal(vsIn.UV, vsIn.WorldTangent, vsIn.WorldNormal, pixelToCam) : normal;
    metallic = cbbMetallic ? TextureMapping_metallic(vsIn.UV, pixelToCam) : cbbMetallic;
    roughness = cbbRoughness ? TextureMapping_roughness(vsIn.UV, pixelToCam) : cbbRoughness;
    emission = cbbEmissive ? TextureMapping_emissive(vsIn.UV, pixelToCam) : emission;
    
    float3 pixelToEye = normalize(cameraWorldPos.xyz - vsIn.WorldPos);
    ambientLighting = AmbientLightingByIBL(albedo.xyz, normal, pixelToEye, metallic, roughness, pixelToCam);
    
    // 빛 타입에 따라 다르게 적용되도록해야함 현재는 dir light만 적용중
    
    for (int i = 0; i < lightCount; ++i)
    {
        float3 lightVec = lightAttributes[i].type == LIGHT_DIRECTIONAL 
        ? -lightAttributes[i].direction.xyz
        : mul(lightAttributes[i].position, world) - worldPosition;
        
        float lightDist = length(lightVec);
        lightVec /= lightDist;

        // Spot light
        float spotFator = lightAttributes[i].type == LIGHT_SPOT
                      ? pow(max(-dot(lightVec, lightAttributes[i].direction.xyz), 0.0f), lightAttributes[i].spotPower)
                      : 1.0f;
        
        // Distance attenuation
        float att = lightAttributes[i].type == LIGHT_DIRECTIONAL
        ? 1.f
        : saturate((lightAttributes[i].fallOffEnd - lightDist)
                         / (lightAttributes[i].fallOffEnd - lightAttributes[i].fallOffStart));

        
        float3 radiance = lightAttributes[i].color.diffuse * spotFator * att; // * shadowFactor;

        
        directLighting += PBR_DirectLighting(pixelToEye, lightVec, albedo.xyz, normal.xyz, metallic, roughness) * radiance;
            
        
    }

    
    //outColor.xyz = CalculateLightPBR_Direct(vsIn.WorldPos, albedo, normal, metallic, roughness);
    //outColor.xyz = DiffuseIBL(albedo.xyz, normal, pixelToEye, metallic);
    //outColor.xyz = SpecularIBL(albedo.xyz, normal, pixelToEye, metallic, roughness);
    //outColor.xyz = directLighting;
    outColor.xyz = ambientLighting + directLighting + emission;

    
    return float4(outColor.xyz, 1.f);;

}
