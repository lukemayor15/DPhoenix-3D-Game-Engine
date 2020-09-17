//#include "Engine.h"
//#include "BillboardSprite.h"
//#include "ParticleEmitter.h"
//
//#include "LITSConst.h"
//#include "Team.h"
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
//
////initial class definition inheriting fron Engine
//class LITSStats : public DPhoenix::Engine
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
//#pragma endregion BTLTMembers
//
//public:
//	LITSStats(HINSTANCE hInstance);
//	~LITSStats();
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
//	void LITSStats::HandleEvents(DPhoenix::IEvent* e);
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
//	void LITSStats::RenderBasicTexPrimitive(DPhoenix::PrimitiveInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / specifically handles textured primitives with directional lights
//	//and fog
//	void LITSStats::RenderLitTexPrimitive(DPhoenix::PrimitiveInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / now with normal mapping!
//	void LITSStats::RenderLitTexNormPrimitive(DPhoenix::PrimitiveInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / now with normal mapping!
//	void RenderSkybox(DPhoenix::Sky* skybox,
//		ID3D11DeviceContext* dc);
//
//	//new method / render billboard sprtes
//	void LITSStats::RenderBillboardSprite(DPhoenix::BillboardSprite * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / render static mesh with subsets
//	void LITSStats::RenderBasicModel(DPhoenix::BasicModelInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / render static mesh with subsets
//	void LITSStats::RenderBasicModelNormal(DPhoenix::BasicModelInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / render animated lit mesh with subsets
//	void LITSStats::RenderSkinnedModel(DPhoenix::SkinnedModelInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//	//new method / render animated lit normal mapped mesh with subsets
//	void LITSStats::RenderSkinnedModelNormal(DPhoenix::SkinnedModelInstance * model,
//		ID3DX11EffectTechnique * tech);
//
//#pragma region LITSMethods
//
//	bool LITSStats::CheckPointInRect(int pointX, int pointY, RECT rect);
//	void LITSStats::CheckMouseHoverMenu();
//	void LITSStats::CheckMouseClickMenu();
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
//	LITSStats theApp(hInstance);
//
//	if (!theApp.Init(false))
//		return 0;
//
//	return theApp.Run();
//}
//
////constructor - don't really need to add much here
//LITSStats::LITSStats(HINSTANCE hInstance)
//	: Engine(hInstance)
//{
//	mMainWndCaption = "Big Trouble in Little Toyland";
//	//create camera here to prevent
//	//issues with matrix generation
//	mCamera = new DPhoenix::Camera();
//}
//
////destructor (release any memory as necessary)
//LITSStats::~LITSStats()
//{
//	DPhoenix::Effects::DestroyAll();
//	DPhoenix::InputLayouts::DestroyAll();
//}
//
////any additional initialisation (we generally initiaise game assets here)
//bool LITSStats::Init(bool fullScreen)
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
//	mFogEnabled = false;
//	mFogStart = 100.0f;
//	mFogRange = 1000.0f;
//	mFogColor = XMFLOAT4(0.25f, 0.0f, 0.0f, 1.0f);
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
//
//	mBrusierMenu = new DPhoenix::CharacterClass(DPhoenix::BRUSIER_SHIP_CLASS, &mTexMgr, md3dDevice, &mAudioMgr);
//	mBrusierMenu->mModelInstance->mPosition.x = 50.0f;
//	mBrusierMenu->mModelInstance->mPosition.y = -7.5f;
//	mBrusierMenu->mModelInstance->mPosition.z = mFlagShipMenu->mModelInstance->mPosition.z - 12.5f;
//	mBrusierMenu->mModelInstance->mScale = XMFLOAT3(10.0f, 10.0f, 10.0f);
//	mBrusierMenu->mModelInstance->mRotation.y = XMConvertToRadians(90.0f);
//
//	mCorvetteMenu = new DPhoenix::CharacterClass(DPhoenix::CORVETTE_SHIP_CLASS, &mTexMgr, md3dDevice, &mAudioMgr);
//	mCorvetteMenu->mModelInstance->mPosition.x = 50.0f;
//	mCorvetteMenu->mModelInstance->mPosition.y = -7.5f;
//	mCorvetteMenu->mModelInstance->mPosition.z = mBrusierMenu->mModelInstance->mPosition.z - 12.5f;
//	mCorvetteMenu->mModelInstance->mScale = XMFLOAT3(10.0f, 10.0f, 10.0f);
//	mCorvetteMenu->mModelInstance->mRotation.y = XMConvertToRadians(90.0f);
//
//	mCrusierMenu = new DPhoenix::CharacterClass(DPhoenix::CRUSIER_SHIP_CLASS, &mTexMgr, md3dDevice, &mAudioMgr);
//	mCrusierMenu->mModelInstance->mPosition.x = 50.0f;
//	mCrusierMenu->mModelInstance->mPosition.y = -7.5f;
//	mCrusierMenu->mModelInstance->mPosition.z = mCorvetteMenu->mModelInstance->mPosition.z - 12.5;
//	mCrusierMenu->mModelInstance->mScale = XMFLOAT3(6.0f, 6.0f, 6.0f);
//	mCrusierMenu->mModelInstance->mRotation.y = XMConvertToRadians(90.0f);
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
//
//#pragma endregion LITSInit
//	return true;
//}
//
////here we give a point location and see if is in the given rect
//bool LITSStats::CheckPointInRect(int pointX, int pointY, RECT rect)
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
//void LITSStats::CheckMouseHoverMenu()
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
//void LITSStats::CheckMouseClickMenu()
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
////what to do on resize - mainly we'lll just call the parent / engine's method
//void LITSStats::OnResize()
//{
//	Engine::OnResize();
//
//	//the window resized so the aspect ratio needs
//	//to be calculated again, and the projection matrix
//	mCamera->SetPerspective(0.25f * XM_PI, AspectRatio(), 1.0f, 100000.0f);
//}
//
////update scene - here is where our update logic for the game loop goes
//void LITSStats::UpdateScene(float dt)
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
//				case 3:
//					mEnemyTeam->mTeamMembers.push_back(new DPhoenix::CharacterClass(*mCorvetteMenu));
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
//			}
//
//			break;
//		}
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
//void LITSStats::BuildGeometryBuffers()
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
//void LITSStats::DrawScene()
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
//	//RenderSkybox(mSkybox, md3dImmediateContext);
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
//	switch (mGameState)
//	{
//	case GAME_MENU_STATE:
//		RenderSprite(mSelectedClassMenu, activeSpriteTech, true);
//		break;
//	}
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
//
//	switch (mGameState)
//	{
//	case GAME_MENU_STATE:
//		std::ostringstream leveltext;
//
//		leveltext << mSelectedLevel;
//
//		mUIFont90pt->DrawFont(m2D1RT, leveltext.str(), LITSConst::selectedLevelLeft,
//			LITSConst::selectedLevelTop, 1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//
//
//#pragma endregion RenderFonts
//#pragma region SelectedClasses
//		std::ostringstream classesText;
//
//		//loop through selected classes and adjust row pos with each
//		float rowAdjust = 0.0f;
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
//		#pragma region BrusierStats
//	std::ostringstream bsText;
//
//	bsText << mBrusierMenu->GetTP() << std::endl;
//	bsText << mBrusierMenu->GetHS() << std::endl;
//	bsText << mBrusierMenu->GetRangeAttack() << std::endl;
//	bsText << mBrusierMenu->GetMeleeAttack() << std::endl;
//	bsText << mBrusierMenu->GetAccuracy() << std::endl;
//	bsText << mBrusierMenu->GetEvasion() << std::endl;
//	bsText << mBrusierMenu->GetCrit() << std::endl;
//	bsText << mBrusierMenu->GetLuck() << std::endl;
//	bsText << mBrusierMenu->GetHullDefense() << std::endl;
//
//	//call draw font method sending all key info
//	//thankgu fonts are top left
//	mUIFont16pt->DrawFont(m2D1RT, bsText.str(), LITSConst::selectedBursierStatsLeft,
//		LITSConst::selectedBrusierTop,
//		1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//#pragma endregion BrusierStats
//
//#pragma region CrusierStats
//	std::ostringstream csText;
//
//	csText << mCrusierMenu->GetTP() << std::endl;
//	csText << mCrusierMenu->GetHS() << std::endl;
//	csText << mCrusierMenu->GetRangeAttack() << std::endl;
//	csText << mCrusierMenu->GetMeleeAttack() << std::endl;
//	csText << mCrusierMenu->GetAccuracy() << std::endl;
//	csText << mCrusierMenu->GetEvasion() << std::endl;
//	csText << mCrusierMenu->GetCrit() << std::endl;
//	csText << mCrusierMenu->GetLuck() << std::endl;
//	csText << mCrusierMenu->GetHullDefense() << std::endl;
//
//
//	//call draw font method sending all key info
//	//thankgu fonts are top left
//	mUIFont16pt->DrawFont(m2D1RT, csText.str(), LITSConst::selectedCursierStatsLeft,
//		LITSConst::selectedCursierStatsTop,
//		1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//#pragma endregion CrusierStats
//
//#pragma region FlagShipStats
//	std::ostringstream fsText;
//
//	fsText << mFlagShipMenu->GetTP() << std::endl;
//	fsText << mFlagShipMenu->GetHS() << std::endl;
//	fsText << mFlagShipMenu->GetRangeAttack() << std::endl;
//	fsText << mFlagShipMenu->GetMeleeAttack() << std::endl;
//	fsText << mFlagShipMenu->GetAccuracy() << std::endl;
//	fsText << mFlagShipMenu->GetEvasion() << std::endl;
//	fsText << mFlagShipMenu->GetCrit() << std::endl;
//	fsText << mFlagShipMenu->GetLuck() << std::endl;
//	fsText << mFlagShipMenu->GetHullDefense() << std::endl;
//
//
//	//call draw font method sending all key info
//	//thankgu fonts are top left
//	mUIFont16pt->DrawFont(m2D1RT, fsText.str(), LITSConst::selectedFlagShipStatsLeft,
//		LITSConst::selectedFlagShipStatsTop,
//		1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//#pragma endregion FlagShipStats
//
//#pragma region CorvetteStats
//	std::ostringstream cosText;
//
//	cosText << mCorvetteMenu->GetTP() << std::endl;
//	cosText << mCorvetteMenu->GetHS() << std::endl;
//	cosText << mCorvetteMenu->GetRangeAttack() << std::endl;
//	cosText << mCorvetteMenu->GetMeleeAttack() << std::endl;
//	cosText << mCorvetteMenu->GetAccuracy() << std::endl;
//	cosText << mCorvetteMenu->GetEvasion() << std::endl;
//	cosText << mCorvetteMenu->GetCrit() << std::endl;
//	cosText << mCorvetteMenu->GetLuck() << std::endl;
//	cosText << mCorvetteMenu->GetHullDefense() << std::endl;
//
//
//	//call draw font method sending all key info
//	//thankgu fonts are top left
//	mUIFont16pt->DrawFont(m2D1RT, cosText.str(), LITSConst::selectedCorvetteStatsLeft,
//		LITSConst::selectedCorvetteStatsTop,
//		1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 1.0f));
//#pragma endregion CorvetteStats
//
//
//
//	}
//	//present to screen
//	HR(mSwapChain->Present(0, 0));
//
//}
//
//void LITSStats::HandleEvents(DPhoenix::IEvent* e)
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
//
//				break;
//			case DIK_DOWN:
//
//				break;
//			case DIK_LEFT:
//
//				break;
//			case DIK_RIGHT:
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
//			}
//			mMouseClickTimer.Reset();
//		}
//	}
//	break;
//	}
//}
//
//void LITSStats::InitAudio()
//{
//
//}
//
//void LITSStats::RenderSprite(DPhoenix::Sprite * sprite, ID3DX11EffectTechnique * tech, bool isHUD)
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
//void LITSStats::RenderColorPrimitive(DPhoenix::PrimitiveInstance * model,
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
//void LITSStats::RenderBasicTexPrimitive(DPhoenix::PrimitiveInstance * model,
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
//void LITSStats::RenderLitTexPrimitive(DPhoenix::PrimitiveInstance * model,
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
//void LITSStats::RenderLitTexNormPrimitive(DPhoenix::PrimitiveInstance * model,
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
////call skybox draw call
//void LITSStats::RenderSkybox(DPhoenix::Sky* skybox,
//	ID3D11DeviceContext* dc)
//{
//	skybox->Draw(dc, mCamera);
//}
//
//void LITSStats::RenderBillboardSprite(DPhoenix::BillboardSprite * sprite,
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
//void LITSStats::RenderBasicModel(DPhoenix::BasicModelInstance * model,
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
//void LITSStats::RenderBasicModelNormal(DPhoenix::BasicModelInstance * model,
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
//void LITSStats::RenderSkinnedModel(DPhoenix::SkinnedModelInstance * model,
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
//void LITSStats::RenderSkinnedModelNormal(DPhoenix::SkinnedModelInstance * model,
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
