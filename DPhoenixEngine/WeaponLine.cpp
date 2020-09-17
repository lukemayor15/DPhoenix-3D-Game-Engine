#include "WeaponLine.h"

DPhoenix::WeaponLine::WeaponLine(CharacterClass* attacker, XMFLOAT3 direction, XMFLOAT3 start,
	AvailableActions action, TeamTypes teamType, Team* playerTeam,
	Team* enemyTeam, TextureMgr* texMgr, ID3D11Device* d3dDevice)
{
	start.y = 20.0f;
	//line propeerties for collision
	mWeaponLine = new Line();
	mWeaponLine->Init(start, direction, 200.0f);
	mWeaponLine->mEntityType = ENTITY_WEAPON_LINE;
	mWeaponLine->mCollidable = true;

	//init weapon propeties
	mAttacker = attacker;
	mAction = action;
	mWeaponStage = FIRE_LINE_WS;

	//team propertoes
	mTeamType = teamType;
	mPlayerTeam = playerTeam;
	mEnemyTeam = enemyTeam;

	//check the action and who fired for updating
	//values
	switch (mAction)
	{
	
	case DPhoenix::CANNON_ACTION:
		mCoverDmg = 0.5f;
		mWeaponModifier = 1.1f;
		if (mTeamType == PLAYER_TEAM)
			mPlayerTeam->mTPPool -= 2;
		else
			mEnemyTeam->mTPPool -= 2;
		break;

	}

	//dmg falgs
	isHit = false;
	mDmg = -1;


	//singletones 
	mTexMgr = texMgr;
	md3dDevice = d3dDevice;
}

DPhoenix::WeaponLine::~WeaponLine()
{

}

