#include "debug.h"
#include "Window.h"

#include <cstddef>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "inputComponent.h"
#include "updateComponent.h"
#include "renderComponent.h"

using namespace ppc;


///////////////////////////////////////////////////////////////////////
// Constructors and Destructor
///////////////////////////////////////////////////////////////////////

Window::Window(unsigned int width, 
               unsigned int height, 
               sf::Color col) : 
            windowSpace_() {
    windowSpace_.create(width, height);
    backgroundColor_ = col;
	inputHandler_ = InputHandler();
}




Window::Window(const sf::Vector2u& size,
               sf::Color col) :
        Window(size.x, size.y, col) {}




Window::Window(const Window& other) :
    windowSpace_() {
    sf::Vector2u windowSize = other.windowSpace_.getSize();
    windowSpace_.create(windowSize.x, windowSize.y);
}




Window::~Window() {
    for (unsigned int i = 0; i < inputcmpnts_.size(); ++i) {
        delete inputcmpnts_[i];
        inputcmpnts_[i] = nullptr;
    }
    for (auto uc : updatecmpnts_) {
        delete uc;
        uc = nullptr;
    }
    for (auto rc : rendercmpnts_) {
        delete rc;
        rc = nullptr;
    }
}




///////////////////////////////////////////////////////////////////////
// Space Getters
///////////////////////////////////////////////////////////////////////

sf::Vector2u Window::getSize() const {
    return windowSpace_.getSize();
}




sf::FloatRect Window::getBounds() const {
    sf::FloatRect result;
    result.left = transform_.getPosition().x;
    result.top = transform_.getPosition().y;
    result.width = float(windowSpace_.getView().getSize().x);
    result.height = float(windowSpace_.getView().getSize().y);
    return result;
}


///////////////////////////////////////////////////////////////////////
// Space Setters
///////////////////////////////////////////////////////////////////////

void Window::setSize(unsigned int width, unsigned int height) {
    windowSpace_.create(width, height);
    trimEntities();
}



/////////////////////////////////////////////////////////////////////
// View Manipulation
/////////////////////////////////////////////////////////////////////

const sf::View& Window::getView() const {
    return windowSpace_.getView();
}



void Window::setView(const sf::View& view) {
    windowSpace_.setView(view);

}



const sf::View& Window::getDefaultView() {
    return windowSpace_.getDefaultView();
}




///////////////////////////////////////////////////////////////////////
// Transformation Setters
///////////////////////////////////////////////////////////////////////

void Window::setPosition(float x, float y) {
    transform_.setPosition(x, y);
}

void Window::move(float x, float y) {
    transform_.move(x, y);
}

void Window::setScale(float x, float y) {
    transform_.setScale(x, y);
}

void Window::scale(float x, float y) {
    transform_.scale(x, y);
}


///////////////////////////////////////////////////////////////////////
// Transformation Getters
///////////////////////////////////////////////////////////////////////

sf::Vector2f Window::getPosition() const {
    return transform_.getPosition();
}

sf::Vector2f Window::getScale() const {
    return transform_.getScale();
}


///////////////////////////////////////////////////////////////////////
// Step Functionality
///////////////////////////////////////////////////////////////////////

void Window::addInputComponent(InputComponent* inputcmpnt) {
    if (inputcmpnt != nullptr) {
        inputcmpnts_.push_back(inputcmpnt);
    }
}




void Window::addRenderComponent(RenderComponent* rendercmpnt) {
    if (rendercmpnt != nullptr) {
        rendercmpnts_.push_back(rendercmpnt);
    }
}




void Window::addUpdateComponent(UpdateComponent* updatecmpnt) {
    if (updatecmpnt != nullptr) {
        updatecmpnts_.push_back(updatecmpnt);
    }
}




void Window::addEntity(Entity& entity) {
	
    //Stores the current index we're on
    size_t i = 0;
    //Stores the number of components we haven't found
    size_t toFind = entity.cmpntCount();

    //While we have more to find and more component* in the Entity:
    while ((toFind > 0) && (i < Entity::maxComponentCount)) {
        //Get the Component at the index
        Component* cmpnt = entity.getComponent(i);

        //If there is a Component at the point in question:
        if (cmpnt != nullptr) {
            //Test if it is an inputComponent
            if (dynamic_cast<InputComponent*>(cmpnt) != nullptr) {
                inputcmpnts_.push_back(dynamic_cast<InputComponent*>(cmpnt));
            //Test if it is an updateComponent
            } else if (dynamic_cast<UpdateComponent*>(cmpnt) != nullptr) {
                updatecmpnts_.push_back(dynamic_cast<UpdateComponent*>(cmpnt));
            //Test if it is a renderComponent
            } else if (dynamic_cast<RenderComponent*>(cmpnt) != nullptr) {
                rendercmpnts_.push_back(dynamic_cast<RenderComponent*>(cmpnt));
            }
        }

        //Search the next index
        ++i;
    }

    entityVec_.push_back(std::move(entity));
}



///////////////////////////////////////////////////////////////////////
// Other Getters
///////////////////////////////////////////////////////////////////////

