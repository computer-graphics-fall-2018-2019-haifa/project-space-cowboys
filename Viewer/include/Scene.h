#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Camera.h"
#include <tuple>
#include "Global.h"

/*
 * Scene class.
 * This class holds all the scene information (models, cameras, lights, etc..)
 */
class Scene {
private:
	std::vector<std::shared_ptr<MeshModel>> models;
	std::vector<Camera> cameras;
	std::vector<char *> modelsNames;
	std::vector<char *> camerasNames;

	int activeCameraIndex;
	int activeModelIndex;

public:
	Scene();

	struct {
		bool showBoundingBox;
		bool showNormals;
	} settings;

	void AddModel(const std::shared_ptr<MeshModel>& model);
	void RemoveModel(int index);
	const int GetModelCount() const;

	void AddCamera(Camera camera);
	const int GetCameraCount() const;

	void SetActiveCameraIndex(int index);
	const int GetActiveCameraIndex() const;
	const Camera GetCamera(int index) const;
	Camera& GetActiveCamera();
	const Camera GetDefaultCamera() const;

	void SetActiveModelIndex(int index);
	const int GetActiveModelIndex() const;
	const MeshModel getActiveModel();
	const std::vector<std::shared_ptr<MeshModel>>& GetAllModels() const;
	const std::vector<Camera> GetAllCameras() const;
	const std::vector<char *> getModelsNames() const;
	const std::vector<char *> getcamerasNames() const;

	char * getActiveCameraName();
	
};