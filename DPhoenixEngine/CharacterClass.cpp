#include "CharacterClass.h"
DPhoenix::CharacterClass::CharacterClass(CharacterClasses _class, TextureMgr * _texMgr,
	ID3D11Device * _md3dDevice, AudioMgr * _audioMgr)
{
	mClass = _class;
	mTexMgr = _texMgr;
	md3dDevice = _md3dDevice;
	mAudioMgr = _audioMgr;

	switch (mClass)
	{
	case FLAG_SHIP_CLASS:
		mAnimModel = new DPhoenix::SkinnedModel(md3dDevice, *mTexMgr,
			"Models\\SoldierAnimations\\SoldierIdle.dae", "Models\\SoldierAnimations\\");

		//load all animations before calling construct animations
		mAnimModel->Animator->LoadNewAnimations("Models\\SoldierAnimations\\SoldierDancing.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\SoldierAnimations\\SoldierMeleeKick.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\SoldierAnimations\\SoldierRunning.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\SoldierAnimations\\SoldierMagic.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\SoldierAnimations\\SoldierWeaponShoot.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\SoldierAnimations\\SoldierHurt.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\SoldierAnimations\\SoldierDying.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\SoldierAnimations\\SoldierDeadTwitch.dae");
		
		
		
		
		//this calate all the frame of animation for the loaded animations
		mAnimModel->Animator->ConstructAnimations();

		//THESE STEps only for toyland models - this is because the texture arent in the dae/ collade FIle
		//here we applying it to all modle substes - for oter imprted mdels
		//this isnt necsseary
		for (int i = 0; i < mAnimModel->SubsetCount; i++)
		{
			mAnimModel->Subsets[i].materialIndex = 0;
		}

		mAnimModel->DiffuseMapSRV[0] =
			mTexMgr->CreateTexture("Models\\SoldierAnimations\\Textures\\2K\\SoldierTPoseWithBones_1001_BaseColor.png");
		mAnimModel->NormalMapSRV[0] =
			mTexMgr->CreateTexture("Models\\SoldierAnimations\\Textures\\2K\\SoldierTPoseWithBones_1001_Normal.png");
		break;
	case BRUSIER_SHIP_CLASS:
		mAnimModel = new DPhoenix::SkinnedModel(md3dDevice, *mTexMgr,
			"Models\\DarkangelAnimation\\AngelIdle.dae", "Models\\DarkangelAnimation\\");

		//load all animations before calling construct animations
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelDancing.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelMelee.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelSneakWalk.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelMelee.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelMelee.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelHurt.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelDying.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelDead.dae");
		
		//this calate all the frame of animation for the loaded animations
		mAnimModel->Animator->ConstructAnimations();

		//THESE STEps only for toyland models - this is because the texture arent in the dae/ collade FIle
		//here we applying it to all modle substes - for oter imprted mdels
		//this isnt necsseary
		for (int i = 0; i < mAnimModel->SubsetCount; i++)
		{
			mAnimModel->Subsets[i].materialIndex = 0;
		}
		mAnimModel->DiffuseMapSRV[0] =
			mTexMgr->CreateTexture("Models\\DragonAnimation\\DragonTextures\\DragonSkin_D.png");
		mAnimModel->NormalMapSRV[0] =
			mTexMgr->CreateTexture("Models\\DragonAnimation\\DragonTextures\\DragonSkin_D_nm.png");
		break;
	case CORVETTE_SHIP_CLASS:
		mAnimModel = new DPhoenix::SkinnedModel(md3dDevice, *mTexMgr,
			"Models\\DarkangelAnimation\\AngelIdle.dae", "Models\\DarkangelAnimation\\");

		//load all animations before calling construct animations
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelDancing.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelMelee.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelSneakWalk.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelMelee.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelMelee.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelHurt.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelDying.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\DarkangelAnimation\\AngelDead.dae");
		//this calate all the frame of animation for the loaded animations
		mAnimModel->Animator->ConstructAnimations();

		//THESE STEps only for toyland models - this is because the texture arent in the dae/ collade FIle
		//here we applying it to all modle substes - for oter imprted mdels
		//this isnt necsseary
		for (int i = 0; i < mAnimModel->SubsetCount; i++)
		{
			mAnimModel->Subsets[i].materialIndex = 0;
		}

		mAnimModel->DiffuseMapSRV[0] =
			mTexMgr->CreateTexture("Textures\\Weapons\\Scales_cm.png");
		mAnimModel->NormalMapSRV[0] =
			mTexMgr->CreateTexture("Textures\\Weapons\\Scales_cm.png");
		
		break;
	case CRUSIER_SHIP_CLASS:
		mAnimModel = new DPhoenix::SkinnedModel(md3dDevice, *mTexMgr,
			"Models\\CatAnimations\\CatIdle.dae", "Models\\CatAnimations\\");

		//load all animations before calling construct animations
		mAnimModel->Animator->LoadNewAnimations("Models\\CatAnimations\\CatDance.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\CatAnimations\\CatMeleeSwipe.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\CatAnimations\\CatWalk.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\CatAnimations\\CatMagicSpit.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\CatAnimations\\CatMeleePounce.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\CatAnimations\\CatHitRecoil.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\CatAnimations\\CatDying.dae");
		mAnimModel->Animator->LoadNewAnimations("Models\\CatAnimations\\CatDead.dae");
		//this calate all the frame of animation for the loaded animations
		mAnimModel->Animator->ConstructAnimations();

		//THESE STEps only for toyland models - this is because the texture arent in the dae/ collade FIle
		//here we applying it to all modle substes - for oter imprted mdels
		//this isnt necsseary
		for (int i = 0; i < mAnimModel->SubsetCount; i++)
		{
			mAnimModel->Subsets[i].materialIndex = 0;
		}

		mAnimModel->DiffuseMapSRV[0] =
			mTexMgr->CreateTexture("Textures\\Weapons\\Furball_cm.png");
		mAnimModel->NormalMapSRV[0] =
			mTexMgr->CreateTexture("Textures\\Weapons\\Furball_nm.png");
		break;
	
	}

	mModelInstance = new DPhoenix::SkinnedModelInstance("", mAnimModel);
	mModelInstance->Model = mAnimModel;

	SetBaseStats();
	CalculateStats(1);

	mLifeState = CH_OK_LIFESTATE;
	mTurnState = CH_WAIT_TURNSTATE;
	mMoveState = CH_PICKRT_MOVESTATE;
	mAnimation = IDLE_ANIMATION;

	mModelInstance->mHalfSizes = XMFLOAT3(4.0f, 4.0f, 4.0f);

	mTargetBeaconId = 0;

}

