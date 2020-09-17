#include "Team.h"

DPhoenix::Team::Team()
{
	mTeamState = TM_OK_TEAMSTATE;

	mTPPool = 0;
	mMaxTPPool = 0;
	mSaves = 3;
	mTeamType = PLAYER_TEAM;

	mCurrentMember = 0;
	mTurnsLeft = 4;

	mStatustext = "";

	//ono, magic number
	mActionstext.resize(15);

	mActionstext[HIT_ACTION] = "RAM (1TP)";
	mActionstext[CANNON_ACTION] = "CANNON (2TP)";
	mActionstext[TORPEDO_ACTION] = "TORPEDO (4TP)";
	mActionstext[SUBCANNON_ACTION] = "SUB CANNON (4TP)";
	mActionstext[HEAVYCANNON_ACTION] = "HEAVY CANNON (6TP)";
	mActionstext[QUICK_FIRIING_ARTILLERY_ACTION] = "Quick-Firing atillery (4TP)";
	mActionstext[BRACE_ACTION] = "BRACE (2TP)";
	mActionstext[CHARGE_ACTION] = "CHARGE(4TP)";
	mActionstext[BARRAGE_ACTION] = "BARRAGE (4TP)";
	mActionstext[SNIPE_ACTION] = "SNIPE (4TP)";
	mActionstext[COMMAND_ACTION] = "COMMAND (5TP)";
	mActionstext[ALL_WEAPONS_FIRE_ACTION] = "ALL WEAPONS FIRE (7TP)";
	mActionstext[EMERGENCY_REPAIR_ACTION] = "EMERGENCY REPAIR (3TP)";
	mActionstext[HOLD_STILL_ACTION] = "HOLD STILL";
	mActionstext[LIGHT_BEACON_ACTION] = "Light BEACON";

	mNewActionselectFlag = false;

}

DPhoenix::Team::~Team()
{

}

void DPhoenix::Team::Update(float dt, LITSMap* map)
{
	//need to update sp falg where necceseaty
	for (int i = 0; i < mTeamMembers.size(); i++)
	{
		//before updating movment ,reset the map block currently on to 
		//no special flag
		int col = map->GetColFromPosition(mTeamMembers[i]->mModelInstance->mPosition);
		int row = map->GetRowFromPosition(mTeamMembers[i]->mModelInstance->mPosition);
		map->mTiles[col][row]->mSpecialFlag = NO_SP_FLAG;

		//now update the team embers
		mTeamMembers[i]->Update(dt);

		//now get the col / row on the map to set flags as necessary
		 col = map->GetColFromPosition(mTeamMembers[i]->mModelInstance->mPosition);
		 row = map->GetRowFromPosition(mTeamMembers[i]->mModelInstance->mPosition);

		//player / enemy check - as long as still alive, need to set the sepical falg on cirrrent ti.es
		if (mTeamType == PLAYER_TEAM && mTeamMembers[i]->mLifeState != CH_DEAD_LIFESTATE)
			map->mTiles[col][row]->mSpecialFlag = PLAYER_SP_FLAG;

		if (mTeamType == ENEMY_TEAM && mTeamMembers[i]->mLifeState != CH_DEAD_LIFESTATE)
			map->mTiles[col][row]->mSpecialFlag = ENEMY_SP_FLAG;



		//based on curent movestate - update status messege
		switch (mTeamMembers[mCurrentMember]->mMoveState)
		{
		case CH_PICKRT_MOVESTATE:
			mStatustext = "Pick Route";
			if (mAvailableActions.size() > 0)
			{
				mAvailableActions.clear();
			}
			break;
		case CH_MOVERT_MOVESTATE:
			mStatustext = "Move Route";
			break;
		case CH_PICKAC_MOVESTATE:
			mStatustext = "Pick Action";
			if (mAvailableActions.size() < 1)
			{
				CheckAvailableActions(map->mTiles, col, row);
			}
			
			break;
		case CH_DOAC_MOVESTATE:
			mStatustext = "Do Action";
			break;
		}
	}
}

//method to calulate tp for team
//should be used at start of turn
void DPhoenix::Team::CalculateTPPool()
{
	//loop through members and add tp
	for (int i = 0; i < mTeamMembers.size(); i++)
	{
		mMaxTPPool += mTeamMembers[i]->GetTP();
	}
	//intialise tp vars
	mTPPool = mTPTurnSnapshot = mMaxTPPool;
}

//this should be called to reset the turn
void DPhoenix::Team::ResetTeamTurn()
{
	//loop through all mebemrs and adjust move / trun states
	for(int i = 0; i < mTeamMembers.size(); i++)
	{
		mTeamMembers[i]->mTurnState = CH_WAIT_TURNSTATE;
		mTeamMembers[i]->mMoveState = CH_PICKRT_MOVESTATE;
	}

	//set to first member and reset to max tp pool
	mCurrentMember = 0;
	mTPPool = mTPTurnSnapshot = mMaxTPPool;

	mTurnsLeft = 0;

	//check for death
	for (int i = mTeamMembers.size() - 1; i > -1; --i)
	{
		if (mTeamMembers[i]->mLifeState != CH_DEAD_LIFESTATE)
		{
			mTurnsLeft++;
			mCurrentMember = i;
		}
	}

	mTeamMembers[mCurrentMember]->mTurnState = CH_ACTIVE_TURNSTATE;
}

