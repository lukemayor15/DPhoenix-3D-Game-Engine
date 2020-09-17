#pragma once

#include "D3DUtil.h"

namespace DPhoenix
{
	//eneity used interally to idneity type of enityi
	enum EntityType
	{
		ENTITY_UNKOWN = -1,
		ENTITY_PLAYER_MESH = 1,
		ENTITY_SCENERY_MESH,
		ENTITY_RAY,
		ENTITY_COLLECTABLE_MESH,
		ENTITY_ENEMY_MESH,
		ENTITY_WEAPON_MESH,
		ENTITY_LINE,
		ENTITY_CAMERA_LINE,
		ENTITY_SELECTION,
		ENTITY_WEAPON_LINE,
		ENTITY_MAGIC_PROJECTILE,
		ENTITY_WALL_MESH,
		ENTITY_COVER_MESH,
		ENTITY_BEACON_MESH
	};

	class Entity
	{
	public:
		int mId;						//unique ID
		std::string mName;				//name
		enum EntityType mEntityType;		//enity type
		bool mAlive;					//is alive
		float mLifetimeStart;			//start of life
		float mLifetimeCounter;			//how long lived
		float mLifetimeLength;			//how long to live
		bool mVisible;					//is visiable
		bool mCollidable;				//is collidable
		bool mCollided;					//has collided
		Entity* mCollideBuddy;			//pointer to colliede enity

		//a vector of all enties collied with 
		std::vector<Entity*> mCollidedEntities;
		std::vector<Entity*> mAABBCollidedEntities;
		float mOpacity;

		//to be used bu child classes
		XMFLOAT3 mPosition;				//position
		XMFLOAT3 mPrevPosition;			// previous position
		XMFLOAT3 mVelocity;				//velocity
		XMFLOAT3 mRelativeVelocity;	//velocity based on forward vecotr
		XMFLOAT3 mScale;				//scale
		XMFLOAT3 mRotation;				//rotation
		XMFLOAT3 mForwardVector;		//forward vector
		XMFLOAT3 mRightVector;			//right vector


										//for collision cgecking
		XMFLOAT3 mHalfSizes;

		//constructor / destuctor
		Entity();
		virtual  ~Entity() { };

		virtual XMMATRIX CalculateTransforms() = 0;
	};
}