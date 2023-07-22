#include "PhysXCollider.h"
#include "GameObj.h"
#include "PhysicsMgr.h"
#include "MeshRenderer.h"



PhysXCollider::PhysXCollider()
	: Component(eComponentType::Collider)
	, mCallback(nullptr)
	, mPhysical(nullptr)
	, mRaycastHit{}
	, mSweepHit	 {}
	, mOverlapHit{}
	, mFilterData{}

{
}
PhysXCollider::~PhysXCollider()
{
}
void PhysXCollider::Initialize()
{

	mFilterData.word0 = 1 << static_cast<unsigned __int32>(GetOwner()->GetLayerType()); // 충돌 레이어 정해주는듯

	// 렌더링할 물체의 모양을 가진 콜라이더
	mPhysical = GetOwner()->GetComponent<Physical>();

	if (mPhysical)
	{
		createDebugGeometry(mPhysical->GetGeometries());
		mPhysical->GetShape()->setSimulationFilterData(mFilterData);
	}
	//mCallback = PhysicsMgr::GetInstance()->GetDispatcher()->GetSimulationCallback();
}
void PhysXCollider::Update()
{
	if (mPhysical)
	{
		mPhysical->GetShape()->setSimulationFilterData(mFilterData);
	}
}
void PhysXCollider::FixedUpdate()
{
}
void PhysXCollider::Render()
{
}
void PhysXCollider::OnCollisionEnter(PhysXCollider* otherCollider)
{
	GetOwner()->OnCollisionEnter(otherCollider->GetOwner());
}
void PhysXCollider::OnCollisionExit(PhysXCollider* otherCollider)
{
}

void PhysXCollider::OnTriggerEnter(PhysXCollider* otherCollider)
{
	GetOwner()->OnTriggerEnter(otherCollider->GetOwner());
}
void PhysXCollider::OnTriggerStay(PhysXCollider* otherCollider)
{
}
void PhysXCollider::OnTriggerExit(PhysXCollider* otherCollider)
{
	GetOwner()->OnTriggerExit(otherCollider->GetOwner());
}

void PhysXCollider::createDebugGeometry(std::shared_ptr<Geometry> geometries)
{
	switch (geometries->eGeomType)
	{
	case eGeometryType::Box:
	{
		const PxBoxGeometry& boxGeom = static_cast<const PxBoxGeometry&>(geometries->boxGeom);
		Vector3 HalfSize = convert::PxVec3ToVector3(boxGeom.halfExtents);
		createDebugBox(HalfSize);
	}
	break;

	case eGeometryType::Capsule:
	{
		const PxCapsuleGeometry& capsuleGeom = static_cast<const PxCapsuleGeometry&>(geometries->capsuleGeom);
		float Radius = capsuleGeom.radius;
		float HalfHeight = capsuleGeom.halfHeight;
		createDebugCapsule(Radius, HalfHeight);
	}
	break;

	case eGeometryType::Sphere:
	{
		const PxSphereGeometry& sphereGeom = static_cast<const PxSphereGeometry&>(geometries->sphereGeom);
		float Radius = sphereGeom.radius;
		createDebugSphere(Radius);
	}
	break;

	case eGeometryType::Plane:
		break;
	}
}
void PhysXCollider::createDebugBox(math::Vector3 halfSize)
{		
	if (!GetOwner()->GetComponent<MeshRenderer>()->GetMesh())
	{
		Mesh* mesh = GETSINGLE(ResourceMgr)->Find<Mesh>(L"Cubemesh");
		GetOwner()->GetComponent<MeshRenderer>()->SetMesh(mesh);
	}

	if (!GetOwner()->GetComponent<MeshRenderer>()->GetMaterial())
	{
		Material* material = GETSINGLE(ResourceMgr)->Find<Material>(L"DebugGeometryMaterial");
		GetOwner()->GetComponent<MeshRenderer>()->SetMaterial(material);
	}

}
void PhysXCollider::createDebugCapsule(float radius, float halfHeight)
{
	//auto [vVertices, vIndices] = Vertex::CreateHemisphereVerticesAndIndices(radius, halfHeight);
	//shared_ptr<GUIMesh> pMesh = make_shared<GUIMesh>();
	//pMesh->Initialize(vVertices, vIndices);
	//shared_ptr<GUIMaterial> pMaterial = GET_SINGLE(Resources)->Get<GUIMaterial>(L"DebugGeometry");

	//GetDebugRenderer()->SetMaterial(pMaterial);
	//GetDebugRenderer()->SetMesh(pMesh);	
}
void PhysXCollider::createDebugSphere(float radius)
{
	if (!GetOwner()->GetComponent<MeshRenderer>()->GetMesh())
	{
		Mesh* mesh = GETSINGLE(ResourceMgr)->Find<Mesh>(L"Spheremesh");
		GetOwner()->GetComponent<MeshRenderer>()->SetMesh(mesh);
	}

	if (!GetOwner()->GetComponent<MeshRenderer>()->GetMaterial())
	{
		Material* material = GETSINGLE(ResourceMgr)->Find<Material>(L"DebugGeometryMaterial");
		GetOwner()->GetComponent<MeshRenderer>()->SetMaterial(material);
	}
}