#include "WeaponMesh.h"

DPhoenix::WeaponMesh::WeaponMesh(CharacterClass* attacker, XMFLOAT3 direction, XMFLOAT3 start,
	AvailableActions action, TeamTypes teamType, Team* playerTeam,
	Team* enemyTeam, TextureMgr* texMgr, ID3D11Device* d3dDevice,
	GeometryGenerator::MeshData* sphere)

{

	start.y = 20.0f;
	//sphere starts small - as it scale the so will halfsize
	Material* materialShiny = new Material();
	materialShiny->Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	materialShiny->Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	materialShiny->Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f);
	materialShiny->Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	//imitial object creation - mai por sep up based on weapon / spell
	mWeaponMeshInstance = new PrimitiveInstance();
	//point light porpeties - update wit diffuse color base on weapon / spell
	mRadiance = new PointLight();
	mRadiance->Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mRadiance->Specular = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	mRadiance->Att = XMFLOAT3(1.0f, 0.1f, 0.02f);
	mRadiance->Range = 75.0f;

	//singletons
	mTexMgr = texMgr;
	md3dDevice = d3dDevice;

	//init weapon prop
	mScale = 1.0f;
	mDistanceTravelled = 0.0f;
	mAttacker = attacker;
	mAction = action;
	mWeaponStage = SPAWN_MESH_WMS;

	//team propties
	mTeamType = teamType;
	mPlayerTeam = playerTeam;
	mEnemyTeam = enemyTeam;

	//set the propties for each acton types
	//genreally weapon travl faster but agic stonrger
	//mostly the same code for each but with value change
	switch (action)
	{
	
	case TORPEDO_ACTION:
		mCoverDmg = 1.1f;
		mWeaponModifier = 1.1f;
		mWeaponType = WEAPON_WT;

		mMaxScale = 8.0f;
		mMaxDistance = 140.0f;

		if (mTeamType == PLAYER_TEAM)
			mPlayerTeam->mTPPool -= 4;
		else
			mEnemyTeam->mTPPool -= 4;

		//set diffuse color 
		mRadiance->Diffuse = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);

		mWeaponMeshInstance->LoadLitTexInstance(md3dDevice, "Textures\\Weapons\\Torpedo_cm.jpg", sphere, mTexMgr);
		mWeaponMeshInstance->mMaterial = materialShiny;
		mWeaponMeshInstance->mNormalMap = mTexMgr->CreateTexture("Textures\\Weapons\\Torpedo_cm.jpg");
		mWeaponMeshInstance->mHalfSizes = XMFLOAT3(0.5f, 0.5f, 0.5f);
		mWeaponMeshInstance->mEntityType = ENTITY_WEAPON_MESH;
		mWeaponMeshInstance->mForwardVector = direction;

		break;
	case SUBCANNON_ACTION:
		mCoverDmg = 0.4f;
		mWeaponModifier = 1.1f;
		mCritModifier = 0.1f;
		mWeaponType = WEAPON_WT;

		mMaxScale = 8.0f;
		mMaxDistance = 60.0f;

		if (mTeamType == PLAYER_TEAM)
			mPlayerTeam->mTPPool -= 4;
		else
			mEnemyTeam->mTPPool -= 4;

		//set diffuse color 
		mRadiance->Diffuse = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);

		mWeaponMeshInstance->LoadLitTexInstance(md3dDevice, "Textures\\Weapons\\SubCannon_cm.png", sphere, mTexMgr);
		mWeaponMeshInstance->mMaterial = materialShiny;
		mWeaponMeshInstance->mNormalMap = mTexMgr->CreateTexture("Textures\\Weapons\\SubCannon_nm.png");
		mWeaponMeshInstance->mHalfSizes = XMFLOAT3(0.5f, 0.5f, 0.5f);
		mWeaponMeshInstance->mEntityType = ENTITY_WEAPON_MESH;
		mWeaponMeshInstance->mForwardVector = direction;
		break;
	case HEAVYCANNON_ACTION:
		mCoverDmg = 0.5f;
		mWeaponModifier = 1.5f;
		mWeaponType = WEAPON_WT;

		mMaxScale = 8.0f;
		mMaxDistance = 60.0f;

		if (mTeamType == PLAYER_TEAM)
			mPlayerTeam->mTPPool -= 6;
		else
			mEnemyTeam->mTPPool -= 6;

		//set diffuse color 
		mRadiance->Diffuse = XMFLOAT4(0.25f, 0.25f, 0.25f, 1.0f);

		mWeaponMeshInstance->LoadLitTexInstance(md3dDevice, "Textures\\Weapons\\HeavyCannon_cm.jpg", sphere, mTexMgr);
		mWeaponMeshInstance->mMaterial = materialShiny;
		mWeaponMeshInstance->mNormalMap = mTexMgr->CreateTexture("Textures\\Weapons\\HeavyCannon_nm.jpg");
		mWeaponMeshInstance->mHalfSizes = XMFLOAT3(0.5f, 0.5f, 0.5f);
		mWeaponMeshInstance->mEntityType = ENTITY_WEAPON_MESH;
		mWeaponMeshInstance->mForwardVector = direction;
		break;
	case QUICK_FIRIING_ARTILLERY_ACTION:
		mCoverDmg = 0.5;
		mWeaponModifier = 1.1f;
		mAccModifer = 0.1f;
		mWeaponType = WEAPON_WT;

		mMaxScale = 8.0f;
		mMaxDistance = 60.0f;

		if (mTeamType == PLAYER_TEAM)
			mPlayerTeam->mTPPool -= 4;
		else
			mEnemyTeam->mTPPool -= 4;

		//set diffuse color 
		mRadiance->Diffuse = XMFLOAT4(1.0f, 0.25f, 0.0f, 1.0f);

		mWeaponMeshInstance->LoadLitTexInstance(md3dDevice, "Textures\\Weapons\\QuickFiringArtillery_cm", sphere, mTexMgr);
		mWeaponMeshInstance->mMaterial = materialShiny;
		mWeaponMeshInstance->mNormalMap = mTexMgr->CreateTexture("Textures\\Weapons\\QuickFiringArtillery_nm");
		mWeaponMeshInstance->mHalfSizes = XMFLOAT3(0.5f, 0.5f, 0.5f);
		mWeaponMeshInstance->mEntityType = ENTITY_WEAPON_MESH;
		mWeaponMeshInstance->mForwardVector = direction;
		break;
	case BARRAGE_ACTION:
		mCoverDmg = 0.5;
		mWeaponModifier = 1.5f;
		mWeaponType = WEAPON_WT;

		mMaxScale = 8.0f;
		mMaxDistance = 140.0f;

		if (mTeamType == PLAYER_TEAM)
			mPlayerTeam->mTPPool -= 5;
		else
			mEnemyTeam->mTPPool -= 5;

		//set diffuse color 
		mRadiance->Diffuse = XMFLOAT4(0.25f, 1.0f, 0.25f, 1.0f);

		mWeaponMeshInstance->LoadLitTexInstance(md3dDevice, "Textures\\Weapons\\Barrage_cm.png", sphere, mTexMgr);
		mWeaponMeshInstance->mMaterial = materialShiny;
		mWeaponMeshInstance->mNormalMap = mTexMgr->CreateTexture("Textures\\Weapons\\Barrage_nm.png");
		mWeaponMeshInstance->mHalfSizes = XMFLOAT3(0.5f, 0.5f, 0.5f);
		mWeaponMeshInstance->mEntityType = ENTITY_WEAPON_MESH;
		mWeaponMeshInstance->mForwardVector = direction;
		break;
	case ALL_WEAPONS_FIRE_ACTION:
		mCoverDmg = 0.5;
		mWeaponModifier = 1.1f * 1.1f * 1.1;
		mAccModifer = -0.2f;
		mWeaponType = WEAPON_WT;

		mMaxScale = 8.0f;
		mMaxDistance = 140.0f;

		if (mTeamType == PLAYER_TEAM)
			mPlayerTeam->mTPPool -= 7;
		else
			mEnemyTeam->mTPPool -= 7;

		//set diffuse color 
		mRadiance->Diffuse = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);

		mWeaponMeshInstance->LoadLitTexInstance(md3dDevice, "Textures\\Weapons\\AllWeaponsFire_cm.png", sphere, mTexMgr);
		mWeaponMeshInstance->mMaterial = materialShiny;
		mWeaponMeshInstance->mNormalMap = mTexMgr->CreateTexture("Textures\\Weapons\\AllWeaponsFire_nm.png");
		mWeaponMeshInstance->mHalfSizes = XMFLOAT3(0.5f, 0.5f, 0.5f);
		mWeaponMeshInstance->mEntityType = ENTITY_WEAPON_MESH;
		mWeaponMeshInstance->mForwardVector = direction;
		break;
	

	}

	XMFLOAT3 mStartPos;
	//assuming the sphere has a radius of 1 to beign with, postiong along forward vec,
	//for half the eentual max scale mean it should spawn in front of char
	//without too much clippong
	mStartPos.x = start.x + mWeaponMeshInstance->mForwardVector.x * (mMaxScale / 2.0f);
	mStartPos.y = start.y + mWeaponMeshInstance->mForwardVector.y * (mMaxScale / 2.0f);
	mStartPos.z = start.z + mWeaponMeshInstance->mForwardVector.z * (mMaxScale / 2.0f);

	//inital pos but uplaod in update
	mRadiance->Position = mStartPos;
	mWeaponMeshInstance->mPosition = mStartPos;
	mWeaponMeshInstance->mPrevPosition = mStartPos;

}

