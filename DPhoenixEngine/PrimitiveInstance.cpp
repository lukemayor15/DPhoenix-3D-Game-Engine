#include "PrimitiveInstance.h"

//constructor - initialse embers
DPhoenix::PrimitiveInstance::PrimitiveInstance()
{
	//null pointers before use
	mMeshPtr = NULL;
	mPrimitiveVB = NULL;
	mPrimitiveIB = NULL;
	mDiffuseMap = NULL;
	//default type
	mPrimitiveType = PRIMITIVE_TEX;

	//default values for all properties
	//note sacle must be 1 nothing will render a t 0
	mPosition.x = 0.0f; mPosition.y = 0.0f; mPosition.z = 0.0f;
	mVelocity.x = 0.0f; mVelocity.y = 0.0f; mVelocity.z = 0.0f;
	mRelativeVelocity.x = 0.0f; mRelativeVelocity.y = 0.0f; mRelativeVelocity.z = 0.0f;
	mScale.x = 1.0f; mScale.y = 1.0f; mScale.z = 1.0f;
	mRotation.x = 0.0f; mRotation.y = 0.0f; mRotation.z = 0.0f;
	mForwardVector.x = 0.0f; mForwardVector.y = 0.0f; mForwardVector.z = 0.0f;
	mRightVector.x = 1.0f; mRightVector.y = 0.0f; mRightVector.z = 0.0f;
	mTexScaleU = 1.0f; mTexScaleV = 1.0f;
}


//destructor - release memory
DPhoenix::PrimitiveInstance::~PrimitiveInstance()
{
	//release vertex indix buffers
	ReleaseCOM(mPrimitiveVB);
	ReleaseCOM(mPrimitiveIB);
}

// update method; handle movment based on velcoity and delta time
void DPhoenix::PrimitiveInstance::Update(float deltaTime, bool moveRelative)
{
	//hold previous position
	mPrevPosition = mPosition;
	//if we are mvoing relatively to the object forward vector we use this
	//may need to adjust after some expermation
	if (moveRelative)
	{
		//get up vector (postive y)
		XMFLOAT3 vecUp(0.0f, 1.0f, 0.0f);
		//calulate right vector based on cross product of up forawrd
		XMVECTOR vecRight = XMVector3Cross(XMLoadFloat3(&vecUp),
			XMLoadFloat3(&mForwardVector));
		XMVECTOR vecForward = XMLoadFloat3(&mForwardVector);
		//scale direction forward / right based on x / z relative velocity
		vecForward = XMVectorScale(vecForward, mRelativeVelocity.z);
		vecRight = XMVectorScale(vecRight, mRelativeVelocity.x);

		//adding the forward and right vectors given us a final veclocity
		XMVECTOR velocityVec = XMVectorAdd(vecForward, vecRight);
		XMFLOAT3 velocity;	XMStoreFloat3(&velocity, velocityVec);

		//update position
		mPosition.x += velocity.x * deltaTime;
		mPosition.y += mRelativeVelocity.y * deltaTime;
		mPosition.z += velocity.z * deltaTime;
	}
	//other wise this is global movment / world space
	else
	{
		mPosition.x += mVelocity.x * deltaTime;
		mPosition.y += mVelocity.y * deltaTime;
		mPosition.z += mVelocity.z * deltaTime;
	}

	
}

//load a mesh instance with only vetex and color data
void DPhoenix::PrimitiveInstance::LoadColorInstance(ID3D11Device * md3dDevice, XMFLOAT4 color, GeometryGenerator::MeshData* meshPtr)
{

	//set render type
	mPrimitiveType = PRIMITIVE_COLOR;
	//assgin pointer to the mesh data
	mMeshPtr = meshPtr;

	//create a new vector of vertices for the buffer
	//same size as amount from mesh data
	std::vector<Vertex::PosColor> vertices;
	vertices.resize(mMeshPtr->Vertices.size());
	
	//this loop extracts the position data for each various vertex
	//and assgins it to out new vector as well as the color data
	for (size_t i = 0; i < mMeshPtr->Vertices.size(); ++i)
	{
		vertices[i].Pos = mMeshPtr->Vertices[i].Position;
		vertices[i].Color = color;
	}

	//vertex buffer
	D3D11_BUFFER_DESC vbd;							//desc struct for vertex buffer
	vbd.Usage = D3D11_USAGE_IMMUTABLE;				//usage flag (cant edit but quicker)
	vbd.ByteWidth = sizeof(Vertex::PosColor)		//multiply struct size by num of vetices
		* mMeshPtr->Vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//bind as vertec buffer
	vbd.CPUAccessFlags = 0;							//cpu ascces ftices lags
	vbd.MiscFlags = 0;								//misc flags
	vbd.StructureByteStride = 0;					//this goes prett deep let leave it at 0

	//create subresource with vertex buffer data
	D3D11_SUBRESOURCE_DATA vinitData;
	//apply vertices array
	vinitData.pSysMem = &vertices[0];
	//create buffer from device (stored in mPrimitiveVB
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mPrimitiveVB));

	//create new idnices vector
	std::vector<UINT> indices;
	//this transfers the data from meshdata to out new vecot to create the buffer
	indices.insert(indices.end(), mMeshPtr->Indices.begin(), mMeshPtr->Indices.end());

	//create indcies buffer
	
	D3D11_BUFFER_DESC ibd;							//desc struct for vertex buffer
	ibd.Usage = D3D11_USAGE_IMMUTABLE;				//usage flag (cant edit but quicker)
	ibd.ByteWidth = sizeof(UINT) * 	mMeshPtr->Indices.size();	//amount of indices * size per index
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;		//bind as index buffer
	ibd.CPUAccessFlags = 0;							//cpu ascces ftices lags
	ibd.MiscFlags = 0;								//misc flags
	ibd.StructureByteStride = 0;					//this goes prett deep let leave it at 0


	D3D11_SUBRESOURCE_DATA iinitData;
	//apply indices array
	iinitData.pSysMem = &indices[0];
	//creeate buffer from device (stored in mPrimiviteIB)
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mPrimitiveIB));
}

