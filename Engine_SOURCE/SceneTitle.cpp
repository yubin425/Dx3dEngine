#include "SceneTitle.h"
#include "TimeMgr.h"

#include "Object.h"
#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "SpriteRenderer.h"
#include "Renderer.h"
#include "Texture.h"
#include "Camera.h"
#include "CameraScript.h"
#include "FontWrapper.h"

#include "GridScript.h"

#include "Application.h"
#include "Player.h"

#include "Physical.h"
#include "PhysXRigidBody.h"
#include "PhysXCollider.h"
#include "PlayerScript.h"
#include "PhysicalMovement.h"
#include "PhysicsMgr.h"
#include "PhysicsScene.h"
#include "PhysX.h"

#include "Sphere.h"
#include "Box.h"

#include "ServerMgr.h"

#include "InputMgr.h"

extern Application application;


SceneTitle::SceneTitle()
	:  mCamera(nullptr)

{
}

SceneTitle::~SceneTitle()
{

}

void SceneTitle::Initialize()
{
	GETSINGLE(PhysXCollisionMgr)->SetCollisionGroup(eLayerType::Platforms, eLayerType::Player);
		
	Scene::Initialize();
}

void SceneTitle::update()
{
	if (KEY_TAP(N_9))
	{
		GETSINGLE(server::ServerMgr)->OpenServer();
	}
	if (KEY_TAP(N_0))
	{
		GETSINGLE(server::ServerMgr)->ConnectAsClient();
	}

	
	Scene::update();
}

void SceneTitle::fixedUpdate()
{
	Scene::fixedUpdate();
}

void SceneTitle::render()
{
		
}