DPhoenix::CharacterClass::CharacterClass(const CharacterClass & character)
{
	//stats--------------------------------------------
	mLevel = character.mLevel;
	mBaseExp = character.mBaseExp; mExp = character.mExp;
	mBaseTP = character.mBaseTP; mTP = character.mTP;
	mBaseHS = character.mBaseHS; mHS = character.mHS; mMaxHS = character.mMaxHS;
	mBaseRangeAttack = character.mBaseRangeAttack; mRangeAttack = character.mRangeAttack;
	mBaseMeleeAttack = character.mBaseMeleeAttack; mMeleeAttack = character.mMeleeAttack;
	mBaseHullDefense = character.mBaseHullDefense; mHullDefense = character.mHullDefense;
	mBaseAccuracy = character.mBaseAccuracy; mAccuracy = character.mAccuracy;
	mBaseEvasion = character.mBaseEvasion; mEvasion = character.mEvasion;
	mBaseCrit = character.mBaseCrit; mCrit = character.mCrit;
	mBaseLuck = character.mBaseLuck; mLuck = character.mLuck;

	//character trait#
	mClass = character.mClass;
	//actions should go here when determinde 
	//models shoud go here when determined

	//temp models
	mModelInstance = new DPhoenix::SkinnedModelInstance(*character.mModelInstance);

	mLifeState = character.mLifeState;
	mTurnState = character.mTurnState;
	mMoveState = character.mMoveState;
	mAnimation = character.mAnimation;

	//pointer to main singletons / devices
	mTexMgr = character.mTexMgr;
	md3dDevice = character.md3dDevice;
	mAudioMgr = character.mAudioMgr;

}

DPhoenix::CharacterClass::~CharacterClass()
{

}

