#pragma once
#include "Team.h"
#include "ParticleEmitter.h"

namespace DPhoenix
{
	enum ParticaleStages
	{
		SPAWN_STAGE_P,
		FADEOUT_STAGE_P,
		COMPLETE_P
	};

	class Particale
	{
	public:

		GameTimer mStageTimer;						//timer for stages
		ParticaleStages mParticaleStage;				//stages of firing
		AvailableActions mAction;					//whichi type of weapon / action
		TeamTypes mTeamType;
		std::vector<CharacterClass*> mTeamMembers;		//the team that fired
		int mCurrentMember;

		ParticleEmitter* mParticleEmitter;

		float mWeaponModifier;						//weapon power mod
		float mCritModifier;
		float mAccModifer;

		PointLight* mRadiance;						//light emanitong from prkectiler
		float mDistanceTravelled;					// how far porject has travled
		float mMaxDistance;							// cout off distance for projectile
		float mMaxScale;							// how big projectile frows
		float mScale;								//scale of projectile

		//singletons
		TextureMgr* mTexMgr;
		ID3D11Device* md3dDevice;

		//pointer to enemt/player
		Team* mPlayerTeam;
		Team* mEnemyTeam;



		Particale(
			AvailableActions action, TeamTypes teamType, Team* playerTeam,
			Team* enemyTeam, TextureMgr* texMgr, ID3D11Device* d3dDevice,
			ParticleEmitter* ParticleEmitter);
		~Particale();

		void Update(float dt);
	};
}