DPhoenix::WeaponMesh::~WeaponMesh()
{

}

void DPhoenix::WeaponMesh::Update(float dt)
{
	//tick stage timer
	mStageTimer.Tick();
	//set intial dmg mod
	float dmgOVerAllModifer = 1.0f;

	// for beacon buff
	bool mIsPlayerTeam = false;
	//keep rotating the esh
	mWeaponMeshInstance->mRotation.x += 7.0f * dt;
	mWeaponMeshInstance->mRotation.y += 7.0f * dt;
	mWeaponMeshInstance->mRotation.z += 7.0f * dt;
	
	//check each stage to perform updates
	switch (mWeaponStage)
	{
	case SPAWN_MESH_WMS:
		//at this tsage the projectile spwans and get alrgetr
		//this calc mean it shoud be apporx o.5 seconds beofre max scale
		mScale += 2.0f * mMaxScale * dt;

		//bound to max scale
		if (mScale >= mMaxScale)
		{
			mScale = mMaxScale;
			//update stage and collision protioes
			mWeaponStage = FIRING_MESH_WMS;
			mWeaponMeshInstance->mCollidable = true;
		}

		//update the sacle and falg size for dispalce and coolision
		mWeaponMeshInstance->mScale.x = mScale;
		mWeaponMeshInstance->mScale.y = mScale;
		mWeaponMeshInstance->mScale.z = mScale;

		mWeaponMeshInstance->mHalfSizes.x = mScale * 0.5f;
		mWeaponMeshInstance->mHalfSizes.y = mScale * 0.5f;
		mWeaponMeshInstance->mHalfSizes.z = mScale * 0.5f;

		mWeaponMeshInstance->Update(dt, true);
		break;
	case FIRING_MESH_WMS:
		// at this point the main demo shod add the weapnmesh as an entity for collision
		//we need to check tha tcollidie enityi is tore so it only vcollides once
		//taht way we arent adding mdoifer. damage serveral times

		//then engine collison method will only add to the collided entties vec
		//once per collison - hence we hst need a set of flags to check ifwe have delt collision
		mHasCollided.resize(mWeaponMeshInstance->mCollidedEntities.size());

		for (int i = 0; i < mWeaponMeshInstance->mCollidedEntities.size(); i++)
		{
			if (!mHasCollided[i])
			{
				//set falg to true
				mHasCollided[i] = true;

				//cover collision
				if (mWeaponMeshInstance->mCollidedEntities[i]->mEntityType == ENTITY_COVER_MESH)
				{
					//update the damge mod
					dmgOVerAllModifer *= mCoverDmg;
					//add billboard sprite
					mBillboards.push_back(new DPhoenix::BillboardSprite());
					mBillboards.back()->Load("Textures\\Impact\\Bang.png", mTexMgr, 15.0f, 15.0f, md3dDevice);
					//initial pos is the current pos
					mBillboards.back()->mPosition = mWeaponMeshInstance->mCollidedEntities[i]->mPosition;
					mBillboards.back()->mPosition.y = mWeaponMeshInstance->mPosition.y;
					//postio backwards along forward vec so facing back at character in font of target
					mBillboards.back()->mPosition.x -= (mWeaponMeshInstance->mForwardVector.x *
						(mWeaponMeshInstance->mCollidedEntities[i]->mHalfSizes.x + 5.0f));
					mBillboards.back()->mPosition.z -= (mWeaponMeshInstance->mForwardVector.z *
						(mWeaponMeshInstance->mCollidedEntities[i]->mHalfSizes.z + 5.0f));
					//add fx
				}

				if (mTeamType == PLAYER_TEAM && mWeaponMeshInstance->mCollidedEntities[i]->mEntityType == ENTITY_ENEMY_MESH)
				{
					mIsPlayerTeam = true;
					//pointer to victim
					CharacterClass* victim;
					
					//loop thpugh the eemy team and their collision to match id to weapppn line
					for (int j = 0; j < mEnemyTeam->mTeamMembers.size(); j++)
					{
						if (mEnemyTeam->mTeamMembers[j]->mModelInstance->mId ==
							mWeaponMeshInstance->mCollidedEntities[i]->mId)
						{
							victim = mEnemyTeam->mTeamMembers[j];
						}
					}

					//based on weapon type, calulate the damge
					if (mWeaponType == WEAPON_WT || mWeaponType == MAGIC_WT)
						mDmgValues.push_back(mAttacker->WeaponAttack(victim, mWeaponModifier, mAccModifer, mCritModifier, dmgOVerAllModifer, mIsPlayerTeam));
					
					//if the last attack was not a miss
					if (mDmgValues.back() > -1)
					{
						victim->TakeDamage(mDmgValues.back());
						// add billboard sprite bang
						mBillboards.push_back(new DPhoenix::BillboardSprite());
						mBillboards.back()->LoadBS("Textures\\Impact\\Bang.png", mTexMgr, 15.0f, 15.0f, md3dDevice);
						mBillboards.back()->mPosition = mWeaponMeshInstance->mCollidedEntities[i]->mPosition;
						mBillboards.back()->mPosition.y = mWeaponMeshInstance->mPosition.y;
						//positioning backawrds along forward vector so facing back at characte rin front of target
						mBillboards.back()->mPosition.x -= (mWeaponMeshInstance->mForwardVector.x *
							(mWeaponMeshInstance->mCollidedEntities[i]->mHalfSizes.x + 5.0f));
						mBillboards.back()->mPosition.z -= (mWeaponMeshInstance->mForwardVector.z *
							(mWeaponMeshInstance->mCollidedEntities[i]->mHalfSizes.z + 5.0f));
					}
					else
					{
						//miss . smaoke animation
					}

					//position the damage value for dispay
					mDmgPosition.push_back(mWeaponMeshInstance->mCollidedEntities[i]->mPosition);

					//if the tyoe is weapon then move to next stage
					if (mWeaponType == WEAPON_WT)
					{
						mWeaponStage = FADE_OUT_WMS;
						mWeaponMeshInstance->mCollidable = false;
					}
				}

				//enemy to player collision 
				if (mTeamType == ENEMY_TEAM && mWeaponMeshInstance->mCollidedEntities[i]->mEntityType == ENTITY_PLAYER_MESH)
				{
					mIsPlayerTeam = false;
					//pointer to victim
					CharacterClass* victim;

					//loop thpugh the eemy team and their collision to match id to weapppn line
					for (int j = 0; j < mPlayerTeam->mTeamMembers.size(); j++)
					{
						if (mPlayerTeam->mTeamMembers[j]->mModelInstance->mId ==
							mWeaponMeshInstance->mCollidedEntities[i]->mId)
						{
							victim = mPlayerTeam->mTeamMembers[j];
						}
					}

					//based on weapon type, calulate the damge
					if (mWeaponType == WEAPON_WT || mWeaponType == MAGIC_WT)
						mDmgValues.push_back(mAttacker->WeaponAttack(victim, mWeaponModifier, 0, 0, dmgOVerAllModifer, mIsPlayerTeam));

					//if the last attack was not a miss
					if (mDmgValues.back() > -1)
					{
						victim->TakeDamage(mDmgValues.back());
						// add billboard sprite bang
						mBillboards.push_back(new DPhoenix::BillboardSprite());
						mBillboards.back()->LoadBS("Textures\\Impact\\Bang.png", mTexMgr, 15.0f, 15.0f, md3dDevice);
						mBillboards.back()->mPosition = mWeaponMeshInstance->mCollidedEntities[i]->mPosition;
						mBillboards.back()->mPosition.y = mWeaponMeshInstance->mPosition.y;
						//positioning backawrds along forward vector so facing back at characte rin front of target
						mBillboards.back()->mPosition.x -= (mWeaponMeshInstance->mForwardVector.x *
							(mWeaponMeshInstance->mCollidedEntities[i]->mHalfSizes.x + 5.0f));
						mBillboards.back()->mPosition.z -= (mWeaponMeshInstance->mForwardVector.z *
							(mWeaponMeshInstance->mCollidedEntities[i]->mHalfSizes.z + 5.0f));
					}
					else
					{
						//miss . smaoke animation
					}

					//position the damage value for dispay
					mDmgPosition.push_back(mWeaponMeshInstance->mCollidedEntities[i]->mPosition);

					//if the tyoe is weapon then move to next stage
					if (mWeaponType == WEAPON_WT)
					{
						mWeaponStage = FADE_OUT_WMS;
						mWeaponMeshInstance->mCollidable = false;
					}
				}

				//wall collision
				if (mWeaponMeshInstance->mCollidedEntities[i]->mEntityType == ENTITY_WALL_MESH)
				{

					// add billboard sprite bang
					mBillboards.push_back(new DPhoenix::BillboardSprite());
					mBillboards.back()->LoadBS("Textures\\Impact\\Bang.png", mTexMgr, 15.0f, 15.0f, md3dDevice);
					mBillboards.back()->mPosition = mWeaponMeshInstance->mCollidedEntities[i]->mPosition;
					mBillboards.back()->mPosition.y = mWeaponMeshInstance->mPosition.y;
					//positioning backawrds along forward vector so facing back at characte rin front of target
					mBillboards.back()->mPosition.x -= (mWeaponMeshInstance->mForwardVector.x *
						(mWeaponMeshInstance->mCollidedEntities[i]->mHalfSizes.x + 5.0f));
					mBillboards.back()->mPosition.z -= (mWeaponMeshInstance->mForwardVector.z *
						(mWeaponMeshInstance->mCollidedEntities[i]->mHalfSizes.z + 5.0f));

					//move to next stage and unset collision
					mWeaponStage = FADE_OUT_WMS;
					mWeaponMeshInstance->mCollidable = false;

				}
			}
		}

		//update distance travelled
		mDistanceTravelled += 100.0f * dt;

		//if greater thatn max distance, move to next stage and unset collidavke
		if (mDistanceTravelled >= mMaxDistance)
		{
			mDistanceTravelled = mMaxDistance;
			mWeaponStage = FADE_OUT_WMS;
			mWeaponMeshInstance->mCollidable = false;
		}

		//update position 
		mWeaponMeshInstance->mRelativeVelocity.z = 100.0f;
		mWeaponMeshInstance->Update(dt, true);

		//loop thorugh and update bill baords
		for (int i = 0; i < mBillboards.size(); i++)
		{
			mBillboards[i]->UpdateBS(dt);
		}
		//move point ight with mesh
		mRadiance->Position = mWeaponMeshInstance->mPosition;

		//loop though and update dmg positions to rise up over time
		for (int i = 0; i < mDmgPosition.size(); i++)
		{
			mDmgPosition[i].y += 1.0f * dt;
		}
		break;
	case FADE_OUT_WMS:
		//shink over time
		mScale -= 4.0f * mMaxScale * dt;

		//apply sacle and halfsize values
		mWeaponMeshInstance->mScale.x = mScale;
		mWeaponMeshInstance->mScale.y = mScale;
		mWeaponMeshInstance->mScale.z = mScale;

		mWeaponMeshInstance->mHalfSizes.x = mScale * 0.5f;
		mWeaponMeshInstance->mHalfSizes.y = mScale * 0.5f;
		mWeaponMeshInstance->mHalfSizes.z = mScale * 0.5f;

		//st to still
		mWeaponMeshInstance->mRelativeVelocity.z = 0.0f;
		mWeaponMeshInstance->Update(dt, true);

		//loop thrpugh abd update billboards
		for (int i = 0; i < mBillboards.size(); i++)
		{
			mBillboards[i]->UpdateBS(dt);
		}
		//loo thpogh ad update dmg pos to rise up over time
		for (int i = 0; i < mDmgPosition.size(); i++)
		{
			mDmgPosition[i].y += 1.0f * dt;
		}

		if (mScale <= 1.0f)
		{
			mScale = 1.0f;
			mWeaponStage = COMPLETE_WMS;
		}

		break;
	case COMPLETE_WMS:
		//falg for main gamge logic to move
		break;

	}


}