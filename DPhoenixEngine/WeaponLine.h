#pragma once
#include "Team.h"
#include "BillboardSprite.h"
#include "ParticleEmitter.h"

namespace DPhoenix
{
	enum WeaponStages
	{
		FIRE_LINE_WS,
		CHECK_LINE_WS,
		ANIMATE_WS,
		COMPLETE_WS
	};

	class WeaponLine
	{
	public:
		Line* mWeaponLine;	//the line for collisions
		CharacterClass* mAttacker;	//the character who fired
		GameTimer mStageTimer;		//timer for stages
		WeaponStages mWeaponStage;	//stage of firing
		AvailableActions mAction;	// which type of weapon / action
		TeamTypes mTeamType;		//the team that fired
		XMFLOAT3 mDmgPosition;		// position of collision to displat dmg
		

		int mDmg;			//dmg value
		bool isHit;		// flag if hit oppent
		float mCoverDmg; //	accumulator
		float mWeaponModifier;	//weapon pwer modifer

		//for display of impact sprites
		std::vector<BillboardSprite*> mBillboards;
		ParticleEmitter* mParticleEmitter;

		//singletons
		TextureMgr* mTexMgr;
		ID3D11Device* md3dDevice;

		//pointers need passing
		Team* mPlayerTeam;
		Team* mEnemyTeam;

		//methods ------------#
		WeaponLine(CharacterClass* attacker, XMFLOAT3 direction, XMFLOAT3 start,
			AvailableActions action, TeamTypes teamType, Team* playerTeam,
			Team* enemyTeam, TextureMgr* texMgr, ID3D11Device* d3dDevice);
		~WeaponLine();

		void Update(float dt);


	};
}