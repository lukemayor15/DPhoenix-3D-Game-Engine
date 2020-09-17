#include "MapBlock.h"

DPhoenix::MapBlock::MapBlock(MapBlockTypes _blockType, TextureMgr * _texMgr,
	ID3D11Device * _md3dDevice, DPhoenix::GeometryGenerator::MeshData* _Box,
	std::vector<std::string>& _floorColorMaps, std::vector<std::string>& _floorNormalMaps,
	std::vector<std::string>& _strongWindColorMaps, std::vector<std::string>& _strongWindNormalMaps,
	std::vector<std::string>& _healColorMaps, std::vector<std::string>& _healNormalMaps,
	std::vector<std::string>& _baseColorMaps, std::vector<std::string>& _baseNormalMaps,
	std::vector<std::string>& _wallColorMaps, std::vector<std::string>& _wallNormalMaps,
	std::vector<std::string>& _coverColorMaps, std::vector<std::string>& _coverNormalMaps,
	int _arrayXPos, int _arrayYPos, float _tileSize, SpecialFlags _spFlag)
{
	mSpecialFlag = _spFlag;

	mMapBlockType = _blockType;
	mArrayXPos = _arrayXPos;
	mArrayYPos = _arrayYPos;

	mPosition.x = mArrayXPos * _tileSize;
	mPosition.z = mArrayYPos * _tileSize;
	mPosition.y = 0.0f;

	//different material types for effects
	Material* materialStandard = new Material();
	Material* materialShiny = new Material();

	materialStandard->Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	materialStandard->Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	materialStandard->Specular = XMFLOAT4(0.5f, 0.5f, 0.5f, 2.0f);
	materialStandard->Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	materialShiny->Ambient = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	materialShiny->Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	materialShiny->Specular = XMFLOAT4(1.0f, 1.0f, 1.0f, 16.0f);
	materialShiny->Reflect = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

	int index = 0;

	switch (mMapBlockType)
	{
	case FLOOR_MAPBLOCK:
		index = rand() % (_floorColorMaps.size());

		mMeshInstance = new PrimitiveInstance();
		mMeshInstance->LoadLitTexInstance(_md3dDevice, _floorColorMaps[index], _Box, _texMgr);
		mMeshInstance->mMaterial = materialStandard;
		mMeshInstance->mNormalMap = _texMgr->CreateTexture(_floorNormalMaps[index]);

		mPosition.y = 0.0f;
		//Enitiy seting for collision
		mMeshInstance->mPosition = mPosition;
		mMeshInstance->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);
		break;
	case STRONGWIND_MAPBLOCK:
		index = rand() % (_strongWindColorMaps.size());

		mMeshInstance = new PrimitiveInstance();
		mMeshInstance->LoadLitTexInstance(_md3dDevice, _strongWindColorMaps[index], _Box, _texMgr);
		mMeshInstance->mMaterial = materialStandard;
		mMeshInstance->mNormalMap = _texMgr->CreateTexture(_strongWindNormalMaps[index]);

		mPosition.y = 0.0f;
		//Enitiy seting for collision
		mMeshInstance->mPosition = mPosition;
		mMeshInstance->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);

		break;
	case BASE_MAPBLOCK:
		index = rand() % (_baseColorMaps.size());

		mMeshInstance = new PrimitiveInstance();
		mMeshInstance->LoadLitTexInstance(_md3dDevice, _baseColorMaps[index], _Box, _texMgr);
		mMeshInstance->mMaterial = materialStandard;
		mMeshInstance->mNormalMap = _texMgr->CreateTexture(_baseNormalMaps[index]);

		mPosition.y = 0.0f;
		//Enitiy seting for collision
		mMeshInstance->mPosition = mPosition;
		mMeshInstance->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);

		break;
	case HEAL_MAPBLOCK:
		index = rand() % (_healColorMaps.size());

		mMeshInstance = new PrimitiveInstance();
		mMeshInstance->LoadLitTexInstance(_md3dDevice, _healColorMaps[index], _Box, _texMgr);
		mMeshInstance->mMaterial = materialStandard;
		mMeshInstance->mNormalMap = _texMgr->CreateTexture(_healNormalMaps[index]);

		mPosition.y = 0.0f;
		//Enitiy seting for collision
		mMeshInstance->mPosition = mPosition;
		mMeshInstance->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);

		break;
	case WALL_MAPBLOCK:

		index = rand() % (_wallColorMaps.size());

		mMeshInstance = new PrimitiveInstance();
		mMeshInstance->LoadLitTexInstance(_md3dDevice, _wallColorMaps[index], _Box, _texMgr);
		mMeshInstance->mMaterial = materialStandard;
		mMeshInstance->mNormalMap = _texMgr->CreateTexture(_wallNormalMaps[index]);

		mPosition.y = _tileSize;

		mMeshInstance->mPosition = mPosition;
		mMeshInstance->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);

		//Enitiy setting for collision

		break;
	case COVER_MAPBLOCK:
		index = rand() % (_coverColorMaps.size());

		mMeshInstance = new PrimitiveInstance();
		mMeshInstance->LoadLitTexInstance(_md3dDevice, _coverColorMaps[index], _Box, _texMgr);
		mMeshInstance->mMaterial = materialStandard;
		mMeshInstance->mNormalMap = _texMgr->CreateTexture(_coverNormalMaps[index]);

		mPosition.y = _tileSize / 2;

		mMeshInstance->mPosition = mPosition;
		mMeshInstance->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);

		//Entity setting for collision
		break;
	case BEACON_MAPBLOCK:

		//same as floor but will have beacons on top -  seprate in case other settinbg applied in future

		index = rand() % (_floorColorMaps.size());

		mMeshInstance = new PrimitiveInstance();
		mMeshInstance->LoadLitTexInstance(_md3dDevice, _floorColorMaps[index], _Box, _texMgr);
		mMeshInstance->mMaterial = materialStandard;
		mMeshInstance->mNormalMap = _texMgr->CreateTexture(_floorNormalMaps[index]);

		mPosition.y = 0.0f;

		mMeshInstance->mPosition = mPosition;
		mMeshInstance->mHalfSizes = XMFLOAT3(10.0f, 10.0f, 10.0f);
		break;
	case NULLSPACE_MAPBLOCK:
		mMeshInstance = NULL;
		break;
	}

	
}

DPhoenix::MapBlock::~MapBlock()
{

}

//hardcoded 20.0f as that the block size (height / width)
