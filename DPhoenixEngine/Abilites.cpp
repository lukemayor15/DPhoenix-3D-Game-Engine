#include "Abilites.h"

DPhoenix::Particale::Particale( 
	AvailableActions action, TeamTypes teamType, Team* playerTeam,
	Team* enemyTeam, TextureMgr* texMgr, ID3D11Device* d3dDevice,
	ParticleEmitter* ParticleEmitter)
{
	//singletons
	mTexMgr = texMgr;
	md3dDevice = d3dDevice;

	//init weapon prop
	mScale = 1.0f;
	mDistanceTravelled = 0.0f;

	mAction = action;
	ParticaleStages mParticaleStage = SPAWN_STAGE_P;

	//team propties
	mTeamType = teamType;
	mPlayerTeam = playerTeam;
	mEnemyTeam = enemyTeam;
	mParticleEmitter = ParticleEmitter;
	mCurrentMember = 0;

	switch (action)
	{
	case COMMAND_ACTION:
	case SNIPE_ACTION:
	case EMERGENCY_REPAIR_ACTION:
	case BRACE_ACTION:
		mParticleEmitter = new DPhoenix::ParticleEmitter();
		mParticleEmitter->Load("Textures\\ObjectAssets\\KnowledgeFire.png",
			mTexMgr, 1.0f, 1.0f, md3dDevice);
		mParticleEmitter->mSprite->SetCurrentFrame(0);
		mParticleEmitter->mSprite->mAnimationColumns = 8;
		mParticleEmitter->mSprite->mAnimationDirection = 16;
		mParticleEmitter->mSprite->SetAnimationRange(0, 7);
		mParticleEmitter->mSprite->SetScale(3.0f);
		mParticleEmitter->mSprite->mFlipValue = 1.0f;

		mParticleEmitter->mPosition = mTeamMembers[mCurrentMember]->mModelInstance->mPosition;

		break;
	}
}

DPhoenix::Particale::~Particale()
{

}

void Update(float dt)
{

}