#include "Scene.h"
#include "MeshModel.h"
#include <string>

using namespace std;

Scene::Scene() :
	activeCameraIndex(0),
	activeModelIndex(0)
{
	//Add default camera
	AddCamera(
		Camera::Camera(
			glm::vec4(0, 0, 0, 0),
			glm::vec4(0, 0, 0, 0),
			glm::vec4(0, 0, 0, 0)
		)
	);
}

void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	models.push_back(model);
	char *name = new char[model->GetModelName().length() + 1];
	strcpy(name, model->GetModelName().c_str());
	modelsNames.push_back(name);
	int i = GetActiveModelIndex();
	models[i]->SetColor({ 0,0,0,0 });
	activeModelIndex = models.size()-1;
	models[activeModelIndex]->SetColor({ 1,1,0,0 });
	
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

const Camera Scene::GetCamera(int index) const
{
	return cameras[index];
}

const Camera Scene::GetActiveCamera() const
{
	if (cameras.size() > activeCameraIndex)
		return cameras[activeCameraIndex];
}

const Camera Scene::GetDefaultCamera() const
{
	return cameras[0];
}

void Scene::SetActiveModelIndex(int index)
{
	// implementation suggestion...
	if (index >= 0 && index < models.size())
	{
		int i = GetActiveModelIndex();
		models[i]->SetColor({ 0,0,0,0 });
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


