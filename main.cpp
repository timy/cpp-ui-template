#include "MainWindow.h"
#include "Widget.h"

int main(int argc, char* argv[]) {

  MainWindow mainWindow;
  mainWindow.Create();
  mainWindow.testMessageProc();

  return 0;
}
