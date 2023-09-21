#include "PhysX.h"
#include "PhysicsScene.h"


PhysX::PhysX()
	:mPhysicsScene(nullptr)
	, mInitialization(nullptr)
	, mTransport (nullptr)
	, mSceneClient (nullptr)
	, mScene(nullptr)
	, mControllerMgr(nullptr)

{
	mInitialization = std::make_shared<PxInitialization>();
}
PhysX::~PhysX()
{
	if (mControllerMgr)
		mControllerMgr->release();

	if (mScene)
		mScene->release();
}

void PhysX::Init()
{
	mInitialization->CreateFoundation();
	mInitialization->CreateCooking();
	mInitialization->CreateVisualDebugger();
	mInitialization->ConntectVisualDebugger();
	mInitialization->CreatePhysics();
//	CreateSceneQuery();
}

PxConvexMesh* PhysX::CreateConvexMesh(const PxVec3* verts, const PxU32 numVerts, PxPhysics* physics, PxCooking* cooking)
{
	// Create descriptor for convex mesh
	physx::PxConvexMeshDesc convexDesc;
	convexDesc.points.count = numVerts;
	convexDesc.points.stride = sizeof(physx::PxVec3);
	convexDesc.points.data = verts;
	convexDesc.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX | PxConvexFlag::eSHIFT_VERTICES;

	physx::PxConvexMesh* convexMesh = NULL;
	physx::PxDefaultMemoryOutputStream buf;
	if (cooking->cookConvexMesh(convexDesc, buf))
	{
		physx::PxDefaultMemoryInputData id(buf.getData(), buf.getSize());
		convexMesh = physics->createConvexMesh(id);
	}

	return convexMesh;
}

PxTriangleMesh* PhysX::CreateTriangleMesh(const PxVec3* verts, const PxU32 numVerts
	, const PxU32* indexs, const PxU32 numIndexes, PxPhysics* physics, PxCooking* cooking)
{
	// Create descriptor for triangle mesh
	PxTriangleMeshDesc meshDesc;
	meshDesc.points.count = numVerts;
	meshDesc.points.stride = sizeof(PxVec3);
	meshDesc.points.data = verts;

	meshDesc.triangles.count = numIndexes / 3;
	meshDesc.triangles.stride = 3 * sizeof(PxU32);
	meshDesc.triangles.data = indexs;

	PxDefaultMemoryOutputStream writeBuffer;
	bool status = cooking->cookTriangleMesh(meshDesc, writeBuffer);
	if (!status)
		return nullptr; 

	PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
	PxTriangleMesh* triangleMesh = physics->createTriangleMesh(readBuffer);

	return triangleMesh;
}

void PhysX::CreatePhysicsScene(const PxSceneDesc& sceneDesc)
{
	assert(mInitialization->GetPhysics());
	CreateScene(sceneDesc);
	CreateControllerManager();

	mPhysicsScene = std::make_shared<PhysicsScene>(mScene);
}

void PhysX::CreateScene(const PxSceneDesc& sceneDesc)
{
	mScene = mInitialization->GetPhysics()->createScene(sceneDesc);
	assert(mScene);
}

void PhysX::CreateControllerManager()
{
	mControllerMgr = PxCreateControllerManager(*mScene);
	assert(mControllerMgr);
}

void PhysX::ConnectDebuggerToScene()
{
	mSceneClient = mScene->getScenePvdClient();
	assert(mSceneClient);

	mSceneClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
	mSceneClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
	mSceneClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);

}

