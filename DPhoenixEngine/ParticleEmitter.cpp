#include "ParticleEmitter.h"

DPhoenix::ParticleEmitter::ParticleEmitter()
{
	//billboard sprite as templete
	mSprite = NULL;

	//position vars
	mPosition.x = 0.0f; mPosition.y = 0.0f; mPosition.z = 0.0f;
	mDirectionAngleH = 0.0f;
	mDirectionAngleV = 0.0f;
	mLength = 50.0f;

	//color, amount, alpha varition
	mMax = 100;
	mMinAlpha = 255; mMaxAlpha = 255;
	mMinR = 255; mMinG = 255; mMinB = 255;
	mMaxR = 255; mMaxG = 255; mMaxB = 255;

	//sperad cars
	mSpreadH = 360; mSpreadV = 360;
	mVelocityH = 10.0f; mVelocityV = 10.0f;
	mMinScale = 1.0f; mMaxScale = 1.0f;

	mEmitDelay = 0.01f;
}

DPhoenix::ParticleEmitter::~ParticleEmitter()
{
	for each(BillboardSprite* sprite in mParticles)
	{
		delete sprite;
		sprite = NULL;
	}

	mParticles.clear();
}

void DPhoenix::ParticleEmitter::Update(float deltaTime)
{

	static GameTimer timer;

	timer.Tick();

	//do we need to add new paricles
	if (mParticles.size() < mMax)
	{
		//slowdown baised on emission delay
		if (timer.TotalTime() > mEmitDelay)
		{
			Add();
			timer.Reset();
		}
	}

	//loop through each paricles
	for each(BillboardSprite* particle in mParticles)
	{

		//update particle
		particle->UpdateBS(deltaTime);

		//is particle beyond the emitters range
		float diffX, diffY, diffZ;
		diffX = particle->mPosition.x - mPosition.x;
		diffY = particle->mPosition.y - mPosition.y;
		diffZ = particle->mPosition.z - mPosition.z;

		float dist = sqrtf(diffX * diffX + diffY * diffY + diffZ * diffZ);

		if (dist > mLength)
		{
			//reset particle to origin
			particle->mPosition = mPosition;
		}

	}

}

bool DPhoenix::ParticleEmitter::Load(std::string filename, TextureMgr * mTexMgr,
	float width, float height, ID3D11Device * md3dDevice)
{

	mSprite = new BillboardSprite();

	mSprite->Load(filename, mTexMgr, width, height, md3dDevice);

	return true;
}

void DPhoenix::ParticleEmitter::Add()
{

	//velocitys on x, y z
	float vX, vY, vZ;

	//new billboard sorite from templete; set image and position
	BillboardSprite* p = new BillboardSprite(*mSprite);
	p->mPosition = mPosition;

	//add some randomnesss to spread
	float variationH = (rand() % mSpreadH - mSpreadH / 2) / 100.0f;
	float variationV = (rand() % mSpreadV - mSpreadV / 2) / 100.0f;

	//set linear velcoity
	float dirH = mDirectionAngleH - 90.0f;
	float dirV = mDirectionAngleV - 90.0f;

	dirH = XMConvertToRadians(dirH);
	dirV = XMConvertToRadians(dirV);

	vX = cos(dirH) + variationH;
	vY = sin(dirV) + variationV;
	vZ = sin(dirH) + variationH;

	p->mVelocity.x = vX * mVelocityH;
	p->mVelocity.y = vY * mVelocityV;
	p->mVelocity.z = vZ * mVelocityH;

	//add particle to emitters
	mParticles.push_back(p);
}