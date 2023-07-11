#pragma once
#include "Engine.h"


class PxInitialization
{
public:
	PxInitialization();
	~PxInitialization();

public:
	PxFoundation* GetFoundation() { return mFoundation; }
	PxPhysics* GetPhysics() { return mPhysics; }

	void	CreateFoundation();
	void	CreatePhysics();

	PxDefaultAllocator& GetAllocator() { return mAllocCallback; }
	PxDefaultErrorCallback& GetErrorCallback() { return mErrorCallback; }

private:
	PxDefaultAllocator		mAllocCallback; // ������ �޸� �Ҵ� �� ���� ���� (���� �ǵ��ʿ����)
	PxDefaultErrorCallback  mErrorCallback; // ���� �� ��� �޽��� ó��
	PxFoundation* mFoundation; // ������ �ý��� �⺻���� �ʱ�ȭ �� ���� ����
	PxPhysics* mPhysics; // �������� ��ü���� ����� ������ �ִ� Ŭ����
};