void DPhoenix::CharacterClass::SetBaseStats()
{
	switch (mClass)
	{
	case CRUSIER_SHIP_CLASS:
		mBaseExp = 100;
		mBaseTP = 5;
		mBaseHS = 50;
		mBaseHullDefense = 20;
		mBaseRangeAttack = 35;
		mBaseMeleeAttack = 20;
		mBaseEvasion = 10;
		mBaseAccuracy = 73;
		mBaseCrit = 8;
		mBaseLuck = 8;
		break;
	case BRUSIER_SHIP_CLASS:
		mBaseExp = 100;
		mBaseTP = 6;
		mBaseHS = 60;
		mBaseHullDefense = 30;
		mBaseRangeAttack = 25;
		mBaseMeleeAttack = 35;
		mBaseEvasion = 10;
		mBaseAccuracy = 70;
		mBaseCrit = 8;
		mBaseLuck = 8;
		break;

	case CORVETTE_SHIP_CLASS:
		mBaseExp = 100;
		mBaseTP = 10;
		mBaseHS = 40;
		mBaseHullDefense = 25;
		mBaseRangeAttack = 30;
		mBaseMeleeAttack = 25;
		mBaseEvasion = 20;
		mBaseAccuracy = 75;
		mBaseCrit = 15;
		mBaseLuck = 15;
		break;
	case FLAG_SHIP_CLASS:
		mBaseExp = 100;
		mBaseTP = 7;
		mBaseHS = 60;
		mBaseHullDefense = 29;
		mBaseRangeAttack = 32;
		mBaseMeleeAttack = 32;
		mBaseEvasion = 13;
		mBaseAccuracy = 75;
		mBaseCrit = 10;
		mBaseLuck = 10;
		break;
	
	}
}

void DPhoenix::CharacterClass::CalculateStats(int _level)
{
	mLevel = _level;
	switch (mClass)
	{
	case CRUSIER_SHIP_CLASS:
		mExp = floor(mBaseExp * (mLevel ^ 2));
		mTP = floor(log2(mLevel) * 2 + mBaseTP);
		mHS = floor(mBaseHS * pow(mLevel, 1.45));
		mMaxHS = mHS;
		mHullDefense = floor(log2(mLevel) * 25 + mBaseHullDefense);
		mRangeAttack = floor(log2(mLevel) * 40 + mBaseRangeAttack);
		mMeleeAttack = floor(log2(mLevel) * 25 + mBaseMeleeAttack);
		mAccuracy = floor(log2(mLevel) * 4 + mBaseAccuracy);
		mEvasion = floor(log2(mLevel) * 3 + mBaseEvasion);
		mLuck = floor(log2(mLevel) * 1.3 + mBaseLuck);
		mCrit = floor(log2(mLevel) * 1.3 + mBaseCrit);

		break;
	case BRUSIER_SHIP_CLASS:
		mExp = mBaseExp * (mLevel ^ 2);
		mTP = floor(log2(mLevel) * 2 + mBaseTP);
		mHS = floor(mBaseHS * pow(mLevel, 1.48));
		mMaxHS = mHS;
		mHullDefense = floor(log2(mLevel) * 36 + mBaseHullDefense);
		mRangeAttack = floor(log2(mLevel) * 28 + mBaseRangeAttack);
		mMeleeAttack = floor(log2(mLevel) * 53 + mBaseMeleeAttack);
		mAccuracy = floor(log2(mLevel) * 4.5 + mBaseAccuracy);
		mEvasion = floor(log2(mLevel) * 3.5 + mBaseEvasion);
		mLuck = floor(log2(mLevel) * 1.3 + mBaseLuck);
		mCrit = floor(log2(mLevel) * 1.3 + mBaseCrit);
		break;

	case CORVETTE_SHIP_CLASS:
		mExp = mBaseExp * (mLevel ^ 2);
		mTP = floor(log2(mLevel) * 2.5 + mBaseTP);
		mHS = floor(mBaseHS * pow(mLevel, 1.5));
		mMaxHS = mHS;
		mHullDefense = floor(log2(mLevel) * 25 + mBaseHullDefense);
		mRangeAttack = floor(log2(mLevel) * 28 + mBaseRangeAttack);
		mMeleeAttack = floor(log2(mLevel) * 25 + mBaseMeleeAttack);
		mAccuracy = floor(log2(mLevel) * 4.5 + mBaseAccuracy);
		mEvasion = floor(log2(mLevel) * 7 + mBaseEvasion);
		mLuck = floor(log2(mLevel) * 6 + mBaseLuck);
		mCrit = floor(log2(mLevel) * 1.3 + mBaseCrit);
		break;
	case FLAG_SHIP_CLASS:
		mExp = mBaseExp * (mLevel ^ 2);
		mTP = floor(log2(mLevel) * 2.2 + mBaseTP);
		mHS = floor(mBaseHS * pow(mLevel, 1.46));
		mMaxHS = mHS;
		mHullDefense = floor(log2(mLevel) * 28 + mBaseHullDefense);
		mRangeAttack = floor(log2(mLevel) * 38 + mBaseRangeAttack);
		mMeleeAttack = floor(log2(mLevel) * 30 + mBaseMeleeAttack);
		mAccuracy = floor(log2(mLevel) * 4.5 + mBaseAccuracy);
		mEvasion = floor(log2(mLevel) * 3 + mBaseEvasion);
		mLuck = floor(log2(mLevel) * 1.3 + mBaseLuck);
		mCrit = floor(log2(mLevel) * 2 + mBaseCrit);
		break;

	}
}

