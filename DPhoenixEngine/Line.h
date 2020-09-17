#pragma once
#include "D3DUtil.h"

namespace DPhoenix
{
	class Line : public Entity
	{
	public:

		XMFLOAT3 mLineBegin;				//origin
		XMFLOAT3 mLineEnd;					//end
		XMFLOAT3 mDirection;				//direction from origin
		float mLineSize;					//size of line
		std::vector<float> mCollisionDistance; // distance from where the line hit
		std::vector<XMFLOAT3> mIntersectionPoints;	//point of intersextion

		//constructor / destructor
		Line();
		~Line();

		//init - takes in orgin , direction and line size / distance
		void Init(XMFLOAT3 startFrom, XMFLOAT3 direction, float distance);

		//add collision prop - build up collection of intersextions
		void AddCollision(float distance, XMFLOAT3 intersectionPoint, Entity* collideBuddy);
		XMFLOAT3 GetNearestPoint();

		//empty method for niheritance
		XMMATRIX CalculateTransforms() { return XMMATRIX(); };
		void SortCollision();
	};
}