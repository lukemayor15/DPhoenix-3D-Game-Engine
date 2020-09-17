#pragma once
#include "D3DUtil.h"

namespace DPhoenix
{
	class EAngle
	{
	public:
		float p, y, r; //pitch / yaw / roll

		//constructor with default values
		EAngle()
		{
			p = y = r = 0.0f;
		}

		//constrcutor with values supplied
		EAngle(float pitch, float yaw, float roll)
		{
			p = pitch;
			y = yaw;
			r = roll;
		}

		//convret to XMFLOAT 3 for use with camera target
		XMFLOAT3 ToFloat3() const;

		//this bounds the yaw and pitch values
		void Normalize();
	};
}