void SceneTitle::Enter()
{
	//mDeleteObj = true;

	{
		mCamera = object::Instantiate<GameObj>(eLayerType::Camera, L"MainCam");
		Camera* cameraComp = mCamera->AddComponent<Camera>(eComponentType::Camera);
		cameraComp->TurnLayerMask(eLayerType::UI, false);
		cameraComp->SmoothOn();
		mCamera->AddComponent<CameraScript>(eComponentType::Script);
		renderer::mainCamera = cameraComp;
		cameraComp->SetProjectionType(eProjectionType::Perspective);
		mCamera->SetPos(Vector3(0.f, 15.f, 0.f));

	}


	{
		GameObj* gridObject = object::Instantiate<GameObj>(eLayerType::Grid, L"Grid");
		
		MeshRenderer* gridMr = gridObject->AddComponent<MeshRenderer>(eComponentType::MeshRenderer);

		gridMr->SetMesh(GETSINGLE(ResourceMgr)->Find<Mesh>(L"Gridmesh"));
		gridMr->SetMaterial(GETSINGLE(ResourceMgr)->Find<Material>(L"GridMaterial"));
		gridMr->LODOff();

		GridScript* gridScript = gridObject->AddComponent<GridScript>(eComponentType::Script);
		gridScript->SetCamera(mainCamera);

		float w = static_cast<float>(application.GetWidth());
		float h = static_cast<float>(application.GetHeight());
		gridObject->SetPos({ 0.f, 0.f, 0.f });
		gridObject->SetScale(Vector3(1.f, 1.f, 1.f));
	}
		
	{
		GameObj* directionalLight = object::Instantiate<GameObj>(eLayerType::None, this, L"DirectionalLightTitleScene");
		directionalLight->GetComponent<Transform>()->SetPosition(Vector3(0.f, 100.f, -50.f));
		directionalLight->SetRotation(Vector3(45.f, 0.f, 0.f));
		Light* lightComp = directionalLight->AddComponent<Light>(eComponentType::Light);
		lightComp->SetType(eLightType::Directional);
		lightComp->SetDiffuse(Vector4(1.f, 1.f, 1.f, 1.f));
		lightComp->SetSpecular(Vector4(1.f, 1.f, 1.f, 1.f));
		lightComp->SetAmbient(Vector4(0.5f, 0.5f, 0.5f, 1.f));
	}


	//{
	//	Player* player = object::Instantiate<Player>(eLayerType::Player);
	//	player->SetPos(Vector3(5.f, 5.f, 5.f));
	//	player->SetScale({ 5.f, 5.f, 5.f });
	//	player->SetName(L"Player");
	//	GUIMaterial* mat = GETSINGLE(ResourceMgr)->CreateMaterial(L"dirt_color", L"dirt_normal", L"PhongShader", L"mat_dirt");
	//	player->GetComponent<GUIMeshRenderer>()->SetMaterial(mat);
	//	//player->GetComponent<GUIMeshRenderer>()->SetMaterialByKey(L"PhongMaterial");
	//	player->GetComponent<GUIMeshRenderer>()->SetMeshByKey(L"Spheremesh");
	//	player->AddComponent<PlayerScript>(eComponentType::Script);

	//	Physical* physical = player->AddComponent<Physical>(eComponentType::Physical);
	//	physical->InitialDefaultProperties(eActorType::Dynamic, eGeometryType::Sphere, Vector3(2.5f, 2.5f, 2.5f));
	//	PxRigidDynamic* dy = physical->GetActor<PxRigidDynamic>();

	//	PhysXRigidBody* rigid = player->AddComponent<PhysXRigidBody>(eComponentType::RigidBody);

	//	player->AddComponent<PhysXCollider>(eComponentType::Collider);
	//	player->AddComponent<PhysicalMovement>(eComponentType::Movement);
	//}

	//{
	//	
	//	Sphere* sphere = object::Instantiate<Sphere>(eLayerType::PhysicalObject);
	//	sphere->SetPos(Vector3(-5.f, 20.f, 5.f));
	//	sphere->SetScale({ 2.5f, 2.5f, 2.5f });
	//	sphere->SetName(L"Sphere");
	//	sphere->GetComponent<GUIMeshRenderer>()->SetMaterialByKey(L"PhongMaterial");

	//}


	{
		GameObj* plane = object::Instantiate<GameObj>(eLayerType::Platforms);
		plane->SetPos(Vector3(0.f, -0.251f, 0.f));
		plane->SetScale({ 100.f, 0.5f, 100.f });
		plane->SetName(L"Plane");
		plane->AddComponent<MeshRenderer>(eComponentType::MeshRenderer)->SetMaterialByKey(L"PhongMaterial");
		plane->AddComponent<Physical>(eComponentType::Physical)->InitialDefaultProperties(eActorType::Static, eGeometryType::Box, Vector3(50.f, 0.25f, 50.f));

		PhysXRigidBody* rigid = plane->AddComponent<PhysXRigidBody>(eComponentType::RigidBody);

		plane->AddComponent<PhysXCollider>(eComponentType::Collider);
	}

	//0720 normal map Test
	{
		// Test Material Init
		{
			Shader* phongShader = GETSINGLE(ResourceMgr)->Find<Shader>(L"PhongShader");
			Material* testCubeMaterial = new Material();
			testCubeMaterial->SetRenderingMode(eRenderingMode::Transparent);
			testCubeMaterial->SetShader(phongShader);
			GETSINGLE(ResourceMgr)->Insert<Material>(L"TestCubeMaterial", testCubeMaterial);
		}


		GameObj* player = object::Instantiate<GameObj>(eLayerType::Player);
		player->SetPos(Vector3(0.f, 5.f, 0.f));
		player->SetScale({ 1.f, 1.f, 1.f });
		//player->GetComponent<Transform>()->SetRotation(Vector3(15.0f, 45.0f, 0.0f));
		player->SetName(L"Player");

		MeshRenderer* meshRenderer = player->AddComponent<MeshRenderer>(eComponentType::MeshRenderer);
		meshRenderer->SetMesh(GETSINGLE(ResourceMgr)->Find<Mesh>(L"Cubemesh"));

		Material* material = GETSINGLE(ResourceMgr)->Find<Material>(L"TestCubeMaterial");
		material->SetTexture(eTextureSlot::T0, GETSINGLE(ResourceMgr)->Find<Texture>(L"dirt_color"));
		material->SetTexture(eTextureSlot::T1, GETSINGLE(ResourceMgr)->Find<Texture>(L"dirt_normal"));

		meshRenderer->SetMaterialByKey(L"TestCubeMaterial");
	}

	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();
}