//load a mesh instance with only vertex and texture data
void DPhoenix::PrimitiveInstance::LoadBasicTexInstance(ID3D11Device * md3dDevice, std::string texFilename, GeometryGenerator::MeshData* meshPtr, TextureMgr* texMgr)
{

	//set render type
	mPrimitiveType = PRIMITIVE_TEX;

	//create new tecture from manger
	mDiffuseMap = texMgr->CreateTexture(texFilename);
	//assgin pointer to the mesh data
	mMeshPtr = meshPtr;

	//create a new vector of vertices for the buffer
	//same size as amount from mesh data
	std::vector<Vertex::PosTex> vertices;
	vertices.resize(mMeshPtr->Vertices.size());

	//this loop extracts the position data for each various vertex
	//and assgins it to out new vector as well as the color data
	for (size_t i = 0; i < mMeshPtr->Vertices.size(); ++i)
	{
		vertices[i].Pos = mMeshPtr->Vertices[i].Position;
		vertices[i].Tex = mMeshPtr->Vertices[i].TexC;
	}

	//vertex buffer
	D3D11_BUFFER_DESC vbd;							//desc struct for vertex buffer
	vbd.Usage = D3D11_USAGE_IMMUTABLE;				//usage flag (cant edit but quicker)
	vbd.ByteWidth = sizeof(Vertex::PosTex)		//multiply struct size by num of vetices
		* mMeshPtr->Vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//bind as vertec buffer
	vbd.CPUAccessFlags = 0;							//cpu ascces ftices lags
	vbd.MiscFlags = 0;								//misc flags
	vbd.StructureByteStride = 0;					//this goes prett deep let leave it at 0

	//create subresource with vertex buffer data
	D3D11_SUBRESOURCE_DATA vinitData;
	//apply vertices array
	vinitData.pSysMem = &vertices[0];
	//create buffer from device (stored in mPrimitiveVB
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mPrimitiveVB));

	//create new idnices vector
	std::vector<UINT> indices;
	//this transfers the data from meshdata to out new vecot to create the buffer
	indices.insert(indices.end(), mMeshPtr->Indices.begin(), mMeshPtr->Indices.end());

	//create indcies buffer

	D3D11_BUFFER_DESC ibd;							//desc struct for vertex buffer
	ibd.Usage = D3D11_USAGE_IMMUTABLE;				//usage flag (cant edit but quicker)
	ibd.ByteWidth = sizeof(UINT) * 	mMeshPtr->Indices.size();	//amount of indices * size per index
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;		//bind as index buffer
	ibd.CPUAccessFlags = 0;							//cpu ascces ftices lags
	ibd.MiscFlags = 0;								//misc flags
	ibd.StructureByteStride = 0;					//this goes prett deep let leave it at 0


	D3D11_SUBRESOURCE_DATA iinitData;
	//apply indices array
	iinitData.pSysMem = &indices[0];
	//creeate buffer from device (stored in mPrimiviteIB)
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mPrimitiveIB));
}

