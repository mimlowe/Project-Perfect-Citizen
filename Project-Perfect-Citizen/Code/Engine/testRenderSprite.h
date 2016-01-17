#pragma once
#include <SFML/Graphics.hpp>
#include "render_component.h"
#include <string>
using namespace std;
class TestRenderSprite : public RenderComponent {
private:
	int privatePlaceholder;
	sf::Sprite* sprite;
	sf::Texture* texture;
public:
	TestRenderSprite(string filename);
	void render(sf::RenderWindow* wnd);
	sf::Sprite* getSprite();
};