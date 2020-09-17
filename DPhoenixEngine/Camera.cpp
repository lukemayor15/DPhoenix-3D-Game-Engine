#include "D3DUtil.h"

//constructor
DPhoenix::Camera::Camera()
{
	//create default perspective matrix
	//position at + 10 on z
	mPosition = XMFLOAT3(0.0f, 0.0f, 10.0f);
	//up direction is y 
	mUpDir = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//aspect ratio (should be update on resize)
	float ratio = 1440 / 900;
	//Send FOV, aspect ratio, near plane , far plane
	SetPerspective(XM_PI / 4.0f, ratio, 1.0f, 10000.0f);
	//default looking target
	mTarget.x = 1.0f; mTarget.y = 0.0f, mTarget.z = 0.0f;

	//new for :LITS
	mGoalPosition = XMFLOAT3(0.0f, 0.0f, 10.0f);
	mTargetPos = XMFLOAT3(10.0f, 0.0f, 10.0f);
	mGoalTarget = mTargetPos;
	//create defalut vieew matrices
	Update(0.0f);
}

//default destructor
DPhoenix::Camera::~Camera()
{

}

void DPhoenix::Camera::SetPerspective(float FOV, float aspectRatio, float nearRange, float farRange)
{
	//set vars
	mFOV = FOV;
	mAspectRatio = aspectRatio;
	mNearRange = nearRange;
	mFarRange = farRange;

	//set the cameras perspective matrix (projection)
	mMatrixProj = XMMatrixPerspectiveFovLH(mFOV, mAspectRatio, mNearRange, mFarRange);
}

