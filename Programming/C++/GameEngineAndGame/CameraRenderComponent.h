#pragma once

#include <SFML/Graphics.hpp>

#include "IRenderComponent.h"

/// Updates the camera/view of the renderwindow. This new camera
/// will be used until another CameraRenderComponent changes it.
/// For positioning the translation component of the gameobject 
/// transform is used.
/// Currently does not support rotation.
class CameraRenderComponent : public IRenderComponent
{
public:
	using ptr = std::shared_ptr<CameraRenderComponent>;

	/// \param view the camera specifications.
	CameraRenderComponent(GameObject& game_object,
		RenderWindow& render_window,
		View view);

	bool init() override;
	void update(float deltaTime) override;
	void draw() override;

private:
	/// the current camera specifications
	View m_view;
	Vector2f m_initialCenter;
};