//#include "Engine.h"
//
////initial class definition inheriting fron Engine
//class FPSDemo : public DPhoenix::Engine
//{
//private:
//	//depth stencil (to handle multiple overlayed sprites)
//	ID3D11DepthStencilState* mDepthStencilState;
//	ID3D11DepthStencilState* mDepthDisabledStencilState;
//	D3D11_DEPTH_STENCIL_DESC mDepthStencilDesc;
//	D3D11_DEPTH_STENCIL_DESC mDepthDisabledStencilDesc;
//
//
//	//texture manager
//	DPhoenix::TextureMgr mTexMgr;
//
//	//audio manager
//	DPhoenix::AudioMgr mAudioMgr;
//
//
//	//font pointer - debug text
//	DPhoenix::Font* mDebugFont;
//
//	//screen scale (for window stretching)
//	XMFLOAT2 mScreenScale;
//
//	//sprite position
//	XMFLOAT3 mPosition;
//	XMFLOAT3 mVelocity;
//
//
//	//view and projection matrices
//	XMMATRIX mView;
//	XMMATRIX mProjection;
//
//	//for geometry genreation
//	DPhoenix::GeometryGenerator* mGeoGen;
//	DPhoenix::GeometryGenerator* mGeoGen1;
//	DPhoenix::GeometryGenerator* mGeoGen2;
//
//	DPhoenix::GeometryGenerator::MeshData* mBox;
//	DPhoenix::GeometryGenerator::MeshData* mSphere;
//	DPhoenix::GeometryGenerator::MeshData* mGrid;
//
//	//vector for color shaded boxes
//	std::vector<DPhoenix::PrimitiveInstance*> mColorBoxes;
//	std::vector<DPhoenix::PrimitiveInstance* >mColorSphere;
//	std::vector<DPhoenix::PrimitiveInstance*> mColorGrid;
//
//	//camera object
//	DPhoenix::Camera* mCamera;
//	DPhoenix::EAngle mCamEAngle;
//
//	//ambient color 
//	XMFLOAT4 mAmbientColor;
//	float mAmbIntensity;
//
//	//for fps scence-------------------------------
//	DPhoenix::PrimitiveInstance* mPlayer;	//player box for movment and collision
//	DPhoenix::PrimitiveInstance* mFloor;	//floor grid
//
//	void InitCollectables();				//initialise collectable objects
//	void InitScenery();						//initialise secenrey objects
//
//	//vectors to hold scenrey / collectables
//	std::vector<DPhoenix::PrimitiveInstance*> mCollectableBoxes;
//	std::vector<DPhoenix::PrimitiveInstance*> mSceneryBoxes;
//
//	//tracking int for collected objects
//	int mCollected;
//
//public:
//	FPSDemo(HINSTANCE hInstance);
//	~FPSDemo();
//
//	bool Init(bool fullScreen);
//	void OnResize();
//	void UpdateScene(float dt);
//	void DrawScene();
//
//	//new function; this builds our quad for the sprite
//	void BuildGeometryBuffers();
//
//	//new method / implements event handling
//	void FPSDemo::HandleEvents(DPhoenix::IEvent* e);
//
//	//new method / initialises sounds to be used in the app
//	void InitAudio();
//
//	//new method / specifically handles individual sprite rendering
//	void RenderSprite(DPhoenix::Sprite* sprite,
//		ID3DX11EffectTechnique* tech, bool isHUD = false);
//
//
//	//new method / specifically handle indiidual color primitives rendering
//	void RenderColorPrimitive(DPhoenix::PrimitiveInstance* model, ID3DX11EffectTechnique* tech);
//
//	//new / speicaffacly handles indidual texture primitives rendering
//	void FPSDemo::RenderBasicTexPrimitive(DPhoenix::PrimitiveInstance* model,
//		ID3DX11EffectTechnique * tech);
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
//	FPSDemo theApp(hInstance);
//
//	if (!theApp.Init(false))
//		return 0;
//
//	return theApp.Run();
//}
//
////constructor - don't really need to add much here
//FPSDemo::FPSDemo(HINSTANCE hInstance)
//	: Engine(hInstance)
//{
//	mMainWndCaption = "Texture Demo";
//
//	//create camera here to pervent
//	//issues with matri genrator
//	mCamera = new DPhoenix::Camera();
//
//}
//
////destructor (release any memory as necessary)
//FPSDemo::~FPSDemo()
//{
//	DPhoenix::Effects::DestroyAll();
//	DPhoenix::InputLayouts::DestroyAll();
//}
//
////intitialise objects that can be collected to test collision
////in pratice you often read from data and usea specfic class
//void FPSDemo::InitCollectables()
//{
//	//for each collectable box , we push back a ne wprimitve instance
//	//then we load a basic textured instance and update varioius primitives
//	mCollectableBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mCollectableBoxes.back()->LoadBasicTexInstance(md3dDevice, "Models\\bluetexture.jpg", mBox, &mTexMgr);
//	mCollectableBoxes.back()->mScale = XMFLOAT3(0.5f, 0.5f, 0.5f);			//half the standard box size
//	mCollectableBoxes.back()->mHalfSizes = XMFLOAT3(2.5f, 2.5f, 2.5f);		//5*5*5 size
//	mCollectableBoxes.back()->mPosition = XMFLOAT3(100.0f, 5.0f, 0.0f);		//up 5 on y so in air
//	mCollectableBoxes.back()->mPrevPosition = XMFLOAT3(100.0f, 5.0f, 0.0f);	// set previous at current init
//	mCollectableBoxes.back()->mCollidable = true;							// set as collidable
//	mCollectableBoxes.back()->mEntityType = DPhoenix::ENTITY_COLLECTABLE_MESH;	//set enity type
//	AddEntity(mCollectableBoxes.back());
//
//	//and more boxs 
//	mCollectableBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mCollectableBoxes.back()->LoadBasicTexInstance(md3dDevice, "Models\\bluetexture.jpg", mBox, &mTexMgr);
//	mCollectableBoxes.back()->mScale = XMFLOAT3(0.5f, 0.5f, 0.5f);			//half the standard box size
//	mCollectableBoxes.back()->mHalfSizes = XMFLOAT3(2.5f, 2.5f, 2.5f);		//5*5*5 size
//	mCollectableBoxes.back()->mPosition = XMFLOAT3(0.0f, 5.0f, 250.0f);		//up 5 on y so in air
//	mCollectableBoxes.back()->mPrevPosition = XMFLOAT3(0.0f, 5.0f, 250.0f);	// set previous at current init
//	mCollectableBoxes.back()->mCollidable = true;							// set as collidable
//	mCollectableBoxes.back()->mEntityType = DPhoenix::ENTITY_COLLECTABLE_MESH;	//set enity type
//	AddEntity(mCollectableBoxes.back());
//
//	mCollectableBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mCollectableBoxes.back()->LoadBasicTexInstance(md3dDevice, "Models\\bluetexture.jpg", mBox, &mTexMgr);
//	mCollectableBoxes.back()->mScale = XMFLOAT3(0.5f, 0.5f, 0.5f);			//half the standard box size
//	mCollectableBoxes.back()->mHalfSizes = XMFLOAT3(2.5f, 2.5f, 2.5f);		//5*5*5 size
//	mCollectableBoxes.back()->mPosition = XMFLOAT3(150.0f, 5.0f, -100.0f);		//up 5 on y so in air
//	mCollectableBoxes.back()->mPrevPosition = XMFLOAT3(150.0f, 5.0f, -100.0f);	// set previous at current init
//	mCollectableBoxes.back()->mCollidable = true;							// set as collidable
//	mCollectableBoxes.back()->mEntityType = DPhoenix::ENTITY_COLLECTABLE_MESH;	//set enity type
//	AddEntity(mCollectableBoxes.back());
//
//	mCollectableBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mCollectableBoxes.back()->LoadBasicTexInstance(md3dDevice, "Models\\bluetexture.jpg", mBox, &mTexMgr);
//	mCollectableBoxes.back()->mScale = XMFLOAT3(0.5f, 0.5f, 0.5f);			//half the standard box size
//	mCollectableBoxes.back()->mHalfSizes = XMFLOAT3(2.5f, 2.5f, 2.5f);		//5*5*5 size
//	mCollectableBoxes.back()->mPosition = XMFLOAT3(-200.0f, 5.0f, -200.0f);		//up 5 on y so in air
//	mCollectableBoxes.back()->mPrevPosition = XMFLOAT3(-200.0f, 5.0f, -200.0f);	// set previous at current init
//	mCollectableBoxes.back()->mCollidable = true;							// set as collidable
//	mCollectableBoxes.back()->mEntityType = DPhoenix::ENTITY_COLLECTABLE_MESH;	//set enity type
//	AddEntity(mCollectableBoxes.back());
//
//}
//
////intialise objects that can be bumbed into to test collision
////in pratice you often read from data and usea sepfic class
//void FPSDemo::InitScenery()
//{
//	//for eahc scenery box, wepush back a nre primtive instance
//	//then we laod a basic texture instance and update various propitse
//	mSceneryBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mSceneryBoxes.back()->LoadBasicTexInstance(md3dDevice, "Models\\metal.png", mBox, &mTexMgr);
//	mSceneryBoxes.back()->mScale = XMFLOAT3(2.0f, 2.0f, 2.0f);			//half the standard box size
//	mSceneryBoxes.back()->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);		//5*5*5 size
//	mSceneryBoxes.back()->mPosition = XMFLOAT3(50.0f, 10.0f, 0.0f);		//up 5 on y so in air
//	mSceneryBoxes.back()->mPrevPosition = XMFLOAT3(50.0f, 10.0f, 0.0f);	// set previous at current init
//	mSceneryBoxes.back()->mCollidable = true;							// set as collidable
//	mSceneryBoxes.back()->mEntityType = DPhoenix::ENTITY_SCENERY_MESH;	//set enity type
//	AddEntity(mSceneryBoxes.back());
//
//	//and more boxes
//	mSceneryBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mSceneryBoxes.back()->LoadBasicTexInstance(md3dDevice, "Models\\metal.png", mBox, &mTexMgr);
//	mSceneryBoxes.back()->mScale = XMFLOAT3(2.0f, 2.0f, 2.0f);			//half the standard box size
//	mSceneryBoxes.back()->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);		//5*5*5 size
//	mSceneryBoxes.back()->mPosition = XMFLOAT3(0.0f, 10.0f, 100.0f);		//up 5 on y so in air
//	mSceneryBoxes.back()->mPrevPosition = XMFLOAT3(0.0f, 10.0f, 100.0f);	// set previous at current init
//	mSceneryBoxes.back()->mCollidable = true;							// set as collidable
//	mSceneryBoxes.back()->mEntityType = DPhoenix::ENTITY_SCENERY_MESH;	//set enity type
//	AddEntity(mSceneryBoxes.back());
//
//	mSceneryBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mSceneryBoxes.back()->LoadBasicTexInstance(md3dDevice, "Models\\metal.png", mBox, &mTexMgr);
//	mSceneryBoxes.back()->mScale = XMFLOAT3(2.0f, 2.0f, 2.0f);			//half the standard box size
//	mSceneryBoxes.back()->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);		//5*5*5 size
//	mSceneryBoxes.back()->mPosition = XMFLOAT3(100.0f, 10.0f, -75.0f);		//up 5 on y so in air
//	mSceneryBoxes.back()->mPrevPosition = XMFLOAT3(100.0f, 10.0f, -75.0f);	// set previous at current init
//	mSceneryBoxes.back()->mCollidable = true;							// set as collidable
//	mSceneryBoxes.back()->mEntityType = DPhoenix::ENTITY_SCENERY_MESH;	//set enity type
//	AddEntity(mSceneryBoxes.back());
//
//	mSceneryBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mSceneryBoxes.back()->LoadBasicTexInstance(md3dDevice, "Models\\metal.png", mBox, &mTexMgr);
//	mSceneryBoxes.back()->mScale = XMFLOAT3(2.0f, 2.0f, 2.0f);			//half the standard box size
//	mSceneryBoxes.back()->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);		//5*5*5 size
//	mSceneryBoxes.back()->mPosition = XMFLOAT3(-100.0f, 10.0f, -100.0f);		//up 5 on y so in air
//	mSceneryBoxes.back()->mPrevPosition = XMFLOAT3(-100.0f, 10.0f, -100.0f);	// set previous at current init
//	mSceneryBoxes.back()->mCollidable = true;							// set as collidable
//	mSceneryBoxes.back()->mEntityType = DPhoenix::ENTITY_SCENERY_MESH;	//set enity type
//	AddEntity(mSceneryBoxes.back());
//}
//
////any additional initialisation (we generally initiaise game assets here)
//bool FPSDemo::Init(bool fullScreen)
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
//	//mGeoGen1 = new DPhoenix::GeometryGenerator();
//
//	//mGeoGen2 = new DPhoenix::GeometryGenerator();
//
//	mBox = new DPhoenix::GeometryGenerator::MeshData();
//	//mSphere = new DPhoenix::GeometryGenerator::MeshData();
//	//mGrid = new DPhoenix::GeometryGenerator::MeshData();
//
//	mGeoGen->CreateBox(10.0f, 10.0f, 10.0f, *mBox);
//
//	//right box 
//	mColorBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mColorBoxes.back()->LoadBasicTexInstance(md3dDevice, "Textures\\Boxes\\dpnew.jpg", mBox, &mTexMgr);
//	mColorBoxes.back()->mPosition.x = 50.0f;
//
//	//left box 
//	mColorBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mColorBoxes.back()->LoadBasicTexInstance(md3dDevice, "Textures\\Boxes\\dpnew.jpg", mBox, &mTexMgr);;
//	mColorBoxes.back()->mPosition.x = -50.0f;
//
//	//top box
//	mColorBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mColorBoxes.back()->LoadBasicTexInstance(md3dDevice, "Textures\\Boxes\\dpnew.jpg", mBox, &mTexMgr);
//	mColorBoxes.back()->mPosition.y = 50.0f;
//
//	//bottum box 
//	mColorBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mColorBoxes.back()->LoadBasicTexInstance(md3dDevice, "Textures\\Boxes\\dpnew.jpg", mBox, &mTexMgr);
//	mColorBoxes.back()->mPosition.y = -50.0f;
//
//	//forward box - 
//	mColorBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mColorBoxes.back()->LoadBasicTexInstance(md3dDevice, "Textures\\Boxes\\dpnew.jpg", mBox, &mTexMgr);
//	mColorBoxes.back()->mPosition.z = 50.0f;
//
//	//back box -
//	mColorBoxes.push_back(new DPhoenix::PrimitiveInstance());
//	mColorBoxes.back()->LoadBasicTexInstance(md3dDevice, "Textures\\Boxes\\dpnew.jpg", mBox, &mTexMgr);
//	mColorBoxes.back()->mPosition.z = -50.0f;
//	//amibent lighting values
//	mAmbientColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
//	mAmbIntensity = 1.0f;
//#pragma region SetupFPSScene
//
//	//create new primitive istnance to repsent player (to be render, but for collision etc)
//	mPlayer = new DPhoenix::PrimitiveInstance();
//	mPlayer->LoadColorInstance(md3dDevice, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), mBox);
//	mPlayer->mEntityType = DPhoenix::ENTITY_PLAYER_MESH;		//set as player type
//	mPlayer->mHalfSizes = XMFLOAT3(5.0f, 5.0f, 5.0f);			//10*10*10 collision box
//	mPlayer->mCollidable = true;								//set colidable
//	mPlayer->mPosition.y = 5.0f;								//init position
//	mCamera->mPosition.y = 5.0f;								//init position
//	AddEntity(mPlayer);											//add to engine
//
//	//create grid usin gemotrygen
//	mGrid = new DPhoenix::GeometryGenerator::MeshData();
//	mGeoGen->CreateGrid(500.0f, 500.0f, 10, 10, *mGrid);
//	//create floor pritmive istnace
//	mFloor = new DPhoenix::PrimitiveInstance();
//	mFloor->LoadBasicTexInstance(md3dDevice, "Models\\wood.png", mGrid, &mTexMgr);
//
//	//init scenery and collectables
//	InitScenery();
//	InitCollectables();
//	mCollected = 0;
//	
//	mPosition.x = 5.0f; mPosition.y = 5.0f; mPosition.z = 0.0f;
//
//	mVelocity.x = 0.0f; mVelocity.y = 0.0f; mVelocity.z = 0.0f;
//
//	//camera and Eangle initilasiotn (cam in constructor due to use in Onresize)
//	mCamEAngle.r = 0.0f; mCamEAngle.p = 0.0f; mCamEAngle.y = 0.0f;
//
//	//debug font
//	//(Arial size 20 sending window, initial brush, writefactory)
//	mDebugFont = new DPhoenix::Font(mhMainWnd, mBlackBrush, mDWriteFactory, "Arial", 20.0f);
//
//	return true;
//}
//
////what to do on resize - mainly we'lll just call the parent / engine's method
//void FPSDemo::OnResize()
//{
//	Engine::OnResize();
//
//	//the window resize so the aspect ratio needs
//	//to be calculated again, and the rpjectiob matrix
//	mCamera->SetPerspective(0.25f * XM_PI, AspectRatio(), 1.0f, 1000000.0f);
//}
//
////update scene - here is where our update logic for the game loop goes
//void FPSDemo::UpdateScene(float dt)
//{
//	//calculate scaling based on window dimensions
//	mScreenScale.x = (float)mClientWidth / 1440;
//	mScreenScale.y = (float)mClientHeight / 900;
//
//	//cmaera updating -get facing direction but no y compoment (hoz)
//	XMFLOAT3 facingDir = mCamEAngle.ToFloat3();
//	facingDir.y = 0.0f;
//	XMVECTOR facingVec = XMLoadFloat3(&facingDir);
//
//	//normailise the vector 9for direction) and store as xmfloat3
//	facingVec - XMVector3Normalize(facingVec);
//	XMStoreFloat3(&facingDir, facingVec);
//	//set the forward vector for the player and update velocity
//	//realtive mov,ent based on direction
//	mPlayer->mForwardVector = facingDir;
//	mPlayer->mRelativeVelocity = mVelocity;
//	mPlayer->Update(dt, true);
//	//update camera position to match player
//	mCamera->mPosition = mPlayer->mPosition;
//	mCamera->Update(mCamEAngle.ToFloat3());
//	
//	//loop through colectable boxes
//	for (int i = 0; i < mCollectableBoxes.size(); )
//	{
//		//if the box has collided add to collected
//		//set alive to flase for the engine updating and remove from vector
//		if (mCollectableBoxes[i]->mCollided)
//		{
//			mCollected++;
//			mCollectableBoxes[i]->mAlive = false;
//			mCollectableBoxes.erase(mCollectableBoxes.begin() + i);
//		}
//		else
//		{
//			i++;
//		}
//	}
//
//	
//
//	//reset velocity after each update as determined by input
//	mVelocity.x = 0.0f; mVelocity.y = 0.0f; mVelocity.z = 0.0f;
//}
//
//void FPSDemo::BuildGeometryBuffers()
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
//void FPSDemo::DrawScene()
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
//#pragma region RenderColorPrimitives
//
//	//set up the vertex input layout
//	//would need to change for diffrent type of renering
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosColor);
//
//	//here we will render th ebox using our new method
//	//we send the pointer to the instance and also the color renering tech
//	//(using color.fx)
//	/*for (int i = 0; i < mColorBoxes.size(); i++)
//	{
//		RenderColorPrimitive(mColorBoxes[i], activeColorTech);
//	}*/
//
//	//RenderColorPrimitive(mColorSphere, activeColorTech);
//	//RenderColorPrimitive(mColorGrid, activeColorTech);
//
//#pragma endregion RenderColorPrimitives
//#pragma region RenderBasicTexturePrimitives
//
//	//set up the vertex input layout
//	//would need to change for diffrent types of rendering
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::PosTex);
//
//	//here we will renfer the bos using out method
//	//we send th epointer to the instance and also the texture rendering technique
//	//using texture.fx
//	for (int i = 0; i < mColorBoxes.size(); i++)
//	{
//		RenderBasicTexPrimitive(mColorBoxes[i], activeBasicTexTech);
//	}
//	//redner floor
//	RenderBasicTexPrimitive(mFloor, activeBasicTexTech);
//	//redner scenery
//	for (int i = 0; i < mSceneryBoxes.size(); i++)
//	{
//		RenderBasicTexPrimitive(mSceneryBoxes[i], activeBasicTexTech);
//	}
//	//redner collectables
//	for (int i = 0; i < mCollectableBoxes.size(); i++)
//	{
//		RenderBasicTexPrimitive(mCollectableBoxes[i], activeBasicTexTech);
//	}
//
//#pragma endregion RenderBasicTexturePrimitives
//#pragma region RenderSprites
//
//	//to render sprites we need to disable depth testing (so it layers on top of each other)
//	//like a collage
//	md3dImmediateContext->IASetInputLayout(DPhoenix::InputLayouts::SpritePosTex);
//
//	//to render sprites we need to disbale depth testing (so it layers on tope of each other)
//
//	md3dImmediateContext->OMSetDepthStencilState(mDepthDisabledStencilState, 1);
//
//	//turn depth stencil back on for 3D rendering
//	md3dImmediateContext->OMSetDepthStencilState(mDepthStencilState, 1);
//
//#pragma endregion RenderSprites
//
//#pragma region RenderFonts
//
//	//string stream object for getting all text to display
//	std::ostringstream debugText;
//
//	debugText << "Debug text:" << std::endl;
//	
//	debugText << "Collected:" << mCollected << std::endl;
//	debugText << "Camera Pos x: " << mCamera->mPosition.x <<
//		" | y: " << mCamera->mPosition.y <<
//		" | Z: " << mCamera->mPosition.z << std::endl;
//	debugText << " Camera lookAt x: " << mCamera->mTarget.x <<
//		" | y: " << mCamera->mTarget.y <<
//		" | Z: " << mCamera->mTarget.z << std::endl;
//
//
//
//	//calculate screen scaling
//	float scaleX = (float)mClientWidth / 1440;
//	float scaleY = (float)mClientHeight / 900;
//
//	//call draw font method sending all key info
//	mDebugFont->DrawFont(m2D1RT, debugText.str(), 10.0f, 500.0f,
//		1.0f, 1.0f, D2D1::ColorF(0xFFFFFF, 0.5f));
//
//#pragma endregion RenderFonts
//
//	//present to screen
//	HR(mSwapChain->Present(0, 0));
//
//}
//
//void FPSDemo::HandleEvents(DPhoenix::IEvent* e)
//{
//	switch (e->GetID())
//	{
//	case DPhoenix::EVENT_KEYPRESS:
//	{
//		DPhoenix::KeyPressEvent* kpe = (DPhoenix::KeyPressEvent*)e;
//		switch (kpe->mKeycode)
//		{
//		case DIK_D:
//			mVelocity.x = 100.0f;
//
//			break;
//
//		case DIK_A:
//			mVelocity.x = -100.0f;
//
//			break;
//		case DIK_W:
//			mVelocity.z = 100.0f;
//
//			break;
//		case DIK_S:
//			mVelocity.z = -100.0f;
//
//			break;
//		case DIK_Q:
//			mVelocity.y = -100.0f;
//			break;
//		case DIK_E:
//			mVelocity.y = 100.0f;
//			break;
//		case DIK_ESCAPE:
//			//shutdown here
//			break;
//		}
//	}
//	break;
//
//	case DPhoenix::EVENT_MOUSEMOTION:
//	{
//		DPhoenix::MouseMotionEvent* mme = (DPhoenix::MouseMotionEvent*)e;
//		float movex = mme->mDeltaX;		//difference in hozrnitel movment
//		float movey = mme->mDeltaY;		//difference in verticle movement
//
//		//set euler angles for camera direction
//		mCamEAngle.y -= movex * 0.0075;
//		mCamEAngle.p -= movey * 0.0075;
//
//		//set restrictions on target movement
//		//directly up / down
//
//		if (mCamEAngle.p >= 1.565)
//			mCamEAngle.p = 1.565;
//		if (mCamEAngle.p <= -1.565)
//			mCamEAngle.p = -1.565;
//
//		mCamEAngle.Normalize();
//	}
//	break;
//	case DPhoenix::EVENT_XBOX_INPUT:
//	{
//		DPhoenix::XBoxEvent* xbe = (DPhoenix::XBoxEvent*)e;
//		if (xbe->mPadState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
//		{
//			mVelocity.x = -500.0f;
//
//		}
//		if (xbe->mPadState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
//		{
//			mVelocity.x = 500.0f;
//
//		}
//		if (xbe->mPadState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
//		{
//			mVelocity.y = 500.0f;
//		}
//		if (xbe->mPadState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
//		{
//			mVelocity.y = -500.0f;
//		}
//		//audio buttons
//		if (xbe->mPadState.Gamepad.wButtons & XINPUT_GAMEPAD_A)
//		{
//			if (!mAudioMgr.GetSound("IgnoranceTitle")->IsPlaying())
//			{
//				mAudioMgr.GetSound("IgnoranceTitle")->Play(true);
//			}
//
//		}
//		if (xbe->mPadState.Gamepad.wButtons & XINPUT_GAMEPAD_B)
//		{
//			if (!mAudioMgr.GetSound("LaserShootFX")->IsPlaying())
//			{
//				mAudioMgr.GetSound("LaserShootFX")->Play(false);
//			}
//			else
//			{
//				mAudioMgr.GetSound("LaserShootFX")->Stop();
//			}
//		}
//		if (xbe->mPadState.Gamepad.wButtons & XINPUT_GAMEPAD_X)
//		{
//			if (!mAudioMgr.GetSound("FlatBelieveClip")->IsPlaying())
//			{
//				mAudioMgr.GetSound("FlatBelieveClip")->Play(false);
//			}
//			else
//			{
//				mAudioMgr.GetSound("FlatBelieveClip")->Stop();
//			}
//		}
//		if (xbe->mPadState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
//		{
//			mAudioMgr.ResetAllSounds();
//		}
//	}
//	break;
//	}
//}
//
//void FPSDemo::InitAudio()
//{
//	mAudioMgr.CreateSound("IgnoranceTitle", "Audio\\Music\\IgnoranceTitle.wav");
//	mAudioMgr.CreateSound("LaserShootFX", "Audio\\FX\\LaserShootFX.wav");
//	mAudioMgr.CreateSound("FlatBelieveClip", "Audio\\Voice\\FlatBelieveClip.wav");
//
//}
//
//void FPSDemo::RenderSprite(DPhoenix::Sprite * sprite, ID3DX11EffectTechnique * tech, bool isHUD)
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
//	XMMATRIX viewProj;
//
//	//HUD objects not affected by cameras
//	if (!isHUD)
//	{
//		//here you would add any 2D camera control
//
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
//void FPSDemo::RenderColorPrimitive(DPhoenix::PrimitiveInstance * model, ID3DX11EffectTechnique * tech)
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
//
//	//concatenate world view / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//	//XMMatrix world = indeinty;
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::ColorFX->SetWorldViewProj(worldViewProj);
//
//	//render using effect shader tech
//
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
//
//
//}
//
//void FPSDemo::RenderBasicTexPrimitive(DPhoenix::PrimitiveInstance * model, ID3DX11EffectTechnique * tech)
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
//
//	//concatenate world view / view / projection matrices for rendering
//	XMMATRIX world = model->CalculateTransforms();
//	//XMMatrix world = indeinty;
//	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
//	DPhoenix::Effects::BasicTexFX->SetWorldViewProj(worldViewProj);
//	DPhoenix::Effects::BasicTexFX->SetAmbLight(XMLoadFloat4(&mAmbientColor));
//	DPhoenix::Effects::BasicTexFX->SetAmbIntensity(mAmbIntensity);
//	DPhoenix::Effects::BasicTexFX->SetDiffuseMap(model->mDiffuseMap);
//	DPhoenix::Effects::BasicTexFX->SetTexScaleU(model->mTexScaleU);
//	DPhoenix::Effects::BasicTexFX->SetTexScaleV(model->mTexScaleV);
//
//	//render using effect shader tech
//
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