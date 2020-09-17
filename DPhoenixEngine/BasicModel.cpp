
#include "D3DUtil.h"

DPhoenix::BasicModel::BasicModel(ID3D11Device * device, TextureMgr * mTexMgr, const std::string & modelFilename, const std::string & texturePath)
{

	Assimp::Importer importer;


	const aiScene* scene = importer.ReadFile(modelFilename,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType |
		aiProcess_SplitLargeMeshes |
		aiProcess_MakeLeftHanded |
		aiProcess_FlipUVs);

	const int iVertexTotalSize = sizeof(aiVector3D) * 3 + sizeof(aiVector2D);

	int iTotalVertices = 0;

	std::vector<int> materialIndices;
	std::vector<int> iMeshStartIndices;
	std::vector<int> iMeshSizes;


	for (int i = 0; i < scene->mNumMeshes; i++)
	{

		MeshGeometry::Subset newSubset;

		aiMesh* mesh = scene->mMeshes[i];
		int iMeshFaces = mesh->mNumFaces;
		materialIndices.push_back(mesh->mMaterialIndex);


		int iSizeBefore = Vertices.size();
		iMeshStartIndices.push_back(iSizeBefore);

		newSubset.materialIndex = mesh->mMaterialIndex;

		newSubset.VertexStart = iSizeBefore;

		if (iSizeBefore > 0) {
			newSubset.FaceStart = Subsets.back().FaceCount + Subsets.back().FaceStart;

		}
		else
		{
			newSubset.FaceStart = 0;
		}


		newSubset.FaceCount = iMeshFaces;

		for (int j = 0; j < iMeshFaces; j++)
		{
			const aiFace& face = mesh->mFaces[j];

			for (int k = 0; k < face.mNumIndices; k++)
			{
				Indices.push_back(face.mIndices[k] + iSizeBefore);
			}
		}

		for (int j = 0; j < mesh->mNumVertices; j++)
		{
			aiVector3D pos = mesh->mVertices[j];
			aiVector3D uv = mesh->mTextureCoords[0][j];
			aiVector3D normal = mesh->mNormals[j];
			aiVector3D tangent = mesh->mTangents[j];

			Vertex::PosNormalTexTan vertex;
			vertex.Pos.x = pos.x; vertex.Pos.y = pos.y; vertex.Pos.z = pos.z;

			vertex.Tex.x = uv.x; vertex.Tex.y = uv.y;
			vertex.Normal.x = normal.x;
			vertex.Normal.y = normal.y;
			vertex.Normal.z = normal.z;


			vertex.TangentU.x = tangent.x;
			vertex.TangentU.y = tangent.y;
			vertex.TangentU.y = tangent.z;
			vertex.TangentU.w = 1.0f;



			PosNormalTexTan vertexCopy;
			vertexCopy.Normal = vertex.Normal;
			vertexCopy.Pos = vertex.Pos;
			vertexCopy.TangentU = vertex.TangentU;
			vertexCopy.Tex = vertex.Tex;

			Vertices.push_back(vertexCopy);

		}


		int iMeshVertices = mesh->mNumVertices;
		iTotalVertices += iMeshVertices;

		iMeshSizes.push_back((Vertices.size() - iSizeBefore));

		newSubset.VertexCount = Vertices.size() - iSizeBefore;

		Subsets.push_back(newSubset);


	}
	ModelMesh.SetVertices(device, &Vertices[0], Vertices.size());
	ModelMesh.SetIndices(device, &Indices[0], Indices.size());

	ModelMesh.SetSubsetTable(Subsets);
	SubsetCount = Subsets.size();


	int iNumMaterials = scene->mNumMaterials;

	Mat.resize(iNumMaterials);
	DiffuseMapSRV.resize(iNumMaterials);
	NormalMapSRV.resize(iNumMaterials);



	for (int i = 0; i < iNumMaterials; i++)
	{
		const aiMaterial* material = scene->mMaterials[i];
		int texIndex = 0;

		aiString path;


		aiColor4D diffuseColor;
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuseColor);


		aiColor4D specularColor;
		aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specularColor);

		aiColor4D ambientColor;
		aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambientColor);



		aiString matName;
		material->Get(AI_MATKEY_NAME, matName);


		float shininess;
		material->Get(AI_MATKEY_SHININESS, shininess);

		float shininessStrength;
		material->Get(AI_MATKEY_SHININESS_STRENGTH, shininessStrength);

		Material dxMaterial;

		ZeroMemory(&dxMaterial, sizeof(dxMaterial));


		dxMaterial.Diffuse.x = diffuseColor.r;
		dxMaterial.Diffuse.y = diffuseColor.g;
		dxMaterial.Diffuse.x = diffuseColor.b;
		dxMaterial.Diffuse.w = 1.0f;

		dxMaterial.Ambient.x = ambientColor.r;
		dxMaterial.Ambient.y = ambientColor.g;
		dxMaterial.Ambient.x = ambientColor.b;
		dxMaterial.Ambient.w = 1.0f;

		dxMaterial.Specular.x = specularColor.r;
		dxMaterial.Specular.y = specularColor.g;
		dxMaterial.Specular.x = specularColor.b;
		dxMaterial.Specular.w = shininess;


		Mat[i] = dxMaterial;

		int texCount = material->GetTextureCount(aiTextureType_DIFFUSE);

		for (texIndex = 0; texIndex < texCount; texIndex++)
		{

			if (material->GetTexture(aiTextureType_DIFFUSE, texIndex, &path) == AI_SUCCESS)
			{
				const char* cPathStr = path.C_Str();

				std::string strPathStr(cPathStr);


				ID3D11ShaderResourceView* diffuseMapSRV = mTexMgr->CreateTexture(texturePath + strPathStr);
				DiffuseMapSRV[i] = diffuseMapSRV;
			}

		}


		texCount = material->GetTextureCount(aiTextureType_NORMALS);


		for (texIndex = 0; texIndex < texCount; texIndex++)
		{

			if (material->GetTexture(aiTextureType_NORMALS, texIndex, &path) == AI_SUCCESS)
			{
				const char* cPathStr = path.C_Str();

				std::string strPathStr(cPathStr);


				ID3D11ShaderResourceView* normalMapSRV = mTexMgr->CreateTexture(texturePath + strPathStr);
				NormalMapSRV[i] = normalMapSRV;
			}

		}


	}






}

