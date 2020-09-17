#include "Beacon.h"

DPhoenix::Beacon::Beacon(XMFLOAT3 position, TextureMgr* texMgr, ID3D11Device* d3dDevice,
	GeometryGenerator::MeshData* sphere, GeometryGenerator::MeshData* pole)
{
	//set singeltions
	mTexMgr = texMgr;
	md3dDevice = d3dDevice;
	//state and initialisation
	mBeaconState = BEACON_UNLIT;
	mIsGrowing = true;
	mRadianceRange = 80.0f;
	//shiny matrial
	Material* materialShiny = new Material();
	materialShiny->Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	materialShiny->Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	materialShiny->Specular = XMFLOAT4(1.0, 1.0f, 1.0f, 1.0f);
	materialShiny->Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	//texture creation for the poles
	mPoleUnlitDiffuseMap = texMgr->CreateTexture("Textures\\Beacons\\Beacon_cm.jpg");
	mPolePlayerLitDiffuseMap = texMgr->CreateTexture("Textures\\Beacons\\Beacon_cm.jpg");
	mPoleEnemyLitDiffuseMap = texMgr->CreateTexture("Textures\\Beacons\\Beacon_cm.jpg");

	mCurrentPoleNormalMap = texMgr->CreateTexture("Textures\\Beacons\\Beacon_nm.jpg");

	//beacon sphere textures
	mBeaconUnlitDiffuseMap = texMgr->CreateTexture("Textures\\Beacons\\BeaconLightUnlit_cm.png");
	mBeaconPlayerLitDiffuseMap = texMgr->CreateTexture("Textures\\Beacons\\BeaconLightPlayerLit_cm.png");
	mBeaconEnemyLitDiffuseMap = texMgr->CreateTexture("Textures\\Beacons\\BeaconLightEnemyLit_cm.png");

	mCurrentPlayerBeaconNormalMap = texMgr->CreateTexture("Textures\\Beacons\\BeaconLightPlayerLit_nm.png");
	mCurrentEnemyBeaconNormalMap = texMgr->CreateTexture("Textures\\Beacons\\BeaconLightEnemyLit_nm.png");
	

	//pole dimensions and position come in the construct
	mPoleMeshInstance = new PrimitiveInstance();
	mPoleMeshInstance->LoadLitTexInstance(md3dDevice, "Textures\\Beacons\\Beacon_cm.jpg", pole, mTexMgr);
	mPoleMeshInstance->mMaterial = materialShiny;
	mPoleMeshInstance->mNormalMap = mTexMgr->CreateTexture("Textures\\Beacons\\Beacon_nm.jpg");
	mPoleMeshInstance->mPosition = position; mPoleMeshInstance->mPrevPosition = position;
	mPoleMeshInstance->mHalfSizes = XMFLOAT3(5.0f, 20.0f, 5.0f);
	mPoleMeshInstance->mEntityType = ENTITY_BEACON_MESH;
	mPoleMeshInstance->mCollidable = true;

	//for the beacon sphere
	mBeaconMeshInstance = new PrimitiveInstance();
	mBeaconMeshInstance->LoadLitTexInstance(md3dDevice, "Textures\\Beacons\\BeaconLightUnlit_cm.png", sphere, mTexMgr);
	mBeaconMeshInstance->mMaterial = materialShiny;
	mBeaconMeshInstance->mNormalMap = mTexMgr->CreateTexture("Textures\\Beacons\\BeaconLight_nm.png");
	mBeaconMeshInstance->mPosition = position; mBeaconMeshInstance->mPrevPosition = position;
	mBeaconMeshInstance->mPosition = position;
	mBeaconMeshInstance->mPosition.y = 45.0f;


}

DPhoenix::Beacon::~Beacon()
{

}

void DPhoenix::Beacon::Update(float dt)
{
	//if we are lit
	if (mBeaconState != BEACON_UNLIT)
	{
		//if light is growing
		if (mIsGrowing)
		{
			//increase range
			mRadianceRange += 20.0f * dt;

			//bound range and unsetgrowing flag
			if (mRadianceRange >= 150.0f)
			{
				mRadianceRange = 150.0f;
				mIsGrowing = false;
			}
		}
		else
		{
			//decrease the range
			mRadianceRange -= 20.0f * dt;

			//bound range and set growing flag
			if (mRadianceRange <= 20.0f)
			{
				mRadianceRange = 20.0f;
				mIsGrowing = true;
			}
		}

		//assign the radiance range for the shader
		mRadiance->Range = mRadianceRange;
	}
}

void DPhoenix::Beacon::LightBeacon(bool isPlayer)
{
	//create a new point light to radiate the ;it beacon
	mRadiance = new PointLight();

	//specular and attenuation constant
	mRadiance->Ambient = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
	mRadiance->Att = XMFLOAT3(1.0f, 0.1f, 0.02f);
	//set the range and pos
	mRadiance->Range = mRadianceRange;
	mRadiance->Position = mBeaconMeshInstance->mPosition;

	//player or enemy diffrent light for each
	//alos pdate the pole and sphere textures
	if (isPlayer)
	{
		mRadiance->Diffuse = XMFLOAT4(0.5, 1.0f, 0.5, 1.0f);
		mRadiance->Specular = XMFLOAT4(0.5f, 1.0f, 0.5f, 1.0f);
		mPoleMeshInstance->mDiffuseMap = mPolePlayerLitDiffuseMap;
		mBeaconMeshInstance->mDiffuseMap = mBeaconPlayerLitDiffuseMap;
		mBeaconMeshInstance->mNormalMap = mCurrentPlayerBeaconNormalMap;
		mBeaconState = BEACON_PLAYER_LIT;
	}
	else
	{
		mRadiance->Diffuse = XMFLOAT4(1.0f, 0.5f, 0.5, 1.0f);
		mRadiance->Specular = XMFLOAT4(1.0f, 0.5f, 0.5f, 1.0f);
		mPoleMeshInstance->mDiffuseMap = mPoleEnemyLitDiffuseMap;
		mBeaconMeshInstance->mDiffuseMap = mBeaconEnemyLitDiffuseMap;
		mBeaconMeshInstance->mNormalMap = mCurrentEnemyBeaconNormalMap;
		mBeaconState = BEACON_ENEMY_LIT;
	}
		
}