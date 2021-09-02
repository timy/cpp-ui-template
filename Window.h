#pragma once

#include <map>

// base class of Window
template <typename DerivedWindow>
class BaseWindow {
public:
  BaseWindow() {}
  virtual ~BaseWindow() {}

  // when message received, map the id of the widget to 
  // the processing function defined in the derived window class
  typedef void (DerivedWindow::* CmdFunc)(int, LPARAM);
  void bind(HMENU id, CmdFunc func) {
    mapCmdFunc.insert(std::make_pair(id, func));
  }
  // invoke process function according to the widget's id
  void cmdProcess(HMENU id, int evt, LPARAM lParam) {
    (static_cast<DerivedWindow*>(this)->*mapCmdFunc[id])(evt, lParam);
  }

private:
  std::map<HMENU, CmdFunc> mapCmdFunc;
};
