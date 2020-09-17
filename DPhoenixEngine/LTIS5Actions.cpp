//#include "Engine.h"
//#include "BillboardSprite.h"
//#include "ParticleEmitter.h"
//
//#include "LITSConst.h"
//#include "Team.h"
//#include "LITSMap.h"
//
////govern control flow
//enum GameStates
//{
//	GAME_TITLE_STATE,
//	GAME_MENU_STATE,
//	GAME_PLAY_STATE,
//	GAME_OVER_STATE
//};
//
//enum MenuStates
//{
//	CHOOSE_MENUSTATE,
//	CONFIRM_MENUSTATE,
//	ENEMY_1_PICKED_MENUSTATE,
//	ENEMY_2_PICKED_MENUSTATE,
//	ENEMY_3_PICKED_MENUSTATE,
//	ENEMY_4_PICKED_MENUSTATE
//};
//
//enum ActionStages
//{
//	AC_INITIAL,
//	AC_PREPARE,
//	AC_FIRE,
//	AC_POSTFIRE,
//	AC_DONE
//};
//
//enum MeleeStages
//{
//	GOTO_TARGET_MEL,
//	HIT_TARGET_MEL,
//	RETURN_MEL
//};
//
//
////initial class definition inheriting fron Engine
//class LITSActions : public DPhoenix::Engine
//{
//private:
//	//depth stencil (to handle multiple overlayed sprites)
//	ID3D11DepthStencilState* mDepthStencilState;
//	ID3D11DepthStencilState* mDepthDisabledStencilState;
//	D3D11_DEPTH_STENCIL_DESC mDepthStencilDesc;
//	D3D11_DEPTH_STENCIL_DESC mDepthDisabledStencilDesc;
//
//	//texture manager
//	DPhoenix::TextureMgr mTexMgr;
//
//	//audio manager
//	DPhoenix::AudioMgr mAudioMgr;
//
//	//font pointer - debug text
//	DPhoenix::Font* mDebugFont;
//
//	//screen scale (for window stretching)
//	XMFLOAT2 mScreenScale;
//
//	//view and projection matrices
//	XMMATRIX mView;
//	XMMATRIX mProjection;
//
//	//for geometry generation
//	DPhoenix::GeometryGenerator* mGeoGen;
//
//	DPhoenix::GeometryGenerator::MeshData* mBox;
//	DPhoenix::GeometryGenerator::MeshData* mSphere;
//	DPhoenix::GeometryGenerator::MeshData* mGrid;
//
//	//camera object
//	DPhoenix::Camera* mCamera;
//	DPhoenix::EAngle mCamEAngle;
//
//	//ambient color
//	XMFLOAT4 mAmbientColor;
//	float mAmbIntensity;
//
//	//skybox
//	DPhoenix::Sky* mSkybox;
//
//
//	//lighting ------------------------------------------------
//	//directional lights
//	std::vector<DirectionalLight*> mDirLights;
//	DirectionalLight mDirLightsArray[1];
//	int mNumDirLights;
//
//	//fog values
//	bool mFogEnabled;
//	float  mFogStart;
//	float  mFogRange;
//	XMFLOAT4 mFogColor;
//
//	//point lights
//	std::vector<PointLight*> mPointLights;
//	int mNumPointLights;
//	PointLight mPointLightsArray[10];
//	float mRange;
//	float mPointRotationValue;
//	float mPointY;
//
//#pragma region BTLTMembers
//	GameStates mGameState;
//	MenuStates mMenuState;
//
//	DPhoenix::Team* mPlayerTeam;
//	DPhoenix::Team* mEnemyTeam;
//
//	DPhoenix::CharacterClass* mCrusierMenu;
//	DPhoenix::CharacterClass* mBrusierMenu;
//	DPhoenix::CharacterClass* mCorvetteMenu;
//	DPhoenix::CharacterClass* mFlagShipMenu;
//
//	//UI elements
//	int mMouseX;
//	int mMouseY;
//
//	DPhoenix::Sprite* mTitleScreen;
//	DPhoenix::Sprite* mTeamMenuScreen;
//
//	DPhoenix::Sprite* mSelectedClassMenu;
//
//	int mSelectedLevel;
//
//	//fonts
//	DPhoenix::Font* mUIFont16pt;
//	DPhoenix::Font* mUIFont18pt;
//	DPhoenix::Font* mUIFont36pt;
//	DPhoenix::Font* mUIFont30pt;
//	DPhoenix::Font* mUIFont48pt;
//	DPhoenix::Font* mUIFont90pt;
//
//	//action timers
//	DPhoenix::GameTimer mMouseClickTimer;
//	DPhoenix::GameTimer mKeyPressTimer;
//	DPhoenix::GameTimer mWaitTimer;
//
//
//
//#pragma region LITSMapMembers
//	DPhoenix::LITSMap* mMap;
//	std::vector<XMFLOAT3> mPlayerSpawnVec;
//	std::vector<XMFLOAT3> mEnemySpawnVec;
//	std::vector<XMFLOAT3> mBeaconSpawnVec;
//
//	std::vector<std::string> mFloorColorMaps;
//	std::vector<std::string> mFloorNormalMaps;
//	std::vector<std::string> mWallColorMaps;
//	std::vector<std::string> mWallNormalMaps;
//	std::vector<std::string> mCoverColorMaps;
//	std::vector<std::string> mCoverNormalMaps;
//
//	float mCameraDistanceOffset;
//	float mCamToFocusAngle;
//#pragma endregion LITSMapMembers
//
//#pragma region LITSUIMembers
//	//ui panel backgrounds
//	DPhoenix::Sprite* mActionsUISprite;
//	DPhoenix::Sprite* mBeaconsUISprite;
//	DPhoenix::Sprite* mEnemyUISprite;
//	DPhoenix::Sprite* mStatusUISprite;
//	DPhoenix::Sprite* mPlayerTeamUISprite;
//
//	//highlight for tuns . actions
//	DPhoenix::Sprite* mHoverdTurnUISprite;
//	DPhoenix::Sprite* mSelectedActionUISprite;
//	DPhoenix::Sprite* mHoverdActionUISprite;
//	DPhoenix::Sprite* mSelectedTurnUISprite;
//	DPhoenix::Sprite* mTakenTurnUISprite;
//
//	//avatars
//	DPhoenix::Sprite* mFlagShipAvatar;
//	DPhoenix::Sprite* mBrusierAvatar;
//	DPhoenix::Sprite* mCrusierAvatar;
//	DPhoenix::Sprite* mCorvetteAvatar;
//
//	//teams
//	DPhoenix::TeamTypes mCurrentTeam;
//
//	//camera testing --------
//	bool mCameraBehindFlag;
//	bool mClickFlag;
//
//	//for truns menu
//	bool mP1Hover, mP2Hover, mP3Hover, mP4Hover;
//
//
//#pragma endregion LITSUIMembers
//
//#pragma region LTISMOvment
//	//this is to genreate the grid
//	DPhoenix::GeometryGenerator::MeshData* mSelectionBox;
//	//the happy path is the path selected for movment
//	std::vector<DPhoenix::PrimitiveInstance*> mHappyPath;
//	//the selection boxes ae possible move displaed
//	std::vector<DPhoenix::PrimitiveInstance*> mSelectionBoxes;
//
//	//aline for the camera prjected into the world
//	//will be ther to check for collision with possible secltions
//	DPhoenix::Line* mCameraLine;
//
//	//diffrently textured tiles for possible selctions
//	DPhoenix::PrimitiveInstance* mSelectionHighLight;
//	DPhoenix::PrimitiveInstance* mBadSelectionHighLight;
//	DPhoenix::PrimitiveInstance* mTargetHighlight;
//
//#pragma region LITSActions
//	//falgs fir action selection
//	bool mGotActions;
//	bool mA1Hover, mA2Hover, mA3Hover, mA4Hover,
//		mA5Hover, mA6Hover, mA7Hover;
//
//	//targets - selected targeted boxes able to be selected
//	std::vector<DPhoenix::PrimitiveInstance*> mTargets;
//	std::vector<DPhoenix::PrimitiveInstance*> mTargetBoxes;
//
//	ActionStages mActionStage;
//	DPhoenix::GameTimer mActionTimer;
//
//	//for melee combat
//	int mMeleeDmg;
//	XMFLOAT3 mMeleeStartPos;
//	MeleeStages mMeleeStage;
//	bool mMeleeHit;
//	XMFLOAT3 mMeleeDmgPos;
//
//#pragma endregion LITSActions
//#pragma endregion LITSMembers
//
//public:
//	LITSActions(HINSTANCE hInstance);
//	~LITSActions();
//
//	bool Init(bool fullScreen);
//	void OnResize();
//	void UpdateScene(float dt);
//	void DrawScene();
//
//	//this builds depth stencil and blend states
//	void BuildGeometryBuffers();
//
//	//new method / implements event handling
//	void LITSActions::HandleEvents(DPhoenix::IEvent* e);
//
//	//new method / initialises sounds to be used in the app
//	void InitAudio();
//
//	//new method / specifically handles individual sprite rendering
//	void RenderSprite(DPhoenix::Sprite* sprite,
//		ID3DX11EffectTechnique* tech, bool isHUD = false);
//
//	//new method / specifically handles individual color primitives rendering
//	void RenderColorPrimitive(DPhoenix::PrimitiveInstance* model,
//		ID3DX11EffectTechnique* tech);
//
//	//new method / specifically handles individual textured primitives rendering
//	void LITSActions::RenderBasicTexPrimitive(DPhoenix::PrimitiveInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / specifically handles textured primitives with directional lights
//	//and fog
//	void LITSActions::RenderLitTexPrimitive(DPhoenix::PrimitiveInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / now with normal mapping!
//	void LITSActions::RenderLitTexNormPrimitive(DPhoenix::PrimitiveInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / now with normal mapping!
//	void RenderSkybox(DPhoenix::Sky* skybox,
//		ID3D11DeviceContext* dc);
//
//	//new method / render billboard sprtes
//	void LITSActions::RenderBillboardSprite(DPhoenix::BillboardSprite * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / render static mesh with subsets
//	void LITSActions::RenderBasicModel(DPhoenix::BasicModelInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / render static mesh with subsets
//	void LITSActions::RenderBasicModelNormal(DPhoenix::BasicModelInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / render animated lit mesh with subsets
//	void LITSActions::RenderSkinnedModel(DPhoenix::SkinnedModelInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / render animated lit normal mapped mesh with subsets
//	void LITSActions::RenderSkinnedModelNormal(DPhoenix::SkinnedModelInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	
//#pragma region LITSMethods
//
//	bool LITSActions::CheckPointInRect(int pointX, int pointY, RECT rect);
//	void LITSActions::CheckMouseHoverMenu();
//	void LITSActions::CheckMouseClickMenu();
//
//	void LITSActions::CheckMouseHoverTurns();
//	void LITSActions::CheckMouseClickTurns();
//
//	//for movment
//	void LITSActions::CheckMouseClickRoute();
//	void LITSActions::CheckSelectableRoute();
//	void LITSActions::ResetPath();
//
//	//for actions
//	void LITSActions::CheckMouseHoverActions();
//	void LITSActions::CheckMouseClickActions();
//
//	void LITSActions::ResetTargeting();
//	void LITSActions::CheckMouseClickTarget();
//
//	XMFLOAT2 LITSActions::Convert3Dto2DPoint(XMFLOAT3 pos3d);
//#pragma endregion LITSMethods
//};
//
////our epplication entry point - WinMain
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
//	PSTR cmdLine, int showCmd)
//{
//	// Enable run-time memory check for debug builds.
//#if defined(DEBUG) | defined(_DEBUG)
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//#endif
//
//	LITSActions theApp(hInstance);
//
//	if (!theApp.Init(false))
//		return 0;
//
//	return theApp.Run();
//}
//
////constructor - don't really need to add much here
//LITSActions::LITSActions(HINSTANCE hInstance)
//	: Engine(hInstance)
//{
//	mMainWndCaption = "Big Trouble in Little Toyland";
//	//create camera here to prevent
//	//issues with matrix generation
//	mCamera = new DPhoenix::Camera();
//}
//
////destructor (release any memory as necessary)
//LITSActions::~LITSActions()
//{
//	DPhoenix::Effects::DestroyAll();
//	DPhoenix::InputLayouts::DestroyAll();
//}
//
////any additional initialisation (we generally initiaise game assets here)
//bool LITSActions::Init(bool fullScreen)
//{
//	if (!Engine::Init(fullScreen))
//		return false;
//
//	//initialise the texture manager
//	mTexMgr.Init(md3dDevice);
//
//	// Must init Effects first since InputLayouts depend on shader signatures.
//	DPhoenix::Effects::InitAll(md3dDevice);
//	DPhoenix::InputLayouts::InitAll(md3dDevice);
//
//	//must init soundlayer to then buffer audio
//	DPhoenix::SoundLayer::Create(mhMainWnd);
//	InitAudio();
//
//	//build render / blend modes etc.
//	BuildGeometryBuffers();
//
//	//create geometry
//	mGeoGen = new DPhoenix::GeometryGenerator();
//
//	mBox = new DPhoenix::GeometryGenerator::MeshData();
//
//	mGeoGen->CreateBox(10.0f, 10.0f, 10.0f, *mBox);
//
//	//different material types for effects
//	Material* materialStandard = new Material();
//	Material* materialShiny = new Material();
//
//	materialStandard->Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	materialStandard->Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	materialStandard->Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f);
//	materialStandard->Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
//
//	materialShiny->Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	materialShiny->Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	materialShiny->Specular = XMFLOAT4(0.8f, 0.8f, 0.8f, 16.0f);
//	materialShiny->Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
//
//	//ambient lighting values
//	mAmbientColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	mAmbIntensity = 1.0f;
//
//#pragma region SetupLights
//
//	//direct above - white light (ish)
//	mDirLights.push_back(new DirectionalLight());
//	mDirLights.back()->Ambient = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
//	mDirLights.back()->Diffuse = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
//	mDirLights.back()->Specular = XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);
//	mDirLights.back()->Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
//
//	mNumDirLights = 1;
//
//	//fog values
//	mFogEnabled = true;
//	mFogStart = 100.0f;
//	mFogRange = 200.0f;
//	mFogColor = XMFLOAT4(0.0f, 0.0f, 0.5f, 1.0f);
//
//	//for point lights
//	mRange = 50.0f;
//	mPointRotationValue = 0.0f;
//	mNumPointLights = 0;
//	mPointY = 25.0f;
//
//
//#pragma endregion SetupLights
//
//	//camera and EAngle initialisation (cam in constructor due to use in OnResize)
//	mCamEAngle.r = 0.0f; mCamEAngle.p = 0.0f; mCamEAngle.y = 0.0f;
//
//	//debug font
//	//(Arial size 20 sending window, initial brush, writefactory)
//	mDebugFont = new DPhoenix::Font(mhMainWnd, mBlackBrush, mDWriteFactory, "Arial", 20.0f);
//#pragma region LITSInit
//	mGameState = GAME_TITLE_STATE;
//	mMenuState = CHOOSE_MENUSTATE;
//
//	//intialise the teams
//	mPlayerTeam = new DPhoenix::Team();
//	mEnemyTeam = new DPhoenix::Team();
//
//	//these are intial loads of the characte classes for th epurposes of display on the menus creen
//	//positions, rortation et.
//
//	mFlagShipMenu = new DPhoenix::CharacterClass(DPhoenix::FLAG_SHIP_CLASS, &mTexMgr, md3dDevice, &mAudioMgr);
//	mFlagShipMenu->mModelInstance->mPosition.x = 50.0f;
//	mFlagShipMenu->mModelInstance->mPosition.y = -7.5f;
//	mFlagShipMenu->mModelInstance->mPosition.z = 37.5;
//	mFlagShipMenu->mModelInstance->mScale = XMFLOAT3(3.5f, 3.5f, 3.5f);
//	mFlagShipMenu->mModelInstance->mRotation.y = XMConvertToRadians(90.0f);
//	mFlagShipMenu->mModelInstance->mRotYOffset = -90.0f;
//
//	mBrusierMenu = new DPhoenix::CharacterClass(DPhoenix::BRUSIER_SHIP_CLASS, &mTexMgr, md3dDevice, &mAudioMgr);
//	mBrusierMenu->mModelInstance->mPosition.x = 50.0f;
//	mBrusierMenu->mModelInstance->mPosition.y = -7.5f;
//	mBrusierMenu->mModelInstance->mPosition.z = mFlagShipMenu->mModelInstance->mPosition.z - 12.5f;
//	mBrusierMenu->mModelInstance->mScale = XMFLOAT3(10.0f, 10.0f, 10.0f);
//	mBrusierMenu->mModelInstance->mRotation.y = XMConvertToRadians(90.0f);
//	mBrusierMenu->mModelInstance->mRotYOffset = -90.0f;
//
//	mCorvetteMenu = new DPhoenix::CharacterClass(DPhoenix::CORVETTE_SHIP_CLASS, &mTexMgr, md3dDevice, &mAudioMgr);
//	mCorvetteMenu->mModelInstance->mPosition.x = 50.0f;
//	mCorvetteMenu->mModelInstance->mPosition.y = -7.5f;
//	mCorvetteMenu->mModelInstance->mPosition.z = mBrusierMenu->mModelInstance->mPosition.z - 12.5f;
//	mCorvetteMenu->mModelInstance->mScale = XMFLOAT3(10.0f, 10.0f, 10.0f);
//	mCorvetteMenu->mModelInstance->mRotation.y = XMConvertToRadians(90.0f);
//	mCorvetteMenu->mModelInstance->mRotYOffset = -90.0f;
//
//	mCrusierMenu = new DPhoenix::CharacterClass(DPhoenix::CRUSIER_SHIP_CLASS, &mTexMgr, md3dDevice, &mAudioMgr);
//	mCrusierMenu->mModelInstance->mPosition.x = 50.0f;
//	mCrusierMenu->mModelInstance->mPosition.y = -7.5f;
//	mCrusierMenu->mModelInstance->mPosition.z = mCorvetteMenu->mModelInstance->mPosition.z - 12.5;
//	mCrusierMenu->mModelInstance->mScale = XMFLOAT3(6.0f, 6.0f, 6.0f);
//	mCrusierMenu->mModelInstance->mRotation.y = XMConvertToRadians(90.0f);
//	mCrusierMenu->mModelInstance->mRotYOffset = -90.0f;
//
//
//
//	mSelectedLevel = 1;
//
//	//Inital animations
//	mCrusierMenu->mAnimModel->Animator->SetAnimation(DPhoenix::IDLE_ANIMATION);
//	mBrusierMenu->mAnimModel->Animator->SetAnimation(DPhoenix::IDLE_ANIMATION);
//	mFlagShipMenu->mAnimModel->Animator->SetAnimation(DPhoenix::IDLE_ANIMATION);
//	mCorvetteMenu->mAnimModel->Animator->SetAnimation(DPhoenix::IDLE_ANIMATION);
//
//	//UI elements-------------------
//	mMouseX = 0;
//	mMouseY = 0;
//
//	mTitleScreen = new DPhoenix::Sprite();
//	mTitleScreen->Load("Textures\\Screens\\Screen_Title.png", &mTexMgr, 1600.0f, 900.0f, md3dDevice);
//
//	mTeamMenuScreen = new DPhoenix::Sprite();
//	mTeamMenuScreen->Load("Textures\\Screens\\Screen_Team.png", &mTexMgr, 1600.0f, 900.0f, md3dDevice);
//
//	mSelectedClassMenu = new DPhoenix::Sprite();
//	mSelectedClassMenu->Load("Textures\\UI\\SelectedClass.png", &mTexMgr, 300.0f, 350.0f, md3dDevice);
//	mSelectedClassMenu->mOpacityValue = 0.0f;
//
//	//fonts
//	mUIFont16pt = new DPhoenix::Font(mhMainWnd, mBlackBrush, mDWriteFactory, "showcard Gothic", 16.0f);
//	mUIFont18pt = new DPhoenix::Font(mhMainWnd, mBlackBrush, mDWriteFactory, "showcard Gothic", 18.0f);
//	mUIFont30pt = new DPhoenix::Font(mhMainWnd, mBlackBrush, mDWriteFactory, "showcard Gothic", 30.0f);
//	mUIFont36pt = new DPhoenix::Font(mhMainWnd, mBlackBrush, mDWriteFactory, "showcard Gothic", 36.0f);
//	mUIFont48pt = new DPhoenix::Font(mhMainWnd, mBlackBrush, mDWriteFactory, "showcard Gothic", 48.0f);
//	mUIFont90pt = new DPhoenix::Font(mhMainWnd, mBlackBrush, mDWriteFactory, "showcard Gothic", 90.0f);
//
//
//#pragma region LITSMapInit
//	mSkybox = new DPhoenix::Sky(md3dDevice, "textures\\Skybox\\bedroomSkybox.dds", 5000.0f);
//
//	mFloorColorMaps.insert(mFloorColorMaps.end(),
//		{ "Textures\\Floor\\Floor_B_cm.png", "Textures\\Floor\\Floor_C_cm.png", "Textures\\Floor\\Floor_D_cm.png",
//		"Textures\\Floor\\Floor_F_cm.png", "Textures\\Floor\\Floor_G_cm.png", "Textures\\Floor\\Floor_H_cm.png",
//		"Textures\\Floor\\Floor_J_cm.png", "Textures\\Floor\\Floor_K_cm.png", "Textures\\Floor\\Floor_L_cm.png",
//		"Textures\\Floor\\Floor_M_cm.png", "Textures\\Floor\\Floor_N_cm.png", "Textures\\Floor\\Floor_P_cm.png",
//		"Textures\\Floor\\Floor_Q_cm.png", "Textures\\Floor\\Floor_R_cm.png", "Textures\\Floor\\Floor_S_cm.png",
//		"Textures\\Floor\\Floor_T_cm.png", "Textures\\Floor\\Floor_V_cm.png", "Textures\\Floor\\Floor_W_cm.png",
//		"Textures\\Floor\\Floor_X_cm.png", "Textures\\Floor\\Floor_X_cm.png", "Textures\\Floor\\Floor_Z_cm.png", });
//
//	mFloorNormalMaps.insert(mFloorNormalMaps.end(),
//		{ "Textures\\Floor\\Floor_B_nm.png", "Textures\\Floor\\Floor_C_nm.png", "Textures\\Floor\\Floor_D_nm.png",
//		"Textures\\Floor\\Floor_F_nm.png", "Textures\\Floor\\Floor_G_nm.png", "Textures\\Floor\\Floor_H_nm.png",
//		"Textures\\Floor\\Floor_J_nm.png", "Textures\\Floor\\Floor_K_nm.png", "Textures\\Floor\\Floor_L_nm.png",
//		"Textures\\Floor\\Floor_M_nm.png", "Textures\\Floor\\Floor_N_nm.png", "Textures\\Floor\\Floor_P_nm.png",
//		"Textures\\Floor\\Floor_Q_nm.png", "Textures\\Floor\\Floor_R_nm.png", "Textures\\Floor\\Floor_S_nm.png",
//		"Textures\\Floor\\Floor_T_nm.png", "Textures\\Floor\\Floor_V_nm.png", "Textures\\Floor\\Floor_W_nm.png",
//		"Textures\\Floor\\Floor_X_nm.png", "Textures\\Floor\\Floor_X_nm.png", "Textures\\Floor\\Floor_Z_nm.png", });
//
//	mWallColorMaps.insert(mWallColorMaps.end(),
//		{ "Textures\\Wall\\Wall_A_cm.png","Textures\\Wall\\Wall_E_cm.png","Textures\\Wall\\Wall_I_cm.png",
//		"Textures\\Wall\\Wall_O_cm.png", "Textures\\Wall\\Wall_U_cm.png" });
//	mWallNormalMaps.insert(mWallNormalMaps.end(),
//		{ "Textures\\Wall\\Wall_A_nm.png","Textures\\Wall\\Wall_E_nm.png","Textures\\Wall\\Wall_I_nm.png",
//		"Textures\\Wall\\Wall_O_nm.png", "Textures\\Wall\\Wall_U_nm.png" });
//	mCoverColorMaps.insert(mCoverColorMaps.end(),
//		{ "Textures\\Cover\\Cover_DeanyP_cm.png", "Textures\\Cover\\Cover_Humpty_cm.png", "Textures\\Cover\\Cover_Ninja_cm.png",
//		"Textures\\Cover\\Cover_SS_cm.png" });
//	mCoverNormalMaps.insert(mCoverNormalMaps.end(),
//		{ "Textures\\Cover\\Cover_DeanyP_nm.png", "Textures\\Cover\\Cover_Humpty_nm.png", "Textures\\Cover\\Cover_Ninja_nm.png",
//		"Textures\\Cover\\Cover_SS_nm.png" });
//
//	/*mMap = new DPhoenix::LITSMap("Data\\Levels\\Level1.csv", &mTexMgr, md3dDevice,
//	mEnemySpawnVec, mPlayerSpawnVec, mBeaconSpawnVec,
//	&mBox, mFloorColorMaps, mFloorNormalMaps, mWallColorMaps, mWallNormalMaps,
//	mCoverColorMaps, mCoverNormalMaps, 30, 30, 20.0f);*/
//
//	mGeoGen->CreateBox(20.0f, 20.0f, 20.0f, *mBox);
//
//	mMap = new DPhoenix::LITSMap("Data\\Levels\\Level1.csv", &mTexMgr, md3dDevice,
//		mEnemySpawnVec, mPlayerSpawnVec, mBeaconSpawnVec,
//		mBox, mFloorColorMaps, mFloorNormalMaps, mWallColorMaps, mWallNormalMaps,
//		mCoverColorMaps, mCoverNormalMaps, 30, 30, 20.0f);
//
//	mCameraDistanceOffset = 50.0f;
//	mCamToFocusAngle = 45.0f;
//
//
//
//#pragma endregion LITSMapInit
//#pragma region LITSUIInit
//	//posision cals are hard - needed to take into account origni 0,0 id screen sprite
//	//luckily all pos are catalogued in LBTS const.h tweaking easier
//
//	mActionsUISprite = new DPhoenix::Sprite();
//	mActionsUISprite->Load("Textures\\UI\\ActionsUI.png", &mTexMgr,
//		LITSConst::gameActionsPanelWidth, LITSConst::gameActionsPanelHeight, md3dDevice);
//	mActionsUISprite->mPosition = XMFLOAT3(LITSConst::gameActionsPanelLeft + LITSConst::gameActionsPanelWidth / 2,
//		LITSConst::gameActionsPanelTop - LITSConst::gameActionsPanelWidth / 2, 0.0f);
//
//	mBeaconsUISprite = new DPhoenix::Sprite();
//	mBeaconsUISprite->Load("Textures\\UI\\BeaconsUI.png", &mTexMgr,
//		LITSConst::gameBeaconsPanelWidth, LITSConst::gameBeaconsPanelHeight, md3dDevice);
//	mBeaconsUISprite->mPosition = XMFLOAT3(LITSConst::gameBeaconsPanelLeft + LITSConst::gameBeaconsPanelWidth / 2,
//		LITSConst::gameBeaconsPanelTop - LITSConst::gameBeaconsPanelHeight / 2, 0.0f);
//
//	mEnemyUISprite = new DPhoenix::Sprite();
//	mEnemyUISprite->Load("Textures\\UI\\EnemyUI.png", &mTexMgr,
//		LITSConst::gameEnemyPanelWidth, LITSConst::gameEnemyPanelHeight, md3dDevice);
//	mEnemyUISprite->mPosition = XMFLOAT3(LITSConst::gameEnemyPanelLeft + LITSConst::gameEnemyPanelWidth / 2,
//		LITSConst::gameEnemyPanelTop - LITSConst::gameEnemyPanelHeight / 2, 0.0f);
//
//	mStatusUISprite = new DPhoenix::Sprite();
//	mStatusUISprite->Load("Textures\\UI\\StatusUI.png", &mTexMgr,
//		LITSConst::gameStatusPanelWidth, LITSConst::gameStatusPanelHeight, md3dDevice);
//	mStatusUISprite->mPosition = XMFLOAT3(LITSConst::gameStatusPanelLeft + LITSConst::gameStatusPanelWidth / 2,
//		LITSConst::gameStatusPanelTop - LITSConst::gameStatusPanelHeight / 2, 0.0f);
//
//	mPlayerTeamUISprite = new DPhoenix::Sprite();
//	mPlayerTeamUISprite->Load("Textures\\UI\\PlayerTeam.png", &mTexMgr,
//		LITSConst::gamePlayerPanelWidth, LITSConst::gamePlayerPanelHeight, md3dDevice);
//	mPlayerTeamUISprite->mPosition = XMFLOAT3(LITSConst::gamePlayerPanelLeft + LITSConst::gamePlayerPanelWidth / 2,
//		LITSConst::gamePlayerPanelTop - LITSConst::gamePlayerPanelHeight / 2, 0.0f);
//
//	mHoverdTurnUISprite = new DPhoenix::Sprite();
//	mHoverdTurnUISprite->Load("Textures\\UI\\HoveredTurn.png", &mTexMgr,
//		LITSConst::gameTurnsHoverWidth, LITSConst::gameTurnsHoverHeight, md3dDevice);
//
//	mSelectedTurnUISprite = new DPhoenix::Sprite();
//	mSelectedTurnUISprite->Load("Textures\\UI\\SelectedTurn.png", &mTexMgr,
//		LITSConst::gameTurnsHoverWidth, LITSConst::gameTurnsHoverHeight, md3dDevice);
//
//	mTakenTurnUISprite = new DPhoenix::Sprite();
//	mTakenTurnUISprite->Load("Textures\\UI\\takenTurn.png", &mTexMgr,
//		LITSConst::gameTurnsHoverWidth, LITSConst::gameTurnsHoverHeight, md3dDevice);
//
//	mSelectedActionUISprite = new DPhoenix::Sprite();
//	mSelectedActionUISprite->Load("Textures\\UI\\SelectedAction.png", &mTexMgr,
//		LITSConst::gameActionHoverWidth, LITSConst::gameActionHoverHeight, md3dDevice);
//
//	mHoverdActionUISprite = new DPhoenix::Sprite();
//	mHoverdActionUISprite->Load("Textures\\UI\\HoveredAction.png", &mTexMgr,
//		LITSConst::gameActionHoverWidth, LITSConst::gameActionHoverHeight, md3dDevice);
//
//	//avatars
//	mFlagShipAvatar = new DPhoenix::Sprite();
//	mFlagShipAvatar->Load("Textures\\UI\\SoldierAvatar.png", &mTexMgr,
//		LITSConst::gameAvatarWidth, LITSConst::gameAvatarHeight, md3dDevice);
//
//	mBrusierAvatar = new DPhoenix::Sprite();
//	mBrusierAvatar->Load("Textures\\UI\\AngelAvatar.png", &mTexMgr,
//		LITSConst::gameAvatarWidth, LITSConst::gameAvatarHeight, md3dDevice);
//
//	mCorvetteAvatar = new DPhoenix::Sprite();
//	mCorvetteAvatar->Load("Textures\\UI\\DragonAvatar.png", &mTexMgr,
//		LITSConst::gameAvatarWidth, LITSConst::gameAvatarHeight, md3dDevice);
//
//	mCrusierAvatar = new DPhoenix::Sprite();
//	mCrusierAvatar->Load("Textures\\UI\\CatAvatar.png", &mTexMgr,
//		LITSConst::gameAvatarWidth, LITSConst::gameAvatarHeight, md3dDevice);
//
//	//set early but not used unti in game state
//	mCurrentTeam = DPhoenix::PLAYER_TEAM;
//
//	//intit flag for cam pos
//	mCameraBehindFlag = false;
//
//#pragma endregion LITSUIInit
//#pragma region LITSInitMovement
//
//	//null caerma line and create in gameplay
//	mCameraLine = NULL;
//	//generate small grid for overlay on map blocks
//	mSelectionBox = new DPhoenix::GeometryGenerator::MeshData();
//	mGeoGen->CreateGrid(20.0f, 20.0f, 2, 2, *mSelectionBox);
//
//	//set up standard templates to copy as new instances as needed for higlights
//	mSelectionHighLight = new DPhoenix::PrimitiveInstance();
//	mSelectionHighLight->LoadLitTexInstance(md3dDevice, "Textures\\Select\\SelectTileGreen_cm.png", mSelectionBox, &mTexMgr);
//	mSelectionHighLight->mMaterial = materialShiny;
//	mSelectionHighLight->mNormalMap = mTexMgr.CreateTexture("Textures\\Select\\SelectTileGreen_nm.png");
//
//	mBadSelectionHighLight = new DPhoenix::PrimitiveInstance();
//	mBadSelectionHighLight->LoadLitTexInstance(md3dDevice, "Textures\\Select\\SelectTileRed_cm.png", mSelectionBox, &mTexMgr);
//	mBadSelectionHighLight->mMaterial = materialShiny;
//	mBadSelectionHighLight->mNormalMap = mTexMgr.CreateTexture("Textures\\Select\\SelectTileRed_nm.png");
//
//	mTargetHighlight = new DPhoenix::PrimitiveInstance();
//	mTargetHighlight->LoadLitTexInstance(md3dDevice, "Textures\\Select\\SelectTileBlue_cm.png", mSelectionBox, &mTexMgr);
//	mTargetHighlight->mMaterial = materialShiny;
//	mTargetHighlight->mNormalMap = mTexMgr.CreateTexture("Textures\\Select\\SelectTileBlue_nm.png");
//
//	//COLLISIONS
//	mGobalCollisionOn = true;
//	mClickFlag = false;
//#pragma endregion LITSInitMovement
//
//#pragma region LITSActionsInit
//	//select flags init
//	mGotActions = false;
//	mA1Hover = mA2Hover = mA3Hover = mA4Hover = mA5Hover = mA6Hover = mA7Hover = false;
//
//
//
//	mActionStage = AC_INITIAL;
//
//	mMeleeDmg = 0;
//	mMeleeStage = GOTO_TARGET_MEL;
//	mMeleeHit = false;
//
//#pragma endregion LITSActionsInit
//
//#pragma endregion LITSInit
//	return true;
//}
//
////here we give a point location and see if is in the given rect
//bool LITSActions::CheckPointInRect(int pointX, int pointY, RECT rect)
//{
//	if (pointX < rect.left)
//		return false;
//	if (pointX > rect.right)
//		return false;
//	if (pointY > rect.top)
//		return false;
//	if (pointY < rect.bottom)
//		return false;
//	return true;
//}
//
////check for where we are hvoering for selction display
//void LITSActions::CheckMouseHoverMenu()
//{
//	//adjustments ot be made to postions has origin 0, 0 in centre
//
//	int mouseX = mMouseX - 800;
//	int mouseY = 450 - mMouseY;
//
//	//here we check each of the calss elcteion areas base on theconstants idnietified
//	//we will chnage the pos of the hover image and opaity based on this
//	if (CheckPointInRect(mouseX, mouseY, LITSConst::selectBrusier))
//	{
//		mSelectedClassMenu->mPosition.x = LITSConst::selectBrusier.left + LITSConst::selectHoverImageWidth / 2;
//		mSelectedClassMenu->mPosition.y = LITSConst::selectBrusier.top - LITSConst::selectHoverImageHeight / 2;
//		mSelectedClassMenu->mOpacityValue = 1.0f;
//	}
//	else if (CheckPointInRect(mouseX, mouseY, LITSConst::selectCrusier))
//	{
//		mSelectedClassMenu->mPosition.x = LITSConst::selectCrusier.left + LITSConst::selectHoverImageWidth / 2;
//		mSelectedClassMenu->mPosition.y = LITSConst::selectCrusier.top - LITSConst::selectHoverImageHeight / 2;
//		mSelectedClassMenu->mOpacityValue = 1.0f;
//	}
//	else if (CheckPointInRect(mouseX, mouseY, LITSConst::selectFlagShip))
//	{
//		mSelectedClassMenu->mPosition.x = LITSConst::selectFlagShip.left + LITSConst::selectHoverImageWidth / 2;
//		mSelectedClassMenu->mPosition.y = LITSConst::selectFlagShip.top - LITSConst::selectHoverImageHeight / 2;
//		mSelectedClassMenu->mOpacityValue = 1.0f;
//	}
//
//	else if (CheckPointInRect(mouseX, mouseY, LITSConst::selectCorvette))
//	{
//		mSelectedClassMenu->mPosition.x = LITSConst::selectCorvette.left + LITSConst::selectHoverImageWidth / 2;
//		mSelectedClassMenu->mPosition.y = LITSConst::selectCorvette.top - LITSConst::selectHoverImageHeight / 2;
//		mSelectedClassMenu->mOpacityValue = 1.0f;
//	}
//	else
//	{
//		mSelectedClassMenu->mOpacityValue = 0.0f;
//	}
//
//
//}
//
//void LITSActions::CheckMouseClickMenu()
//{
//	//adjustments to be made to pos as DX11 has origin as 0,0 in centre
//	int mouseX = mMouseX - 800;
//	int mouseY = 450 - mMouseY;
//
//	//class selection - once picked, create a copy and add to the player team
//	if (CheckPointInRect(mouseX, mouseY, LITSConst::selectBrusier))
//	{
//		if (mPlayerTeam->mTeamMembers.size() < 4)
//		{
//			mPlayerTeam->mTeamMembers.push_back(new DPhoenix::CharacterClass(*mBrusierMenu));
//		}
//	}
//	else if (CheckPointInRect(mouseX, mouseY, LITSConst::selectCrusier))
//	{
//		if (mPlayerTeam->mTeamMembers.size() < 4)
//		{
//			mPlayerTeam->mTeamMembers.push_back(new DPhoenix::CharacterClass(*mCrusierMenu));
//		}
//	}
//	else if (CheckPointInRect(mouseX, mouseY, LITSConst::selectFlagShip))
//	{
//		if (mPlayerTeam->mTeamMembers.size() < 4)
//		{
//			mPlayerTeam->mTeamMembers.push_back(new DPhoenix::CharacterClass(*mFlagShipMenu));
//		}
//	}
//	else if (CheckPointInRect(mouseX, mouseY, LITSConst::selectCorvette))
//	{
//		if (mPlayerTeam->mTeamMembers.size() < 4)
//		{
//			mPlayerTeam->mTeamMembers.push_back(new DPhoenix::CharacterClass(*mCorvetteMenu));
//		}
//	}
//	else if (CheckPointInRect(mouseX, mouseY, LITSConst::selectUpArrow))
//	{
//		//change and bound level value - recal all stats
//		if (mSelectedLevel < 20)
//		{
//			mSelectedLevel++;
//			mBrusierMenu->CalculateStats(mSelectedLevel);
//			mCrusierMenu->CalculateStats(mSelectedLevel);
//			mFlagShipMenu->CalculateStats(mSelectedLevel);
//			mCorvetteMenu->CalculateStats(mSelectedLevel);
//
//			for (int i = 0; i < mPlayerTeam->mTeamMembers.size(); i++)
//			{
//				mPlayerTeam->mTeamMembers[i]->CalculateStats(mSelectedLevel);
//			}
//		}
//	}
//
//	else if (CheckPointInRect(mouseX, mouseY, LITSConst::selectDownArrow))
//	{
//		//change and bound level value - recal all stats
//		if (mSelectedLevel > 1)
//		{
//			mSelectedLevel--;
//			mBrusierMenu->CalculateStats(mSelectedLevel);
//			mCrusierMenu->CalculateStats(mSelectedLevel);
//			mFlagShipMenu->CalculateStats(mSelectedLevel);
//			mCorvetteMenu->CalculateStats(mSelectedLevel);
//
//			for (int i = 0; i < mPlayerTeam->mTeamMembers.size(); i++)
//			{
//				mPlayerTeam->mTeamMembers[i]->CalculateStats(mSelectedLevel);
//			}
//		}
//	}
//
//	else if (CheckPointInRect(mouseX, mouseY, LITSConst::selectRemoveLast))
//	{
//		//pop / remove last entry in player temas member
//		if (mPlayerTeam->mTeamMembers.size() > 0)
//		{
//			mPlayerTeam->mTeamMembers.pop_back();
//		}
//	}
//}
//
////Hovwe check for player turns panel
//void LITSActions::CheckMouseHoverTurns()
//{
//	//adjustments to be nade to pos as DX11 has origin as 0,0 in centre
//	int mouseX = mMouseX - 800;
//	int mouseY = 450 - mMouseY;
//
//	//unset falgs before checks
//	mP1Hover = mP2Hover = mP3Hover = mP4Hover = false;
//
//	//if it is the player team and the current member is in the pick ruoute movestate
//	//check each row of the player panel to see if is shouldbe hoverd
//
//	if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//		mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKRT_MOVESTATE)
//	{
//		if (CheckPointInRect(mouseX, mouseY, LITSConst::gamePlayer1Section))
//		{
//			mP1Hover = true;
//		}
//		else if (CheckPointInRect(mouseX, mouseY, LITSConst::gamePlayer2Section))
//		{
//			mP2Hover = true;
//		}
//		else if (CheckPointInRect(mouseX, mouseY, LITSConst::gamePlayer3Section))
//		{
//			mP3Hover = true;
//		}
//		else if (CheckPointInRect(mouseX, mouseY, LITSConst::gamePlayer4Section))
//		{
//			mP4Hover = true;
//		}
//	}
//}
//
//
////if clcikng on player turns panle m what member select
//void LITSActions::CheckMouseClickTurns()
//{
//	int currentMember = mPlayerTeam->mCurrentMember;
//	//based on hover flag - send the meber index to the team
//	if (mCurrentTeam == DPhoenix::PLAYER_TEAM)
//	{
//		if (mP1Hover) mPlayerTeam->SelectMember(0);
//		if (mP2Hover) mPlayerTeam->SelectMember(1);
//		if (mP3Hover) mPlayerTeam->SelectMember(2);
//		if (mP4Hover) mPlayerTeam->SelectMember(3);
//	}
//
//	if (currentMember != mPlayerTeam->mCurrentMember)
//		ResetPath();
//}
//
////lcik check for the route
//void LITSActions::CheckMouseClickRoute()
//{
//	//loop though the selection noxes to check for a collision
//	for (int i = 0; i < mSelectionBoxes.size(); i++)
//	{
//		if (mSelectionBoxes[i]->mCollided)
//		{
//			//get the col / row of the selection box based on pos
//			int col = mMap->GetColFromPosition(mSelectionBoxes[i]->mPosition);
//			int row = mMap->GetRowFromPosition(mSelectionBoxes[i]->mPosition);
//
//			//as long as e have a floor block with no special flag
//			if (mMap->mTiles[col][row]->mSpecialFlag == DPhoenix::NO_SP_FLAG &&
//				mMap->mTiles[col][row]->mMapBlockType == DPhoenix::FLOOR_MAPBLOCK)
//			{
//				//push bac a copy of the current selection box to the happy path
//				mHappyPath.push_back(new DPhoenix::PrimitiveInstance(*mSelectionBoxes[i]));
//				//make more solid / opaque
//				mHappyPath.back()->mOpacity = 0.95f;
//				//decerment tp pool
//				mPlayerTeam->mTPPool--;
//				//set sepcial falg of current map block to happy path
//				mMap->mTiles[col][row]->mSpecialFlag = DPhoenix::HAPPY_PATH_SP_FLAG;
//			}
//		}
//	}
//
//	//set all selection boxes to not alive so engine buries team
//	for (int i = 0; i < mSelectionBoxes.size(); i++)
//	{
//		mSelectionBoxes[i]->mAlive = false;
//	}
//	//clear the slection boxes and checl selectable route at this point
//	mSelectionBoxes.clear();
//	CheckSelectableRoute();
//}
//
//void LITSActions::CheckMouseHoverActions()
//{
//	//adjustment to be amde to positions as dx11 has origin as 0, 0 in centre
//	int mouseX = mMouseX - 800;
//	int mouseY = 450 - mMouseY;
//
//	//unset hover flags
//	mA1Hover = mA2Hover = mA3Hover = mA4Hover = mA5Hover = mA6Hover = mA7Hover = false;
//
//	//ame sure we are the player and we can pick an actions
//	if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//		mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKAC_MOVESTATE)
//	{
//		//for each possible action - we need to know if the hover is in the area
//		//and if that action is available to set the hover flag
//		if (CheckPointInRect(mouseX, mouseY, LITSConst::actionSelect1Section)
//			&& mPlayerTeam->mAvailableActions.size() > 0)
//		{
//			mA1Hover = true;
//		}
//		if (CheckPointInRect(mouseX, mouseY, LITSConst::actionSelect2Section)
//			&& mPlayerTeam->mAvailableActions.size() > 1)
//		{
//			mA2Hover = true;
//		}
//		if (CheckPointInRect(mouseX, mouseY, LITSConst::actionSelect3Section)
//			&& mPlayerTeam->mAvailableActions.size() > 2)
//		{
//			mA3Hover = true;
//		}
//		if (CheckPointInRect(mouseX, mouseY, LITSConst::actionSelect4Section)
//			&& mPlayerTeam->mAvailableActions.size() > 3)
//		{
//			mA4Hover = true;
//		}
//		if (CheckPointInRect(mouseX, mouseY, LITSConst::actionSelect5Section)
//			&& mPlayerTeam->mAvailableActions.size() > 4)
//		{
//			mA5Hover = true;
//		}
//		if (CheckPointInRect(mouseX, mouseY, LITSConst::actionSelect6Section)
//			&& mPlayerTeam->mAvailableActions.size() > 5)
//		{
//			mA6Hover = true;
//		}
//		if (CheckPointInRect(mouseX, mouseY, LITSConst::actionSelect7Section)
//			&& mPlayerTeam->mAvailableActions.size() > 6)
//		{
//			mA7Hover = true;
//		}
//	}
//}
//
//void LITSActions::CheckMouseClickActions()
//{
//	//current member before selection
//	int currentMember = mPlayerTeam->mCurrentMember;
//
//	//if we can pick an action check each hover flag to send the right id
//	if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//		mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKAC_MOVESTATE)
//	{
//		if (mA1Hover) mPlayerTeam->CheckSelectedAction(0);
//		if (mA2Hover) mPlayerTeam->CheckSelectedAction(1);
//		if (mA3Hover) mPlayerTeam->CheckSelectedAction(2);
//		if (mA4Hover) mPlayerTeam->CheckSelectedAction(3);
//		if (mA5Hover) mPlayerTeam->CheckSelectedAction(4);
//		if (mA6Hover) mPlayerTeam->CheckSelectedAction(5);
//		if (mA7Hover) mPlayerTeam->CheckSelectedAction(6);
//	}
//	//reset path for new member if hold still selected
//	if (currentMember != mPlayerTeam->mCurrentMember)
//		ResetPath();
//}
//
//void LITSActions::ResetTargeting()
//{
//	//assimption this only called if new action selected for player member
//	//picking action
//
//	mTargets.clear();
//	//set to unalive so buried by engine
//	for (int i = 0; i < mTargetBoxes.size(); i++)
//	{
//		mTargetBoxes[i]->mAlive = false;
//	}
//
//	mTargetBoxes.clear();
//
//	//get current row col based on player position
//	int currentRow =
//		mMap->GetRowFromPosition(mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mModelInstance->mPosition);
//	int currentCol =
//		mMap->GetColFromPosition(mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mModelInstance->mPosition);
//
//	//for control of selection areas
//	XMFLOAT3 spawnPosition;
//	int minRow = 0;
//	int maxRow = 0;
//	int minCol = 0;
//	int maxCol = 0;
//
//	switch (mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mSelectedAction)
//	{
//	case DPhoenix::HIT_ACTION:
//		//set checking for only adjacent squares of vaild tiles
//		minRow = max(currentRow - 1, 0);
//		maxRow = min(currentRow + 1, mMap->mWidth - 1);
//		minCol = max(currentCol - 1, 0);
//		maxCol = min(currentCol + 1, mMap->mLength - 1);
//
//		//loop thorugh rows and columns in rnage
//		for (int col = minCol; col <= maxCol; col++)
//		{
//			for (int row = minRow; row <= maxRow; row++)
//			{
//				// bit checking current tile
//				if (!(currentCol == col && currentRow == row))
//				{
//					//check if enemy on adjacent square
//					if (mMap->mTiles[col][row]->mSpecialFlag == DPhoenix::ENEMY_SP_FLAG)
//					{
//						//if so ge the position to set the target highlight for possible selections
//						spawnPosition = mMap->GetPositionABoveFromMapRef(col, row);
//						mTargetBoxes.push_back(new DPhoenix::PrimitiveInstance(*mTargetHighlight));
//						mTargetBoxes.back()->mPosition = spawnPosition;
//						mTargetBoxes.back()->mPrevPosition = mTargetBoxes.back()->mPosition;
//						mTargetBoxes.back()->mOpacity = 0.25f;
//						//need to set collision types and entity properties
//						mTargetBoxes.back()->mEntityType = DPhoenix::ENTITY_SELECTION;
//						mTargetBoxes.back()->mHalfSizes.x = 10.0f; mTargetBoxes.back()->mHalfSizes.z = 10.0f;
//						mTargetBoxes.back()->mCollidable = true;
//						AddEntity(mTargetBoxes.back());
//					}
//				}
//			}
//		}
//		break;
//	}
//
//}
//
//void LITSActions::CheckMouseClickTarget()
//{
//	//loop through the target boxes to see if any collided
//	for (int i = 0; i < mTargetBoxes.size(); i++)
//	{
//		//if collided
//		if (mTargetBoxes[i]->mCollided)
//		{
//			//hten we clear the current target vector and then push back a copy
//			//of the collided target selection
//			mTargets.clear();
//			mTargets.push_back(new DPhoenix::PrimitiveInstance(*mTargetBoxes[i]));
//			mTargets.back()->mOpacity = 0.95f;
//		}
//	}
//}
//
////for damage text display etc, takes in 3D position to conver to screen co-ords
//XMFLOAT2 LITSActions::Convert3Dto2DPoint(XMFLOAT3 pos3d)
//{
//	//need to convert to bector to use project fiction
//	XMVECTOR vec3d = XMLoadFloat3(&pos3d);
//	//identity matrix necessary for project function
//	XMMATRIX identity = XMMatrixIdentity();
//	//ased upon the view port propties ND CAMERA matrices
//	//project to area on 2D screen
//	XMVECTOR vec2d = XMVector3Project(vec3d,
//		mScreenViewport.TopLeftX,
//		mScreenViewport.TopLeftY,
//		mScreenViewport.Width,
//		mScreenViewport.Height,
//		mScreenViewport.MinDepth,
//		mScreenViewport.MaxDepth,
//		mCamera->GetProj(),
//		mCamera->GetView(),
//		identity);
//
//	//convert result to XMFLOAT2 and return
//	XMFLOAT2 pos2d;
//	XMStoreFloat2(&pos2d, vec2d);
//
//	return pos2d;
//}
//
//
//void LITSActions::CheckSelectableRoute()
//{
//	//check tile surrounding selection
//	//might beaa but lol - prob a awy of doing an elaborate loop on it
//	int currentTileCol = mMap->GetColFromPosition(mHappyPath.back()->mPosition);
//	int currentTileRow = mMap->GetRowFromPosition(mHappyPath.back()->mPosition);
//	XMFLOAT3 spawnPosition;
//
//	//check enough tp leftfor 2 tp each of remainng members
//	if (mPlayerTeam->mTPPool > mPlayerTeam->mTurnsLeft * 2)
//	{
//		//some ardcoded values here - we want to go from - 1 to 1
//		for (int i = 0; i < 4; i++)
//		{
//			bool validMove = true;
//			bool validSelection = false;
//
//			DPhoenix::MapBlock* targetMapBlock;
//
//			//check if valid move and set target for selection - 4 adjacent squares
//			switch (i)
//			{
//			case 0:
//				if (currentTileCol - 1 < 0)
//					validMove = false;
//				else
//				{
//					spawnPosition = mMap->GetPositionABoveFromMapRef(currentTileCol - 1, currentTileRow);
//					targetMapBlock = mMap->mTiles[currentTileCol - 1][currentTileRow];
//				}
//				break;
//			case 1:
//				if (currentTileCol + 1 >= mMap->mWidth) validMove = false;
//				else
//				{
//					spawnPosition = mMap->GetPositionABoveFromMapRef(currentTileCol + 1, currentTileRow);
//					targetMapBlock = mMap->mTiles[currentTileCol + 1][currentTileRow];
//				}
//				break;
//			case 2:
//				if (currentTileRow - 1 < 0) validMove = false;
//				else
//				{
//					spawnPosition = mMap->GetPositionABoveFromMapRef(currentTileCol, currentTileRow - 1);
//					targetMapBlock = mMap->mTiles[currentTileCol][currentTileRow - 1];
//				}
//				break;
//			case 3:
//				if (currentTileRow + 1 >= mMap->mLength) validMove = false;
//				else
//				{
//					spawnPosition = mMap->GetPositionABoveFromMapRef(currentTileCol, currentTileRow + 1);
//					targetMapBlock = mMap->mTiles[currentTileCol][currentTileRow + 1];
//				}
//				break;
//			}
//
//			//if a valid move check the block type
//			if (validMove)
//			{
//				//if it is a floor block with no special flag, it is valid to add
//				if (targetMapBlock->mMapBlockType == DPhoenix::FLOOR_MAPBLOCK &&
//					targetMapBlock->mMapBlockType == DPhoenix::NO_SP_FLAG)
//				{
//					mSelectionBoxes.push_back(new DPhoenix::PrimitiveInstance(*mSelectionHighLight));
//					validSelection = true;
//				}
//
//				//if it is a cover or wall block with no special flag, it is valid to add
//				if (targetMapBlock->mMapBlockType == DPhoenix::COVER_MAPBLOCK ||
//					targetMapBlock->mMapBlockType == DPhoenix::WALL_MAPBLOCK)
//				{
//					mSelectionBoxes.push_back(new DPhoenix::PrimitiveInstance(*mBadSelectionHighLight));
//					validSelection = true;
//				}
//
//				if (validSelection)
//				{
//					//now set pos and propeties
//					mSelectionBoxes.back()->mPosition = spawnPosition;
//					mSelectionBoxes.back()->mPrevPosition = mSelectionBoxes.back()->mPosition;
//					mSelectionBoxes.back()->mOpacity = 0.7f;
//					//enetity / collideable propeties needed for collision with cursoir / camera line
//					mSelectionBoxes.back()->mEntityType = DPhoenix::ENTITY_SELECTION;
//					mSelectionBoxes.back()->mHalfSizes.x = 10.0f; mSelectionBoxes.back()->mHalfSizes.z = 10.0f;
//					mSelectionBoxes.back()->mCollidable = true;
//					AddEntity(mSelectionBoxes.back());
//				}
//			}
//		}
//	}
//}
////reset happy path
//void LITSActions::ResetPath()
//{
//	//clear the happy path
//	mHappyPath.clear();
//
//	//set all current selection boxes to not alive so buried by engine
//	for (int i = 0; i < mSelectionBoxes.size(); i++)
//	{
//		mSelectionBoxes[i]->mAlive = false;
//	}
//
//	mSelectionBoxes.clear();
//
//	//push nac the first happy path step based on the current player's position
//	mHappyPath.push_back(new DPhoenix::PrimitiveInstance(*mSelectionHighLight));
//	//get map colimn and row of current pos
//	int pathCol = mMap->GetColFromPosition(mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mModelInstance->mPosition);
//	int pathRow = mMap->GetRowFromPosition(mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mModelInstance->mPosition);
//	//now update the first happy path square with the correct pos
//	mHappyPath.back()->mPosition = mMap->GetPositionABoveFromMapRef(pathCol, pathRow);
//	mHappyPath.back()->mOpacity = 0.75f;
//
//	//resert all happy path flags thorugh ourt the map
//	for (int col = 0; col < mMap->mWidth; col++)
//	{
//		for (int row = 0; row < mMap->mLength; row++)
//		{
//			if (mMap->mTiles[col][row]->mSpecialFlag == DPhoenix::HAPPY_PATH_SP_FLAG)
//				mMap->mTiles[col][row]->mSpecialFlag = DPhoenix::NO_SP_FLAG;
//		}
//	}
//
//	//check selectable squares to move to
//	CheckSelectableRoute();
//}
////what to do on resize - mainly we'lll just call the parent / engine's method
//void LITSActions::OnResize()
//{
//	Engine::OnResize();
//
//	//the window resized so the aspect ratio needs
//	//to be calculated again, and the projection matrix
//	mCamera->SetPerspective(0.25f * XM_PI, AspectRatio(), 1.0f, 100000.0f);
//}
//
////update scene - here is where our update logic for the game loop goes
//void LITSActions::UpdateScene(float dt)
//{
//	//calculate scaling based on window dimensions
//	mScreenScale.x = (float)mClientWidth / 1440;
//	mScreenScale.y = (float)mClientHeight / 900;
//
//	switch (mGameState)
//	{
//	case GAME_MENU_STATE:
//		mDirLights.back()->Ambient = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
//		mDirLights.back()->Direction = XMFLOAT3(1.0f, 0.0f, 0.0f);
//
//		mBrusierMenu->mModelInstance->mInstanceAnimator->SetAnimation(DPhoenix::IDLE_ANIMATION);
//		mCrusierMenu->mModelInstance->mInstanceAnimator->SetAnimation(DPhoenix::IDLE_ANIMATION);
//		mFlagShipMenu->mModelInstance->mInstanceAnimator->SetAnimation(DPhoenix::IDLE_ANIMATION);
//		mCorvetteMenu->mModelInstance->mInstanceAnimator->SetAnimation(DPhoenix::IDLE_ANIMATION);
//
//		mBrusierMenu->mModelInstance->Update(dt, true);
//		mCrusierMenu->mModelInstance->Update(dt, true);
//		mFlagShipMenu->mModelInstance->Update(dt, true);
//		mCorvetteMenu->mModelInstance->Update(dt, true);
//
//		switch (mMenuState)
//		{
//		case CONFIRM_MENUSTATE:
//		case ENEMY_1_PICKED_MENUSTATE:
//		case ENEMY_2_PICKED_MENUSTATE:
//		case ENEMY_3_PICKED_MENUSTATE:
//
//			//2 seconds between each enemy pick
//			if (mWaitTimer.TotalTime() > 2.0f)
//			{
//				srand(time(0));
//				//random number between 0 and 3 to get class
//				int rng = rand() % +4;
//
//				switch (rng)
//				{
//				case 0:
//					mEnemyTeam->mTeamMembers.push_back(new DPhoenix::CharacterClass(*mBrusierMenu));
//					break;
//				case 1:
//					mEnemyTeam->mTeamMembers.push_back(new DPhoenix::CharacterClass(*mCrusierMenu));
//					break;
//				case 2:
//					mEnemyTeam->mTeamMembers.push_back(new DPhoenix::CharacterClass(*mFlagShipMenu));
//					break;
//				case 3:
//					mEnemyTeam->mTeamMembers.push_back(new DPhoenix::CharacterClass(*mCorvetteMenu));
//					break;
//				}
//
//				switch (mMenuState)
//				{
//				case CONFIRM_MENUSTATE: mMenuState = ENEMY_1_PICKED_MENUSTATE; break;
//				case ENEMY_1_PICKED_MENUSTATE: mMenuState = ENEMY_2_PICKED_MENUSTATE; break;
//				case ENEMY_2_PICKED_MENUSTATE: mMenuState = ENEMY_3_PICKED_MENUSTATE; break;
//				case ENEMY_3_PICKED_MENUSTATE: mMenuState = ENEMY_4_PICKED_MENUSTATE; break;
//
//				}
//				mWaitTimer.Reset();
//			}
//
//			break;
//		case ENEMY_4_PICKED_MENUSTATE:
//			if (mWaitTimer.TotalTime() > 2.0f)
//			{
//				mGameState = GAME_PLAY_STATE;
//
//				mPlayerTeam->mTeamMembers[0]->mModelInstance->mPosition = mPlayerSpawnVec[0];
//				mPlayerTeam->mTeamMembers[1]->mModelInstance->mPosition = mPlayerSpawnVec[1];
//				mPlayerTeam->mTeamMembers[2]->mModelInstance->mPosition = mPlayerSpawnVec[2];
//				mPlayerTeam->mTeamMembers[3]->mModelInstance->mPosition = mPlayerSpawnVec[3];
//
//				mEnemyTeam->mTeamMembers[0]->mModelInstance->mPosition = mEnemySpawnVec[0];
//				mEnemyTeam->mTeamMembers[1]->mModelInstance->mPosition = mEnemySpawnVec[1];
//				mEnemyTeam->mTeamMembers[2]->mModelInstance->mPosition = mEnemySpawnVec[2];
//				mEnemyTeam->mTeamMembers[3]->mModelInstance->mPosition = mEnemySpawnVec[3];
//
//
//				for (int i = 0; i < mPlayerTeam->mTeamMembers.size(); i++)
//				{
//					mPlayerTeam->mTeamMembers[i]->mModelInstance->mRotYOffset = 0.0f;
//				}
//
//				for (int i = 0; i < mEnemyTeam->mTeamMembers.size(); i++)
//				{
//					mEnemyTeam->mTeamMembers[i]->mModelInstance->mRotYOffset = 0.0f;
//				}
//
//				mPlayerTeam->CalculateTPPool(); mPlayerTeam->ResetTeamTurn();
//				mEnemyTeam->CalculateTPPool(); mEnemyTeam->ResetTeamTurn();
//
//				mEnemyTeam->mTeamType = DPhoenix::ENEMY_TEAM;
//
//				//add plaayers / enimes to entities
//				for (int i = 0; i < mPlayerTeam->mTeamMembers.size(); i++)
//				{
//					mPlayerTeam->mTeamMembers[i]->mModelInstance->mEntityType = DPhoenix::ENTITY_PLAYER_MESH;
//					mPlayerTeam->mTeamMembers[i]->mModelInstance->mCollidable = true;
//					AddEntity(mPlayerTeam->mTeamMembers[i]->mModelInstance);
//				}
//
//				for (int i = 0; i < mEnemyTeam->mTeamMembers.size(); i++)
//				{
//					mEnemyTeam->mTeamMembers[i]->mModelInstance->mEntityType = DPhoenix::ENTITY_ENEMY_MESH;
//					mEnemyTeam->mTeamMembers[i]->mModelInstance->mCollidable = true;
//					AddEntity(mEnemyTeam->mTeamMembers[i]->mModelInstance);
//				}
//
//				//need intial line---------------
//				mCameraLine = new::DPhoenix::Line();
//				AddEntity(mCameraLine);
//
//				//need initial line
//				mCameraLine = new::DPhoenix::Line();
//				AddEntity(mCameraLine);
//			}
//
//			break;
//		}
//		break;
//	case GAME_PLAY_STATE:
//		mDirLights[0]->Direction = XMFLOAT3(0.0f, -1.0f, 0.0f);
//
//		//unit circle calulations oft radius around player to pos
//		float zBase = sin(XMConvertToRadians(mCamToFocusAngle));
//		float xBase = cos(XMConvertToRadians(mCamToFocusAngle));
//
//#pragma region CheckTeam
//		//set the active team for easier shorthand
//		DPhoenix::Team* activeTeam;
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM)
//			activeTeam = mPlayerTeam;
//		else if (mCurrentTeam == DPhoenix::ENEMY_TEAM)
//			activeTeam = mEnemyTeam;
//
//		if (activeTeam->mTurnsLeft == 0)
//		{
//			//checks to switch etams if out of turns
//			if (activeTeam->mTeamType == DPhoenix::PLAYER_TEAM)
//			{
//				activeTeam = mEnemyTeam;
//				mCurrentTeam = DPhoenix::ENEMY_TEAM;
//
//			}
//			else
//			{
//				activeTeam = mPlayerTeam;
//				mCurrentTeam = DPhoenix::PLAYER_TEAM;
//			}
//			activeTeam->ResetTeamTurn();
//		}
//
//		//pointer to current team member for easier sorthand logic
//		DPhoenix::CharacterClass* currentCharacter =
//			activeTeam->mTeamMembers[activeTeam->mCurrentMember];
//#pragma endregion CheckTeam
//#pragma region CameraPos
//
//		//wher should the camera focus
//		XMFLOAT3 currentFocus;
//
//		//what our move stat for current char
//		//if picking need higher view if not show behind char
//		if (currentCharacter->mMoveState == DPhoenix::CH_PICKRT_MOVESTATE ||
//			currentCharacter->mMoveState == DPhoenix::CH_PICKAC_MOVESTATE)
//		{
//			mCameraBehindFlag = false;
//			currentFocus = currentCharacter->mModelInstance->mPosition;
//
//			if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//				currentCharacter->mMoveState == DPhoenix::CH_PICKRT_MOVESTATE)
//			{
//				if (mHappyPath.size() < 1)
//				{
//					ResetPath();
//				}
//
//				currentFocus = mHappyPath.back()->mPosition;
//			}
//		}
//		else
//		{
//			mCameraBehindFlag = true;
//			currentFocus = currentCharacter->mModelInstance->mPosition;
//			currentFocus.y = 20.0f;
//		}
//
//		if (currentCharacter->mMoveState == DPhoenix::CH_DOAC_MOVESTATE && mActionStage == AC_POSTFIRE)
//		{
//			mCameraBehindFlag = false;
//		}
//
//		//set the goal target for te camera
//		mCamera->mGoalTarget = currentFocus;
//
//		//nased pm flag set, adjust goal pos
//		if (!mCameraBehindFlag)
//		{
//			mCamera->mGoalPosition.x = currentFocus.x - (xBase * mCameraDistanceOffset);
//			mCamera->mGoalPosition.y = currentFocus.y + mCameraDistanceOffset;
//			mCamera->mGoalPosition.z = currentFocus.z - (zBase * mCameraDistanceOffset);
//		}
//		else
//		{
//			if (currentCharacter->mMoveState == DPhoenix::CH_DOAC_MOVESTATE &&
//				mActionStage != AC_POSTFIRE)
//			{
//				//light vec
//				//get up vec
//				XMFLOAT3 vecUp(0.0f, 1.0f, 0.0f);
//				//calulate right vec based on cross product of up and forward
//				XMVECTOR vecRight = XMVector3Cross(XMLoadFloat3(&vecUp),
//					XMLoadFloat3(&currentCharacter->mModelInstance->mForwardVector));
//				//now store the right vec as float
//				XMFLOAT3 rightDir; XMStoreFloat3(&rightDir, vecRight);
//				//the x and z can be used to pos to the right of the character fpr an over shoulder effect
//				mCamera->mGoalPosition.x = currentFocus.x - currentCharacter->mModelInstance->mForwardVector.x * 20.0f + (rightDir.x * 10.0f);
//				mCamera->mGoalPosition.y = currentFocus.y + 5.0f;
//				mCamera->mGoalPosition.z = currentFocus.z - currentCharacter->mModelInstance->mForwardVector.z * 20.0f + (rightDir.z * 10.0f);
//			}
//			else
//			{
//				mCamera->mGoalPosition.x = currentFocus.x - currentCharacter->mModelInstance->mForwardVector.x * 20.0f;
//				mCamera->mGoalPosition.y = 20.0f;
//				mCamera->mGoalPosition.z = currentFocus.z - currentCharacter->mModelInstance->mForwardVector.z * 20.0f;
//				
//			}
//		}
//#pragma endregion CameraPos
//#pragma region Selections
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM
//			&& currentCharacter->mTurnState == DPhoenix::CH_ACTIVE_TURNSTATE
//			&& currentCharacter->mMoveState == DPhoenix::CH_PICKRT_MOVESTATE)
//		{
//			//check collision
//			for (int i = 0; i < mSelectionBoxes.size(); i++)
//			{
//				if (mSelectionBoxes[i]->mCollided)
//				{
//					mSelectionBoxes[i]->mOpacity = 0.8f;
//				}
//				else
//				{
//					mSelectionBoxes[i]->mOpacity = 0.7f;
//				}
//			}
//		}
//		//check if we are in the pick action state and have selected ana ctions
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM
//			&& currentCharacter->mTurnState == DPhoenix::CH_ACTIVE_TURNSTATE
//			&& currentCharacter->mMoveState == DPhoenix::CH_PICKAC_MOVESTATE
//			&& currentCharacter->mSelectedAction != DPhoenix::NO_ACTION)
//		{
//			//time to construct the paths for display for targeting
//			if (mPlayerTeam->mNewActionselectFlag)
//			{
//				ResetTargeting();
//				mPlayerTeam->mNewActionselectFlag = false;
//			}
//
//			//get rid of old happy path
//			mHappyPath.clear();
//
//			for (int i = 0; i < mSelectionBoxes.size(); i++)
//			{
//				mSelectionBoxes[i]->mAlive = false;
//			}
//
//			mSelectionBoxes.clear();
//
//			//check collision
//			for (int i = 0; i < mTargetBoxes.size(); i++)
//			{
//				if (mTargetBoxes[i]->mCollided)
//				{
//					mTargetBoxes[i]->mOpacity = 0.8f;
//				}
//				else
//				{
//					mTargetBoxes[i]->mOpacity = 0.7f;
//				}
//			}
//		}
//#pragma endregion Selections
//#pragma region ActionsUpdating
//		//get current and oppsing team for action updationg
//		DPhoenix::Team* currentTeam; DPhoenix::Team* opposingTeam;
//
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM)
//		{
//			currentTeam = mPlayerTeam; opposingTeam = mEnemyTeam;
//		}
//		else
//		{
//			currentTeam = mEnemyTeam; opposingTeam = mPlayerTeam;
//		}
//#pragma endregion ActionsUpdating
//#pragma region ActionInitialStage
//		if (currentCharacter->mTurnState == DPhoenix::CH_ACTIVE_TURNSTATE
//			&& currentCharacter->mMoveState == DPhoenix::CH_DOAC_MOVESTATE
//			&& mActionStage == AC_INITIAL)
//		{
//			//start turning around and mpvong the camera
//			//could interpolate moving now for speed so truns instantly
//			XMVECTOR targetPosVec = XMLoadFloat3(&mTargets.back()->mPosition);
//			XMVECTOR playerPosVec = XMLoadFloat3(&currentCharacter->mModelInstance->mPosition);
//			//subtract the pos and normalise to get the directiob of the target
//			XMVECTOR pointAtTargetVec = XMVectorSubtract(targetPosVec, playerPosVec);
//			pointAtTargetVec = XMVector3Normalize(pointAtTargetVec);
//			//now conver to float3 to use
//			XMFLOAT3 newLookDir;
//			XMStoreFloat3(&newLookDir, pointAtTargetVec);
//				//0 the y axis so no movement on y
//			newLookDir.y = 0.0f;
//			//set new forward vec for current character
//			currentCharacter->mModelInstance->mForwardVector = newLookDir;
//			//now set to perpare action stage
//			mActionStage = AC_PREPARE;
//
//		}
//
//#pragma endregion ActionInitialStage
//#pragma region ActionPerpareStage
//		if (currentCharacter->mTurnState == DPhoenix::CH_ACTIVE_TURNSTATE
//			&&currentCharacter->mMoveState == DPhoenix::CH_DOAC_MOVESTATE
//			&& mActionStage == AC_PREPARE)
//		{
//				//if the camera is at the goal position
//			if (mCamera->mPosition.x == mCamera->mGoalPosition.x &&
//				mCamera->mPosition.y == mCamera->mGoalPosition.y &&
//				mCamera->mPosition.z == mCamera->mGoalPosition.z)
//			{
//				//ready to fire
//				mActionStage = AC_FIRE;
//
//				//check the current selected action to then do the right moves
//				switch (currentCharacter->mSelectedAction)
//				{
//				case DPhoenix::HIT_ACTION:
//					//take away the tp deom the team pool and set first melle cars
//					mMeleeStartPos = currentCharacter->mModelInstance->mPosition;
//					mMeleeStage = GOTO_TARGET_MEL;
//					currentTeam->mTPPool -= 1;
//					break;
//
//				}
//			}
//				
//
//		}
//#pragma endregion ActionPerpareStage
//#pragma region ActionFireStage
//		if (currentCharacter->mTurnState == DPhoenix::CH_ACTIVE_TURNSTATE
//			&& currentCharacter->mMoveState == DPhoenix::CH_DOAC_MOVESTATE
//			&& mActionStage == AC_FIRE)
//		{
//			//this falg is for whenth eaction is omplete whatever it is
//			bool weaponDoneFlag = false;
//
//			//this is the block for the melee actions
//			if (currentCharacter->mSelectedAction == DPhoenix::HIT_ACTION)
//			{
//				//we havent collided yet so keep flag for when we do
//				bool meleeCollision = false;
//
//				switch (mMeleeStage)
//				{
//				case GOTO_TARGET_MEL:
//					//initial loops through
//					for (int i = 0; i < opposingTeam->mTeamMembers.size(); i++)
//					{
//						for (int j = 0; j < opposingTeam->mTeamMembers[i]->mModelInstance->mAABBCollidedEntities.size(); i++)
//						{
//							//loop through the collided entities of all opposing team mebers
//							//to see f they have collided with current character
//							if (opposingTeam->mTeamMembers[i]->mModelInstance->mAABBCollidedEntities[j]->mId ==
//								currentCharacter->mModelInstance->mId)
//							{
//								//do battle cal, get the position to display the damage and the value
//								mMeleeDmg = currentCharacter->MeleeAttack(opposingTeam->mTeamMembers[i]);
//								mMeleeDmgPos = opposingTeam->mTeamMembers[i]->mModelInstance->mPosition;
//								//set flags and ensure the oppoent takes the damage
//								mMeleeHit = true;
//								opposingTeam->mTeamMembers[i]->TakeDamage(mMeleeDmg);
//								meleeCollision = true;
//							}
//
//						}
//					}
//					if (meleeCollision)
//					{
//						//change melle stage set the current character to the melle action
//						mMeleeStage = HIT_TARGET_MEL;
//						currentCharacter->mModelInstance->mInstanceAnimator->SetAnimation(DPhoenix::MELEE_ANIMATION);
//						currentCharacter->mModelInstance->SetTimePos(0);
//						currentCharacter->mModelInstance->SetLoopClips(false);
//						mActionTimer.Reset();
//					}
//					else
//					{
//						//otherwise we kepp mocing towards the oppent hence set walign animaitn
//						if (currentCharacter->mModelInstance->mInstanceAnimator->GetAnimationIndex() != DPhoenix::WALK_ANIMATION)
//						{
//							currentCharacter->mModelInstance->mInstanceAnimator->SetAnimation(DPhoenix::WALK_ANIMATION);
//							currentCharacter->mModelInstance->SetTimePos(0);
//							currentCharacter->mModelInstance->SetTimePos(true);
//						}
//						// and keep movimng along forward vec
//						currentCharacter->mModelInstance->mPosition.x +=
//							currentCharacter->mModelInstance->mForwardVector.x * 20.0f * dt;
//						currentCharacter->mModelInstance->mPosition.z +=
//							currentCharacter->mModelInstance->mForwardVector.z * 20.0f * dt;
//					}
//					break;
//				case HIT_TARGET_MEL:
//					//increase the y height of the damage position
//					mMeleeDmgPos.y += 1.0f * dt;
//
//					//tick the timer
//					mActionTimer.Tick();
//
//					//if enough time has passed to process the hit
//					if (mActionTimer.TotalTime() > 2.5f)
//					{
//						//time to return - walk back and reset timer
//						mMeleeStage = RETURN_MEL;
//						currentCharacter->mModelInstance->mInstanceAnimator->SetAnimation(DPhoenix::WALK_ANIMATION);
//						currentCharacter->mModelInstance->SetTimePos(0);
//						currentCharacter->mModelInstance->SetLoopClips(true);
//						mActionTimer.Reset();
//						//face back to our pos
//						currentCharacter->mModelInstance->mRotYOffset = 180.0f;
//					}
//
//					break;
//
//				case RETURN_MEL:
//					//keep increase damage height
//					mMeleeDmgPos.y += 1.0f * dt;
//
//					//the goal is back to the pos we started the melle process from
//					//so get the distance between our current position and that
//					XMVECTOR goalPosVec = XMLoadFloat3(&mMeleeStartPos);
//					XMVECTOR modelPosVec = XMLoadFloat3(&currentCharacter->mModelInstance->mPosition);
//					XMVECTOR pointAtGoalVec = XMVectorSubtract(goalPosVec, modelPosVec);
//					XMVECTOR goalDistanceVec = pointAtGoalVec;
//					XMFLOAT3 goalDistance;
//					XMStoreFloat3(&goalDistance, XMVector3Length(goalDistanceVec));
//
//					//if we are within bounds set status to end the melle attack and set idle
//					if (goalDistance.x < 0.5f)
//					{
//						weaponDoneFlag = true;
//						currentCharacter->mModelInstance->mInstanceAnimator->SetAnimation(DPhoenix::IDLE_ANIMATION);
//						currentCharacter->mModelInstance->SetTimePos(0);
//						currentCharacter->mModelInstance->SetLoopClips(true);
//						//face back to enemy
//						currentCharacter->mModelInstance->mRotYOffset = 0.0f;
//
//					}
//					else
//					{
//						//other wse keep mocing back to where started
//						currentCharacter->mModelInstance->mPosition.x -=
//							currentCharacter->mModelInstance->mForwardVector.x * 20.0f * dt;
//						currentCharacter->mModelInstance->mPosition.z -=
//							currentCharacter->mModelInstance->mForwardVector.z * 20.0f * dt;
//					}
//					break;
//
//				}
//
//			}
//			//if done come out of firing stage
//			if (weaponDoneFlag)
//			{
//				mActionStage = AC_POSTFIRE;
//				mActionTimer.Reset();
//			}
//			
//		}
//
//#pragma endregion ActionFireStage
//#pragma region ActionPostFireStage
//		if (currentCharacter->mTurnState == DPhoenix::CH_ACTIVE_TURNSTATE
//			&&  currentCharacter->mMoveState == DPhoenix::CH_DOAC_MOVESTATE
//			&& mActionStage == AC_POSTFIRE)
//		{
//			//let the damge cotiune rising a little longer
//			mActionTimer.Tick();
//			mMeleeDmgPos.y += 1.0f * dt;
//
//			//after whuch point we are done and it is time to end turn
//			if (mActionTimer.TotalTime() > 0.5f)
//			{
//				//set flag and updatet tp pool
//				mActionStage = AC_DONE;
//				currentTeam->mTPTurnSnapshot = currentTeam->mTPPool;
//				currentTeam->EndCurrentTurn();
//
//				//reset targets vectors
//				for (int i = 0; i < mTargetBoxes.size(); i++)
//				{
//					mTargetBoxes[i]->mAlive = false;
//				}
//
//				mTargetBoxes.clear();
//				mTargets.clear();
//
//				//unset flag
//				mMeleeHit = false;
//			}
//		}
//#pragma endregion ActionPostFireStage
//
//		mPlayerTeam->Update(dt, mMap);
//		mEnemyTeam->Update(dt, mMap);
//
//		mCamera->Update(dt);
//#pragma region CameraLine
//		//Move the mouse cursour ciirdubates ibti - 1 to +1 range
//		//1600 x 900 resloustion of window
//
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM
//			&& currentCharacter->mTurnState == DPhoenix::CH_ACTIVE_TURNSTATE
//			&& mMouseX > 0 && mMouseX < 1600 && mMouseY > 0 && mMouseY < 900)
//		{
//			float mouseXbyorigin = mMouseX;
//			float mouseYbyorigin = mMouseY;
//			//convert the ppoint to within the viewpoint bounds
//			float pointX = ((2.0f * (float)mouseXbyorigin) / (float)1600) - 1.0f;
//			float pointY = (((2.0f * (float)mouseYbyorigin) / (float)900) - 1.0f) * -1.0f;
//
//			//adjust the points using the prkjec matrix to account for the aspevt ratio of the viewpoint
//			pointX = pointX / mCamera->GetProj()._11;
//			pointY = pointY / mCamera->GetProj()._22;
//
//			//get the inverse of the view matrix
//			XMVECTOR det = XMMatrixDeterminant(mCamera->GetView());
//			XMMATRIX InverseView = XMMatrixInverse(&det, mCamera->GetView());
//
//			XMFLOAT3 lineDir;
//
//			//calulate the direction of the picking ray in view space
//			lineDir.x = (pointX * InverseView._11) + (pointY * InverseView._21) + InverseView._31;
//			lineDir.y = (pointX * InverseView._12) + (pointY * InverseView._22) + InverseView._32;
//			lineDir.z = (pointX * InverseView._13) + (pointY * InverseView._23) + InverseView._33;
//
//			//normalise
//			XMVECTOR linePointVec = XMLoadFloat3(&lineDir);
//			linePointVec = XMVector3Normalize(linePointVec);
//			XMStoreFloat3(&lineDir, linePointVec);
//
//			//update line propties
//			mCameraLine->Init(mCamera->mPosition, lineDir, 1000.0f);
//			mCameraLine->mEntityType = DPhoenix::ENTITY_CAMERA_LINE;
//			mCameraLine->mCollidable = true;
//			//AddEntity(mCameraLine);
//		}
//#pragma endregion CameraLine
//		break;
//	}
//	//timer updates
//	mMouseClickTimer.Tick();
//	mKeyPressTimer.Tick();
//	mWaitTimer.Tick();
//
//
//
//}
//
//void LITSActions::BuildGeometryBuffers()
//{
//#pragma region GeometryCreation
//
//
//#pragma endregion GeometryCreation
//
//#pragma region BlendStates
//	//CREATE BLEND STATE ==========================================
//	//this is so transparency can be layered for our sprites
//
//	//create blend description struct and set properties
//	D3D11_BLEND_DESC blendDesc;
//	ZeroMemory(&blendDesc, sizeof(blendDesc));
//	blendDesc.RenderTarget[0].BlendEnable = TRUE;						//enable alpha blend
//	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;				//blend operation (add colour)
//	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;			//source blend - alpha 
//	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;	//dest blend - inverse source alpha
//	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;		//blend operation for alpha
//	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;			//blend based fully on source
//	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;		//not blended based on destination
//																		//this can affect the blend / transparency with different hex values
//	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
//
//	//blend state (allow transparency)
//	ID3D11BlendState* alphaBlendState_;
//	//create the blend state with the properties set
//	//OM stands for output merger - final stage of shader pipeline
//	md3dDevice->CreateBlendState(&blendDesc, &alphaBlendState_);
//	md3dImmediateContext->OMSetBlendState(alphaBlendState_, 0, 0xffffffff);
//#pragma endregion BlendStates
//
//#pragma region DepthStencilStates
//
//	//DEPTH STENCIL STATES ==================================================
//	//disabled depth stenciling will enable for 2D sprites to be layered on top of each other
//	//we will use the standard depth stencilling for 3D rendering
//
//	// Initialize the description of the stencil state.
//	ZeroMemory(&mDepthStencilDesc, sizeof(mDepthStencilDesc));
//
//	// Set up the description of the stencil state.
//	//enable depth checking
//	mDepthStencilDesc.DepthEnable = true;
//	//use full buffer for depth checks
//	mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
//	//compare depth data
//	//If the source data is less than the destination data, the comparison passes.
//	mDepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
//
//
//	//enable stencil testing
//	mDepthStencilDesc.StencilEnable = true;
//	//use all buffer for reading
//	mDepthStencilDesc.StencilReadMask = 0xFF;
//	//use all buffer for writing
//	mDepthStencilDesc.StencilWriteMask = 0xFF;
//
//	// Stencil operations if pixel is front-facing.
//	//keep if stencil test fails
//	mDepthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	//increment if stencil and depth fails
//	mDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
//	//keep if stencil test passes
//	mDepthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	//always compare data gainst existing
//	mDepthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//
//	// Stencil operations if pixel is back-facing.
//	//keep if stencil test fails
//	mDepthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	//decrement if stencil and depth fails
//	mDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
//	//keep if stencil test passes
//	mDepthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	//always compare data gainst existing
//	mDepthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//
//	// Create the depth stencil state.
//	HRESULT result = md3dDevice->CreateDepthStencilState(&mDepthStencilDesc, &mDepthStencilState);
//	if (FAILED(result))
//	{
//		//like oh no scoob
//		//return false;
//	}
//
//	// Set the depth stencil state.
//	md3dImmediateContext->OMSetDepthStencilState(mDepthStencilState, 1);
//
//	// Clear the second depth stencil state before setting the parameters.
//	ZeroMemory(&mDepthDisabledStencilDesc, sizeof(mDepthDisabledStencilDesc));
//
//	// Now create a second depth stencil state which turns off the Z buffer for 2D rendering.  The only difference is 
//	// that DepthEnable is set to false, all other parameters are the same as the other depth stencil state.
//	mDepthDisabledStencilDesc.DepthEnable = false;
//	mDepthDisabledStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
//	mDepthDisabledStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
//	mDepthDisabledStencilDesc.StencilEnable = true;
//	mDepthDisabledStencilDesc.StencilReadMask = 0xFF;
//	mDepthDisabledStencilDesc.StencilWriteMask = 0xFF;
//	mDepthDisabledStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	mDepthDisabledStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
//	mDepthDisabledStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	mDepthDisabledStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//	mDepthDisabledStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
//	mDepthDisabledStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
//	mDepthDisabledStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
//	mDepthDisabledStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
//
//	// Create the state using the device.
//	result = md3dDevice->CreateDepthStencilState(&mDepthDisabledStencilDesc, &mDepthDisabledStencilState);
//	if (FAILED(result))
//	{
//		//return false;
//	}
//
//#pragma endregion DepthStencilStates
//
//}
//
//void LITSActions::DrawScene()
//{
//
//#pragma region InitialRenderingSetup
//	//do we have the context and swapchain?
//	assert(md3dImmediateContext);
//	assert(mSwapChain);
//
//	//set the effect techniques we wish to use
//	ID3DX11EffectTechnique* activeSpriteTech = DPhoenix::Effects::SpriteFX->SpriteTech;
//	ID3DX11EffectTechnique* activeColorTech = DPhoenix::Effects::ColorFX->ColorTech;
//	ID3DX11EffectTechnique* activeBasicTexTech = DPhoenix::Effects::BasicTexFX->BasicTexTech;
//	ID3DX11EffectTechnique* activeLitTexTech = DPhoenix::Effects::LitTexFX->LitTexTech;
//	ID3DX11EffectTechnique* activeLitTexNormalTech = DPhoenix::Effects::LitTexNormalFX->LitTexNormalTech;
//	ID3DX11EffectTechnique* activeSkyTech = DPhoenix::Effects::SkyFX->SkyTech;
//	ID3DX11EffectTechnique* activeLitBillboardTech = DPhoenix::Effects::LitBillboardFX->LitBillboardTech;
//	ID3DX11EffectTechnique* activeLitTexSkinnedTech = DPhoenix::Effects::LitTexFX->LitTexSkinnedTech;
//	ID3DX11EffectTechnique* activeLitTexNormSkinnedTech = DPhoenix::Effects::LitTexNormalFX->LitTexNormalSkinnedTech;
//
//	//clear the screen with the defined colour
//	float clearColor[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
//	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, clearColor);
//	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::SpritePosTex);
//	//set primitive topology as triangle list (adjacent trinagles to render for GPU efficiency)
//	md3dImmediateContext->IASetPrimitiveTopology(
//		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//
//	//clear all Direct2D before rendering any text
//	//(this overwrites the 3D clear color)
//	m2D1RT->BeginDraw();
//
//	m2D1RT->Clear(D2D1::ColorF(0x00000000));
//
//	m2D1RT->EndDraw();
//
//#pragma endregion InitialRenderingSetup
//
//#pragma region RenderSpritesBG
//
//	//to render sprites we need to disable depth testing (so it layers on top of each other)
//	//like a collage
//	md3dImmediateContext->OMSetDepthStencilState(mDepthDisabledStencilState, 1);
//
//	switch (mGameState)
//	{
//	case GAME_TITLE_STATE:
//		RenderSprite(mTitleScreen, activeSpriteTech, true);
//		break;
//	case GAME_MENU_STATE:
//		RenderSprite(mTeamMenuScreen, activeSpriteTech, true);
//		break;
//	}
//
//	//turn depth stencil back on for 3D rendering
//	md3dImmediateContext->OMSetDepthStencilState(mDepthStencilState, 1);
//
//#pragma endregion RenderSpritesBG
//
//#pragma region RenderColorPrimitives
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosColor);
//
//	//here we will render the box using our new method
//
//#pragma endregion RenderColorPrimitives
//
//#pragma region RenderBasicTexturedPrimitives
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosTex);
//
//#pragma endregion RenderBasicTexturedPrimitives
//
//#pragma region SetUpLights
//	//zero array memory
//	memset(mDirLightsArray, 0, sizeof(mDirLightsArray));
//
//	int i = 0;
//	//loop through the vector and dereference pointer
//	//to populate array for shader
//	for each(DirectionalLight* dirLight in mDirLights)
//	{
//		mDirLightsArray[i] = *dirLight;
//		i++;
//	}
//
//	//zero array memory
//	memset(mPointLightsArray, 0, sizeof(mPointLightsArray));
//
//	i = 0;
//	//loop through the vector and dereference pointer
//	//to populate array for shader
//	for each(PointLight* pointLight in mPointLights)
//	{
//		mPointLightsArray[i] = *pointLight;
//		mPointLightsArray[i].Range = mRange;
//		i++;
//	}
//
//#pragma endregion SetUplights
//
//#pragma region RenderLitTexturedPrimitives
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosNormalTexTan);
//
//	switch (mGameState)
//	{
//	case GAME_PLAY_STATE:
//		//loop through and redner map blocks
//		for (int row = 0; row < mMap->mLength; row++)
//		{
//			for (int col = 0; col < mMap->mWidth; col++)
//			{
//				if (mMap->mTiles[col][row]->mMapBlockType == DPhoenix::FLOOR_MAPBLOCK ||
//					mMap->mTiles[col][row]->mMapBlockType == DPhoenix::WALL_MAPBLOCK ||
//					mMap->mTiles[col][row]->mMapBlockType == DPhoenix::COVER_MAPBLOCK ||
//					mMap->mTiles[col][row]->mMapBlockType == DPhoenix::BEACON_MAPBLOCK)
//				{
//					RenderLitTexNormPrimitive(mMap->mTiles[col][row]->mMeshInstance, activeLitTexNormalTech);
//				}
//			}
//		}
//#pragma region Selections
//		//get current team
//		DPhoenix::Team* activeTeam;
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM)
//			activeTeam = mPlayerTeam;
//		if (mCurrentTeam == DPhoenix::ENEMY_TEAM)
//			activeTeam = mEnemyTeam;
//
//		//get current members moves state if pick or move roy, render slection boxes / happ path
//		if ((activeTeam->mTeamMembers[activeTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKRT_MOVESTATE ||
//			activeTeam->mTeamMembers[activeTeam->mCurrentMember]->mMoveState == DPhoenix::CH_MOVERT_MOVESTATE))
//		{
//			for (int i = 0; i < mHappyPath.size(); i++)
//			{
//				RenderLitTexNormPrimitive(mHappyPath[i], activeLitTexNormalTech);
//			}
//
//			for (int i = 0; i < mSelectionBoxes.size(); i++)
//			{
//				RenderLitTexNormPrimitive(mSelectionBoxes[i], activeLitTexNormalTech);
//			}
//		}
//#pragma endregion Selections
//#pragma region Targets
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//			mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKAC_MOVESTATE)
//		{
//			for (int i = 0; i < mTargets.size(); i++)
//			{
//				RenderLitTexNormPrimitive(mTargets[i], activeLitTexNormalTech);
//			}
//
//			for (int i = 0; i < mTargetBoxes.size(); i++)
//			{
//				RenderLitTexNormPrimitive(mTargetBoxes[i], activeLitTexNormalTech);
//			}
//		}
//#pragma endregion Targets
//	}
//
//
//
//#pragma endregion RenderLitTexturedPrimitives
//
//#pragma region RenderLitTexturedNormalPrimitives
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosNormalTexTan);
//
//
//#pragma endregion RenderLitTexturedNormalPrimitives
//
//#pragma region RenderSkinnedMeshes
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosNormalTexTanSkinned);
//
//
//#pragma endregion RenderSkinnedMeshes
//
//#pragma region RenderSkinnedNormalMeshes
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosNormalTexTanSkinned);
//
//	switch (mGameState)
//	{
//	case GAME_MENU_STATE:
//		RenderSkinnedModelNormal(mBrusierMenu->mModelInstance, activeLitTexNormSkinnedTech);
//		RenderSkinnedModelNormal(mCrusierMenu->mModelInstance, activeLitTexNormSkinnedTech);
//		RenderSkinnedModelNormal(mFlagShipMenu->mModelInstance, activeLitTexNormSkinnedTech);
//		RenderSkinnedModelNormal(mCorvetteMenu->mModelInstance, activeLitTexNormSkinnedTech);
//		break;
//	case GAME_PLAY_STATE:
//		//loop thorugh each team to redner
//		for (int i = 0; i < mPlayerTeam->mTeamMembers.size(); i++)
//		{
//			RenderSkinnedModelNormal(mPlayerTeam->mTeamMembers[i]->mModelInstance, activeLitTexNormSkinnedTech);
//		}
//
//		for (int i = 0; i < mEnemyTeam->mTeamMembers.size(); i++)
//		{
//			RenderSkinnedModelNormal(mEnemyTeam->mTeamMembers[i]->mModelInstance, activeLitTexNormSkinnedTech);
//		}
//	}
//
//
//#pragma endregion RenderSkinnedNormalMeshes
//
//#pragma region RenderSkybox
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::Pos);
//
//	switch (mGameState)
//	{
//	case GAME_PLAY_STATE:
//		RenderSkybox(mSkybox, md3dImmediateContext);
//		break;
//	}
//
//
//#pragma endregion RenderSkybox
//
//#pragma region RenderBillboards
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosNormalTexTan);
//
//
//#pragma endregion RenderBillboards
//
//#pragma region RenderBasicMeshes
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosNormalTexTan);
//
//
//#pragma endregion RenderBasicMeshes
//
//#pragma region RenderBasicNormalMeshes
//
//	//set up the vertex input layout
//	//(would need to change for different types of rendering)
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosNormalTexTan);
//
//
//
//#pragma endregion RenderBasicNormalMeshes
//
//
//#pragma region RenderSpritesFG
//
//	//to render sprites we need to disable depth testing (so it layers on top of each other)
//	//like a collage
//	md3dImmediateContext->OMSetDepthStencilState(mDepthDisabledStencilState, 1);
//
//	float rowAdjust = 0.0f;
//	switch (mGameState)
//	{
//	case GAME_MENU_STATE:
//		RenderSprite(mSelectedClassMenu, activeSpriteTech, true);
//		break;
//	case GAME_PLAY_STATE:
//
//#pragma region UIAreas
//		RenderSprite(mActionsUISprite, activeSpriteTech, true);
//		RenderSprite(mBeaconsUISprite, activeSpriteTech, true);
//		RenderSprite(mEnemyUISprite, activeSpriteTech, true);
//		RenderSprite(mStatusUISprite, activeSpriteTech, true);
//		RenderSprite(mPlayerTeamUISprite, activeSpriteTech, true);
//
//#pragma endregion UIAreas
//#pragma region Avatars
//
//		//loop thorugh each team meber adjusting the row each time
//		//to pos the relevent avatar
//		for (int i = 0, rowAdjust = 0.0f;
//			i < mPlayerTeam->mTeamMembers.size();
//			i++, rowAdjust += LITSConst::gamePlayerAvatarsYAdjust)
//		{
//			switch (mPlayerTeam->mTeamMembers[i]->mClass)
//			{
//			case DPhoenix::FLAG_SHIP_CLASS:
//				mFlagShipAvatar->mPosition.x =
//					LITSConst::gamePlayerAvatarsInitialX + LITSConst::gameAvatarWidth / 2;
//				mFlagShipAvatar->mPosition.y =
//					LITSConst::gamePlayerAvatarsInitialY + rowAdjust - LITSConst::gameAvatarHeight / 2;
//				RenderSprite(mFlagShipAvatar, activeSpriteTech, true);
//				break;
//			case DPhoenix::BRUSIER_SHIP_CLASS:
//				mBrusierAvatar->mPosition.x =
//					LITSConst::gamePlayerAvatarsInitialX + LITSConst::gameAvatarWidth / 2;
//				mBrusierAvatar->mPosition.y =
//					LITSConst::gamePlayerAvatarsInitialY + rowAdjust - LITSConst::gameAvatarHeight / 2;
//				RenderSprite(mBrusierAvatar, activeSpriteTech, true);
//				break;
//			case DPhoenix::CORVETTE_SHIP_CLASS:
//				mCorvetteAvatar->mPosition.x =
//					LITSConst::gamePlayerAvatarsInitialX + LITSConst::gameAvatarWidth / 2;
//				mCorvetteAvatar->mPosition.y =
//					LITSConst::gamePlayerAvatarsInitialY + rowAdjust - LITSConst::gameAvatarHeight / 2;
//				RenderSprite(mCorvetteAvatar, activeSpriteTech, true);
//				break;
//			case DPhoenix::CRUSIER_SHIP_CLASS:
//				mCrusierAvatar->mPosition.x =
//					LITSConst::gamePlayerAvatarsInitialX + LITSConst::gameAvatarWidth / 2;
//				mCrusierAvatar->mPosition.y =
//					LITSConst::gamePlayerAvatarsInitialY + rowAdjust - LITSConst::gameAvatarHeight / 2;
//				RenderSprite(mCrusierAvatar, activeSpriteTech, true);
//				break;
//			}
//
//		}
//
//		for (int i = 0, rowAdjust = 0.0f;
//			i < mEnemyTeam->mTeamMembers.size();
//			i++, rowAdjust += LITSConst::gameEnemyAvatarsYAdjust)
//		{
//			switch (mEnemyTeam->mTeamMembers[i]->mClass)
//			{
//			case DPhoenix::FLAG_SHIP_CLASS:
//				mFlagShipAvatar->mPosition.x =
//					LITSConst::gameEnemyAvatarsInitialX + LITSConst::gameAvatarWidth / 2;
//				mFlagShipAvatar->mPosition.y =
//					LITSConst::gameEnemyAvatarsInitialY + rowAdjust - LITSConst::gameAvatarHeight / 2;
//				RenderSprite(mFlagShipAvatar, activeSpriteTech, true);
//				break;
//			case DPhoenix::BRUSIER_SHIP_CLASS:
//				mBrusierAvatar->mPosition.x =
//					LITSConst::gameEnemyAvatarsInitialX + LITSConst::gameAvatarWidth / 2;
//				mBrusierAvatar->mPosition.y =
//					LITSConst::gameEnemyAvatarsInitialY + rowAdjust - LITSConst::gameAvatarHeight / 2;
//				RenderSprite(mBrusierAvatar, activeSpriteTech, true);
//				break;
//			case DPhoenix::CORVETTE_SHIP_CLASS:
//				mCorvetteAvatar->mPosition.x =
//					LITSConst::gameEnemyAvatarsInitialX + LITSConst::gameAvatarWidth / 2;
//				mCorvetteAvatar->mPosition.y =
//					LITSConst::gameEnemyAvatarsInitialY + rowAdjust - LITSConst::gameAvatarHeight / 2;
//				RenderSprite(mCorvetteAvatar, activeSpriteTech, true);
//				break;
//			case DPhoenix::CRUSIER_SHIP_CLASS:
//				mCrusierAvatar->mPosition.x =
//					LITSConst::gameEnemyAvatarsInitialX + LITSConst::gameAvatarWidth / 2;
//				mCrusierAvatar->mPosition.y =
//					LITSConst::gameEnemyAvatarsInitialY + rowAdjust - LITSConst::gameAvatarHeight / 2;
//				RenderSprite(mCrusierAvatar, activeSpriteTech, true);
//				break;
//			}
//
//		}
//
//
//#pragma endregion Avatars
//
//#pragma region TurnsMenu
//
//		//only display turns higlighting if player teams tunr
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM)
//		{
//			//loop through each member
//			for (int i = 0, rowAdjust = 0.0f;
//				i < mPlayerTeam->mTeamMembers.size();
//				i++, rowAdjust += LITSConst::gamePlayerYAdjust)
//			{
//				//3 checks - selcted taken hovered
//				if (mPlayerTeam->mTeamMembers[i]->mTurnState == DPhoenix::CH_ACTIVE_TURNSTATE)
//				{
//					mSelectedTurnUISprite->mPosition.x =
//						LITSConst::gamePlayerTurnInitialX + LITSConst::gameTurnsHoverWidth / 2;
//					mSelectedTurnUISprite->mPosition.y =
//						LITSConst::gamePlayerTurnInitialY + rowAdjust - LITSConst::gameTurnsHoverHeight / 2;
//					RenderSprite(mSelectedTurnUISprite, activeSpriteTech, true);
//
//
//				}
//				else if (mPlayerTeam->mTeamMembers[i]->mTurnState == DPhoenix::CH_COMP_TURNSTATE)
//
//				{
//					mTakenTurnUISprite->mPosition.x =
//						LITSConst::gamePlayerTurnInitialX + LITSConst::gameTurnsHoverWidth / 2;
//					mTakenTurnUISprite->mPosition.y =
//						LITSConst::gamePlayerTurnInitialY + rowAdjust - LITSConst::gameTurnsHoverHeight / 2;
//					RenderSprite(mTakenTurnUISprite, activeSpriteTech, true);
//				}
//				else
//				{
//					//the hover flags eed to be aligend to currebt member to falg if displayed
//					bool showHover = false;
//					switch (i)
//					{
//					case 0:
//						if (mP1Hover) showHover = true;
//						break;
//					case 1:
//						if (mP2Hover) showHover = true;
//						break;
//					case 2:
//						if (mP3Hover) showHover = true;
//						break;
//					case 3:
//						if (mP4Hover) showHover = true;
//						break;
//
//					}
//
//					if (showHover)
//					{
//						mHoverdTurnUISprite->mPosition.x =
//							LITSConst::gamePlayerTurnInitialX + LITSConst::gameTurnsHoverWidth / 2;
//						mHoverdTurnUISprite->mPosition.y =
//							LITSConst::gamePlayerTurnInitialY + rowAdjust - LITSConst::gameTurnsHoverHeight / 2;
//						RenderSprite(mHoverdTurnUISprite, activeSpriteTech, true);
//					}
//				}
//			}
//		}
//#pragma endregion TurnsMenu
//#pragma region ActionsMenu
//		//check we are in the right state for action selections to be displayed
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//			mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKAC_MOVESTATE)
//		{
//
//			//check the hover flag, if so render th ehover sprite in the correct positions
//			if (mA1Hover)
//			{
//				mHoverdActionUISprite->mPosition.x = LITSConst::actionSelect1Section.left + LITSConst::gameActionHoverWidth / 2;
//				mHoverdActionUISprite->mPosition.y = LITSConst::actionSelect1Section.top - LITSConst::gameActionHoverHeight / 2;
//				RenderSprite(mHoverdActionUISprite, activeSpriteTech, true);
//			}
//			if (mA2Hover)
//			{
//				mHoverdActionUISprite->mPosition.x = LITSConst::actionSelect2Section.left + LITSConst::gameActionHoverWidth / 2;
//				mHoverdActionUISprite->mPosition.y = LITSConst::actionSelect2Section.top - LITSConst::gameActionHoverHeight / 2;
//				RenderSprite(mHoverdActionUISprite, activeSpriteTech, true);
//			}
//			if (mA3Hover)
//			{
//				mHoverdActionUISprite->mPosition.x = LITSConst::actionSelect3Section.left + LITSConst::gameActionHoverWidth / 2;
//				mHoverdActionUISprite->mPosition.y = LITSConst::actionSelect3Section.top - LITSConst::gameActionHoverHeight / 2;
//				RenderSprite(mHoverdActionUISprite, activeSpriteTech, true);
//			}
//			if (mA4Hover)
//			{
//				mHoverdActionUISprite->mPosition.x = LITSConst::actionSelect4Section.left + LITSConst::gameActionHoverWidth / 2;
//				mHoverdActionUISprite->mPosition.y = LITSConst::actionSelect4Section.top - LITSConst::gameActionHoverHeight / 2;
//				RenderSprite(mHoverdActionUISprite, activeSpriteTech, true);
//			}
//			if (mA5Hover)
//			{
//				mHoverdActionUISprite->mPosition.x = LITSConst::actionSelect5Section.left + LITSConst::gameActionHoverWidth / 2;
//				mHoverdActionUISprite->mPosition.y = LITSConst::actionSelect5Section.top - LITSConst::gameActionHoverHeight / 2;
//				RenderSprite(mHoverdActionUISprite, activeSpriteTech, true);
//			}
//			if (mA6Hover)
//			{
//				mHoverdActionUISprite->mPosition.x = LITSConst::actionSelect6Section.left + LITSConst::gameActionHoverWidth / 2;
//				mHoverdActionUISprite->mPosition.y = LITSConst::actionSelect6Section.top - LITSConst::gameActionHoverHeight / 2;
//				RenderSprite(mHoverdActionUISprite, activeSpriteTech, true);
//			}
//			if (mA7Hover)
//			{
//				mHoverdActionUISprite->mPosition.x = LITSConst::actionSelect7Section.left + LITSConst::gameActionHoverWidth / 2;
//				mHoverdActionUISprite->mPosition.y = LITSConst::actionSelect7Section.top - LITSConst::gameActionHoverHeight / 2;
//				RenderSprite(mHoverdActionUISprite, activeSpriteTech, true);
//			}
//
//		}
//#pragma endregion ActionsMenu
//
//		break;
//	}
//
//
//	//turn depth stencil back on for 3D rendering
//	md3dImmediateContext->OMSetDepthStencilState(mDepthStencilState, 1);
//
//#pragma endregion RenderSpritesFG
//
//#pragma region RenderFonts
//
//	//string stream object for getting all text to display
//	std::ostringstream debugText;
//
//	debugText << "Debug text:" << std::endl;
//	debugText << "Mouse Pos: X: " << mMouseX << " Y: " << mMouseY << std::endl;
//	debugText << "DX11m Pos: X" << mMouseX - 800 << " Y: " << 450 - mMouseY << std::endl;
//
//	//calculate screen scaling
//	float scaleX = (float)mClientWidth / 1600;
//	float scaleY = (float)mClientHeight / 900;
//
//	//call draw font method sending all key info
//	mDebugFont->DrawFont(m2D1RT, debugText.str(), 10.0f, 500.0f,
//		1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 0.5f));
//	std::ostringstream leveltext;
//	std::ostringstream classesText;
//	std::ostringstream bsText;
//	std::ostringstream csText;
//	std::ostringstream fsText;
//	std::ostringstream cosText;
//	//for gameplay ui
//	std::ostringstream statsText;
//	//for actions
//	std::ostringstream statusText;
//	std::ostringstream actionsText;
//	std::ostringstream dmgText;
//
//
//	switch (mGameState)
//	{
//	case GAME_MENU_STATE:
//
//
//		leveltext << mSelectedLevel;
//
//		mUIFont90pt->DrawFont(m2D1RT, leveltext.str(), LITSConst::selectedLevelLeft,
//			LITSConst::selectedLevelTop, 1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//
//
//
//#pragma region SelectedClasses
//
//
//
//
//		for (int i = 0;
//			i < mPlayerTeam->mTeamMembers.size();
//			i++, rowAdjust += LITSConst::selectedCharacterClassesRowSpacing)
//
//		{
//			switch (mPlayerTeam->mTeamMembers[i]->mClass)
//			{
//			case DPhoenix::BRUSIER_SHIP_CLASS:
//				classesText << "BRUSIER SHIP" << std::endl;
//				break;
//			case DPhoenix::CRUSIER_SHIP_CLASS:
//				classesText << "CRUSIER SHIP" << std::endl;
//				break;
//			case DPhoenix::FLAG_SHIP_CLASS:
//				classesText << "FLAG SHIP" << std::endl;
//				break;
//			case DPhoenix::CORVETTE_SHIP_CLASS:
//				classesText << "CORVETTE SHIP" << std::endl;
//				break;
//
//			}
//
//			//call draw font method sending all key info
//			//thankfull fonts are from top left
//			mUIFont36pt->DrawFont(m2D1RT, classesText.str(), LITSConst::selectedCharacterClassesLeft,
//				LITSConst::selectedCharacterClassesTop + rowAdjust,
//				1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//
//			classesText.clear(); classesText.str("");
//		}
//
//		rowAdjust = 0.0f;
//
//		//and for the enimes
//		for (int i = 0; i < mEnemyTeam->mTeamMembers.size();
//			i++, rowAdjust += LITSConst::selectedEnemyClassesRowSpacing)
//
//		{
//			switch (mEnemyTeam->mTeamMembers[i]->mClass)
//			{
//			case DPhoenix::BRUSIER_SHIP_CLASS:
//				classesText << "BRUSIER SHIP" << std::endl;
//				break;
//			case DPhoenix::CRUSIER_SHIP_CLASS:
//				classesText << "CRUSIER SHIP" << std::endl;
//				break;
//			case DPhoenix::FLAG_SHIP_CLASS:
//				classesText << "FLAG SHIP" << std::endl;
//				break;
//			case DPhoenix::CORVETTE_SHIP_CLASS:
//				classesText << "CORVETTE SHIP" << std::endl;
//				break;
//
//			}
//
//			//call draw font method sending all key info
//			//thankfull fonts are from top left
//			mUIFont36pt->DrawFont(m2D1RT, classesText.str(), LITSConst::selectedEnemyClassesLeft,
//				LITSConst::selectedEnemyClassesTop + rowAdjust,
//				1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//
//			classesText.clear(); classesText.str("");
//		}
//#pragma endregion SelectedClasses
//
//#pragma region BrusierStats
//
//
//		bsText << mBrusierMenu->GetTP() << std::endl;
//		bsText << mBrusierMenu->GetHS() << std::endl;
//		bsText << mBrusierMenu->GetRangeAttack() << std::endl;
//		bsText << mBrusierMenu->GetMeleeAttack() << std::endl;
//		bsText << mBrusierMenu->GetAccuracy() << std::endl;
//		bsText << mBrusierMenu->GetEvasion() << std::endl;
//		bsText << mBrusierMenu->GetCrit() << std::endl;
//		bsText << mBrusierMenu->GetLuck() << std::endl;
//		bsText << mBrusierMenu->GetHullDefense() << std::endl;
//
//		//call draw font method sending all key info
//		//thankgu fonts are top left
//		mUIFont16pt->DrawFont(m2D1RT, bsText.str(), LITSConst::selectedBursierStatsLeft,
//			LITSConst::selectedBrusierTop,
//			1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//#pragma endregion BrusierStats
//
//#pragma region CrusierStats
//
//
//		csText << mCrusierMenu->GetTP() << std::endl;
//		csText << mCrusierMenu->GetHS() << std::endl;
//		csText << mCrusierMenu->GetRangeAttack() << std::endl;
//		csText << mCrusierMenu->GetMeleeAttack() << std::endl;
//		csText << mCrusierMenu->GetAccuracy() << std::endl;
//		csText << mCrusierMenu->GetEvasion() << std::endl;
//		csText << mCrusierMenu->GetCrit() << std::endl;
//		csText << mCrusierMenu->GetLuck() << std::endl;
//		csText << mCrusierMenu->GetHullDefense() << std::endl;
//
//
//		//call draw font method sending all key info
//		//thankgu fonts are top left
//		mUIFont16pt->DrawFont(m2D1RT, csText.str(), LITSConst::selectedCursierStatsLeft,
//			LITSConst::selectedCursierStatsTop,
//			1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//#pragma endregion CrusierStats
//
//#pragma region FlagShipStats
//
//
//		fsText << mFlagShipMenu->GetTP() << std::endl;
//		fsText << mFlagShipMenu->GetHS() << std::endl;
//		fsText << mFlagShipMenu->GetRangeAttack() << std::endl;
//		fsText << mFlagShipMenu->GetMeleeAttack() << std::endl;
//		fsText << mFlagShipMenu->GetAccuracy() << std::endl;
//		fsText << mFlagShipMenu->GetEvasion() << std::endl;
//		fsText << mFlagShipMenu->GetCrit() << std::endl;
//		fsText << mFlagShipMenu->GetLuck() << std::endl;
//		fsText << mFlagShipMenu->GetHullDefense() << std::endl;
//
//
//		//call draw font method sending all key info
//		//thankgu fonts are top left
//		mUIFont16pt->DrawFont(m2D1RT, fsText.str(), LITSConst::selectedFlagShipStatsLeft,
//			LITSConst::selectedFlagShipStatsTop,
//			1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//#pragma endregion FlagShipStats
//
//#pragma region CorvetteStats
//
//
//		cosText << mCorvetteMenu->GetTP() << std::endl;
//		cosText << mCorvetteMenu->GetHS() << std::endl;
//		cosText << mCorvetteMenu->GetRangeAttack() << std::endl;
//		cosText << mCorvetteMenu->GetMeleeAttack() << std::endl;
//		cosText << mCorvetteMenu->GetAccuracy() << std::endl;
//		cosText << mCorvetteMenu->GetEvasion() << std::endl;
//		cosText << mCorvetteMenu->GetCrit() << std::endl;
//		cosText << mCorvetteMenu->GetLuck() << std::endl;
//		cosText << mCorvetteMenu->GetHullDefense() << std::endl;
//
//
//		//call draw font method sending all key info
//		//thankgu fonts are top left
//		mUIFont16pt->DrawFont(m2D1RT, cosText.str(), LITSConst::selectedCorvetteStatsLeft,
//			LITSConst::selectedCorvetteStatsTop,
//			1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//#pragma endregion CorvetteStats
//		break;
//
//	case GAME_PLAY_STATE:
//
//
//#pragma region PlayerStats
//		statsText.clear(); statsText.str("");
//
//		//TP pool
//		statsText << mPlayerTeam->mTPPool;
//		mUIFont30pt->DrawFont(m2D1RT, statsText.str(),
//			LITSConst::gamePlayerStatsTPLeft, LITSConst::gamePlayerStatsTPTop,
//			1.0f, 1.0f, D2D1::ColorF(0xffffff, 1.0f));
//		statsText.clear(); statsText.str("");
//
//		//separate var here as icnerment twice in single loop iteration
//		rowAdjust = 0.0f;
//
//		for (int i = 0; i < mPlayerTeam->mTeamMembers.size(); i++)
//		{
//			//HP
//			statsText << mPlayerTeam->mTeamMembers[i]->GetHS() << " / " << mPlayerTeam->mTeamMembers[i]->GetHSMax();
//			mUIFont16pt->DrawFont(m2D1RT, statsText.str(),
//				LITSConst::gamePlayerStatsLeft, LITSConst::gamePlayerStatsTop + rowAdjust,
//				1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//			statsText.clear(); statsText.str("");
//
//			rowAdjust += LITSConst::gamePlayerStatsYAdjust;
//		}
//#pragma endregion PlayerStats
//#pragma region EnemyStats
//
//		//separate var here as icnerment twice in single loop iteration
//		rowAdjust = 0.0f;
//
//		for (int i = 0; i < mEnemyTeam->mTeamMembers.size(); i++)
//		{
//			//HP
//			statsText << mEnemyTeam->mTeamMembers[i]->GetHS() << " / " << mEnemyTeam->mTeamMembers[i]->GetHSMax();
//			mUIFont16pt->DrawFont(m2D1RT, statsText.str(),
//				LITSConst::gameEnemyStatsLeft, LITSConst::gameEnemyStatsTop + rowAdjust,
//				1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//			statsText.clear(); statsText.str("");
//
//			rowAdjust += LITSConst::gameEnemyStatsYAdjust;
//		}
//#pragma endregion EnemyStats
//
//#pragma region StatusBar
//		//check which is the ucrrent team and get their status text
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM)
//		{
//			statusText << mPlayerTeam->mStatustext;
//		}
//		else if (mCurrentTeam == DPhoenix::ENEMY_TEAM)
//		{
//			statusText << mEnemyTeam->mStatustext;
//		}
//		mUIFont36pt->DrawFont(m2D1RT, statusText.str(), LITSConst::actionsStatusTextLeft, LITSConst::actionsStatusTextTop,
//			1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//		statusText.clear(); statusText.str("");
//
//#pragma endregion StatusBar
//#pragma region ActionBar
//		//if in the right stae, loop thorugh the avilable actions to display each
//		if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//			(mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKAC_MOVESTATE ||
//				mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_DOAC_MOVESTATE))
//		{
//			float initialY = 0.0f;
//
//			for (int i = 0; i < mPlayerTeam->mAvailableActions.size(); i++, initialY += LITSConst::actionTextYAdjust)
//			{
//				actionsText.clear(); actionsText.str("");
//				actionsText << mPlayerTeam->mActionstext[mPlayerTeam->mAvailableActions[i]];
//
//				mUIFont18pt->DrawFont(m2D1RT, actionsText.str(), LITSConst::actionsTextLeft, LITSConst::actionsTextTop + initialY,
//					1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//			}
//		}
//#pragma endregion ActionBAr
//
//#pragma region DmgText
//		//if melle registerd hit
//		if (mMeleeHit)
//		{
//			dmgText.clear(); dmgText.str("");
//
//			//if greater than -1 it is an git we need to display the value of
//			if (mMeleeDmg > -1)
//			{
//				dmgText << mMeleeDmg;
//			}
//			else
//			{
//				//otherwise it has missed
//				dmgText << "*MISS*";
//			}
//			//convert the pos in 3D to 2D
//			XMFLOAT2 dmgPos2d = Convert3Dto2DPoint(mMeleeDmgPos);
//			//and now display in red
//			mUIFont30pt->DrawFont(m2D1RT, dmgText.str(), dmgPos2d.x, dmgPos2d.y,
//				1.0f, 1.0f, D2D1::ColorF(0xCC0000, 1.0f));
//		}
//#pragma endregion DmgText
//		break;
//
//
//
//
//	}
//	//present to screen
//	HR(mSwapChain->Present(0, 0));
//#pragma endregion RenderFonts
//}
//
//void LITSActions::HandleEvents(DPhoenix::IEvent* e)
//{
//	switch (e->GetID())
//	{
//	case DPhoenix::EVENT_KEYPRESS:
//	{
//		DPhoenix::KeyPressEvent* kpe = (DPhoenix::KeyPressEvent*)e;
//		if (mKeyPressTimer.TotalTime() > 0.2)
//		{
//			switch (kpe->mKeycode)
//			{
//			case DIK_UP:
//			case DIK_W:
//				if (mKeyPressTimer.TotalTime() > 0.1)
//				{
//					if (mCurrentTeam == DPhoenix::PLAYER_TEAM)
//					{
//						mPlayerTeam->NextMember();
//						if (mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mTurnState == DPhoenix::CH_ACTIVE_TURNSTATE &&
//							mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKRT_MOVESTATE)
//						{
//							ResetPath();
//						}
//					}
//
//					mKeyPressTimer.Reset();
//				}
//				break;
//			case DIK_DOWN:
//			case DIK_S:
//				if (mKeyPressTimer.TotalTime() > 0.1)
//				{
//					if (mCurrentTeam == DPhoenix::PLAYER_TEAM)
//					{
//						mPlayerTeam->PrevMember();
//					}
//
//					mKeyPressTimer.Reset();
//				}
//
//				break;
//			case DIK_LEFT:
//			case DIK_A:
//				if (mGameState == GAME_PLAY_STATE)
//				{
//					mCamToFocusAngle -= 1.0f;
//				}
//
//				break;
//			case DIK_RIGHT:
//			case DIK_D:
//				if (mGameState == GAME_PLAY_STATE)
//				{
//					mCamToFocusAngle += 1.0f;
//				}
//
//				break;
//			case DIK_ESCAPE:
//				//shutdown here
//				break;
//			case DIK_RETURN:
//
//				if (mGameState == GAME_TITLE_STATE)
//				{
//					mGameState = GAME_MENU_STATE;
//				}
//				else if (mGameState == GAME_MENU_STATE)
//				{
//					if (mMenuState == CHOOSE_MENUSTATE &&
//						mPlayerTeam->mTeamMembers.size() == 4)
//					{
//						mMenuState = CONFIRM_MENUSTATE;
//						mWaitTimer.Reset();
//					}
//				}
//				else if (mGameState == GAME_PLAY_STATE)
//				{
//					//if picking route,set to move and assign happy path
//					if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//						mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKRT_MOVESTATE)
//					{
//						mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mHappyPath = mHappyPath;
//						mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState = DPhoenix::CH_MOVERT_MOVESTATE;
//					}
//					else if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//						mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKAC_MOVESTATE)
//					{
//						if (mTargets.size() > 0)
//						{
//							mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState = DPhoenix::CH_DOAC_MOVESTATE;
//							mActionStage = AC_INITIAL;
//						}
//					}
//				}
//
//				break;
//			}
//			mKeyPressTimer.Reset();
//		}
//
//	}
//	break;
//	case DPhoenix::EVENT_KEYRELEASE:
//	{
//		DPhoenix::KeyReleaseEvent* kre = (DPhoenix::KeyReleaseEvent*)e;
//		switch (kre->mKeycode)
//		{
//		case DIK_F:
//
//			break;
//		}
//	}
//	break;
//	case DPhoenix::EVENT_MOUSEMOVE:
//	{
//		DPhoenix::MouseMoveEvent* mme = (DPhoenix::MouseMoveEvent*)e;
//		mMouseX = mme->mPosX;		//difference in horizontal movement
//		mMouseY = mme->mPosY;		//difference in vertical movement
//
//		switch (mGameState)
//		{
//		case GAME_MENU_STATE:
//			if (mMenuState == CHOOSE_MENUSTATE)
//				CheckMouseHoverMenu();
//			break;
//		case GAME_PLAY_STATE:
//			if (mCurrentTeam == DPhoenix::PLAYER_TEAM)
//			{
//				CheckMouseHoverTurns();
//				CheckMouseHoverActions();
//			}
//			break;
//		}
//
//	}
//	break;
//	case DPhoenix::EVENT_MOUSECLICK:
//	{
//		DPhoenix::MouseClickEvent* mc = (DPhoenix::MouseClickEvent*)e;
//
//		if (mMouseClickTimer.TotalTime() > 0.2)
//		{
//			switch (mGameState)
//			{
//			case GAME_MENU_STATE:
//				if (mc->mButton == 0 && mMenuState == CHOOSE_MENUSTATE)
//					CheckMouseClickMenu();
//				break;
//			case GAME_PLAY_STATE:
//				if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//					mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState
//					== DPhoenix::CH_PICKRT_MOVESTATE)
//				{
//					CheckMouseClickTurns();
//					CheckMouseClickRoute();
//				}
//				if (mCurrentTeam == DPhoenix::PLAYER_TEAM &&
//					mPlayerTeam->mTeamMembers[mPlayerTeam->mCurrentMember]->mMoveState == DPhoenix::CH_PICKAC_MOVESTATE)
//				{
//					CheckMouseClickActions();
//					CheckMouseClickTarget();
//				}
//				break;
//			}
//			mMouseClickTimer.Reset();
//		}
//	}
//	case DPhoenix::EVENT_MOUSEWHEEL:
//	{
//		DPhoenix::MouseWheelEvent* mwe = (DPhoenix::MouseWheelEvent*)e;
//
//		switch (mGameState)
//		{
//
//		case GAME_PLAY_STATE:
//
//			mCameraDistanceOffset -= mwe->mWheel * 0.1f;
//
//			if (mCameraDistanceOffset < 10.0f)
//				mCameraDistanceOffset = 10.0f;
//			if (mCameraDistanceOffset > 100.0f)
//				mCameraDistanceOffset = 100.0f;
//
//
//
//
//		}
//	}
//	break;
//	}
//}
//
//void LITSActions::InitAudio()
//{
//
//}
//
//void LITSActions::RenderSprite(DPhoenix::Sprite * sprite, ID3DX11EffectTechnique * tech, bool isHUD)
//{
//	//here we calculate the scale on X and Y based on the client width / height
//	//vs. our original resolution 
//	//float scaleX = mScreenScale.x;
//	//float scaleY = mScreenScale.y;
//
//	float scaleY = 1.0f;
//	float scaleX = 1.0f;
//
//	//add to a vector to use in matrices
//	XMFLOAT3 scaleVec; scaleVec.x = scaleX;
//	scaleVec.y = scaleY; scaleVec.z = 1.0f;
//
//	//create view / projection matrix
//	XMMATRIX viewProj;
//
//	//HUD objects not affected by cameras
//	if (!isHUD)
//	{
//		//here you would add any 2D camera control
//	}
//	else
//	{
//		//an identity matrix is standard and used as a basis
//		//for other calculations
//		XMMATRIX view = XMMatrixIdentity();
//		//orthographic, left handed co-ordinates
//		XMMATRIX projection = XMMatrixOrthographicLH(
//			(float)mClientWidth,	//width of viewport
//			(float)mClientHeight,	//height of viewport
//			0.1f,					//nearplane (Z)
//			100.0f					//far plane (Z)
//		);
//
//		//create view / projection matrix (multiply / concatenate)
//		//these represent the 'camera'
//		viewProj = XMMatrixMultiply(view, projection);
//	}
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = sprite->CalculateTransforms(scaleVec, isHUD);
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::SpriteFX->SetWorldViewProj(worldViewProj);
//
//	//now we get all the matching Sprite properties to send to the shader
//	DPhoenix::Effects::SpriteFX->SetDiffuseMap(sprite->GetShaderResourceView());			//texture
//	DPhoenix::Effects::SpriteFX->SetColumn(sprite->GetCurrentFrame());						//col / frame
//	DPhoenix::Effects::SpriteFX->SetNumCols(sprite->mAnimationColumns);						//num frames
//	DPhoenix::Effects::SpriteFX->SetFlipValue(sprite->mFlipValue);							//flip value
//	DPhoenix::Effects::SpriteFX->SetLerpValue(sprite->mColorLerpValue);						//lerp value
//	DPhoenix::Effects::SpriteFX->SetOpacityValue(sprite->mOpacityValue);					//opacity
//	DPhoenix::Effects::SpriteFX->SetAltColorValue(XMLoadFloat4(&sprite->mAltColorValue));	//alt color
//
//																							//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//use current context and get current rendering pass
//		tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//
//		//call Render method of Sprite object
//		sprite->Render(md3dImmediateContext);
//	}
//
//	//reset the lerp value on the shader
//	DPhoenix::Effects::SpriteFX->SetLerpValue(0.0f);
//}
//
//void LITSActions::RenderColorPrimitive(DPhoenix::PrimitiveInstance * model,
//	ID3DX11EffectTechnique * tech)
//{
//	//here we calculate the scale on X and Y based on the client width / height
//	//vs. our original resolution 
//	float scaleX = mScreenScale.x;
//	float scaleY = mScreenScale.y;
//
//	//add to a vector to use in matrices
//	XMFLOAT3 scaleVec; scaleVec.x = scaleX;
//	scaleVec.y = scaleY; scaleVec.z = 1.0f;
//
//	//create view / projection matrix
//	XMMATRIX view = mCamera->GetView();
//	XMMATRIX proj = mCamera->GetProj();
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//	//XMMATRIX world = Identity;
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::ColorFX->SetWorldViewProj(worldViewProj);
//
//	//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//use current context and get current rendering pass
//		tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//
//		//call Render method of Sprite object
//		model->Render(md3dImmediateContext);
//	}
//}
//
//void LITSActions::RenderBasicTexPrimitive(DPhoenix::PrimitiveInstance * model,
//	ID3DX11EffectTechnique * tech)
//{
//	//here we calculate the scale on X and Y based on the client width / height
//	//vs. our original resolution 
//	float scaleX = mScreenScale.x;
//	float scaleY = mScreenScale.y;
//
//	//add to a vector to use in matrices
//	XMFLOAT3 scaleVec; scaleVec.x = scaleX;
//	scaleVec.y = scaleY; scaleVec.z = 1.0f;
//
//	//create view / projection matrix
//	XMMATRIX view = mCamera->GetView();
//	XMMATRIX proj = mCamera->GetProj();
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//	//XMMATRIX world = Identity;
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::BasicTexFX->SetWorldViewProj(worldViewProj);
//	DPhoenix::Effects::BasicTexFX->SetAmbLight(XMLoadFloat4(&mAmbientColor));
//	DPhoenix::Effects::BasicTexFX->SetAmbIntensity(mAmbIntensity);
//	DPhoenix::Effects::BasicTexFX->SetDiffuseMap(model->mDiffuseMap);
//	DPhoenix::Effects::BasicTexFX->SetTexScaleU(model->mTexScaleU);
//	DPhoenix::Effects::BasicTexFX->SetTexScaleV(model->mTexScaleV);
//
//	//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//use current context and get current rendering pass
//		tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//
//		//call Render method of Sprite object
//		model->Render(md3dImmediateContext);
//	}
//}
//
//void LITSActions::RenderLitTexPrimitive(DPhoenix::PrimitiveInstance * model,
//	ID3DX11EffectTechnique * tech)
//{
//
//	//create view / projection matrix
//	XMMATRIX view = mCamera->GetView();
//	XMMATRIX proj = mCamera->GetProj();
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//
//	DPhoenix::Effects::LitTexFX->SetWorld(
//		world
//	);
//
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::LitTexFX->SetWorldViewProj(worldViewProj);
//
//	// Inverse-transpose is just applied to normals.  So zero out 
//	// translation row so that it doesn't get into our inverse-transpose
//	// calculation--we don't want the inverse-transpose of the translation.
//	XMMATRIX A = world;
//	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//
//	XMVECTOR det = XMMatrixDeterminant(A);
//
//	DPhoenix::Effects::LitTexFX->SetWorldInvTranpose(
//		XMMatrixTranspose(XMMatrixInverse(&det, A))
//	);
//
//	DPhoenix::Effects::LitTexFX->SetAmbLight(XMLoadFloat4(&mAmbientColor));
//	DPhoenix::Effects::LitTexFX->SetAmbIntensity(mAmbIntensity);
//	DPhoenix::Effects::LitTexFX->SetDiffuseMap(model->mDiffuseMap);
//
//	DPhoenix::Effects::LitTexFX->SetEyePosW(mCamera->mPosition);
//	DPhoenix::Effects::LitTexFX->SetFogEnabled(mFogEnabled);
//	DPhoenix::Effects::LitTexFX->SetFogColor(XMLoadFloat4(&mFogColor));
//	DPhoenix::Effects::LitTexFX->SetFogStart(mFogStart);
//	DPhoenix::Effects::LitTexFX->SetFogRange(mFogRange);
//
//	DPhoenix::Effects::LitTexFX->SetDirtLights(mDirLightsArray);
//	DPhoenix::Effects::LitTexFX->SetMaterial(*model->mMaterial);
//
//	DPhoenix::Effects::LitTexFX->SetDirLightsCount(mNumDirLights);
//
//	DPhoenix::Effects::LitTexFX->SetPointLights(mPointLightsArray);
//	DPhoenix::Effects::LitTexFX->SetPointLightsCount(mNumPointLights);
//
//	//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//use current context and get current rendering pass
//		tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//
//		//call Render method of Sprite object
//		model->Render(md3dImmediateContext);
//	}
//}
//
//void LITSActions::RenderLitTexNormPrimitive(DPhoenix::PrimitiveInstance * model,
//	ID3DX11EffectTechnique * tech)
//{
//
//	//create view / projection matrix
//	XMMATRIX view = mCamera->GetView();
//	XMMATRIX proj = mCamera->GetProj();
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//
//	DPhoenix::Effects::LitTexNormalFX->SetWorld(
//		world
//	);
//
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::LitTexNormalFX->SetWorldViewProj(worldViewProj);
//
//	// Inverse-transpose is just applied to normals.  So zero out 
//	// translation row so that it doesn't get into our inverse-transpose
//	// calculation--we don't want the inverse-transpose of the translation.
//	XMMATRIX A = world;
//	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//
//	XMVECTOR det = XMMatrixDeterminant(A);
//
//	DPhoenix::Effects::LitTexNormalFX->SetWorldInvTranpose(
//		XMMatrixTranspose(XMMatrixInverse(&det, A))
//	);
//
//	DPhoenix::Effects::LitTexNormalFX->SetAmbLight(XMLoadFloat4(&mAmbientColor));
//	DPhoenix::Effects::LitTexNormalFX->SetAmbIntensity(mAmbIntensity);
//	DPhoenix::Effects::LitTexNormalFX->SetDiffuseMap(model->mDiffuseMap);
//
//	DPhoenix::Effects::LitTexNormalFX->SetNormalMap(model->mNormalMap);
//
//	DPhoenix::Effects::LitTexNormalFX->SetEyePosW(mCamera->mPosition);
//	DPhoenix::Effects::LitTexNormalFX->SetFogEnabled(mFogEnabled);
//	DPhoenix::Effects::LitTexNormalFX->SetFogColor(XMLoadFloat4(&mFogColor));
//	DPhoenix::Effects::LitTexNormalFX->SetFogStart(mFogStart);
//	DPhoenix::Effects::LitTexNormalFX->SetFogRange(mFogRange);
//
//	DPhoenix::Effects::LitTexNormalFX->SetDirLights(mDirLightsArray);
//	DPhoenix::Effects::LitTexNormalFX->SetMaterial(*model->mMaterial);
//
//	DPhoenix::Effects::LitTexNormalFX->SetDirLightsCount(mNumDirLights);
//
//	DPhoenix::Effects::LitTexNormalFX->SetPointLights(mPointLightsArray);
//	DPhoenix::Effects::LitTexNormalFX->SetPointLightsCount(mNumPointLights);
//
//	DPhoenix::Effects::LitTexNormalFX->SetOpacity(model->mOpacity);
//
//	//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//use current context and get current rendering pass
//		tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//
//		//call Render method of Sprite object
//		model->Render(md3dImmediateContext);
//	}
//	//reset beofre next render
//	DPhoenix::Effects::LitTexNormalFX->SetOpacity(1.0f);
//
//}
//
////call skybox draw call
//void LITSActions::RenderSkybox(DPhoenix::Sky* skybox,
//	ID3D11DeviceContext* dc)
//{
//	skybox->Draw(dc, mCamera);
//}
//
//void LITSActions::RenderBillboardSprite(DPhoenix::BillboardSprite * sprite,
//	ID3DX11EffectTechnique * tech)
//{
//	//create view / projection matrix
//	XMMATRIX view = mCamera->GetView();
//	XMMATRIX proj = mCamera->GetProj();
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = sprite->GetWorldBS(mCamera->mPosition);
//
//	DPhoenix::Effects::LitBillboardFX->SetWorld(
//		world
//	);
//
//	//XMMATRIX world = Identity;
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::LitBillboardFX->SetWorldViewProj(worldViewProj);
//
//	// Inverse-transpose is just applied to normals.  So zero out 
//	// translation row so that it doesn't get into our inverse-transpose
//	// calculation--we don't want the inverse-transpose of the translation.
//	XMMATRIX A = world;
//	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//
//	XMVECTOR det = XMMatrixDeterminant(A);
//
//	DPhoenix::Effects::LitBillboardFX->SetWorldInvTranpose(
//		XMMatrixTranspose(XMMatrixInverse(&det, A))
//	);
//
//	DPhoenix::Effects::LitBillboardFX->SetAmbLight(XMLoadFloat4(&mAmbientColor));
//	DPhoenix::Effects::LitBillboardFX->SetAmbIntensity(mAmbIntensity);
//	DPhoenix::Effects::LitBillboardFX->SetDiffuseMap(sprite->GetShaderResourceView());
//
//	DPhoenix::Effects::LitBillboardFX->SetEyePosW(mCamera->mPosition);
//	DPhoenix::Effects::LitBillboardFX->SetFogColor(XMLoadFloat4(&mFogColor));
//	DPhoenix::Effects::LitBillboardFX->SetFogStart(mFogStart);
//	DPhoenix::Effects::LitBillboardFX->SetFogRange(mFogRange);
//
//	Material* materialStandard = new Material();
//
//	materialStandard->Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	materialStandard->Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	materialStandard->Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 32.0f);
//	materialStandard->Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
//
//	DPhoenix::Effects::LitBillboardFX->SetMaterial(*materialStandard);
//
//	DPhoenix::Effects::LitBillboardFX->SetDirtLights(mDirLightsArray);
//	DPhoenix::Effects::LitBillboardFX->SetDirLightsCount(mNumDirLights);
//
//	DPhoenix::Effects::LitBillboardFX->SetPointLights(mPointLightsArray);
//	DPhoenix::Effects::LitBillboardFX->SetPointLightsCount(mNumPointLights);
//
//	DPhoenix::Effects::LitBillboardFX->SetColumn(sprite->GetCurrentFrame());					//col / frame
//	DPhoenix::Effects::LitBillboardFX->SetNumCols(sprite->mAnimationColumns);					//num frames
//	DPhoenix::Effects::LitBillboardFX->SetFlipValue(sprite->mFlipValue);						//flip value
//	DPhoenix::Effects::LitBillboardFX->SetLerpValue(sprite->mColorLerpValue);					//lerp value
//	DPhoenix::Effects::LitBillboardFX->SetOpacity(sprite->mOpacityValue);					//opacity
//	DPhoenix::Effects::LitBillboardFX->SetAltColorValue(XMLoadFloat4(&sprite->mAltColorValue));	//alt color
//
//																								//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//use current context and get current rendering pass
//		tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//
//		//call Render method of Sprite object
//		sprite->RenderBS(md3dImmediateContext);
//	}
//}
//
//
//void LITSActions::RenderBasicModel(DPhoenix::BasicModelInstance * model,
//	ID3DX11EffectTechnique * tech)
//{
//
//	//create view / projection matrix
//	XMMATRIX view = mCamera->GetView();
//	XMMATRIX proj = mCamera->GetProj();
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//
//	DPhoenix::Effects::LitTexFX->SetWorld(
//		world
//	);
//
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::LitTexFX->SetWorldViewProj(worldViewProj);
//
//	// Inverse-transpose is just applied to normals.  So zero out 
//	// translation row so that it doesn't get into our inverse-transpose
//	// calculation--we don't want the inverse-transpose of the translation.
//	XMMATRIX A = world;
//	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//
//	XMVECTOR det = XMMatrixDeterminant(A);
//
//	DPhoenix::Effects::LitTexFX->SetWorldInvTranpose(
//		XMMatrixTranspose(XMMatrixInverse(&det, A))
//	);
//
//	DPhoenix::Effects::LitTexFX->SetAmbLight(XMLoadFloat4(&mAmbientColor));
//	DPhoenix::Effects::LitTexFX->SetAmbIntensity(mAmbIntensity);
//
//	DPhoenix::Effects::LitTexFX->SetEyePosW(mCamera->mPosition);
//	DPhoenix::Effects::LitTexFX->SetFogEnabled(mFogEnabled);
//	DPhoenix::Effects::LitTexFX->SetFogColor(XMLoadFloat4(&mFogColor));
//	DPhoenix::Effects::LitTexFX->SetFogStart(mFogStart);
//	DPhoenix::Effects::LitTexFX->SetFogRange(mFogRange);
//
//	DPhoenix::Effects::LitTexFX->SetDirtLights(mDirLightsArray);
//
//	DPhoenix::Effects::LitTexFX->SetDirLightsCount(mNumDirLights);
//
//	DPhoenix::Effects::LitTexFX->SetPointLights(mPointLightsArray);
//	DPhoenix::Effects::LitTexFX->SetPointLightsCount(mNumPointLights);
//
//	//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//loop through subsets
//		for (UINT subset = 0; subset < model->Model->SubsetCount; ++subset)
//		{
//			//get pointer to the model / mesh data
//			DPhoenix::BasicModel* bmPtr = model->Model;
//			//get the material index for this subset
//			UINT materialIndex = bmPtr->Subsets[subset].materialIndex;
//			//set the material 
//			DPhoenix::Effects::LitTexFX->SetMaterial(bmPtr->Mat[materialIndex]);
//			//if we have a diffuse map then set it for this subset
//			if (bmPtr->DiffuseMapSRV[materialIndex] != NULL)
//			{
//				DPhoenix::Effects::LitTexFX->SetDiffuseMap(bmPtr->DiffuseMapSRV[materialIndex]);
//			}
//			else
//			{
//				DPhoenix::Effects::LitTexFX->SetDiffuseMap(NULL);
//			}
//			//call the draw method with the given subset
//			tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//			bmPtr->ModelMesh.Draw(md3dImmediateContext, subset);
//		}
//	}
//}
//
//void LITSActions::RenderBasicModelNormal(DPhoenix::BasicModelInstance * model,
//	ID3DX11EffectTechnique * tech)
//{
//
//	//create view / projection matrix
//	XMMATRIX view = mCamera->GetView();
//	XMMATRIX proj = mCamera->GetProj();
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//
//	DPhoenix::Effects::LitTexNormalFX->SetWorld(
//		world
//	);
//
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::LitTexNormalFX->SetWorldViewProj(worldViewProj);
//
//	// Inverse-transpose is just applied to normals.  So zero out 
//	// translation row so that it doesn't get into our inverse-transpose
//	// calculation--we don't want the inverse-transpose of the translation.
//	XMMATRIX A = world;
//	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//
//	XMVECTOR det = XMMatrixDeterminant(A);
//
//	DPhoenix::Effects::LitTexNormalFX->SetWorldInvTranpose(
//		XMMatrixTranspose(XMMatrixInverse(&det, A))
//	);
//
//	DPhoenix::Effects::LitTexNormalFX->SetAmbLight(XMLoadFloat4(&mAmbientColor));
//	DPhoenix::Effects::LitTexNormalFX->SetAmbIntensity(mAmbIntensity);
//
//	DPhoenix::Effects::LitTexNormalFX->SetEyePosW(mCamera->mPosition);
//	DPhoenix::Effects::LitTexNormalFX->SetFogEnabled(mFogEnabled);
//	DPhoenix::Effects::LitTexNormalFX->SetFogColor(XMLoadFloat4(&mFogColor));
//	DPhoenix::Effects::LitTexNormalFX->SetFogStart(mFogStart);
//	DPhoenix::Effects::LitTexNormalFX->SetFogRange(mFogRange);
//
//	DPhoenix::Effects::LitTexNormalFX->SetDirLights(mDirLightsArray);
//
//	DPhoenix::Effects::LitTexNormalFX->SetDirLightsCount(mNumDirLights);
//
//	DPhoenix::Effects::LitTexNormalFX->SetPointLights(mPointLightsArray);
//	DPhoenix::Effects::LitTexNormalFX->SetPointLightsCount(mNumPointLights);
//
//	//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//loop through subsets
//		for (UINT subset = 0; subset < model->Model->SubsetCount; ++subset)
//		{
//			//get pointer to the model / mesh data
//			DPhoenix::BasicModel* bmPtr = model->Model;
//			//get the material index for this subset
//			UINT materialIndex = bmPtr->Subsets[subset].materialIndex;
//			//set the material 
//			DPhoenix::Effects::LitTexNormalFX->SetMaterial(bmPtr->Mat[materialIndex]);
//			//if we have a diffuse map then set it for this subset
//			if (bmPtr->DiffuseMapSRV[materialIndex] != NULL)
//			{
//				DPhoenix::Effects::LitTexNormalFX->SetDiffuseMap(bmPtr->DiffuseMapSRV[materialIndex]);
//			}
//
//			if (bmPtr->NormalMapSRV[materialIndex] != NULL)
//			{
//				DPhoenix::Effects::LitTexNormalFX->SetNormalMap(bmPtr->NormalMapSRV[materialIndex]);
//			}
//			//call the draw method with the given subset
//			tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//			bmPtr->ModelMesh.Draw(md3dImmediateContext, subset);
//		}
//	}
//}
//
//void LITSActions::RenderSkinnedModel(DPhoenix::SkinnedModelInstance * model,
//	ID3DX11EffectTechnique * tech)
//{
//
//	//create view / projection matrix
//	XMMATRIX view = mCamera->GetView();
//	XMMATRIX proj = mCamera->GetProj();
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//
//	DPhoenix::Effects::LitTexFX->SetWorld(
//		world
//	);
//
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::LitTexFX->SetWorldViewProj(worldViewProj);
//
//	// Inverse-transpose is just applied to normals.  So zero out 
//	// translation row so that it doesn't get into our inverse-transpose
//	// calculation--we don't want the inverse-transpose of the translation.
//	XMMATRIX A = world;
//	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//
//	XMVECTOR det = XMMatrixDeterminant(A);
//
//	DPhoenix::Effects::LitTexFX->SetWorldInvTranpose(
//		XMMatrixTranspose(XMMatrixInverse(&det, A))
//	);
//
//	std::vector<XMFLOAT4X4> finalTransforms = model->GetFinalTransforms();
//	/*std::vector<XMFLOAT4X4> finalTransforms = model->GetBoneTransforms();*/
//	DPhoenix::Effects::LitTexFX->SetBoneTransforms(
//		&finalTransforms[0],
//		finalTransforms.size());
//
//	DPhoenix::Effects::LitTexFX->SetAmbLight(XMLoadFloat4(&mAmbientColor));
//	DPhoenix::Effects::LitTexFX->SetAmbIntensity(mAmbIntensity);
//
//	DPhoenix::Effects::LitTexFX->SetEyePosW(mCamera->mPosition);
//	DPhoenix::Effects::LitTexFX->SetFogEnabled(mFogEnabled);
//	DPhoenix::Effects::LitTexFX->SetFogColor(XMLoadFloat4(&mFogColor));
//	DPhoenix::Effects::LitTexFX->SetFogStart(mFogStart);
//	DPhoenix::Effects::LitTexFX->SetFogRange(mFogRange);
//
//	DPhoenix::Effects::LitTexFX->SetDirtLights(mDirLightsArray);
//
//	DPhoenix::Effects::LitTexFX->SetDirLightsCount(mNumDirLights);
//
//	DPhoenix::Effects::LitTexFX->SetPointLights(mPointLightsArray);
//	DPhoenix::Effects::LitTexFX->SetPointLightsCount(mNumPointLights);
//
//	//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//loop through subsets
//		for (UINT subset = 0; subset < model->Model->SubsetCount; ++subset)
//		{
//			//get pointer to the model / mesh data
//			DPhoenix::SkinnedModel* bmPtr = model->Model;
//			//get the material index for this subset
//			UINT materialIndex = bmPtr->Subsets[subset].materialIndex;
//			//set the material 
//			DPhoenix::Effects::LitTexFX->SetMaterial(bmPtr->Mat[materialIndex]);
//			//if we have a diffuse map then set it for this subset
//			if (bmPtr->DiffuseMapSRV[materialIndex] != NULL)
//			{
//				DPhoenix::Effects::LitTexFX->SetDiffuseMap(bmPtr->DiffuseMapSRV[materialIndex]);
//			}
//			else
//			{
//				ID3D11ShaderResourceView* tempTex = mTexMgr.CreateTexture("Models\\wood.png");
//				DPhoenix::Effects::LitTexFX->SetDiffuseMap(tempTex);
//			}
//			//call the draw method with the given subset
//			tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//			bmPtr->ModelMesh.Draw(md3dImmediateContext, subset);
//		}
//	}
//}
//
//void LITSActions::RenderSkinnedModelNormal(DPhoenix::SkinnedModelInstance * model,
//	ID3DX11EffectTechnique * tech)
//{
//
//	//create view / projection matrix
//	XMMATRIX view = mCamera->GetView();
//	XMMATRIX proj = mCamera->GetProj();
//
//	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
//
//	//concatenate world / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//
//	DPhoenix::Effects::LitTexNormalFX->SetWorld(
//		world
//	);
//
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::LitTexNormalFX->SetWorldViewProj(worldViewProj);
//
//	// Inverse-transpose is just applied to normals.  So zero out 
//	// translation row so that it doesn't get into our inverse-transpose
//	// calculation--we don't want the inverse-transpose of the translation.
//	XMMATRIX A = world;
//	A.r[3] = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
//
//	XMVECTOR det = XMMatrixDeterminant(A);
//
//	DPhoenix::Effects::LitTexNormalFX->SetWorldInvTranpose(
//		XMMatrixTranspose(XMMatrixInverse(&det, A))
//	);
//
//	std::vector<XMFLOAT4X4> finalTransforms = model->GetFinalTransforms();
//	/*std::vector<XMFLOAT4X4> finalTransforms = model->GetBoneTransforms();*/
//	DPhoenix::Effects::LitTexNormalFX->SetBoneTransforms(
//		&finalTransforms[0],
//		finalTransforms.size());
//
//	DPhoenix::Effects::LitTexNormalFX->SetAmbLight(XMLoadFloat4(&mAmbientColor));
//	DPhoenix::Effects::LitTexNormalFX->SetAmbIntensity(mAmbIntensity);
//
//	DPhoenix::Effects::LitTexNormalFX->SetEyePosW(mCamera->mPosition);
//	DPhoenix::Effects::LitTexNormalFX->SetFogEnabled(mFogEnabled);
//	DPhoenix::Effects::LitTexNormalFX->SetFogColor(XMLoadFloat4(&mFogColor));
//	DPhoenix::Effects::LitTexNormalFX->SetFogStart(mFogStart);
//	DPhoenix::Effects::LitTexNormalFX->SetFogRange(mFogRange);
//
//	DPhoenix::Effects::LitTexNormalFX->SetDirLights(mDirLightsArray);
//
//	DPhoenix::Effects::LitTexNormalFX->SetDirLightsCount(mNumDirLights);
//
//	DPhoenix::Effects::LitTexNormalFX->SetPointLights(mPointLightsArray);
//	DPhoenix::Effects::LitTexNormalFX->SetPointLightsCount(mNumPointLights);
//
//	//render using effect shader technique
//	D3DX11_TECHNIQUE_DESC techDesc;
//	tech->GetDesc(&techDesc);
//	for (UINT p = 0; p < techDesc.Passes; ++p)
//	{
//		//loop through subsets
//		for (UINT subset = 0; subset < model->Model->SubsetCount; ++subset)
//		{
//			//get pointer to the model / mesh data
//			DPhoenix::SkinnedModel* bmPtr = model->Model;
//			//get the material index for this subset
//			UINT materialIndex = bmPtr->Subsets[subset].materialIndex;
//			//set the material 
//			DPhoenix::Effects::LitTexNormalFX->SetMaterial(bmPtr->Mat[materialIndex]);
//			//if we have a diffuse map then set it for this subset
//			if (bmPtr->DiffuseMapSRV[materialIndex] != NULL)
//			{
//				DPhoenix::Effects::LitTexNormalFX->SetDiffuseMap(bmPtr->DiffuseMapSRV[materialIndex]);
//			}
//			else
//			{
//				ID3D11ShaderResourceView* tempTex = mTexMgr.CreateTexture("Models\\wood.png");
//				DPhoenix::Effects::LitTexNormalFX->SetDiffuseMap(tempTex);
//			}
//
//			if (bmPtr->NormalMapSRV[materialIndex] != NULL)
//			{
//				DPhoenix::Effects::LitTexNormalFX->SetNormalMap(bmPtr->NormalMapSRV[materialIndex]);
//			}
//			else
//			{
//				ID3D11ShaderResourceView* tempTex = mTexMgr.CreateTexture("Models\\woodNM.png");
//				DPhoenix::Effects::LitTexNormalFX->SetNormalMap(tempTex);
//
//			}
//			//call the draw method with the given subset
//			tech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
//			bmPtr->ModelMesh.Draw(md3dImmediateContext, subset);
//		}
//	}
//}
