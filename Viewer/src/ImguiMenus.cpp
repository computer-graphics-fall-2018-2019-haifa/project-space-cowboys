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

glm::vec4 clearColor = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);
glm::vec2 offset = glm::vec2(0, 0);
float scalar = 1;

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
		static int counter = 0;
		static int sensitivity = 50;
		static float zoom = 1.0f;

		ImGui::Begin("Viewport Settings");                          // Create a window called "Hello, world!" and append into it.

		//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		

		ImGui::ColorEdit3("clear color", (float*)&clearColor); // Edit 3 floats representing a color		

		ImGui::SliderInt("Sensitivity", &sensitivity, 10, 1000);

		if (ImGui::Button("Up"))
		{
			scene.GetActiveCamera().Translate(glm::vec3(0, sensitivity, 0));
		}

		if (ImGui::Button("Right"))
		{
			scene.GetActiveCamera().Translate(glm::vec3(-sensitivity, 0, 0));
		}

		ImGui::SameLine();
		if (ImGui::Button("Left"))
		{
			scene.GetActiveCamera().Translate(glm::vec3(sensitivity, 0, 0));
		}		

		if (ImGui::Button("Down"))
		{
			scene.GetActiveCamera().Translate(glm::vec3(0, -sensitivity, 0));
		}

		if (ImGui::SliderFloat("Zoom", &zoom, -1000, 1000))
		{
			scene.GetActiveCamera().SetZoom(zoom);
		}
		
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
		
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}
}