//load a mesh instance with full data (pos, normal , texture and tangent)
//load a mesh instance with only vertex and texture data
void DPhoenix::PrimitiveInstance::LoadLitTexInstance(ID3D11Device * md3dDevice, std::string texFilename, GeometryGenerator::MeshData* meshPtr, TextureMgr* texMgr)
{

	//set render type
	mPrimitiveType = PRIMITIVE_LITTEX;

	//create new tecture from manger
	mDiffuseMap = texMgr->CreateTexture(texFilename);
	//assgin pointer to the mesh data
	mMeshPtr = meshPtr;

	//create a new vector of vertices for the buffer
	//same size as amount from mesh data
	std::vector<Vertex::PosNormalTexTan> vertices;
	vertices.resize(mMeshPtr->Vertices.size());

	//this loop extracts the position data for each various vertex
	//and assgins it to out new vector as well as the color data
	for (size_t i = 0; i < mMeshPtr->Vertices.size(); ++i)
	{
		vertices[i].Pos = mMeshPtr->Vertices[i].Position;
		vertices[i].Normal = mMeshPtr->Vertices[i].Normal;
		vertices[i].Tex = mMeshPtr->Vertices[i].TexC;
		

		//pad out the tangent for effficenty
		XMFLOAT4 newTangent(mMeshPtr->Vertices[i].TangentU.x,
			mMeshPtr->Vertices[i].TangentU.y,
			mMeshPtr->Vertices[i].TangentU.z,
			1.0f);
		vertices[i].TangentU = newTangent;
	}
	
	
	//vertex buffer
	D3D11_BUFFER_DESC vbd;							//desc struct for vertex buffer
	vbd.Usage = D3D11_USAGE_IMMUTABLE;				//usage flag (cant edit but quicker)
	vbd.ByteWidth = sizeof(Vertex::PosNormalTexTan)		//multiply struct size by num of vetices
		* mMeshPtr->Vertices.size();
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;		//bind as vertec buffer
	vbd.CPUAccessFlags = 0;							//cpu ascces ftices lags
	vbd.MiscFlags = 0;								//misc flags
	vbd.StructureByteStride = 0;					//this goes prett deep let leave it at 0

	//create subresource with vertex buffer data
	D3D11_SUBRESOURCE_DATA vinitData;
	//apply vertices array
	vinitData.pSysMem = &vertices[0];
	//create buffer from device (stored in mPrimitiveVB
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mPrimitiveVB));

	//create new idnices vector
	std::vector<UINT> indices;
	//this transfers the data from meshdata to out new vecot to create the buffer
	indices.insert(indices.end(), mMeshPtr->Indices.begin(), mMeshPtr->Indices.end());

	//create indcies buffer

	D3D11_BUFFER_DESC ibd;							//desc struct for vertex buffer
	ibd.Usage = D3D11_USAGE_IMMUTABLE;				//usage flag (cant edit but quicker)
	ibd.ByteWidth = sizeof(UINT) * 	mMeshPtr->Indices.size();	//amount of indices * size per index
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;		//bind as index buffer
	ibd.CPUAccessFlags = 0;							//cpu ascces ftices lags
	ibd.MiscFlags = 0;								//misc flags
	ibd.StructureByteStride = 0;					//this goes prett deep let leave it at 0


	D3D11_SUBRESOURCE_DATA iinitData;
	//apply indices array
	iinitData.pSysMem = &indices[0];
	//creeate buffer from device (stored in mPrimiviteIB)
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mPrimitiveIB));
}


//apply trasforms and output world matrixa
//to convert to object space to world space
XMMATRIX DPhoenix::PrimitiveInstance::CalculateTransforms()
{
	//initialise matrices with indeity matrix where appropirate
	XMMATRIX Scale = XMMatrixScaling(mScale.x, mScale.y, mScale.z);
	XMMATRIX Translation = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);
	XMMATRIX RotationX = XMMatrixRotationX(mRotation.x);
	XMMATRIX RotationY = XMMatrixRotationY(mRotation.y);
	XMMATRIX RotationZ = XMMatrixRotationZ(mRotation.z);

	//rotations must be conmcatenated in this order
	XMMATRIX Rotation = XMMatrixMultiply(RotationZ, XMMatrixMultiply(RotationY, RotationX));

	//final transfomrs must also be concatenated in this order
	XMMATRIX World = XMMatrixMultiply(Rotation, XMMatrixMultiply(Scale, Translation));

	//return the matrix so it can be use with th shader
	return World;

}

//render - takes in a device contect and draws the buffers
void DPhoenix::PrimitiveInstance::Render(ID3D11DeviceContext* dc)
{
	//stride (size of each data point)
	UINT stride;

	switch (mPrimitiveType)
	{
	case PRIMITIVE_COLOR:
		stride = sizeof(Vertex::PosColor);
		break;
	case PRIMITIVE_TEX:
		stride = sizeof(Vertex::PosTex);
		break;
	case PRIMITIVE_LITTEX:
		stride = sizeof(Vertex::PosNormalTexTan);
		break;
	}
	//the offset is where in the data to begain
	//0 means the beginng
	UINT offset = 0;

	//this sets the vertex buffer for the
	//INput assembler
	dc->IASetVertexBuffers(
		0, 1, &mPrimitiveVB, &stride, &offset
	);

	//this set the index buffer to the
	//input assembler
	dc->IASetIndexBuffer(
		mPrimitiveIB, DXGI_FORMAT_R32_UINT, 0
	);

	//draw the mesh using indices
	dc->DrawIndexed(mMeshPtr->Indices.size(), 0, 0);
}

void DPhoenix::PrimitiveInstance::SetFacingRotation(float offsetDeg)
{
	{
		//calualte the rotain that needs to be applied to the
		//modle to face forward vector
		float angle = atan2(-mForwardVector.x, -mForwardVector.z) * (180.0 / XM_PI);

		//covner to rotaion in radines
		//offset is there in case models face odd firections for orgin
		float rotation = (float)(angle + offsetDeg) * 0.0174532925f;

		mRotation.y = rotation;
	}
}
