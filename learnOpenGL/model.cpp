#include "model.h"
#include <iostream>
using namespace std;

Model::Model(const char* path)
{
	loadModel(path);
}

Model::~Model()
{
}

void Model::Draw(Shader shader)
{
	for (auto& mesh : meshes)
		mesh.Draw(shader);
}

void Model::loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);
	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
	{
		cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
	}
	directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);

}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// process all mesh's nodes
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// next, repeat the process node for it's child node 
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh * node, const aiScene* scene)
{
}

std::vector<Texture> Model::loadMaterialTexture(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	return std::vector<Texture>();
}
