#include "../../Inputs/InputContextManager.h"
#include "../../Draw/DrawableContainer.h"
#include "../../Draw/IGraphicSystem.h"
#include "../../ECS/ISystem.h"
#include "SceneHolder.h"
#include "Scene.h"

ska::Scene::Scene(SceneHolder& sh, InputContextManager& ril) :
m_inputCManager(ril),
m_holder(sh) {
}

ska::Scene::Scene(Scene& oldScene):
m_inputCManager(oldScene.m_inputCManager),
m_holder(oldScene.m_holder) {

}

void ska::Scene::graphicUpdate(DrawableContainer& drawables) {
	/* Graphics */
	for (auto& s : m_graphics) {
		s->setDrawables(drawables);
		s->update();
	}
}

void ska::Scene::eventUpdate(unsigned int) {

	/* Logics */
	for (auto& s : m_logics) {
		s->update();
	}
}