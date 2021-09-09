#pragma once

#include <string>
#include "Window.h"

class ChannelDetailsWindow;

template<typename Window, typename T>
class Widget;

struct rdb_t;
struct ckb_t;
struct btn_t;

// a user-defined main window, containing some standalone widgets 
// and 4 sub-regions, each of which includes widgets in group
class MainWindow : public BaseWindow<MainWindow> {
public:
  MainWindow();
  virtual ~MainWindow();

  void Create();
  void testMessageProc();

protected:

  // process functions for standalone widgets
  void cmd_ckbCardEnabled(WID id, int evt, LPARAM lParam);
  void cmd_btnApply(WID id, int evt, LPARAM lParam);

  // process functions for widgets in group
  void cmd_rdbChannelEnabled(WID id, int evt, LPARAM lParam);
  void cmd_edtPrecursor(WID id, int evt, LPARAM lParam);
  void cmd_edtLength(WID id, int evt, LPARAM lParam);
  void cmd_ckbRetrigger(WID id, int evt, LPARAM lParam);
  void cmd_ckbEdgeMode(WID id, int evt, LPARAM lParam);
  void cmd_ckbRising(WID id, int evt, LPARAM lParam);
  void cmd_edtThreshold(WID id, int evt, LPARAM lParam);
  void cmd_edtOffset(WID id, int evt, LPARAM lParam);

  // standalone widgets
  Widget<MainWindow, ckb_t>* ckbCardEnabled;
  Widget<MainWindow, btn_t>* btnApply;

  // widgets in group organized in sub-region
  const int nChannels = 4;     // number of sub-region
  ChannelDetailsWindow* chd;   // pointer to sub-regions
  friend ChannelDetailsWindow;

private:
  // utilities
  // convert from WID id to group index for widgets in sub-region
  size_t indexOfChannelDetailsGroup(std::string label, WID id);
};
