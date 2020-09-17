#pragma once
#include "D3DUtil.h"

namespace DPhoenix
{
	class Sky
	{
	public:
		Sky(ID3D11Device* device, const std::string& cubemapFilename, float skySphereRadius);
		~Sky();

		//get cubemap textures for each 'face'
		ID3D11ShaderResourceView* CubeMapSRV();
		//draw the skyboxvoid Draw(ID3D11DeviceContext* dc, Camera* camera);
		void Draw(ID3D11DeviceContext* dc, Camera* camera);
	private:
		Sky(const Sky& rhs);
		Sky& operator=(const Sky& rhs);


	private:
		//vertex and index buffers
		ID3D11Buffer* mVB;
		ID3D11Buffer * mIB;
		//cubema texture for each 'face'
		ID3D11ShaderResourceView* mCubeMapSRV;
		//index count for rendering
		UINT mIndexCount;
	};
}
