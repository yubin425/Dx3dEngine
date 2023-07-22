#include "Material.h"


Material::Material()
	:Resource(eResourceType::Material)
	, mMode(eRenderingMode::Transparent)
	, mConstantBuffer{}

{
}
Material::Material(std::wstring textureColor, std::wstring shaderName)
	: Resource(eResourceType::Material)
	, mMode(eRenderingMode::Transparent)
{

	mTexture[static_cast<UINT>(eTextureSlot::T0)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureColor);
	mShader = GETSINGLE(ResourceMgr)->Find<Shader>(shaderName);
	mConstantBuffer.xyzw1 = Vector4{ 1.f, 1.f, 1.f, 1.f };
}
Material::Material(std::wstring textureColor, std::wstring textureNormal, std::wstring shaderName)
	: Resource(eResourceType::Material)
	, mMode(eRenderingMode::Transparent)
{

	mTexture[static_cast<UINT>(eTextureSlot::T0)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureColor);
	mTexture[static_cast<UINT>(eTextureSlot::T1)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureNormal);
	mShader = GETSINGLE(ResourceMgr)->Find<Shader>(shaderName);
	mConstantBuffer.xyzw1 = Vector4{ 1.f, 1.f, 1.f, 1.f };
}

Material::Material(std::wstring textureColor, std::wstring textureNormal, std::wstring textureEmissive, std::wstring shaderName)
	: Resource(eResourceType::Material)
	, mMode(eRenderingMode::Transparent)
{

	mTexture[static_cast<UINT>(eTextureSlot::T0)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureColor);
	mTexture[static_cast<UINT>(eTextureSlot::T1)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureNormal);
	mTexture[static_cast<UINT>(eTextureSlot::T2)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureEmissive);
	mShader = GETSINGLE(ResourceMgr)->Find<Shader>(shaderName);
	mConstantBuffer.xyzw1 = Vector4{ 1.f, 1.f, 1.f, 1.f };
}

Material::Material(std::wstring textureColor, std::wstring textureNormal, std::wstring textureEmissive, std::wstring textureMetal, std::wstring shaderName)
	: Resource(eResourceType::Material)
	, mMode(eRenderingMode::Transparent)
{

	mTexture[static_cast<UINT>(eTextureSlot::T0)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureColor);
	mTexture[static_cast<UINT>(eTextureSlot::T1)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureNormal);
	mTexture[static_cast<UINT>(eTextureSlot::T2)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureEmissive);
	mTexture[static_cast<UINT>(eTextureSlot::T3)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureMetal);
	mShader = GETSINGLE(ResourceMgr)->Find<Shader>(shaderName);
	mConstantBuffer.xyzw1 = Vector4{ 1.f, 1.f, 1.f, 1.f };
}

Material::Material(std::wstring textureColor, std::wstring textureNormal, std::wstring textureEmissive, std::wstring textureMetal, std::wstring textureRoughness, std::wstring shaderName)
	: Resource(eResourceType::Material)
	, mMode(eRenderingMode::Transparent)
{

	mTexture[static_cast<UINT>(eTextureSlot::T0)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureColor);
	mTexture[static_cast<UINT>(eTextureSlot::T1)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureNormal);
	mTexture[static_cast<UINT>(eTextureSlot::T2)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureEmissive);
	mTexture[static_cast<UINT>(eTextureSlot::T3)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureMetal);
	mTexture[static_cast<UINT>(eTextureSlot::T4)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureRoughness);

	mShader = GETSINGLE(ResourceMgr)->Find<Shader>(shaderName);
	mConstantBuffer.xyzw1 = Vector4{ 1.f, 1.f, 1.f, 1.f };
}



