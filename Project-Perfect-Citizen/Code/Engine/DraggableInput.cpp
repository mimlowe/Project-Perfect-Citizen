#include "../Engine/debug.h"
#include "DraggableInput.h"

using namespace ppc;

///////////////////////////////////////////////////////////////////////
// Constructors & Destructor
///////////////////////////////////////////////////////////////////////

DraggableInput::DraggableInput(WindowInterface& win) : 
                               InputComponent(3) {
    //Set Private Variables
    isDragging_ = false;
    isWindow_ = true;
    win_ = &win;
    startX_ = 0;
    startY_ = 0;
}




DraggableInput::DraggableInput(sf::Transformable& trans) :
                               InputComponent(3) {
    //Set Private Variables
    isDragging_ = false;
    isWindow_ = false;
    trans_ = &trans;
}




DraggableInput::~DraggableInput() {

}




///////////////////////////////////////////////////////////////////////
// Setters
///////////////////////////////////////////////////////////////////////

void DraggableInput::setBounds(const sf::FloatRect& bounds) {
    bounds_ = bounds;
}




///////////////////////////////////////////////////////////////////////
// Input Function
///////////////////////////////////////////////////////////////////////

bool DraggableInput::registerInput(sf::Event& ev) {
    //If we have a mousePress
    if (ev.type == ev.MouseButtonPressed) {

        sf::Vector2f mousePos(float(ev.mouseButton.x), 
                              float(ev.mouseButton.y));
		
        //See if it was a left click in bounds
        if ((ev.mouseButton.button == sf::Mouse::Left) &&
            (bounds_.contains(mousePos))) {
			DEBUGF("ni", "x: " << mousePos.x << " y: " << mousePos.y);
            //Set the flag to true
			startX_ = ev.mouseButton.x;
			startY_ = ev.mouseButton.y;
            isDragging_ = true;
			DEBUGF("ni", isDragging_);
        }

    //If we have a mouseRelease
    } else if (ev.type == ev.MouseButtonReleased) {

        if (ev.mouseButton.button == sf::Mouse::Left){
            isDragging_ = false;
        }

    } else if (ev.type == ev.MouseMoved) {
		int endX_ = ev.mouseMove.x;
		int endY_ = ev.mouseMove.y;
		//DEBUGF("ni", "MOVING");
        //See if we're dragging
        if (isDragging_) {
			DEBUGF("ni", "Y R WE NOT MOVING");
            sf::Vector2f shift(float(endX_ - startX_),
                               float(endY_ - startY_));
            //If we're pointing to a Window:
            if (isWindow_) {
                win_->move(shift);
                startX_ = endX_ - shift.x;
                startY_ = endY_ - shift.y;
            //Else if we're pointing to a Transformable
            } else {
				trans_->move(shift);
				bounds_.left += shift.x;
				bounds_.top += shift.y;
				startX_ = endX_;
				startY_ = endY_;
            }
        }

        return false;
    }

    return true;
}
