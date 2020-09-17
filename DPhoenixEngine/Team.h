#pragma once
#include "D3DUtil.h"
#include "CharacterClass.h"
#include "LITSMap.h"
#include "Beacon.h"

namespace DPhoenix
{
	enum TeamStates
	{
		TM_OK_TEAMSTATE,
		TM_DYING_TEAMSTATE,
		TM_DEAD_TEAMSTATE
	};

	enum TeamTypes
	{
		PLAYER_TEAM,
		ENEMY_TEAM
	};

	class Beacon;

	class Team
	{
		//look at me breaking encaplusation again
		//if you want to fix tihs, points make prizes
	public:

		//members vars---------------------------------------------------
		std::vector<CharacterClass*> mTeamMembers;
		int mTPPool;
		TeamStates mTeamState;
		int mSaves;
		int mTeamNumber;

		//ui added members
		int mMaxTPPool;
		int mTPTurnSnapshot;
		int mCurrentMember;
		int mTurnsLeft;
		std::string mStatustext;
		TeamTypes mTeamType;
		bool mHeal;//check if on heal sqaure
		//actions added members
		std::vector<AvailableActions> mAvailableActions;
		std::vector<std::string> mActionstext;
		bool mNewActionselectFlag;

		//add it members
		//the target selected for the current emebers turn
		MapBlock* mSelectedTarget;
		//there might be mofre for the class yet
		//right now its a usefol place for oter mechanices

		//member mthods
		//constrict
		Team();
		~Team();

		//UI added methods
		void CalculateTPPool();
		void ResetTeamTurn();

		void NextMember();
		void PrevMember();
		void SelectMember(int index);

		//actions added methods
		void CheckAvailableActions(std::vector<std::vector<MapBlock*>>& _map, int currentCol, int currentRow);
		void CheckSelectedAction(int index, LITSMap* map);

		void EndCurrentTurn(LITSMap* map);

		bool CheckTeamState();

		//standard methods for game loop
		//we might not use these
		void Update(float dt, LITSMap* map);
		//void Draw();

		//AI methods
		void DetermineAIStatus(LITSMap* map, std::vector<Beacon*>& beaconVec);
		void DetermineMovement(LITSMap* map, std::vector<Beacon*>& beaconVec,
			Team* opposingTeam, std::vector<PrimitiveInstance*>& happyPath,
			PrimitiveInstance* selectionBox);
		void DetermineAction(LITSMap* map, std::vector<Beacon*>& beaconVec,
			Team* opposingTeam,
			std::vector<PrimitiveInstance*>& targets, PrimitiveInstance* targetHighlight);


	};


}