#ifndef PPC_CMPNT_INPUT
#define PPC_CMPNT_INPUT

#include "ppc_entity.h"

//TODO: Input Components should eventually handle Observers

namespace ppc {

///////////////////////////////////////////////////////////////////////
/// @brief Input Component Interface
///////////////////////////////////////////////////////////////////////
class InputComponent {
public:

  /////////////////////////////////////////////////////////////////////
  // Memory Management
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Initializes an Input Component
    /// @details Resets the Component to its initial state.
    /// @post Returns the Component to its initial state so it can be
    ///     reused.
    ///////////////////////////////////////////////////////////////////
    virtual InputComponent* init() = 0;

    ///////////////////////////////////////////////////////////////////
    /// @brief Virtual Destructor
    ///////////////////////////////////////////////////////////////////
    virtual ~InputComponent() {};


  /////////////////////////////////////////////////////////////////////
  // Input Component Interface
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Register Input
    /// @details This is the function called to update the Component
    ///     given the new Input State. It will be called once per Input
    ///     update step.
    ///////////////////////////////////////////////////////////////////
    virtual void update() = 0;


private:

    //Private Constructor to prevent instantiation
    InputComponent(Entity* entityPtr = nullptr);

    Entity* entity;

};


};      //End namespace ppc


#endif  //PPC_CMPNT_INPUT