DPhoenix::BasicModel::~BasicModel()
{
}


DPhoenix::BasicModelInstance::BasicModelInstance()
{
	//default values for all properties
	//note scale must be 1! Nothing will render at 0!
	mPosition.x = 0.0f; mPosition.y = 0.0f; mPosition.z = 0.0f;
	mVelocity.x = 0.0f; mVelocity.y = 0.0f; mVelocity.z = 0.0f;
	mRelativeVelocity.x = 0.0f; mRelativeVelocity.y = 0.0f; mRelativeVelocity.z = 0.0f;
	mScale.x = 1.0f; mScale.y = 1.0f; mScale.z = 1.0f;
	mRotation.x = 0.0f; mRotation.y = 0.0f; mRotation.z = 0.0f;
	mForwardVector.x = 0.0f; mForwardVector.y = 0.0f; mForwardVector.z = 1.0f;
	mRightVector.x = 1.0f; mRightVector.y = 0.0f; mRightVector.z = 0.0f;

}

void DPhoenix::BasicModelInstance::Update(float dt, bool moveRelative)
{
	mPrevPosition = mPosition;


	mPrevPosition = mPosition;

	//if we are moving relatively to the object's forward vector we use this
	//(may need to adjust after some experimentation)
	if (moveRelative)
	{
		XMFLOAT3 vecUp(0.0f, 1.0f, 0.0f);

		XMVECTOR vecRight = XMVector3Cross(XMLoadFloat3(&vecUp),
			XMLoadFloat3(&mForwardVector));
		XMVECTOR vecForward = XMLoadFloat3(&mForwardVector);

		vecForward = XMVectorScale(vecForward, mRelativeVelocity.z);
		vecRight = XMVectorScale(vecRight, mRelativeVelocity.x);


		XMVECTOR velocityVec = XMVectorAdd(vecForward, vecRight);
		XMFLOAT3 velocity;
		XMStoreFloat3(&velocity, velocityVec);

		mPosition.x += velocity.x * dt;
		mPosition.y += mRelativeVelocity.y * dt;
		mPosition.z += velocity.z * dt;



	}
	//otherwise this is global movement / world space
	else
	{
		mPosition.x += mVelocity.x * dt;
		mPosition.y += mVelocity.y * dt;
		mPosition.z += mVelocity.z * dt;
	}

}

void DPhoenix::BasicModelInstance::SetFacingRotation(float offsetDeg)
{

	float angle = atan2(-mForwardVector.x, -mForwardVector.z) * (180.0 / XM_PI);

	float rotation = (float)(angle + offsetDeg) * 0.0174532925f;

	mRotation.y = rotation;
}

DPhoenix::BasicModelInstance::~BasicModelInstance()
{
}

XMMATRIX DPhoenix::BasicModelInstance::CalculateTransforms()
{
	//initialises matrices with identity matrix where appropriate
	XMMATRIX Scale = XMMatrixScaling(mScale.x, mScale.y, mScale.z);
	XMMATRIX Translation = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);
	XMMATRIX RotationX = XMMatrixRotationX(mRotation.x);
	XMMATRIX RotationY = XMMatrixRotationY(mRotation.y);
	XMMATRIX RotationZ = XMMatrixRotationZ(mRotation.z);

	//rotations must be concatenated correctly in this order
	XMMATRIX Rotation = XMMatrixMultiply(RotationZ, XMMatrixMultiply(RotationY, RotationX));

	//final transforms must also be concatenated in this order (TSR)
	XMMATRIX World = XMMatrixMultiply(Rotation, XMMatrixMultiply(Scale, Translation));

	//return the matrix so it can be used with the shader
	return World;
}
