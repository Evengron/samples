#include "stdafx.h"

#include "MainState.h"
#include "Game.h"
#include "InputManager.h"

#include "CameraRenderComponent.h"
#include "SpriteRenderComponent.h"
#include "PlayerMoveComponent.h"
#include "TransformCopyComponent.h"
#include "ShapeRenderComponent.h"

using namespace std;

MainState::MainState(GameStateManager* gameStateManager, Game* game)
	: GameState(gameStateManager, game)
{
}

void MainState::init()
{
	const std::string &resourcePath = "../assets/";

	m_gameObjectManager.init();

	// ROUGH SETUP PROCESS. JUST LOAD GAMEOBJECTS AND THEIR COMPONENTS.

	// lambda closure as helper function to create and add sprite GameObjects
	auto addSpriteHelper = [this](const std::string gameObjectId,
		std::string& resource,
		sf::Color mask_color = sf::Color::Black)
	{
		auto gameObject = make_shared<GameObject>(gameObjectId);
		auto renderComp = make_shared<SpriteRenderComponent>(
			*gameObject,
			m_game->getWindow(),
			resource,
			mask_color);
		gameObject->addComponent(renderComp);

		m_gameObjectManager.addGameObject(gameObject);
		m_renderComponentsVec.push_back(renderComp);
	};

	// load background
	addSpriteHelper("Background", resourcePath + "asteroids_bg.jpg");
	addSpriteHelper("Ship", resourcePath + "ship.png", sf::Color(255, 128, 255));
	addSpriteHelper("Ship2", resourcePath + "ship.png", sf::Color(255, 128, 255));

	// add movement control to sprite (w,a,s,d)
	{
		auto gameObject = m_gameObjectManager.getGameObject("Ship");
		gameObject->addComponent(make_shared<PlayerMoveComponent>(
			*gameObject, 0));
	}
	{
		auto gameObject = m_gameObjectManager.getGameObject("Ship2");
		gameObject->addComponent(make_shared<PlayerMoveComponent>(
			*gameObject, 1));
	}

	// Camera that is tied to the movement of the ship
	// and restricted to the size of the playing field (background)
	{
		auto camera = make_shared<GameObject>("Camera");
		auto renderComp = make_shared<CameraRenderComponent>(
			*camera, m_game->getWindow(), m_game->getWindow().getView());
		auto transformComp = make_shared<TransformCopyComponent>(
			*camera, *m_gameObjectManager.getGameObject("Ship"));

		camera->addComponent(renderComp);
		camera->addComponent(transformComp);

		m_gameObjectManager.addGameObject(camera);
		// make sure the camera is rendered first, so that the transformation is updated
		// correctly for all renderComponents.
		m_renderComponentsVec.insert(m_renderComponentsVec.begin(), renderComp);
	}

	// Initialize GameObjects
	for (auto go : m_gameObjectManager.getGameObjects())
		go.second->init();


	// FINE TUNING OF SETUP. BUILD CONNECTIONS BETWEEN GAMEOBJECTS AND COMPONENTS. SETUP DETAILS
	// GameObjectManager is very powerful and allows you to retreive GameObjects based on their ids
	// and the components contained in the GameObjects. This allows you to fine tune the setup of the game.
	// the following happens here:
	// 1. the background is centered around the origin and scaled up
	// 2. the flippers are moved to locations based on the size and location of the Background (measured offline from image).
	// 3. the ship is centered on the screen and an offset is set for the copy, based on the 
	//    size of the window 
	// comment this part out to see how the basic setup looks, and how the finetuning changes
	// the setup
	{
		auto background_scale = 4.f;
		// center background around origin
		auto background_game_object = m_gameObjectManager.getGameObject("Background");
		auto background_sprite = background_game_object->getComponent<SpriteRenderComponent>();
		auto back_ground_sprite_bounds = background_sprite->getSprite().getLocalBounds();
		background_game_object->scale({ background_scale, background_scale });

		// place ship 
		m_gameObjectManager.getGameObject("Ship")->move(550, 350);
		m_gameObjectManager.getGameObject("Ship2")->move(550, 450);

		// Offset camera view to be centered 
		auto cameraGameObject = m_gameObjectManager.getGameObject("Camera");
		auto cameraCopyTransform = cameraGameObject->getComponent<TransformCopyComponent>();
		cameraCopyTransform->setOffset(-0.5f * sf::Vector2f{ m_game->getWindow().getSize() });
	}

}

void MainState::update(const float delta_time)
{
	if (InputManager::get_instance().isKeyPressed("Exit"))
	{
		mGameStateManager->setState("MenuState");
		return;
	}

	// update remaining game objects
	for (auto goPair : m_gameObjectManager.getGameObjects())
		goPair.second->update(delta_time);
}

void MainState::draw()
{
	for (auto renderComp : m_renderComponentsVec)
		renderComp->draw();
}

void
MainState::exit()
{
	m_gameObjectManager.shutdown();
	m_renderComponentsVec.clear();
}
