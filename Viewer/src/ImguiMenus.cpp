#pragma once
#define _USE_MATH_DEFINES

#include "ImguiMenus.h"
#include "MeshModel.h"
#include "Utils.h"
#include <cmath>
#include <memory>
#include <stdio.h>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <nfd.h>
#include <random>

bool showDemoWindow = false;
bool showAnotherWindow = false;
bool showCameraPropWindow = false;
bool showActiveCamera = true;
bool showActiveModel = false;
Camera *cam;
std::shared_ptr<MeshModel> activeModel ;
glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec2 offset = glm::vec2(0, 0);
float scalar = 1;

const glm::vec4& GetClearColor()
{
	return clearColor;
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{	
	 cam = &scene.GetActiveCamera();
	
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
				
	
		ImGui::Begin("Viewport Settings");                          // Create a window called "Hello, world!" and append into it.

		
		ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color		

		
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (showAnotherWindow)
	{
		ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			showAnotherWindow = false;
		}
		ImGui::End();
	}

	// 4. Demonstrate creating a fullscreen menu bar and populating it.
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoFocusOnAppearing;
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Load Model...", "CTRL+O"))
				{
					nfdchar_t *outPath = NULL;
					nfdresult_t result = NFD_OpenDialog("obj;png,jpg", NULL, &outPath);
					if (result == NFD_OKAY) {
						scene.AddModel(std::make_shared<MeshModel>(Utils::LoadMeshModel(outPath, false)));
						free(outPath);
						showActiveModel = true;
						activeModel = scene.getActiveModel();
					}
					else if (result == NFD_CANCEL) {
					}
					else {
					}

				}
				if (ImGui::MenuItem("Add Camera", "CTRL+A"))
				{
					showCameraPropWindow = true;
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Add Primitives"))
			{
				if (ImGui::MenuItem("Add Poly"))
				{
					scene.AddModel(std::make_shared<MeshModel>(MeshModel(0)));
					activeModel = scene.getActiveModel();
					showActiveModel = true;
					cam->SetCameraLookAt(cam->eye, activeModel->superCenterPoint, cam->up);

				}
				if (ImGui::MenuItem("Add box"))
				{
					
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Models and Cameras"))
			{
				if (ImGui::BeginMenu("Models"))
				{
					int size = scene.GetModelCount();
					if (size != 0) {
						std::vector<char*> names(scene.getModelsNames());
						int size = scene.GetModelCount();
						float sz = ImGui::GetTextLineHeight();
						for (int i = 0; i < size; i++)
						{
							const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
							ImVec2 p = ImGui::GetCursorScreenPos();
							ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
							ImGui::Dummy(ImVec2(sz, sz));
							ImGui::SameLine();
							if (ImGui::MenuItem(names[i]))
							{
								scene.SetActiveModelIndex(i);
								activeModel = scene.getActiveModel();

							}
						}
					}
					ImGui::EndMenu();

				}

				if (ImGui::BeginMenu("Cameras"))
				{
					int size = scene.GetCameraCount();
					if (size != 0) {
						std::vector<char*> cNames(scene.getcamerasNames());

						float sz = ImGui::GetTextLineHeight();
						for (int i = 0; i < size; i++)
						{
							const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
							ImVec2 p = ImGui::GetCursorScreenPos();
							ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + sz, p.y + sz), ImGui::GetColorU32((ImGuiCol)i));
							ImGui::Dummy(ImVec2(sz, sz));
							ImGui::SameLine();
							if (ImGui::MenuItem(cNames[i]))
							{
								scene.SetActiveCameraIndex(i);
							}
						}
					}
					ImGui::EndMenu();
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("help"))
			{
				if (ImGui::MenuItem("Demo imgui","F1"))
				{
					showDemoWindow = true;
				}
				ImGui::EndMenu();
			}
			

			ImGui::EndMainMenuBar();
		}
	}
	// 4. camera prop window.

	if (showCameraPropWindow)
	{
		ImGui::Begin("Camera Properties", &showCameraPropWindow);
		ImGui::Text("please select the new camera properties");
		static float eyeInput[4] = { 0, 0, 5, 0 };
		static float atInput[4] = { 0, 0, -10, 0 };
		static float upInput[4] = { 0, 0, 1, 0 };

		ImGui::InputFloat3("Camera Position", eyeInput);
		ImGui::InputFloat3("look At Position", atInput);
		ImGui::InputFloat3("Up Position", atInput);

		glm::vec4 eye = glm::vec4(eyeInput[0], eyeInput[1], eyeInput[2], 0);
		glm::vec4 at = glm::vec4(atInput[0], atInput[1], atInput[2], 0);
		glm::vec4 up = glm::vec4(upInput[0], upInput[1], upInput[2], 0);
		glm::vec4 zero;


		if (!(at == zero || up == zero)) {
			if (ImGui::Button("create"))
			{
				scene.AddCamera(Camera::Camera(eye, at, up));
				showCameraPropWindow = false;
			}
		}

		ImGui::End();
	}




	
	char* name;
	name = (char*)malloc(sizeof(char) * 25);
	strcpy(name, scene.getActiveCameraName());
	strcat(name, " Properties");

	if (showActiveCamera) {
		ImGui::Begin(name, NULL);
		static float zoom = 1.0f;
		
		
		static int k;
		ImGui::RadioButton("Projection", &k, 0);
		ImGui::RadioButton("Orthografic", &k, 1);
		scene.GetActiveCamera().projection = k;
		if (k == 0) {
			cam->SetPerspectiveProjection(cam->fovy, cam->aspect, cam->zNear, cam->zFar);
		}
		else {
			cam->setProjectionTransformation(scene.settings.w, scene.settings.h);
		}
		if (ImGui::SliderFloat("Zoom", &zoom, 1, 10)){
			scene.GetActiveCamera().SetZoom(zoom);
		}
		ImGui::Separator();
		ImGui::Text("tt");
		if (ImGui::Button("focus on active model")) {
			cam->at = activeModel->superCenterPoint;
			
			cam->updateLookAt();
		}
		static int c = 0;
		ImGui::RadioButton("Cmaera Rotation", &c, 0); ImGui::SameLine();
		ImGui::RadioButton("Cmaera Pan", &c, 1);
		if (c == 0) {
			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 1.0f, 0.0f, 0.0f, 0.8 });
			ImGui::Text("Rotate x"); ImGui::SameLine();
			ImGui::SliderAngle("x", &(cam->rotate.x)); ImGui::SameLine();
			ImGui::PopStyleColor(1);
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0 / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0 / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0 / 7.0f, 0.8f, 0.8f));
			if (ImGui::Button("Reset x")) {
				cam->rotate.x = 0.0f;
			}
			ImGui::PopStyleColor(3);

			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.0f, 1.0f, 0.0f, 0.8 });
			ImGui::Text("Rotate y"); ImGui::SameLine();
			ImGui::SliderAngle("y", &(cam->rotate.y)); ImGui::SameLine();
			ImGui::PopStyleColor(1);
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0 / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0 / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0 / 7.0f, 0.8f, 0.8f));
			if (ImGui::Button("Reset y")) {
				cam->rotate.y = 0.0f;
			}
			ImGui::PopStyleColor(3);

			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.0f, 0.0f, 1.0f, 0.8 });
			ImGui::Text("Rotate z"); ImGui::SameLine();
			ImGui::SliderAngle("z", &(cam->rotate.z)); ImGui::SameLine();
			ImGui::PopStyleColor(1);
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0 / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0 / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0 / 7.0f, 0.8f, 0.8f));
			if (ImGui::Button("Reset z")) {
				cam->rotate.z = 0.0f;
			}
			ImGui::PopStyleColor(3);
		}
		if (c == 1) {
			ImGui::SliderFloat("Pan X", &(cam->translate.x), -1000.0f, 1000.0f);
			ImGui::SliderFloat("Pan Y", &(cam->translate.y), -1000.0f, 1000.0f);
			ImGui::SliderFloat("Pan Z", &(cam->translate.z), -1000.0f, 1000.0f);
		}
		cam->updateEye();
		ImGui::End();
	}
	
	free(name);
	
	if (showActiveModel) {
		
		
		ImGui::Begin("active model", NULL);
		
		static bool boundingBox = false;
		static bool normals = false;
		scene.settings.showBoundingBox = boundingBox;
		scene.settings.showNormals = normals;
		
		static int e = 2;
		static int w = 0;
		

		static int mSensitivity = 50;
		if (ImGui::Checkbox("Show Bounding Box", &boundingBox)) {
			scene.settings.showBoundingBox = boundingBox;
		}ImGui::SameLine();
		ImGui::ColorEdit4("Box color", (float*)&activeModel->boxColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel );
		if (ImGui::Checkbox("Show normals", &normals)) {
			scene.settings.showNormals = normals;
		}ImGui::SameLine();
		ImGui::ColorEdit4("Morm Color", (float*)&activeModel->normColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel );


		ImGui::Text("");
		ImGui::RadioButton("World", &w, 0); ImGui::SameLine();
		ImGui::RadioButton("Local", &w, 1);
		ImGui::Text("");
		ImGui::Separator();
		ImGui::Text("");
		ImGui::RadioButton("Rotate", &e, 2); ImGui::SameLine();
		ImGui::RadioButton("Scale", &e, 0); ImGui::SameLine();
		ImGui::RadioButton("Move", &e, 1);
		if (w) {

			
		}
		else {
			
		}
		ImGui::Text("");
		ImGui::Separator();
		ImGui::Text("");
		if (e == 0) {

			ImGui::DragFloat("Scale x  ", &(activeModel->scale[w].x), 0.1f); ImGui::SameLine();
			if (ImGui::Button("Reset x")){
				activeModel->scale[w].x = 1.0f;
			}
			ImGui::DragFloat("Scale y  ", &(activeModel->scale[w].y), 0.1f); ImGui::SameLine();
			if (ImGui::Button("Reset y")){
				activeModel->scale[w].y = 1.0f;
			}
			ImGui::DragFloat("Scale z  ", &(activeModel->scale[w].z), 0.1f); ImGui::SameLine();
			if (ImGui::Button("Reset z")){
				activeModel->scale[w].z = 1.0f;
			}
		}
		if (e == 1) {
			ImGui::SliderInt("Sensitivity", &mSensitivity, 1, 100);
			ImGui::Text("Move on X"); 
			if (ImGui::Button("x -  ")){
				activeModel->translate[w].x -= 1 * mSensitivity;
			}
			; ImGui::SameLine();
			if (ImGui::Button("x +  ")){
				activeModel->translate[w].x += 1.0 * mSensitivity;
			} ImGui::SameLine();
			ImGui::Text(":  %d", (int)activeModel->translate[w].x);

			ImGui::Text("Move on Y");
			if (ImGui::Button("y -  ")){
				activeModel->translate[w].y -= 1 * mSensitivity;
			}
			; ImGui::SameLine();
			if (ImGui::Button("y +  ")){
				activeModel->translate[w].y += 1 * mSensitivity;
			}ImGui::SameLine();
			ImGui::Text(":  %d", (int)activeModel->translate[w].y);

			ImGui::Text("Move on Z");
			if (ImGui::Button("z -  ")){
				activeModel->translate[w].z -= 1 * mSensitivity;
			}
			; ImGui::SameLine();
			if (ImGui::Button("z +  ")){
				activeModel->translate[w].z += 1 * mSensitivity;
			}ImGui::SameLine();
			ImGui::Text(":  %d", (int)activeModel->translate[w].z);
		}
		if (e == 2) {
			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 1.0f, 0.0f, 0.0f, 0.8 });
			ImGui::Text("Rotate x"); ImGui::SameLine();
			ImGui::SliderAngle("x", &(activeModel->rotate[w].x)); ImGui::SameLine();
			ImGui::PopStyleColor(1);
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0 / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0 / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0 / 7.0f, 0.8f, 0.8f));
			if (ImGui::Button("Reset x")){
				activeModel->rotate[w].x = 0.0f;
			}
			ImGui::PopStyleColor(3);

			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.0f, 1.0f, 0.0f, 0.8 });
			ImGui::Text("Rotate y"); ImGui::SameLine();
			ImGui::SliderAngle("y", &(activeModel->rotate[w].y)); ImGui::SameLine();
			ImGui::PopStyleColor(1);
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0 / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0 / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0 / 7.0f, 0.8f, 0.8f));
			if (ImGui::Button("Reset y")){
				activeModel->rotate[w].y = 0.0f;
			}
			ImGui::PopStyleColor(3);

			ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0.0f, 0.0f, 1.0f, 0.8 });
			ImGui::Text("Rotate z"); ImGui::SameLine();
			ImGui::SliderAngle("z", &(activeModel->rotate[w].z)); ImGui::SameLine();
			ImGui::PopStyleColor(1);
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0 / 7.0f, 0.6f, 0.6f));
			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0 / 7.0f, 0.7f, 0.7f));
			ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0 / 7.0f, 0.8f, 0.8f));
			if (ImGui::Button("Reset z")){
				activeModel->rotate[w].z = 0.0f;
			}
			ImGui::PopStyleColor(3);
		}
		ImGui::Text("");
		
		activeModel->updateTransformations(scene.settings.w, scene.settings.h);
		ImGui::End();
	}

}
