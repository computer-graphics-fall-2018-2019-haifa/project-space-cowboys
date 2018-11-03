#include "Scene.h"
#include "MeshModel.h"
#include <string>

using namespace std;

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{

}

void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	models.push_back(model);
	
	char *name = new char[model->GetModelName().length() + 1];
	strcpy(name, model->GetModelName().c_str());
	modelsNames.push_back(name);
	
}

const int Scene::GetModelCount() const
{
	return models.size();
}

void Scene::AddCamera(const Camera& camera)
{
	cameras.push_back(camera);
}

const int Scene::GetCameraCount() const
{
	return cameras.size();
}

void Scene::SetActiveCameraIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < cameras.size())
	{
		activeCameraIndex = index;
		
	}
}

const int Scene::GetActiveCameraIndex() const
{
	return activeCameraIndex;
}

void Scene::SetActiveModelIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < models.size())
	{
		activeModelIndex = index;
		models[index]->SetColor({ 1,1,0,0 });
	}
}

const int Scene::GetActiveModelIndex() const
{
	return activeModelIndex;
}

const std::vector<std::shared_ptr<MeshModel>>& Scene::GetAllModels() const
{
	return models;
}


const std::vector<char *> Scene::getModelsNames() const
{
	return modelsNames;
}


