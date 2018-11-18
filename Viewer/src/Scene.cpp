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
/* adding a model to the sence and adding the name to the name vec without the .obj*/
void Scene::AddModel(const std::shared_ptr<MeshModel>& model)
{
	models.push_back(model);
	char *name = new char[model->GetModelName().length() + 1];
	strcpy(name, model->GetModelName().c_str());
	char * end = strstr(name, ".obj");
	*end = '\0';
	modelsNames.push_back(name);
	int i = GetActiveModelIndex();
	models[i]->SetColor({ 0,0,0,0 });
	activeModelIndex = models.size()-1;
	models[activeModelIndex]->SetColor({ 1,1,0,0 });
	
}
/*removing a model from the scene*/
void Scene::RemoveModel(int index) 
{
	models.erase(models.begin() + index);
	modelsNames.erase(modelsNames.begin() + index);
}
const int Scene::GetModelCount() const
{
	return models.size();
}

void Scene::AddCamera( Camera camera)
{
	cameras.push_back(camera);
	
	char *name = new char[(camera.GetModelName()).length() + 1];
	strcpy(name, (camera.GetModelName()).c_str());
	char * end = strstr(name, "obj");
	*end = '\0';
	std::string cameraNum = std::to_string(cameras.size());
	strcat(name, cameraNum.c_str());
	camerasNames.push_back(name);
	SetActiveCameraIndex(cameras.size() - 1);

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
		int i = GetActiveCameraIndex();
		cameras[i].SetColor({ 1,0,0,0 });
		activeModelIndex = index;
		cameras[index].SetColor({ 0,1,0,0 });
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

Camera& Scene::GetActiveCamera()
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

const MeshModel Scene::getActiveModel()
{
	return *models[activeModelIndex];
}

const std::vector<std::shared_ptr<MeshModel>>& Scene::GetAllModels() const
{
	return models;
}

const std::vector<Camera> Scene::GetAllCameras() const
{
	return cameras;
}

const std::vector<char *> Scene::getModelsNames() const
{
	return modelsNames;
}

const std::vector<char*> Scene::getcamerasNames() const
{
	return camerasNames;
}

 char* Scene::getActiveCameraName() 
{
	return camerasNames[activeCameraIndex];
}


