#pragma once
#include "D3DUtil.h"

namespace DPhoenix
{
	class Camera
	{
	private :
		//prohection, view , rotation matrices
		// And up direction
		XMMATRIX mMatrixProj;
		XMMATRIX mMatrixView;
		XMMATRIX mMatrixRot;
		XMFLOAT3 mUpDir;

		//camera properties
		//near, farm range and aspect ratio
		float mNearRange;
		float mFarRange;
		float mAspectRatio;
		float mFOV;

	public:

		//new public members ofr lITS / smoothing
		XMFLOAT3 mGoalPosition;
		XMFLOAT3 mTargetPos;
		XMFLOAT3 mGoalTarget;
			
		//position, rotation and target vectors
		XMFLOAT3 mPosition;
		XMFLOAT3 mRotation;
		XMFLOAT3 mTarget;

		//constrcutor / destructor
		Camera();
		~Camera();

		//set perspectives
		void SetPerspective(float FOV, float aspectRatio, float nearRange, float farRange);

		//get view / projection matrix
		XMMATRIX GetView() { return mMatrixView;}
		XMMATRIX GetProj() { return mMatrixProj; }

		void Update(float dt);

		//rotate / look / move
		void Rotate(float x, float y, float z);
		void Look(float x, float y, float z);
		void Move(float x, float y, float z);




	};
}