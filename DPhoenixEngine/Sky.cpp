#include "D3DUtil.h"

DPhoenix::Sky::Sky(ID3D11Device* device,
	const std::string& cubemapFilename, float skySphereRadius)
{

	//create shader resouce view from loading cube map texture
	HR(D3DX11CreateShaderResourceViewFromFile(device,
		cubemapFilename.c_str(), 0, 0, &mCubeMapSRV, 0));

	//genrate sphere to map cube inside
	GeometryGenerator::MeshData sphere;
	GeometryGenerator geoGen;
	geoGen.CreateSphere(skySphereRadius, 30, 30, sphere);

	//STL vector for the position values
	std::vector<XMFLOAT3> vertices(sphere.Vertices.size());
	//populate the vertices from the generate sphere
	for (size_t i = 0; i < sphere.Vertices.size(); ++i)
		{
			vertices[i] = sphere.Vertices[i].Position;
		}
		//vertex buffers
	D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = sizeof(XMFLOAT3) * vertices.size();
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;
		vbd.StructureByteStride = 0;
	//assign vertivces and crate buffers
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];
	HR(device->CreateBuffer(&vbd, &vinitData, &mVB));

	
	//get index count from henerate sphere
	mIndexCount = sphere.Indices.size();
	//index buffer desc steup
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(USHORT) * mIndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	//populate the indices from henerated shape
	std::vector<USHORT> indices16;
	indices16.assign(sphere.Indices.begin(), sphere.Indices.end());
	//assign indices and create buffeer
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices16[0];
	HR(device->CreateBuffer(&ibd, &iinitData, &mIB));

}

DPhoenix::Sky::~Sky()
{
	ReleaseCOM(mVB);
	ReleaseCOM(mIB);
	ReleaseCOM(mCubeMapSRV);
}

ID3D11ShaderResourceView* DPhoenix::Sky::CubeMapSRV()
{
	return mCubeMapSRV;
}

void DPhoenix::Sky::Draw(ID3D11DeviceContext* dc, Camera* camera)
{
	//position and world matrix
	XMFLOAT3 eyePos = camera->mPosition;
	XMMATRIX world = XMMatrixTranslation(eyePos.x, eyePos.y, eyePos.z);

	//create ciew / rpjection matrix
	XMMATRIX view = camera->GetView();
	XMMATRIX proj = camera->GetProj();
	//transfromation matrices for camera
	XMMATRIX viewProj = XMMatrixMultiply(view, proj);
	XMMATRIX worldViewProj = XMMatrixMultiply(world, viewProj);
	//set shader vars
	Effects::SkyFX->SetWorldViewProj(worldViewProj);
	Effects::SkyFX->SetCubeMap(mCubeMapSRV);

	//caluate stride - set buffer to input assmebler
	UINT stride = sizeof(XMFLOAT3);
	UINT offset = 0;
	dc->IASetVertexBuffers(0, 1, &mVB, &stride, &offset);
	dc->IASetIndexBuffer(mIB, DXGI_FORMAT_R16_UINT, 0);
	dc->IASetInputLayout(InputLayouts::Pos);
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//get techniqe from shader
	D3DX11_TECHNIQUE_DESC techDesc;
	Effects::SkyFX->SkyTech->GetDesc(&techDesc);
	//loop through tech passes
	for (UINT p = 0; p < techDesc.Passes; ++p)
	{
		//get current pass
		ID3DX11EffectPass* pass = Effects::SkyFX->SkyTech->GetPassByIndex(p);
		//apply devcei context
		pass->Apply(0, dc);
			//draw the indexed sky sphered
			dc->DrawIndexed(mIndexCount, 0, 0);
	}

}