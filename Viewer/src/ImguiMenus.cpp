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

glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

const glm::vec4& GetClearColor()
{
	return clearColor;
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &showDemoWindow);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &showAnotherWindow);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

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
						scene.AddModel(std::make_shared<MeshModel>(Utils::LoadMeshModel(outPath)));
						free(outPath);
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
			
			if (ImGui::BeginMenu("Objects"))
			{
				if (ImGui::BeginMenu("Models"))
				{
					std::vector<char*> names(scene.getModelsNames());
					int size = scene.GetModelCount();
					for (int i = 0; i < size; i++)
					{
						if (ImGui::MenuItem(names[i]))
						{
							scene.SetActiveModelIndex(i);
							ImGui::EndMenu();
						}
						
					}
					
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Cameras"))
				{
					ImGui::EndMenu();
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
		static float eyeInput[4] = { 0, 0, 0, 0 };
		static float atInput[4] = { 0, 0, 0, 0 };
		static float upInput[4] = { 0, 0, 0, 0 };

		ImGui::InputFloat3("Camera Position", eyeInput);

		glm::vec4 eye = glm::vec4(eyeInput[0], eyeInput[1], eyeInput[2], 0);
		glm::vec4 at = glm::vec4(0, 0, 0, 0);
		glm::vec4 up = glm::vec4(0, 0, 0, 0);

		Camera camera = Camera(eye, at, up);
		scene.AddCamera(camera);
		

		if (ImGui::Button("create"))
		{


			showCameraPropWindow = false;
		}


		ImGui::End();
	}
}