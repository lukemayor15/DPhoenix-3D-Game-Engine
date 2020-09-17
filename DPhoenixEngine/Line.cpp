#include "D3DUtil.h"

DPhoenix::Line::Line() : Entity()
{
	mEntityType = ENTITY_LINE;
}

DPhoenix::Line::~Line()
{

}

void DPhoenix::Line::Init(XMFLOAT3 startForm, XMFLOAT3 direction, float distance)
{
	//set props for ebing and end line
	mLineBegin = startForm;
	mDirection = direction;
	mLineSize = distance;

	//start an end to the line
	mLineEnd.x = mLineBegin.x + mDirection.x * distance;
	mLineEnd.y = mLineBegin.y + mDirection.y * distance;
	mLineEnd.z = mLineBegin.z + mDirection.z * distance;

	//clear vecotors
	mCollisionDistance.clear();
	mIntersectionPoints.clear();
	mCollidedEntities.clear();
}

void DPhoenix::Line::AddCollision(float distance, XMFLOAT3 intersectionPoint, Entity* collideBuddy)
{
	//collision detectiob prors - add new collision
	mCollisionDistance.push_back(distance);
	mIntersectionPoints.push_back(intersectionPoint);
	mCollidedEntities.push_back(collideBuddy);
}

//this is the nearest point to the begin of line
// this is only to be calle dif line has collided
XMFLOAT3 DPhoenix::Line::GetNearestPoint()
{
	float lowestDistance = mLineSize;
	int mLowPointIndex = 0;

	//loop thorugh distance and get loweet
	for (int i = 0; i < mCollisionDistance.size(); i++)
	{
		if (mCollisionDistance[i] < lowestDistance)
		{
			lowestDistance = mLineSize;
			mLowPointIndex = i;
		}
	}

	return mIntersectionPoints[mLowPointIndex];
}

//put the collision in order by distance
void DPhoenix::Line::SortCollision()
{
	//should all be same size
	std::vector<float> oldDistance = mCollisionDistance;
	//vector to hold reorderd intersection points
	std::vector<XMFLOAT3> newIntersections;
	newIntersections.resize(mIntersectionPoints.size());
	//vector to hold reorder collided entities
	std::vector<Entity*> newCollisionEntities;
	newCollisionEntities.resize(mCollidedEntities.size());

	//this will reroder the collsiin distnacevecotr from smallest to highest

	//loop thorugh sorted vector
	for (int i = 0; i < mCollisionDistance.size(); i++)
	{
		//now loop though old distance vector to match the values
		for (int j = 0; j < oldDistance.size(); j++)
		{
			//if value matches, we need to update new related vecotrs to match
			if (mCollisionDistance[i] == oldDistance[j])
			{
				newIntersections[i] = mIntersectionPoints[j];
				newCollisionEntities[j] = mCollidedEntities[i];
			}
		}
	}

	//assign the sort vectors
	mCollidedEntities = newCollisionEntities;
	mIntersectionPoints = newIntersections;
}