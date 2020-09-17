#pragma once
#include "D3DUtil.h"


namespace DPhoenix
{

	//this will be used tod etermine stat calulations, model loading
	//avaiable acrions, battle calualtions etc
	enum CharacterClasses
	{
		FLAG_SHIP_CLASS,
		BRUSIER_SHIP_CLASS,
		CORVETTE_SHIP_CLASS,
		CRUSIER_SHIP_CLASS
		
	};

	//governs animations and aviable update logic
	enum LifeStates
	{
		CH_OK_LIFESTATE,
		CH_HURT_LIFESTATE,
		CH_DYING_LIFESTATE,
		CH_DEAD_LIFESTATE
	};

	//govern the trun based system
	enum TurnStates
	{
		CH_WAIT_TURNSTATE,
		CH_ACTIVE_TURNSTATE,
		CH_COMP_TURNSTATE
	};

	enum MoveStates
	{
		CH_PICKRT_MOVESTATE,
		CH_MOVERT_MOVESTATE,
		CH_PICKAC_MOVESTATE,
		CH_DOAC_MOVESTATE
	};

	enum CharacterAnimations
	{
		IDLE_ANIMATION,
		DANCE_ANIMATION,
		MELEE_ANIMATION,
		WALK_ANIMATION,
		MAGIC_ANIMATION,
		WEAPON_ANIMATION,
		HURT_ANIMATION,
		DYING_ANIMATION,
		DEAD_ANIMATION

	};

	enum AvailableActions
	{
		HIT_ACTION,
		CANNON_ACTION,
		TORPEDO_ACTION,
		SUBCANNON_ACTION,
		HEAVYCANNON_ACTION,
		QUICK_FIRIING_ARTILLERY_ACTION,
		BRACE_ACTION,
		CHARGE_ACTION,
		SNIPE_ACTION,
		BARRAGE_ACTION,
		COMMAND_ACTION,
		ALL_WEAPONS_FIRE_ACTION,
		EMERGENCY_REPAIR_ACTION,
		HOLD_STILL_ACTION,
		LIGHT_BEACON_ACTION,
		NO_ACTION

	};
	
	class CharacterClass
	{
		//breaking encspulation
		//really all tese proptise should have getters and setters
		//points for fixes
	private:
		int mLevel;
		int mBaseExp, mExp;
		int mBaseTP, mTP;
		int mBaseHS, mHS, mMaxHS;
		int mBaseHullDefense, mHullDefense;
		int mBaseRangeAttack, mRangeAttack;
		int mBaseMeleeAttack, mMeleeAttack;
		int mBaseEvasion, mEvasion;
		int mBaseAccuracy, mAccuracy;
		int mBaseCrit, mCrit;
		int mBaseLuck, mLuck;


	public:
		//member vars

		//stats --------------------------------------
		//Setters
		void SetLevel(int level)
		{
			mLevel = level;
		};
		int GetLevel()
		{
			return mLevel;
		};

		void SetExp(int baseExp, int exp)
		{
			mBaseExp = baseExp;
			mExp = exp;
		};
		int GetExp()
		{
			return mBaseExp, mExp;
		}

		void SetTP(int baseTP, int TP)
		{
			mBaseTP = baseTP;
			mTP = TP;
		}
		int GetTP()
		{
			return mBaseTP, mTP;
		}

		void SetHSMax(int maxHS)
		{
			
			mMaxHS = maxHS;
		}

		int GetHSMax()
		{
			return  mMaxHS;
		}

		void SetHS(int HS)
		{

			mHS = HS;
	
		}


		int GetHS()
		{
			return  mHS;
		}

		int GetHSBase()
		{
			return mBaseHS;
		}

		void SetHSBase(int baseHS)
		{
			mBaseHS = baseHS;
		}

		void SetHullDefence(int baseHullDefense, int hullDefense)
		{
			mBaseHullDefense = baseHullDefense;
			mHullDefense = hullDefense;

		}

		int GetHullDefense()
		{
			return mBaseHullDefense, mHullDefense;
		}

		void SetRangeAttack(int baseRangeAttack, int rangeAttack)
		{
			mBaseRangeAttack = baseRangeAttack;
			mRangeAttack = rangeAttack;
		}

		int GetRangeAttack()
		{
			return mBaseRangeAttack, mRangeAttack;
		}
		void SetMeleeAttack(int baseMeleeAttack, int MeleeAttack)
		{
			mBaseMeleeAttack = baseMeleeAttack;
			mMeleeAttack = MeleeAttack;
		}

		int GetMeleeAttack()
		{
			return mBaseMeleeAttack, mMeleeAttack;
		}

		void SetEvasion(int baseEvasion, int evasion)
		{
			mBaseEvasion = baseEvasion;
			mEvasion = evasion;
		}

		int GetEvasion()
		{
			return mBaseEvasion, mEvasion;
		}

		void SetAccuracy(int baseAccuracy, int accuracy)
		{
			mBaseAccuracy = accuracy;
			mAccuracy = accuracy;
		}

		int GetAccuracy()
		{
			return mBaseAccuracy, mAccuracy;
		}

		void SetCrit(int baseCrit, int crit)
		{
			mBaseCrit= baseCrit;
			mCrit= crit;
		}

		int GetCrit()
		{
			return mCrit, mBaseCrit;
		}

		void SetLuck(int baseLuck, int Luck)
		{
			mBaseLuck = baseLuck;
			mLuck = Luck;
		}

		int GetLuck()
		{
			return mBaseLuck, mLuck;
		}
		
		


		//character traits------------------------------
		CharacterClasses mClass;
		//actionsshould go here when determinded
		//modles should go here when determinded

		//models for charcters
		DPhoenix::SkinnedModel* mAnimModel;
		DPhoenix::SkinnedModelInstance* mModelInstance;

		LifeStates mLifeState;
		TurnStates mTurnState;
		MoveStates mMoveState;
		CharacterAnimations mAnimation;

		//pointer to main singletons / devices
		TextureMgr* mTexMgr;
		ID3D11Device* md3dDevice;
		AudioMgr* mAudioMgr;

		//for movment
		std::vector<PrimitiveInstance*> mHappyPath;

		//for actions
		AvailableActions mSelectedAction;
		GameTimer mLifeStateTimer;

		//for AI
		int mTargetBeaconId;


		//methods ----------------------------------------------
		CharacterClass(CharacterClasses _class, TextureMgr* _texMgr,
			ID3D11Device* _md3dDevice, AudioMgr* _audioMgr);
		//copy consruct
		CharacterClass(const CharacterClass &character);
		~CharacterClass();
		
		//main methods 
		//state growth / cals
		void SetBaseStats();
		void CalculateStats(int _level);
		//battle
		//the modifer releates to type of weapon/ magi
		//the coverdmg impies well figure out cover / wall collisions first
		int MeleeAttack(CharacterClass* _target);
		int WeaponAttack(CharacterClass* _target, float _dmgmodifier, float _accmodifer, float _critmodifer, float _coverDmg, bool);

		//logic / rendering
		void Update(float dt);
		//we likely to instead call te draw method from the link model in the main dmeo rendering method
		//void Draw();

		void TakeDamage(int dmg);
	};

 
}