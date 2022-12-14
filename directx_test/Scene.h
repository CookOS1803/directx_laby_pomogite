#pragma once
#include "NormWin.h"
#include <memory>
#include "SceneObject.h"

class Graphics;

class Scene
{
public:

	constexpr Scene(Graphics* gfx) : objects(), uiObjects(), pGfx(gfx) {}

	constexpr const std::vector<std::unique_ptr<SceneObject>>& Objects() const noexcept { return objects; }
	SceneObject* CreateObject();
	SceneObject* CreateUIObject();

	constexpr std::vector<std::unique_ptr<SceneObject>>& Objects() { return objects; }
	constexpr std::vector<std::unique_ptr<SceneObject>>& UIObjects() { return uiObjects; }

private:

	std::vector<std::unique_ptr<SceneObject>> objects;
	std::vector<std::unique_ptr<SceneObject>> uiObjects;
	Graphics* pGfx;
};

