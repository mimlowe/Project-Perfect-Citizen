#pragma once

#include <SFML/Graphics.hpp>
#include "../Engine/updateComponent.h"
#include "buttonRenderComponent.h"
#include "textInputRenderComponent.hpp"
#include "textInputKeys.hpp"
#include "../Engine/NodeState.h"
#include <iostream>

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Update Component for a button
/// @author Alex Vincent
/// @details Updates render position of a button
///////////////////////////////////////////////////////////////////////

class buttonUpdateComponent : public ppc::UpdateComponent {

private:
	buttonRenderComponent& buttonToUpdate_;
	sf::Vector2f lastPosition_;
	

public:

	///////////////////////////////////////////////////////////////////////
	/// @brief Default constructor
	///////////////////////////////////////////////////////////////////////
	buttonUpdateComponent(buttonRenderComponent& bRC);


	///////////////////////////////////////////////////////////////////////
	/// @brief Default destructor
	///////////////////////////////////////////////////////////////////////
	~buttonUpdateComponent();

	///////////////////////////////////////////////////////////////////////
	/// @brief Sets the new button position
	///////////////////////////////////////////////////////////////////////
	void setButtonPosition(sf::Vector2f newPos);

	///////////////////////////////////////////////////////////////////////
	/// @brief Overridden update function of all update components.
	/// Calls renderPosition of the private button
	///////////////////////////////////////////////////////////////////////
	void update(sf::Time& deltaTime) override;

};
