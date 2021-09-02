#include "Widget.h"
#include "Window.h"

#include <iostream>
using std::cout;
using std::endl;

#include <vector>
#include <string>

class MainWindow;

// widgets in group as a sub-window, which will reside on the MainWindow
class ChannelDetailsWindow : public BaseWindow<ChannelDetailsWindow> {
public:
  ChannelDetailsWindow() {

    ws.push_back(w["rdbChannelEnabled"] = new Widget<ChannelDetailsWindow, rdb_t>);
    wsCmdFunc.push_back(&ChannelDetailsWindow::cmd_rdbChannelEnabled);
    ws.push_back(w["edtPrecursor"] = new Widget<ChannelDetailsWindow, edt_t>);
    wsCmdFunc.push_back(&ChannelDetailsWindow::cmd_edtPrecursor);
    ws.push_back(w["edtLength"] = new Widget<ChannelDetailsWindow, edt_t>);
    wsCmdFunc.push_back(&ChannelDetailsWindow::cmd_edtLength);
    ws.push_back(w["ckbRetrigger"] = new Widget<ChannelDetailsWindow, ckb_t>);
    wsCmdFunc.push_back(&ChannelDetailsWindow::cmd_ckbRetrigger);
    ws.push_back(w["ckbEdgeMode"] = new Widget<ChannelDetailsWindow, ckb_t>);
    wsCmdFunc.push_back(&ChannelDetailsWindow::cmd_ckbEdgeMode);
    ws.push_back(w["ckbRising"] = new Widget<ChannelDetailsWindow, ckb_t>);
    wsCmdFunc.push_back(&ChannelDetailsWindow::cmd_ckbRising);
    ws.push_back(w["edtThreshold"] = new Widget<ChannelDetailsWindow, edt_t>);
    wsCmdFunc.push_back(&ChannelDetailsWindow::cmd_edtThreshold);
    ws.push_back(w["edtOffset"] = new Widget<ChannelDetailsWindow, edt_t>);
    wsCmdFunc.push_back(&ChannelDetailsWindow::cmd_edtOffset);
  }
  virtual ~ChannelDetailsWindow() {
    for (auto i : w)
      delete i.second;
    w.clear();
    ws.clear();
  }
  void Create(MainWindow* wnd, int y) {
    pWnd = wnd;
    for (size_t i = 0; i < ws.size(); i++) {
      int x = 100 + i * 40;
      ws[i]->Create(this, x, y, wsCmdFunc[i]);
    }
  }

  void testMessageProc() {
    cmdProcess(w["edtPrecursor"]->id, 100, 40);
  }


  std::map<std::string, BaseWidget<ChannelDetailsWindow>*> w;

protected:
  void cmd_rdbChannelEnabled(int evt, LPARAM lParam) { cout << "rdbChannelEnabled in chd is clicked!" << endl; }
  void cmd_edtPrecursor(int evt, LPARAM lParam) { cout << "edtPrecursor in chd is clicked!" << endl; }
  void cmd_edtLength(int evt, LPARAM lParam) { cout << "edtLength in chd is clicked!" << endl; }
  void cmd_ckbRetrigger(int evt, LPARAM lParam) { cout << "ckbRetrigger in chd is clicked!" << endl; }
  void cmd_ckbEdgeMode(int evt, LPARAM lParam) { cout << "ckbEdgeMode in chd is clicked!" << endl; }
  void cmd_ckbRising(int evt, LPARAM lParam) { cout << "ckbRising in chd is clicked!" << endl; }
  void cmd_edtThreshold(int evt, LPARAM lParam) { cout << "edtThreshold in chd is clicked!" << endl; }
  void cmd_edtOffset(int evt, LPARAM lParam) { cout << "edtOffset in chd is clicked!" << endl; }

private:
  std::vector<BaseWidget<ChannelDetailsWindow>*> ws; // widgets of sequence
  std::vector<BaseWidget<ChannelDetailsWindow>::CmdFunc> wsCmdFunc; // command functions for widgets of sequence
  MainWindow* pWnd; // parent window
};

// a user-defined main window, containing some standalone widgets and a sub-window including widgets in group
class MainWindow : public BaseWindow<MainWindow> {
public:
  MainWindow() {}
  virtual ~MainWindow() {}

  void Create() {
    // create widgets, and register their individual process functions
    // example of standalone widgets
    rdbChannelEnabled_1.Create(this, 100, 100, &MainWindow::cmd_rdbChannelEnabled_1);
    rdbChannelEnabled_2.Create(this, 200, 100, &MainWindow::cmd_rdbChannelEnabled_2);
    // example of widget in group
    chd.Create(this, 200);
  }

  void testMessageProc() {
    // when receiving message, dispatch to relevant process function according to widget id
    // in WinAPI£¬id = LOWORD(wParam) under the message WM_COMMAND,
    // which is unique of HMENU type as specified by SendMessage
    cmdProcess(rdbChannelEnabled_2.id, 20, 200); // test standalong widgets
    chd.testMessageProc(); // test widgets in group
  }

protected:

  // process functions
  void cmd_rdbChannelEnabled_1(int evt, LPARAM lParam) { cout << "rdbChannelEnabled_1 clicked!" << endl; }
  void cmd_rdbChannelEnabled_2(int evt, LPARAM lParam) { cout << "rdbChannelEnabled_2 clicked!" << endl; }

  // widgets
  Widget<MainWindow, rdb_t> rdbChannelEnabled_1;
  Widget<MainWindow, rdb_t> rdbChannelEnabled_2;
  ChannelDetailsWindow chd;
};

int main(int argc, char* argv[]) {

  MainWindow mainWindow;
  mainWindow.Create();
  mainWindow.testMessageProc();

  return 0;
}