int DPhoenix::CharacterClass::MeleeAttack(CharacterClass* _target)
{
	std::srand(time(0));

	float rng1 = rand() % 30 + 1;
	float rng2 = rand() % 100 + 1;

	float dmg = mMeleeAttack * (rng1 * 0.1) - (_target->mHullDefense / rng1);

	if (dmg < 0)
		return 0;
	else
		dmg *= 3;

	return std::round(dmg);
}

int DPhoenix::CharacterClass::WeaponAttack(CharacterClass* _target, float _dmgmodifier, float _accmodifer, float _critmodifer, float _coverDmg, bool _isPlayerTeam)
{
	std::srand(time(0));

	int rng1 = rand() % 30 + 1;
	int rng2 = rand() % 100 + 1;
	int rng3 = rand() % 3 + 1;

	//check for if one of the two teams has lit the beacons provide buff base on that beacon to that team
	if ( _isPlayerTeam)
	{
		_accmodifer + 10.0f;
	}
	else if (_isPlayerTeam)
	{
		_critmodifer + 10.0f;
	}

	if ( _isPlayerTeam == false)
	{
		_accmodifer + 10.0f;
	}
	else if (_isPlayerTeam == false)
	{
		_critmodifer + 10.0f;
	}

	float accAdd = 0; // Modifer for accuary for  flagship weapon
	float critAdd = 0; //modifer for crit weapones
	float dmgAdd = 0; // damage modifer

	if (mAccuracy + mLuck + accAdd > _target->mEvasion + _target->mLuck + rng2)
		return -1; // indicates miss

	float rangeAttack = mRangeAttack * _dmgmodifier;

	float dmg = rangeAttack * (rng1 * 0.1) - (_target->mHullDefense / rng1);

	if (dmg < 0)
		return 0;
	else
		dmg *= 3;
	if (mCrit + mLuck + critAdd > rng2)
	{
		dmg * 1.5;
	}
	

	return std::round(dmg);
}

