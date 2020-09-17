#pragma once
#include "D3DUtil.h"


//adpated from richardsSoftware

namespace DPhoenix
{
	//this is a copy futm the vertex namespace for conveince
	//dependency issues from header files lad to this solution
	struct PosNormalTexTanSkinned
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 Tex;
		XMFLOAT4 TangentU;
		XMFLOAT3 Weights;
		BYTE BoneIndices[4];
	};

	//this represents ech bone / 
	//node in the skeletion hierachery
	class Bone
	{
	public:
		std::string Name;
		//bind space transforms
		aiMatrix4x4 Offset;
		//local matrix transform
		aiMatrix4x4 LocalTransform;
		//to-root transform
		aiMatrix4x4 GlobalTransform;
		//copy of the original locla transform
		aiMatrix4x4 OriginalLocalTransform;
		//parent bone reference
		Bone* Parent;
		//child bone refrence
		std::vector<Bone*> Children;
		//is this a bone (or just node)
		bool isBone = false;

		Bone() { }
	};

	//for skinning -each vertex will have
	//a set of bones it is weighted by
	//should be max 4 and all add up to 1
	struct VertexWeight
	{
		UINT boneIndex;
		float weight;
	};

	//for each animation channel over time
	//there willbe a set of keys to scale , pos, rotate etc.
	//this holds them and keeps and animatino name also
	class AnimationChannel
	{
	public:
		std::string Name;
		std::vector<aiVectorKey> PositionKeys;
		std::vector<aiQuatKey> RotationKeys;
		std::vector<aiVectorKey> ScalingKeys;
	};

	//animaition evlulator - handles skinned / skelte animations
	//and interpolations
	class AnimEvaluator
	{
	private:
		//how many animtions
		std::vector<AnimationChannel> Channels;
		//wht was the last time point the animation was at
		float LastTime;
		//set of indexes for pos . scale / rpt keys in animation
		//used to interpolate between the animations
		//new stl struct
		std::vector<std::tuple<int, int, int>> LastPositions;
	public:
		//animation name
		std::string Name;
		bool PlayAnimationForward;		//play forward
		float TicksPerSecond;			//animation rate per sec
		float Duration;					//how lonf the animation cycle is
		//2D stl vecto of matrices - for each bone, what are the
		//transformation matrices foer them
		std::vector<std::vector<aiMatrix4x4>> Transforms;
		//constructor - takes i  assimp animation class
		AnimEvaluator(aiAnimation* anim);
		//this constructs the full animaitonto store in memory
		void Evaluate(float dt, std::map<std::string, Bone*>& bones);
		//get bone transforms
		std::vector<aiMatrix4x4> GetTransforms(float dt);
		//get the frame at a given index
		int GetFrameIndexAt(float dt);
	};

	class SceneAnimator
	{
	private:
		//helper structers
		//the root node of the skelton
		Bone* _skeleton;
		//a map to match names with bone struct
		std::map<std::string, Bone*> _bonesByName;
		//a  map to match bones with their indcc
		std::map<std::string, int> _bonesToIndex;
		//a map to match an animation with its id
		std::map<std::string, int> _animationNameToId;
		//wht is the current animation
		int CurrentAnimationIndex;
		int _i;; // for dummy name iterator
		//create the bone hierarchy
		Bone* CreateBoneTree(aiNode* node, Bone* parent);
		//this concatenates the transforms in bone space up the tree
		static void CalculateBoneToWorldTransform(Bone* child);
		//get the animations from the assimp model import
		void ExtractAnimations(const aiScene* scene);
		//calulate the current transforms interlop between frame
		void Calculate(float dt);
		//update the bone hierachet transfomrs
		static void UpdateTransforms(Bone* node);
	public:
		//list of animatio sand bones
		std::vector<AnimEvaluator> Animations;
		std::vector<Bone*> _bones;
		//quick evulator for checking is skinned
		bool HasSkeleton()
		{
			return _bones.size() > 0;
		}

		//constructor
		SceneAnimator();

		//copy construct
		SceneAnimator(const SceneAnimator &animator);

		//intialise th eskeletion and aniaitons base don assimp scene
		void Init(const aiScene* scene);
		//get a bone id the name
		int GetBoneIndex(std::string name);
		//set an animation given te name
		void SetAnimation(std::string name);
		//get transforms form bone hierachey
		std::vector<aiMatrix4x4> GetTransforms(float dt);

		//New for multiple anims
		//this method assums we are using the sme mesh / heirachy but loading
		//just the aniamiton data
		void LoadNewAnimations(std::string filename);
		void ConstructAnimations();
		//set an animation given the index
		void SetAnimation(int index);
		//cycle to next animaion
		void NextAnimation();
		void PrevAnimation();

		//new to get idnex
		int GetAnimationIndex() { return CurrentAnimationIndex; }

	};

	class SkinnedModel
	{
	private:
		///this gets the bone indices and blend weight neccsary for defind vertices
		void ExtractBoneWeightsFromMesh(aiMesh* mesh, std::map<UINT,
			std::vector<VertexWeight>>&vertToBoneWeights);
		//this then construct the vertex inpyr layout from the mesh data
		void ExtractVertices(aiMesh* mesh, std::map<UINT,
			std::vector<VertexWeight>>&vertToBoneWeights,
			bool flipTexY, std::vector<PosNormalTexTanSkinned>& _vertices);

	public:
		//each subset of the mesh
		std::vector<MeshGeometry::Subset> Subsets;
		//the verties for rendering
		std::vector<PosNormalTexTanSkinned> Vertices;
		//the indices for rendering
		std::vector<USHORT> Indices;
		//a pointer to the animation class model
		SceneAnimator* Animator;
		//the mesh geometry itself
		MeshGeometry ModelMesh;
		//number of subsets
		int SubsetCount;
		//materials and shader resource vire for mapping
		std::vector<Material> Mat;
		std::vector<ID3D11ShaderResourceView*> DiffuseMapSRV;
		std::vector<ID3D11ShaderResourceView*> NormalMapSRV;
		//constructor , take sin file name and texture path to exreact everythung
		SkinnedModel(ID3D11Device* device, TextureMgr& texMgr, const std::string& modelFilename,
			const std::string& texturePath, bool flipTexY = false);

		//to govern vertex bone wieght for each subset
		int mCurrentVertexCount;
		int mCurrentVertexCountBones;

		void CompressSubsets();
	};

	//an instance of the model to ender - as entity for inherited values
	class SkinnedModelInstance : public Entity
	{
	private:
		//animation data
		float _timePos;				//current time pos
		std::string _clipName;		//name of animation clip
		bool  _loopClips;			//loop animation
		std::vector<XMFLOAT4X4> _finalTransforms;		//a set of the final bone transforms for shdaer
		std::queue<std::string> _clipQueue;				//clip queue for animation

	public:
		//pointer t the mesh data
		SkinnedModel* Model;

		SceneAnimator* mInstanceAnimator;

		//constrcutor
		SkinnedModelInstance(std::string clipName,
			SkinnedModel* model);

		//copy construct
		SkinnedModelInstance(const SkinnedModelInstance &modelInstance);
		//getter and setter for animation clips
		std::string GetClipName() {
			return _clipName;	};
		void SetClipName(std::string name);
		std::vector < std::string> GetClips();
		//getter and setter for looping animation
		bool GetLoopClips() {	return _loopClips;	}
		void SetLoopClips(bool value) {
			_loopClips = value;	}
		//get the final bone tranfomrs for the shader
		std::vector<XMFLOAT4X4> GetFinalTransforms();

		//main entity maagment for instances
		void Update(float deltaTime, bool moveRelative);
		XMMATRIX CalculateTransforms();	//world matrix
		void SetFacingRotation(float offsetDrag);

		//get bone transforms for skeletion
		std::vector<XMFLOAT4X4> GetBoneTransforms();

		//rotation offset
		float mRotYOffset;

		//new methods for animation control
		float GetTimePos() { return _timePos; }
		void SetTimePos(float pos) {_timePos = pos; }
	};
}