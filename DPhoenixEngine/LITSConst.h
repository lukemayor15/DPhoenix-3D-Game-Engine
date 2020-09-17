#pragma once
#include "D3DUtil.h"

namespace LITSConst
{
#pragma region settings

	//things like dmage modifers can go here
#pragma endregion settings

#pragma region SelecteMenuUI

	//for hover images
	const int selectHoverImageWidth = 300;
	const int selectHoverImageHeight = 350;


#pragma region HoverAndClickAreas
	//all RECt initaisition in orfer left, top, reigt,bottum

	//these are all base don the directx11 positions of the xcreen
	//where the orihin 0,0, is in the center
	const RECT selectFlagShip = { -800, 150, -800 + selectHoverImageWidth, 150 - selectHoverImageHeight };
	const RECT selectCorvette = { -500, 150, -500 + selectHoverImageWidth, 150 - selectHoverImageHeight };
	const RECT selectBrusier = { -200, 150, -200 + selectHoverImageWidth, 150 - selectHoverImageHeight };
	const RECT selectCrusier = { 100, 150, 100 + selectHoverImageWidth, 150 - selectHoverImageHeight };


	
	
	const RECT selectUpArrow = { 700, 250, 700 + 50, 250 - 50 };
	const RECT selectDownArrow = { 700, 200, 700 + 50, 200 - 50 };
	const RECT selectRemoveLast = { 700, -100, 700 + 50, -100 - 50 };

#pragma endregion HoverAndClickAreas

#pragma region TextPositions

	//these positions are based on an orignin of 0, 0 in the top left
	//as they are for font rendering positions
	const float selectedLevelLeft = 1350.0f;
	const float selectedLevelTop = 200.0f;

	const float selectedCharacterClassesLeft = 1250.0f;
	const float selectedCharacterClassesTop = 350.0f;
	const float selectedCharacterClassesRowSpacing = 50.0f;

	const float selectedEnemyClassesLeft = 1300.0f;
	const float selectedEnemyClassesTop = 710.0f;
	const float selectedEnemyClassesRowSpacing = 40.0f;

	const float selectedBursierStatsLeft = 800.0f;
	const float selectedBrusierTop = 650.0f;
	
	const float selectedCursierStatsLeft = 1100.0f;
	const float selectedCursierStatsTop = 650.0f;

	const float selectedFlagShipStatsLeft = 200.0f;
	const float selectedFlagShipStatsTop = 650.0f;

	const float selectedCorvetteStatsLeft = 500.0f;
	const float selectedCorvetteStatsTop = 650.0f;
#pragma endregion TextPositions

#pragma endregion SelectMenuUI

#pragma region GameplayUI

#pragma region ImageProperties
	
	//select hober image
	const float gameActionHoverWidth = 250.0f;
	const float gameActionHoverHeight = 25.0f;

	const float gameTurnsHoverWidth = 250.0f;
	const float gameTurnsHoverHeight = 25.0f;

	//avatars
	const float gameAvatarWidth = 25.0f;
	const float gameAvatarHeight = 25.0f;

	//ui baclgrounds - pos, based on direct 11

	const float gameActionsPanelLeft = -750.0f;
	const float gameActionsPanelTop = 350.0f;
	const float gameActionsPanelWidth = 250.0f;
	const float gameActionsPanelHeight = 250.0f;

	const float gameBeaconsPanelLeft = 500.0f;
	const float gameBeaconsPanelTop = -100.0f;
	const float gameBeaconsPanelWidth = 250.0f;
	const float gameBeaconsPanelHeight = 250.0f;

	const float gameEnemyPanelLeft = 500.0f;
	const float gameEnemyPanelTop = 200.0f;
	const float gameEnemyPanelWidth = 250.0f;
	const float gameEnemyPanelHeight = 250.0f;

	const float gameStatusPanelLeft = -500.0f;
	const float gameStatusPanelTop = 400.0f;
	const float gameStatusPanelWidth = 1000.0f;
	const float gameStatusPanelHeight = 50.0f;

	const float gamePlayerPanelLeft = -750.0f;
	const float gamePlayerPanelTop = -50.0f;
	const float gamePlayerPanelWidth = 250.0f;
	const float gamePlayerPanelHeight = 300.0f;

