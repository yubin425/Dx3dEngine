#pragma once
#include "Graphics.h"

using namespace dru::enums;

namespace dru
{
	class ConstantBuffer : GpuBuffer
	{
		friend class Material;

	public:
		ConstantBuffer();
		ConstantBuffer(eCBType type);
		virtual ~ConstantBuffer();	

		bool Create(UINT size);
		void SetData(void* data);
		void Bind(eShaderStage stage);
		void Clear();


	private:
		const eCBType mType;
	};

}