//go to next member of the team
void DPhoenix::Team::NextMember()
{
	//safeguard - should only change if current member acrive and picking route
	//or if turn is completed
	if ((mTeamMembers[mCurrentMember]->mTurnState == CH_ACTIVE_TURNSTATE &&
		mTeamMembers[mCurrentMember]->mMoveState == CH_PICKRT_MOVESTATE) ||
		mTeamMembers[mCurrentMember]->mTurnState == CH_COMP_TURNSTATE)
	{
		//RESET TP POOL TO CURRENT TURN snapshot
		mTPPool = mTPTurnSnapshot;

		//selected flag for checking which member to selct
		bool  selected = false;

		//if current flag member has not ocmpleted turn,set to wait turn
		if (mTeamMembers[mCurrentMember]->mTurnState != CH_COMP_TURNSTATE)
			mTeamMembers[mCurrentMember]->mTurnState = CH_WAIT_TURNSTATE;

		//while no one is selected
		while (!selected)
		{
			//increment curent member
			mCurrentMember++;
			if (mCurrentMember > mTeamMembers.size() - 1)
				mCurrentMember = 0;

			//if the new current member is waiting and not dead
			if (mTeamMembers[mCurrentMember]->mTurnState == CH_WAIT_TURNSTATE &&
				mTeamMembers[mCurrentMember]->mLifeState != CH_DEAD_LIFESTATE)
			{
				//set as selected, active and in te picl route movestate
				selected = true;
				mTeamMembers[mCurrentMember]->mTurnState = CH_ACTIVE_TURNSTATE;
				mTeamMembers[mCurrentMember]->mMoveState = CH_PICKRT_MOVESTATE;
			}

		}
	}
}

//go to previous member of the team
void DPhoenix::Team::PrevMember()
{
	//safeguard - should only change if current member active and picking route
	//or if turn is complete
	if ((mTeamMembers[mCurrentMember]->mTurnState == CH_ACTIVE_TURNSTATE &&
		mTeamMembers[mCurrentMember]->mMoveState == CH_PICKRT_MOVESTATE) ||
		mTeamMembers[mCurrentMember]->mTurnState == CH_COMP_TURNSTATE)
	{
		//reset TP pool to the current turn snapshot
		mTPPool = mTPTurnSnapshot;

		//selected flag for checking whih member to select
		bool selected = false;

		//if current member has not complete turn, set to wait turn state
		if (mTeamMembers[mCurrentMember]->mTurnState != CH_COMP_TURNSTATE)
			mTeamMembers[mCurrentMember]->mTurnState = CH_WAIT_TURNSTATE;

		//while no one is selected
		while (!selected)
		{
			//decremnt current members
			mCurrentMember--;

			//bounds if less than 0 set to team size
			if (mCurrentMember < 0)
				mCurrentMember = mTeamMembers.size() - 1;

			if (mTeamMembers[mCurrentMember]->mTurnState == CH_WAIT_TURNSTATE &&
				mTeamMembers[mCurrentMember]->mLifeState != CH_DEAD_LIFESTATE)
			{
				//set as selected, active and in the pick route movestate
				selected = true;
				mTeamMembers[mCurrentMember]->mTurnState = CH_ACTIVE_TURNSTATE;
				mTeamMembers[mCurrentMember]->mMoveState = CH_PICKRT_MOVESTATE;
			}
		}
	}
}

void DPhoenix::Team::SelectMember(int index)
{
	//if same as index, end early
	if (mCurrentMember == index)
		return;

	//also if this meber has completed, bow out now
	if (mTeamMembers[index]->mTurnState == CH_COMP_TURNSTATE)
		return;

	//reset tp pool to the current snapshot
	mTPPool = mTPTurnSnapshot;

	//if intended selction is not dead, then set as asctive
	//and store the index, oter wise return
	if (mTeamMembers[index]->mLifeState != CH_DEAD_LIFESTATE)
	{
		mTeamMembers[index]->mTurnState = CH_ACTIVE_TURNSTATE;
		mCurrentMember = index;
	}
	else
	{
		return;
	}

	//loop though rest of member here and if active to set wait
	for (int i = 0; i < mTeamMembers.size(); i++)
	{
		//as long as not our newly selected
		if (i != index)
		{
			if (mTeamMembers[i]->mTurnState == CH_ACTIVE_TURNSTATE)
				mTeamMembers[i]->mTurnState = CH_WAIT_TURNSTATE;
		}
	}
}