void DPhoenix::CharacterClass::Update(float dt)
{
	//lots of logic to go here
	switch (mLifeState)
	{
	case CH_OK_LIFESTATE:

		switch (mTurnState)
		{
		case CH_ACTIVE_TURNSTATE:
			switch (mMoveState)
			{
			case CH_PICKAC_MOVESTATE:
				mModelInstance->Model->Animator->SetAnimation(IDLE_ANIMATION);

				if (mModelInstance->mInstanceAnimator->GetAnimationIndex() != IDLE_ANIMATION)
				{
					//set to dile aniamion
					mModelInstance->mInstanceAnimator->SetAnimation(IDLE_ANIMATION);
					mModelInstance->SetTimePos(0);
					mModelInstance->SetLoopClips(true);

				}
				break;
			case CH_MOVERT_MOVESTATE:
				if (!mAudioMgr->GetSound("Walk")->IsPlaying())
				{
					mAudioMgr->GetSound("Walk")->Play(true);
				}

				if (mModelInstance->mInstanceAnimator->GetAnimationIndex() != WALK_ANIMATION)
				{
					mModelInstance->mInstanceAnimator->SetAnimation(WALK_ANIMATION);
					mModelInstance->SetTimePos(0);
					mModelInstance->SetLoopClips(true);
				}

				//the goal is the ifrst part of the happy path
				XMFLOAT3 goal = mHappyPath[0]->mPosition;
				//not taking into account y value so just x and z
				goal.y = mModelInstance->mPosition.y;

				//coversions for cal
				//get direction to goal
				XMVECTOR goalPosVec = XMLoadFloat3(&goal);
				XMVECTOR modelPosVec = XMLoadFloat3(&mModelInstance->mPosition);
				XMVECTOR pointAtGoalVec = XMVectorSubtract(goalPosVec, modelPosVec);
				//cal dist to post
				XMVECTOR goalDistanceVec = pointAtGoalVec;
				XMFLOAT3 goalDistance;
				XMStoreFloat3(&goalDistance, XMVector3Length(goalDistanceVec));
				//normalise for dist
				pointAtGoalVec = XMVector3Normalize(pointAtGoalVec);
				//store as float3
				XMFLOAT3 moveDir;
				XMStoreFloat3(&moveDir, pointAtGoalVec);

				//set forward vec to model
				mModelInstance->mForwardVector = moveDir;

				//update the movment towards the goal
				mModelInstance->mPosition.x += moveDir.x * 30.0f * dt;
				mModelInstance->mPosition.y += moveDir.y * 30.0f * dt;
				mModelInstance->mPosition.z += moveDir.z * 30.0f * dt;

				//i we are with 5.0f of the goal
				if (goalDistance.x < 5.0f)
				{
					//remove th first elemt of the ppayy path
					mHappyPath.erase(mHappyPath.begin());

					//uf no happy path left, we need to go into pick action movestate
					if (mHappyPath.size() == 0)
					{
						mModelInstance->Model->Animator->SetAnimation(IDLE_ANIMATION);
						mModelInstance->SetTimePos(0);
						mModelInstance->SetLoopClips(true);
						mMoveState = CH_PICKAC_MOVESTATE;
					}
					if (mAudioMgr->GetSound("Walk")->IsPlaying())
					{
						mAudioMgr->GetSound("Walk")->Stop();
						mAudioMgr->GetSound("Walk")->SetPosition(0);
					}
				}

				break;

			}
			break;
		}
		break;

	case CH_HURT_LIFESTATE:
	{
		mLifeStateTimer.Tick();
		if (!mAudioMgr->GetSound("Hurt")->IsPlaying())
		{
			mAudioMgr->GetSound("Hurt")->Play(true);

		}

		if (mModelInstance->mInstanceAnimator->GetAnimationIndex() != HURT_ANIMATION)
		{
			//set to hurt animation
			mModelInstance->mInstanceAnimator->SetAnimation(HURT_ANIMATION);
			mModelInstance->SetTimePos(0);
			mModelInstance->SetLoopClips(false);
		}

		if (mLifeStateTimer.TotalTime() >= 1.0f)
		{
			mLifeState = CH_OK_LIFESTATE;
			//set to idle
			mModelInstance->mInstanceAnimator->SetAnimation(IDLE_ANIMATION);
			mModelInstance->SetTimePos(0);
			mModelInstance->SetLoopClips(true);
			mLifeStateTimer.Reset();

			mAudioMgr->GetSound("Hurt")->Stop();
			mAudioMgr->GetSound("Hurt")->SetPosition(0);
			
		}

		

		

		
	}
	break;
	case CH_DYING_LIFESTATE:
	{
		mLifeStateTimer.Tick();

		if (!mAudioMgr->GetSound("Hurt")->IsPlaying())
		{
			mAudioMgr->GetSound("Hurt")->Play(true);

		}

		if (mModelInstance->mInstanceAnimator->GetAnimationIndex() != DYING_ANIMATION)
		{
			//set to dying aniamtion
			mModelInstance->mInstanceAnimator->SetAnimation(DYING_ANIMATION);
			mModelInstance->SetTimePos(0);
			mModelInstance->SetLoopClips(false);
		}

		if (mLifeStateTimer.TotalTime() >= 1.0f)
		{
			mLifeState = CH_DEAD_LIFESTATE;
			mModelInstance->mInstanceAnimator->SetAnimation(DEAD_ANIMATION);
			mModelInstance->SetTimePos(0);
			mModelInstance->SetLoopClips(true);
			mLifeStateTimer.Reset();

			mAudioMgr->GetSound("Hurt")->Stop();
			mAudioMgr->GetSound("Hurt")->SetPosition(0);
			mModelInstance->mPosition.x = 120.0f;
			mModelInstance->mPosition.y = 0.0f;
			mModelInstance->mPosition.z = 580.0f;
			

			
		}
		
	}
	break;
	}
	mModelInstance->Update(dt, true);
}

void DPhoenix::CharacterClass::TakeDamage(int dmg)
{
	mHS -= dmg;
	if (mHS <= 0)
	{
		mHS = 0;
		mLifeState = CH_DYING_LIFESTATE;
	}
	else
	{
		mLifeState = CH_HURT_LIFESTATE;
	}

	mLifeStateTimer.Reset();
}