void DPhoenix::WeaponLine::Update(float dt)
{
	//tick stage timer
	mStageTimer.Tick();

	bool mIsPlayerTeam = true;
	//check for beaocn buff
	//set initial dmg modifer
	float dmgOverallModifier = 1.0f;
	//flag to seep loop thogh collision
	//until hit a wall or oppent
	bool keepLooping = true;

	switch (mWeaponStage)
	{
	case FIRE_LINE_WS:
		//should only last one frame nefore checking
		//as collision sould have happend
		mWeaponStage = CHECK_LINE_WS;
		break;
	case CHECK_LINE_WS:
		//if the line has collided we then need to sort the collision in odre of distance
		//nearest to furthest
		if (mWeaponLine->mCollided)
			mWeaponLine->SortCollision();

		//main loop - go though all collided entites stop when hit wall or oppent
		for (int i = 0; i < mWeaponLine->mCollidedEntities.size() && keepLooping; i++)
		{
			//cover checks
			if (mWeaponLine->mCollidedEntities[i]->mEntityType == ENTITY_COVER_MESH)
			{
				//update the damge modifer
				dmgOverallModifier *= mCoverDmg;
				//add billboard sprite
				mBillboards.push_back(new DPhoenix::BillboardSprite());
				mBillboards.back()->LoadBS("Textures\\Impact\\Bang.png", mTexMgr, 15.0f, 15.0f, md3dDevice);
				mBillboards.back()->mPosition = mWeaponLine->mIntersectionPoints[i];
				//add fx
				//particle
				mParticleEmitter = new DPhoenix::ParticleEmitter();
				mParticleEmitter->Load("Textures\\ObjectAssets\\KnowledgeFire.png",
					mTexMgr, 1.0, 1.0f, md3dDevice);
				mParticleEmitter->mSprite->SetCurrentFrame(0);
				mParticleEmitter->mSprite->mAnimationColumns = 8;
				mParticleEmitter->mSprite->mAnimationDirection = 16;
				mParticleEmitter->mSprite->SetAnimationRange(0, 7);
				mParticleEmitter->mSprite->SetScale(2.0f);
				mParticleEmitter->mPosition = mWeaponLine->mIntersectionPoints[i];
				mParticleEmitter->Update(dt);

			}

			//player to enemy hit
			if (mTeamType == PLAYER_TEAM && mWeaponLine->mCollidedEntities[i]->mEntityType == ENTITY_ENEMY_MESH)
			{
				mIsPlayerTeam = true;
				//pointer to victim
				CharacterClass* victim;

				//loopthrough the nemy team and their collision to match the id to the weapon line
				for (int j = 0; j < mEnemyTeam->mTeamMembers.size(); j++)
				{
					if (mEnemyTeam->mTeamMembers[j]->mModelInstance->mId ==
						mWeaponLine->mCollidedEntities[i]->mId)
					{
						//set the victim as the struct enemy
						victim = mEnemyTeam->mTeamMembers[j];
					}
				}

				//calulate dmage using the weapon attach method,sending modifers
				mDmg = mAttacker->WeaponAttack(victim, mWeaponModifier,  0, 0, dmgOverallModifier, mIsPlayerTeam);
				isHit = true;

				//if dmg greater than -1
				if (mDmg > -1)
				{
					//the vicitim should take the hit
					victim->TakeDamage(mDmg);
					//add billboard sprite bang)
					mBillboards.push_back(new DPhoenix::BillboardSprite());
					mBillboards.back()->LoadBS("Textures\\Impact\\Bang.png", mTexMgr, 15.0f, 15.0f, md3dDevice);
					mBillboards.back()->mPosition = mWeaponLine->mIntersectionPoints[i];
				}
				else
				{
					//miss / smoke animation
				}

				//unset loopingfalg and set the damge posiotn to the point of impact
				keepLooping = false;
				mDmgPosition = mWeaponLine->mIntersectionPoints[i];

				//add fx
			}
			//enemy to player hit
			if (mTeamType == ENEMY_TEAM && mWeaponLine->mCollidedEntities[i]->mEntityType == ENTITY_PLAYER_MESH)
			{
				mIsPlayerTeam = false;
				//pointer to victim
				CharacterClass* victim;

				//loopthrough the nemy team and their collision to match the id to the weapon line
				for (int j = 0; j < mPlayerTeam->mTeamMembers.size(); j++)
				{
					if (mPlayerTeam->mTeamMembers[j]->mModelInstance->mId ==
						mWeaponLine->mCollidedEntities[i]->mId)
					{
						//set the victim as the struct enemy
						victim = mPlayerTeam->mTeamMembers[j];
					}
				}

				//calulate dmage using the weapon attach method,sending modifers
				mDmg = mAttacker->WeaponAttack(victim, mWeaponModifier, dmgOverallModifier, 0.0f, 0.0f, mIsPlayerTeam);
				isHit = true;

				//if dmg greater than -1
				if (mDmg > -1)
				{
					//the vicitim should take the hit
					victim->TakeDamage(mDmg);
					//add billboard sprite bang)
					mBillboards.push_back(new DPhoenix::BillboardSprite());
					mBillboards.back()->LoadBS("Textures\\Impact\\Bang.png", mTexMgr, 15.0f, 15.0f, md3dDevice);
					mBillboards.back()->mPosition = mWeaponLine->mIntersectionPoints[i];
				}
				else
				{
					//miss / smoke animation
				}

				//unset loopingfalg and set the damge posiotn to the point of impact
				keepLooping = false;
				mDmgPosition = mWeaponLine->mIntersectionPoints[i];

				//add fx
			}

			//wall hit
			if (mWeaponLine->mCollidedEntities[i]->mEntityType == ENTITY_WALL_MESH)
			{
				//unset looping flag
				keepLooping = false;
				//add to billboard sprite bang
				mBillboards.push_back(new DPhoenix::BillboardSprite());
				mBillboards.back()->LoadBS("Textures\\Impact\\Bang.png", mTexMgr, 15.0f, 15.0f, md3dDevice);
				mBillboards.back()->mPosition = mWeaponLine->mIntersectionPoints[i];

				//add fx
			}
		}
		//unset entity propeties so engine can remove
		mWeaponLine->mCollidable = false;
		mWeaponLine->mAlive = false;

		//reser thimer and got to next stage
		mStageTimer.Reset();
		mWeaponStage = ANIMATE_WS;
		break;
	case ANIMATE_WS:
		//within bounds, animate dmage and billboards
		if (mStageTimer.TotalTime() <= 2.5f)
		{
			mDmgPosition.y += 1.0f * dt;

			for (int i = 0; i < mBillboards.size(); i++)
			{
				mBillboards[i]->UpdateBS(dt);
			}
		}
		else
		{
			//outside of bounds reset tier and move to final stage
			mStageTimer.Reset();
			mWeaponStage = COMPLETE_WS;
		}

		break;
	case COMPLETE_WS:
		//used as flag in main game logic
		break;
	
	}
}