//update
void DPhoenix::Camera::Update(float dt)
{
	//new for LITS - move to goal pos
	//this interpoloates te camera pos
	if (mPosition.x != mGoalPosition.x ||
		mPosition.y != mGoalPosition.y ||
		mPosition.z != mGoalPosition.z)
	{
		//conversion to vector tpes to use XM methods
		XMVECTOR goalPosVec = XMLoadFloat3(&mGoalPosition);
		XMVECTOR cameraPosVec = XMLoadFloat3(&mPosition);
		//subtract and normalise to get direction to goal
		XMVECTOR pointAtGoalVec = XMVectorSubtract(goalPosVec, cameraPosVec);
		pointAtGoalVec = XMVector3Normalize(pointAtGoalVec);

		//and now conver back to float3
		XMFLOAT3 moveDir;
		XMStoreFloat3(&moveDir, pointAtGoalVec);

		//the camera pos might bvery close or vary widly-
		//hence it best to move 2x distance / ps * dt eahc time of the distace
		// should get an easing efect
		//get ablsute distance
		float xDistPc = abs(mPosition.x - mGoalPosition.x);
		float yDistPc = abs(mPosition.y - mGoalPosition.y);
		float zDistPc = abs(mPosition.z - mGoalPosition.z);

		//rateof movemnt twice the distnace per sec
		//this get slower it gets closer
		mPosition.x += moveDir.x * xDistPc * 2.0f * dt;
		mPosition.y += moveDir.y * yDistPc * 2.0f * dt;
		mPosition.z += moveDir.z * zDistPc * 2.0f * dt;

		//now calulate the distnac ebetween the foal pos and current pos

		goalPosVec = XMLoadFloat3(&mGoalPosition);
		cameraPosVec = XMLoadFloat3(&mPosition);
		XMVECTOR distance = XMVector3Length(XMVectorSubtract(goalPosVec, cameraPosVec));
		XMFLOAT3 distFloat;
		XMStoreFloat3(&distFloat, distance);
		//if we within a ertin distance snap to pos
		if (distFloat.x < 0.01f)
		{
			mPosition = mGoalPosition;
		}
	}
	//no yijs bit interlopaes the camears target pos
	//to determine the lok at
	if (mTargetPos.x != mGoalTarget.x ||
		mTargetPos.y != mGoalTarget.y ||
		mTargetPos.z != mGoalTarget.z)
	{
		//conver to vec toypes to use XM methods
		XMVECTOR goalTargetVec = XMLoadFloat3(&mGoalTarget);
		XMVECTOR cameraTargetVec = XMLoadFloat3(&mTargetPos);
		//subtract and normalise to get directional goal
		XMVECTOR pointAtGoalVec = XMVectorSubtract(goalTargetVec, cameraTargetVec);
		pointAtGoalVec = XMVector3Normalize(pointAtGoalVec);

		//amd now conver back to float3
		XMFLOAT3 moveDir;
		XMStoreFloat3(&moveDir, pointAtGoalVec);

		//tyhe camera pos might be very close or widly
		//hence it best to move 2x distance ps * dt each time of distance
		//should get an easing effect
		//get absloute distance on each axis
		float xDistPc = abs(mTargetPos.x - mGoalTarget.x);
		float yDistPc = abs(mTargetPos.y - mGoalTarget.y);
		float zDistPc = abs(mTargetPos.z - mGoalTarget.z);
		//rate of movment = twice the distnace per sec
		//this gets slower as it get closer
		mTargetPos.x += moveDir.x * xDistPc * 2.0f * dt;
		mTargetPos.y += moveDir.y * yDistPc * 2.0f * dt;
		mTargetPos.z += moveDir.z * zDistPc * 2.0f * dt;

		//now cal the distane between goal pos and current pos
		goalTargetVec = XMLoadFloat3(&mGoalTarget);
		cameraTargetVec = XMLoadFloat3(&mTargetPos);
		XMVECTOR distance = XMVector3Length(XMVectorSubtract(goalTargetVec, cameraTargetVec));
		XMFLOAT3  distFloat;
		XMStoreFloat3(&distFloat, distance);
		//if wethin a certain distande, snap pos
		if (distFloat.x < 0.01f)
		{
			mTargetPos = mGoalTarget;
		}


	}
	//now we adjust the pos and target we need recal
	//the look direction to then construct the matrices
	
	//conver to vector format the target post
	XMVECTOR targetPosVec = XMLoadFloat3(&mTargetPos);
	XMVECTOR cameraPosVec = XMLoadFloat3(&mPosition);

	//now subtract the vectors and normalise get direction
	XMVECTOR pointAtTargetVec = XMVectorSubtract(targetPosVec, cameraPosVec);
	pointAtTargetVec = XMVector3Normalize(pointAtTargetVec);
	//and oncvert ack to float3 to use in cal
	XMFLOAT3 newLookDir;
	XMStoreFloat3(&newLookDir, pointAtTargetVec);

	//this update the camera target nased on ,ook dirextion
	mTarget.x = mPosition.x + newLookDir.x;
	mTarget.y = mPosition.y + newLookDir.y;
	mTarget.z = mPosition.z + newLookDir.z;

	

	//Build the virew matrix (position, target, updirection)
	XMVECTOR pos = XMVectorSet(mPosition.x, mPosition.y, mPosition.z, 1.0f);
	XMVECTOR target = XMVectorSet(mTarget.x, mTarget.y, mTarget.z, 1.0f);
	XMVECTOR up = XMVectorSet(mUpDir.x, mUpDir.y, mUpDir.z, 0.0f);

	//create view matrix
	mMatrixView = XMMatrixLookAtLH(pos, target, up);
}

//adjust rotation relative to current rotation
void DPhoenix::Camera::Rotate(float x, float y, float z)
{
	mRotation.x += x; mRotation.y += y; mRotation.z += z;
}

//set target value relative to current
void DPhoenix::Camera::Look(float x, float y, float z)
{
	mPosition.x += x; mPosition.y += y; mPosition.z += z;
}

//move relative position and target
void DPhoenix::Camera::Move(float x, float y, float z)
{
	mPosition.x += x; mPosition.y += y; mPosition.z += z;
	mTarget.x += x; mPosition.y += y; mPosition.z += z;
}