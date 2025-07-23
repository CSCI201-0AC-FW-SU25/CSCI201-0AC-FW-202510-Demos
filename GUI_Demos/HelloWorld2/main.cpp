#include <CtrlLib/CtrlLib.h>

using namespace Upp;

GUI_APP_MAIN
{
	TopWindow w;
	w.Title("Hello World").Sizeable();
	w.SetRect(0,0,500,300);
	w.Run();
}