Material::Material(std::wstring textureName, eTextureSlot slot, std::wstring shaderName)
	: Resource(eResourceType::Material)
	, mMode(eRenderingMode::Transparent)
{
	mTexture[static_cast<UINT>(slot)] = GETSINGLE(ResourceMgr)->Find<Texture>(textureName);
	mShader = GETSINGLE(ResourceMgr)->Find<Shader>(shaderName);
	mConstantBuffer.xyzw1 = Vector4{ 1.f, 1.f, 1.f, 1.f };
	mConstantBuffer.xyzw2 = Vector4{ 0.f, 0.f, 0.f, 0.f };
}
Material::~Material()
{
}
HRESULT Material::Load(const std::wstring& path)
{
	return E_NOTIMPL;
}
void Material::SetData(eGPUParam param, void* data)
{
	switch (param)
	{
	case eGPUParam::Int_1:
		mConstantBuffer.iData1 = *static_cast<int*>(data);
		break;
	case eGPUParam::Int_2:
		mConstantBuffer.iData2 = *static_cast<int*>(data);
		break;
	case eGPUParam::Int_3:
		mConstantBuffer.iData3 = *static_cast<int*>(data);
		break;
	case eGPUParam::Int_4:
		mConstantBuffer.iData4 = *static_cast<int*>(data);
		break;
	case eGPUParam::Float_1:
		mConstantBuffer.fData1 = *static_cast<float*>(data);
		break;
	case eGPUParam::Float_2:
		mConstantBuffer.fData2 = *static_cast<float*>(data);
		break;
	case eGPUParam::Float_3:
		mConstantBuffer.fData3 = *static_cast<float*>(data);
		break;
	case eGPUParam::Float_4:
		mConstantBuffer.fData4 = *static_cast<float*>(data);
		break;
	case eGPUParam::Vector2_1:
		mConstantBuffer.xy1 = *static_cast<Vector2*>(data);
		break;
	case eGPUParam::Vector2_2:
		mConstantBuffer.xy2 = *static_cast<Vector2*>(data);
		break;
	case eGPUParam::Vector2_3:
		mConstantBuffer.xy3 = *static_cast<Vector2*>(data);
		break;
	case eGPUParam::Vector2_4:
		mConstantBuffer.xy4 = *static_cast<Vector2*>(data);
		break;
	case eGPUParam::Vector3_1:
		mConstantBuffer.xyz1 = *static_cast<Vector3*>(data);
		break;
	case eGPUParam::Vector3_2:
		mConstantBuffer.xyz2 = *static_cast<Vector3*>(data);
		break;
	case eGPUParam::Vector3_3:
		mConstantBuffer.xyz3 = *static_cast<Vector3*>(data);
		break;
	case eGPUParam::Vector3_4:
		mConstantBuffer.xyz4 = *static_cast<Vector3*>(data);
		break;
	case eGPUParam::Vector4_1:
		mConstantBuffer.xyzw1 = *static_cast<Vector4*>(data);
		break;
	case eGPUParam::Vector4_2:
		mConstantBuffer.xyzw2 = *static_cast<Vector4*>(data);
		break;
	case eGPUParam::Vector4_3:
		mConstantBuffer.xyzw3 = *static_cast<Vector4*>(data);
		break;
	case eGPUParam::Vector4_4:
		mConstantBuffer.xyzw4 = *static_cast<Vector4*>(data);
		break;
	case eGPUParam::Matrix_1:
		mConstantBuffer.matrix1 = *static_cast<Matrix*>(data);
		break;
	case eGPUParam::Matrix_2:
		mConstantBuffer.matrix2 = *static_cast<Matrix*>(data);
		break;
	case eGPUParam::Matrix_3:
		mConstantBuffer.matrix3 = *static_cast<Matrix*>(data);
		break;
	case eGPUParam::Matrix_4:
		mConstantBuffer.matrix4 = *static_cast<Matrix*>(data);
		break;
	case eGPUParam::TextureExistence:
		mConstantBuffer.textureExistence = *static_cast<int*>(data);
		break;
	case eGPUParam::Bool_1:
		mConstantBuffer.bool1 = *static_cast<int*>(data);
		break;
	case eGPUParam::Bool_2:
		mConstantBuffer.bool2 = *static_cast<int*>(data);
		break;
	case eGPUParam::Bool_3:
		mConstantBuffer.bool3 = *static_cast<int*>(data);
		break;
	default:
		break;
	}

}
void Material::Bind()
{
	for (UINT i = 0; i < static_cast<UINT>(eTextureSlot::End); i++)
	{
		if (mTexture[i] == nullptr)
			continue;

		mTexture[i]->BindShaderResource(eShaderStage::VS, i);
		mTexture[i]->BindShaderResource(eShaderStage::HS, i);
		mTexture[i]->BindShaderResource(eShaderStage::DS, i);
		mTexture[i]->BindShaderResource(eShaderStage::GS, i);
		mTexture[i]->BindShaderResource(eShaderStage::PS, i);
		mTexture[i]->BindShaderResource(eShaderStage::CS, i);
	}
	ConstantBuffer* pCB = renderer::constantBuffers[static_cast<UINT>(eCBType::Material)];

	// 텍스처 개수
	mConstantBuffer.textureExistence = 0;

	if (mTexture[0]) // color가 있습니다.
	{
		++mConstantBuffer.textureExistence;
	}
	if (mTexture[1]) // normal이 있습니다.
	{
		++mConstantBuffer.textureExistence;
	}
	if (mTexture[2]) // Emissive가 있습니다.
	{
		++mConstantBuffer.textureExistence;
	}
	if (mTexture[3]) // Metal가 있습니다.
	{
		++mConstantBuffer.textureExistence;
	}
	if (mTexture[4]) // Roughness가 있습니다.
	{
		++mConstantBuffer.textureExistence;
	}


	pCB->SetData(&mConstantBuffer);
	pCB->Bind(eShaderStage::VS);
	pCB->Bind(eShaderStage::GS);
	pCB->Bind(eShaderStage::PS);

	mShader->Bind();
}
void Material::Clear()
{
	for (size_t i = 0; i < static_cast<UINT>(eTextureSlot::End); i++)
	{
		if (mTexture[i] == nullptr)
			continue;

		mTexture[i]->Clear();
	}

	ConstantBuffer* pCB = renderer::constantBuffers[static_cast<UINT>(eCBType::Material)];
	pCB->Clear();

}
void Material::SetShaderByKey(std::wstring key)
{
	Shader* shader = GETSINGLE(ResourceMgr)->Find<Shader>(key);
	mShader = shader;
}