//lonf meoth if noe exspecially compex - check to see waht actions can be performed based on current map pos
void DPhoenix::Team::CheckAvailableActions(std::vector<std::vector<MapBlock*>>& _map, int currentCol, int currentRow)
{
	//clear the aviable actions vector
	mAvailableActions.clear();
	//flag for melle attacks
	bool canHit = false;

	//first check form the player persepctive if an enmy is an adjacent tile
	if (mTeamType == PLAYER_TEAM)
	{
		//tile to the left
		if (currentCol - 1 > 0)
		{
			if (_map[currentCol - 1][currentRow]->mSpecialFlag == ENEMY_SP_FLAG)
				canHit = true;
		}
		//tile to the right
		if (currentCol + 1 < _map.size())
		{
			if (_map[currentCol + 1][currentRow]->mSpecialFlag == ENEMY_SP_FLAG)
				canHit = true;
		}
		//tile begind
		if (currentRow - 1 > 0)
		{
			if (_map[currentCol][currentRow - 1]->mSpecialFlag == ENEMY_SP_FLAG)
				canHit = true;
		}

		if (currentRow + 1 < _map[0].size())
		{
			if (_map[currentCol][currentRow + 1]->mSpecialFlag == ENEMY_SP_FLAG)
				canHit = true;
		}
	}

	else if (mTeamType == ENEMY_TEAM)
	{
		//tile to the left
		if (currentCol - 1 > 0)
		{
			if (_map[currentCol - 1][currentRow]->mSpecialFlag == PLAYER_SP_FLAG)
				canHit = true;
		}
		//tile to the right
		if (currentCol + 1 < _map.size())
		{
			if (_map[currentCol + 1][currentRow]->mSpecialFlag == PLAYER_SP_FLAG)
				canHit = true;
		}
		//tile begind
		if (currentRow - 1 > 0)
		{
			if (_map[currentCol][currentRow - 1]->mSpecialFlag == PLAYER_SP_FLAG)
				canHit = true;
		}

		if (currentRow + 1 < _map[0].size())
		{
			if (_map[currentCol][currentRow + 1]->mSpecialFlag == PLAYER_SP_FLAG)
				canHit = true;
		}
	}

	//if a melle attack is possbile and ewe have the tp to perform it
	//push bacj the hit action
	if (canHit && mTPPool >= 1)
	{
		mAvailableActions.push_back(HIT_ACTION);
	}

	//the shooting / prjectile are ablaive based on class and tp cost
	//hecne this is acheck by a class and tp of ucrrent meber
	//to see which actions are pushed ack
	//values here are ahrdcoded but could potentially be confiugre in a seprate file
	switch (mTeamMembers[mCurrentMember]->mClass)
	{
	case BRUSIER_SHIP_CLASS:

		if (mTPPool >= 2)
			mAvailableActions.push_back(CANNON_ACTION);
		if (mTPPool >= 6)
			mAvailableActions.push_back(HEAVYCANNON_ACTION);
		//if (mTPPool >= 2)
		//	mAvailableActions.push_back(BRACE_ACTION);
		//if (mTPPool >= 4)
		//	mAvailableActions.push_back(CHARGE_ACTION);
		//if (mTPPool >= 2)
		//	mAvailableActions.push_back(EMERGENCY_REPAIR_ACTION);
		
		break;
	case CRUSIER_SHIP_CLASS:

		if (mTPPool >= 2 )
			mAvailableActions.push_back(CANNON_ACTION);
		if (mTPPool >= 3)
			mAvailableActions.push_back(BARRAGE_ACTION);
		//if (mTPPool >= 2)
		//	mAvailableActions.push_back(BRACE_ACTION);
		//if (mTPPool >= 2)
		//	mAvailableActions.push_back(SNIPE_ACTION);
		//if (mTPPool >= 4)
		//	mAvailableActions.push_back(EMERGENCY_REPAIR_ACTION);
		if (mTPPool >= 4)
			mAvailableActions.push_back(TORPEDO_ACTION);
		break;
	case FLAG_SHIP_CLASS:

		if (mTPPool >= 2)
			mAvailableActions.push_back(CANNON_ACTION);
		if (mTPPool >= 4)
			mAvailableActions.push_back(TORPEDO_ACTION);
		//if (mTPPool >= 4)
		//	mAvailableActions.push_back(QUICK_FIRIING_ARTILLERY_ACTION);
		//if (mTPPool >= 2)
		//	mAvailableActions.push_back(EMERGENCY_REPAIR_ACTION);
		//if (mTPPool >= 2)
		//	mAvailableActions.push_back(BRACE_ACTION);
		//if (mTPPool >= 5)
		//	mAvailableActions.push_back(COMMAND_ACTION);
		if (mTPPool >= 7)
			mAvailableActions.push_back(ALL_WEAPONS_FIRE_ACTION);
		break;
	case CORVETTE_SHIP_CLASS:

		if (mTPPool >= 2)
			mAvailableActions.push_back(CANNON_ACTION);
		if (mTPPool >= 5)
			mAvailableActions.push_back(SUBCANNON_ACTION);
		//if (mTPPool >= 2)
		//	mAvailableActions.push_back(SNIPE_ACTION);
		//if (mTPPool >= 2)
		//	mAvailableActions.push_back(EMERGENCY_REPAIR_ACTION);
		//if (mTPPool >= 2)
		//	mAvailableActions.push_back(BRACE_ACTION);

		break;
		
	
	}
	//alwats aviable is a hold still option to get to the next turn
	mAvailableActions.push_back(HOLD_STILL_ACTION);

	//the final avain;e action is to light a beacon if on an adjacent square
	//check simlair to melle above
	//tuke to the left


	//tile to the left
	if (currentCol - 1 > 0)
	{
		if (_map[currentCol - 1][currentRow]->mMapBlockType == BEACON_MAPBLOCK)
			mAvailableActions.push_back(LIGHT_BEACON_ACTION);
	}
	//tile to the right
	if (currentCol + 1 < _map.size())
	{
		if (_map[currentCol + 1][currentRow]->mMapBlockType == BEACON_MAPBLOCK)
			mAvailableActions.push_back(LIGHT_BEACON_ACTION);
	}
	//tile begind
	if (currentRow - 1 > 0)
	{
		if (_map[currentCol][currentRow - 1]->mMapBlockType == BEACON_MAPBLOCK)
			mAvailableActions.push_back(LIGHT_BEACON_ACTION);
	}

	if (currentRow + 1 > _map[0].size())
	{
		if (_map[currentCol][currentRow + 1]->mMapBlockType == BEACON_MAPBLOCK)
			mAvailableActions.push_back(LIGHT_BEACON_ACTION);
	}

}

