#pragma once

#include "typedef.h"
#include <map>
// base class of Window
template <typename DerivedWindow>
class BaseWindow {
public:
  BaseWindow() {}
  virtual ~BaseWindow() {}

  // when message received, map the id of the widget to 
  // the processing function defined in the derived window class
  typedef void (DerivedWindow::* CmdFunc)(WID, int, LPARAM);
  void bind(WID id, CmdFunc func) {
    mapCmdFunc.insert(std::make_pair(id, func));
  }
  // process according to the widget's id
  void cmdProcess(WID id, int evt, LPARAM lParam) {
    (static_cast<DerivedWindow*>(this)->*mapCmdFunc[id])(id, evt, lParam);
  }

private:
  std::map<WID, CmdFunc> mapCmdFunc;
};
