#include "D3DUtil.h"

DPhoenix::MeshGeometry::MeshGeometry()
: mVB(0), mIB(0),
mIndexBufferFormat(DXGI_FORMAT_R16_UINT),
mVertexStride(0)

{
}

//release memory
DPhoenix::MeshGeometry::~MeshGeometry()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
}

//construct for index buffer
void DPhoenix::MeshGeometry::SetIndices(ID3D11Device* device,
	const USHORT* indices, UINT count)
{


	//indexbuffer desc struct
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(USHORT) * count;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	//assign veteices and create buffer
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = indices;

	HR(device->CreateBuffer(&ibd, &iinitData, &mIB));
}

//set subtable of sub meshes
void DPhoenix::MeshGeometry::SetSubsetTable(std::vector<Subset>& subsetTable)
{
	mSubsetTable = subsetTable;
}

//draw given subset
void DPhoenix::MeshGeometry::Draw(ID3D11DeviceContext* dc, UINT subsetId)
{
	UINT offset = 0;
	//set the vertec and index buffers
	dc->IASetVertexBuffers(0, 1, &mVB, &mVertexStride, &offset);
	dc->IASetIndexBuffer(mIB, mIndexBufferFormat, 0);

	//draw the sybet based on the index value for this subset
	dc->DrawIndexed(
		mSubsetTable[subsetId].FaceCount * 3,
	mSubsetTable[subsetId].FaceStart * 3,
	0);
}