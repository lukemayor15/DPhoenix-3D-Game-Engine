#pragma once
#include "MapBlock.h"

namespace DPhoenix
{
	class LITSMap
	{
	public:

		//using vector as ppose to arrays
		// simply so they can be dynamically resize without 
		//restoring to gobals 
		std::vector<std::vector<MapBlock*>> mTiles;

		//width and length ion tiles
		int mWidth;
		int mLength;

		//constrcutors - takes in map data filename, texture maganer, d3d dveice
		//and amount of tiles per pane; and amount of panels
		//as well as XMFLOAT3 origin points for spawn locations
		LITSMap(std::string filename, TextureMgr* mTexMgr, ID3D11Device* md3dDevice,
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
			float tileSize);
		~LITSMap() { };

		// array ciner methods for selctions / paths
		int GetColFromPosition(XMFLOAT3 _pos);
		int GetRowFromPosition(XMFLOAT3 _pos);
		XMFLOAT3 GetPositionABoveFromMapRef(int col, int row);
	};
}
