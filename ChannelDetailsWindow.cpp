#include "MainWindow.h"
#include "Widget.h"
#include "ChannelDetailsWindow.h"

// ChannelDetailsWindow Implementations

ChannelDetailsWindow::ChannelDetailsWindow() {
  ws.push_back(w["rdbChannelEnabled"] = new Widget<MainWindow, rdb_t>);
  wsCmdFunc.push_back(&MainWindow::cmd_rdbChannelEnabled);
  ws.push_back(w["edtPrecursor"] = new Widget<MainWindow, edt_t>);
  wsCmdFunc.push_back(&MainWindow::cmd_edtPrecursor);
  ws.push_back(w["edtLength"] = new Widget<MainWindow, edt_t>);
  wsCmdFunc.push_back(&MainWindow::cmd_edtLength);
  ws.push_back(w["ckbRetrigger"] = new Widget<MainWindow, ckb_t>);
  wsCmdFunc.push_back(&MainWindow::cmd_ckbRetrigger);
  ws.push_back(w["ckbEdgeMode"] = new Widget<MainWindow, ckb_t>);
  wsCmdFunc.push_back(&MainWindow::cmd_ckbEdgeMode);
  ws.push_back(w["ckbRising"] = new Widget<MainWindow, ckb_t>);
  wsCmdFunc.push_back(&MainWindow::cmd_ckbRising);
  ws.push_back(w["edtThreshold"] = new Widget<MainWindow, edt_t>);
  wsCmdFunc.push_back(&MainWindow::cmd_edtThreshold);
  ws.push_back(w["edtOffset"] = new Widget<MainWindow, edt_t>);
  wsCmdFunc.push_back(&MainWindow::cmd_edtOffset);
}
ChannelDetailsWindow::~ChannelDetailsWindow() {
  for (auto i : w)
    delete i.second;
  w.clear();
  ws.clear();
  wsCmdFunc.clear();
}
void ChannelDetailsWindow::Create(MainWindow* wnd, int x, int y) {
  for (size_t i = 0; i < ws.size(); i++) {
    int x = 100 + i * 40;
    ws[i]->Create(wnd, x, y, wsCmdFunc[i]);
  }
}