InputHandler& Window::getInputHandler() {
    return inputHandler_;
}




///////////////////////////////////////////////////////////////////////
// Step Functionality
///////////////////////////////////////////////////////////////////////

void Window::update(sf::Time& deltaTime) {
    //Loop over all updateComponents
    for (UpdateComponent* c : updatecmpnts_) {
        c->update(deltaTime);
    }
}




void Window::registerInput(sf::Event ev) {
    sf::Vector2f click;
    sf::FloatRect viewRect;
    sf::View currView = windowSpace_.getView();
    sf::Vector2f defaultViewPos = windowSpace_.getView().getSize();
    defaultViewPos.x /= 2.0f;
    defaultViewPos.y /= 2.0f;

    switch (ev.type) {
    case sf::Event::MouseButtonPressed:
    case sf::Event::MouseButtonReleased:
        click = {float(ev.mouseButton.x), float(ev.mouseButton.y) };
        viewRect.width = currView.getSize().x;
        viewRect.height = currView.getSize().y;
        mouseInView_ = viewRect.contains(click);
        if (mouseInView_) {
            click -= defaultViewPos;
            click += currView.getCenter();
            ev.mouseButton.x = int(click.x);
            ev.mouseButton.y = int(click.y);
        }
        break;
    case sf::Event::MouseMoved:
        if (mouseInView_) {
            click = { float(ev.mouseMove.x), float(ev.mouseMove.y) };
            click -= defaultViewPos;
            click += currView.getCenter();
            ev.mouseMove.x = int(click.x);
            ev.mouseMove.y = int(click.y);
        }
        break;
    }

    inputHandler_.registerEvent(ev);
}




void Window::refresh(sf::RenderStates states) {
    //Clear Window to Background Color
    windowSpace_.clear(backgroundColor_);

    //Draws all objects in the window
    for (RenderComponent* c : rendercmpnts_) {
        windowSpace_.draw(*c, states);
    }

    windowSpace_.display();
}




void Window::draw(sf::RenderTarget& target,
                  sf::RenderStates states) const {
    //Create a sprite off of the windowSpace_
    sf::Sprite spr;
    spr.setTexture(windowSpace_.getTexture());
    sf::Vector2f viewSize = windowSpace_.getView().getSize();
    sf::Vector2f viewScale;
    viewScale.x = viewSize.x / windowSpace_.getSize().x;
    viewScale.y = viewSize.y / windowSpace_.getSize().y;
    spr.scale(viewScale);

    states.transform *= transform_.getTransform();

    //Draw the sprite
    target.draw(spr, states);
}




///////////////////////////////////////////////////////////////////////
/// Helper Functions
///////////////////////////////////////////////////////////////////////

void Window::trimEntities() {
    //For all entites:
    for (auto i = entityVec_.begin(); i != entityVec_.end();) {
        sf::Vector2f pos = i->getPosition();
        sf::Vector2u size = windowSpace_.getSize();

        //If that entity is not in the WindowSpace
        if ((pos.x >= size.x) || (pos.y >= size.y) || (pos.x < 0) ||
                (pos.y < 0)) {
            //Remove the Entity
            deleteEntity(i);

        } else { 
            ++i; 
        }
    }
}




void Window::deleteEntity(std::vector<Entity>::iterator entityIt) {
    //Loop over the Components in the Entity
    for (size_t c = 0; c < Entity::maxComponentCount; ++c) {
        Component* cmpnt = entityIt->getComponent(c);
        //If there is a Componentn in this slot:
        if (cmpnt != nullptr) {
            delete cmpnt;
            removeComponent(cmpnt);
        }
    }

    //Remove the Entity
    entityVec_.erase(entityIt);
}




void Window::removeComponent(Component* cmpntPtr) {
    //Test if it is an inputComponent
    if (dynamic_cast<InputComponent*>(cmpntPtr) != nullptr) {
        auto cmpntIt = std::find(inputcmpnts_.begin(),
            inputcmpnts_.end(),
            dynamic_cast<InputComponent*>(cmpntPtr));
        //Delete if found
        if (cmpntIt != inputcmpnts_.end()) {
            inputcmpnts_.erase(cmpntIt);
        }
        //Test if it is an updateComponent
    } else if (dynamic_cast<UpdateComponent*>(cmpntPtr) != nullptr) {
        auto cmpntIt = std::find(updatecmpnts_.begin(),
            updatecmpnts_.end(),
            dynamic_cast<UpdateComponent*>(cmpntPtr));
        //Delete if found
        if (cmpntIt != updatecmpnts_.end()) {
            updatecmpnts_.erase(cmpntIt);
        }
        //Test if it is a renderComponent
    } else if (dynamic_cast<RenderComponent*>(cmpntPtr) != nullptr) {
        auto cmpntIt = std::find(rendercmpnts_.begin(),
            rendercmpnts_.end(),
            dynamic_cast<RenderComponent*>(cmpntPtr));
        //Delete if found
        if (cmpntIt != rendercmpnts_.end()) {
            rendercmpnts_.erase(cmpntIt);
        }
    }
}
