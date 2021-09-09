#include "MainWindow.h"
#include "ChannelDetailsWindow.h"
#include "Widget.h"

#include <iostream>
using std::cout;
using std::endl;

// MainWindow Implementations

MainWindow::MainWindow() {
  ckbCardEnabled = new Widget<MainWindow, ckb_t>;
  btnApply = new Widget<MainWindow, btn_t>;
  chd = new ChannelDetailsWindow[nChannels];
}

MainWindow::~MainWindow() {
  delete ckbCardEnabled;
  delete btnApply;
  delete[] chd;
}

void MainWindow::Create() {
  // create widgets, and register their individual process functions
  // standalone widgets
  ckbCardEnabled->Create(this, 100, 100, &MainWindow::cmd_ckbCardEnabled);
  btnApply->Create(this, 200, 100, &MainWindow::cmd_btnApply);
  // widget in group
  for (int i = 0; i < nChannels; i++)
    chd[i].Create(this, 100, 200);
}

void MainWindow::testMessageProc() {
  // when receiving message, dispatch to relevant process function according to widget id
  // in WinAPI£Ỳid = LOWORD(wParam) under the message WM_COMMAND,
  // which is unique of WID type as specified by SendMessage
  cmdProcess(btnApply->id, 20, 200); // test standalong widgets
  cmdProcess(chd[2].w["rdbChannelEnabled"]->id, 12, 300); // test widget in group
}

size_t MainWindow::indexOfChannelDetailsGroup(std::string label, WID id) {
  return (id - chd[0].w[label]->id) / chd[0].w.size();
}

// process functions

void MainWindow::cmd_ckbCardEnabled(WID id, int evt, LPARAM lParam) {
  cout << "ckbCardEnabled clicked!" << endl;
}
void MainWindow::cmd_btnApply(WID id, int evt, LPARAM lParam) {
  cout << "btnApply clicked!" << endl;
}

// process functions for widget in group

void MainWindow::cmd_rdbChannelEnabled(WID id, int evt, LPARAM lParam) {
  int i = indexOfChannelDetailsGroup("rdbChannelEnabled", id);
  cout << "rdbChannelEnabled " << i << " in chd is clicked!" << endl;
}
void MainWindow::cmd_edtPrecursor(WID id, int evt, LPARAM lParam) {
  int i = indexOfChannelDetailsGroup("edtPrecursor", id);
  cout << "edtPrecursor in chd " << i << " is clicked!" << endl;
}
void MainWindow::cmd_edtLength(WID id, int evt, LPARAM lParam) {
  int i = indexOfChannelDetailsGroup("edtLength", id);
  cout << "edtLength in chd " << i << " is clicked!" << endl;
}
void MainWindow::cmd_ckbRetrigger(WID id, int evt, LPARAM lParam) {
  int i = indexOfChannelDetailsGroup("ckbRetrigger", id);
  cout << "ckbRetrigger in chd " << i << " is clicked!" << endl;
}
void MainWindow::cmd_ckbEdgeMode(WID id, int evt, LPARAM lParam) {
  int i = indexOfChannelDetailsGroup("ckbEdgeMode", id);
  cout << "ckbEdgeMode in chd " << i << " is clicked!" << endl;
}
void MainWindow::cmd_ckbRising(WID id, int evt, LPARAM lParam) {
  int i = indexOfChannelDetailsGroup("ckbRising", id);
  cout << "ckbRising in chd " << i << " is clicked!" << endl;
}
void MainWindow::cmd_edtThreshold(WID id, int evt, LPARAM lParam) {
  int i = indexOfChannelDetailsGroup("edtThreshold", id);
  cout << "edtThreshold in chd " << i << " is clicked!" << endl;
}
void MainWindow::cmd_edtOffset(WID id, int evt, LPARAM lParam) {
  int i = indexOfChannelDetailsGroup("edtOffset", id);
  cout << "edtOffset in chd " << i << " is clicked!" << endl;
}