	//pos and offset to support pos in loops
	const float gamePlayerAvatarsInitialX = -550.0f;
	const float gamePlayerAvatarsInitialY = -150.0f;
	const float gamePlayerAvatarsYAdjust = -50.0f;

	const float gameEnemyAvatarsInitialX = 525.0f;
	const float gameEnemyAvatarsInitialY = 150.0f;
	const float gameEnemyAvatarsYAdjust = -50.0f;

	const float gamePlayerTurnInitialX = -750.0f;
	const float gamePlayerTurnInitialY = -150.0f;
	const float gamePlayerYAdjust = -25.0f;
#pragma endregion ImageProperties

#pragma region HoverAndClickAreas
	//All rect initialsation are in the order left, top right bor

	//these are all based on te direct11 positions of the screen
	//here the origin 00 is the center

	const RECT gamePlayer1Section = { gamePlayerPanelLeft, -150.0f,
									gamePlayerPanelLeft + gameTurnsHoverWidth, -150.0f - gameTurnsHoverHeight };
	const RECT gamePlayer2Section = { gamePlayerPanelLeft, -175.0f,
										gamePlayerPanelLeft + gameTurnsHoverWidth, -175.0f - gameTurnsHoverHeight };
	const RECT gamePlayer3Section = { gamePlayerPanelLeft, -200.0f,
										gamePlayerPanelLeft + gameTurnsHoverWidth, -200.0f - gameTurnsHoverHeight };
	const RECT gamePlayer4Section = { gamePlayerPanelLeft, -225.0f,
										gamePlayerPanelLeft + gameTurnsHoverWidth, -225.0f - gameTurnsHoverHeight };
#pragma endregion HoverAndClickAreas

#pragma region TextPositions
	//these pos and base on an orgin of 0,0 in top left
	//as the are are for font rendering pos

	//player stats panel
	float const gamePlayerStatsTPLeft = 200.0f;
	float const gamePlayerStatsTPTop = 550.0f;

	float const gamePlayerStatsLeft = 150.0f;
	float const gamePlayerStatsTop = 600.0f;
	float const gamePlayerStatsYAdjust = 29.0f;

	float const gameEnemyStatsLeft = 1450.0f;
	float const gameEnemyStatsTop = 290.0f;
	float const gameEnemyStatsYAdjust = 25.0f;

#pragma endregion TextPositions


#pragma region actions

#pragma region hoverandclickareas
	const RECT actionSelect1Section = { -750.0, 300.0f,
										-750.0f + gameActionHoverWidth, 300.0f - gameActionHoverHeight };
	const RECT actionSelect2Section = { -750.0, 275.0f,
										-750.0f + gameActionHoverWidth, 275.0f - gameActionHoverHeight };
	const RECT actionSelect3Section = { -750.0, 250.0f,
										-750.0f + gameActionHoverWidth, 250.0f - gameActionHoverHeight };
	const RECT actionSelect4Section = { -750.0, 225.0f,
										-750.0f + gameActionHoverWidth, 225.0f - gameActionHoverHeight };
	const RECT actionSelect5Section = { -750.0, 200.0f,
										-750.0f + gameActionHoverWidth, 200.0f - gameActionHoverHeight };
	const RECT actionSelect6Section = { -750.0, 175.0f,
										-750.0f + gameActionHoverWidth, 175.0f - gameActionHoverHeight };
	const RECT actionSelect7Section = { -750.0, 150.0f,
										-750.0f + gameActionHoverWidth, 150.0f - gameActionHoverHeight };
	const RECT actionSelect8Section = { -750.0, 325.0f,
										-750.0f + gameActionHoverWidth, 325.0f - gameActionHoverHeight };
#pragma endregion hoverandclickareas

#pragma region TextPositions
	//status bar
	float const actionsStatusTextLeft = 510.0f;
	float const actionsStatusTextTop = 50.0f;

	//avaiable actions
	float const actionsTextLeft = 60.0f;
	float const actionsTextTop = 150.0f;
	float const actionTextYAdjust = 25.0f;

	//beacons text
	float const actionsBeaconsLeft = 1350.0f;
	float const actionsBeaconsTop = 605.0f;
	float const actionsBeaconsYAdjust = 55.0f;
#pragma endregion TextPositions
#pragma actions


}