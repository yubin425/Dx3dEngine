#include "BaseRenderer.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObj.h"
#include "Material.h"
#include "Mesh.h"


BaseRenderer::BaseRenderer(eComponentType type)
	:Component(type)
	, mbIsAnim(false)
	, mbUseLOD(false)
	, mSpriteSize(Vector2::Zero)
	, mMesh (nullptr)
	, mModel (nullptr)
	, mMaterial (nullptr)
{
	// 디폴트 매시 지정
	Mesh* mesh = GETSINGLE(ResourceMgr)->Find<Mesh>(L"Cubemesh");

	SetMesh(mesh);
}
BaseRenderer::~BaseRenderer()
{
}
void BaseRenderer::Initialize()
{
}
void BaseRenderer::Update()
{
}
void BaseRenderer::FixedUpdate()
{

}

void BaseRenderer::Render()
{
	if (mbUseLOD)
	{
		//LOD();
	}
}

void BaseRenderer::SetMeshByKey(std::wstring key)
{
	mMesh = GETSINGLE(ResourceMgr)->Find<Mesh>(key);
}

void BaseRenderer::SetMaterial(Material* material, UINT modelMeshSlot)
{
	if (mModel)
	{
		mModel->SetVariableMaterials(modelMeshSlot, material);
	}
	else
	{
		mMaterial = material;
	}
}

void BaseRenderer::SetMaterialByKey(std::wstring key, UINT modelMeshSlot)
{
	if (mModel)
	{
		mModel->SetVariableMaterialsByKey(modelMeshSlot, key);
		mMaterial = GETSINGLE(ResourceMgr)->Find<Material>(key);
	}
	else
	{
		mMaterial = GETSINGLE(ResourceMgr)->Find<Material>(key);
	}
}

void BaseRenderer::SetAnimMaterial(Material* material, Vector2 spriteSize)
{
	mMaterial = material;
	mbIsAnim = true;
	mSpriteSize = spriteSize;
}

void BaseRenderer::SetModelByKey(std::wstring key)
{
	mModel = GETSINGLE(ResourceMgr)->Find<Model>(key);
}

void BaseRenderer::SetModelByKey(std::wstring modelKey, std::wstring materialKey)
{
	mModel = GETSINGLE(ResourceMgr)->Find<Model>(modelKey);
	mMaterial = GETSINGLE(ResourceMgr)->Find<Material>(materialKey);
}


void BaseRenderer::ChangeColor(Vector4 color)
{
	MulColor(Vector4::Zero);
	AddColor(color);
}

void BaseRenderer::MulColor(Vector4 color)
{
	mMaterial->SetData(eGPUParam::Vector4_1, &color);
}

void BaseRenderer::AddColor(Vector4 color)
{
	mMaterial->SetData(eGPUParam::Vector4_2, &color);
}

void BaseRenderer::LOD()
{
	Vector3 camPos = renderer::mainCamera->GetOwnerWorldPos();
	Vector3 objPos = GetOwnerWorldPos();

	float distance = Vector3::Distance(camPos, objPos);

	if (mMaterial)
	{
		if (distance > 200.f)
		{
			mMaterial->SetShaderByKey(L"FlatShader");
		}
		else
		{
			mMaterial->SetShaderByKey(L"PhongShader");
		}
	}
}
