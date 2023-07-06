#include "Fmod.h"
#include <combaseapi.h>


namespace dru
{
	FMOD::Studio::System* Fmod::mSystem = nullptr;
	FMOD::System* Fmod::mCoreSystem = nullptr;

	void Fmod::Initialize()
	{
		void* extraDriverData = NULL;

		FMOD::Studio::System::create(&mSystem);

		// The example Studio project is authored for 5.1 sound, so set up the system output mode to match
		mSystem->getCoreSystem(&mCoreSystem);
		mCoreSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE::FMOD_SPEAKERMODE_5POINT1, 0);

		mSystem->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, extraDriverData);

	}

	bool Fmod::CreateSound(const std::string& path, FMOD::Sound** sound)
	{
		if (FMOD_RESULT::FMOD_OK != mCoreSystem->createSound(path.c_str(), FMOD_3D, 0, sound))
			return false;

		return true;
	}

	void Fmod::SoundPlay(FMOD::Sound* sound, FMOD::Channel** channel)
	{
		mCoreSystem->playSound(sound, 0, false, channel);
	}

	void Fmod::Set3DListenerAttributes(const Vector3* pos, const Vector3* vel, const Vector3* forward, const Vector3* up)
	{
		FMOD_VECTOR fmodPos(pos->x, pos->y, pos->z);
		FMOD_VECTOR fmodVel(vel->x, vel->y, vel->z);
		FMOD_VECTOR fmodForward(forward->x, forward->y, forward->z);
		FMOD_VECTOR fmodUp(up->x, up->y, up->z);

		mCoreSystem->set3DListenerAttributes(0, &fmodPos, &fmodVel, &fmodForward, &fmodUp);
	}

	void Fmod::Release()
	{
		//mCoreSystem->release();
		//mCoreSystem = nullptr;

		mSystem->release();
		mSystem = nullptr;
	}


}