//method to set actions index when index set
void DPhoenix::Team::CheckSelectedAction(int index, LITSMap* map)
{
	switch (mAvailableActions[index])
	{
	case HIT_ACTION:
	case CANNON_ACTION:
	case HEAVYCANNON_ACTION:
	case SUBCANNON_ACTION:
	case TORPEDO_ACTION:
	case QUICK_FIRIING_ARTILLERY_ACTION:
	case BRACE_ACTION:
	case CHARGE_ACTION:
	case SNIPE_ACTION:
	case BARRAGE_ACTION:
	case COMMAND_ACTION:
	case ALL_WEAPONS_FIRE_ACTION:
	case EMERGENCY_REPAIR_ACTION:
	case LIGHT_BEACON_ACTION:
		//here we st the action anda  floag to indicate it has just been selected
		mTeamMembers[mCurrentMember]->mSelectedAction = mAvailableActions[index];
		mNewActionselectFlag = true;
		break;
	case HOLD_STILL_ACTION:
		mTPTurnSnapshot = mTPPool;
		EndCurrentTurn(map);
		break;
	}
}

//this end for the current team member
void DPhoenix::Team::EndCurrentTurn(LITSMap* map)
{
	//set the current member to complete turn state and decerement turns left
	mTeamMembers[mCurrentMember]->mTurnState = CH_COMP_TURNSTATE;
	mTurnsLeft--;

	//if we have turns left then we selct the member

	if (mTurnsLeft > 0)
	{
		
		NextMember();
	}


	CheckTeamState();
	//added in as i think it doesnt seem to check the team stauts at the end of the turn, therefore if a player dies at end of there turn
	//and is last one the team will be place in dead state.
}

//this method is to check if the team i still alive
bool DPhoenix::Team::CheckTeamState()
{
	//init flags and counter
	bool isAlive = true;
	int countTheDead = 0;

	
	//loop thorugh and check life states to see if members dead
	for (int i = 0; i < mTeamMembers.size(); i++)
	{
		if (mTeamMembers[i]->mLifeState == CH_DEAD_LIFESTATE)
		{
			countTheDead++;
		}
	}
	//if all memers are dead , we need to unsert the alive flag
	//and set the team state
	if (mTeamMembers.size() == countTheDead)
	{
		isAlive = false;
		mTeamState = TM_DEAD_TEAMSTATE;
	}
	return isAlive;
}

void DPhoenix::Team::DetermineAIStatus(LITSMap* map, std::vector<Beacon*>& beaconVec)
{
	//ai is determine by how many beacons lit - enmy players ill go for beacons
	//first and the n go for players
	//this is determine on a team0turn by team turn basis

	//this intial asigns beacons to the team
	//checks per turn will cosnider distance between target beacon
	//also the distance betweene ach player
	//will go for nearest

	//if next baecon, light it
	//if next ot player, melle attack
	//if attack but not near fir

	//assert statement these sohold be more of these
	//anyway we need 4 of each to make this loop work
	assert(beaconVec.size() == 2);
	assert(mTeamMembers.size() == 4);

	//we going to shuddle the beacon ids so they are randomyl assign each turn
	std::vector<int> beaconIds;
	beaconIds.insert(beaconIds.end(), { 0, 1 });

	//using built in reandom gen
	std::random_shuffle(beaconIds.begin(), beaconIds.end());

	mTeamMembers[0]->mTargetBeaconId = beaconIds[0];
	mTeamMembers[1]->mTargetBeaconId = beaconIds[0];
	mTeamMembers[2]->mTargetBeaconId = beaconIds[1];
	mTeamMembers[3]->mTargetBeaconId = beaconIds[1];
	
}

