#pragma once
#include "D3DUtil.h"

namespace DPhoenix
{
	class MeshGeometry
	{
	public:
		//tihs is to mange propertise for each subset
		//these are parts of a mesh that are render with diffrent
		//material props
		struct Subset
		{
			Subset() :
				Id(-1),
				VertexStart(0), VertexCount(0),
				FaceStart(0), FaceCount(0)
			{
			}

		UINT Id;			//WHICH subset from the model
		UINT VertexStart;	// from which vertex does the subset start
		UINT VertexCount;	//how many vertices in this subset
		UINT FaceStart;		// from which face does subset start
		UINT FaceCount;		// how mnay faces in this subet
		UINT materialIndex;	// what material applies to the subset
			};

		public:
			//constructor and deconstructor
			MeshGeometry();
			~MeshGeometry();

			//template fucntion for crating vertex buffewr using nay vertex type
			template <typename VertexType>
			void SetVertices(ID3D11Device* device, const VertexType* vertices, UINT count);
			//function for creating index buffer
			void SetIndices(ID3D11Device* device, const USHORT* indices, UINT count);
			//set vector for each subset of a mesh
			void SetSubsetTable(std::vector<Subset>& subsetTable);
			//draw the mesh by each subset
			void Draw(ID3D11DeviceContext* dc, UINT subsetId);

		private:
			//copy constructors
			MeshGeometry(const MeshGeometry& rhs);
			MeshGeometry& operator=(const MeshGeometry& rhs);

		private:
			//vertex / index buffers
			ID3D11Buffer* mVB;
			ID3D11Buffer* mIB;

			DXGI_FORMAT mIndexBufferFormat;	//alawys 16 bit
			UINT mVertexStride;				//size of each data print

			//vector for each subset of a mesh
			std::vector<Subset> mSubsetTable;
		};

		//template function is defined here to prevent odd namespace issues
		template<typename VertexType>
		void MeshGeometry::SetVertices(ID3D11Device* device, const VertexType* vertices, UINT count)
		{
			//release vertex buffer
			ReleaseCOM(mVB);
			//calulate the vertex stide based on vertex type
			mVertexStride = sizeof(VertexType);
			//vertex buffer desc struct
			D3D11_BUFFER_DESC vbd;
			vbd.Usage = D3D11_USAGE_IMMUTABLE;
			vbd.ByteWidth = sizeof(VertexType) * count;
			vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vbd.CPUAccessFlags = 0;
			vbd.MiscFlags = 0;
			vbd.StructureByteStride = 0;
			//assign veteices and create buffer
			D3D11_SUBRESOURCE_DATA vinitData;
			vinitData.pSysMem = vertices;
			HR(device->CreateBuffer(&vbd, &vinitData, &mVB));

		}
	}