#include <memory>
#include <iostream>
#include <map>

#include "scene.h"
#include "scenerunner.h"

#include "diffuse_reflection.h"
#include "adsReflection.h"
#include "adsTwoSide.h"

static std::map< std::string, std::string > sceneData = {
		{"ads",        "Ambient, diffuse, and specular shading."},
		{"diffuse",    "Diffuse shading only"},
		/*{"discard",    "Example of discarding fragments"},
		{"flat",       "Flat shading"},
		{"subroutine", "Using a shader subroutine"},*/
		{"two-ads",   "Two-sided lighting"}
};

int main(int argc, char** argv)
{
	std::string recipeName = SceneRunner::parseCLArgs(argc, argv, sceneData);
	SceneRunner runner("Chapter 02 - " + recipeName);

	std::unique_ptr<Scene> scene;
	
	if (recipeName == "diffuse") {
		scene = std::unique_ptr<Scene>(new DiffuseReflection());
	}
	else if (recipeName == "ads") {
		scene = std::unique_ptr<Scene>(new ADSReflection());
	}
	else if (recipeName == "two-ads") {
		scene = std::unique_ptr<Scene>(new ADSTwoReflection());
	}

	return runner.run(*scene);

	return 0;
}