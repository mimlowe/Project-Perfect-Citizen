#include "ButtonBuilder.h"
#include "buttonRenderComponent.h"
#include "../Game/mousePressButton.h"
#include "../Engine/debug.h"
#include <ostream>
#include "TextDisplayRenderComponent.h"

ppc::ButtonBuilder::ButtonBuilder() 
{
	sheetX = 0;
	sheetY = 0;
	width = 0;
	frames = 0;
	size = 1;

	posX = 0.f;
	posY = 0.f;

	sprtUp = nullptr;
	sprtDown = nullptr;

	spriteSheet = nullptr;
	inputHandle = nullptr;

	label = "";
}

ppc::ButtonBuilder::~ButtonBuilder()
{
}

void ppc::ButtonBuilder::setSpritesByIndicies(int x, int y, int r, int f)
{
	sheetX = x;
	sheetY = y;
	width = r;
	frames = f;
}

void ppc::ButtonBuilder::setSize(float s) {
	size = s;
}

void ppc::ButtonBuilder::setNonClickable() {
	clickable = false;
}

void ppc::ButtonBuilder::setButtonPosition(float x, float y)
{
	posX = x;
	posY = y;
}

void ppc::ButtonBuilder::setButtonPosition(sf::Vector2f pos)
{
	posX = pos.x;
	posY = pos.y;
}

void ppc::ButtonBuilder::setLabelMessage(std::string l) 
{
	label = l;
}

void ppc::ButtonBuilder::setLabelFont(sf::Font& f)
{
	font = &f;
}

void ppc::ButtonBuilder::setLabelSize(int lS)
{
	labelSize = lS;
}

void ppc::ButtonBuilder::setSpriteSheet(sf::Image& sheet)
{
	spriteSheet = &sheet;
}

void ppc::ButtonBuilder::setInputHandle(ppc::InputHandler& ih)
{
	inputHandle = &ih;
}

void ppc::ButtonBuilder::create(Entity& e){

	/* I: RENDER COMPONENTS */
	buttonRenderComponent* buttonRender = nullptr;
	TextDisplayRenderComponent* labelRender = nullptr;
	mousePressButton* mpb = nullptr;
		
	/* Case: Custom Buttom depending on whether there is one or more character */
	if (label.compare("") != 0) {
		if (label.size() > 1) buttonRender = new buttonRenderComponent(*spriteSheet, 4, 1, 2, 1);
		else buttonRender = new buttonRenderComponent(*spriteSheet, 6, 3, 1, 1);

		/* Construct the Custom Button*/
		labelRender = new TextDisplayRenderComponent(*font, sf::Color::Black, posX, posY, labelSize, label);

		/* Determine the position where the text should be placed in this button */
		float buttonWidth = (buttonRender->getSprite()->getLocalBounds().width) * size;
		float buttonHeight = (buttonRender->getSprite()->getLocalBounds().height) * size;

		sf::FloatRect textRect = labelRender->getText()->getLocalBounds();

		labelRender->getText()->setOrigin(textRect.left + textRect.width / 2.0f,
			textRect.top + textRect.height / 2.0f);

		labelRender->updatePosition(posX + (buttonWidth / 2.0f),
			posY + (buttonHeight / 2.0f));

	}
	/* Default: Button from Sprite Sheet Indicies */
	else {
		buttonRender = new buttonRenderComponent(*spriteSheet, sheetX, sheetY, width, frames);
	}

	/* Set the position for the bounds */
	buttonRender->setImageScale(size, size);
	buttonRender->renderPosition(sf::Vector2f(posX, posY));

	/* II: INPUT COMPONENT */
	if (clickable) {
		mpb = new mousePressButton(*inputHandle, buttonRender->getSprite()->getGlobalBounds(), "GENERIC_BUTTON");
	}
	
	/* III: DECORATING THE ENTITY */
	e.addComponent(buttonRender);
	if(labelRender != nullptr) e.addComponent(labelRender);
	if( mpb != nullptr) e.addComponent(mpb);
	buttonRender->renderPosition(sf::Vector2f(posX, posY));

}
