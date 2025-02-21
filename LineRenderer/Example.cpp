#include "Example.h"
#include "LineRenderer.h"
#include "imgui.h"
#include "TextStream.h"

Example::Example()
{
	//Use the constructor to set up the application info, because the harness
	//needs this information early so it can set the name of the window when
	//it creates it.
	appInfo.appName = "Example Program";
}

void Example::Initialise()
{
	//You should set up your application here. This function gets called
	//after the window is set up and the rendering context is created, so if
	//you're doing anything weird with rendering, OpenGL functions will be
	//available at this point.
}

void Example::Update(float delta)
{
	//Everything that your program does every frame should go here.
	//This includes rendering done with the line renderer!

	ImGui::Begin("Well Well Well");

	ImGui::SliderFloat("DVD", &someTestValue, -1, 7);

	ImGui::End();


	TextStream output(lines, cursorPos, 0.5f, Colour::GREEN.Lighten());

	output << "DVD " << someTestValue;
}

void Example::OnLeftClick()
{

}
