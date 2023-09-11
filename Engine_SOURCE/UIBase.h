#pragma once
//#include "Entity.h"
#include "GameObj.h"

using namespace math;
class UIBase : public GameObj
{
public:
	struct Event
	{
		void operator=(std::function<void()> func)
		{
			mEvent = std::move(func);
		}

		void operator()()
		{
			if (mEvent)
				mEvent();
		}


		std::function<void()> mEvent;
	};


	UIBase(eUIType type);
	virtual ~UIBase();

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Render() override;
	void FontRender() override;


	// UI�� Ȱ��ȭ�Ǹ� �Ҹ��� �Լ�
	void Activate();
	// UI�� ��Ȱ��ȭ�Ǹ� �Ҹ��� �Լ�
	void InActivate();
	//UI�� ������� ȣ��Ǵ� �Լ�
	void UIClear();

	eUIType GetUIType() { return mUIType; }
	bool GetIsFullScreen() { return mUIbFullScreen; }
	void SetIsFullScreen(bool enable) { mUIbFullScreen = enable; }
	void SetUIParent(UIBase* parent) { mUIParent = parent; }

	Vector3 GetUIScreenPos() { return mUIScreenPos; }
	Vector3 GetUIPos() { return mUIPos; }
	Vector3 GetUISize() { return mUISize; }
	void SetUIScreenPos(Vector3 pos) { mUIScreenPos = pos; }
	void SetUIPos(Vector3 pos) { mUIPos = pos; }
	void SetUISize(Vector3 size) { mUISize = size; }
	void Addchild(UIBase* uiBase);

protected:
	UIBase* mUIParent;
	Vector3 mUIScreenPos;
	Vector3 mUIPos;
	Vector3 mUISize;


private:
	virtual void OnInit() {};
	virtual void OnActive() {};
	virtual void OnInActive() {};
	virtual void OnUpdate() {};
	virtual void OnFixedUpdate() {};
	virtual void OnRender() {};
	virtual void OnFontRender() {};
	virtual void OnClear() {};

private:
	eUIType mUIType;
	bool mUIbFullScreen;
	bool mbUIEnable;

	//���Ͱ� �� �޸� ģȭ���̱� ������ ���
	std::vector<UIBase*> mChilds;
};