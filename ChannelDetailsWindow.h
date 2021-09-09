#pragma once

#include <map>
#include <vector>
#include <string>

#include "Widget.h"

class MainWindow;

// widgets in group as a sub-window, which will reside on the MainWindow
class ChannelDetailsWindow {
public:
  ChannelDetailsWindow();
  virtual ~ChannelDetailsWindow();

  virtual void Create(MainWindow* wnd, int x, int y);

  std::map<std::string, BaseWidget<MainWindow>*> w;
  std::vector<BaseWidget<MainWindow>*> ws; // widgets of sequence

  typedef void (MainWindow::* CmdFunc)(WID, int, LPARAM);
  std::vector<CmdFunc> wsCmdFunc;
};
