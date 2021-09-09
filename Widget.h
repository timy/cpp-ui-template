#pragma once

#include "typedef.h"

class AbstractWidget {
public:
  AbstractWidget() { id = counter++; } // automatically assigned unique id for each widget
  virtual ~AbstractWidget() {}

  WID id; // id may be used when invoking SendMessage
private:
  static WID counter; // counter for id
};

// base class of widget
// Since a widget must reside on a window, it needs know the type of parent window and its pointer.
// Each widget should be associated to a process function, which will be called by the parent window.
template <typename Window>
class BaseWidget : public AbstractWidget {
public:
  BaseWidget() : AbstractWidget() {} 
  virtual ~BaseWidget() {}

  // the prototype of process function defined in derived window class
  typedef void (Window::* CmdFunc)(WID, int, LPARAM);
  virtual void Create(Window* wnd, int x, int y, CmdFunc func) {
    wnd->bind(id, func); // map: id -> process function
  }
};

// general template of widget
template <typename Window, typename T>
class Widget : public BaseWidget<Window> {
public:
  Widget() {}
  virtual ~Widget() {}
  virtual void Create(Window* wnd, int x, int y) {
    BaseWidget<Window>::Create(wnd, x, y, nullptr);
  }
};

// different types of widgets
struct btn_t {}; // button
struct rdb_t {}; // radiobox
struct ckb_t {}; // checkbox
struct edt_t {}; // edit

// classes for different types of widgets
template <typename Window>
class Widget<Window, rdb_t> : public BaseWidget<Window> { // Radiobutton
public:
  virtual void Create(Window* wnd, int x, int y, typename BaseWidget<Window>::CmdFunc func) {
    // create some actual radiobutton here ...
    BaseWidget<Window>::Create(wnd, x, y, func);
  }
};

template <typename Window>
class Widget<Window, edt_t> : public BaseWidget<Window> { // Edit
public:
  virtual void Create(Window* wnd, int x, int y, typename BaseWidget<Window>::CmdFunc func) {
    // create some actual edit here ...
    BaseWidget<Window>::Create(wnd, x, y, func);
  }
};

template <typename Window>
class Widget<Window, ckb_t> : public BaseWidget<Window> { // Checkbox
public:
  virtual void Create(Window* wnd, int x, int y, typename BaseWidget<Window>::CmdFunc func) {
    // create some actual checkbox here ...
    BaseWidget<Window>::Create(wnd, x, y, func);
  }
};

template <typename Window>
class Widget<Window, btn_t> : public BaseWidget<Window> { // Button
public:
  virtual void Create(Window* wnd, int x, int y, typename BaseWidget<Window>::CmdFunc func) {
    // create some actual button here ...
    BaseWidget<Window>::Create(wnd, x, y, func);
  }
};
