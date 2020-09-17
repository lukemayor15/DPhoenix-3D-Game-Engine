#pragma once
#include "D3DUtil.h"

//note: make sure structer allgiment agress with HLSL structer padding rules
//elements are pack into 4D vectors with the restrication that an element
//cannot staddle a 4D vector boundary

//light from an arbritary distant point (sunlight)
struct DirectionalLight
{
	//zeroise
	DirectionalLight() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 Ambient;		// ambient light color (unifrom brightness)
	XMFLOAT4 Diffuse;		//diffuse light color (scatterd brightness)
	XMFLOAT4 Specular;		//dpecular color (shiny highlights - w dimension is power)
	XMFLOAT3 Direction;     //direction lightpointing
	float pad;				// pad the last float so we can set an array of light if we wanted

};

//as applied to mdoles and how they react to light source
struct Material
{
	//zeroise before use
	Material() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 Ambient;		// ambient light color (unifrom brightness)
	XMFLOAT4 Diffuse;		//diffuse light color (scatterd brightness)
	XMFLOAT4 Specular;		//dpecular color (shiny highlights - w dimension is power)
	XMFLOAT4 Reflect;		//refection values (adance challenge)
};

//light from a position that emanates in all directions
struct PointLight
{
	//zerosize before use
	PointLight() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 Ambient;		// ambient light color (unifrom brightness)
	XMFLOAT4 Diffuse;		//diffuse light color (scatterd brightness)
	XMFLOAT4 Specular;		//dpecular color (shiny highlights - w dimension is power)

	//packed into 4d vector : (position range)
	XMFLOAT3 Position;
	float Range;

	//Packed into 4D vector (a0, a1, a2, pad) - attenuattion (drop-off) around source
	XMFLOAT3 Att;
	float Pad;	//Pad the last float so we can set an array of light if we wanted.

};
//spotlight struct - coned light from a point in direction
struct SpotLight
{
	//zeroise before use
	SpotLight() { ZeroMemory(this, sizeof(this)); }

	XMFLOAT4 Ambient;	//ambient light color (unifrom brightness)
	XMFLOAT4 Diffuse;	// diffuse light color (scatterd brightness)
	XMFLOAT4 Specular;	// specular color (shiny highlights - w dimension is power)

	//paced into 4D vector : (position, range)
	XMFLOAT3 Position;
	float Range;

	//packed into 4D vector (direction, spot)
	XMFLOAT3 Direction;
	float Spot;

	//packed into 4D vecotr (a0, a1, a2, pad)- attenuatii(drop-off) around source
	XMFLOAT3 Att;
	float pad;	// pad the last flaot so we can set an array of lights if we wanted
};