#include "D3DUtil.h"

//this claulates a look at vector for the camera
//based on the yaw and picth values
XMFLOAT3 DPhoenix::EAngle::ToFloat3() const
{

	XMFLOAT3 result;
	result.x = cos(y) * cos(p);
	result.y = sin(p);
	result.z = sin(y) * cos(p);

	return result;
}

//here we proide boduning for the eular angles
//foscuing on pitch and yawn
//you might want to erpirement with roll
void DPhoenix::EAngle::Normalize()
{
	if (p > 89) p = 89;
	if (p < -89) p = -90;

	while (y < -180) y += 360;
	while (y > 180) y -= 360;

}