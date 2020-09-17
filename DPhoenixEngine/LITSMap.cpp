#include "LITSMap.h"

DPhoenix::LITSMap::LITSMap(std::string filename, TextureMgr* mTexMgr, ID3D11Device* md3dDevice,
	std::vector<XMFLOAT3>& enemySpawnVec,
	std::vector<XMFLOAT3>& playerSpawnVec,
	std::vector<XMFLOAT3>& beaconSpawnVec,
	DPhoenix::GeometryGenerator::MeshData* _Box,
	std::vector<std::string>& _floorColorMaps, std::vector<std::string>& _floorNormalMaps,
	std::vector<std::string>& _strongWindColorMaps, std::vector<std::string>& _strongWindNormalMaps,
	std::vector<std::string>& _healColorMaps, std::vector<std::string>& _healNormalMaps,
	std::vector<std::string>& _baseColorMaps, std::vector<std::string>& _baseNormalMaps,
	std::vector<std::string>& _wallColorMaps, std::vector<std::string>& _wallNormalMaps,
	std::vector<std::string>& _coverColorMaps, std::vector<std::string>& _coverNormalMaps,
	int tilesWidth, int tilesLength,
	float tileSize)
{
	//get from csvv file and populate 2D vector
	std::ifstream inMapFile(filename);

	//helpers for parsiong CSV file
	std::string value;
	std::string ignore;
	//calualte the width and height in titles
	mWidth = tilesWidth;
	mLength = tilesLength;
	//size of tiles assume square

	//values used in constructing map
	int row = mLength - 1; // counting backwards beacuse it stacks tiles
	int col = 0;
	int count = 0;

	//set the vecot values based on our tile size
	//(build 2d array)
	mTiles.resize(mWidth);
	for (int i = 0; i < mTiles.size(); i++)
	{
		mTiles[i].resize(mLength);
	}
	XMFLOAT3 objectPos;		// used to set spawn positions

	//size to 4 each as per design - cpuld be define with spearate const vars
	playerSpawnVec.resize(4);
	enemySpawnVec.resize(4);
	

	//map parsing: starting at the top row and doing by column
	//after each row has the colum filled, deceremnt 
	//and repeat actions - builds map array as it appers in teh speadsheet

	//seed once
	srand(time(0));

	//read in map file and coutine while open
	while (inMapFile.good())
	{
		//get line until next comma - store in value
		std::getline(inMapFile, value, '\n');

		//if we have an actual line
		if (value.length() > 1)
		{
			//loop though the cahrs in the value given
			for (int i = 0; i < value.length(); i++)
			{
				//we be using the portion of the asci table
				//which doesnt include commas or ifle header weirdness
				//hence we can checj we can chech we are between these vales
				int indexStart = (int)'0';
				int indexEnd = (int)'z';
				//if the char avalue is widith the ascii table values set
				if ((int)value[i] >= indexStart && int(value[i] <= indexEnd))
				{
					//check what the value is for this tile
					switch (value[i])
					{
					case '0':
						mTiles[col][row] = new MapBlock(DPhoenix::NULLSPACE_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);
						break;
					case 'e':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);
						break;
					case 'd':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);
						//graveyard block no need renaming caused more work creating a new block.
						break;
					case 'H':
						mTiles[col][row] = new MapBlock(DPhoenix::HEAL_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);
						break;
					case 'B':
						mTiles[col][row] = new MapBlock(DPhoenix::BASE_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);
						break;
					case 's':
						mTiles[col][row] = new MapBlock(DPhoenix::STRONGWIND_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);
						break;
					case 'g':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);
						break;
					case 'c':
						mTiles[col][row] = new MapBlock(DPhoenix::COVER_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);

						
						break;
					case 'w':
						mTiles[col][row] = new MapBlock(DPhoenix::WALL_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);
						

						break;
					case 'p':
						mTiles[col][row] = new MapBlock(DPhoenix::BEACON_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::NO_SP_FLAG);

							beaconSpawnVec.push_back(XMFLOAT3(col * tileSize, tileSize / 2 + 5.0f, row * tileSize));
						break;

					case '1':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::PLAYER_SP_FLAG);
						playerSpawnVec[0] = XMFLOAT3(col * tileSize, tileSize / 2, row * tileSize);

						break;
					case '2':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::PLAYER_SP_FLAG);
						playerSpawnVec[1] = XMFLOAT3(col * tileSize, tileSize / 2, row * tileSize);

						break;
					case '3':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::PLAYER_SP_FLAG);
						playerSpawnVec[2] = XMFLOAT3(col * tileSize, tileSize / 2, row * tileSize);

						break;
					case '4':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::PLAYER_SP_FLAG);
						playerSpawnVec[3] = XMFLOAT3(col * tileSize, tileSize / 2, row * tileSize);

						break;
					case '9':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::ENEMY_SP_FLAG);
						enemySpawnVec[0] = XMFLOAT3(col * tileSize, tileSize / 2, row * tileSize);
						break;
					case '8':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::ENEMY_SP_FLAG);
						enemySpawnVec[1] = XMFLOAT3(col * tileSize, tileSize / 2, row * tileSize);
						break;
					case '7':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::ENEMY_SP_FLAG);
						enemySpawnVec[2] = XMFLOAT3(col * tileSize, tileSize / 2, row * tileSize);
						break;
					case '6':
						mTiles[col][row] = new MapBlock(DPhoenix::FLOOR_MAPBLOCK,
							mTexMgr, md3dDevice, _Box,
							_floorColorMaps, _floorNormalMaps,
							_strongWindColorMaps, _strongWindNormalMaps,
							_healColorMaps, _healNormalMaps,
							_baseColorMaps, _baseNormalMaps,
							_wallColorMaps, _wallNormalMaps,
							_coverColorMaps, _coverNormalMaps,
							col, row, tileSize, DPhoenix::ENEMY_SP_FLAG);
						enemySpawnVec[3] = XMFLOAT3(col * tileSize, tileSize / 2, row * tileSize);
						break;
					}
					col++;
				}
			}
			row--; col = 0;
		}

	}
}