void DPhoenix::Team::DetermineMovement(LITSMap* map, std::vector<Beacon*>& beaconVec,
	Team* opposingTeam, std::vector<PrimitiveInstance*>& happyPath,
	PrimitiveInstance* selectionBox)
{

	//at this poont it is a spefic character turn
	//this method should be coalled when enemy team mever
	//is it PICTRT actionstae

	//this method is ement to determin the happy path - automayicaly
	//the plaayer doesnt need the selciton dsiplayed so the happy path just apperas

	//this method should determin the full happy path ready to move along it
	//it will determine the happy path one update
	//against the cpy there no need for delays
	//hober it should be fair

	//for targets select
	std::vector<MapBlock*> potentialTargets;
	std::vector<float> distances;
#pragma region SelectPotentialTargets
	//add all opposing team mebers as targets
	for (int i = 0; i < opposingTeam->mTeamMembers.size(); i++)
	{
		if (opposingTeam->mTeamMembers[i]->mLifeState != CH_DEAD_LIFESTATE &&
			opposingTeam->mTeamMembers[i]->mLifeState != CH_DYING_LIFESTATE)
		{
			int col = map->GetColFromPosition(
				opposingTeam->mTeamMembers[i]->mModelInstance->mPosition);
			int row = map->GetRowFromPosition(
					opposingTeam->mTeamMembers[i]->mModelInstance->mPosition);

			potentialTargets.push_back(map->mTiles[col][row]);
		}
	}

	//add target beacon if isnt lit by the enemy
	if (beaconVec[mTeamMembers[mCurrentMember]->mTargetBeaconId]->mBeaconState != BEACON_ENEMY_LIT)
	{
		int col = map->GetColFromPosition(
			beaconVec[mTeamMembers[mCurrentMember]->mTargetBeaconId]->mPoleMeshInstance->mPosition);
		int row = map->GetRowFromPosition(
			beaconVec[mTeamMembers[mCurrentMember]->mTargetBeaconId]->mPoleMeshInstance->mPosition);

		potentialTargets.push_back(map->mTiles[col][row]);

	}
#pragma endregion SelectPotentialTargets
#pragma region CalulateTarget
	//need to get character grid pos
	int currentCharCol = map->GetColFromPosition(mTeamMembers[mCurrentMember]->mModelInstance->mPosition);
	int currentCharRow = map->GetRowFromPosition(mTeamMembers[mCurrentMember]->mModelInstance->mPosition);

	for (int i = 0; i < potentialTargets.size(); i++)
	{
		float distance = 0.0f;
		//ablsoute value for dsitance
		int xDist = abs(potentialTargets[i]->mArrayXPos - currentCharCol);
		int yDist = abs(potentialTargets[i]->mArrayYPos - currentCharRow);

		//here we could go full pythagors, yet as we only moving vert and hox
		//the manhatten dsitacen should suffice to order targets
		distance = xDist + yDist;

		distances.push_back(distance);
	}

	//now we need ot reorder the distance and also ensere that
	//the corrsponding target vec is reordered
	//simaliar approach used in line class
	std::vector<float> oldDistances = distances;

	std::vector<MapBlock*> newTargets;
	newTargets.resize(potentialTargets.size());

	//this will reoder the dsitance vec
	//from smallest to largets
	sort(distances.begin(), distances.end());

	//loop though the sorted vectors
	for (int i = 0; i < distances.size(); i++)
	{
		//now loop though old distances vector to match the valeus
		for (int j = 0; j < oldDistances.size(); j++)
		{
			//if valuye macthes we need to update the ne
			//related vectors
			if (distances[i] == oldDistances[j])
			{
				newTargets[i] = potentialTargets[j];
			}
		}
	}

	//assign the osrted vec
	potentialTargets = newTargets;

	//now we should have te nearest target as the first elemt
	mSelectedTarget = potentialTargets[0];

#pragma endregion CalulateTarget

#pragma region ConstructHappyPath
	int targetCol = mSelectedTarget->mArrayXPos;
	int targetRow = mSelectedTarget->mArrayYPos;

	//need to add the begion of happy path if not there already
	if (happyPath.size() < 1)
	{
		happyPath.push_back(new DPhoenix::PrimitiveInstance(*selectionBox));
		happyPath.back()->mPosition = mTeamMembers[mCurrentMember]->mModelInstance->mPosition;
		happyPath.back()->mPosition.y = 10.5f;
		happyPath.back()->mOpacity = 0.75f;

		int happyPathCol = map->GetColFromPosition(happyPath.back()->mPosition);
		int happyPathRow = map->GetRowFromPosition(happyPath.back()->mPosition);

		map->mTiles[happyPathCol][happyPathRow]->mSpecialFlag = HAPPY_PATH_SP_FLAG;
	}

	//check to see if we are enxt to the target already
	bool isNextToTarget = false;

	//need to separatecheck for adjacent row or col

	if ((currentCharRow == targetRow && (abs(currentCharCol - targetCol) == 1)) ||
		(currentCharCol == targetCol && (abs(currentCharRow - targetRow) == 1))
		)
	{
		isNextToTarget = true;
	}

	//if were next to target bypass consturction
	if (!isNextToTarget)
	{
		//conctruct path movment for fraction of current tp pool
		//checl vaild moes
		//check moveid direction of target
		// if theer is a match between both take it
		// iherwuse pick another vaild move
		//if we are next to target or out of tp end loop

		//in orcer left, up,right , down
		std::vector<bool> validMoves;
		std::vector<bool> desiredMoves; 
		std::vector<int> movmentIds;
		std::vector<XMFLOAT3> positions; 

		
		//get fraction of tp 
		int turnPointsToLeave = mTPPool / mTurnsLeft;

		if (mTurnsLeft == 1)
			turnPointsToLeave = 0;
		//need to take of a tp each turn
		for (int i = mTPPool; i > turnPointsToLeave && !isNextToTarget; i--, mTPPool--)
		{
			//determine the valid moves
			bool happyPathAddedto = false;

			int happyPathRow = map->GetRowFromPosition(happyPath.back()->mPosition);
			int happyPathCol = map->GetColFromPosition(happyPath.back()->mPosition);

			validMoves.clear(); validMoves.resize(4);
			desiredMoves.clear(); desiredMoves.resize(4);
			positions.clear(); positions.resize(4);
			movmentIds.clear();

			if (happyPathCol - 1 > -1)
				if ((map->mTiles[happyPathCol - 1][happyPathRow]->mMapBlockType == DPhoenix::FLOOR_MAPBLOCK &&
					map->mTiles[happyPathCol - 1][happyPathRow]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol - 1][happyPathRow]->mMapBlockType == DPhoenix::STRONGWIND_MAPBLOCK &&
					map->mTiles[happyPathCol - 1][happyPathRow]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol - 1][happyPathRow]->mMapBlockType == DPhoenix::HEAL_MAPBLOCK &&
					map->mTiles[happyPathCol - 1][happyPathRow]->mSpecialFlag == DPhoenix::NO_SP_FLAG||
					map->mTiles[happyPathCol - 1][happyPathRow]->mMapBlockType == DPhoenix::BASE_MAPBLOCK &&
					map->mTiles[happyPathCol - 1][happyPathRow]->mSpecialFlag == DPhoenix::NO_SP_FLAG))
				{
					validMoves[0] = true;
					positions[0] = map->GetPositionABoveFromMapRef(happyPathCol - 1, happyPathRow);
				}
			//UP -------------------------------------------------------------------------------------------
			if (happyPathRow - 1 > -1)
				if (map->mTiles[happyPathCol][happyPathRow - 1]->mMapBlockType == DPhoenix::FLOOR_MAPBLOCK &&
					map->mTiles[happyPathCol][happyPathRow - 1]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol][happyPathRow - 1]->mMapBlockType == DPhoenix::STRONGWIND_MAPBLOCK &&
					map->mTiles[happyPathCol][happyPathRow - 1]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol][happyPathRow - 1]->mMapBlockType == DPhoenix::HEAL_MAPBLOCK &&
					map->mTiles[happyPathCol][happyPathRow - 1]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol][happyPathRow - 1]->mMapBlockType == DPhoenix::BASE_MAPBLOCK &&
					map->mTiles[happyPathCol][happyPathRow - 1]->mSpecialFlag == DPhoenix::NO_SP_FLAG)
				{
					validMoves[3] = true;
					positions[3] = map->GetPositionABoveFromMapRef(happyPathCol, happyPathRow - 1);
				}

			//RIGHT ----------------------------------------------------------------------------------------
			if (happyPathCol + 1 < map->mWidth)
				if (map->mTiles[happyPathCol + 1][happyPathRow]->mMapBlockType == DPhoenix::FLOOR_MAPBLOCK &&
					map->mTiles[happyPathCol + 1][happyPathRow]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol + 1][happyPathRow]->mMapBlockType == DPhoenix::STRONGWIND_MAPBLOCK &&
					map->mTiles[happyPathCol + 1][happyPathRow]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol + 1][happyPathRow]->mMapBlockType == DPhoenix::HEAL_MAPBLOCK &&
					map->mTiles[happyPathCol + 1][happyPathRow]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol + 1][happyPathRow]->mMapBlockType == DPhoenix::BASE_MAPBLOCK &&
					map->mTiles[happyPathCol + 1][happyPathRow]->mSpecialFlag == DPhoenix::NO_SP_FLAG)
				{
					validMoves[2] = true;
					positions[2] = map->GetPositionABoveFromMapRef(happyPathCol + 1, happyPathRow);
				}
			//DOWN ----------------------------------------------------------------------------------------			
			if (happyPathRow + 1 < map->mLength)
				if (map->mTiles[happyPathCol][happyPathRow + 1]->mMapBlockType == DPhoenix::FLOOR_MAPBLOCK &&
					map->mTiles[happyPathCol][happyPathRow + 1]->mSpecialFlag == DPhoenix::NO_SP_FLAG||
					map->mTiles[happyPathCol][happyPathRow + 1]->mMapBlockType == DPhoenix::STRONGWIND_MAPBLOCK &&
					map->mTiles[happyPathCol][happyPathRow + 1]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol][happyPathRow + 1]->mMapBlockType == DPhoenix::HEAL_MAPBLOCK &&
					map->mTiles[happyPathCol][happyPathRow + 1]->mSpecialFlag == DPhoenix::NO_SP_FLAG ||
					map->mTiles[happyPathCol][happyPathRow + 1]->mMapBlockType == DPhoenix::BASE_MAPBLOCK &&
					map->mTiles[happyPathCol][happyPathRow + 1]->mSpecialFlag == DPhoenix::NO_SP_FLAG)
				{
					validMoves[1] = true;
					positions[1] = map->GetPositionABoveFromMapRef(happyPathCol, happyPathRow + 1);
				}

			//determine the desired moves ------------------------------------------------------------------
			//(in direction of the selected target)

			if (happyPathCol - targetCol > 0)
				desiredMoves[0] = true;	//left			
			if (happyPathRow - targetRow < 0)
				desiredMoves[1] = true;	//up
			if (happyPathCol - targetCol < 0)
				desiredMoves[2] = true;	//right
			if (happyPathRow - targetRow > 0)
				desiredMoves[3] = true;	//down			

			//FIRST TRY - ARE VALID MOVES DESIRED MOVES???? ---------------------------------------------------
			for (int i = 0; i < validMoves.size(); i++)
			{
				if (validMoves[i] == desiredMoves[i] &&
					validMoves[i] == true)
					movmentIds.push_back(i);
			}

			//IF NONE OF THE VALID MOVES ARE AS DESIRED, POPULATE THE VECTOR WITH ALL VALID MOVES -------------
			if (movmentIds.size() == 0)
			{
				for (int i = 0; i < validMoves.size(); i++)
				{
					if (validMoves[i] == true)
						movmentIds.push_back(i);
				}
			}

			//we may ot have any valid moves though ageter these checkks, in which case skip ahead
			//however if we do, need to randomly seelct
			if (movmentIds.size() > 0)
			{
				//now we have the mvoment ids to select from, et randomise to then add to happy path
				//suing buld in random gen
				std::random_shuffle(movmentIds.begin(), movmentIds.end());
				int selectedId = movmentIds[0];

				//mow we hav the pos id we want, we can add to the happy path
				happyPath.push_back(new DPhoenix::PrimitiveInstance(*selectionBox));
				happyPath.back()->mPosition = positions[selectedId];
				happyPath.back()->mPrevPosition = happyPath.back()->mPosition;
				happyPath.back()->mPosition.y = 10.5f;
				happyPath.back()->mOpacity = 0.75f;
				happyPathAddedto = true;

				int lastAddedCol = map->GetColFromPosition(positions[selectedId]);
				int lastAddedRow = map->GetRowFromPosition(positions[selectedId]);

				map->mTiles[lastAddedCol][lastAddedRow]->mSpecialFlag = HAPPY_PATH_SP_FLAG;

				//now a final check as we addeed amove, does this put us next to the target
				if ((lastAddedRow == targetRow && (abs(lastAddedCol - targetCol) == 1)) ||
					(lastAddedCol == targetCol && (abs(lastAddedRow - targetRow) == 1)))
				{
					isNextToTarget = true;
				}

				if (map->mTiles[lastAddedCol][lastAddedRow]->mMapBlockType = HEAL_MAPBLOCK)
				{
					mHeal = true;
				}

			}
			else
			{
				break;
			}

		}

	}

	//update statee anda ssing path
	mTeamMembers[mCurrentMember]->mMoveState = CH_MOVERT_MOVESTATE;
	mTeamMembers[mCurrentMember]->mHappyPath = happyPath;
