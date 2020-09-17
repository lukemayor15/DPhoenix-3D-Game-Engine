#pragma once

#include "D3DUtil.h"

namespace DPhoenix
{

	enum PrimitiveTypes
	{
		PRIMITIVE_COLOR,
		PRIMITIVE_TEX,
		PRIMITIVE_LITTEX
	};

	class PrimitiveInstance : public Entity
	{
	private:
		GeometryGenerator::MeshData* mMeshPtr;

		//vertex and index buffers for the quad / sprites
		ID3D11Buffer* mPrimitiveVB;
		ID3D11Buffer* mPrimitiveIB;
		//primtive type relationg to input layout for rendering
		PrimitiveTypes mPrimitiveType;

	public:
		


		//texture map /color map . diffuse map
		ID3D11ShaderResourceView* mDiffuseMap;
		Material* mMaterial;	//materail to react with light

		//normal map
		ID3D11ShaderResourceView* mNormalMap;
		
		//bvalues for texture scaling
		float mTexScaleU; float mTexScaleV;
		//constrcutor	/ destructor
		PrimitiveInstance();
		~PrimitiveInstance();

		//heance we will update the instances movment
		//we will experiment with moving relatively around the forward vector
		//at some point layer on
		void Update(float deltaTime, bool moveRelative);

		//this is to load instance of a mesh using only position and color data
		//we get a pointer to the mesh data from geometryGenrator , a dfefied color
		//r,g,b,a and also the device to create the buffers
		void LoadColorInstance(ID3D11Device* md3dDevice, XMFLOAT4 color, GeometryGenerator::MeshData* meshPtr);

		//tihs is to load an isntace of a mesh using only postion an duv data
		//we get apointer to the mesh data from gemoatrygen, a texture and file name
		//the device to create the buffers and a pointer to the texture manger
		void LoadBasicTexInstance(ID3D11Device* md3dDevice, std::string texFilename,
			GeometryGenerator::MeshData* meshPtr, TextureMgr* texMgr);

		//this genrates the world matrix based onscale
		//tranaslation (movment and roitatiob for rendering
		XMMATRIX CalculateTransforms();

		//this render the idnivdal instance tro the device context
		void Render(ID3D11DeviceContext* dc);

		//this is to load an instance of a mesh suig full data
		//this doesnt inlcude a normal map (coming soon) but includes a material to react with light
		//we get a point to the esh data form gemoometrygenrator , a texture filename
		//the device to create the bufferes amd apointer to the texture mangaer
		void LoadLitTexInstance(ID3D11Device* md3dDevice, std::string texFilename, GeometryGenerator::MeshData* meshPtr, TextureMgr* texMgr);

		//faces the forward vector
		void SetFacingRotation(float offsetDeg);
	};
}