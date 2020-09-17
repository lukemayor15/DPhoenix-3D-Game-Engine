#pragma once
#include "Team.h"
#include "BillboardSprite.h"

namespace DPhoenix
{
	enum WeaponMeshStages
	{
		SPAWN_MESH_WMS,
		FIRING_MESH_WMS,
		FADE_OUT_WMS,
		COMPLETE_WMS
	};

	//weapon type stops when hits a chracter
	//magic can go thoug and hit others
	enum WeaponTypes
	{
		MAGIC_WT,
		WEAPON_WT
	};

	class WeaponMesh
	{
	public:
		PrimitiveInstance* mWeaponMeshInstance;		//the mesh for collisons
		CharacterClass* mAttacker;					//the cahracter who fired
		GameTimer mStageTimer;						//timer for stages
		WeaponMeshStages mWeaponStage;				//stages of firing
		AvailableActions mAction;					//whichi type of weapon / action
		TeamTypes mTeamType;						//the team that fired

		std::vector<XMFLOAT3> mDmgPosition;			//vector to hold pos of dmg
		std::vector<int> mDmgValues;				//vector to hold dmg value
		std::vector<bool> mHasCollided;				//falgs for iw we have dealt indivial caollision

		std::vector<BillboardSprite*> mBillboards;	//for display of impcat sprite
		float mCoverDmg;							//accumalotor of cover modifer
		float mWeaponModifier;						//weapon power mod
		float mCritModifier;
		float mAccModifer;

		PointLight* mRadiance;						//light emanitong from prkectiler
		float mDistanceTravelled;					// how far porject has travled
		float mMaxDistance;							// cout off distance for projectile
		float mMaxScale;							// how big projectile frows
		float mScale;								//scale of projectile
		WeaponTypes mWeaponType;					//type of weapon / magic

		//singletons
		TextureMgr* mTexMgr;
		ID3D11Device* md3dDevice;				

		//pointer to enemt/player
		Team* mPlayerTeam;
		Team* mEnemyTeam;

		WeaponMesh(CharacterClass* attacker, XMFLOAT3 direction, XMFLOAT3 start,
			AvailableActions action, TeamTypes teamType, Team* playerTeam,
			Team* enemyTeam, TextureMgr* texMgr, ID3D11Device* d3dDevice,
			GeometryGenerator::MeshData* sphere);
		~WeaponMesh();

		void Update(float dt);
	};
}