#pragma endregion ConstructHappyPath
}

void DPhoenix::Team::DetermineAction(LITSMap * map, std::vector<Beacon*>& beaconVec, Team* opposingTeam,
	std::vector<PrimitiveInstance*>& targets, PrimitiveInstance* targetHighlight)
{
	//first we need to determin if our target is a beacon or an poosing team
	//if a beacon and we are next to it lit it
	//if beacon but not next to i hold
	//if other team and next to it melee
	//if other team and not next to it choose random projectile

	//target pro
	int targetCol = mSelectedTarget->mArrayXPos;
	int targetRow = mSelectedTarget->mArrayYPos;

	int currentCol = map->GetColFromPosition(mTeamMembers[mCurrentMember]->mModelInstance->mPosition);
	int currentRow = map->GetRowFromPosition(mTeamMembers[mCurrentMember]->mModelInstance->mPosition);

	bool isNextToTarget = false;

	//check to se if nect to target
	if ((currentRow == targetRow && (abs(currentCol - targetCol) == 1)) ||
		(currentCol == targetCol && (abs(currentRow - targetRow) == 1)))
	{
		isNextToTarget = true;
	}
#pragma region BeaconTarget
	if (mSelectedTarget->mMapBlockType == BEACON_MAPBLOCK)
	{
		if (isNextToTarget)
		{
			//ok, add target to vectr and magic happen
			targets.clear();
			targets.push_back(new DPhoenix::PrimitiveInstance(*targetHighlight));
			targets.back()->mPosition = map->GetPositionABoveFromMapRef(targetCol, targetRow);
			targets.back()->mOpacity = 0.95f;

			mTeamMembers[mCurrentMember]->mMoveState = CH_DOAC_MOVESTATE;
			mTeamMembers[mCurrentMember]->mSelectedAction = LIGHT_BEACON_ACTION;

		}
		else
		{
			//hold still
			mTPTurnSnapshot = mTPPool;
			EndCurrentTurn(map);
		}
	}
#pragma endregion BeaconTarget
#pragma region CharacterTarget
	//check our target is plyer
	if (mSelectedTarget->mSpecialFlag == PLAYER_SP_FLAG)
	{
		//if we have no tp best hold sti;
		if (mTPPool == 0)
		{
			//ho;d sto;;'
			mTPTurnSnapshot = mTPPool;
			EndCurrentTurn(map);
		}
		//oterwise we next to target melle hit
		else if (isNextToTarget)
		{
			targets.clear();
			targets.push_back(new DPhoenix::PrimitiveInstance(*targetHighlight));
			targets.back()->mPosition = map->GetPositionABoveFromMapRef(targetCol, targetRow);
			targets.back()->mOpacity = 0.95f;

			mTeamMembers[mCurrentMember]->mMoveState = CH_DOAC_MOVESTATE;
			mTeamMembers[mCurrentMember]->mSelectedAction = HIT_ACTION;

			mTPPool--;
		}
		//otherwise let randlmy seelct from avaible actions
		else
		{
			//right let see what action we have avainale
			CheckAvailableActions(map->mTiles, currentCol, currentRow);

			//vector copy for withough hold still
			std::vector<AvailableActions> actionsNotHoldStill = mAvailableActions;

			for (int i = 0; i < actionsNotHoldStill.size();)
			{
				if (actionsNotHoldStill[i] == HOLD_STILL_ACTION ||
					actionsNotHoldStill[i] == LIGHT_BEACON_ACTION)
				{
					actionsNotHoldStill.erase(actionsNotHoldStill.begin() + i);
				}
				else
				{
					i++;
				}

			}
			//if no actions left, well it was hold still
			if (actionsNotHoldStill.size() == 0)
			{
				//hold still
				mTPTurnSnapshot = mTPPool;
				EndCurrentTurn(map);
			}
			else
			{
				//yay we have anoter action er can use to attack
				//in which case radonly seelct

				int action = rand() % actionsNotHoldStill.size();

				mTeamMembers[mCurrentMember]->mSelectedAction = actionsNotHoldStill[action];

				//now all waepon/ magic has 5 squre around char to target
				//we need first of all to buoi;d taht
				// after we detimne the first adversy we come across and target them
				//if none in target we attemp edge to target
				//nearrst the neast foe

				int minRow = max(currentRow - 5, 0);
				int maxRow = min(currentRow + 5, map->mWidth - 1);
				int minCol = max(currentCol - 5, 0);
				int maxCol = min(currentCol + 5, map->mLength - 1);

				XMFLOAT3 targetPos;

				bool isTargetfound = false;

				for (int col = minCol; col <= maxCol && !isTargetfound; col++)
				{
					for (int row = minRow; row <= maxRow && !isTargetfound; row++)
					{
						if (!(currentCol == col && currentRow == row))
						{
							if (map->mTiles[col][row]->mSpecialFlag == DPhoenix::PLAYER_SP_FLAG)
							{
								targetPos = map->GetPositionABoveFromMapRef(col, row);
								targets.push_back(new DPhoenix::PrimitiveInstance(*targetHighlight));
								targets.back()->mPosition = targetPos;
								targets.back()->mPrevPosition = targets.back()->mPosition;
								isTargetfound = true;
							}
						}
					}
				}

				
				//ok nting in rane of target selct so lets try and fiure at the nereast ede
				//to a player
				if (!isTargetfound)
				{
					// alread have te row / col of the nearset targets so lget g a final
					// target pos based upon the outer edge of our targeting area
					int finalRow;
					int finalCol;

					if (targetRow <= minRow)
					{
						finalRow = minRow;
					}			
					else if(targetRow >= maxRow)
					{
						finalRow = maxRow;
					}
					else
					{
						finalRow = targetRow;
					}

					if (targetCol <= minCol)
					{
						finalCol = minCol;
					}
					else if (targetCol >= maxCol)
					{
						finalCol = maxCol;
					}
					else
					{
						finalCol = targetCol;
					}
					targetPos = map->GetPositionABoveFromMapRef(finalCol, finalRow);
					targets.push_back(new DPhoenix::PrimitiveInstance(*targetHighlight));
					targets.back()->mPosition = targetPos;
					targets.back()->mPrevPosition = targets.back()->mPosition;
				}
				//set to do action
				mTeamMembers[mCurrentMember]->mMoveState = CH_DOAC_MOVESTATE;
			}

		}
	}
#pragma endregion CharacterTarget
}