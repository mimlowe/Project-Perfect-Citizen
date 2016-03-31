#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Engine/renderComponent.h"
#include <string>
#include "../Engine/InputHandler.h"

namespace ppc {

	///////////////////////////////////////////////////////////////////////
	/// @brief Designated Generic Builder Object for Buttons
	/// @author Alex Vincent 
	/// @details A package with API function calls allowing for individual
	/// creations and augmentations of a button. This augments and returns 
	///////////////////////////////////////////////////////////////////////
	class ButtonBuilder {
	private:
		int sheetX;
		int sheetY;
		int width;
		int frames;
		int size;

		float posX;
		float posY;

		sf::Sprite* sprtUp;
		sf::Sprite* sprtDown;

		sf::Image* spriteSheet; 
		ppc::InputHandler* inputHandle;

	public:
		///////////////////////////////////////////////////////////////////////
		/// @brief Constructor for buttonRenderComponent
		/// @details Creates a default button
		///////////////////////////////////////////////////////////////////////
		ButtonBuilder();

		~ButtonBuilder();

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the down and up sprite when the button is pressed
		///////////////////////////////////////////////////////////////////////
		void setSpritesByIndicies(int x, int y, int r, int f);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the down and up sprite when the button is pressed
		///////////////////////////////////////////////////////////////////////
		void setSprites(sf::Sprite&, sf::Sprite&);

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the function the button will execute when pressed
		///////////////////////////////////////////////////////////////////////
		void setFunction();

		///////////////////////////////////////////////////////////////////////
		/// @brief Set the position of the button
		///////////////////////////////////////////////////////////////////////
		void setButtonPosition(float x, float y);

		void setButtonPosition(sf::Vector2f pos);

		void setSpriteSheet(sf::Image&);

		void setInputHandle(ppc::InputHandler&);
		///////////////////////////////////////////////////////////////////////
		/// @brief Returns the constructed button
		///////////////////////////////////////////////////////////////////////
		void create(Entity&);

	};


};
