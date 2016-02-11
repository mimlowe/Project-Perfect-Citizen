
#pragma once

#include <SFML/Graphics.hpp>

#include "updateComponent.h"
#include "buttonRenderComponent.h"

using namespace std;

///////////////////////////////////////////////////////////////////////
/// @brief Designated Animator Component for an animated Button Renderer
/// @author Michael Lowe
/// @details The Animator Component updates the frame for
///          Button Render Components that have more than two states
///////////////////////////////////////////////////////////////////////

class animatorComponent : public ppc::UpdateComponent {
    
private:
    buttonRenderComponent *render;
    float speed;
    sf::Time counter;
    sf::Time framePeriod;
public:
    animatorComponent();
    animatorComponent(buttonRenderComponent& r, float s);
    ~animatorComponent();
    void update(sf::Time& deltaTime) override;

};

