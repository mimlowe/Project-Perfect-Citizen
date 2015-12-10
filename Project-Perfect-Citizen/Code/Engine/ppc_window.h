#ifndef PPC_WINDOW_H
#define PPC_WINDOW_H




namespace ppc {

class Computer;

// TODO: Implement Window class. Flesh out details via Doxygen.
///////////////////////////////////////////////////////////////////////
/// @brief Defines an in-game window object
/// @details 
///////////////////////////////////////////////////////////////////////
class Window {

  /////////////////////////////////////////////////////////////////////
  // Constructors & Destructor
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief No Default Constructor
    /// @details The Window class is dependent on defining its 'theme'
    ///     via parameters or via the Computer it is created in. For
    ///     now, we have no way of finding the current Computer, so we
    ///     must take this information in via constructor arguments
    ///////////////////////////////////////////////////////////////////
    Window() = delete;

    ///////////////////////////////////////////////////////////////////
    /// @brief Copy Constructor
    ///////////////////////////////////////////////////////////////////
    Window(const Window& other);

    ///////////////////////////////////////////////////////////////////
    /// @brief Move Constructor
    ///////////////////////////////////////////////////////////////////
    Window(Window&& other);

    ///////////////////////////////////////////////////////////////////
    /// @brief Computer Constuctor
    ///////////////////////////////////////////////////////////////////
    //Window(Computer&& other);

    ///////////////////////////////////////////////////////////////////
    /// @brief Default Destructor
    ///////////////////////////////////////////////////////////////////
    ~Window();



  /////////////////////////////////////////////////////////////////////
  // Operators
  /////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////
    /// @brief Copy Assignment Operator
    ///////////////////////////////////////////////////////////////////
    Window& operator=(const Window& other);

    ///////////////////////////////////////////////////////////////////
    /// @brief Move Assignment Operator
    ///////////////////////////////////////////////////////////////////
    Window& operator=(Window&& other);



  /////////////////////////////////////////////////////////////////////
  // 
  /////////////////////////////////////////////////////////////////////



};


}   //End namespace ppc


#endif  //End PPC_WINDOW_H

