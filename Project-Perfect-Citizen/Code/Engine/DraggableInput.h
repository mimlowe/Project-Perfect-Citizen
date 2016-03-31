#ifndef DRAGGABLE_INPUT_H
#define DRAGGABLE_INPUT_H

#include "inputComponent.h"
#include "subject.h"
#include <SFML/Graphics/Rect.hpp>

namespace sf {
    class Transformable;
}

namespace ppc {

class WindowInterface;

class DraggableInput : public InputComponent {
public:

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    DraggableInput() = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Window Dragging Constructor.
    ///////////////////////////////////////////////////////////////////
    DraggableInput(WindowInterface& win);

    ///////////////////////////////////////////////////////////////////
    /// @brief Transformable Dragging Constructor.
    ///////////////////////////////////////////////////////////////////
    DraggableInput(sf::Transformable& trans);

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor.
    ///////////////////////////////////////////////////////////////////
    virtual ~DraggableInput();


  /////////////////////////////////////////////////////////////////////
  // Setters
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the bounds to check clicks against.
    ///////////////////////////////////////////////////////////////////
    void setBounds(const sf::FloatRect& bounds);

    ///////////////////////////////////////////////////////////////////
    /// @brief Sets the bounds to clamp the object to, given it's local
    ///     space.
    ///////////////////////////////////////////////////////////////////
    void setClampBounds(const sf::FloatRect& clamp);

    ///////////////////////////////////////////////////////////////////
    /// @brief Removes the clamp from the draggable.
    ///////////////////////////////////////////////////////////////////
    void removeClamp();

    
  /////////////////////////////////////////////////////////////////////
  // Input Function
  /////////////////////////////////////////////////////////////////////

    bool registerInput(sf::Event& ev);


  /////////////////////////////////////////////////////////////////////
  // Subject Functionality
  /////////////////////////////////////////////////////////////////////

    Subject& onDrag();


private:

  /////////////////////////////////////////////////////////////////////
  // Priavate Helpers
  /////////////////////////////////////////////////////////////////////

    void clamp();

    void drag(const sf::Vector2f& delta);


  /////////////////////////////////////////////////////////////////////
  // Private Members
  /////////////////////////////////////////////////////////////////////

    bool isDragging_;
    bool isClamped_;

	int startX_;
	int startY_;

    sf::FloatRect bounds_;
    sf::FloatRect clamp_;

    bool isWindow_;

    union {
        WindowInterface* win_;
        sf::Transformable* trans_;
    };

    Subject onDrag_;


};


};      //namespace ppc


#endif  //DRAGGABLE_INPUT_H