//hardcoded 20.0f as that the block size
int DPhoenix::LITSMap::GetColFromPosition(XMFLOAT3 _pos)
{
	//this rounds to the correct tile
	float x = round(_pos.x / 20.0f);

	//-1 means invaild / out of bounds
	if (x < 0 || x > mWidth)
		return -1;
	else
		return x;
}


//hardcoded 20.0f as that the block size
int DPhoenix::LITSMap::GetRowFromPosition(XMFLOAT3 _pos)
{
	//this rounds to the correct tile
	float z = round(_pos.z / 20.0f);

	//-1 means invaild / out of bounds
	if (z < 0 || z > mLength)
		return -1;
	else
		return z;
}

//gicewn the col and row whit is the pos above the block
//highlighting blocks
XMFLOAT3 DPhoenix::LITSMap::GetPositionABoveFromMapRef(int col, int row)
{
	XMFLOAT3 position;
	
	position.x = col * 20.0f;
	position.y = 10.5f;

	//based on the block type, well adjust the height
	if (mTiles[col][row]->mMapBlockType == FLOOR_MAPBLOCK ||
		mTiles[col][row]->mMapBlockType == BEACON_MAPBLOCK ||
		mTiles[col][row]->mMapBlockType == HEAL_MAPBLOCK||
		mTiles[col][row]->mMapBlockType == BASE_MAPBLOCK ||
		mTiles[col][row]->mMapBlockType == STRONGWIND_MAPBLOCK 
		)
		position.y = 10.5f;

	if (mTiles[col][row]->mMapBlockType == COVER_MAPBLOCK)
		position.y = 20.5f;

	if (mTiles[col][row]->mMapBlockType == WALL_MAPBLOCK)
		position.y = 30.5f;

	position.z = row * 20.0f;
	return position;
}



