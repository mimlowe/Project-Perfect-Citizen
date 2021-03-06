#include "../Engine/debug.h"
#include "TextBoxRenderComponent.h"


using namespace std;

TextBoxRenderComponent::TextBoxRenderComponent(sf::Font& f, sf::Color c,
	float x,
	float y,
	int s,
	string str) : font(f) {

	this->text = new sf::Text();
	this->outline = new sf::Text();

	labelString = str;

	size_t pos = 0;

	for (unsigned int i = 0, j = 0; i < labelString.size(); ++i, ++j) {
		if (labelString.at(i) == '_' && j > 5) {
			labelString.insert(i, "\n");
			i++;
			j = 0;
		}
	}

	text->setFont(font);
	text->setPosition(x, y);
	text->setCharacterSize(s);
	text->setColor(c);
	text->setString(labelString);

	outline->setFont(font);
	outline->setPosition(x + 2, y);
	outline->setCharacterSize(s);
	if (text->getColor() == sf::Color::Black)
		outline->setColor(sf::Color::White);
	else outline->setColor(sf::Color::Black);
	outline->setString(labelString);

}

TextBoxRenderComponent::~TextBoxRenderComponent() {
	delete text;
	delete outline;
}

void TextBoxRenderComponent::updateLabelPosition(float x, float y) {
	text->setPosition(x, y);
}

void TextBoxRenderComponent::updateLabelSize(int s) {
	text->setCharacterSize(s);
}

void TextBoxRenderComponent::updateLabelString(string str) {
	labelString = str;
	outline->setString(labelString);
}

void TextBoxRenderComponent::draw(sf::RenderTarget& target,
	sf::RenderStates states) const {
	target.draw(*(this->outline), states);
	target.draw(*(this->text), states);
}